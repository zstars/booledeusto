/*$T boole/Circuito/Entrada.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "Entrada.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
Entrada::Entrada(AnsiString n, int x1, int y1)
{
	nombre = n;
	x = x1;
	y = y1;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Entrada::Entrada(AnsiString n)
{
	nombre = n;
	x = 0;
	y = 0;
};

//
// =======================================================================================================================
//    con el parametro altura se desplaza la altura de la entrada hacia abajo para permitir dibujar las salidas que
//    vienen de los flip-flops en los sistemas secuenciales. En los sistemas combinacionales vale cero.
// =======================================================================================================================
//
void Entrada::Dibujar(int altura)
{
	y += 30;
	if(nombre == "CLK")
	{
		//
		// FormR->Image1->Canvas->Pen->Color = clBlue; FormR->Image1->Canvas->Font->Color
		// = clBlue;
		//
		FormR->Image1->Canvas->Pen->Color = clNavy;
		FormR->Image1->Canvas->Font->Color = clNavy;
		FormR->Image1->Canvas->TextOut(x - 2, y - 15, nombre);
		FormR->Image1->Canvas->MoveTo(x, y);
		FormR->Image1->Canvas->LineTo(x, y + altura + 50);
		y = y + altura + 50;
		FormR->Image1->Canvas->Pen->Color = clBlack;
		FormR->Image1->Canvas->Font->Color = clBlack;
	}
	else if(nombre == "RESET")
	{
		FormR->Image1->Canvas->Pen->Color = clRed;
		FormR->Image1->Canvas->Font->Color = clRed;

		// y-=20;
		FormR->Image1->Canvas->TextOut(x - 2, y - 15, nombre);
		FormR->Image1->Canvas->MoveTo(x, y);
		FormR->Image1->Canvas->LineTo(x, y + altura + 40);
		y = y + altura + 40;
		FormR->Image1->Canvas->Pen->Color = clBlack;
		FormR->Image1->Canvas->Font->Color = clBlack;
	}
	else
	{
		FormR->Image1->Canvas->TextOut(x - 2, y - 15, nombre);
		FormR->Image1->Canvas->MoveTo(x, y);
		FormR->Image1->Canvas->LineTo(x, y + altura + 50);
		y = y + altura + 50;
	}
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Entrada::DibujarNot(int altura)
{
	y += 30;
	y = y + altura; // se va a dibujar la entrada a partir de y+altura.
	FormR->Image1->Canvas->MoveTo(x - 20, y);
	FormR->Image1->Canvas->LineTo(x, y);

	FormR->Image1->Canvas->LineTo(x, y + 10);

	FormR->Image1->Canvas->MoveTo(x - 10, y + 10);
	FormR->Image1->Canvas->LineTo(x + 10, y + 10);

	FormR->Image1->Canvas->LineTo(x + 2, y + 27);

	FormR->Image1->Canvas->MoveTo(x - 10, y + 10);
	FormR->Image1->Canvas->LineTo(x - 2, y + 27);

	FormR->Image1->Canvas->Arc(x - 2, y + 26, x + 3, y + 31, x, y + 31, x, y + 31);

	FormR->Image1->Canvas->MoveTo(x, y + 31);
	FormR->Image1->Canvas->LineTo(x, y + 40);

	y = y + 40;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Entrada::Unir(int x1, int y1)
{
	FormR->Image1->Canvas->MoveTo(x, y);
	FormR->Image1->Canvas->LineTo(x, y1);
	FormR->Image1->Canvas->Brush->Color = clBlack;
	FormR->Image1->Canvas->Ellipse(x - 2, y1 - 2, x + 3, y1 + 2);
	FormR->Image1->Canvas->LineTo(x1, y1);
	FormR->Image1->Canvas->Brush->Color = clWhite;	// Restauramos el color de Brush
	x = x;
	y = y1;
};
