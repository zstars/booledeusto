/*$T boole/Circuito/CircuitoCombinacional.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef CircuitoCombinacionalH
#define CircuitoCombinacionalH
#include "V_Circuito.h"
#include "Entrada.h"
#include "funciones.h"
#include "Puerta.h"
#include "PuertaAnd.h"
#include "PuertaOr.h"
#include "PuertaNand.h"
#include "PuertaNor.h"
class	CircuitoCombinacional
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int			nAnd, nOr, nNand, nNor;
	Entrada		*AEntradas;
	Entrada		*E2;
	AnsiString	*EC;
	int			lonE;	// Longitud del array de Entradas
	int			lonE2;
	int			lonEC;	// Longitud del array de terminos de la ecuacion.
	int			modo;
	AnsiString	s;
	Punto		limite, tamanio, salida;

	CircuitoCombinacional(void)		{ };
	CircuitoCombinacional(AnsiString s);
	~CircuitoCombinacional(void);

	bool	existeEntrada(AnsiString entrada);
	void	crearArrayEntradas(void);
	void	agregarEntrada(AnsiString nombre);
	void	crearArrayEC(void);
	void	eliminarEntradasRepetidas(void);
	void	ordenarEntradas(void);
	void	dibujarEntradas(int altura);
	void	asignarPosicionesAEntradas(int x, int y);
	void	dibujarCircuitoCombinacional(int desplazamientoX);
	void	dibujarSalida(void);

	int		getLonE(void)	{ return lonE; }
	void	buscarEntrada(AnsiString nombre);
	Punto	getLimite(void)		{ return limite; }
};
#endif
