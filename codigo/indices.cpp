#include "indices.h"
#include "checkML.h"

bool ejecutarLeerFichero(const string& nombreArchivo, tIndicePalabras& tabla, tListaCadenas& visitado, tListaCadenas& noVisitado, tListaCadenas & totales, tMatriz & L, int &j)
{
	ifstream fichero_entrada;
	bool ok = false;
	fichero_entrada.open(nombreArchivo);

	if (!fichero_entrada.is_open())
	{
		cout << "ERROR: no se pudo abrir el fichero :" << nombreArchivo << endl;
	}
	else
	{
		ok = true;
		// Cargamos la lista desde el fichero inicial
		procesarFicheroEnTabla(fichero_entrada, tabla, nombreArchivo, visitado, noVisitado,totales, L, j);

		// Cerramos el fichero
		fichero_entrada.close();
	}
	return ok;
}

void procesarFicheroEnTabla(istream& fichero, tIndicePalabras& tabla, string nombreArchivo, tListaCadenas& visitado, tListaCadenas& noVisitado,  tListaCadenas & totales, tMatriz & L, int &j)
{
	char c;
	char menor = char(60);
	char mayor = char(62);

	string palabra = "";

	while (!fichero.eof())
	{
		// Obtenemos un caracter
		fichero.get(c);

		if (menor == c)
		{
			while (c != mayor)
			{
				// Insertamos al final de la palabra el caracter
				palabra.push_back(c);	//tolower(c)

				// Obtenemos el siguiente caracter
				fichero.get(c);
			}
			// Guardamos el mayor
			palabra.push_back(c);
		}
		// Si es un espacio o un signo de puntuacion
		else if (isspace(c) || ispunct(c) || fichero.eof())
		{
			// Si no esta vacia la palabra
			if (!palabra.empty())
			{
				// Si la palabra es un enlace (es decir un nombre de un fichero <ejemplo.txt>)
				if (esEnlace(palabra))
				{
					string enlace = getEnlace(palabra);
					int i = getPosicion(totales, enlace);

					// Si está en totales en la posición i 
					if (i != -1){
						// Entonces poner lij a 1.0
						L.matriz[i][j] = 1.0;
					}
					else{
						// Entoces añadimos el enlace en la lista noVisitado y en totales
						insertar(noVisitado, enlace);
						insertar(totales, enlace);
						
						// aumentarCapacidad el tamaño de L en 1
						L.dim++;
						
						//poner lt−1, j a 1.0 siendo t el nuevo tamaño
						L.matriz[L.dim - 1][j] = 1.0;
					}
				}
				else
				{
					// Entonces guardamos la palabra en la tabla
					insertar(tabla, palabra, nombreArchivo);
				}
				// Volvemos al estado inicial de la palabra
				palabra = "";
			}
		}
		else
		{
			// En caso de no ser espacio ni puntuacuion , añadimos el caracter al final de la palabra
			palabra.push_back(tolower(c));
		}
	}
}

bool isspace(char c)
{
	return (char(32) == c);
}

bool ispunct(char c)
{
	char comillaSimple = char(39);
	char saltoLinea = char(10);

	return ('.' == c || ',' == c || ':' == c || ';' == c || '?' == c || '!' == c || '-' == c || '_' == c ||
		'(' == c || ')' == c || comillaSimple == c || '"' == c || '{' == c || '}' == c || '[' == c || ']' == c || saltoLinea == c || '@' == c);
}

bool crearTabla(tIndicePalabras & tabla, tListaCadenas & totales, const string &archivoInicial, tMatriz & L)
{
	
	bool ok = false;
	// Primero reservamos la memoria inicial
	tListaCadenas visitados, noVisitados;

	// 1. Inicializar visitados y no - visitados a listas vacías y totales a listas vacías
	//     , totales será siempre la unión de visitados y no-visitados.
	inicializarListaCadena(visitados);
	inicializarListaCadena(noVisitados);

	// 2. Meter el archivo inicial en no visitados y en totales e iniciar la matriz L a tamaño 1 con un cero
	insertar(noVisitados, archivoInicial);
	insertar(totales, archivoInicial);
	L.dim = 1;

	// 3 Mientras haya algún archivo en no-visitados
	while (!estaVacia(noVisitados))
	{
		// 3.a Entoncess sacamos un enlace (nombre de archivo) de noVisitados ,guardar su posición j en totales.
		int posOcupada = getPosicionOcupada(noVisitados);
		string nombreArchivo = getCadena(noVisitados, posOcupada);
		eliminar(noVisitados, posOcupada);
		insertar(totales, nombreArchivo);

		int j = getPosicion(totales, nombreArchivo);

		// 3.b. Comprobamos si ese enlace ( archivo ) ha sido visitado
		bool visitado = buscar(visitados, nombreArchivo);
		
		// Si no ha sido visitado
		if (!visitado)
		{
			// Entoces Leemos el contenido del fichero y metemos sus datos en la tabla, en caso de existir un enlace lo metemos en noVisitados
			ok = ejecutarLeerFichero(nombreArchivo, tabla, visitados, noVisitados, totales, L, j);
			
			// Lo metemos en visitados
			insertar(visitados, nombreArchivo);
		}
	}

	// Liberamos visitados y no visitados
	liberar(visitados);
	liberar(noVisitados);

	return ok;
}

bool esEnlace(string s)
{
	bool ok = false;

	if (s.size() > 1)
	{
		if (s.at(0) == '<' && s.at(s.size() - 1) == '>')
		{
			ok = true;
		}
	}
	return ok;
}

string getEnlace(string s)
{
	return s.substr(1, s.size() - 2);
}
