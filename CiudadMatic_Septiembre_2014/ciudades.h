#ifndef CIUDADMATIC_H
#define CIUDADMATIC_H

#include <iostream>
#include "HashMap.h"
#include "TreeMap.h"
#include "List.h"

using namespace std;

typedef int Presupuesto;
typedef string Nombre;
typedef string Id;

class ciudadMatic {
private:
	
	typedef struct {
		Id id;
		int coste;
		int impuesto;
		int calidad;
	} InfoEdificio;
	
	// ESCRIBIR AQUI DICCIONARIOS O LISTAS
	HashMap<string, InfoEdificio> _dic_edificios_disponibles;
	TreeMap<string, InfoEdificio> _dic_edificios_ciudad;
	Presupuesto _presupuesto;

public:
	
	ciudadMatic(){}

	/*
	CiudadMatic : inicializa una nueva ciudad vacía, con el dinero que se pase como argumento
	disponible para ser gastado.
	*/
	void crea(Presupuesto pres){
		_presupuesto = pres;
		HashMap<string, InfoEdificio> nuevo_dic;
		TreeMap<string, InfoEdificio> nuevo_dic2;
		_dic_edificios_disponibles = nuevo_dic;
		_dic_edificios_ciudad = nuevo_dic2;
	}

	/*
	nuevoTipo: añade un nuevo tipo de edicio al sistema, con un identicador proporcionado
	por el usuario (por ejemplo, bar), un coste de construcción, una cantidad de impuestos
	generada por turno, y una calidad de base (máximo de turnos sin reparar). No devuelve
	nada.
	*/
	void nuevoTipo(string id, int cos, int imp, int cal){
		InfoEdificio nuevo_edificio;
		nuevo_edificio.id = id;
		nuevo_edificio.coste = cos;
		nuevo_edificio.impuesto = imp;
		nuevo_edificio.calidad = cal;
		_dic_edificios_disponibles.insert(id, nuevo_edificio);
	}

	/*
	insertaEdicio: dado el nombre de un edicio (por ejemplo, El Bar de Moe), y el identi
	cador de su tipo, y asumiendo que se disponga del dinero necesario para construirlo,
	añade el edicio a la ciudad y resta su coste de construcción del dinero disponible. No
	devuelve nada.
	*/
	void insertaEdificio(Nombre nom, Id id){
		if (_dic_edificios_disponibles.contains(id)) {
			HashMap<string, InfoEdificio>::Iterator it = _dic_edificios_disponibles.find(id);
			if (_presupuesto >= it.value().coste) {
				_presupuesto -= it.value().coste;
				_dic_edificios_ciudad.insert(nom, it.value());
			}
		}
	}

	/*
	reparaEdicio: repara el edicio cuyo identicador se pase como argumento a como recién
	construido, a un coste del 10% del coste de construcción (descartando los decimales),
	independientemente de lo estropeado que estuviese. No devuelve nada.
	*/
	void reparaEdificio(Nombre nom){
		if (_dic_edificios_ciudad.contains(nom)) {
			TreeMap<string, InfoEdificio>::Iterator it = _dic_edificios_ciudad.find(nom);
			it.value().coste += it.value().coste * 0.10;
		}
	}

	/*
	nTurno: todos los edicios construidos generan los impuestos que les corresponden por
	su tipo. Después, todos se estropean por un punto de calidad, y aquellos que lleguen a
	0 son derribados y eliminados de la ciudad. Devuelve el dinero total disponible para el
	nuevo turno (impuestos generados + dinero no gastado del turno anterior).
	*/
	int finTurno(){
		TreeMap<string, InfoEdificio>::Iterator it = _dic_edificios_ciudad.begin();
		int total = _presupuesto;
		while (it != _dic_edificios_ciudad.end()) {
			if (it.value().calidad > 1) {
				total += it.value().impuesto;
				it.value().calidad -= 1;
			}
			// calidad <= 1
			else {
				total += it.value().impuesto;
				_dic_edificios_ciudad.erase(it.key());
			}
			it.next();
		}
		return total;
	}
	/*
	listaEdicios : dado un identicador de tipo de edicio, devuelve una lista con los edicios
	de ese tipo que están actuamente construidos, por orden de antigüedad (primero el más
	viejo).
	*/
	List<Id> listaEdificios(Id id){
		// lineal
		TreeMap<string, InfoEdificio>::Iterator it = _dic_edificios_ciudad.begin();
		List<Id> milista;
		while (it != _dic_edificios_ciudad.end()) {
			if (it.value().id == id) {
				milista.push_front(it.value().id);
			}
			it.next();
		}
		return milista;
	}

};

#endif