#ifndef __VENTAS_H
#define __VENTAS_H

#include "DiccionarioHash.h"
#include "diccionario.h"
#include "lista.h"
#include <string>

using namespace std;

typedef string tCliente;
typedef string tProducto;

/* Excepción levantada por 'an_oferta' 
   cuando dicha operación no puede aplicarse */ 
class EErrorAltaProducto {};

/* Excepción levantada por 'venta' 
   cuando dicha operación no puede aplicarse */ 
class EErrorVenta {};

/* Excepción levantada por 'primero_en_espera' 
   cuando dicha operación no puede aplicarse */ 
class EErrorAccesoListaEspera {};

/* Excepción levantada por 'pon_en_espera',
   'cancela_espera' y 'num_en_espera' cuando
   no existe el producto al que se refieren   */ 
class EProductoNoExiste {};

/* Clase para representar los resultados
   de la operación 'lista_ventas' */
class Venta {
	public:
	   string _producto;
	   int _unidades_vendidas;
	   Venta(string producto, int unidades_vendidas) {
		   _producto = producto;
		   _unidades_vendidas = unidades_vendidas;
	   }	
};

// ###################################
// PARTE NUEVA
// ###################################

typedef Lista<tCliente>::Iterator Posicion;

// ###################################

class SistemaVentas {
	public:
	   SistemaVentas();
	   void an_oferta(const tProducto& producto, unsigned int num_unidades);
	   void pon_en_espera(const tCliente& cliente, const tProducto& producto);
	   void cancela_espera(const tCliente& cliente, const tProducto& producto);
	   unsigned int num_en_espera(const tProducto& producto) const;
	   void venta(const tProducto& producto, unsigned int num_unidades);
	   const string primero_en_espera(const tProducto& producto) const;
	   Lista<Venta> lista_ventas() const;
     private:	   
	
	// ###################################

	/* INCLUYE AQUI LAS DEFINICIONES RELATIVAS A LA REPRESENTACION */
	// Diccionario con producto y lista de espera de los clientes
	DiccionarioHash<tProducto, Lista<tCliente>> _dic_prod_cliente;
	// Diccionario cliente y unidades que quiere
	DiccionarioHash<string, Posicion> _dic_cliente_it;
	// Diccionario producto y unidades disponibles
	DiccionarioHash<tProducto, int> _dic_prod_unidades;	
	// Diccionario producto y unidades vendidas
	Diccionario<tProducto, int> _dic_prod_vendidas;
	// ###################################
	   
};

#endif