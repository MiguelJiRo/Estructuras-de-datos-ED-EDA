/**
NOMBRE Y APELLIDOS:
LABORATORIO:
PUESTO:
USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "CarnetPorPuntos.h"


/**
Implementa aquí los métodos de las clases adicionales
*/

InfoConductor::InfoConductor(
	int puntos,
	Posicion posicion) :

	_puntos(puntos), 
	_posicion(posicion) {}
	
int InfoConductor::getpuntos() const{
	return _puntos;
}
Posicion InfoConductor::getposicion() const{
	return _posicion;
}
 
/**
Debes completar la implementación de las operaciones de CarnetPorPuntos,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
nuevo(dni): Añade un nuevo conductor identicado por su dni (un string), con 15
puntos. En caso de que el dni esté duplicado, la operación lanza un error Conductor
duplicado.
*/
void CarnetPorPuntos::nuevo(const string& dni) {
	  // A IMPLEMENTAR
	// constante
	if (_dic_dni_info.contiene(dni))
		throw EConductorDuplicado();

	_lista_conductores[15].pon_ppio(dni);
	_dic_dni_info.inserta(dni, InfoConductor(15, _lista_conductores[15].begin()));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
quitar(dni, puntos): Le resta puntos a un conductor tras una infracción. Si a un conductor
se le quitan más puntos de los que tiene, se quedará con 0 puntos. Si los puntos
resultantes de esta operación son los mismos que los que tiene el conductor actualmente,
entonces la operación debe ignorarse. En caso de que el conductor no exista, lanza un
error Conductor inexistente.
*/
void CarnetPorPuntos::quitar(const string& dni, unsigned int puntos) {
	  // A IMPLEMENTAR
	if (!_dic_dni_info.contiene(dni))
		throw EConductorNoExiste();

	if (puntos != 0) {
		DiccionarioHash<string, InfoConductor>::Iterator it = _dic_dni_info.busca(dni);
		int nuevos_puntos = it.valor().getpuntos() - puntos;
		if (nuevos_puntos <= 0) {
			nuevos_puntos = 0;
		}
		_lista_conductores[it.valor().getpuntos()].eliminar(it.valor().getposicion());
		_lista_conductores[nuevos_puntos].pon_ppio(dni);
		_dic_dni_info.inserta(dni, InfoConductor(nuevos_puntos, _lista_conductores[nuevos_puntos].begin()));
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
recuperar(dni, puntos): Le añade puntos a un conductor enmendado. Si debido a una
recuperación un conductor supera los 15 puntos, se quedará con 15 puntos. Si los puntos
resultantes de esta operación son los mismos que los que tiene el conductor actualmente,
entonces la operación debe ignorarse. En caso de que el conductor no exista, lanza un
error Conductor inexistente.
*/
void CarnetPorPuntos::recuperar(const string& dni, unsigned int puntos) {
	  // A IMPLEMENTAR
	if (!_dic_dni_info.contiene(dni))
		throw EConductorNoExiste();
	if (puntos != 0) {
		DiccionarioHash<string, InfoConductor>::Iterator it = _dic_dni_info.busca(dni);
		int nuevos_puntos = it.valor().getpuntos() + puntos;
		if (nuevos_puntos >= 15) {
			nuevos_puntos = 15;
		}
		_lista_conductores[it.valor().getpuntos()].eliminar(it.valor().getposicion());
		_lista_conductores[nuevos_puntos].pon_ppio(dni);
		_dic_dni_info.inserta(dni, InfoConductor(nuevos_puntos, _lista_conductores[nuevos_puntos].begin()));
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
consultar(dni): Devuelve los puntos actuales de un conductor. En caso de que el conductor
no exista, lanza un error Conductor inexistente.
*/
unsigned int CarnetPorPuntos::consultar(const string& dni) const {
	  // A IMPLEMENTAR
	if (!_dic_dni_info.contiene(dni))
		throw EConductorNoExiste();
	DiccionarioHash<string, InfoConductor>::ConstIterator it = _dic_dni_info.cbusca(dni);
	return it.valor().getpuntos();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
cuantos_con_puntos(puntos): Devuelve cuántos conductores tienen un determinado nú-
mero de puntos. En caso de que el número de puntos no esté entre 0 y 15 lanza un error
Puntos no válidos.
*/
unsigned int CarnetPorPuntos::cuantos_con_puntos(unsigned int puntos) const {
	  // A IMPLEMENTAR
	if (puntos < 0 || puntos > 15)
		throw EPuntosNoValidos();
	return _lista_conductores[puntos].longitud();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
lista_por_puntos(puntos): Produce una lista con los DNI de los conductores que poseen
un número determinado de puntos. La lista estará ordenada por el momento en el que el
conductor pasó a tener esos puntos, primero el que menos tiempo lleva con esos puntos. En
caso de que el número de puntos no esté entre 0 y 15 lanza un error Puntos no válidos.
*/
const Lista<string>& CarnetPorPuntos::lista_por_puntos(unsigned int puntos) const {
	  // A IMPLEMENTAR
	if (puntos < 0 || puntos > 15)
		throw EPuntosNoValidos();
	return _lista_conductores[puntos];
}

