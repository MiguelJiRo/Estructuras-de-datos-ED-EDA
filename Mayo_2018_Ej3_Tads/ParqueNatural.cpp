#include "ParqueNatural.h"
#include "lista.h"

/*
  COMPLEJIDAD

*/
ParqueNatural::ParqueNatural() {
	/* A IMPLEMENTAR */
}

/*
  COMPLEJIDAD	CONSTANTE

*/
/*
an_ecosistema(ecosistema): Añade un nuevo ecosistema con identicador ecosistema
al parque. Si el ecosistema ya existe, levanta una excepción EEcosistemaDuplicado.
*/
void ParqueNatural::an_ecosistema(const string& ecosistema) {
	/* A IMPLEMENTAR */
	if (_dic_eco_especie.contiene(ecosistema))
		throw EEcosistemaDuplicado();

	Diccionario<string, int> nuevo_ecosistema;
	_dic_eco_especie.inserta(ecosistema, nuevo_ecosistema);
}

/*
  COMPLEJIDAD CONSTANTE

*/
/*
an_ejemplares(ecosistema,especie,n): Añade n ejemplares de la especie con identi-
cador especie al ecosistema con identicador ecosistema. Si ecosistema no existe,
levanta una excepción EEcosistemaNoExiste. Si la especie ya habita en el ecosistema se
incrementará su número de ejemplares en n; si la especie no habita en el ecosistema, se
registrará en el ecosistema esa nueva especie con ese número de ejemplares.
*/
void ParqueNatural::an_ejemplares(const string& ecosistema, const string& especie, int n) {
	/* A IMPLEMENTAR */
	if (!_dic_eco_especie.contiene(ecosistema))
		throw EEcosistemaNoExiste();

	Diccionario<string, Diccionario<string, int>>::Iterator it = _dic_eco_especie.busca(ecosistema);

	if (it.valor().contiene(especie)) {
		Diccionario<string, int>::Iterator it2 = it.valor().busca(especie);
		int valor_antiguo = it2.valor();
		valor_antiguo += n;
		it.valor().inserta(especie, valor_antiguo);		
	}
	else {
		it.valor().inserta(especie, n);
		Diccionario<string, Lista<string>>::Iterator it3 = _dic_eco_lista_especie.busca(ecosistema);
		Lista<string> animales;
		if (_dic_eco_lista_especie.contiene(ecosistema)) {
			animales = it3.valor();
		}		
		animales.pon_final(especie);
		_dic_eco_lista_especie.inserta(ecosistema, animales);
	}
	
	if (_dic_especie_cant.contiene(especie)) {
		Diccionario<string, int>::Iterator it4 = _dic_especie_cant.busca(especie);
		int valor_antiguo = it4.valor() + n;
		_dic_especie_cant.inserta(especie, valor_antiguo);
	}
	else {
		_dic_especie_cant.inserta(especie, n);
	}	
}

/*
  COMPLEJIDAD LINEAL

*/
/*
lista_especies_ecosistema(ecosistema,n)->lista: Devuelve una lista con los identi-
cadores de las n últimas nuevas especies añadidas al ecosistema de identicador ecosistema,
ordenadas por orden inverso de inserción (es decir, primero la última nueva añadida, segundo
la penúltima nueva añadida, y así sucesivamente). Si ecosistema no existe, levanta
una excepción EEcosistemaNoExiste.
*/
Lista<string> ParqueNatural::lista_especies_ecosistema(const string& ecosistema, int n) const {
	/* A IMPLEMENTAR */
	if (!_dic_eco_especie.contiene(ecosistema))
		throw EEcosistemaNoExiste();

	Lista<string> milista;
	Diccionario<string, Lista<string>>::ConstIterator it = _dic_eco_lista_especie.cbusca(ecosistema);
	Lista<string> miecosistema = it.valor();
	int i = 1;
	Lista<string>::ConstIterator it2 = miecosistema.cbegin();

	while (it2 != miecosistema .cend()) {
		if (i >= miecosistema.longitud() - n + 1) {
			milista.pon_ppio(it2.elem());
		}		
		it2.next();
		++i;
	}

	return milista;
}

/*
  COMPLEJIDAD CONSTANTE

*/
/*
numero_ejemplares_en_ecosistema(ecosistema,especie)->numero: Devuelve la cantidad
de ejemplares de la especie especie que habitan el ecosistema ecosistema. Si
ecosistema no existe, levanta una excepción EEcosistemaNoExiste. Si la especie no habita
en el ecosistema, la operación devolverá 0 ejemplares.
*/
int ParqueNatural::numero_ejemplares_en_ecosistema(const string& ecosistema, const string& especie) const {
	/* A IMPLEMENTAR */
	if (!_dic_eco_especie.contiene(ecosistema))
		throw EEcosistemaNoExiste();

	Diccionario<string, Diccionario<string, int>>::ConstIterator it = _dic_eco_especie.cbusca(ecosistema);

	if (it.valor().contiene(especie)) {
		Diccionario<string, int>::ConstIterator it2 = it.valor().cbusca(especie);
		return it2.valor();
	}
	else
		return 0;
}

/*
  COMPLEJIDAD LINEAL

*/
/*
lista_especies_parque()->lista: Devuelve una lista de todas las especies del parque,
ordenada alfabéticamente.
*/
Lista<string> ParqueNatural::lista_especies_parque() const {
	/* A IMPLEMENTAR */
	Lista<string> milista;
	Diccionario<string, int>::ConstIterator it = _dic_especie_cant.cbegin();
	while (it != _dic_especie_cant.cend()) {
		milista.pon_final(it.clave());
		it.next();
	}
	return milista;
}

/*
  COMPLEJIDAD CONSTANTE

*/
/*
numero_ejemplares_en_parque(especie)->numero: Devuelve el número de ejemplares
que hay de la especie especie en el parque. Si la especie no habita en el parque, la
operación devolverá 0 ejemplares.
*/
int ParqueNatural::numero_ejemplares_en_parque(const string& especie) const {
	/* A IMPLEMENTAR */
	Diccionario<string, int>::ConstIterator it = _dic_especie_cant.cbusca(especie);

	if (_dic_especie_cant.contiene(especie)) {
		return it.valor();
	}
	else
		return 0;
}
