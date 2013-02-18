/***************************************************************************
                          rdSeleccionarIPsQM.h  -  description
                             -------------------
    begin                : Thu Apr 12 2001
    copyright            : (C) 2001 by Borja Sotomayor
    email                : borja@borjanet.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef RDSELECCIONARIPSQM_H
#define RDSELECCIONARIPSQM_H

#include <rdSeleccionarIPs.h>

/**
  *@author Borja Sotomayor
  */

/**
	* Clase base virtual para la obtención de implicantes primos utilizando
	* el método de Quine-McCluskey. En esta clase están codificados los procedimientos
	* de extracción de implicantes primos esenciales. Sin embargo, las clases
	* derivadas deben implementar ResolucionCiclica(), para que la clase
	* pueda resolver tablas ciclicas en el proceso de selección.
	*/
class rdSeleccionarIPs_QM : public rdSeleccionarIPs  {
	public:
		/// Constructor. Recibe un puntero al simplificador al que pertenece.
		rdSeleccionarIPs_QM(rdSimplificador *padre);

		void SeleccionarIPs();


	protected:

/*#########-  METODOS PROTEGIDOS  -#########*/
    /** Encuentra los implicantes primos esenciales de la funcion booleana
    	* basandose en el conjunto de implicantes primos y minterminos.
			*/
    bool EncontrarIPEs(void);
    /// Busca los minterminos que quedan por cubrir.
    void BuscarTerminosNoCubiertos(void);
    /// Elimina los implicantes primos redundantes del conjunto de IPs.
    void EliminarRedundantes(void);
    /// Elimina los implicantes primos no deseables del conjunto de IPS.
    void EliminarNoDeseables(void);
    /** Realiza una seleccion de implicantes primos para resolver una
			* tabla ciclica (cuando ningun implicante primo es inmediatamente
			* esencial).
			*/
    virtual void ResolucionCiclica(void) = 0;


/*#########-  MIEMBROS PROTEGIDOS  -#########*/

    /// Conjunto auxiliar de implicantes primos
    set<CuboBool> setIPsAux;

    /** Variable que indica el tipo de implicantes primos
			* (esenciales primarios, esenciales secundarios, o
			* no esenciales) se estan seleccionando.
			*/
    int tipoIPE;
};

#endif
