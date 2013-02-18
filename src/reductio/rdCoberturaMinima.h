/***************************************************************************
                          rdCoberturaMinima.h  -  description
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

#ifndef RDCOBERTURAMINIMA_H
#define RDCOBERTURAMINIMA_H

#include "cubobool.h"
#include <list>
#include <string>

/**
  *@author Borja Sotomayor
  */

/**
	* El proposito de esta clase es hallar una cobertura minima para un conjunto
	* de minterminos. La cobertura minima se halla en el momento que se instancia
	* la clase.
	*/
class rdCoberturaMinima {

	public:

/*#########-  CONSTRUCTORES Y DESTRUCTORES -#########*/
	
		/** Constructor. Recibe la lista de minterminos (listMint) de la cual se quiere
			* encontrar la cobertura minima. Tambien se reciben los IPs (listIPs) de los
			* que se dispone para encontrar la cobertura minima, el numero de variables (numV),
			* y un parametro que indica si se desea o no sesgar el arbol de busqueda (sesg).
			* En el momento en el que se crea el objeto, se haya la cobertura minima, y se
			* deposita el resultado en el miembro 'listaMinima'.
			*/
		rdCoberturaMinima(list<CuboBool> *listIPs, list<CuboBool> *listMint, size numV, bool sesg);
		/// Destructor
		~rdCoberturaMinima();


/*#########-  MIEMBROS PUBLICOS -#########*/

		/// Lista en la que se depositan los IPs que conforman la cobertura minima.
		list<CuboBool*> listaMinima;
		/** Tras encontrar la cobertura minima, se deposita en este miembro un mensaje
			* con datos estadisticos, tales como el sesgo del arbol de busqueda.
			*/
		string mensaje;


private:	

/*#########-  METODOS PRIVADOS -#########*/

	/// Función que recorre recursivamente el arbol de busqueda.
	long recorrer(list<CuboBool>::iterator i);
	/// Elabora el mensaje con datos estadisticos.
	void elaborarMensaje(void);


/*#########-  MIEMBROS PRIVADOS -#########*/

	/// Lista de minterminos para los cuales se desea encontrar una cobertura minima.
	list<CuboBool> *listaMint;
	/// Lista de implicantes primos de los que se dispone para encontrar la cobertura minima.
	list<CuboBool> *listaIPs;

	/// Numero de variables de la función.
	size numVar;
	/// Indica si vamos a sesgar el arbol de busqueda.
	bool sesgo;


	/// El numero de implicantes primos de los que disponemos.
	long unsigned int numIPs;
	/// El numero de combinaciones de IPs procesadas.
	long unsigned int combProcesadas;

	/// Estructuras auxiliares de datos
	list<CuboBool*> pila, listaMintAux;

	/// Variables auxiliares
	unsigned int coste, costeMejor, tamanyoMejor, nivel;
};

#endif
