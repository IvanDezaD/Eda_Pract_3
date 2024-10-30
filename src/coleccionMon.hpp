/*
 * Ivan Deza del Alamo 837603
 * David Hudrea Pavlov
 * */
#pragma once
#include "colaGenerica.hpp"
#include <stdlib.h>

//Implementacion primitiva del tipo iden
struct iden{
  int id;
  iden* anterior;
};

bool operator==(iden i1, iden i2){
  return i1.id == i2.id;
}

void idAnterior(iden i, iden *anterior){
  anterior = i.anterior;
}

template<typename M> struct coleccionMon;

template<typename M> void crear(coleccionMon<M> &m);

template<typename M> void tamaño(coleccionMon<M> &m);

template<typename M> void esVacia(coleccionMon<M> &m);

template<typename M> void anyadir(coleccionMon<M> &m, iden id, void* val); //De momento dejo un puntero a void para pensar que usaremos

template<typename M> bool actualizar(coleccionMon<M> &m, iden id, void* newVal); //lo mismo que lo anterior

template<typename M> bool esta(coleccionMon<M> &m, iden id);

template<typename M> void* obtenerVal(coleccionMon<M> &m, iden id);

template<typename M> int obtenerNumActu(coleccionMon<M> &m, iden id);

template<typename M> int obtenerNumCons(coleccionMon<M> &m, iden id);

template<typename M> void registrarConsulta(coleccionMon<M>, iden id);

template<typename M> void borrar(coleccionMon<M>, iden id);

//Faltan por añadir las del iterador
template<typename M> void iniciarIterador(coleccionMon<M> &m);

template<typename M> bool existeSiguiente(coleccionMon<M> &m);

template<typename M> void siguienteIdent(coleccionMon<M> &m, iden &id);

template<typename M> void siguienteVal(coleccionMon<M> &m, void* val);

template<typename M> void siguienteNumActu(coleccionMon<M> &m, int* numActu);

template<typename M> void siguienteNumCons(coleccionMon<M> &m, int* numCons);

template<typename M> bool avanza(coleccionMon<M> &m);



template<typename M>
struct coleccionMon{
  friend void crear<M>(coleccionMon<M> &m);
  friend void tamaño<M>(coleccionMon<M> &m);
  friend void esVacia<M>(coleccionMon<M> &m);
  friend void anyadir<M>(coleccionMon<M> &m, iden id, void *val);
  friend bool actualizar<M>(coleccionMon<M> &m, iden id, void *newVal);
  friend bool esta<M>(coleccionMon<M> &m, iden id);
  friend void* obtenerVal<M>(coleccionMon<M>, iden id);
  friend int obtenerNumActu<M>(coleccionMon<M> &m, iden id);
  friend int obtenerNumCons<M>(coleccionMon<M> &m, iden id);
  friend void registrarConsulta<M>(coleccionMon<M>, iden id);
  friend void borrar<M>(coleccionMon<M>, iden id);
  //Operaciones basicas del iterador
  
};





