#include <iostream>
#include "ConfederacionHidrografica.h"
#include <string>
#include "Pantano.h"
#include "Rio.h"

using namespace std;

int menu() {
	int op;
	cout << "0: Salir." << endl;
	cout << "1: Crear rio." << endl;
	cout << "2: Crear pantano." << endl;
	cout << "3: Embalsar en pantano." << endl;
	cout << "4: Embalsado en pantano." << endl;
	cout << "5: Embalsado en rio." << endl;
	cout << "6: Transvasar." << endl;
	cout << "7: Mostrar conferencia hidrografica." << endl << endl;
	cout << "Introduzca una opcion: ";
	cin >> op;
	cout << endl;
	return op;
}

void creaRio(ConfederacionHidrografica& conferencia) {
	string nombreRio;
	cout << "Introduce el nombre del rio: ";
	cin >> nombreRio;
	conferencia.insertar_rio(nombreRio);
}

void crearPantano(ConfederacionHidrografica& conferencia) {
	string nombreRio, nombrePantano;
	float cmax, vol;
	cout << "Introduce el nombre del rio: ";
	cin >> nombreRio;
	cout << "Introduce el nombre del pantano: ";
	cin >> nombrePantano;
	cout << "Introduce la capacidad maxima del pantano: ";
	cin >> cmax;
	cout << "Introduce el volumen actual del pantano: ";
	cin >> vol;
	conferencia.insertar_pantano(nombreRio, nombrePantano, cmax, vol);
}

void embalsarPantano(ConfederacionHidrografica& conferencia) {
	string nombreRio, nombrePantano;
	float vol;
	cout << "Introduce el nombre del rio: ";
	cin >> nombreRio;
	cout << "Introduce el nombre del pantano: ";
	cin >> nombrePantano;
	cout << "Introduce el volumen a embalsar en el pantano: ";
	cin >> vol;
	conferencia.embalsar(nombreRio, nombrePantano, vol);
}

void embalsadoEnPantano(ConfederacionHidrografica& conferencia) {
	string nombreRio, nombrePantano;
	cout << "Introduce el nombre del rio: ";
	cin >> nombreRio;
	cout << "Introduce el nombre del pantano: ";
	cin >> nombrePantano;
	cout << "En el pantano hay: " << conferencia.embalsado_pantano(nombreRio, nombrePantano) << endl;
}

void embalsadoEnRio(ConfederacionHidrografica& conferencia) {
	string nombreRio, nombrePantano;
	cout << "Introduce el nombre del rio: ";
	cin >> nombreRio;
	cout << "En el rio hay: " << conferencia.embalsado_cuenca(nombreRio) << endl;
}

void transvasar(ConfederacionHidrografica& conferencia) {
	string origen, destino, porigen, pdestino;
	float vol;
	cout << "Introduce el nombre del rio origen: ";
	cin >> origen;
	cout << "Introduce el nombre del pantano origen: ";
	cin >> porigen;
	cout << "Introduce el nombre del rio destino: ";
	cin >> destino;
	cout << "Introduce el nombre del pantano destino: ";
	cin >> pdestino;
	cout << "Introduce el volumen a transvasar: ";
	cin >> vol;
	conferencia.transvasar(origen, porigen, destino, pdestino, vol);
}

/*void mostrar(ConfederacionHidrografica& conferencia) {
	conferencia.mostrar();
}*/

int main() {
	ConfederacionHidrografica conferencia = ConfederacionHidrografica();
	int op = menu();
	while (op != 0) {
		switch (op) {
		case 1: creaRio(conferencia);
			break;
		case 2: crearPantano(conferencia);
			break;
		case 3: embalsarPantano(conferencia);
			break;
		case 4: embalsadoEnPantano(conferencia);
			break;
		case 5: embalsadoEnRio(conferencia);
			break;
		case 6: transvasar(conferencia);
			break;
		/*case 7: mostrar(conferencia);
			break;*/
		}
		cout << endl;
		op = menu();
	}
}