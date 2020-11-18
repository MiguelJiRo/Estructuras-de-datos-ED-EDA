/*
NOMBRE Y APELLIDOS:

*/



#include <iostream>
#include <string>
#include "Arbin.h"
using namespace std;



/* Puedes implementar aquí las funciones auxiliares que consideres
   oportuno */

/*
COMPLEJIDAD: Determina justificadamente la complejidad del procedimiento 

*/
/*
Ejemplo de entrada (árboles de ejemplo dados en el enunciado)
=============================================================
((#-9[100])5(#-4[3]))
(([5]-2[6])2(#-1[-1]))

Salida asociada
===============
4
NO_RENTABLE
*/
void mejor_renta_aux(Arbin<int> a, int& renta_maxima, bool &es_rentable, int acc) {
	if (!a.esVacio()) {
		if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) {
			if (renta_maxima < acc + a.raiz()) {
				renta_maxima = acc + a.raiz();
				es_rentable = true;
			}
		}
		if (acc + a.raiz() > 0) {
			mejor_renta_aux(a.hijoIz(), renta_maxima, es_rentable, acc + a.raiz());
			mejor_renta_aux(a.hijoDer(), renta_maxima, es_rentable, acc + a.raiz());
		}
	}
}

void mejor_renta(Arbin<int> a, bool& es_rentable, int& renta_maxima) {
	/* A IMPLEMENTAR */
	renta_maxima = 0;
	es_rentable = false;
	mejor_renta_aux(a, renta_maxima, es_rentable, 0);
}


Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
  		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

void muestra_solucion(bool rentable, int renta_max) {
  if (rentable) {
	 cout << renta_max << endl; 
  }	
  else {
	 cout << "NO_RENTABLE " << endl; 
  }
}

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		bool es_rentable;
		int renta_maxima;
		mejor_renta(a,es_rentable,renta_maxima);
		muestra_solucion(es_rentable,renta_maxima);
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}