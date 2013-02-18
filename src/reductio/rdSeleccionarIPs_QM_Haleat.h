/***************************************************************************
                          rdSeleccionarIPs_QM_Haleat.h  -  description
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

#ifndef RDSELECCIONARIPS_QM_HALEAT_H
#define RDSELECCIONARIPS_QM_HALEAT_H

#include <rdSeleccionarIPsQM.h>

/**
  *@author Borja Sotomayor
  */

/**
	* Clase que utiliza un metodo heuristico para seleccionar un conjunto
	* de implicantes primos que puede no ser minimo. Al encontrar una tabla ciclica,
	* se selecciona un implicante primo al azar y se incluye en la cobertura minima.
	*/
class rdSeleccionarIPs_QM_Haleat : public rdSeleccionarIPs_QM  {
	public:
		/// Constructor. Recibe un puntero al simplificador al que pertenece.
		rdSeleccionarIPs_QM_Haleat(rdSimplificador *padre);
		/// Destructor
		~rdSeleccionarIPs_QM_Haleat();

		void ResolucionCiclica(void);
};

#endif
