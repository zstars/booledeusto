/***************************************************************************
                          rdsimplificador.h  -  description
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

#ifndef RDSIMPLIFICADOR_H
#define RDSIMPLIFICADOR_H

/**
  *@author Borja Sotomayor
  */


#include "cubobool.h"
#include "reductio.h"
#include <set>
#include <string>

/**
	* Esta es la clase principal y más importante de Reductio. Gestiona
	*	todo el proceso de simplificación.
	*/
class rdSimplificador {

public:

	// Las clases de obtención y selección de Reductio tienen que
	// ser amigas del simplificador, ya que tienen que acceder
	// a datos privados suyos.
	friend class rdObtenerIPs;
	friend class rdObtenerIPs_QM;
	friend class rdSeleccionarIPs;
	friend class rdSeleccionarIPs_QM;
	friend class rdSeleccionarIPs_QM_Haleat;
	friend class rdSeleccionarIPs_QM_Hbestcover;
	friend class rdSeleccionarIPs_QM_NHsesg1;
	friend class rdSeleccionarIPs_QM_NHsesg2;
	friend class rdSeleccionarIPs_QM_NHnosesg;
	friend class rdSeleccionarIPs_FuerzaBruta;


/*#########-  CONSTRUCTORES Y DESTRUCTORES  -#########*/
    /// Constructor. Recibe el numero de variables de la funcion.
    rdSimplificador(size numVarP);
		/// Destructor
    ~rdSimplificador();


/*#########-  METODOS PUBLICOS  -#########*/

    /// Anyade un mintermino a la funcion
    void AnyadirMint(const CuboBool &c);
    /// Anyade un termino irrelevante a la funcion
    void AnyadirTI(const CuboBool &c);
    /// Simplifica la funcion.
    void Simplificar(void);


/*#########-  METODOS GET Y SET  -#########*/
		/// @name Metodos Get Y SET
		//@{

    /// Devuelve el iterador begin del conjunto de implicantes primos.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPsBEGIN(void);
    /// Devuelve el iterador end del conjunto de implicantes primos.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPsEND(void);
    /// Devuelve el iterador begin del conjunto de implicantes primos esenciales primarios.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPE1sBEGIN(void);
    /// Devuelve el iterador end del conjunto de implicantes primos esenciales primarios.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPE1sEND(void);
    /// Devuelve el iterador begin del conjunto de implicantes primos esenciales secundarios.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPE2sBEGIN(void);
    /// Devuelve el iterador end del conjunto de implicantes primos esenciales secundarios.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPE2sEND(void);
    /// Devuelve el iterador begin del conjunto de implicantes primos no esenciales.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPnEsBEGIN(void);
    /// Devuelve el iterador end del conjunto de implicantes primos no esenciales.
		/// Apunta a un conjunto vacio si la función no ha sido simplificada.
    set<CuboBool>::iterator setIPnEsEND(void);

    /// Devuelve el numero de variables de la función.
		size GetNumVar(void);

		/// Permite fijar el metodo de obtención de implicantes primos que va a utilizarse.
		/// El codigo debe estar en el rango [0..NUM_METODOS_OBT)
	  int SetObtenedor(int codObt);
		/// Permite fijar el metodo de selección de implicantes primos que va a utilizarse.
		/// El codigo debe estar en el rango [0..NUM_METODOS_SEL)
  	int SetSelector(int codSel);

  	//@}
/*#########-  MIEMBROS PUBLICOS  -#########*/

	/// Mensaje en el que se dan detalles sobre la simplificacion.
  string Mensaje;
	/// Array con los nombres de los metodos de obtención de implicantes primos.
	/// metodosObtencion[n] contiene el nombre del metodo cuyo codigo es n.
  char * metodosObtencion[NUM_METODOS_OBT + 1];
	/// Array con los nombres de los metodos de selección de implicantes primos.
	/// metodosSelección[n] contiene el nombre del metodo cuyo codigo es n.
	char * metodosSeleccion[NUM_METODOS_SEL + 1];

private:


/*#########-  CONJUNTOS  -#########*/
		/// @name Conjuntos
		//@{
    /// Conjunto de Minterminos de la funcion.
    set<CuboBool> *setMint;
    /// Conjunto de Terminos Irrelevantes de la función.
    set<CuboBool> *setTIs;
    /// Conjunto de Implicantes Primos de la función.
    set<CuboBool> *setIPs;
    /// Array de implicantes primos esenciales primarios (0),
    /// esenciales secundarios (1), y no esenciales (2).
    set<CuboBool> *ipe[3];
		//@}

/*#########-  MIEMBROS PRIVADOS  -#########*/

		/// El numero de variables
    size numVar;
    /// Nos indica si la funcion esta simplificada o no
    bool simplificada;

		/// Puntero al objeto que se encargará de obtener los implicantes primos
		/// de la función.
	  rdObtenerIPs *obtenedor;
		/// Puntero al objeto que se encargará de hacer una selección de implicantes
		/// primos.
		rdSeleccionarIPs *selector;

};

#endif
