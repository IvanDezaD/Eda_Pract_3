#include "informe.hpp"
#include <string>

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
      resultado += "[ 1 --> ";
      resultado += comment;
      resultado += " ---];;";
      int iter = 2;
      while(existeSiguiente(i.comentarios)){
        siguiente(i.comentarios,comment);
        resultado += "[ ";
        resultado += to_string(iter);
        resultado += " --> ";
        resultado += comment;
        resultado += " ---];;";
        avanza(i.comentarios);
        iter++;
      }

      return resultado;

    }
}

void liberar(informe &i){
  i.descrip.clear();
  liberar(i.comentarios);
}
