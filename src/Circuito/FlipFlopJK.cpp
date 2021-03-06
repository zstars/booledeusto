/*$T boole/Circuito/FlipFlopJK.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "FlipFlopJK.h"
#include "V_Circuito.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
FlipFlopJK::FlipFlopJK(int n1, int x1, int y1) :
	FlipFlop(n1, x1, y1)
{
	J = Punto(x1, y1 - 15);
	K = Punto(x1, y1 + 15);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlopJK::Dibujar(void)
{
	FlipFlop::Dibujar();

	FormR->Image1->Canvas->MoveTo(J.x, J.y);
	FormR->Image1->Canvas->LineTo(J.x + 10, J.y);
	FormR->Image1->Canvas->TextOut(J.x + 14, J.y - 6, "J" + (AnsiString) n);

	FormR->Image1->Canvas->MoveTo(K.x, K.y);
	FormR->Image1->Canvas->LineTo(K.x + 10, K.y);
	FormR->Image1->Canvas->TextOut(K.x + 14, K.y - 6, "K" + (AnsiString) n);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlopJK::UnirJ(int x1, int y1)
{
	FormR->Image1->Canvas->MoveTo(J.x, J.y);
	FormR->Image1->Canvas->LineTo(J.x, y1);
	FormR->Image1->Canvas->LineTo(x1 - 1, y1);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlopJK::UnirK(int x1, int y1)
{
	FormR->Image1->Canvas->MoveTo(K.x, K.y);
	FormR->Image1->Canvas->LineTo(K.x, y1);
	FormR->Image1->Canvas->LineTo(x1 - 1, y1);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlopJK::UnirCLK(int x1, int y1)
{
	FlipFlop::UnirCLK(x1, y1);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlopJK::UnirQ(int x1, int nJK, int k)
{
	FlipFlop::UnirQ(x1, nJK, k);
}
