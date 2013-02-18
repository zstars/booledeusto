/*$T boole/Circuito/Entrada.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef EntradaH
#define EntradaH
#include "V_Circuito.h"

class	Entrada
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	AnsiString	nombre;
	int			x;
	int			y;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Entrada(void)	{ };
	Entrada(AnsiString n, int x1, int x2);
	Entrada(AnsiString n);

	void		Dibujar(int altura);
	void		DibujarNot(int altura);
	void		Unir(int x1, int y1);

	AnsiString	getNombre(void)				{ return nombre; }
	int			getx(void)					{ return x; }
	int			gety(void)					{ return y; }
	void		setNombre(AnsiString n)		{ nombre = n; }
	void		setx(int x1)				{ x = x1; }
	void		sety(int y1)				{ y = y1; }
};
#endif
