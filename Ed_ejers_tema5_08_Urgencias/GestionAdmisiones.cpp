/**
  NOMBRE Y APELLIDOS:
  LABORATORIO:
  PUESTO:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "GestionAdmisiones.h"

/** 
Implementación de las operaciones de la clase Paciente 
*/

Paciente::Paciente(const string& nombre, unsigned int edad, const string& sintomas):
    _nombre(nombre), _sintomas(sintomas), _edad(edad) {}	

unsigned int Paciente::edad() const {
   return _edad;	
}
const string& Paciente::nombre() const {
   return _nombre;	
}
const string& Paciente::sintomas() const {
   return _sintomas;	
}

/**
Implementa aquí los métodos de las clases adicionales
*/

InfoPaciente::InfoPaciente(const Paciente& paciente, const Posicion &posicion) :
	_paciente(paciente), _posicion(posicion) {}

const Paciente& InfoPaciente::datos() const {
	return _paciente;
}

Posicion InfoPaciente::posicion() const {
	return _posicion;
}
/**
Debes completar la implementación de las operaciones de GestionAdmisiones,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
//crea() : Operación constructora que crea un sistema de gestión de
//admisiones vacío.
GestionAdmisiones::GestionAdmisiones() {
	// A IMPLEMENTAR
	// no hace falta
	//DiccionarioHash<CodigoPaciente, Paciente> _pacientes = DiccionarioHash<CodigoPaciente, Paciente>();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
//an_paciente(codigo, nombre, edad, sintomas) : añade al sistema un nuevo
//paciente con código de identificación codigo, con nombre nombre, con
//edad edad y con una descripción de síntomas sintomas.En caso de que el
//código esté duplicado, la operación señala un error “Paciente duplicado”.
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas) {
	// A IMPLEMENTAR
	if (_pacientes.contiene(codigo)) {
		throw EPacienteDuplicado();
	}
	_lista_espera.pon_ppio(codigo);
	_pacientes.inserta(codigo, InfoPaciente(Paciente(nombre,edad,sintomas), _lista_espera.begin()));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
//info_paciente(codigo, nombre, edad, sintomas) : nombre, edad y sintomas
//devuelven la información correspondiente al paciente con código codigo.
//En caso de que el código no exista, levanta un error “Paciente inexistente”.
void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const {
	// A IMPLEMENTAR	
	if (!_pacientes.contiene(codigo)) {
		throw EPacienteNoExiste();
	}
	/*nombre = _pacientes.valorPara(codigo).nombre();
	edad = _pacientes.valorPara(codigo).edad();
	sintomas = _pacientes.valorPara(codigo).sintomas();*/

	
	DiccionarioHash<CodigoPaciente, InfoPaciente>::ConstIterator it = _pacientes.cbusca(codigo);

	nombre = it.valor().datos().nombre();
	edad = it.valor().datos().edad();
	sintomas = it.valor().datos().sintomas();
	
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
//siguiente(codigo) : almacena en codigo el código del siguiente paciente a
//ser atendido.En caso de que no haya más pacientes, esta operación
//levanta un error “No hay pacientes”.
void GestionAdmisiones::siguiente(CodigoPaciente& codigo) const {
  // A IMPLEMENTAR
	if (_lista_espera.esVacia())
		throw ENoHayPacientes();

	codigo = _lista_espera.ultimo();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
//hay_pacientes() : devuelve true si hay más pacientes en espera, y false en
//otro caso.
bool GestionAdmisiones::hay_pacientes() const {  
  // A IMPLEMENTAR

	if (_lista_espera.esVacia()) {
		return false;
	}
	else {
		return true;
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
//elimina(codigo) : elimina del sistema todo el rastro del paciente con
//código codigo.Si no existe tal paciente, la operación no tiene efecto.
void GestionAdmisiones::elimina(CodigoPaciente codigo) {
	// A IMPLEMENTAR

	/*
	LINEAL 
	_pacientes.borra(codigo);

	Lista<CodigoPaciente>::Iterator it = _lista_espera.begin();

	while (it.elem() != codigo || it != _lista_espera.end())
		it.next();

	if (it.elem() == codigo)
		_lista_espera.eliminar(it);
	*/

	// CONSTANTE

	DiccionarioHash<CodigoPaciente, InfoPaciente>::ConstIterator it = _pacientes.cbusca(codigo);

	if (it != _pacientes.cend()) {
		_lista_espera.eliminar(it.valor().posicion());
		_pacientes.borra(codigo);
	}
}
   
