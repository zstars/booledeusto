/***************************************************************************
                          rdObtenerIPsQM.h  -  description
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

#ifndef RDOBTENERIPSQM_H
#define RDOBTENERIPSQM_H

#include <rdObtenerIPs.h>

/**
  *@author Borja Sotomayor
  */

/**
	* Clase de obtención de implicantes primos que utiliza el clásico método
	* de Quine-McCluskey.
	*/
class rdObtenerIPs_QM : public rdObtenerIPs  {
	public:
	
		/// Constructor. Recibe un puntero al simplificador al que pertenece.
		rdObtenerIPs_QM(rdSimplificador *padre);
		/// Destructor.
		~rdObtenerIPs_QM();

		void obtenerIPs();
};

#endif
