/***************************************************************************
                          rdSeleccionarIPs_QM_Hbestcover.cpp  -  description
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

#include "rdSeleccionarIPs_QM_Hbestcover.h"


/// Constructor. Recibe un puntero al simplificador al que pertenece.
rdSeleccionarIPs_QM_Hbestcover::rdSeleccionarIPs_QM_Hbestcover(rdSimplificador *padre):rdSeleccionarIPs_QM(padre)
{
}


/// Destructor
rdSeleccionarIPs_QM_Hbestcover::~rdSeleccionarIPs_QM_Hbestcover()
{
}



/** Realiza una seleccion de implicantes primos para resolver una
	* tabla ciclica (cuando ningun implicante primo es inmediatamente
	* esencial).
	*/
void rdSeleccionarIPs_QM_Hbestcover::ResolucionCiclica(void)
{
		// Esta resolución ciclica no es best-cover!!!!!
		// Hay que implementarla correctamente

    set<CuboBool>::iterator i=setIPsAux.begin();

    simp->ipe[2]->insert(*i);


    set<CuboBool>::iterator j=simp->setMint->begin();
    while(j!=simp->setMint->end())
        if ((*i)>>(*j))
            simp->setMint->erase(j++);
        else
            j++;

    setIPsAux.erase(i);
}
