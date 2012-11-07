/***************************************************************************
                          rdSeleccionarIPs_QM_NHsesg1.h  -  description
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

#ifndef RDSELECCIONARIPS_QM_NHSESG1_H
#define RDSELECCIONARIPS_QM_NHSESG1_H

#include <rdSeleccionarIPsQM.h>
#include "rdCoberturaMinima.h"

/**
  *@author Borja Sotomayor
  */

/**
	* Clase que utiliza un metodo no heuristico para seleccionar un conjunto
	* minimo de implicantes primos. Al llegar a una tabla ciclica, se hace
	* una exploración recursiva de las posibles combinaciones de implicantes
	* primos que podrian formar la cobertura minima. La exploracion se sesga
	* siempre que es posible. La lista de implicantes primos se explora
	* en el orden en el que llega (no se preprocesa la lista).
	*/
class rdSeleccionarIPs_QM_NHsesg1 : public rdSeleccionarIPs_QM  {
	public:
		/// Constructor. Recibe un puntero al simplificador al que pertenece.
		rdSeleccionarIPs_QM_NHsesg1(rdSimplificador *padre);
		/// Destructor
		~rdSeleccionarIPs_QM_NHsesg1();
	
		void ResolucionCiclica(void);
	
	private:
		/// En caso de llegar a una tabla ciclica, utilizamos 'coberturaMinima' para
		/// encontrar entre los implicantes primos que queden un conjunto minimo
		/// que cubra los minterminos que todavia no han sido cubiertos.
		rdCoberturaMinima *coberturaMinima;
};

#endif
