#include "matriz.h"
#include "checkML.h"

tMatriz matrizConstante(double x, int n){
	tMatriz m;

	// Ponemos la dimension de la matriz
	m.dim = n;

	// Modificamos los valores de la matriz
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m.matriz[i][j] = x;
		}
	}
	return m;
}

double redondear_numero(double numero) {
	return double(int(numero*10000.0 + .5)) / 10000.0;
}

tVector operator*(const tMatriz & m, const tVector & v){
	/*
	 
	 i		( 1 2 )  [4]	= ( 1*4 + 2*2 )   ( 8  )
	i+1		( 2 3 )	 [2]	  ( 2*4 + 3*2 )	  ( 14 )
			j	j+1
					M							  V
		| (ij		i(j+1)	....	in  |		[ i ]		=	( M[i][j] * V[i]	+ M[i][j+1] *V[i+1] .... M[i][n] * V[n]) 
		| ((i+1)j	(i+1)(j+1)...(i+1)n	|		[i+1]		    ( M[i+1][j] * V[i]	+ M[i+1][j+1] *V[i+1] .... M[i][n] * V[n]) 
		| 	.							|		[ . ]			( .							 ) 
		| 	.							|		[ . ]			( .							 ) 
		| ((n)j	  (n)(j+1)   ...(n)n	|		[ . ]			( M[n][j] * V[i]	+ M[n][j+1] *V[i+1] .... M[n][n] * V[n]) 
	*/
	tVector r;
	r.tam = m.dim;

	for (int i = 0; i < m.dim; i++)
	{
		double sumaColumnas = 0;
		
		for (int j = 0; j < m.dim; j++)
		{
			sumaColumnas += m.matriz[i][j] * v.vector[j];
		}
		r.vector[i] = redondear_numero (sumaColumnas);
	}

	return r;
}

tMatriz operator*(double x, const tMatriz & m){
	tMatriz mr; // matriz resultado
	mr.dim = m.dim;
	for (int i = 0; i < m.dim; i++)
	{
		for (int j = 0; j < m.dim; j++)
		{
			mr.matriz[i][j] = m.matriz[i][j] * x;
		}
	}
	return mr;
}

tMatriz operator+(const tMatriz & m1, const tMatriz & m2){
	tMatriz mr; // matriz resultado
	mr.dim = m1.dim;

	for (int i = 0; i < m1.dim; i++)
	{
		for (int j = 0; j < m1.dim; j++)
		{
			mr.matriz[i][j] = m1.matriz[i][j] + m2.matriz[i][j];
		}
	}

	return mr;
}

tMatriz desdeEnlacesAMatriz(const tMatriz & L){
	/*
		M la matriz (1−c ) CN +cM' , donde CN es la matriz con todas las
		entradas iguales a 1N
		
	*/

	tMatriz M, M_1, M_2 ,Cn;	// matriz resultado
	tVector N, X;
	double c = 0.85;
	double resto_c = 1 - 0.85;

	M.dim = L.dim;
	Cn.dim = L.dim;
	N.tam = L.dim;
	X.tam = L.dim;

	// Inicializamos el vector
	for (size_t i = 0; i < MAX_VECTOR	; i++)
	{
		N.vector[i] = 0;
		X.vector[i] = redondear_numero(double(double(1)/double(L.dim)));
	}

	// Creamos el Vector N con el numero de enlaces que tiene cada pagina
	for (int j = 0; j < L.dim; j++)
	{
		double numEnl = 0;
		for (int i = 0; i < L.dim; i++)
		{
			numEnl += L.matriz[i][j];
		}
		N.vector[j] = numEnl;
	}
	cout << "Vector X" << endl;
	imprimir(X);

	// Creamos la matriz Cn
	for (int j = 0; j < Cn.dim; j++){
		for (int i = 0; i < Cn.dim; i++){
			
			if (N.vector[j] == 0) {
					Cn.matriz[i][j] = redondear_numero(double(double(1) / double(N.tam)));
			}
			else {
				Cn.matriz[i][j] = redondear_numero (1 / N.vector[j]);
			}
			
		}
	}
	// Matriz Cn
	cout << "Matriz Cn" << endl;
	imprimir(Cn);

	// Multiplicamos  (1-c)*Cn
	cout << "Matriz (1-c)*Cn" << endl;
	M_1 = resto_c * Cn;
	imprimir(M_1);

	// Multiplicamos c Por la Matriz L (M prima en el enunciado)
	M_2 = c*L;
	cout << "Multiplicacion de la matriz c*L" << endl;
	imprimir(M_2);
	
	// Creamos la suma de las dos partes de la ecuacion para hayar la matriz M
	//cout << "Matriz M" << endl;
	M = M_1 + M_2;

	return M;
}

tMatriz desdeEnlacesAMatrizSimple(const tMatriz & L) {
	tMatriz M;
	tVector N;

	N.tam = L.dim;
	M.dim = L.dim;

	// Inicializamos el vector
	inicializar(N, 0);

	// Creamos el Vector N con el numero de enlaces que tiene cada pagina
	for (int j = 0; j < L.dim; j++)
	{
		double numEnl = 0;
		for (int i = 0; i < L.dim; i++)
		{
			numEnl += L.matriz[i][j];
		}
		N.vector[j] = numEnl;
	}
	// Creamos la matriz M simple
	for (int j = 0; j < L.dim; j++) {
		for (int i = 0; i < L.dim; i++) {

			if (N.vector[j] == 0) {
				M.matriz[i][j] = redondear_numero(double(double(1) / double(N.tam)));
			}
			else {
				if (L.matriz[i][j] == 0) {
					M.matriz[i][j] = 0;
				}
				else {
					double num = 1 / N.vector[j];
					M.matriz[i][j] = redondear_numero(num);
				}

			}

		}
	}
	return M;
}

tVector normaliza( tVector const & v)
{
	tVector vr;
	vr.tam = v.tam;

	// Obtenemos la suma total de los elementos
	double suma = 0;
	for (int i = 0; i < vr.tam; i++)
	{
		suma = suma + v.vector[i];
	}

	for (int i = 0; i < vr.tam; i++)
	{
		vr.vector[i] = v.vector[i] / suma;
	}
	
	return vr;
}

tVector vectorPropio(const tMatriz & M)
{
	tVector X;

	// Inicializamos todos los elementos de X con (1 / numero total de enlaces)
	X.tam = M.dim;
	inicializar(X, redondear_numero(double(double(1) / double(M.dim))));

	// Calculamos el page Rank
	while (X != M*X) {

		X = M*X;
	}
	
	return X;
}

void inicializar(tVector & v, double a) {
	for (int i = 0; i < v.tam; i++)
	{
		v.vector[i] = a;
	}
}

bool  operator!= (const tVector & v1, const tVector & v2){
	int cont = 0;
	bool ok = false;
	int i = 0;

	while (i < v1.tam && !ok){
		
		if (v1.vector[i] != v2.vector[i]){
			ok = true;
		}
		else{
			i++;
		}
	}

	return ok;
}

void imprimir(const tMatriz & m){
	for (int i = 0; i < m.dim; i++)
	{
		for (int j = 0; j < m.dim; j++)
		{
			cout << " " <<  m.matriz[i][j] ;
		}
		cout << endl;
	}
}

void imprimir(const tVector & v){
	for (int i = 0; i < v.tam; i++)
	{
		cout << " " << v.vector[i] << endl;
	}
	cout << endl;
}
