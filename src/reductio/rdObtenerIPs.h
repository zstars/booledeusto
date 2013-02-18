/***************************************************************************
                          rdObtenerIPs.h  -  description
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

#ifndef RDOBTENERIPS_H
#define RDOBTENERIPS_H

#include "rdsimplificador.h"

/**
  *@author Borja Sotomayor
  */

/**
	* Clase base virtual para la obtención de implicantes primos.
	* Las clases derivadas deben implementar el metodo obtenerIPs.
	*/
class rdObtenerIPs
{
	public:
		/// Constructor. Recibe un puntero al simplificador al que pertenece.
		rdObtenerIPs(rdSimplificador *padre);
	
		/// A partir de los minterminos de la función, obtiene los implicantes
		/// primos de la función.	
		virtual void obtenerIPs() = 0;

	protected:
		/** Puntero al simplificador al que pertenece esta clase. */
		rdSimplificador *simp;
};

#endif
