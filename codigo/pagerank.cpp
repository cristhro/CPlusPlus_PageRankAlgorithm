#include "pagerank.h"
#include "checkML.h"

double getPageRank(tListaPageRank &pr, string s) {
	bool enc = false;
	int i = 0;

	while (i < pr.tam && !enc)
	{
		if (pr.lista[i].fichero == s) {
			enc = true;
		}
		else {
			i++;
		}
	}
	return pr.lista[i].rank;
}
tListaPageRank getListaPageRankBusqueda(tListaPageRank &pr, tListaCadenas &l) {
	tListaPageRank listaPR;
	tPageRank  tmp;
	int pos;

	listaPR.tam = l.tam;

	for (int i = 0; i < l.tam; i++)
	{
		// Guardamos el fichero y su page rank en la estructura
		listaPR.lista[i].fichero = l.lista[i];
		listaPR.lista[i].rank = getPageRank(pr, l.lista[i]);

		// Lo ordenamos
		pos = i;
		while ((pos > 0)
			&& (listaPR.lista[pos - 1].rank < listaPR.lista[pos].rank))
		{
			tmp = listaPR.lista[pos];
			listaPR.lista[pos] = listaPR.lista[pos - 1];
			listaPR.lista[pos - 1] = tmp;
			pos--;
		}

	}

	return listaPR;
}
void mostrarListaPageRank(tListaPageRank &pr) {
	for (int i = 0; i < pr.tam; i++)
	{
		cout << "Encontrada en " << '"' << pr.lista[i].fichero << '"' << " (relevancia ";
		cout << pr.lista[i].rank << ")" << endl;
	}
}
void normalizarListaPageRank(tListaPageRank &pr) {
	double suma = 0;
	for (int i = 0; i < pr.tam; i++)
	{
		suma += pr.lista[i].rank;
	}

	for (int i = 0; i < pr.tam; i++)
	{
		pr.lista[i].rank = pr.lista[i].rank / suma;
	}
}
void crearListaPageRank(tListaPageRank &pageRank, tListaCadenas &totales, tVector &X)
{
	pageRank.tam = totales.tam;
	for (int i = 0; i < pageRank.tam; i++)
	{
		pageRank.lista[i].fichero = totales.lista[i];
		pageRank.lista[i].rank = X.vector[i];
	}
}
