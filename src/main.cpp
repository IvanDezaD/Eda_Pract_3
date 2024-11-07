#include "colaGenerica.hpp"
#include "coleccionMon.hpp"
#include "informe.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void opcionA(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  //Variables necesarias
  string desc, numAsStr;
  long num;
  informe informe;
  //Leer del fichero
  getline(f,numAsStr);
  num = stoi(numAsStr);
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
  string numAsStr, coment, desc;
  long int num;
  informe nuevoInforme;
  
  getline(f,numAsStr);
  num = stoi(numAsStr);
  
  getline(f,desc);
  getline(f,coment);

  if(esta(listado, num)){
    obtenerVal(listado, num, nuevoInforme);
    cambiarDescripcion(desc, nuevoInforme);
    registrarComentario(coment, nuevoInforme);
    actualizar(listado, num, nuevoInforme);
    of << "CAMBIADO: " << "[ " << num << " ]" << " ;;; " << obtenerNumActu(listado, num) << " ;;; " << obtenerNumCons(listado, num) << " ] --- " << desc << " --- " << coment << " ---" << endl;
  }
  else {
    of << "NO CAMBIADO: " << num << endl;
  }
}

void opcionO(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr;
  long int num;
  getline(f, numAsStr);
  if(esta(listado, num)) {
    informe miInforme;
    registrarConsulta(listado, num);
    obtenerVal(listado, num, miInforme);
    of << "LOCALIZADO: " << "[ " << num << " ;;; " << obtenerNumActu(listado , num) << " ;;; " << obtenerNumCons(listado, num) << " ] --- ( " << comentariosRegistrados(miInforme) << " ) --- " << descripcion(miInforme) << " --- " << endl;
  }
  else{
    of << "NO LOCALIZADO: " << num << endl;
  }
}

void opcionE(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr;
  long int num;

  getline(f, numAsStr);
  num = stoi(numAsStr);

  if(esta(listado, num)){
    of << "CONOCIDO: " << num << endl;
  }
  else{
    of << "DESCONOCIDO: " << num << endl;
  }
}

void opcionB(ifstream &f, ofstream &of, coleccionMon<long int, informe> &listado){
  string numAsStr;
  long int num;

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
  string numAsStr;
  long int num;

  getline(f, numAsStr);
  num = stoi(numAsStr);

  if(esta(listado, num)){
    of << "****INFORME: " << num;
  }
}

int main(int argc, char** argv){
  string fichero=argv[1];
  ifstream f;
  ofstream of; //fichero de salida
  f.open(fichero);
  of.open("salida.txt");
  string instruccion; string salto;
  while(f >> instruccion){
    if(instruccion == "A"){
      opcionA(f, of);
    }
  }
}
