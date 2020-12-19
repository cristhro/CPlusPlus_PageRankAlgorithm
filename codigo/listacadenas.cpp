#include "listacadenas.h"
#include "checkML.h"

/*********************************************************************************************************
*                               IMPLEMENTACION DE METODOS Y FUNCIONES                                    *
**********************************************************************************************************/

void inicializarListaCadena(tListaCadenas& l)
{
	// Inicializamos el tamaño variable de la lista a cero
	l.tam = 0;
	l.numElem = 0;
	l.capacidad = TAM_INICIAL;
	l.lista = new string[TAM_INICIAL];

	// Inicializamos todos los elementos de la lista de cadenas a una cadena vacia
	for (int i = 0; i < l.capacidad; i++)
	{
		l.lista[i] = "";
	}
}

int getTamanno(const tListaCadenas& l)
{
	return l.tam;
}

string getCadena(const tListaCadenas& l, int pos)
{
	return l.lista[pos];
}

void insertar(tListaCadenas& l, const string& s)
{	
	int posicion = getPosicion(l, s);

	// SI NO EXISTE
	if (!buscar(l, s))
	{
		//INSERTA UN NUEVO ELEMENTO
		if (l.tam < l.capacidad)
		{
			l.lista[l.tam] = s;
		}
		else
		{
			aumentarCapacidad(l);
			l.lista[l.tam] = s;
		}
		l.tam++;
		l.numElem++;

		// ORDENAMOS LA LISTA
		int pos = l.tam - 1;
		string tmp;

		while ((pos > 0) && (l.lista[pos] < l.lista[pos - 1]))
		{
			tmp = l.lista[pos];
			l.lista[pos] = l.lista[pos - 1];
			l.lista[pos - 1] = tmp;
			pos--;
		}
	}
}

bool buscar(const tListaCadenas& l, const string& s)
{
	// Llamada Rec
	return (getPosicion(l, s) != -1);
}

int getPosicionRec(const tListaCadenas& l, const string& buscado, int ini, int fin) {
	int pos = -1;

	if (ini <= fin) {
		int mitad = (ini + fin) / 2;

		if (buscado == l.lista[mitad]) {
			pos = mitad;
		}
		else if (buscado < l.lista[mitad]) {
			pos = getPosicionRec(l, buscado, ini, mitad - 1);
		}
		else {
			pos = getPosicionRec(l, buscado, mitad + 1, fin);
		}
	}

	return pos;
}

int getPosicion(const tListaCadenas& l, const string& buscado){

	int pos = -1, ini = 0, fin = l.tam - 1;
	
	// VERSION RECURSIVA
	return getPosicionRec(l, buscado, ini, fin);

	// VERSION NORMAL
	/*
	bool encontrado = false;
	int mitad;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2; // División entera
		if (buscado == l.lista[mitad]) {
			encontrado = true;
		}
		else if (buscado < l.lista[mitad]) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	}
	if (encontrado) {
		pos = mitad;
	}

	return pos;
	*/
	
}

void eliminar(tListaCadenas& l, int pos)
{
	// Modificamos el elemento del 'lista' en la 'pos' con una cadena vacia
	if (pos >= 0 && pos < l.tam){
		l.lista[pos] = "";
		l.numElem--;
	}

}

void imprimir(const tListaCadenas& l)
{	
	for (int i = 0; i < l.tam; i++)
	{
		cout << l.lista[i] ;
		if (i < l.tam - 1) cout << ", ";
	}
}

bool estaVacia(const tListaCadenas& l)
{
	return (l.numElem == 0);
}

int getPosicionOcupada(tListaCadenas& l)
{
	bool encontrado = false;
	int pos = 0;

	// Recorremos el 'lista' de la lista 'l' desde la pos 0 hasta el tamaño que tenga la lista 'l.tam'
	// Seguimos recorriendo hasta encontrar un string no vacio
	while (pos < l.tam && !encontrado)
	{
		// Si conincide el string 's' con un elemento del lista en la pos 
		if (l.lista[pos] != "")
		{
			// Entonces actualizamos la variable 'encontrado a true' con esto sale del bucle
			encontrado = true;
		}
		else
		{
			// En caso de no encontrar el string 's' seguimos la busqueda en la siguiente 'pos'
			pos++;
		}
	}
	
	return pos;
}

void aumentarCapacidad(tListaCadenas & l){
	//Duplica el tamaño
	string * aux = nullptr;

	aux = new string[3 * l.capacidad / 2 + 1];
	for (int i = 0; i < l.tam; i++)
	{
		aux[i] = l.lista[i];
	}
	delete[] l.lista;	
	
	l.lista = aux;
	l.capacidad = 3 * l.capacidad / 2 + 1;

	aux = nullptr;
}

void liberar(tListaCadenas & l){
	delete[] l.lista;
	l.tam = 0;
	l.capacidad = 0;
	l.numElem = 0;
	l.lista = NULL;
};