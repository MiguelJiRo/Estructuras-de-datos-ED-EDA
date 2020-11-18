#ifndef __FECHA_H
#define __FECHA_H
using namespace std;

#include <iostream>


class Fecha{
private:
	int f_dia;
	int f_hora;
	int f_minuto;

public:
	//Constructores

	Fecha(){}

	Fecha(int dia, int hora, int minuto){
		f_dia = dia;
		f_hora = hora;
		f_minuto = minuto;
	}

	int getDia(){ return f_dia; }
	int getHora(){ return f_hora; }
	int getMinuto(){ return f_minuto; }

	bool operator==(Fecha fecha) const {
		return (this->f_dia == fecha.getDia() && this->f_hora == fecha.getHora() && this->f_minuto == fecha.getMinuto());
	}

	bool operator!=(Fecha fecha)const {
		return (this->f_dia != fecha.getDia()) || (this->f_hora != fecha.getHora()) || (this->f_minuto != fecha.getMinuto());
	}

	bool operator>(Fecha fecha) const {
		bool mayor = false;

		if (this->f_dia > fecha.getDia())
			mayor = true;
		else if (this->f_dia == fecha.getDia() && this->f_hora > fecha.getHora())
			mayor = true;
		else if (this->f_dia == fecha.getDia() && this->f_hora == fecha.getHora() && this->f_minuto > fecha.getMinuto())
			mayor = true;

		return mayor;
	}

	bool operator <(Fecha fecha) const{
		bool menor = false;

		if (this->f_dia < fecha.getDia())
			menor = true;
		else if (this->f_dia == fecha.getDia() && this->f_hora < fecha.getHora())
			menor = true;
		else if (this->f_dia == fecha.getDia() && this->f_hora == fecha.getHora() && this->f_minuto < fecha.getMinuto())
			menor = true;

		return menor;
	
	}
};


#endif