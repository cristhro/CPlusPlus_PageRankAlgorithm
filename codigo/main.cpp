/*
	Nombre: practica 4
	Autores : Cristhian Rodriguez Gomez y Luis Mathioux Abad
	Fecha : 14 / 05 / 2017
	Descripcion : Buscador de información.
*/

#include <iostream>	// cout, cin
#include <fstream>	// istream, ostream, ifstream, ofstream
#include <string>
#include "conio.h"
#include "pagerank.h"
#include "checkML.h"

using namespace std;


void metodoPrincipal();

void metodoPrincipal() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << "Buscador Fdi Fp " << endl << endl << endl << endl;

	tIndicePalabras tabla;
	tListaCadenas totales;
	tListaPageRank pageRank;
	tMatriz L, M;
	tVector X;	// lista que contiene el rank de cada pagina
	string archivoInicial = "A.txt";
	string palabra;
	bool tablaCreada = false;

	L = matrizConstante(0.0, MAX_MATRIZ - 1);

	// Inicializar tabla y totales
	inicializarListaCadena(totales);
	inicializarIndice(tabla);

	// Pedimos el fichehro inicial
	cout << "Por favor, introduzca el nombre del fichero raiz a partir del " << endl << "que se creara el indice (ej: nombreFich.txt ): ";
	cin >> archivoInicial;

	// Creamos el indice con el archivo inicial
	tablaCreada = crearTabla(tabla, totales, archivoInicial, L);

	if (tablaCreada)
	{
		// desdeEnlacesAMatriz
		M = desdeEnlacesAMatrizSimple(L);
		X = vectorPropio(M);

		imprimir(tabla);
		// Page Rank
		// crearListaPageRank(pageRank, totales, X);

		cout << endl << "Introduce una palabra ('fin' para terminar ):";
		cin >> palabra;
		cout << endl;

		while (palabra != "fin") {

			int pos = -1;
			pos = getPosicion(tabla, palabra);

			if (pos != -1) {

				tRegistroIndicePalabras registro;
				registro = getRegistro(tabla, pos);
				tListaPageRank pr = getListaPageRankBusqueda(pageRank, registro.valor);
				normalizarListaPageRank(pr);
				mostrarListaPageRank(pr);
			}
			else {
				cout << "AVISO: Palabra no encontrada!" << endl;
			}
			// Siguiente palabra
			cout << endl << "Introduce una palabra ('fin' para terminar ):";
			cin >> palabra;
			cout << endl;

		}
	}
	else {
		cout << "ERROR: no se ha posido crear las tablas " << endl;
	}

	// Liberamos totales
	liberar(totales);
	liberar(tabla);
}

int main()
{	
	// pruebaTabla();
	metodoPrincipal();
	
	system("PAUSE");
	return 0;
}


