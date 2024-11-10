/* Ivan Deza del Alamo 8376003
 * David Hudrea Pavlov
 * */
#pragma once
#include <stdlib.h>
#include <stdio.h>

template<typename C> struct cola;

//Crea una cola vacia
template<typename C> void crear(cola<C> &c);


//Añade un elemento a la cola c al final
template<typename C> void encolar(cola<C> &c, const C& e);

//Devuelve el primer elemento de la cola c en e. Devuelve false si la cola esta vacia
template<typename C> bool primero(const cola<C> &c, C& e);

//Devuelve true si la cola c esta vacia
template<typename C> bool esVacia(const cola<C> &c);

//Elimina el primer elemento de la cola c, si no esta vacia. Si la cola esta vacia no hace nada
template<typename C> void desenencolar(cola<C> &c);

//Devuelve el numero de elementos de la cola c
template<typename C> int longitud(const cola<C> &c);


//Creacion de un iterador para la cola para recorrerla. El iterador se inicializa en el primer elemento de la cola
template<typename C> void iniciarIterador(cola<C> &c);

//Devuelve true si existe un siguiente elemento en la cola
template<typename C> bool existeSiguiente(const cola<C> &c);

//Devuelve el siguiente elemento de la cola en e.
template<typename C> void siguiente(const cola<C> &c, C& e);

//Avanza el iterador al siguiente elemento de la cola
template<typename C> void avanza(cola<C> &c);

//Libera la memoria de la cola
template<typename C> void liberar(cola<C> &c);


template<typename C>
struct cola{
  //Operaciones basicas de la estructura
  friend void crear<C>(cola<C> &c);
  friend void encolar<C>(cola<C> &c, const C &e);
  friend bool primero<C>(const cola<C> &c, C &e);
  friend bool esVacia<C>(const cola<C> &c);
  friend void desenencolar<C>(cola<C> &c);
  friend int longitud<C>(const cola<C> &c);
  friend void liberar<C>(cola<C> &c);
  //Operaciones basicas del iterador 
  friend void iniciarIterador<C>(cola<C> &c);
  friend bool existeSiguiente<C>(const cola<C> &c);
  friend void siguiente<C>(const cola<C> &c, C &e);
  friend void avanza<C>(cola<C> &c);
  
  private:
    //Estructura basica del nodo
    struct Nodo {
      C dato;
      Nodo *siguiente;
    };
    
    Nodo *primero;
    Nodo *ultimo;
    int numElem;
    Nodo *iterador;
};

template<typename C>
  void crear(cola<C> &c){
  c.ultimo = nullptr;
  c.numElem = 0;
  c.primero = nullptr;
  c.iterador = nullptr;
}

template<typename C>
void encolar(cola<C> &c, const C &e){
  if(esVacia(c)) {
    //Si esta vacia, el inicio es igual al final
    c.ultimo = new typename cola<C>::Nodo;
    c.primero = c.ultimo;
  }
  else{
    c.ultimo->siguiente = new typename cola<C>::Nodo;
    c.ultimo = c.ultimo->siguiente;
  }
  c.ultimo->dato = e;
  c.ultimo->siguiente = nullptr;
  c.numElem++;
}

//Dudas con como devolver el error
template<typename C>
bool primero(const cola<C> &c, C &e){
  if(esVacia(c)) {
    return false;
  }
  e = c.primero->dato;
  return true;
}

template<typename C>
bool esVacia(const cola<C> &c) {
  return c.primero == nullptr || c.numElem == 0;
}

template<typename C>
void desenencolar(cola<C> &c){
  typename cola<C>::Nodo* auxPtr;
  if(!esVacia(c)){
    auxPtr = c.primero;
    c.primero = c.primero->siguiente;
    delete auxPtr;
    c.numElem--;
    if(esVacia(c)){
      c.ultimo = nullptr;
    }
  }
}

template<typename C>
int longitud(const cola<C> &c){
  return c.numElem;
}

template<typename C>
void liberar(cola<C> &c){
  typename cola<C>::Nodo* actual = c.primero;
    while (!esVacia(c)) {
        typename cola<C>::Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
        c.numElem--;
    }
    // Restablecemos los punteros y el contador de elementos
    c.primero = nullptr;
    c.ultimo = nullptr;
    c.iterador = nullptr;
    c.numElem = 0;
}

template<typename C>
void iniciarIterador(cola<C> &c) {
  c.iterador = c.primero;
}

template<typename C>
bool existeSiguiente(const cola<C> &c) {
  return c.iterador->siguiente != nullptr;
}

template<typename C>
void siguiente(const cola<C> &c, C &e){
  e = c.iterador->siguiente->dato;
}

template<typename C>
void avanza(cola<C> &c){
  c.iterador = c.iterador->siguiente;
}
