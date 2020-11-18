#include "lista.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  string linea;
  int pos, longitud;
  while (!cin.eof()) {
	  getline(cin, linea);
	  stringstream slinea(linea);
	  int valor;
	  Lista<int> lista;
	  while (slinea >> valor) {
		  lista.pon_final(valor);
	  }
	  cin >> pos >> longitud;
	  lista.invertir(pos, longitud);
	  lista.imprime();
	  cout << endl;
  }
}
