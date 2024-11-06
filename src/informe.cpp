#include "informe.hpp"
#include<iostream>

using namespace std;

void crearInforme(string descrip, informe& i){
    i.descrip = descrip;
    crear(i.comentarios);
    
}

string descripcion(informe& i){
    return i.descrip;
}


void cambiarDescripcion(string nueva, informe& i){
    i.descrip= nueva;
}

int comentariosRegistrados(informe& i){
    return longitud(i.comentarios);
}

void registrarComentario(string coment, informe& i){
    encolar(i.comentarios, coment);
}

string comentarios(informe& i){
  string resultado = "";
    string comment;


    if(esVacia(i.comentarios)){
      return resultado;
    }
    else {
      iniciarIterador(i.comentarios);
      primero(i.comentarios,comment);
      resultado = comment;
      while(existeSiguiente(i.comentarios)){
        siguiente(i.comentarios,comment);
        resultado += comment;  
        avanza(i.comentarios);

      }

      return resultado;

    }
}
