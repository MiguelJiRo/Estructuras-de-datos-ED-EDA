#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

#include "List.h"
#include "ciudades.h"
#include <io.h>
#include <fcntl.h>

// FUNCIONA

void mostrarLista(List<Id> l){

	List<Id>::Iterator it = l.begin();
	
	if (it != l.end()){
		cout << "    " << it.elem() << endl;
		it.next();
	}
	while (it != l.end()){
		cout << "    " << it.elem() << endl;	
		it.next();
	}
	
}

bool resuelve() {

	int numCasos;
	cin >> numCasos;
	if (!cin) return false;

	string inst;
	Presupuesto pres;
	ciudadMatic ciu;
	Id id;
	Nombre nom;
	int cos, imp, cal;

	for (int i = 0; i < numCasos; ++i) {
		try {
			cin >> inst;
			if(inst == "crea"){
				cin >> pres;
				ciu.crea(pres);
				cout << " ***Ciudad creada con un presupuesto de " << pres << "euros\n" << "\n";
			}
			else if (inst == "nuevoTipo") {
				cin >> id >> cos >> imp >> cal;
				ciu.nuevoTipo(id, cos, imp, cal);
				cout << " ***Insertado el tipo " << id << endl << "\n";
			}
			else if (inst == "insertaEdificio") {
				cin >> id >> nom;		
				ciu.insertaEdificio(nom, id);
				cout << " ***El edificio con id " << id << " ha sido insertado con nombre " << nom << endl << "\n";
			}
			else if (inst == "finTurno") {			
				int total = ciu.finTurno();
				cout << " Se devuelve un total de " << total << endl << "\n";
			}
			else if (inst == "reparaEdificio") {
				cin >>nom;
				ciu.reparaEdificio(nom);
				cout << "El edificio " << nom << " ha sido reparado.\n" << "\n";
			}
			else if (inst == "listaEdificios"){
				cin >> id;
				List<Id> lista = ciu.listaEdificios(id);
				cout << " Edificios con el id " << id << endl << "\n";
				mostrarLista(lista);
				cout << "---\n";
			}
		}
		catch (ExcepcionTAD e) { cout << e.msg() << '\n' << "---\n" << "\n"; }

	}
	cout << "------\n";


	return true;
}

int main() {
	while (resuelve()){}
	return 0;
}