#ifndef __CONSULTORIO_H
#define __CONSULTORIO_H
using namespace std;

#include <iostream>
#include <utility>
#include <string>
#include "Fecha.h"
#include "List.h"
#include "TreeMap.h"
#include "HashMap.h"

typedef string Medico;
typedef string Paciente;

class Consultorio{

private:
	typedef TreeMap<Fecha, Paciente> _dic_TablaCitas; // TreeMap para que respete el orden
	HashMap<Medico, _dic_TablaCitas> _dic_tablaMedicos; //esto es el consultorio

public:
	// constructores	
	Consultorio(){
		this->_dic_tablaMedicos = *new HashMap<Medico, _dic_TablaCitas>;
	}

	Consultorio(HashMap <Medico, _dic_TablaCitas> tablaMedicos){
		this->_dic_tablaMedicos = tablaMedicos;
	}

	class EMedicoNoExiste {};
	class EFechaOcupada {};
	class ENoHayPacientes {};

	// Métodos de la clase
	/*
	nuevoMedico(m): da de alta un nuevo medico en el consultorio. Si el medico ya estaba en el
	consultorio, este no se modifica.
	*/
	void nuevoMedico(Medico med){
		if (!_dic_tablaMedicos.contains(med)) {
			TreeMap<Fecha, Paciente> nueva_TablaCitas;
			_dic_tablaMedicos.insert(med, nueva_TablaCitas);
		}
	}
	/*
	pideConsulta(p,m,f): el paciente p pide consulta con el medico m para una fecha f. Si el medico
	no esta dado de alta se lanzara una excepcion con el mensaje Medico no existente. Si el medico
	ya tiene reservada esta fecha, se lanzara una excepcion con el mensaje Fecha ocupada. Un paciente
	puede tener varias citas con el mismo medico, siempre que sean en distinto momento.
	*/
	void pideConsulta(Paciente p, Medico m, Fecha f){
		if (!_dic_tablaMedicos.contains(m)) {
			throw EMedicoNoExiste();
		}
		HashMap<Medico, _dic_TablaCitas>::Iterator it = _dic_tablaMedicos.find(m);
		if (it.value().contains(f)) {
			throw EFechaOcupada();
		}
		it.value().insert(f, p);
	}

	/*
	siguientePaciente(m): consulta el paciente al que le toca el turno de ser atendido por el medico m.
	Suponemos que el siguiente paciente es el que tiene una fecha menor. Si el medico no esta dado
	de alta se lanzara una excepcion con el mensaje Medico no existente. Si el medico no tiene
	pacientes asignados se lanzara una excepcion con mensaje No hay pacientes.
	*/
	Paciente siguientePaciente(Medico m){
		if (!_dic_tablaMedicos.contains(m)) {
			throw EMedicoNoExiste();
		}
		HashMap<Medico, _dic_TablaCitas>::Iterator it = _dic_tablaMedicos.find(m);
		if (it.value().empty()) {
			throw ENoHayPacientes();
		}
		TreeMap<Fecha, Paciente>::Iterator it2 = it.value().begin();
		return it2.value();;
	}
	/*
	atiendeConsulta(m): elimina el siguiente paciente del medico m. Suponemos que el siguiente
	paciente es el que tiene una fecha menor. Si el medico no esta dado de alta se lanzara una excepcion
	con el mensaje Medico no existente. Si el medico no tiene pacientes asignados se lanzara una
	excepcion con mensaje No hay pacientes.
	*/
	void atiendeConsulta(Medico m){
		if (!_dic_tablaMedicos.contains(m)) {
			throw EMedicoNoExiste();
		}
		HashMap<Medico, _dic_TablaCitas>::Iterator it = _dic_tablaMedicos.find(m);
		if (it.value().empty()) {
			throw ENoHayPacientes();
		}
		TreeMap<Fecha, Paciente>::Iterator it2 = it.value().begin();
		it.value().erase(it2.key());
	}
	/*
	listaPacientes(m,d): devuelve la lista de pacientes del medico m que tienen cita el da d. Se
	supone que el da es un numero entero correcto. Si el medico no esta dado de alta se lanzara una
	excepcion con el mensaje Medico no existente. Si el medico no tiene pacientes ese da, la lista
	devuelta sera vaca.
	*/
	List<pair<Fecha,Paciente>> listaPacientes(Medico m, Fecha f){
		if (!_dic_tablaMedicos.contains(m)) {
			throw EMedicoNoExiste();
		}
		List<pair<Fecha, Paciente>> milista;
		HashMap<Medico, _dic_TablaCitas>::Iterator it = _dic_tablaMedicos.find(m);
		if (!it.value().empty()) {
			TreeMap<Fecha, Paciente>::Iterator it2 = it.value().begin();
			while (it2 != it.value().end()) {
				Fecha primero = it2.key();
				if (primero.getDia() == f.getDia())
				{
					Fecha nueva_fecha = it2.key();
					Paciente nuevo_paciente = it2.value();
					milista.push_back(make_pair(nueva_fecha, nuevo_paciente));
				}
				it2.next();
			}
		}
		return milista;
	}
};
#endif