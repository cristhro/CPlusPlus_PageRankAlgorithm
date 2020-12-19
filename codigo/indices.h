#ifndef INDICES_H_
#define INDICES_H_

#include "clavevalor.h"
#include "listacadenas.h"
#include "matriz.h"
#include <fstream>
#include <algorithm>
#include <cctype>

/*
	Funcion que devuelve 'true' si el carcater 'c' es un espacio
*/
bool isspace(char c);
/*
	Funcion que devuelve 'true' si el caracter es un simbolo de puntuacion
*/
bool ispunct(char c);
/*
	Procedimiento que crea la tabla de indices a partir del archivo inicial, al mismo tiempo inicializa la matriz 'L'
*/
bool crearTabla(tIndicePalabras & tabla, tListaCadenas & totales, const string &archivoInicial, tMatriz & L);
/*
	Procedimiento que se encarga de leer las palabras
	y los enlaces del fichero para luego clasificarlos en la tabla de indice 'tabla' y de inicializar la matriz 'L'
*/
void procesarFicheroEnTabla(istream& fichero, tIndicePalabras& tabla, string nombreArchivo, tListaCadenas &visitado, tListaCadenas &noVisitado, tListaCadenas & totales, tMatriz & L, int &j);
/*
	Procedimiento que se encarga de abrir un fichero y comprobar los posibles errores,
	si el fichero esta abierto correctamente
		entonces llama a la funcion 'procesarFicheroEnTabla'
*/
bool ejecutarLeerFichero(const string& nombreArchivo, tIndicePalabras& tabla, tListaCadenas &visitado, tListaCadenas &noVisitado, tListaCadenas & totales, tMatriz & L, int &j);
/*
	Funcion que devuelve 'true' si el string 's' es un enlace del tipo (<enlace.txt>)
*/
bool esEnlace(string s);
/*
	Funcion que a partir de un enlace string 's' devuelve el enlace sin los ('<' y '>')
*/
string getEnlace(string s);

#endif /* INDICES_H_ */
