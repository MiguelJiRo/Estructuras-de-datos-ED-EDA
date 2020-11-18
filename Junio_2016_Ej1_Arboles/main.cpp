#include <iostream>
#include <string>
#include "Arbin.h"
using namespace std;



bool esHoja(Arbin<int> a) {
	return !a.esVacio() && a.hijoIz().esVacio() && a.hijoDer().esVacio();
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad del procedimiento
*/
/*
((([1]2#)3([4]5[6]))7((#8([9]10[11]))12[13]))
(((([0]0[0])0([0] - 1[0])) - 2#)0(([0]0[0])0[0]))

*/

// Resuelto en 5' 26'' 76'''
int num_navegables_aux(Arbin<int> a, int &cuenta) {
	if (a.esVacio()) {
		return 0;
	}
	if (esHoja(a)) {
		return 1;
	}
	else {
		int izq = num_navegables_aux(a.hijoIz(), cuenta);
		int der = num_navegables_aux(a.hijoDer(), cuenta);

		if (izq + der >= 3) {
			cuenta++;
		}

		if (izq + der + a.raiz() <= 0)
			return 0;
		else
			return izq + der + a.raiz();
	}
}

int num_navegables(Arbin<int> a) {
	int cuenta = 0;
	num_navegables_aux(a, cuenta);
	return cuenta;
}

///////////////////////////////////////////


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



/**
((([1]2#)3([4]5[6]))7((#8([9]10[11]))12[13]))
(((([0]0[0])0([0]-1[0]))-2#)0(([0]0[0])0[0]))
*/

/*
Salidas esperadas/correctas
1
5
*/


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		cout << num_navegables(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	system("PAUSE");
	return 0;
}