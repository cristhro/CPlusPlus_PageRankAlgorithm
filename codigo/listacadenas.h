#ifndef LISTACADENAS_H_
#define LISTACADENAS_H_

#include <string>
#include <iostream>

using namespace std;

/************************************
* DECLARACION DE TIPOS Y CONSTANTES *
*************************************/
const int TAM_MAX = 100;
const int TAM_INICIAL = 3;


typedef struct
{
	int tam;
	string *lista;
	int numElem;
	int capacidad;
} tListaCadenas;

/*********************************************************************************************************
*                               DECLARACION DE METODOS Y FUNCIONES                                       *
**********************************************************************************************************/
/**
 * \brief  Inicializa los atributos de la lista 'l' a una cadena vacia
 * \param l 
 */
void inicializarListaCadena(tListaCadenas& l);
/**
 * \brief Devuelve el tamaño de la lista 'l'
 * \param l 
 * \return 
 */
int getTamanno(const tListaCadenas& l);
/**
 * \brief Devuelve 1 cadena en la posición 'pos' de la lista 'l'
 * \param l 
 * \param pos 
 * \return 
 */
string getCadena(const tListaCadenas& l, int pos);
/**
 * \brief Inserta un elemento al final de la lista 'l' si el elemento 's' no existe
 * \param l 
 * \param s 
 */
void insertar(tListaCadenas& l, const string& s);
/**
 * \brief  Devuelve true si lacadena está en la lista, y false si no.
 * \param l 
 * \param s 
 * \return 
 */
bool buscar(const tListaCadenas& l, const string& s);
/**
* \brief  Devuelve la pos en la que se encuentra el string 's' , -1 si no lo encuentra
* \param l
* \param s
* \return
*/
int getPosicion(const tListaCadenas& l, const string& s);
/**
* \brief  Devuelve la pos en la que se encuentra el string 's' , -1 si no lo encuentra
* \param l
* \param buscado
* \param ini
* \param fin
* \return
*/
int getPosicionRec(const tListaCadenas& l, const string& buscado, int ini, int fin);
/**
 * \brief Elimina el elemento en la posicion 'pos' de la lista 'l'
 * \param l 
 * \param pos 
 */
void eliminar(tListaCadenas& l, int pos);
/**
 * \brief  Imprime los elem. de la lista 'l'.
 * \param l 
 */
void imprimir(const tListaCadenas& l);
/**
 * \brief Funcion que devuelve true si la lista 'l' esta vacia
 * \param l 
 * \return 
 */
bool estaVacia(const tListaCadenas& l);

int getPosicionOcupada(tListaCadenas& l);

void aumentarCapacidad(tListaCadenas & l);

void liberar(tListaCadenas & l);
#endif /* LISTACADENAS_H_ */
