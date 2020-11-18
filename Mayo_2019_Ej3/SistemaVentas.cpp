/*

NOMBRE Y APELLIDOS:

*/

#include "SistemaVentas.h"
#include <string>

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
SistemaVentas::SistemaVentas() {
	/* A IMPLEMENTAR */
	
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 CONSTANTE
	 
	*/

//an_oferta(producto, num_unidades) : Crea una nueva oferta para el producto producto,
//con num_unidades unidades disponibles.Esta es una operación parcial : no debe existir ya
//un producto con el mismo nombre en el sistema, y, además, el número de unidades debe
//ser positivo.

void SistemaVentas::an_oferta(const tProducto& producto, unsigned int num_unidades) {
	/* A IMPLEMENTAR */
	if (_dic_prod_unidades.contiene(producto) || num_unidades <= 0) {
		throw EErrorAltaProducto();
	}
	else {
		_dic_prod_unidades.inserta(producto, num_unidades);
		Lista<tCliente> nueva_lista;
		_dic_prod_cliente.inserta(producto, nueva_lista);
	}	
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 CONSTANTE
	 
	*/

//pon_en_espera(cliente, producto) : Añade al cliente cliente a la lista de espera de
//la oferta para el producto producto.En caso de que el cliente ya esté esperando para
//comprar dicho producto, la operación no tendrá ningún efecto.Esta es una operación
//parcial : el producto al que se hace referencia debe estar ofertándose actualmente en el
//sistema.

void SistemaVentas::pon_en_espera(const tCliente& cliente, const tProducto& producto) {
	/* A IMPLEMENTAR */
	// ERROR EXTERNO

	// si está en la lista de espera no tendrá efecto
	// el producto debe de estar ofertandose
	string cliente_producto = cliente + producto;
	if (_dic_prod_unidades.contiene(producto) && !_dic_cliente_it.contiene(cliente_producto)) 
	{
		DiccionarioHash<tProducto, Lista<tCliente>>::Iterator it = _dic_prod_cliente.busca(producto);
		it.valor().pon_ppio(cliente);
		_dic_cliente_it.inserta(cliente_producto, it.valor().begin());
	}
}	
	
   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	  
	 CONSTANTE

	*/

//cancela_espera(cliente, producto) : Elimina al cliente cliente de la lista de espera
//correspondiente al producto en oferta producto.Si el cliente no está esperando en la
//lista de espera del producto, la operación no tendrá ningún efecto.Esta es una operación
//parcial : el producto debe estar ofertándose en el sistema.

void SistemaVentas::cancela_espera(const tCliente& cliente, const tProducto& producto) {
	/* A IMPLEMENTAR */
	// ERROR EXTERNO
	string cliente_producto = cliente + producto;
	if (_dic_cliente_it.contiene(cliente_producto) && _dic_prod_unidades.contiene(producto)) 
	{		
		DiccionarioHash<string, Posicion>::Iterator it = _dic_cliente_it.busca(cliente_producto);
		DiccionarioHash<tProducto, Lista<tCliente>>::Iterator it2 = _dic_prod_cliente.busca(producto);
		it2.valor().eliminar(it.valor());
		_dic_prod_cliente.inserta(producto, it2.valor());
		_dic_cliente_it.borra(cliente_producto);
	}
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 CONSTANTE
	 
	*/

//num_en_espera(producto)->num_clientes: Devuelve el número de clientes que están
//esperando para comprar el producto producto.Esta es una operación parcial : el producto
//debe estar ofertándose en el sistema.

unsigned int SistemaVentas::num_en_espera(const tProducto& producto) const {
	/* A IMPLEMENTAR */
	if (_dic_prod_unidades.contiene(producto)) 
	{
		DiccionarioHash<tProducto, Lista<tCliente>>::ConstIterator it = _dic_prod_cliente.cbusca(producto);
		return it.valor().longitud();
	}
	return 0;
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 CONSTANTE
	 
	*/

//venta(producto, num_unidades) : Registra una venta de num_unidades unidades del
//producto producto al primer cliente de la lista de espera.Dicho cliente se elimina de la
//lista de espera.En caso de que, tras dicha venta, no queden más unidades, la venta para
//el producto se cerrará, eliminado la oferta del sistema(y, por tanto, todos los clientes que
//están esperando se quedarán sin producto).Esta es una operación parcial : el producto
//debe estar ofertándose actualmente en el sistema, la lista de espera para dicho producto
//no debe estar vacía, y el número de unidades solicitado no debe sobrepasar el número de
//unidades disponibles.

void SistemaVentas::venta(const tProducto& producto, unsigned int num_entradas) {
	/* A IMPLEMENTAR */
	if (_dic_prod_unidades.contiene(producto) 
		&& !_dic_prod_cliente.busca(producto).valor().esVacia() 
		&& _dic_prod_unidades.busca(producto).valor() >= num_entradas) 
	{
		tCliente micliente = _dic_prod_cliente.busca(producto).valor().ultimo();
		string cliente_producto = micliente + producto;
		_dic_cliente_it.borra(cliente_producto);
		////////////////////////////////////////////////////////////////////
		if (_dic_prod_unidades.busca(producto).valor() == num_entradas) {
			_dic_prod_cliente.borra(producto);
			_dic_prod_unidades.borra(producto);
		}
		////////////////////////////////////////////////////////////////////
		else {
			// elimino el ultimo de la lista prod cliente
			_dic_prod_cliente.busca(producto).valor().quita_final();
			// actualizo unidades
			int unidades = _dic_prod_unidades.busca(producto).valor();
			unidades -= num_entradas;
			_dic_prod_unidades.inserta(producto, unidades);
		}
		////////////////////////////////////////////////////////////////////
		if (!_dic_prod_vendidas.contiene(producto)) {
			_dic_prod_vendidas.inserta(producto, num_entradas);
		}
		else {
			int total = _dic_prod_vendidas.busca(producto).valor();
			total += num_entradas;
			_dic_prod_vendidas.inserta(producto, total);
		}
	}
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 CONSTANTE
	 
	*/

//primero_en_espera(producto)->cliente: Devuelve el nombre del primer cliente que
//está esperando para comprar el producto producto.Esta es una operación parcial : el
//producto se debe estar ofertando actualmente, y su lista de espera no debe estar vacía.

const string SistemaVentas::primero_en_espera(const tProducto& producto) const {
	/* A IMPLEMENTAR */
	DiccionarioHash<tProducto, Lista<tCliente>>::ConstIterator it = _dic_prod_cliente.cbusca(producto);

	if (_dic_prod_unidades.contiene(producto) && !it.valor().esVacia()) {
		return it.valor().ultimo();
	}
	throw EErrorAccesoListaEspera();
}

    /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 LINEAL
	 
	*/

//lista_ventas()->Lista.Devuelve una lista del número de unidades vendido para cada
//producto desde la puesta en marcha del sistema.Cada elemento de esta lista consiste en :
//(i)el nombre del producto; y(ii) todas las unidades vendidas de este producto(si un
//producto se ha ofertado varias veces, este valor será el total vendido para cada oferta).La
//lista estará ordenada alfabéticamente por los nombres de productos.

Lista<Venta> SistemaVentas::lista_ventas() const {
	/* A IMPLEMENTAR */
	Lista<Venta> aux_lista;
	Diccionario<tProducto, int>::ConstIterator it = _dic_prod_vendidas.cbegin();
	while (it != _dic_prod_vendidas.cend()) {
		aux_lista.pon_final(Venta(it.clave(), it.valor()));
		it.next();
	}
	return aux_lista;
}

