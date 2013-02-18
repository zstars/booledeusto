/*$T boole/Circuito/FlipFlop.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "FlipFlop.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
FlipFlop::FlipFlop(int n1, int x1, int y1)
{
	n = n1;
	CLK = Punto(x1, y1);

	// J=Punto (x1,y1-15); K=Punto (x1,y1+15);
	Q = Punto("Q" + IntToStr(n), x1 + 70, y1 - 15);
	NQ = Punto("~Q" + IntToStr(n), x1 + 70, y1 + 15);
	RESET = Punto(x1 + 35, y1 + 35);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlop::Dibujar(void)
{
	FormR->Image1->Canvas->Rectangle(CLK.x + 10, CLK.y - 25, CLK.x + 60, CLK.y + 25);

	// se dibuja el triangulo del CLK en color azul.
	FormR->Image1->Canvas->Pen->Color = clNavy;
	FormR->Image1->Canvas->MoveTo(CLK.x, CLK.y);
	FormR->Image1->Canvas->LineTo(CLK.x + 10, CLK.y);
	FormR->Image1->Canvas->MoveTo(CLK.x + 10, CLK.y - 7);
	FormR->Image1->Canvas->LineTo(CLK.x + 25, CLK.y);
	FormR->Image1->Canvas->LineTo(CLK.x + 10, CLK.y + 7);
	FormR->Image1->Canvas->LineTo(CLK.x + 10, CLK.y);
	FormR->Image1->Canvas->Pen->Color = clBlack;

	// se dibuja el RESET en color rojo.
	FormR->Image1->Canvas->Pen->Color = clRed;
	FormR->Image1->Canvas->Ellipse(RESET.x - 3, RESET.y - 10, RESET.x + 3, RESET.y - 4);
	FormR->Image1->Canvas->MoveTo(RESET.x, RESET.y - 4);
	RESET.y += 10;
	FormR->Image1->Canvas->LineTo(RESET.x, RESET.y);
	FormR->Image1->Canvas->Pen->Color = clBlack;

	FormR->Image1->Canvas->MoveTo(Q.x, Q.y);
	FormR->Image1->Canvas->LineTo(Q.x - 10, Q.y);
	FormR->Image1->Canvas->TextOut(Q.x - 28, Q.y - 6, "Q" + (AnsiString) n);

	FormR->Image1->Canvas->MoveTo(NQ.x, NQ.y);
	FormR->Image1->Canvas->LineTo(NQ.x - 10, NQ.y);
	FormR->Image1->Canvas->TextOut(NQ.x - 28, NQ.y - 6, "Q" + (AnsiString) n);
	FormR->Image1->Canvas->MoveTo(NQ.x - 28, NQ.y - 6);
	FormR->Image1->Canvas->LineTo(NQ.x - 14, NQ.y - 6);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlop::UnirCLK(int x1, int y1)
{
	FormR->Image1->Canvas->Pen->Color = clNavy;
	FormR->Image1->Canvas->MoveTo(CLK.x, CLK.y);

	FormR->Image1->Canvas->Brush->Color = clNavy;
	FormR->Image1->Canvas->Ellipse(CLK.x - 20 - 2, CLK.y - 2, CLK.x - 20 + 3, CLK.y + 2);
	FormR->Image1->Canvas->Brush->Color = clWhite;	// Restauramos el color de Brush

	FormR->Image1->Canvas->LineTo(CLK.x - 20, CLK.y);
	FormR->Image1->Canvas->LineTo(CLK.x - 20, y1);
	FormR->Image1->Canvas->LineTo(x1 - 1, y1);
	FormR->Image1->Canvas->Pen->Color = clBlack;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlop::UnirRESET(int x1, int y1)
{
	FormR->Image1->Canvas->Pen->Color = clRed;
	FormR->Image1->Canvas->MoveTo(RESET.x, RESET.y);

	FormR->Image1->Canvas->Brush->Color = clRed;
	FormR->Image1->Canvas->Ellipse(CLK.x - 10 - 2, RESET.y - 2, CLK.x - 10 + 3, RESET.y + 2);
	FormR->Image1->Canvas->Brush->Color = clWhite;	// Restauramos el color de Brush

	FormR->Image1->Canvas->LineTo(CLK.x - 10, RESET.y);
	FormR->Image1->Canvas->LineTo(CLK.x - 10, y1);
	FormR->Image1->Canvas->LineTo(x1 - 1, y1);
	FormR->Image1->Canvas->Pen->Color = clBlack;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FlipFlop::UnirQ(int x1, int nJK, int k)
{
	FormR->Image1->Canvas->MoveTo(Q.x, Q.y);
	Q.x = Q.x + (k + 1) * 10;
	FormR->Image1->Canvas->LineTo(Q.x, Q.y);

	FormR->Image1->Canvas->Brush->Color = clBlack;
	FormR->Image1->Canvas->Ellipse(Q.x - 2, Q.y - 2, Q.x + 3, Q.y + 2);
	FormR->Image1->Canvas->Brush->Color = clWhite;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// Restauramos el color de Brush

	int y1 = 60 + (nJK - k - 1) * 10;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	FormR->Image1->Canvas->LineTo(Q.x, y1);
	FormR->Image1->Canvas->LineTo(x1, y1);

	FormR->Image1->Canvas->Brush->Color = clBlack;
	FormR->Image1->Canvas->Ellipse(x1 - 2, y1 - 2, x1 + 3, y1 + 2);
	FormR->Image1->Canvas->Brush->Color = clWhite;	// Restauramos el color de Brush
	Q.x = Q.x;
}
