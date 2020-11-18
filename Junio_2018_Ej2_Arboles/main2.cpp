
// NOMBRE Y APELLIDOS

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "bintree_eda.h"

/*
	RESUELTO EN  4' 40'' 42'''
*/
int diametro_aux(bintree<char> const& a, int &maximo) {
	if (a.empty()) {
		return 0;
	}
	else {
		int izq = diametro_aux(a.left(), maximo);
		int der = diametro_aux(a.right(), maximo);

		if (izq + der > maximo) {
			maximo = izq + der;
		}

		if (izq > der)
			return izq + 1;
		else
			return der + 1;
	}
}

// calcula el diámetro de un árbol binario
int diametro(bintree<char> const& arbol) {
	int maximo = 0;
	if (!arbol.empty()) {
		diametro_aux(arbol, maximo);
		maximo++;
	}
	return maximo;
}

// Análisis y justificación del coste: ...


void resuelve() {
   auto arbol = leerArbol('.');
   cout << diametro(arbol) << '\n';
}

int main() {
   // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   int numCasos;
   cin >> numCasos;
   
   for (int i = 0; i < numCasos; ++i) {
      resuelve();
   }

   // restablecimiento de cin
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("pause");
#endif

   return 0;
}
