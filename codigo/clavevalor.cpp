#include "clavevalor.h"
#include "listacadenas.h"
#include "checkML.h"

int getTamanno(const tIndicePalabras& idx)
{
	return idx.tam;
}

tRegistroIndicePalabras getRegistro(const tIndicePalabras& idx, int pos)
{
	return idx.tabla[pos];
}

bool buscar(const tIndicePalabras& idx, const string& s)
{
	return (getPosicion(idx, s) != -1);
}

int getPosicionRec(const tIndicePalabras& idx, const string& buscado, int ini, int fin) {
	int pos = -1;

	if (ini <= fin) {
		int mitad = (ini + fin) / 2;
		if (buscado == idx.tabla[mitad].clave) {
			pos = mitad;
		}
		else if (buscado < idx.tabla[mitad].clave) {
			pos = getPosicionRec(idx, buscado, ini, mitad - 1);
		}
		else {
			pos = getPosicionRec(idx, buscado, mitad + 1, fin);
		}
	}

	return pos;
}

int getPosicion(const tIndicePalabras& idx, const string& buscado)
{
	int pos = -1, ini = 0, fin = idx.tam - 1;

	// VERSION RECURSIVA
	return getPosicionRec(idx, buscado, ini, fin);

	// VERISON NORMAL
	/*
	int mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2; // División entera
		if (buscado == idx.tabla[mitad].clave) {
			encontrado = true;
		}
		else if (buscado < idx.tabla[mitad].clave) {
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

void insertar(tIndicePalabras& idx, const string& palabra, const string& nombreArchivo){
	int pos = getPosicion(idx, palabra);
	tRegistroIndicePalabras registro;

	// Si lo encuentra en la 'palabra' como clave en el Indice de palabras
	if (pos != -1)
	{
		// Modificamos el registro
		registro = getRegistro(idx, pos);
		insertar(registro.valor, nombreArchivo);
		idx.tabla[pos] = registro;
	}
	else
	{  
		registro.clave = palabra;
		// Inicializamos la lista de cadenas
		inicializarListaCadena(registro.valor);
		insertar(registro.valor, nombreArchivo);	

		
		// Añadimos el registro al final
		if (idx.tam < idx.capacidad)
		{
			idx.tabla[idx.tam] = registro;
		}
		else
		{
			aumentarCapacidad(idx);
			idx.tabla[idx.tam] = registro;
		}
		idx.tam++;

		// Ordenamos la tabla
		int pos = idx.tam - 1;
		tRegistroIndicePalabras dato, tmp;

		while ((pos > 0) && (idx.tabla[pos].clave < idx.tabla[pos -1].clave))
		{
			tmp = idx.tabla[pos];
			idx.tabla[pos] = idx.tabla[pos - 1];
			idx.tabla[pos - 1] = tmp;
			pos--;
		}
	}
}

void imprimir(const tIndicePalabras& idx)
{
	cout << setw(15) << "CLAVE" << setw(20) << "VALOR" << endl;
	cout << setw(15) << "-----" << setw(20) << "-----" << endl;
	for (int i = 0; i < idx.tam; ++i)
	{
		cout << setw(15) << idx.tabla[i].clave  << setw(0)  << " ==> " << setw(0) << "[ ";
		imprimir(idx.tabla[i].valor);
		cout << " ]" << endl;
	}
}

void inicializarIndice(tIndicePalabras& idx)
{
	idx.tam = 0;
	idx.tabla = new tRegistroIndicePalabras[TAM_INICIAL_REGISTROS];
	idx.capacidad = TAM_INICIAL_REGISTROS;

	for (int i = 0; i < TAM_INICIAL_REGISTROS; i++)
	{
		tRegistroIndicePalabras r;
		
		r.clave = "";
		//r.valor = nullptr;
		
		idx.tabla[i] = r;
	}
}

void aumentarCapacidad(tIndicePalabras& idx){

	//Duplica el tamaño
	tRegistroIndicePalabras * aux = nullptr;

	aux = new tRegistroIndicePalabras[3 * idx.capacidad / 2 + 1];
	for (int i = 0; i < idx.tam; i++)
	{
		aux[i] = idx.tabla[i];
	}

	// Liberamos cada elemento de la tabla anterior
	/*for (int i = 0; i < idx.capacidad; i++)
	{
		liberar(idx.tabla[i].valor);
		idx.tabla[i].clave = "";
	}
*/
	// Liberamos la tabla
	delete[] idx.tabla;

	idx.tabla = aux;
	idx.capacidad = 3 * idx.capacidad / 2 + 1;

	aux = nullptr;
};

void liberar(tIndicePalabras& idx){

	// Liberamos cada elemento de la tabla
	for (int i = 0; i < idx.tam; i++)
	{
		liberar(idx.tabla[i].valor);
		idx.tabla[i].clave = "";
	}

	delete[] idx.tabla;
	idx.tam = 0;
	idx.capacidad = 0;
}