/*$T boole/Circuito/CircuitoSecuencial.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef CircuitoSecuencialH
#define CircuitoSecuencialH

#include "V_Circuito.h"
#include "funciones.h"
#include "CircuitoCombinacional.h"
#include "FlipFlopJK.h"
#include "FlipFlopD.h"

class	CircuitoSecuencial
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int						numeroFlipFlops;
	TListBox				*Lista;
	CircuitoCombinacional	*CC;
	CircuitoCombinacional	*salida;
	bool					tipoFlipFlops;

	~CircuitoSecuencial(void);
	CircuitoSecuencial(TListBox *Lista1, int longitudLista, bool tipoFlipFlops1);
	void	dibujarCircuitoSecuencial(void);
};
#endif
