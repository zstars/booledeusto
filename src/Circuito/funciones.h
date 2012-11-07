/*$T boole/Circuito/funciones.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef funcionesH
#define funcionesH
#include "Entrada.h"

bool		salidaNegada(AnsiString s);
AnsiString	getNombreEntrada(AnsiString s);
bool		existeSim(AnsiString s, char sim);
int			Modo(AnsiString s);
int			numTerminos(AnsiString s);
bool		mayor(AnsiString E1, AnsiString E2);
bool		esSimbolo(AnsiString s);
bool		esEntrada(AnsiString s);

// A PARTIR DE AQUÍ SON FUNCIONES PARA DIBUJAR EL CIRCUITO.
void		limpiarCanvas(void);
int			crearArrayEntradas(AnsiString s, Entrada *E, int lonE);
int			crearArrayEC(AnsiString s, AnsiString *EC, int lonEC);
int			getNumeroAnds(AnsiString *EC, int lonEC, int modo);
int			getNumeroOrs(AnsiString *EC, int lonEC, int modo);
int			getNumeroNands(AnsiString *EC, int lonEC, int modo);
int			getNumeroNors(AnsiString *EC, int lonEC, int modo);
int			ordenarEntradas(Entrada *E, int lonE);
void		asignarPosicionesAEntradas(Entrada *E, int lonE);
void		dibujarEntradas(Entrada *E, int lonE);
void		dibujarCircuito
			(
				AnsiString	s,
				Entrada		*E,
				int			lonE,
				AnsiString	*EC,
				int			lonEC,
				int			modo,
				int			nAnd,
				int			nOr,
				int			nNor,
				int			nNand,
				AnsiString	salida,
				Punto		limite
			);
#endif
