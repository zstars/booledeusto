/*$T boole/Circuito/FlipFlopJK.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef FlipFlopJKH
#define FlipFlopJKH
#include "V_Circuito.h"
#include "FlipFlop.h"
class FlipFlopJK : public FlipFlop
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Punto	J, K;

	FlipFlopJK(void)	{ };
	FlipFlopJK(int n, int x, int y);
	void	Dibujar(void);
	void	UnirJ(int x1, int y1);
	void	UnirK(int x1, int y1);
	void	UnirCLK(int x1, int y1);
	void	UnirQ(int x1, int nJK, int k);
};
#endif
