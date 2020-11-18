#include "Rio.h"

using namespace std;

Rio::Rio() {}

float Rio::embalsado_pantano(const string& pantano) const {
	return buscar_pantano(pantano).vol();  
}

float Rio::embalsado_total() const {
	// a implementar
}


const Pantano& Rio::buscar_pantano(const string& pantano) const {
	DiccionarioHash<string, Pantano>::ConstIterator ipantano = _pantanos.cbusca(pantano);
	DiccionarioHash<string, Pantano>::ConstIterator ifin = _pantanos.cend();
	if (ipantano == ifin) throw EPantanoNoExiste();
	return ipantano.valor();
}