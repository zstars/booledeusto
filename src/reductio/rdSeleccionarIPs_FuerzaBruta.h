/***************************************************************************
                          rdSeleccionarIPs_FuerzaBruta.h  -  description
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

#ifndef RDSELECCIONARIPS_FUERZABRUTA_H
#define RDSELECCIONARIPS_FUERZABRUTA_H


#include "rdSeleccionarIPs.h"
#include "rdCoberturaMinima.h"

/**
  *@author Borja Sotomayor
  */

/**
	* Clase que selecciona el conjunto minimo de implicantes primos
	* utilizando un algoritmo de fuerza bruta.
	*/
class rdSeleccionarIPs_FuerzaBruta : public rdSeleccionarIPs {
	public:
		/// Constructor. Recibe un puntero al simplificador al que pertenece.
		rdSeleccionarIPs_FuerzaBruta(rdSimplificador *padre);
		/// Destructor
		~rdSeleccionarIPs_FuerzaBruta();

		void SeleccionarIPs();

	private:
		/// Utilizado para encontrar un conjunto minimo de implicantes primos
		/// que cubran los minterminos de la función.
		rdCoberturaMinima *coberturaMinima;
};

#endif
