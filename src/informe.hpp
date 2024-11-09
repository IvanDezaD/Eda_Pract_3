#pragma once

#include<iostream>
using namespace std;
#include "colaGenerica.hpp"

struct informe;

//Dada una cadena descrip devuelve un informe compuesto con descripcion descrip 
//y sin ningun comentario registrado.
void crearInforme(string descrip, informe& i);

//Dado un informe i  formado como (D,C) devuelve la 
//cadena D, i.e. la descripcion en el informe i.
string descripcion(informe& i);

//Dado un informe i formado como (D,C)  devuelve un 
//informe igual al compuesto como (nueva, C)
void cambiarDescripcion(string nueva, informe& i);

//Dado un informe i formado como (D,C), devuelve el
//numero total de comentarios registrados en el informe i.
int comentariosRegistrados(informe& i);

//Dado un informe i formado como (D,C) y un comentario coment,
//devuelve un informe igual al resultante de añañdir el comentario
//coment a los registrados en el informe i, es decir, un informe igual al
//compuesto como (D, encolar(C, coment))
void registrarComentario(string coment, informe& i);

//Dado un informe i formado como (D,C), devuelve una cadena formada con la información detallada
//de todos los comentarios registrados en su C y en el mismo orden en el que fueron registrados,
//empezando por el primero que se registró y acabando por el último registrado.
//Si el informe i no tiene ningún comentario registrado la cadena resultado será la cadena vacía
string comentarios(informe& i);

/*
 * Dado un informe, se libera toda la memoria ocupada, tanto la que ocupa la descripcion como la que ocupa 
 * la cola<C>.
 * */
void liberar(informe &i);

struct informe{
    friend void crearInforme(string descrip, informe& i);
    friend string descripcion(informe& i);
    friend void cambiarDescripcion(string nueva, informe& i);
    friend int comentariosRegistrados(informe& i);
    friend void registrarComentario(string coment, informe& i);
    friend string comentarios(informe& i);
    friend void liberar(informe& i);
    private:

    string descrip;
    cola<string> comentarios;

};

