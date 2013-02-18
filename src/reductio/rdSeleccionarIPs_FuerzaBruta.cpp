/***************************************************************************
                          rdSeleccionarIPs_FuerzaBruta.cpp  -  description
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

#include "rdSeleccionarIPs_FuerzaBruta.h"


/// Constructor. Recibe un puntero al simplificador al que pertenece.
rdSeleccionarIPs_FuerzaBruta::rdSeleccionarIPs_FuerzaBruta(rdSimplificador *padre):rdSeleccionarIPs(padre)
{
}


/// Destructor
rdSeleccionarIPs_FuerzaBruta::~rdSeleccionarIPs_FuerzaBruta()
{
}


/** Una vez que se han obtenido los implicantes primos de la función,
	* este metodo hace una selección de IPs.
	*/
void rdSeleccionarIPs_FuerzaBruta::SeleccionarIPs(void)
{
	list<CuboBool> *listaIPs = new list<CuboBool>(simp->setIPs->begin(), simp->setIPs->end());
	list<CuboBool> *listaMint = new list<CuboBool>(simp->setMint->begin(), simp->setMint->end());

	coberturaMinima = new rdCoberturaMinima(listaIPs, listaMint, simp->numVar, false);

	for(list<CuboBool*>::iterator i=coberturaMinima->listaMinima.begin(); i!=coberturaMinima->listaMinima.end(); i++)
		simp->ipe[2]->insert(*(*i));

	simp->Mensaje = coberturaMinima->mensaje;

	delete coberturaMinima;
	delete listaIPs;
	delete listaMint;
}