/*$T boole/Circuito/FlipFlopD.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef FlipFlopDH
#define FlipFlopDH
#include "V_Circuito.h"
#include "FlipFlop.h"

class FlipFlopD : public FlipFlop
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Punto	D;

	FlipFlopD(void)		{ };
	FlipFlopD(int n, int x, int y);
	void	Dibujar(void);
	void	UnirD(int x1, int y1);
	void	UnirCLK(int x1, int y1);
	void	UnirQ(int x1, int nJK, int k);
};
#endif
