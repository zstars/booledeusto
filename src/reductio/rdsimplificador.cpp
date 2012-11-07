/***************************************************************************
                          rdsimplificador.cpp  -  description
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

#include "rdsimplificador.h"
#include "rdObtenerIPs.h"
#include "rdObtenerIPsQM.h"
#include "rdSeleccionarIPs_QM_Haleat.h"
#include "rdSeleccionarIPs_QM_Hbestcover.h"
#include "rdSeleccionarIPs_QM_NHsesg1.h"
#include "rdSeleccionarIPs_QM_NHsesg2.h"
#include "rdSeleccionarIPs_QM_NHnosesg.h"
#include "rdSeleccionarIPs_FuerzaBruta.h"



/*#########-  CONSTRUCTORES Y DESTRUCTORES  -#########*/


/// Constructor. Recibe el numero de variables de la funcion.
rdSimplificador::rdSimplificador(size numVarP):numVar(numVarP),simplificada(false), obtenedor(NULL)
{

	metodosObtencion[0] = "Método Quine-McCluskey";
	metodosObtencion[1] = NULL;

	metodosSeleccion[0] = "No-Heuristico Recursivo Sesgado 1";
	metodosSeleccion[1] = "No-Heuristico Recursivo Sesgado 2";
	metodosSeleccion[2] = "No-Heuristico Recursivo sin Sesgado";
	metodosSeleccion[3] = "Heuristico - Metodo 'Best Cover'";
	metodosSeleccion[4] = "Heuristico - Metodo Aleatorio";
	metodosSeleccion[5] = "Fuerza Bruta";
	metodosSeleccion[6] = NULL;

	setMint = new set<CuboBool>();
  setTIs = new set<CuboBool>();
  setIPs = new set<CuboBool>();

  ipe[0] = new set<CuboBool>();
  ipe[1] = new set<CuboBool>();
  ipe[2] = new set<CuboBool>();
        obtenedor = NULL;
        selector = NULL;
};


/// Destructor
rdSimplificador::~rdSimplificador()
{
	if(obtenedor)
		delete obtenedor;
	if(selector)
		delete selector;
}




/*#########-  METODOS PUBLICOS  -#########*/


/// Anyade un mintermino a la funcion
void rdSimplificador::AnyadirMint(const CuboBool &c)
{
    CuboBool cAux=c;

    cAux.literales = numVar;
    setMint->insert(cAux);
    simplificada = false;
}


/// Anyade un termino irrelevante a la funcion
void rdSimplificador::AnyadirTI(const CuboBool &c)
{
    CuboBool cAux=c;

    cAux.literales = numVar;
    setTIs->insert(cAux);
    simplificada = false;
}


/// Simplifica la funcion.
void rdSimplificador::Simplificar(void)
{
		Mensaje = "No hay detalles.";

    setIPs->clear();

    ipe[PRIMARIO]->clear();
    ipe[SECUNDARIO]->clear();
    ipe[NO_ESENCIAL]->clear();

		obtenedor->obtenerIPs();
		selector->SeleccionarIPs();

    simplificada = true;
}




/*#########-  METODOS GET Y SET  -#########*/


/// Devuelve el iterador begin del conjunto de implicantes primos.
/// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPsBEGIN(void)
{
    return setIPs->begin();
}


/// Devuelve el iterador end del conjunto de implicantes primos.
/// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPsEND(void)
{
    return setIPs->end();
}


/// Devuelve el iterador begin del conjunto de implicantes primos esenciales primarios.
/// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPE1sBEGIN(void)
{
    return ipe[PRIMARIO]->begin();
}


// Devuelve el iterador end del conjunto de implicantes primos esenciales primarios.
// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPE1sEND(void)
{
    return ipe[PRIMARIO]->end();
}


// Devuelve el iterador begin del conjunto de implicantes primos esenciales secundarios.
// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPE2sBEGIN(void)
{
    return ipe[SECUNDARIO]->begin();
}


// Devuelve el iterador end del conjunto de implicantes primos esenciales secundarios.
// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPE2sEND(void)
{
    return ipe[SECUNDARIO]->end();
}


// Devuelve el iterador begin del conjunto de implicantes primos no esenciales.
// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPnEsBEGIN(void)
{
    return ipe[NO_ESENCIAL]->begin();
}


// Devuelve el iterador end del conjunto de implicantes primos no esenciales.
// Apunta a un conjunto vacio si la función no ha sido simplificada.
set<CuboBool>::iterator rdSimplificador::setIPnEsEND(void)
{
    return ipe[NO_ESENCIAL]->end();
}


/// Devuelve el numero de variables de la función.
size rdSimplificador::GetNumVar(void)
{
	return numVar;
}


/// Permite fijar el metodo de obtención de implicantes primos que va a utilizarse.
/// El codigo debe estar en el rango [0..NUM_METODOS_OBT)
int rdSimplificador::SetObtenedor(int codObt)
{
	switch(codObt)
	{
  	case QM:
			if (obtenedor)
				delete obtenedor;
			obtenedor = new rdObtenerIPs_QM(this);
			return 0;
		default: return 1;
	}
}


/// Permite fijar el metodo de selección de implicantes primos que va a utilizarse.
/// El codigo debe estar en el rango [0..NUM_METODOS_SEL)
int rdSimplificador::SetSelector(int codSel)
{
	switch(codSel)
	{
  	case QM_NOHEUR_SESGADO1:
			if (selector)
				delete selector;
			selector = new rdSeleccionarIPs_QM_NHsesg1(this);
			return 0;
  	case QM_NOHEUR_SESGADO2:
			if (selector)
				delete selector;
			selector = new rdSeleccionarIPs_QM_NHsesg2(this);
			return 0;
  	case QM_NOHEUR_NOSESGADO:
			if (selector)
				delete selector;
			selector = new rdSeleccionarIPs_QM_NHnosesg(this);
			return 0;
  	case QM_HEUR_BESTCOVER:
			if (selector)
				delete selector;
			selector = new rdSeleccionarIPs_QM_Hbestcover(this);
			return 0;
  	case QM_HEUR_ALEATORIO:
			if (selector)
				delete selector;
			selector = new rdSeleccionarIPs_QM_Haleat(this);
			return 0;
  	case FUERZA_BRUTA:
			if (selector)
				delete selector;
			selector = new rdSeleccionarIPs_FuerzaBruta(this);
			return 0;
		default: return 1;
	}
}
