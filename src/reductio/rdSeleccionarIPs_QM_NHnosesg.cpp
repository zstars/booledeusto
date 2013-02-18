/***************************************************************************
                          rdSeleccionarIPs_QM_NHnosesg.cpp  -  description
                             -------------------
    begin                : Sat Apr 14 2001
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

#include "rdSeleccionarIPs_QM_NHnosesg.h"


/// Constructor. Recibe un puntero al simplificador al que pertenece.
rdSeleccionarIPs_QM_NHnosesg::rdSeleccionarIPs_QM_NHnosesg(rdSimplificador *padre):rdSeleccionarIPs_QM(padre)
{
}


/// Destructor
rdSeleccionarIPs_QM_NHnosesg::~rdSeleccionarIPs_QM_NHnosesg()
{
}


/** Realiza una seleccion de implicantes primos para resolver una
	* tabla ciclica (cuando ningun implicante primo es inmediatamente
	* esencial).
	*/
void rdSeleccionarIPs_QM_NHnosesg::ResolucionCiclica(void)
{
	list<CuboBool> *listaIPs = new list<CuboBool>(setIPsAux.begin(), setIPsAux.end());
	list<CuboBool> *listaMint = new list<CuboBool>(simp->setMint->begin(), simp->setMint->end());

	coberturaMinima = new rdCoberturaMinima(listaIPs, listaMint, simp->numVar, false);

	for(list<CuboBool*>::iterator i=coberturaMinima->listaMinima.begin(); i!=coberturaMinima->listaMinima.end(); i++)
		simp->ipe[2]->insert(*(*i));

	simp->setMint->clear();

	simp->Mensaje = coberturaMinima->mensaje;

	delete coberturaMinima;
	delete listaIPs;
	delete listaMint;

}