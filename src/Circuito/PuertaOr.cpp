/*$T boole/Circuito/PuertaOr.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "PuertaOr.h"
#pragma package(smart_init)
#include <Math.h>

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PuertaOr::PuertaOr(int n1, int x1, int y1) :
	Puerta(n1, x1, y1)
{
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PuertaOr::Dibujar(void)
{
	Puerta::Dibujar();
	if(n > 1)
	{
		/*~~~~~~~~~~~~~~~~*/
		int x = Patita[0].x;
		int y = Patita[0].y;
		int a, b, R;
		/*~~~~~~~~~~~~~~~~*/

		b = (n + 1) * 5 + y;
		R = (n + 1) * 10;
		a = x - sqrt(-b * b + 2 * b * y - y * y + R * R);

		// Arco Interior. El x+1, y x-1 (+1,-1) es solo para corregir un peque�o error
		FormR->Image1->Canvas->Arc(a - R, b - R, a + R, b + R, x + 1, R + y, x - 1, y);

		// Dibuja las patitas de entrada
		for(int i = 1; i <= n; i++)
		{
			/*~~~~~*/
			int d, e;
			/*~~~~~*/

			e = y + 10 * i;
			d = a + sqrt(-e * e + 2 * b * e - b * b + R * R);
			FormR->Image1->Canvas->MoveTo(x - 5, e);
			FormR->Image1->Canvas->LineTo(d, e);
			Patita[i + 1] = Punto(x - 5, e);
		}
	}
};
