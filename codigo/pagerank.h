#ifndef PAGERANK_H_
#define PAGERANK_H_

#include "listacadenas.h" // modulo listacadenas
#include "clavevalor.h"
#include "indices.h"
#include "matriz.h"
#include "main.h"

using namespace std;

typedef struct {
	double rank;
	string fichero;
}tPageRank;

const int MAX_LISTA = 500;
typedef tPageRank tListaRank[MAX_LISTA];

typedef struct {
	tListaRank lista;
	int tam;
}tListaPageRank;

void crearListaPageRank(tListaPageRank &pageRank, tListaCadenas &totales, tVector &X);;
double getPageRank(tListaPageRank &pr, string s);
tListaPageRank getListaPageRankBusqueda(tListaPageRank &pr, tListaCadenas &l);
void mostrarListaPageRank(tListaPageRank &pr);
void crearListaPageRank(tListaPageRank &pageRank, tListaCadenas &totales, tVector &X);
void normalizarListaPageRank(tListaPageRank &pageRank);

#endif /* PAGERANK_H_ */