/*
NOMBRE Y APELLIDOS:
*/

#include <iostream>
#include <string>
#include "Arbin.h"
#include "lista.h"
using namespace std;



bool esHoja(Arbin<int> a) {
	return !a.esVacio() && a.hijoIz().esVacio() && a.hijoDer().esVacio();
}

/* Puedes implementar aquí las funciones auxiliares que consideres
   oportuno */


/*
COMPLEJIDAD: Determina justificadamente la complejidad del procedimiento
*/
bool coinciden(Arbin<int> &a, Lista<int> &list) {
	
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



/**
((([1]2#)3([4]5[6]))7((#8([9]10[11]))12[13]))
(((([0]0[0])0([0]-1[0]))-2#)0(([0]0[0])0[0]))
*/


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		Lista<int> list;
		list.pon_final(7);
		list.pon_final(3);
		list.pon_final(2);
		list.pon_final(1);
		list.pon_final(5);
		list.pon_final(4);
		list.pon_final(6);
		list.pon_final(12);
		list.pon_final();
		list.pon_final(10);
		list.pon_final(9);
		list.pon_final(11);
		list.pon_final(13);
		cout << coinciden(a, list) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}