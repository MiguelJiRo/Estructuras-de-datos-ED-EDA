#ifndef __CONFEDERACION_HIDROGRAFICA_H
#define __CONFEDERACION_HIDROGRAFICA_H

#include "Rio.h"
#include "diccionarioHash.h"

class ERioDuplicado{};
class ERioNoExiste{};

// clase para representar la confederación hidrográfica: diccionario de nombres de río (clave = string) 
// y colección de los pantanos que contiene el río (valor = clase Rio = diccionario)

class ConfederacionHidrografica {
  public:
	  /**
	    Crea una confederación vacía, sin ríos.
	  */
	  ConfederacionHidrografica();

	  /**
	    Inserta un nuevo río en la confederación.
		Si el río ya existe, levanta la excepción ERioDuplicado
		@param rio El río a insertar
	  */
	  void insertar_rio(const string& rio);

	  /**
  	    Inserta un nuevo pantano en un río.
	    Si el río no existe, levanta la excepción ERioNoExiste.
	    Si el pantano ya existe, levanta la excepción EPantanoDuplicado.
	    @param rio El nombre del río al que se va a añadir del pantano.
	    @param pantano El nombre del pantano a añadir
	    @cmax Capacidad máxima del pantano
	    @vol Volumen inicial embalsado en el pantano
	  */
	  void insertar_pantano(const string& rio, const string& pantano, const float cmax, const float vol); 


	  /**
	    Embalsa un cierto volumen en un pantano de un rio
	    Si el río no existe, se levanta la excepción ERioNoExiste
	    Si el pantano no existe, se levanta la excepción EPantanoNoExiste
		Si no cabe todo el volumen de agua, el pantano se llena
		@param rio Nombre del rio
	    @param pantano Nombre del pantano
	    @param vol Volumen a embalsar
	  */
	  void embalsar(const string& rio, const string& pantano, const float vol);
	  
	  
	  /**
	    Consulta el volumen embalsado en un pantano de un río
	    Si el río no existe, se levanta la excepción ERioNoExiste
	    Si el pantano no existe, se levanta la excepción EPantanoNoExiste
	    @param rio Nombre del rio
	    @param pantano Nombre del pantano
	  */
	  float embalsado_pantano(const string& rio, const string& pantano) const; 

	  /**
	   Consulta el volumen total embalsado en un río
	   Si el río no existe, se levanta la excepción ERioNoExiste
	   @param rio Nombre del rio
	  */
	  float embalsado_cuenca(const string& rio) const; 

	  /**
	   Realiza un transvase de agua entre pantanos
	   Si alguno de los ríos no existe, se levanta la excepción ERioNoExiste
	   Si alguno de los pantanos no existe, se levanta la excepción EPantanoNoExiste
	   Si el volumen a transvasar es negativo, se cambia el sentido del transvase (es decir,
	   se pasa el agua del pantano destino al origen)
	   Solo se trasvasa la cantidad que quepa en el pantano destino, y, como 
	   mucho, la cantidad embalsada en el pantano de origen
	   @param rio_origen Nombre del río origen
	   @param pantano_origen Nombre del pantano origen
	   @param rio_destino Nombre del río destino
	   @param pantano_destino Nombre del pantano destino
	   @param vol Volumen a transvasar
	  */
	  void transvasar(const string& rio_origen, const string& pantano_origen, 
		              const string& rio_destino, const string& pantano_destino, 
		              float vol); 

  private:
	  DiccionarioHash<string, Rio> _rios;

	  /**
  	   Busca un río
	   Levanta la excepción ERioNoExiste en caso de que el río no exista.
	   @rio Nombre del rio a buscar
	   @return Referencia constante al río
	   */
	  const Rio& busca_rio(const string& rio) const;	  
};

#endif // !__CONFEDERACION_HIDROGRAFICA_H
