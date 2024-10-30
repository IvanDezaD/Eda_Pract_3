/* Ivan Deza del Alamo 8376003
 * David Hudrea Pavlov
 * */
#pragma once
#include <stdlib.h>

template<typename C> struct cola;

template<typename C> void crear(cola<C> &c);

template<typename C> void encolar(cola<C> &c, const C& e);

template<typename C> bool primero(const cola<C> &c, C& e);

template<typename C> bool esVacia(const cola<C> &c);

template<typename C> void desenencolar(cola<C> &c);

template<typename C> int longitud(cola<C> &c);

template<typename C> void iniciarIterador(cola<C> &c);

template<typename C> bool existeSiguiente(cola<C> &c);

template<typename C> void siguiente(cola<C> &c, C& e);

template<typename C> void avanza(cola<C> &c);


template<typename C>
struct cola{
  //Operaciones basicas de la estructura
  friend void crear<C>(cola<C> &c);
  friend void encolar<C>(cola<C> &c, const C &e);
  friend bool primero<C>(const cola<C> &c, C &e);
  friend bool esVacia<C>(const cola<C> &c);
  friend void desenencolar<C>(cola<C> &c);
  friend int longitud<C>(const cola<C> &c);
  //Operaciones basicas del iterador 
  friend void iniciarIterador<C>(cola<C> &c);
  friend bool existeSiguiente<C>(const cola<C> &c);
  friend void siguiente<C>(const cola<C> &c, C &e);
  friend void avanza<C>(const cola<C> &c);
  
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
void primero(const cola<C> &c, C &e){
  e = c.primero->dato;
}

template<typename C>
bool esVacia(const cola<C> &c) {
  return c.primero == nullptr;
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
