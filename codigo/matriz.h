#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <string>
#include <iostream>

using namespace std;


const int MAX_MATRIZ = 50;
typedef struct {
	double matriz[MAX_MATRIZ][MAX_MATRIZ];
	int dim;	// dimension de la matriz
}tMatriz;

const int MAX_VECTOR = 50;

typedef struct {
	double vector[MAX_VECTOR];
	int tam;
}tVector;

/*
	Crea una matriz de n ∙ n , en la que todos los valores iniciales son x.
*/
tMatriz matrizConstante(double x, int n);
/*
	Multiplica una matriz por un Vector
*/
tVector operator*(const tMatriz & m, const tVector & v);
/*
	Obtiene la matriz que se obtiene multiplicando cada elemento de m por x.
*/
tMatriz operator*(double x, const tMatriz & m);
/*
	Suma dos matrices.
*/
tMatriz operator+(const tMatriz & m1, const tMatriz & m2);
/*
	Devuelve la matriz M obtenida de L como en la introducción de la sección 4.

*/
tMatriz desdeEnlacesAMatriz(const tMatriz & L);

tMatriz desdeEnlacesAMatrizSimple(const tMatriz & L);

tVector normaliza(const tVector & v);

tVector vectorPropio(const tMatriz & M);

bool  operator!= (const tVector & v1, const tVector & v2);

double redondear_numero(double numero);
/*
	Procedimiento que inicializa el vector 'v' con el valor 'a'
*/
void inicializar(tVector & v, double a);
void imprimir(const tMatriz & m);
void imprimir(const tVector & v);
#endif /* MATRIZ_H_ */