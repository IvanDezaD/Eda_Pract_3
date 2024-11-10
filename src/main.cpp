#include <iostream>
#include <fstream>
#include <ostream>
#include <stdlib.h>
#include "colaGenerica.hpp"
#include "coleccionMon.hpp"
#include "informe.hpp"

using namespace std;

void opcionA(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  //Variables necesarias
  string desc, numAsStr, junk;
  long int num;
  informe informe;
  //Leer del fichero
  getline(f, junk);
  getline(f,numAsStr);
  num = stol(numAsStr);
  getline(f, desc);
  //Si no esta el numero registrado lo que haremos sera añadirlo
  if(!esta(listado, num)){
    //Si no esta el numero registrado lo que haremos sera crear el informe asociado e introducirlo
    crearInforme(desc, informe);
    anyadir(listado, num, informe);
    of << "INTRODUCIDO: ";
  }
  else{
    of << "NO INTRODUCIDO: ";
  }
  of << "[ " << num << " ] --- " << desc << endl;
}

void opcionC(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr, coment, desc, junk;
  long int num;
  informe nuevoInforme;

  getline(f, junk);
  getline(f,numAsStr);
  
  num = stol(numAsStr);
  
  getline(f,desc);
  getline(f,coment);

  if(obtenerVal(listado, num, nuevoInforme)){
    cambiarDescripcion(desc, nuevoInforme);
    registrarComentario(coment, nuevoInforme);
    actualizar(listado, num, nuevoInforme);
    of << "CAMBIADO: " << "[ " << num << " ;;; " << obtenerNumActu(listado, num) << " ;;; " << obtenerNumCons(listado, num) << " ] --- " << desc << " --- " << coment << " ---" << endl;
  }
  else {
    of << "NO CAMBIADO: " << num << endl;
  }
}

void opcionO(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr, junk;
  long int num;
  getline(f, junk);
  getline(f, numAsStr);
  num = stol(numAsStr);
  if(registrarConsulta(listado, num)) {
    informe miInforme;
    obtenerVal(listado, num, miInforme);
    of << "LOCALIZADO: " << "[ " << num << " ;;; " << obtenerNumActu(listado , num) << " ;;; " << obtenerNumCons(listado, num) << " ] --- ( " << comentariosRegistrados(miInforme) << " ) --- " << descripcion(miInforme) << " ---" << endl;
  }
  else{
    of << "NO LOCALIZADO: " << num << endl;
  }
}

void opcionE(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr, junk;
  long int num;

  getline(f, junk);
  getline(f, numAsStr);
  num = stol(numAsStr);

  if(esta(listado, num)){
    of << "CONOCIDO: " << num << endl;
  }
  else{
    of << "DESCONOCIDO: " << num << endl;
  }
}

void opcionB(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr, junk;
  long int num;

  getline(f, junk);
  getline(f, numAsStr);
  num = stoi(numAsStr);
  
  if(esta(listado, num)){
    borrar(listado, num);
    of << "BORRADO: " << num << endl;
  }
  else {
    of << "NO BORRADO: " << num << endl;
  }
}

void opcionLI(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr, junk;
  long int num;
  
  getline(f, junk);
  getline(f, numAsStr);
  num = stoi(numAsStr);
  informe miInforme;

  of << "****INFORME: " << num << endl;
  if(obtenerVal(listado, num, miInforme)){
    registrarConsulta(listado, num);
        of << descripcion(miInforme) << endl;
    if(comentariosRegistrados(miInforme) > 0){
      of << comentarios(miInforme) << endl;
    }
    of << "****TOTALES: Act->( " << obtenerNumActu(listado, num) << " ) Cons->( " << obtenerNumCons(listado, num) << " ) Coment->( " << comentariosRegistrados(miInforme) << " )" << endl;
  }
  else{
    of << "****DESCONOCIDO" << endl;
  }
}

void opcionLT(ofstream &of, coleccionMon<long int, informe> &listado){
  //Declaracion de variables
  informe miInforme;
  long int num;
  int numActu;
  int numCons;
  
  of << "-----LISTADO: " << tamaño(listado) << endl;
  
  if(esVacia(listado)){
    of << "-----" << endl;
    return;
  }
  //Ponemos el iterador al principio del todo.
  iniciarIterador(listado); //Verificado que el iterador se inicializa correctamente
  while(siguienteYAvanza(listado, num, miInforme, numActu, numCons)){

    of << "[ " << num << " ;;; " << numActu << " ;;; " << numCons
    << " ] --- ( " << comentariosRegistrados(miInforme) << " ) --- " << descripcion(miInforme)
    << " ---" << endl;
  }
  of << "-----" << endl;
}

int main(int argc, char** argv){
  if(argc != 2){
    printf("Numero de parametros mal introducido, ejemplo de uso: ./programa entrada.txt\n");
  }
  string fichero=argv[1];
  ifstream f;
  ofstream of; //fichero de salida

  f.open(fichero);
  of.open("salida.txt");

  if(f.is_open()){

    coleccionMon<long int, informe> listado;
    crear(listado);
    string instruccion; string salto;
    while(f >> instruccion){
      if(instruccion == "A"){
        opcionA(f, of, listado);
      }
      else if (instruccion == "O"){
        opcionO(f, of,  listado);
      }
      else if(instruccion == "E"){
        opcionE(f, of, listado);
      }
      else if(instruccion == "B"){
        opcionB(f, of, listado);
      }
      else if(instruccion == "C") {
        opcionC(f,of,listado);
      }
      else if(instruccion == "LT") {
        opcionLT(of,listado);
      }
      else if(instruccion == "LI"){
        opcionLI(f,of,listado);
      }
    }
    borrarTodaLaColeccion(listado);
  }
  else{
    cout << "NO SE HA PODIDO ENCONTRAR EL FICHERO" << endl;
  }
}
