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
    _nombre(nombre),  _sintomas(sintomas), _edad(edad) {}	

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

InfoPaciente::InfoPaciente(
	Paciente paciente,
	Posicion posicion,
	int gravedad) :

	_paciente(paciente),
	_gravedad(gravedad),
	_posicion(posicion) {}

Paciente InfoPaciente::getpaciente() const {
	return _paciente;
}
int InfoPaciente::getgravedad() const {
	return _gravedad;
}
Posicion InfoPaciente::getposicion() const {
	return _posicion;
}


/**
Debes completar la implementación de las operaciones de GestionAdmisiones,
y justificar la complejidad de los mismos.
*/ 


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
GestionAdmisiones::GestionAdmisiones() {
	// A IMPLEMENTAR
	
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
an_paciente(codigo, nombre, edad, sintomas, gravedad): Añade al sistema
un nuevo paciente con código de identificación codigo, con nombre
nombre, con edad edad, con una descripción de síntomas sintomas, y con
código de gravedad gravedad. En caso de que el código esté duplicado, la
operación señala un error “Paciente duplicado”.
*/
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas, Gravedad gravedad) {
	// A IMPLEMENTAR
	if (_dic_codigo_paciente.contiene(codigo)) {
		throw EPacienteDuplicado();
	}
	// 0 grave // 1 normal // 2 leve
	Paciente mipaciente(nombre, edad, sintomas);
	int grav;
	if (gravedad == GRAVE)	grav = 0;
	else if (gravedad == NORMAL) grav = 1;
	else grav = 2;
	_lista_pacientes[grav].pon_ppio(codigo);
	_dic_codigo_paciente.inserta(codigo, InfoPaciente(mipaciente, _lista_pacientes[grav].begin(), grav));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
info_paciente(codigo, nombre, edad, sintomas): Almacena en nombre,
edad y síntomas la información correspondiente del paciente con código
codigo. En caso de que el código no exista, levanta un error “Paciente
inexistente”.
*/
void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const {
	// A IMPLEMENTAR
	if (!_dic_codigo_paciente.contiene(codigo))
		throw EPacienteNoExiste();

	DiccionarioHash<CodigoPaciente, InfoPaciente>::ConstIterator it = _dic_codigo_paciente.cbusca(codigo);
	nombre = it.valor().getpaciente().nombre();
	edad = it.valor().getpaciente().edad();
	sintomas = it.valor().getpaciente().sintomas();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
siguiente(codigo, gravedad): Almacena en codigo y gravedad,
respectivamente, el código y la gravedad del siguiente paciente a ser
atendido. Como se ha indicado antes, se atiende primero a los pacientes
graves, después a los de nivel de gravedad normal, y por último a los
leves. Dentro de cada nivel, los pacientes se atienden por orden de
llegada. En caso de que no haya más pacientes, esta operación levanta un
error “No hay pacientes”.
*/
void GestionAdmisiones::siguiente(CodigoPaciente& codigo, Gravedad& gravedad) const {
	// A IMPLEMENTAR
	if (!_lista_pacientes[0].esVacia()) {
		codigo = _lista_pacientes[0].ultimo();
		gravedad = GRAVE;
	}
	else if (!_lista_pacientes[1].esVacia()) {
		codigo = _lista_pacientes[1].ultimo();
		gravedad = NORMAL;
	}
	else if (!_lista_pacientes[2].esVacia()) {
		codigo = _lista_pacientes[2].ultimo();
		gravedad = LEVE;
	}
	else {
		throw ENoHayPacientes();
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
hay_pacientes(). Devuelve true si hay más pacientes en espera, y false en
otro caso.
*/
bool GestionAdmisiones::hay_pacientes() const {  
	// A IMPLEMENTAR
	if (!_lista_pacientes[0].esVacia() || !_lista_pacientes[1].esVacia() || !_lista_pacientes[2].esVacia()) {
		return true;
	}
	else {
		return false;
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
/*
elimina(codigo): Elimina del sistema todo el rastro del paciente con
código codigo. Si no existe tal paciente, la operación no tiene efecto.
*/
void GestionAdmisiones::elimina(CodigoPaciente codigo) {
	// A IMPLEMENTAR
	if (_dic_codigo_paciente.contiene(codigo)) {
		DiccionarioHash<CodigoPaciente, InfoPaciente>::Iterator it = _dic_codigo_paciente.busca(codigo);
		_lista_pacientes[it.valor().getgravedad()].eliminar(it.valor().getposicion());
	}
}
   
