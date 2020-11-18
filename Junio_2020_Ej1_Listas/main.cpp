//#define AUTO

#include <iostream>
#include <sstream>
#include "lista.h"

using namespace std;

typedef struct {
	string input;
	string output;
} tCaso;

const int NCASOS = 5;
tCaso casos[NCASOS] = {
		  { "5 1 2 0 3 4","1 0 2 3 4#4 3 2 0 1" },
		  { "7 1 2 0 3 0 5 6","1 0 2 3 0 5 6#6 5 0 3 2 0 1" },
		  { "3 5 0 6","0 5 6#6 5 0" },
		  { "3 0 5 6","0 5 6#6 5 0" },
		  { "3 5 6 0","5 0 6#6 0 5" }
};

bool ejecuta_caso(istream& cin, ostream& cout) {
	Lista<int> lista;
	int n;
	cin >> n;
	if (n < 0) {
		return false;
	}
	else {
		for (int i = 0; i < n; i++) {
			int elem;
			cin >> elem;
			lista.pon_final(elem);
		}
		lista.transponer();
		lista.imprime(cout);
		cout << "#";
		lista.imprime_invertida(cout);
		return true;
	}
}

void autocorreccion() {
	bool ok = true;
	for (int i = 0; i < NCASOS; i++) {
		stringstream in;
		stringstream out;
		in << casos[i].input;
		ejecuta_caso(in, out);
		if (out.str() != casos[i].output) {
			ok = false;
			cout << "ERROR" << endl;
			cout << "....ENTRADA:" << casos[i].input << endl;
			cout << "....SALIDA ESPERADA:" << casos[i].output << endl;
			cout << "....SALIDA OBTENIDA:" << out.str() << endl;
		}
	}
	if (ok) {
		cout << "Todos los casos de prueba se han superado correctamente." << endl;
	}
	else {
		cout << "Se han encontrado discrepancias con casos de prueba." << endl;
	}
}


int main() {
#ifndef AUTO
	while (ejecuta_caso(cin, cout)) {
		cout << endl;
	}
#endif
#ifdef AUTO
	autocorreccion();
	system("pause");
#endif
	return 0;
}