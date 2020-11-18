#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/** Indica aquí, razonadamente, la complejidad de numero_adivinos

*/

unsigned int numero_adivinos(const Arbin<int>& a) {
	// A IMPLEMENTAR

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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		cout << numero_adivinos(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
