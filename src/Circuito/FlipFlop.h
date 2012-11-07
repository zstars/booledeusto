/*$T boole/Circuito/FlipFlop.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef FlipFlopH
#define FlipFlopH

#include "V_Circuito.h"

class	FlipFlop
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Punto			Q, NQ, CLK, RESET;
	int				n;
	FlipFlop(void)	{ };
	FlipFlop(int n, int x, int y);
	virtual void	Dibujar(void);

	//
	// virtual void UnirJ (int ,int ); virtual void UnirK (int ,int ); virtual void
	// UnirD (int ,int );
	//
	void			UnirCLK(int x1, int y1);
	void			UnirRESET(int x1, int y1);
	void			UnirQ(int x1, int nJK, int k);
};
#endif
