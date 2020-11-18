
// NOMBRE Y APELLIDOS

#include <iostream>
#include <fstream>
using namespace std;

#include "queue_eda.h"  // con lista enlazada simple

class MezclarListas : public queue<int> {
public:
   void print(std::ostream& o = std::cout) const {
      if (!this->empty()) {// la lista no está vacía
         Nodo * aux = this->prim;
         o << aux->elem;
         aux = aux->sig;
         while (aux != nullptr) {
            o << ' ' << aux->elem;
            aux = aux->sig;
         }
      }
   }
   
   // introduce los elementos de other (una lista enlazada ordenada)
   // en la lista representada por this (también ordenada)
   void mezclar_ord(MezclarListas & other) {
	   int cont = this->size();
	   while (cont > 0) 
	   {
		   if (other.empty() || this->front() < other.front()) {
			   // lista this
			   int aux = this->front();
			   this->push(aux);
			   this->pop();
			   cont--;
		   }
		   else {
				// lista other
				this->push(other.front());
				other.pop();			   
		   } 
	   }

	   while (!other.empty()) {
		   this->push(other.front());
		   other.pop();
	   }
   }
   
};

inline std::ostream& operator<<(std::ostream & o, MezclarListas const& a) {
   a.print(o);
   return o;
}

MezclarListas leerLista() {
   MezclarListas lista;
   int n;
   std::cin >> n;
   while (n != 0) {
      lista.push(n);
      std::cin >> n;
   }
   return lista;
}

bool resuelveCaso() {
   auto lista1 = leerLista();
   auto lista2 = leerLista();
   lista1.mezclar_ord(lista2);   
   std::cout << lista1 << '\n';
   return true;
}

int main() {
   // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   int casos;
   cin >> casos;
   while (casos--) {
      resuelveCaso();
   }
   
   // restablecimiento de cin
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("pause");
#endif

}

