/*$T boole/Circuito/PuertaNor.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef PuertaNorH
#define PuertaNorH
#include "PuertaOr.h"

class PuertaNor : public PuertaOr
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	PuertaNor(void)		{ };
	PuertaNor(int n, int x1, int x2);
	void	Dibujar(void);
};
#endif
