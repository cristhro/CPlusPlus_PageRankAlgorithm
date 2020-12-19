#ifndef CLAVEVALOR_H_
#define CLAVEVALOR_H_

#include <string>
#include <iostream>
#include "listacadenas.h" // modulo listacadenas
#include <iomanip>

using namespace std;

/************************************
* DECLARACION DE TIPOS Y CONSTANTES *
*************************************/
typedef struct
{
	string clave;
	tListaCadenas valor;
} tRegistroIndicePalabras;

const int TAM_MAX_REGISTROS = 200;
const int TAM_INICIAL_REGISTROS = 1;
typedef tRegistroIndicePalabras tListaRegistro[TAM_MAX_REGISTROS];

typedef struct
{
	tRegistroIndicePalabras *tabla;
	int tam;
	int capacidad;
} tIndicePalabras;

/*********************************************************************************************************
*                               DECLARACION DE METODOS Y FUNCIONES                                       *
**********************************************************************************************************/

/**
 * \brief Devuelve el tamaño de la tabla
 * \param  
 * \return 
 */
int getTamanno(const tIndicePalabras& idx);
/**
 * \brief devuelve registro en posicion 'pos'
 * \param l 
 * \param pos 
 * \return 
 */
tRegistroIndicePalabras getRegistro(const tIndicePalabras& idx, int pos);
/**
 * \brief Devuelve true si la palabra es una clave en la tabla y false en caso contrario.
 * \param l 
 * \param s 
 * \return 
 */
bool buscar(const tIndicePalabras& idx, const string& s);
/**
 * \brief Devuelve la posicion del regisro cuya clave es s, -1 si ¬Existe
 * \param l 
 * \param s 
 * \return 
 */
int getPosicion(const tIndicePalabras& idx, const string& s);
/**
 * \brief Si palabra es ya una clave de la tabla,
		  * añade nombreArchivo a la   lista   de   archivos   correspondiente. 
		  * Si   no,   crea   un   registro   nuevo   con   esainformación 
 * \param idx 
 * \param palabra 
 * \param nombreArchivo 
 */
void insertar(tIndicePalabras& idx, const string& palabra, const string& nombreArchivo);
/**
 * \brief imprime la tabla 
 * \param idx 
 */
void imprimir(const tIndicePalabras& idx);
/**
 * \brief Inicializa el indice
 * \param idx 
 */
void inicializarIndice(tIndicePalabras& idx);
/**
* \brief Devuelve la posicion del regisro cuya clave es s, -1 si no Existe (Recursiva) 
* \param l
* \param buscado
* \param ini
* \param fin
* \return
*/
int getPosicionRec(const tIndicePalabras& idx, const string& buscado, int ini, int fin);

void aumentarCapacidad(tIndicePalabras& idx);

void liberar(tIndicePalabras& idx);
#endif /* CLAVEVALOR_H_ */
