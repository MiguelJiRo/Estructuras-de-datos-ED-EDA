 
#include "hotelcli.h"

/*METODOS CLIENTE*/
Cliente::Cliente(const string& DNI, const string& nombre, const int& telefono) {}

const string& Cliente::DNI() const {
	return _DNI;
}
const string& Cliente::nombre() const {
	return _nombre;
}
const int& Cliente::telefono() const {
	return _telefono;
}

bool Cliente::operator==(const Cliente &c2) {

	return this->nombre == c2.nombre;

}

/*METODOS AGENCIA*/

Agencia::Agencia() {}

/**
• aloja(c, h): modifica el estado de la agencia alojando a un cliente c en un
hotel h. Si c ya tenía antes otro alojamiento, éste queda cancelado. Si h no
estaba dado de alta en el sistema, se le dará de alta.
*/
void Agencia::aloja(const Cliente& c, const string& hotel) 
{
	// constante
	if (_dic_cliente_aloja.contiene(c)) {
		desaloja(c);
	}

	// inserto el nuevo
	_dic_cliente_aloja.inserta(c, hotel);
	// existe el hotel
	if (_dic_hotel_clientes.contiene(hotel)) {
		Diccionario<string, Diccionario<Cliente, int>>::Iterator it2 = _dic_hotel_clientes.busca(hotel);
		it2.valor().inserta(c, 1);
	}
	// no existe el hotel
	else {
		Diccionario<Cliente, int> nuevo_dic;
		nuevo_dic.inserta(c, 1);
		_dic_hotel_clientes.inserta(hotel, nuevo_dic);
	}	
}

/**
desaloja(c): modifica el estado de una agencia desalojando a un cliente c
del hotel que éste ocupase. Si c no tenía alojamiento, el estado de la
agencia no se altera.
*/
void Agencia::desaloja(Cliente c) 
{
	// constante
	if(_dic_cliente_aloja.contiene(c)) {
		// lo busco
		DiccionarioHash<Cliente, string>::Iterator it = _dic_cliente_aloja.busca(c);
		Diccionario<string, Diccionario<Cliente, int>>::Iterator it2 = _dic_hotel_clientes.busca(it.valor());
		// lo elimino
		_dic_cliente_aloja.borra(c);
		it2.valor().borra(c);
	}
}
/**
alojamiento(c): permite consultar el hotel donde se aloja un cliente c,
siempre que éste tuviera alojamiento. En caso de no tener alojamiento
produce un error.
*/
const string& Agencia::alojamiento(Cliente c) const {
	// constante
	if (!_dic_cliente_aloja.contiene(c)) {
		throw ENoHayMensaje();
	}
	DiccionarioHash<Cliente, string>::ConstIterator it = _dic_cliente_aloja.cbusca(c);
	return it.valor();
}
/**
listado_hoteles(): obtiene una lista ordenada de todos los hoteles que
están dados de alta en la agencia.
*/
Lista<string> Agencia::listado_hoteles() {
	// lineal
	Diccionario<string, Diccionario<Cliente, int>>::ConstIterator it = _dic_hotel_clientes.cbegin();
	Lista<string> lista_hoteles;
	while (it != _dic_hotel_clientes.cend()) {
		lista_hoteles.pon_final(it.clave());
		it.next();
	}
	return lista_hoteles;
}
 /**
 huespedes(h): permite obtener la lista ordenada de clientes que se alojan
 en el hotel h. Dicha lista será vacía si no hay clientes en el hotel.
 */
 Lista<string> Agencia::huespedes(string h) {
	 // lineal
	 Diccionario<string, Diccionario<Cliente, int>>::ConstIterator it = _dic_hotel_clientes.cbusca(h);
	 Diccionario<Cliente, int>::ConstIterator it2 = it.valor().cbegin();
	 Lista<string> lista_huespedes;
	 while (it2 != it.valor().cend()) {
		 lista_huespedes.pon_final(it2.clave().nombre());
		 it2.next();
	 }
	 return lista_huespedes;
 }

 int main() {
	 Agencia agencia = Agencia();
	Cliente cPepe=  Cliente("a12", "pepe", 1222);
	Cliente cAna= Cliente("a789", "ana", 5675);
	Cliente cJuan=  Cliente("x456", "juan", 4567);
	 agencia.aloja(cPepe, "Asa");
	 agencia.aloja(cAna, "Melia");
	 agencia.aloja(cJuan, "Melia");
	 agencia.desaloja(cJuan);
	 agencia.alojamiento(cAna);
	 agencia.listado_hoteles();
	 agencia.huespedes("Melia");
	 
 }
