/*
 * Ivan Deza del Alamo 837603
 * David Hudrea Pavlov
 * */
#pragma once
#include "colaGenerica.hpp"
#include <stdlib.h>

//Ident es un long para identificar. Podemos usar la cola generica.

template<typename M, typename I> struct coleccionMon;

template<typename M, typename I> void crear(coleccionMon<M,I> &m);

template<typename M, typename I> int tamaño(const coleccionMon<M,I> &m);

template<typename M, typename I> bool esVacia(const coleccionMon<M,I> &m);

template<typename M, typename I> void anyadir(coleccionMon<M,I> &m, const M &iden, const I &val);

template<typename M, typename I> bool actualizar(coleccionMon<M,I> &m, const M &iden, const I &val);

template<typename M, typename I> bool esta(const coleccionMon<M,I> &m, const M &iden);

template<typename M, typename I> bool obtenerVal(const coleccionMon<M,I> &m, const M &iden, I &val);

template<typename M, typename I> int obtenerNumActu(coleccionMon<M,I> &m, const M &iden);

template<typename M, typename I> int obtenerNumCons(coleccionMon<M,I> &m, const M &iden);

template<typename M, typename I> void registrarConsulta(const coleccionMon<M,I> &m, const M &iden);

//template<typename M, typename I> void borrar(coleccionMon<M,I>, const M &iden);

//Faltan por añadir las del iterador
//template<typename M, typename I> void iniciarIterador(coleccionMon<M,I> &m);

//template<typename M, typename I> bool existeSiguiente(coleccionMon<M,I> &m);

//template<typename M, typename I> void siguienteIdent(coleccionMon<M,I> &m, M &iden);

//template<typename M, typename I> void siguienteVal(coleccionMon<M,I> &m, I &val);

//template<typename M, typename I> int siguienteNumActu(coleccionMon<M,I> &m);

//template<typename M, typename I> int siguienteNumCons(coleccionMon<M,I> &m);

//template<typename M, typename I> bool avanza(coleccionMon<M,I> &m);



template<typename M, typename I>
struct coleccionMon{
  friend void crear<M,I>(coleccionMon<M,I> &m);
  friend int tamaño<M,I>(const coleccionMon<M,I> &m);
  friend bool esVacia<M,I>(const coleccionMon<M,I> &m);
  friend void anyadir<M,I>(coleccionMon<M,I> &m, const M &iden, const I &val);
  friend bool actualizar<M,I>(coleccionMon<M,I> &m, const M &iden, const I &val);
  friend bool esta<M,I>(const coleccionMon<M,I> &m, const M &iden);
  friend bool obtenerVal<M,I>(const coleccionMon<M,I> &m, const M &iden, I &val);
  friend int obtenerNumActu<M,I>(coleccionMon<M,I> &m, const M &iden);
  friend int obtenerNumCons<M,I>(coleccionMon<M,I> &m, const M &iden);
  friend void registrarConsulta<M,I>(const coleccionMon<M,I> &m, const M &iden);
  //friend void borrar<M,I>(coleccionMon<M,I> &m, const M &iden);
  //Operaciones basicas del iterador
  //friend void iniciarIterador<M,I>(coleccionMon<M,I> &m);
  //friend bool existeSiguiente<M,I>(coleccionMon<M, I> &m);
  //friend void siguienteIdent<M,I>(coleccionMon<M, I> &m, M &iden);
  //friend void siguienteVal<M,I>(coleccionMon<M, I> &m, I &val);
  //friend int siguienteNumActu<M,I>(coleccionMon<M, I> &m);
  //friend int siguienteNumCons<M,I>(coleccionMon<M, I> &m);
  //friend void avanza<M,I>(coleccionMon<M, I> &m);

  struct nodo {
    M iden;
    I val;
    nodo* siguiente;
    int numConsultas;
    int numActu;
  };
  nodo* primero;
  nodo* iterador;
  int numElementos;
};

template<typename M, typename I>
void crear(coleccionMon<M,I> &m){
  m.primero = nullptr;
  m.numElementos = 0;
}

template<typename M, typename I>
int tamaño(const coleccionMon<M,I> &m){
  return m.numElementos;
}

template<typename M, typename I>
bool esVacia(const coleccionMon<M, I> &m){
  return m.numElementos == 0;
}

template<typename M, typename I>
void anyadir(coleccionMon<M, I> &m, const M &iden, const I &val){
  if(esVacia(m)){
    typename coleccionMon<M,I>::nodo* nuevoNodo = new typename coleccionMon<M,I>::nodo;
    nuevoNodo->iden = iden;
    nuevoNodo->val = val;
    nuevoNodo->numConsultas = 0;
    nuevoNodo->numActu = 0;
    nuevoNodo->siguiente = nullptr;
    m.primero = nuevoNodo;
    m.numElementos++;
  }
  else {
    if(esta(m,iden)){
      return ;
    }
    typename coleccionMon<M,I>::nodo* aux = m.primero;
    aux->siguiente = m.primero;
    
    while(aux->siguiente != nullptr){
      aux = aux->siguiente;
    }
    typename coleccionMon<M, I>::nodo* nuevoNodo = new typename coleccionMon<M,I>::nodo;
    nuevoNodo->iden = iden;
    nuevoNodo->val = val;
    nuevoNodo->numConsultas = 0;
    nuevoNodo->numActu = 0;
    m.numElementos++;
    aux->siguiente = nuevoNodo;
  }
}

template<typename M, typename I>
bool actualizar(coleccionMon<M,I> &m, const M &iden, const I &newVal){
  bool success = false;
  typename coleccionMon<M,I>::nodo* aux = m.primero;
  while(aux != nullptr){
    if(aux->iden == iden){
      aux->val = newVal;
      aux->numActu++;
      success = true;
      return success; //Para salir antes de la funcion ahorrando tiempo
    }
    aux = aux->siguiente;
  }
  return success;
}

template<typename M, typename I>
bool esta(const coleccionMon<M,I> &m, const M &iden){
  typename coleccionMon<M,I>::nodo* aux = m.primero;
  while(aux != nullptr){
    if(aux->iden == iden){
      return true;
    }
    aux = aux->siguiente;
  }
  return false;
}

template<typename M, typename I>
bool obtenerVal(const coleccionMon<M,I> &m, const M &iden, I &val){
  typename coleccionMon<M,I>::nodo* aux = m.primero;
  while(aux != nullptr){
    if(aux->iden == iden){
      val = aux->val;
      return true;
    }
    aux = aux->siguiente;
  }
  return false;
}

template<typename M, typename I>
int obtenerNumActu(coleccionMon<M, I> &m, const M &iden){
  typename coleccionMon<M, I>::nodo* aux = m.primero;
  while(aux != nullptr){
    if(aux->iden == iden){
      return aux->numActu;
    }
    aux = aux->siguiente;
  }
  return -1; //No se encontró el identificador correcto
}

template<typename M, typename I>
int obtenerNumCons(coleccionMon<M, I> &m, const M &iden){
  typename coleccionMon<M, I>::nodo* aux = m.primero;
  while(aux != nullptr){
    if(aux->iden == iden){
      return aux->numConsultas;
    }
    aux = aux->siguiente;
  }
  return -1; //No se encontró el identificador correcto
}

template<typename M, typename I>
void registrarConsulta(const coleccionMon<M,I> &m, const M &iden){
  typename coleccionMon<M,I>::nodo* aux = m.primero;
  while(aux != nullptr){
    if(aux->iden == iden){
      aux->numConsultas++;
    }
    aux = aux->siguiente;
  }
}



