/*
 * Ivan Deza del Alamo 837603
 * David Hudrea Pavlov
 * */
#pragma once
#include "colaGenerica.hpp"
#include <stdlib.h>

// Ident es un long para identificar. Podemos usar la cola generica.



template <typename M, typename I> struct coleccionMon;

//Funcion para crear una coleccion vacia
template <typename M, typename I> void crear(coleccionMon<M, I> &m);

//Funcion para obtener el tamaño de la coleccion m
template <typename M, typename I> int tamaño(const coleccionMon<M, I> &m);

//Funcion para saber si la coleccion esta vacia
template <typename M, typename I> bool esVacia(const coleccionMon<M, I> &m);

//Añade un par identificador-valor a la coleccion. Si ya existe el identificador, no hace nada
template <typename M, typename I>
void anyadir(coleccionMon<M, I> &m, const M &iden, const I &val);

//Actualiza el valor asociado a un identificador. Si no existe el identificador, devuelve false
template <typename M, typename I>
bool actualizar(coleccionMon<M, I> &m, const M &iden, const I &val);

//Devuelve true si el identificador esta en la coleccion
template <typename M, typename I>
bool esta(const coleccionMon<M, I> &m, const M &iden);


//Devuelve el valor asociado a un identificador. Si no existe el identificador, devuelve false
template <typename M, typename I>
bool obtenerVal(const coleccionMon<M, I> &m, const M &iden, I &val);

//Devuelve el numero de actualizaciones de un identificador. Si no existe el identificador, devuelve -1
template <typename M, typename I>
int obtenerNumActu(coleccionMon<M, I> &m, const M &iden);

//Devuelve el numero de consultas de un identificador. Si no existe el identificador, devuelve -1
template <typename M, typename I>
int obtenerNumCons(coleccionMon<M, I> &m, const M &iden);

//Registra una consulta de un identificador dado. Si no existe el identificador, devuelve false
template <typename M, typename I> bool registrarConsulta(const coleccionMon<M, I> &m, const M &iden);

//Borra un identificador de la coleccion. Si no existe el identificador, no hace nada
template<typename M, typename I> void borrar(coleccionMon<M,I> &m);

//Funciones del iterador

//Funcion que inicializa el iterador para recorrer la coleccion, donde el siguiente nodo a visitar es el de iden menor a los demas
template<typename M, typename I> void iniciarIterador(coleccionMon<M,I> &m);

//Funcion que devuelve true si existe un siguiente nodo a visitar
template<typename M, typename I> bool existeSiguiente(coleccionMon<M,I> &m);

//Funcion que devuelve el siguiente nodo a visitar, incluyendo el identificador, el valor, el numero de actualizaciones y el numero de consultas
//Ademas, avanza el iterador al siguiente nodo
template<typename M, typename I> bool siguienteYAvanza(coleccionMon<M,I> &m, M &iden, I &val, int &numActu, int &numCons);

// El tipo de dato M requerira tener las funciones:
  //  bool operator==(const m& iden1, const m& iden2) devuelve true si los identificadores son iguales
  // bool operator <(const m& iden1, const m& iden2) devuelve true si el identificador 1 es menor que el identificador 2


template <typename M, typename I> struct coleccionMon {
  friend void crear<M, I>(coleccionMon<M, I> &m);
  friend int tamaño<M, I>(const coleccionMon<M, I> &m);
  friend bool esVacia<M, I>(const coleccionMon<M, I> &m);
  friend void anyadir<M, I>(coleccionMon<M, I> &m, const M &iden, const I &val);
  friend bool actualizar<M, I>(coleccionMon<M, I> &m, const M &iden,
                               const I &val);
  friend bool esta<M, I>(const coleccionMon<M, I> &m, const M &iden);
  friend bool obtenerVal<M, I>(const coleccionMon<M, I> &m, const M &iden,
                               I &val);
  friend int obtenerNumActu<M, I>(coleccionMon<M, I> &m, const M &iden);
  friend int obtenerNumCons<M, I>(coleccionMon<M, I> &m, const M &iden);
  friend bool registrarConsulta<M, I>(const coleccionMon<M, I> &m,
                                      const M &iden);
  friend void borrar<M,I>(coleccionMon<M,I> &m);
  //Operaciones basicas del iterador
  friend void iniciarIterador<M,I>(coleccionMon<M,I> &m);
  friend bool existeSiguiente<M,I>(coleccionMon<M, I> &m);
  friend bool siguienteYAvanza<M,I>(coleccionMon<M,I> &m, M &iden, I &val, int &numActu, int &numCons);
  
  struct nodo {
    M iden;
    I val;
    nodo *siguiente;
    int numConsultas;
    int numActu;
  };
  nodo *primero;
  nodo *iterador;
  int numElementos;
};

void liberar(long int){
  //return;
}

template <typename M, typename I> void crear(coleccionMon<M, I> &m) {
  m.primero = nullptr;
  m.numElementos = 0;
}

template <typename M, typename I> int tamaño(const coleccionMon<M, I> &m) {
  return m.numElementos;
}

template <typename M, typename I> bool esVacia(const coleccionMon<M, I> &m) {
  return m.numElementos == 0;
}

template <typename M, typename I>
void anyadir(coleccionMon<M, I> &m, const M &iden, const I &val) {
  typename coleccionMon<M, I>::nodo *aux = m.primero;

  // Si la colección está vacía, inserta el primer nodo
  if (esVacia(m)) {
    typename coleccionMon<M, I>::nodo *primerpar = new typename coleccionMon<M, I>::nodo;
    primerpar->iden = iden;
    primerpar->val = val;
    primerpar->numConsultas = 0;
    primerpar->numActu = 1;
    primerpar->siguiente = nullptr;
    m.primero = primerpar;
    m.numElementos++;
    return;
  }

  if(aux->iden == iden){
    return;
  }

  

  // Si el nuevo elemento debe ir al principio
  if (iden < aux->iden) {
    typename coleccionMon<M, I>::nodo *nuevo = new typename coleccionMon<M, I>::nodo;
    nuevo->iden = iden;
    nuevo->val = val;
    nuevo->numConsultas = 0;
    nuevo->numActu = 1;
    nuevo->siguiente = aux;
    m.primero = nuevo;
    m.numElementos++;
    return;
  }

  // Busca la posición correcta para insertar
  while (aux->siguiente != nullptr && aux->siguiente->iden < iden) {
    aux = aux->siguiente;
  }

  // Verifica si el elemento ya existe para evitar duplicados
  if (aux->siguiente != nullptr && aux->siguiente->iden == iden) {
    return;
  }

  // Inserta el nuevo nodo en la posición correcta
  typename coleccionMon<M, I>::nodo *nuevo = new typename coleccionMon<M, I>::nodo;
  nuevo->iden = iden;
  nuevo->val = val;
  nuevo->numConsultas = 0;
  nuevo->numActu = 1;
  nuevo->siguiente = aux->siguiente;
  aux->siguiente = nuevo;
  m.numElementos++;
}

template <typename M, typename I>
bool actualizar(coleccionMon<M, I> &m, const M &iden, const I &newVal) {
  bool success = false;
  typename coleccionMon<M, I>::nodo *aux = m.primero;
  while (aux != nullptr) {
    if (aux->iden == iden) {
      aux->val = newVal;
      aux->numActu++;
      success = true;
      return success; // Para salir antes de la funcion ahorrando tiempo
    }
    aux = aux->siguiente;
  }
  return success;
}

template <typename M, typename I>
bool esta(const coleccionMon<M, I> &m, const M &iden) {
  typename coleccionMon<M, I>::nodo *aux = m.primero;
  while (aux != nullptr && aux->iden < iden) {
    aux = aux->siguiente;
  }
  if (aux != nullptr && aux->iden == iden) {
    return true;
  }else{
    return false;
  }
}

template <typename M, typename I>
bool obtenerVal(const coleccionMon<M, I> &m, const M &iden, I &val) {
  typename coleccionMon<M, I>::nodo *aux = m.primero;
  while (aux != nullptr && aux->iden < iden) {
    aux = aux->siguiente;
  }
  if (aux != nullptr && aux->iden == iden) {
    val = aux->val;
    return true;
  }else{
    return false;
  }

}

template <typename M, typename I>
int obtenerNumActu(coleccionMon<M, I> &m, const M &iden) {
  typename coleccionMon<M, I>::nodo *aux = m.primero;
  while (aux != nullptr && aux->iden < iden) {
    aux = aux->siguiente;
  }
  if (aux != nullptr && aux->iden == iden) {
    return aux->numActu;
  }else{
    return -1; // No se encontró el identificador correcto
  }
}

template <typename M, typename I>
int obtenerNumCons(coleccionMon<M, I> &m, const M &iden) {
  typename coleccionMon<M, I>::nodo *aux = m.primero;
  while (aux != nullptr && aux->iden < iden) {
    aux = aux->siguiente;
  }
  if (aux != nullptr && aux->iden == iden) {
    return aux->numConsultas;
  }else{
    return -1; // No se encontró el identificador correcto
  }
}

template <typename M, typename I>
bool registrarConsulta(const coleccionMon<M, I> &m, const M &iden) {
  typename coleccionMon<M, I>::nodo *aux = m.primero;
  while (aux != nullptr && aux->iden < iden) {
    aux = aux->siguiente;
  }
  if (aux != nullptr && aux->iden == iden) {
    aux->numConsultas++;
    return true;
  }else{
    return false; // No se encontró el identificador correcto
  }

}


template<typename M,typename I>
void borrar(coleccionMon<M,I> &m, const M &iden){
  typename coleccionMon<M, I>::nodo *aux = m.primero;
  typename coleccionMon<M, I>::nodo *aux2;
  bool parar = false;
  if(esVacia(m)){
    return;
  }
  if (!(iden < m.primero->iden)){
    if (m.primero->iden == iden){
      m.primero = m.primero->siguiente;
      liberar(aux->iden);
      liberar(aux->val);
      delete aux;
      m.numElementos--;
    }
    else{
      aux2 = m.primero;
      aux = m.primero->siguiente;
      while(aux != nullptr && !parar){
        if(iden < aux->iden){
          parar=true;
        }else if(aux->iden == iden){
          aux2->siguiente = aux->siguiente;
          parar=true;
          liberar(aux->iden);
          liberar(aux->val);
          delete aux;
          m.numElementos--;
        }
        else{
          aux2 = aux;
          aux = aux->siguiente;
        }
      }
    }
  }
}

template<typename M, typename I>
void borrarTodaLaColeccion(coleccionMon<M, I> &m) {
    typename coleccionMon<M, I>::nodo *aux = m.primero;
    typename coleccionMon<M, I>::nodo *temp;

    while (aux != nullptr) {
        temp = aux->siguiente;  // Guarda el siguiente nodo
        liberar(aux->iden); // Libera la memoria del identificador (si es necesario)
        liberar(aux->val);      // Libera la memoria del valor (si es necesario)
        delete aux;             // Elimina el nodo actual
        aux = temp;             // Avanza al siguiente nodo
    }

    // Restablecer la colección a su estado vacío
    m.primero = nullptr;
    m.numElementos = 0;
}

template<typename M, typename I>
void iniciarIterador(coleccionMon<M,I> &m){
  m.iterador = m.primero;
}

template<typename M, typename I>
bool existeSiguiente(coleccionMon<M,I> &m){
  return m.iterador->siguiente != nullptr;
}

template<typename M, typename I>
bool siguienteYAvanza(coleccionMon<M,I> &m, M &iden, I &val, int &numActu, int &numCons){
  bool result;
  if(m.iterador != nullptr){
    iden = m.iterador->iden;
    val = m.iterador->val;
    numActu = m.iterador->numActu;
    numCons = m.iterador->numConsultas;
    m.iterador = m.iterador->siguiente;
    result = true;
  }else{
    result = false;
  }
  return result;
}

