#ifndef ___PANTANO_H
#define ___PANTANO_H

// clase con la información relativa a un pantano: capacidad máxima y volumen embalsado

class Pantano {
public:
	Pantano(float cmax = 0, float vol = 0) : _cmax(cmax), _vol(vol) {}
	float cmax() const; 
	float vol() const; 
	void pon_vol(float vol); 
private:
	float _cmax; // Capacidad máxima
	float _vol;  // Volumen embalsado
};

#endif // !___PANTANO_H


