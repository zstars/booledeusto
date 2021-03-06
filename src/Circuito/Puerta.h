/*$T boole/Circuito/Puerta.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef PuertaH
#define PuertaH
#include "V_Circuito.h"

class	Puerta
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int				n;	// n�mero de entradas.

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Punto			*Patita;

	//
	// ===================================================================================================================
	//    Patita[0]: esquina superior izquierda. Patita[1]: salida de la puerta. Patita[2]: primera entrada de la puerta.
	// ===================================================================================================================
	//
	Puerta(void)	{ };
	Puerta(int n, int x, int y);
	virtual void	Dibujar(void);
	void __fastcall Unir(Punto *Patita);

	int				getN(void)	{ return n; }
	Punto			getP(int i) { return Patita[i]; }
	void			setN(int n1){ n = n1; }
};
#endif
