/*$T boole/Circuito/Puerta.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "Puerta.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
Puerta::Puerta(int n1, int x1, int y1)
{
	n = n1;
	Patita = new Punto[n + 2];
	Patita[0] = Punto(x1, y1);
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Puerta::Dibujar(void)
{
	/*~~~~~~~~~~~~~~~~*/
	int x = Patita[0].x;
	int y = Patita[0].y;
	/*~~~~~~~~~~~~~~~~*/

	// Dibuja un arco dado un punto y un nº de entradas a la puerta
	if(n > 1)
	{
		FormR->Image1->Canvas->Arc(x - (n + 1) * 5, y, x + (n + 1) * 5, y + (n + 1) * 10, x, y + (n + 1) * 10, x, y);

		// Dibuja la patita de salida
		FormR->Image1->Canvas->MoveTo(x + (n + 1) * 5, y + (n + 1) * 5);
		FormR->Image1->Canvas->LineTo(x + (n + 1) * 5 + 10, y + (n + 1) * 5);
		Patita[1] = Punto(x + (n + 1) * 5 + 10, y + (n + 1) * 5);
	}
	else
	{
		Patita[2] = Punto(x - 5, y + 10);
		Patita[1] = Punto(x + 15, y + 10);
		FormR->Image1->Canvas->MoveTo(Patita[2].x, Patita[2].y);
		FormR->Image1->Canvas->LineTo(Patita[1].x, Patita[1].y);
	}
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Puerta::Unir(Punto *PS)
{
	for(double f = 0; f < (double) n / 2; f++)
	{
		/*~~~~~~~~~~~~*/
		int i = (int) f;
		/*~~~~~~~~~~~~*/

		FormR->Image1->Canvas->MoveTo(PS[i].x, PS[i].y);	// P1.x+(Patita[i+2].x-P1.x)/2
		FormR->Image1->Canvas->LineTo((Patita[i + 2].x - 10 * i), PS[i].y);
		FormR->Image1->Canvas->LineTo((Patita[i + 2].x - 10 * i), Patita[i + 2].y);
		FormR->Image1->Canvas->LineTo(Patita[i + 2].x, Patita[i + 2].y);

		FormR->Image1->Canvas->MoveTo(PS[n - i - 1].x, PS[n - i - 1].y);
		FormR->Image1->Canvas->LineTo((Patita[n - i + 1].x - 10 * i), PS[n - i - 1].y);
		FormR->Image1->Canvas->LineTo((Patita[n - i + 1].x - 10 * i), Patita[n - i + 1].y);
		FormR->Image1->Canvas->LineTo(Patita[n - i + 1].x, Patita[n - i + 1].y);
	}
}
