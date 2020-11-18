#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "lista.h"
using namespace std;

// subprograma genérico para visualizar una lista por pantalla
template <class T>
void pinta(const Lista<T>& lista) {
	typename Lista<T>::ConstIterator it = lista.cbegin();
	while (it != lista.cend()) {
		cout << it.elem() << endl;
		it.next();
	}
}


/**
SUBPROGRAMA PARA CONSTRUIR UN ARBOL DE ENTEROS A PARTIR DE SU REPRESENTACIÓN EN UNA LÍNEA DEL ARCHIVO DE ENTRADA
Los árboles se representan de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con
	v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
	con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.

Ejemplos:
#  --> arbol vacío
[1] --> arbol hoja
([1]2[3])  --> arbol con raiz 2, hijo derecho 3 e hijo izdo 1
([1]2([3]4#)) --> arbol con raiz 2, hijo derecho (raíz = 4; sin hijo derecho; hijo izdo 3) e hijo izdo 1
*/
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

bool esHoja(const Arbin<int>& a) {
	return !a.esVacio() && (a.hijoDer().esVacio() && a.hijoIz().esVacio());
}

/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// Realizado en 4' 39'' 56'''
int numNodosSumativos_aux(const Arbin<int>& a, int &cuenta) {
	if (a.esVacio())
		return 0;
	if (esHoja(a)) {
		return a.raiz();
	}
	else {
		int izq = numNodosSumativos_aux(a.hijoIz(), cuenta);
		int der = numNodosSumativos_aux(a.hijoDer(), cuenta);

		if (izq + der == a.raiz()) {
			cuenta++;
		}

		return izq + der + a.raiz();
	}
}

unsigned int numNodosSumativos(const Arbin<int>& a) {
	int cuenta = 0;
	numNodosSumativos_aux(a, cuenta);
	return cuenta;
}

void prueba(Arbin<int> a) {

	cout << "------------------------" << endl;
	cout << a << "\n";	

	cout << "Numero nodos sumativos = " << numNodosSumativos(a) << "\n";

	cout << "------------------------" << endl;
}



int main() {
	Arbin<int> arbol;
	ifstream archivo;

	archivo.open("in.txt");
	while (archivo.peek() != EOF)  {
		Arbin<int> a = lee_arbol(archivo);
		prueba(a);
		string resto_linea;
		getline(archivo, resto_linea);
	}
	archivo.close();
	system("PAUSE");
	return 0;
}
