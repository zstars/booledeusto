/*$T boole/Boole1/DINARRAY.CPP GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#include <math.h>
#pragma hdrstop
#include "DinArray.h"

//
// =======================================================================================================================
//    escribe el nombre del sistema combinacional
// =======================================================================================================================
//
void DinArray::EscribirNombre(AnsiString a)
{
	nombre = a;
};

//
// =======================================================================================================================
//    devuelve el nombre del sistema combinacional
// =======================================================================================================================
//
AnsiString DinArray::LeerNombre(void)
{
	return nombre;
};

//
// =======================================================================================================================
//    devuelve el número de variables de entrada
// =======================================================================================================================
//
int DinArray::NumEntradas(void)
{
	return vEntradas;
};

//
// =======================================================================================================================
//    devuelve el número de filas (2^vEntradas)
// =======================================================================================================================
//
int DinArray::NumFilas(void)
{
	return filas;
};

//
// =======================================================================================================================
//    devuelve el número de columnas o variables de salida
// =======================================================================================================================
//
int DinArray::NumColumnas(void)
{
	return columnas;
};

//
// =======================================================================================================================
//    borra los nombres de las variables de entrada
// =======================================================================================================================
//
void DinArray::BorrarEntradas(void)
{
	entradas = "";
}

//
// =======================================================================================================================
//    borra los nombres de las variables de salida
// =======================================================================================================================
//
void DinArray::BorrarSalidas(void)
{
	salidas = "";
}

/*
 =======================================================================================================================
    crea (no construye) la matriz, los vectores para los nombres de las variables de entrada y salida e inicializa las
    variables correspondientes al número de entradas, filas, columnas y los números de orden de cada fila
 =======================================================================================================================
 */
void DinArray::DinX(AnsiString nom, int vEntr, int col)
{
	nombre = nom;
	vEntradas = vEntr;
	filas = pow(2, vEntradas);
	columnas = col;
	BorrarEntradas();
	BorrarSalidas();

	matriz = new nodoEntrada;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	nodoEntrada *ultimoPunteroEntrada = matriz;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	(*matriz).nOrden = 0;

	for(int fila = 1; fila < filas; fila++)
	{
		(*ultimoPunteroEntrada).estaFila = new nodoSalida;
		(*(*ultimoPunteroEntrada).estaFila).dato = ' ';

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		nodoSalida	*ultimoPunteroSalida = (*ultimoPunteroEntrada).estaFila;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int columna = 1; columna < columnas; columna++)
		{
			(*ultimoPunteroSalida).siguienteSalida = new nodoSalida;
			ultimoPunteroSalida = (*ultimoPunteroSalida).siguienteSalida;
			(*ultimoPunteroSalida).dato = ' ';
		}
		(*ultimoPunteroSalida).siguienteSalida = NULL;
		(*ultimoPunteroEntrada).siguienteEntrada = new nodoEntrada;
		ultimoPunteroEntrada = (*ultimoPunteroEntrada).siguienteEntrada;
		(*ultimoPunteroEntrada).nOrden = fila;
	}
	(*ultimoPunteroEntrada).estaFila = new nodoSalida;
	(*(*ultimoPunteroEntrada).estaFila).dato = ' ';

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	nodoSalida	*ultimoPunteroSalida = (*ultimoPunteroEntrada).estaFila;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int columna = 1; columna < columnas; columna++)
	{
		(*ultimoPunteroSalida).siguienteSalida = new nodoSalida;
		ultimoPunteroSalida = (*ultimoPunteroSalida).siguienteSalida;
		(*ultimoPunteroSalida).dato = ' ';
	}
	(*ultimoPunteroSalida).siguienteSalida = NULL;
	(*ultimoPunteroEntrada).siguienteEntrada = NULL;
};

//
// =======================================================================================================================
//    borra una celda y todas que le siguen en la fila de forma recursiva
// =======================================================================================================================
//
void DinArray::borrarSalidas(nodoSalida *puntero)
{
	if((*puntero).siguienteSalida != NULL)
	{
		borrarSalidas((*puntero).siguienteSalida);
	}

	delete puntero;
};

//
// =======================================================================================================================
//    borra una fila y todas las que le siguen de forma recursiva
// =======================================================================================================================
//
void DinArray::borrarEntradas(nodoEntrada *puntero)
{
	if((*puntero).siguienteEntrada != NULL)
	{
		borrarEntradas((*puntero).siguienteEntrada);
	}

	borrarSalidas((*puntero).estaFila);
	delete puntero;
};

//
// =======================================================================================================================
//    borra (no destruye) la matriz e inicializa las variables a 0
// =======================================================================================================================
//
void DinArray::BorrarDinArray(void)
{
	nombre = "";
	if(matriz != NULL)
	{
		borrarEntradas(matriz);
		matriz = NULL;
	}

	entradas = "";
	salidas = "";
	vEntradas = 0;
	filas = 0;
	columnas = 0;
};

//
// =======================================================================================================================
//    lee una posición de la matriz
// =======================================================================================================================
//
char DinArray::LeerDinArray(int fil, int col)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	nodoEntrada *punteroEntrada = matriz;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int f = 0; f < fil; f++)
	{
		punteroEntrada = (*punteroEntrada).siguienteEntrada;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	nodoSalida	*punteroSalida = (*punteroEntrada).estaFila;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int c = 0; c < col; c++)
	{
		punteroSalida = (*punteroSalida).siguienteSalida;
	}

	return(*punteroSalida).dato;
};

//
// =======================================================================================================================
//    escribe un caracter en una posición de la matriz
// =======================================================================================================================
//
void DinArray::EscribirDinArray(int fil, int col, char dat)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	nodoEntrada *punteroEntrada = matriz;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int f = 0; f < fil; f++)
	{
		punteroEntrada = (*punteroEntrada).siguienteEntrada;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	nodoSalida	*punteroSalida = (*punteroEntrada).estaFila;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int c = 0; c < col; c++)
	{
		punteroSalida = (*punteroSalida).siguienteSalida;
	}
	(*punteroSalida).dato = dat;
};

/*
 =======================================================================================================================
    escribe el nombre de una variable de entrada en la posición que le indiquemos del vector de entradas
 =======================================================================================================================
 */
void DinArray::AnadirEntrada(AnsiString a)
{
	entradas = entradas + a;
};

/*
 =======================================================================================================================
    escribe el nombre de una variable de salida en la posición que le indiquemos del vector de salidas
 =======================================================================================================================
 */
void DinArray::AnadirSalida(AnsiString a)
{
	salidas = salidas + a;
};

/*
 =======================================================================================================================
    lee el nombre de una variable de entrada de la posición que le indiquemos del vector de entradas
 =======================================================================================================================
 */
AnsiString DinArray::LeerEntrada(int a)
{
	return Trim(entradas.SubString(30 * a + 1, 30));
};

/*
 =======================================================================================================================
    lee el nombre de una variable de salida de la posición que le indiquemos del vector de salidas
 =======================================================================================================================
 */
AnsiString DinArray::LeerSalida(int a)
{
	return Trim(salidas.SubString(30 * a + 1, 30));
};
