/***************************************************************************
                          rdSeleccionarIPs_QM_Hbestcover.h  -  description
                             -------------------
    begin                : Fri Apr 13 2001
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

#ifndef RDSELECCIONARIPS_QM_HBESTCOVER_H
#define RDSELECCIONARIPS_QM_HBESTCOVER_H

#include <rdSeleccionarIPsQM.h>

/**
  *@author Borja Sotomayor
  */

/**
	* Clase que utiliza un metodo heuristico (Best Cover) para seleccionar un conjunto
	* de implicantes primos que puede no ser minimo. Al encontrar una tabla ciclica,
	* se selecciona el implicante primo que más minterminos cubra, y se incluye
	* en la cobertura minima.
	*/
class rdSeleccionarIPs_QM_Hbestcover : public rdSeleccionarIPs_QM  {
	public:
		/// Constructor. Recibe un puntero al simplificador al que pertenece.
		rdSeleccionarIPs_QM_Hbestcover(rdSimplificador *padre);
		/// Destructor
		~rdSeleccionarIPs_QM_Hbestcover();

		void ResolucionCiclica(void);
};

#endif
