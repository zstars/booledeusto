/*$T boole/Boole2/SistemaSecuencial.cpp GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "SistemaSecuencial.h"
#include "V_Boole2.h"
#include "Unit2.h"
#include "Unit16.h"
#include "uLog.h"
#include "mensajes.inc"

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

#pragma package(smart_init)
int		grabaste = 1;
int		Radio = 25;

// Radio de los circulos
TColor	ObjSel = clRed;

// Color del Objeto Seleccionado
TColor	ObjMov = clBlue;

// Color del Objeto Moviendose
TColor	ColFon = clWhite;

// Color de Fondo
TColor	ColAct = clLtGray;

// Color de estado activado inicio modificado Ainara
int		conTabla = 0;
int		numpaso = 0;

bool	simulando = false;
int		simulacion = NO_SIMULANDO;

bool parpadeo = false;

SISTEMA Sistema;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool SISTEMA::AplicarEntrada(AnsiString &ent)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	FLECHA	f;
	bool	flechaEncontrada = false;
	int		i = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(!flechaEncontrada && i < GetNumFlechas())
	{
		f = DevolverFlecha(i);
		if(f.FlechaCirculoSale() == indiceActual && PuedeSeguir(ent, f.DevolverEtiqueta1()))
		{
			flechaEncontrada = true;
			indiceFlechaActual = i;
		}

		i++;
	}

  if (flechaEncontrada)
    entrada = ent;
  else
    entrada = "";

	
	return flechaEncontrada;
}

// Aplica un clock.
// Se supone que hay una entrada estable y valida.
void SISTEMA::Clk()
{
    indiceAnterior = indiceActual;
		indiceActual = getFlechaActual().FlechaCirculoEntra();
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::Resetear(void)
{
	// Volvemos al estado inicial
	indiceActual = indiceInicial;
  indiceAnterior = -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int ElevarBase2(int Exp)
{
	/*~~~~~~~~~~*/
	int Resul = 1;
	/*~~~~~~~~~~*/

	for(int i = 0; i < Exp; i++)
	{
		Resul = 2 * Resul;
	}

	return Resul;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString Dec2BinAcot(int Dec, int NumCar)
// convierte un decimal en binario NumCar es el numero de caracteres que tendra el binario
{
	/*~~~~~~~~~~~~~~~~~~~*/
	AnsiString	Binario, b;
	/*~~~~~~~~~~~~~~~~~~~*/

	Binario = "";

	/*~~~~~~*/
	int resto;
	/*~~~~~~*/

	resto = 0;
	for(int j = 0; j < NumCar; j++)
	{
		// calculamos el nuero en binario
		resto = Dec % 2;
		Dec = Dec / 2;
		Binario += resto;
	}

	// pero lo guarda al reves asi que lo doy la vuelta
	for(int j = 0; j < NumCar; j++)
	{
		b += "p";
	}

	// con lo cual que damos la vuelta a lo de lo cual
	for(int j = 1; j <= NumCar; j++)
	{
		b[j] = Binario[(NumCar + 1) - j];
	}

	return b;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PAR::setPrimero(int a)
{
	primero = a;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PAR::setSegundo(int b)
{
	segundo = b;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int PAR::getPrimero(void)
{
	return primero;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int PAR::getSegundo(void)
{
	return segundo;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CELDA::CELDA(void)
{
	ok = 1;
	util = 0;
	tachado = 0;
	numpares = -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CELDA::esOk(void)
{
	if(ok == 1)
		return 1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CELDA::setNoOk(void)
{
	ok = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CELDA::esUtil(void)
{
	if(util == 1)
		return 1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CELDA::setUtil(void)
{
	util = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CELDA::setNoUtil(void)
{
	util = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CELDA::esTachado(void)
{
	if(tachado == 1)
		return 1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CELDA::Tachar(void)
{
	tachado = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CELDA::obtenerPrimero(int i)
{
	return par[i].getPrimero();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CELDA::obtenerSegundo(int i)
{
	return par[i].getSegundo();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CELDA::AnyadirPar(int a, int b)
{
	numpares++;

	/*~~*/
	PAR p;
	/*~~*/

	p.setPrimero(a);
	p.setSegundo(b);
	par[numpares] = p;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CELDA::obtenerNumpares(void)
{
	return numpares;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SOLUCION::SOLUCION(void)
{
	numequivalentes = -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SOLUCION::AnyadirEquivalentes(int a, int b)
{
	numequivalentes++;

	/*~~*/
	PAR p;
	/*~~*/

	p.setPrimero(a);
	p.setSegundo(b);
	equivalentes[numequivalentes] = p;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SOLUCION::getNumeroEquivalentes(void)
{
	return numequivalentes;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SOLUCION::obtenerPrimerEq(int i)
{
	return equivalentes[i].getPrimero();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SOLUCION::obtenerSegundoEq(int i)
{
	return equivalentes[i].getSegundo();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString CIRCULO::DevolverEtiqueta1(void)
{
	return Etiqueta1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CIRCULO::ActualizarEtiqueta1(AnsiString a)
{
	Etiqueta1 = a;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString CIRCULO::DevolverEtiqueta2(void)
{
	return Etiqueta2;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CIRCULO::ActualizarEtiqueta2(AnsiString a)
{
	Etiqueta2 = a;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CIRCULO::ActualizarCoordenadasCirculo(int X, int Y)
// Actualiza las coordenadas X e Y del circulo
{
	CirculoX = X;
	CirculoY = Y;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CIRCULO::CoordenadaCirculoX(void)
// Devuelve la coordenada X del circulo
{
	return CirculoX;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CIRCULO::CoordenadaCirculoY(void)
// Devuelve la coordenada X del circulo
{
	return CirculoY;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString FLECHA::DevolverEtiqueta1(void)
{
	return Etiqueta1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString FLECHA::DevolverEtiqueta2(void)
{
	return Etiqueta2;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FLECHA::ActualizarEtiqueta1(AnsiString et1)
{
	Etiqueta1 = et1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FLECHA::ActualizarEtiqueta2(AnsiString et2)
{
	Etiqueta2 = et2;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FLECHA::ActualizarCirculoSale(int i)
// Pone el numero del circulo del que sale la flecha
{
	CirculoSale = i;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FLECHA::ActualizarCirculoEntra(int i)
// Pone el numero del circulo al que entra la flecha
{
	CirculoEntra = i;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int FLECHA::FlechaCirculoEntra(void)
// Devuelve el numero del circulo al que entra la flecha
{
	return CirculoEntra;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int FLECHA::FlechaCirculoSale(void)
// Devuelve el numero del circulo del que sale la flecha
{
	return CirculoSale;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FLECHA::ActualizarCoordenadasFlecha(int X, int Y)
// Actualiza las coordenadas X e Y de la flecha
{
	FlechaX = X;
	FlechaY = Y;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int FLECHA::CoordenadaFlechaX(void)
// Devuelve la coordenada X de la flecha
{
	return FlechaX;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int FLECHA::CoordenadaFlechaY(void)
// Devuelve la coordenada Y de la flecha
{
	return FlechaY;
};


bool Combinables(AnsiString &strA, AnsiString &strB)
{
                bool combinables = true;
                int peso = 0;

                for(int i = 1; i <= strA.Length() && combinables; i++)
                {
                        char a = strA[i];
                        char b = strB[i];

                        if ((a == 'X' && b != 'X') || (a != 'X' && b == 'X'))
                                combinables = false;
                        else if ((a == '1' && b == '0') || (a == '0' && b == '1'))
                        {
                                peso++;
                                if (peso > 1)
                                        combinables = false;
                        }
                }

                return combinables;
}

bool Iguales(AnsiString strA, AnsiString strB)
{
        bool entradasIguales = true;

        if (strA.Length() != strB.Length())
                return false;
        else
        {
                for(int i = 1; i <= strA.Length() && entradasIguales; i++)
                {
                        char a = strA[i];
                        char b = strB[i];

                        if ((a == '1' && b == '0') || (a == '0' && b == '1'))
                        	entradasIguales=false;
                }

		return entradasIguales;
        }

};


bool FLECHA::CombinableCon(FLECHA &f)
{
        AnsiString barrera1 = this->Etiqueta1;
        AnsiString barrera2 = f.Etiqueta1;

        if (barrera1.Length() != barrera2.Length())
                return false;
        else
        	return Combinables(barrera1, barrera2);

};

bool FLECHA::CombinarCon(FLECHA &f)
{
        bool combinado = false;

        for(int i = 1; i <= Etiqueta1.Length() && !combinado; i++)
        {
                char a = Etiqueta1[i];
                char b = f.Etiqueta1[i];
                if ((a == '1' && b == '0') || (a == '0' && b == '1'))
                {
                        combinado = true;
                        Etiqueta1[i] = 'X';
                }
        }
}

//
// =======================================================================================================================
//    CLASE SISTEMA
// =======================================================================================================================
//
void SISTEMA::ActualizarTipo(int t)
// Actualiza el tipo de diagrama (1=Mealy 0=Moore)
{
	if((t == 0) || (t == 1))
	{
		Tipo = t;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::DevolverTipo(void)
// Devuelve el tipo de diagrama (1=Mealy 0=Moore)
{
	return Tipo;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarNumCarEnt(int t)
// Actualizar el Numero de caracteres de la entrada del automata
{
	NumCarEnt = t;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::DevolverNumCarEnt(void)
// Devuelve el Numero de caracteres de la entrada del automata
{
	return NumCarEnt;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarNumCarSal(int t)
// Actualizar el Numero de caracteres de la salida del automata
{
	NumCarSal = t;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::DevolverNumCarSal(void)
// Devuelve el Numero de caracteres de la salida del automata
{
	return NumCarSal;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarEtiqueta1Circulo(int num, AnsiString a)
// Actualiza la etiqueta del circulo num desde la clase sistema
{
	circulo[num].ActualizarEtiqueta1(a);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarEtiqueta2Circulo(int num, AnsiString a)
// Actualiza la etiqueta del circulo num desde la clase sistema
{
	circulo[num].ActualizarEtiqueta2(a);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarEtiqueta1Flecha(int num, AnsiString a)
// Actualiza la etiqueta1 de la flecha num desde la clase sistema
{
	flecha[num].ActualizarEtiqueta1(a);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarEtiqueta2Flecha(int num, AnsiString a)
// Actualiza la etiqueta2 de la flecha num desde la clase sistema
{
	flecha[num].ActualizarEtiqueta2(a);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarFlecha(int n, int x, int y)
// Actualiza las coordenadas de la flecha n desde la clase sistema
{
	flecha[n].ActualizarCoordenadasFlecha(x, y);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarCirculo(int n, int x, int y)
// Actualiza las coordenadas del circulo n desde la clase sistema
{
	circulo[n].ActualizarCoordenadasCirculo(x, y);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarValorSale(int n, int i)
// Actualiza el numero de Circulo i del que sale la flecha n
{
	flecha[n].ActualizarCirculoSale(i);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarValorEntra(int n, int i)
// Actualiza el numero de Circulo i al que entra la flecha n
{
	flecha[n].ActualizarCirculoEntra(i);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::CirculoMoviendo(bool s)
// Quita o pone un circulo en movimiento
{
	circulomoviendose = s;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::FlechaMoviendo(bool s)
// Quita o pone un flecha en movimiento
{
	flechamoviendose = s;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool SISTEMA::EstaCirculoMoviendose(void)
// Nos informa si esta o no moviendose el circulo seleccionado
{
	return circulomoviendose;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool SISTEMA::EstaFlechaMoviendose(void)
// Nos informa si esta o no moviendose la flecha seleccionada
{
	return flechamoviendose;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::SeleccionarCirculo(int i)
// Selecciona un circulo y deselecciona una flecha
{
	CirculoMoviendo(false);
	circulosel = i;
	if(flechasel != -1)
	{
		flechasel = -1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::SeleccionarFlecha(int i)
// Selecciona una flecha y deselecciona un circulo
{
	FlechaMoviendo(false);
	flechasel = i;
	if(circulosel != -1)
	{
		circulosel = -1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CIRCULO SISTEMA::DevolverCirculo(int i)
// Devuelve las atributos del circulo i (solo sirve para consultar valores)
{
	return circulo[i];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLECHA SISTEMA::DevolverFlecha(int i)
// Devuelve los atributos de la flecha i (solo sirve para consultar valores)
{
	return flecha[i];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
double SISTEMA::Spline_CalcX(int ApX, int BpX, int CpX, int DpX, double T, double D)
// Calcula los puntos de X de la Spline
{
	/*~~~~~~~~~~~*/
	double	T2, T3;
	/*~~~~~~~~~~~*/

	T2 = T * T;		// t al cuadrado
	T3 = T2 * T;	// t al cubo
	return(((ApX * T3) + (BpX * T2) + (CpX * T) + DpX) / D);	// Calculo de la x
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
double SISTEMA::Spline_CalcY(int ApY, int BpY, int CpY, int DpY, double T, double D)
// Calcula los puntos de Y de la Spline
{
	/*~~~~~~~~~~~*/
	double	T2, T3;
	/*~~~~~~~~~~~*/

	T2 = T * T;
	T3 = T2 * T;
	return(((ApY * T3) + (BpY * T2) + (CpY * T) + DpY) / D);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::DibujaSentido(int x1, int y1, int x2, int y2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	float	d1, d2;
	double	alfa;
	double	theta;
	double	xf1, yf1, xf2, yf2;
	bool	Reverso;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	if(x2 < x1)
		Reverso = True;
	else
		Reverso = false;

	d1 = x2 - x1;
	if((d1 < 0.01) && (d1 > -0.01)) d1 = 0.5;
	d2 = y2 - y1;

	alfa = (180.0 / Pi) * atan(((double) d2) / ((double) d1));

	if(Reverso == false)
		theta = 20 + 180 + alfa;
	else
		theta = 20 + alfa;

	xf1 = x2 + cos(theta * Pi / 180) * 15;
	yf1 = y2 + sin(theta * Pi / 180) * 15;

	if(Reverso == false)
		theta = -20 + 180 + alfa;
	else
		theta = -20 + alfa;

	xf2 = x2 + cos(theta * Pi / 180) * 15;
	yf2 = y2 + sin(theta * Pi / 180) * 15;

	/*~~~~~~~~~~~~~~~~~~*/
	TBrushStyle Estilo;
	TPenStyle	EstiloPen;
	TColor		col;
	/*~~~~~~~~~~~~~~~~~~*/

	EstiloPen = Form1Boole2->Tablero->Canvas->Pen->Style;
	Estilo = Form1Boole2->Tablero->Canvas->Brush->Style;
	Form1Boole2->Tablero->Canvas->Pen->Style = psSolid;
	col = Form1Boole2->Tablero->Canvas->Brush->Color;
	Form1Boole2->Tablero->Canvas->Brush->Style = bsSolid;
	Form1Boole2->Tablero->Canvas->Brush->Color = Form1Boole2->Tablero->Canvas->Pen->Color;

	/*~~~~~~~~~~~~*/
	TPoint	ptos[3];
	/*~~~~~~~~~~~~*/

	ptos[0].x = x2;
	ptos[0].y = y2;
	ptos[1].x = xf1;
	ptos[1].y = yf1;
	ptos[2].x = xf2;
	ptos[2].y = yf2;
	Form1Boole2->Tablero->Canvas->Polygon(EXISTINGARRAY(ptos));

	Form1Boole2->Tablero->Canvas->Brush->Style = Estilo;
	Form1Boole2->Tablero->Canvas->Brush->Color = col;
	Form1Boole2->Tablero->Canvas->Pen->Style = EstiloPen;

	// Fin Flecha Form1Boole2->Tablero->Canvas->MoveTo(x2,y2);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::Spline(int x1, int y1, int x2, int y2, int x3, int y3)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	int		i, j;
	double	Xs, Ys, Lx, Ly;
	double	ApX, BpX, CpX, DpX;
	double	ApY, BpY, CpY, DpY;
	double	ax[6];
	double	ay[6];
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	ax[0] = x1;
	ax[1] = x1;
	ax[2] = x2;
	ax[3] = x3;
	ax[4] = x3;
	ax[5] = x3;

	ay[0] = y1;
	ay[1] = y1;
	ay[2] = y2;
	ay[3] = y3;
	ay[4] = y3;
	ay[5] = y3;

	Form1Boole2->Tablero->Canvas->MoveTo(x1, y1);
	for(i = 1; i <= 2; i++)
	{
		// Calcula coeficientes
		ApX = -ax[i - 1] + 3 * ax[i] - 3 * ax[i + 1] + ax[i + 2];
		BpX = 2 * ax[i - 1] - 5 * ax[i] + 4 * ax[i + 1] - ax[i + 2];
		CpX = -ax[i - 1] + ax[i + 1];
		DpX = 2 * ax[i];
		ApY = -ay[i - 1] + 3 * ay[i] - 3 * ay[i + 1] + ay[i + 2];
		BpY = 2 * ay[i - 1] - 5 * ay[i] + 4 * ay[i + 1] - ay[i + 2];
		CpY = -ay[i - 1] + ay[i + 1];
		DpY = 2 * ay[i];

		Lx = Spline_CalcX(ApX, BpX, CpX, DpX, 0, 2);
		Ly = Spline_CalcY(ApY, BpY, CpY, DpY, 0, 2);

		for(j = 1; j <= Resolution; j++)
		{
			Xs = Spline_CalcX(ApX, BpX, CpX, DpX, (double) j / Resolution, 2);
			Ys = Spline_CalcY(ApY, BpY, CpY, DpY, (double) j / Resolution, 2);

			Form1Boole2->Tablero->Canvas->LineTo(Xs, Ys);
			Lx = Xs;
			Ly = Ys;
			if((i == 1) && (j == Resolution - 1)) DibujaSentido(Lx, Ly, x2, y2);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::DibujarLazo(int num, int x, int y)
// Dibuja el bucle de un estado
{
	/*~~~~~~~~~~~~~~~~~~~*/
	int		xf, yf, xm, ym;
	double	xl, yl;
	double	angulo; // el angulo en que se empieza a dibujar el lazo
	//~~~~~~~~~~~~~~~~~~~

	xf = DevolverFlecha(num).CoordenadaFlechaX();
	yf = DevolverFlecha(num).CoordenadaFlechaY();
	xm = x + ((xf - x) / 2);
	ym = y + (yf - y) / 2;

	/*~~~~~~~~~~~*/
	// Calcular ptos del lazo
	int resol = 19;
	/*~~~~~~~~~~~*/

	Form1Boole2->Tablero->Canvas->MoveTo(xm + 40, ym);
	for(int i = 1; i <= resol; i++)
	{
		xl = (double) xm + cos((double) i * (resol - 1) * Pi / 180) * (40); // el 40 es la hipotenusa es decir el radio
																			///del lazo
		yl = (double) ym + sin((double) i * (resol - 1) * Pi / 180) * (40);
		Form1Boole2->Tablero->Canvas->LineTo(xl, yl);
	}

	Form1Boole2->Tablero->Canvas->LineTo(xm + 40, ym);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::RestauraSistema(void)
// Restaura la pantalla con la situacion actual del sistema
{
	// Rectangulo para borrar la pantalla Form1Boole2->Caption=grabaste;
	Form1Boole2->Tablero->Canvas->Brush->Style = bsSolid;
	Form1Boole2->Tablero->Canvas->Brush->Color = ColFon;
	Form1Boole2->Tablero->Canvas->Pen->Style = psSolid;
	Form1Boole2->Tablero->Canvas->Pen->Color = ColFon;
	Form1Boole2->Tablero->Canvas->Rectangle(0, 0, Form1Boole2->Tablero->Width, Form1Boole2->Tablero->Height);
	Form1Boole2->Tablero->Canvas->Brush->Style = bsClear;
	Form1Boole2->Tablero->Canvas->Pen->Color = clBlack;
	Form1Boole2->Tablero->Canvas->Pen->Width = 1;

	// Bucle para dibujar todas las flechas del Sistema
	for(int i = 0; i < NumFlechas(); i++)
	{
		if(flechasel != i || simulando)
		{
			Form1Boole2->Tablero->Canvas->Pen->Color = clBlack;
			Form1Boole2->Tablero->Canvas->Pen->Style = psSolid;
		}
		else
		{
			Form1Boole2->Tablero->Canvas->Pen->Color = ObjSel;
			if(flechamoviendose == true)
			{
				Form1Boole2->Tablero->Canvas->Pen->Color = ObjMov;	// clBlue;
			}

			Form1Boole2->Tablero->Canvas->Pen->Style = psDashDotDot;
		}

		if(simulando && indiceFlechaActual == i && simulacion != BATCH_PARADO)
		{
			Form1Boole2->Tablero->Canvas->Pen->Color = clRed;
			Form1Boole2->Tablero->Canvas->Pen->Width = 2;
		}
		else
		{
			Form1Boole2->Tablero->Canvas->Pen->Color = clBlack;
			Form1Boole2->Tablero->Canvas->Pen->Width = 1;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int EntraX, EntraY, SaleX, SaleY, PuntoX, PuntoY;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		EntraX = DevolverCirculo(DevolverFlecha(i).FlechaCirculoEntra()).CoordenadaCirculoX();
		EntraY = DevolverCirculo(DevolverFlecha(i).FlechaCirculoEntra()).CoordenadaCirculoY();
		SaleX = DevolverCirculo(DevolverFlecha(i).FlechaCirculoSale()).CoordenadaCirculoX();
		SaleY = DevolverCirculo(DevolverFlecha(i).FlechaCirculoSale()).CoordenadaCirculoY();
		Form1Boole2->Tablero->Canvas->Brush->Style = bsSolid;
		Form1Boole2->Tablero->Canvas->Brush->Color = ColFon;
		Form1Boole2->Tablero->Canvas->Brush->Style = bsSolid;

		if(DevolverFlecha(i).FlechaCirculoEntra() == DevolverFlecha(i).FlechaCirculoSale())
		{
			DibujarLazo(i, EntraX, EntraY);

			// El cuadradito del lazo
			PuntoX = DevolverFlecha(i).CoordenadaFlechaX();
			PuntoY = DevolverFlecha(i).CoordenadaFlechaY();
			Form1Boole2->Tablero->Canvas->Rectangle(PuntoX - 3, PuntoY - 3, PuntoX + 3, PuntoY + 3);
		}
		else
		{
			Spline
			(
				SaleX,
				SaleY,
				DevolverFlecha(i).CoordenadaFlechaX(),
				DevolverFlecha(i).CoordenadaFlechaY(),
				EntraX,
				EntraY
			);
		}

		// Poner etiqueta en flecha
		if(Tipo == 0)
		{
			Form1Boole2->Tablero->Canvas->TextOut
				(
					DevolverFlecha(i).CoordenadaFlechaX() - (DevolverNumCarEnt() * 3),
					DevolverFlecha(i).CoordenadaFlechaY() - 20,
					DevolverFlecha(i).DevolverEtiqueta1()
				);
		}
		else
		{
			if(DevolverFlecha(i).DevolverEtiqueta1() != "")
			{
				Form1Boole2->Tablero->Canvas->TextOut
					(
						DevolverFlecha(i).CoordenadaFlechaX() - (DevolverNumCarEnt() * 7),
						DevolverFlecha(i).CoordenadaFlechaY() - 20,
						DevolverFlecha(i).DevolverEtiqueta1()
					);
				Form1Boole2->Tablero->Canvas->TextOut
					(
						DevolverFlecha(i).CoordenadaFlechaX(),
						DevolverFlecha(i).CoordenadaFlechaY() - 20,
						"/"
					);
				Form1Boole2->Tablero->Canvas->TextOut
					(
						DevolverFlecha(i).CoordenadaFlechaX() + 7,
						DevolverFlecha(i).CoordenadaFlechaY() - 20,
						DevolverFlecha(i).DevolverEtiqueta2()
					);
			}
		}
	}

	// Bucle para situar todos los circulos del sistema
	for(int i = 0; i < NumCirculos(); i++)
	{
		if(circulosel != i || simulando)
		{
			Form1Boole2->Tablero->Canvas->Pen->Color = clBlack;
			Form1Boole2->Tablero->Canvas->Pen->Style = psSolid;
			if(simulando && i == indiceInicial)
				Form1Boole2->Tablero->Canvas->Pen->Width = 3;
			else
				Form1Boole2->Tablero->Canvas->Pen->Width = 1;
		}
		else
		{
			Form1Boole2->Tablero->Canvas->Pen->Color = ObjSel;
			if(circulomoviendose == true)
			{
				Form1Boole2->Tablero->Canvas->Pen->Color = ObjMov;
			}

			Form1Boole2->Tablero->Canvas->Pen->Style = psDashDotDot;
		}

		Form1Boole2->Tablero->Canvas->Brush->Style = bsSolid;
		if(simulando && i == indiceActual && simulacion != BATCH_PARADO)
      if (indiceActual == indiceAnterior && parpadeo)
  			Form1Boole2->Tablero->Canvas->Brush->Color = ColFon;
      else
  			Form1Boole2->Tablero->Canvas->Brush->Color = ColAct;
		else
			Form1Boole2->Tablero->Canvas->Brush->Color = ColFon;

		// Dibujar el circulo
		Form1Boole2->Tablero->Canvas->Ellipse
			(
				DevolverCirculo(i).CoordenadaCirculoX() - Radio,
				DevolverCirculo(i).CoordenadaCirculoY() - Radio,
				DevolverCirculo(i).CoordenadaCirculoX() + Radio,
				DevolverCirculo(i).CoordenadaCirculoY() + Radio
			);

		// Dibujar la etiqueta Poner la etiqueta en el circulo
		Form1Boole2->Tablero->Canvas->Brush->Style = bsClear;

		/*~~~~~~~~~~~~~~~~~*/
		AnsiString	Etiqueta;
		/*~~~~~~~~~~~~~~~~~*/

		Etiqueta = DevolverCirculo(i).DevolverEtiqueta1();

		//
		// compruebo si la etique ta es del standar es decir E Numero y si el del estandar
		// el numero que le pongo sera el de su estado
		//
		/*if(Etiqueta.SubString(1, 4) == "E")
		{

			//
			// estos dos if son para que al rellenar circulos con la etiqueta standar no crea
			// que la ha rellenado el usuario
			//
			int gr;


			if(grabaste == 1) gr = grabaste;
			Etiqueta = "E";
			Etiqueta += i;
			ActualizarEtiqueta1Circulo(i, Etiqueta);
			if(gr == 1) grabaste = gr;
		}*/

		Form1Boole2->Tablero->Canvas->TextOut
			(
				DevolverCirculo(i).CoordenadaCirculoX() - 18,
				DevolverCirculo(i).CoordenadaCirculoY() - 20,
				Etiqueta
			);

		// Poner la etiqueta en el circulo
		if(Tipo == MOORE && DevolverCirculo(i).DevolverEtiqueta2() != "")
		{
			Form1Boole2->Tablero->Canvas->TextOut
				(
					DevolverCirculo(i).CoordenadaCirculoX() - (DevolverNumCarSal() * 3),
					DevolverCirculo(i).CoordenadaCirculoY(),
					DevolverCirculo(i).DevolverEtiqueta2()
				);

			// linea de separacion entre las dos etiquetas
			Form1Boole2->Tablero->Canvas->MoveTo
				(
					DevolverCirculo(i).CoordenadaCirculoX() - 15,
					DevolverCirculo(i).CoordenadaCirculoY() - 5
				);
			Form1Boole2->Tablero->Canvas->LineTo
				(
					DevolverCirculo(i).CoordenadaCirculoX() + 15,
					DevolverCirculo(i).CoordenadaCirculoY() - 5
				);
		}
	}

	Form1Boole2->Tablero->Canvas->Refresh();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::BorrarFlecha(void)
// Elimina una flecha
{
	// reordenamos el array
	for(int p = flechasel; p < numflechas; p++)
	{
		flecha[p] = flecha[p + 1];
	}

	numflechas--;
	SeleccionarFlecha(-1);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::BorrarCirculo(void)
// Elimina un circulo y las flechas asociadas a el
{
	// reordenamos el array
	for(int p = circulosel; p < numcirculos; p++)
	{
		circulo[p] = circulo[p + 1];
	}

	/*~~~~~~*/
	// eliminamos todas las flechas que pertenecian a ese circulo
	int i;
	int final;
	/*~~~~~~*/

	final = numflechas;
	i = 0;
	while(i < final)
	{
		if
		(
			(DevolverFlecha(i).FlechaCirculoEntra() == circulosel)
		||	(DevolverFlecha(i).FlechaCirculoSale() == circulosel)
		)
		{
			for(int j = i; j < numflechas; j++)
			{
				flecha[j] = flecha[j + 1];
			}

			final--;
			i--;
		}

		i++;
	}

	numflechas = final;

	/*~~~~*/
	//
	// recorro todas las flechas para indicar correctamente los circulos a los que van
	// ya que al reordenar el array los circulos cambian de nombre
	//
	int aux;
	/*~~~~*/

	for(int p2 = 0; p2 < numflechas; p2++)
	{
		/*~~~~~~*/
		int sale;
		int entra;
		/*~~~~~~*/

		entra = DevolverFlecha(p2).FlechaCirculoEntra();
		sale = DevolverFlecha(p2).FlechaCirculoSale();
		if((entra) > circulosel)
		{
			aux = entra;
			DevolverFlecha(p2).ActualizarCirculoEntra(aux - 1);
			ActualizarValorEntra(p2, aux - 1);
		}

		if((sale) > circulosel)
		{
			aux = sale;
			DevolverFlecha(p2).ActualizarCirculoSale(aux - 1);
			ActualizarValorSale(p2, aux - 1);
		}
	}

	numcirculos--;
	SeleccionarCirculo(-1);
	CirculoMoviendo(false);
	grabaste = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::MoverCirculo(void)
// Mueve un circulo a la par que el raton
{
	for(int i = 0; i < numflechas; i++)
	{
		if
		(
			(DevolverFlecha(i).FlechaCirculoSale() == DevolverFlecha(i).FlechaCirculoEntra())
		&&	(DevolverFlecha(i).FlechaCirculoSale() == circulosel)
		)
		{
			/*~~~~~~~~~~~~~*/
			int xf, yf;
			int xc, yc, x, y;
			/*~~~~~~~~~~~~~*/

			xf = DevolverFlecha(i).CoordenadaFlechaX();
			yf = DevolverFlecha(i).CoordenadaFlechaY();

			xc = circulo[circulosel].CoordenadaCirculoX();
			yc = circulo[circulosel].CoordenadaCirculoY();
			x = RatonX + xf - xc;
			y = RatonY + yf - yc;
			ActualizarFlecha(i, x, y);
		}
	}

	for(int i = 0; i < numflechas; i++)
	{
		if
		(
			(DevolverFlecha(i).FlechaCirculoSale() != DevolverFlecha(i).FlechaCirculoEntra())
		&&	(
				(DevolverFlecha(i).FlechaCirculoSale() == circulosel)
			||	(DevolverFlecha(i).FlechaCirculoEntra() == circulosel)
			)
		)
		{
			/*~~~~~~~~~~~~~*/
			int xf, yf;
			int xc, yc, x, y;
			/*~~~~~~~~~~~~~*/

			xf = DevolverFlecha(i).CoordenadaFlechaX();
			yf = DevolverFlecha(i).CoordenadaFlechaY();
			xc = circulo[circulosel].CoordenadaCirculoX();
			yc = circulo[circulosel].CoordenadaCirculoY();
			if
			(
				(xc != Radio)
			&&	(yc != Radio)
			&&	(xc != Form1Boole2->Tablero->Width - Radio)
			&&	(yc != Form1Boole2->Tablero->Height - Radio)
			)
			{
				ActualizarFlecha(i, xf + ((RatonX - xc) / 2), yf + ((RatonY - yc) / 2));
			}
		}
	}

	circulo[circulosel].ActualizarCoordenadasCirculo(RatonX, RatonY);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::MoverFlecha(void)
// Mueve una flecha a la par que el raton
{
	/*~~~~~~~~~~~*/
	double	angulo;
	/*~~~~~~~~~~~*/

	// si es un lazo
	if(DevolverFlecha(flechasel).FlechaCirculoSale() == DevolverFlecha(flechasel).FlechaCirculoEntra())
	{
		angulo = RatonX % 360;

		/*~~~~~*/
		int x, y;
		/*~~~~~*/

		x = DevolverCirculo(DevolverFlecha(flechasel).FlechaCirculoSale()).CoordenadaCirculoX() +
			cos(angulo * Pi / 180) *
			80;

		// 80 es el diametro del lazo
		y = DevolverCirculo(DevolverFlecha(flechasel).FlechaCirculoSale()).CoordenadaCirculoY() +
			sin(angulo * Pi / 180) *
			80;
		ActualizarFlecha(flechasel, x, y);
	}

	// si no es un lazo
	else
	{
		ActualizarFlecha(flechasel, RatonX, RatonY);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::CirculoSeleccionado(void)
// Devuelve el circulo actualmente seleccionado
{
	return circulosel;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::FlechaSeleccionada(void)
// Devuelve el circulo actualmente seleccionado
{
	return flechasel;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarRaton(int X, int Y)
// Actualiza las coordenadas del raton en el sistema
{
	RatonX = X;
	RatonY = Y;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::InicializarCirculo(void)
// Inicializa un nuevo circulo
{
	if(numcirculos < MaxCir)
	{
		/*~~~~~~~~~~~*/
		AnsiString	et;
		/*~~~~~~~~~~~*/

		et = "Q";
		et += numcirculos;
		circulo[numcirculos].ActualizarCoordenadasCirculo(RatonX, RatonY);
		ActualizarEtiqueta1Circulo(numcirculos, et);
		ActualizarEtiqueta2Circulo(numcirculos, "");
		numcirculos++;
		SeleccionarCirculo(numcirculos - 1);
		grabaste = 0;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::RatonEncimaCirculo(void)
// Comprueba si el raton esta encima de un circulo devuelve el numero del circulo o -1
{
	/*~~~~~~~~*/
	int c, x, y;
	/*~~~~~~~~*/

	for(c = 0; c < numcirculos; c++)
	{
		x = circulo[c].CoordenadaCirculoX();
		y = circulo[c].CoordenadaCirculoY();
		if((RatonX > x - Radio && RatonX < x + Radio) && (RatonY > y - Radio && RatonY < y + Radio))
		{
			return c;
		}
	}

	return -1;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::RatonEncimaFlecha(void)
// Comprueba si el raton esta encima del cuadrado de una flecha y devuelve el numero de la flecha o -1
{
	/*~~~~~~~~*/
	int c, x, y;
	/*~~~~~~~~*/

	for(c = 0; c < numflechas; c++)
	{
		x = flecha[c].CoordenadaFlechaX();
		y = flecha[c].CoordenadaFlechaY();
		if((RatonX > x - 15 && RatonX < x + 15) && (RatonY > y - 10 && RatonY < y + 10))
		{
			return c;
		}
	}

	return -1;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::NumCirculos(void)
// Devuelve el numero de circulos en el sistema
{
	return numcirculos;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::NumFlechas(void)
// Devuelve el numero de flechas en el sistema
{
	return numflechas;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarNumCirculos(int a)
// Pone el numero de circulos en el sistema
{
	numcirculos = a;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ActualizarNumFlechas(int a)
// Pone el numero de flechas en el sistema
{
	numflechas = a;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::InicializarFlecha(void)
// Inicializa una nueva flecha
{
	if(numflechas < MaxFle)
	{
		if(flecha[numflechas].FlechaCirculoEntra() == -1)
		{
			/*~~~~~~~*/
			int xe, ye;
			int xs, ys;
			int xf, yf;
			/*~~~~~~~*/

			flecha[numflechas].ActualizarCirculoEntra(circulosel);
			xe = DevolverCirculo(flecha[numflechas].FlechaCirculoEntra()).CoordenadaCirculoX();
			ye = DevolverCirculo(flecha[numflechas].FlechaCirculoEntra()).CoordenadaCirculoY();
			xs = DevolverCirculo(flecha[numflechas].FlechaCirculoSale()).CoordenadaCirculoX();
			ys = DevolverCirculo(flecha[numflechas].FlechaCirculoSale()).CoordenadaCirculoY();
			if(xe < xs)
			{
				xf = xe;
			}
			else
			{
				xf = xs;
			}

			if(ye < ys)
			{
				yf = ye;
			}
			else
			{
				yf = ys;
			}

			if(flecha[numflechas].FlechaCirculoEntra() == flecha[numflechas].FlechaCirculoSale())
			// si es un lazo
			{
				flecha[numflechas].ActualizarCoordenadasFlecha(xe + 80, ye);
			}

			// si no es lazo
			else
			{
				flecha[numflechas].ActualizarCoordenadasFlecha(xf + abs(xe - xs) / 2, yf + abs(ye - ys) / 2);
			}

			SeleccionarFlecha(numflechas);
			FlechaMoviendo(true);
			ActualizarEtiqueta1Flecha(numflechas, "");
			ActualizarEtiqueta2Flecha(numflechas, "");
			numflechas++;

			Form2->BotonPuntero->Enabled = true;
			Form2->BotonCirculo->Enabled = true;
		}
		else
		{
			flecha[numflechas].ActualizarCirculoSale(circulosel);
			flecha[numflechas].ActualizarCirculoEntra(-1);

			// Si empezamos a poner una flecha hay que terminar de ponerla
			Form2->BotonPuntero->Enabled = false;
			Form2->BotonCirculo->Enabled = false;
			grabaste = 0;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool SISTEMA::RatonCercaAlgo(int Margen)
// Nos informa si el raton esta cerca de algun cuadrado o circulo
{
	/*~~~~~~~~*/
	int c, x, y;
	/*~~~~~~~~*/

	for(c = 0; c < numcirculos; c++)
	{
		if(c != circulosel)
		{
			x = circulo[c].CoordenadaCirculoX();
			y = circulo[c].CoordenadaCirculoY();
			if((RatonX > x - Margen && RatonX < x + Margen) && (RatonY > y - Margen && RatonY < y + Margen))
			{
				return true;
			}
		}
	}

	for(c = 0; c < numflechas; c++)
	{
		x = flecha[c].CoordenadaFlechaX();
		y = flecha[c].CoordenadaFlechaY();
		if((RatonX > x - Margen && RatonX < x + Margen) && (RatonY > y - Margen && RatonY < y + Margen))
		{
			return true;
		}
	}

	return false;
}

//
// =======================================================================================================================
//    inicio modificado Ainara
// =======================================================================================================================
//
void SISTEMA::crearTablaImplicacion(void)
{
	for(int i = 0; i < numcirculos; i++)	// tiene que haber num nodos -1
		for(int j = i + 1; j < numcirculos; j++)
		{
			/*~~~~~~~~~*/
			CELDA	cell;
			/*~~~~~~~~~*/

			cell.setUtil();
			celda[i][j] = cell;
		}

	if(conTabla == 1)
	{
		Form16->Grid1->Visible = true;
		Form16->Grid1->RowCount = numcirculos;
		Form16->Grid1->ColCount = numcirculos;

		for(int h = 0; h < numcirculos - 1; h++)
		{
			Form16->Grid1->Cells[h + 1][0] = circulo[h].DevolverEtiqueta1();
			for(int g = h + 1; g < numcirculos; g++) Form16->Grid1->Cells[0][g] = circulo[g].DevolverEtiqueta1();
			for(int f = 0; f < h; f++)
			{
				Form16->Grid1->Cells[h + 1][f + 1] = "xxxxxx";
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::particionDeSalida(void)
{
        if(Tipo==MEALY)
        {
        	for(int i = 0; i < numflechas; i++)
        	{
        		/*~~~~~~~~~~~~~~~~~~~~~~~*/
        		AnsiString	in1, out1;
        		int			ndsal1, ndent1;
        		/*~~~~~~~~~~~~~~~~~~~~~~~*/

        		in1 = flecha[i].DevolverEtiqueta1();
        		out1 = flecha[i].DevolverEtiqueta2();
        		ndsal1 = flecha[i].FlechaCirculoSale();
        		ndent1 = flecha[i].FlechaCirculoEntra();

        		for(int j = i + 1; j < numflechas; j++)
        		{
        			/*~~~~~~~~~~~~~~~~~~~~~~~*/
        			AnsiString	in2, out2;
        			int			ndsal2, ndent2;
        			/*~~~~~~~~~~~~~~~~~~~~~~~*/

	        		in2 = flecha[j].DevolverEtiqueta1();
        			out2 = flecha[j].DevolverEtiqueta2();
               			ndsal2 = flecha[j].FlechaCirculoSale();
        			ndent2 = flecha[j].FlechaCirculoEntra();
        			if
        			(
        				((ndsal1 < ndsal2) && (celda[ndsal1][ndsal2].esTachado() == 0))
        			||	((ndsal2 < ndsal1) && (celda[ndsal2][ndsal1].esTachado() == 0))
        			)
        			{
        				if(Iguales(in1,in2) && !Iguales(out1,out2)) // entradas iguales
        				{
        					if(ndsal1 < ndsal2)
        					{
        						celda[ndsal1][ndsal2].Tachar();
        						celda[ndsal1][ndsal2].setNoOk();
        						if(conTabla == 1)
        							Form16->Grid1->Cells[ndsal1 + 1][ndsal2] = Form16->Grid1->Cells[ndsal1 + 1][ndsal2] + "---";
        					}
        					else
        					{
        						celda[ndsal2][ndsal1].Tachar(); // cuidado con el orden i-j <> j-i!!!
        						celda[ndsal2][ndsal1].setNoOk();
        						if(conTabla == 1) Form16->Grid1->Cells[ndsal2 + 1][ndsal1] = "---";
        					}
        				}
        			}
        		}
        	}
        }
        else if (Tipo==MOORE)
        {
                for(int i = 0; i < numcirculos; i++)
        	{
        		/*~~~~~~~~~~~~~~~~~~~~~~~*/
        		AnsiString	salida1;
        		/*~~~~~~~~~~~~~~~~~~~~~~~*/

        		salida1 = circulo[i].DevolverEtiqueta2();

        		for(int j = i + 1; j < numcirculos; j++)
        		{
        			/*~~~~~~~~~~~~~~~~~~~~~~~*/
        			AnsiString	salida2;
        			/*~~~~~~~~~~~~~~~~~~~~~~~*/

        			salida2 = circulo[j].DevolverEtiqueta2();

        			if
        			(
        				((i < j) && (celda[i][j].esTachado() == 0))
        			||	((j < i) && (celda[j][i].esTachado() == 0))
        			)
        			{
        				if(!Iguales(salida1,salida2)) // entradas iguales
        				{
        					if(i < j)
        					{
        						celda[i][j].Tachar();
        						celda[i][j].setNoOk();
        						if(conTabla == 1)
        							Form16->Grid1->Cells[i + 1][j] = Form16->Grid1->Cells[i + 1][j] + "---";
        					}
        					else
        					{
        						celda[j][i].Tachar(); // cuidado con el orden i-j <> j-i!!!
        						celda[j][i].setNoOk();
        						if(conTabla == 1) Form16->Grid1->Cells[j + 1][i] = "---";
        					}
        				}
        			}
                        }
                }
        }
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::paresImplicados(void)
{

	for(int i = 0; i < numflechas; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	in1, out1;
		int			ndsal1, ndent1;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		ndsal1 = flecha[i].FlechaCirculoSale();
		ndent1 = flecha[i].FlechaCirculoEntra();
		in1 = flecha[i].DevolverEtiqueta1();
                if(Tipo == MEALY)
			out1 = flecha[i].DevolverEtiqueta2();
        	else if (Tipo==MOORE)
			out1 = circulo[ndsal1].DevolverEtiqueta2();

		for(int j = i + 1; j < numflechas; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	in2, out2;
			int			ndsal2, ndent2;


			ndsal2 = flecha[j].FlechaCirculoSale();
			ndent2 = flecha[j].FlechaCirculoEntra();
			in2 = flecha[j].DevolverEtiqueta1();
                        if(Tipo == MEALY)
				out2 = flecha[j].DevolverEtiqueta2();
                        else if (Tipo==MOORE)
				out2 = circulo[ndsal2].DevolverEtiqueta2();
			if
			(
				((ndsal1 < ndsal2) && (celda[ndsal1][ndsal2].esTachado() == 0))
			||	((ndsal2 < ndsal1) && (celda[ndsal2][ndsal1].esTachado() == 0))
			)
			{
				if
				(
                                         (Iguales(in1,in2) && Iguales(out1,out2) )
				&&	(
						!(((ndsal1 == ndent1) && (ndsal2 == ndent2))
						||	((ndsal1 == ndent2) && (ndsal2 == ndent1))
						||	(ndent1 == ndent2)
						)
					)
				)
				{
					if(ndsal1 < ndsal2)
					{
						if(ndent1 < ndent2)
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							int alright = 1;
							int nn = celda[ndsal1][ndsal2].obtenerNumpares();
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							for(int a = 0; a <= nn; a++)
							{
								if
								(
									(celda[ndsal1][ndsal2].obtenerPrimero(a) == ndent1)
								&&	(celda[ndsal1][ndsal2].obtenerSegundo(a) == ndent2)
								) alright = 0;
							}

							if(alright == 1)
							{
								celda[ndsal1][ndsal2].AnyadirPar(ndent1, ndent2);
								celda[ndsal1][ndsal2].setNoOk();
								if(conTabla == 1)
								{
									Form16->Grid1->Cells[ndsal1 + 1][ndsal2] = Form16->Grid1->Cells[ndsal1 + 1][
											ndsal2] +
										circulo[ndent1].DevolverEtiqueta1() +
										"-" +
										circulo[ndent2].DevolverEtiqueta1() +
										" ";
								}
							}
						}
						else
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							int alright = 1;
							int nn = celda[ndsal1][ndsal2].obtenerNumpares();
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							for(int a = 0; a <= nn; a++)
							{
								if
								(
									(celda[ndsal1][ndsal2].obtenerPrimero(a) == ndent2)
								&&	(celda[ndsal1][ndsal2].obtenerSegundo(a) == ndent1)
								) alright = 0;
							}

							if(alright == 1)
							{
								celda[ndsal1][ndsal2].AnyadirPar(ndent2, ndent1);
								celda[ndsal1][ndsal2].setNoOk();
								if(conTabla == 1)
								{
									Form16->Grid1->Cells[ndsal1 + 1][ndsal2] = Form16->Grid1->Cells[ndsal1 + 1][
											ndsal2] +
										circulo[ndent2].DevolverEtiqueta1() +
										"-" +
										circulo[ndent1].DevolverEtiqueta1() +
										" ";
								}
							}
						}
					}
					else
					{
						if(ndent1 < ndent2)
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							int alright = 1;
							int nn = celda[ndsal1][ndsal2].obtenerNumpares();
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							for(int a = 0; a <= nn; a++)
							{
								if
								(
									(celda[ndsal1][ndsal2].obtenerPrimero(a) == ndent1)
								&&	(celda[ndsal1][ndsal2].obtenerSegundo(a) == ndent2)
								) alright = 0;
							}

							if(alright == 1)
							{
								celda[ndsal2][ndsal1].AnyadirPar(ndent1, ndent2);
								celda[ndsal2][ndsal1].setNoOk();
								if(conTabla == 1)
								{
									Form16->Grid1->Cells[ndsal2 + 1][ndsal1] = Form16->Grid1->Cells[ndsal2 + 1][
											ndsal1] +
										circulo[ndent1].DevolverEtiqueta1() +
										"-" +
										circulo[ndent2].DevolverEtiqueta1() +
										" ";
								}
							}
						}
						else
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							int alright = 1;
							int nn = celda[ndsal1][ndsal2].obtenerNumpares();
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							for(int a = 0; a <= nn; a++)
							{
								if
								(
									(celda[ndsal1][ndsal2].obtenerPrimero(a) == ndent1)
								&&	(celda[ndsal1][ndsal2].obtenerSegundo(a) == ndent2)
								) alright = 0;
							}

							if(alright == 1)
							{
								celda[ndsal2][ndsal1].AnyadirPar(ndent2, ndent1);
								celda[ndsal2][ndsal1].setNoOk();
								if(conTabla == 1)
								{
									Form16->Grid1->Cells[ndsal2 + 1][ndsal1] = Form16->Grid1->Cells[ndsal2 + 1][
											ndsal1] +
										circulo[ndent2].DevolverEtiqueta1() +
										"-" +
										circulo[ndent1].DevolverEtiqueta1() +
										" ";
								}
							}
						}
					}
				}
			}
		}
	/*
        else if (Tipo==MOORE)
        {
                for(int i = 0; i < numcirculos; i++)
        	{

        		AnsiString	salida1;


        		salida1 = circulo[i].DevolverEtiqueta2();

        		for(int j = i + 1; j < numcirculos; j++)
        		{
        			AnsiString	salida2;

        			salida2 = circulo[j].DevolverEtiqueta2();

			if
			(
				((i < j) && (celda[i][j].esTachado() == 0))
			||	((j < i) && (celda[j][i].esTachado() == 0))
			)
			{
				if(Iguales(salida1,salida2))
				{
					if(i < j)
					{
							int alright = 1;
							int nn = celda[i][j].obtenerNumpares();

							for(int a = 0; a <= nn; a++)
							{
								if
								(
									(celda[i][j].obtenerPrimero(a) == ndent1)
								&&	(celda[i][j].obtenerSegundo(a) == ndent2)
								) alright = 0;
							}

							if(alright == 1)
							{
								celda[i][j].AnyadirPar(ndent1, ndent2);
								celda[i][j].setNoOk();
								if(conTabla == 1)
								{
									Form16->Grid1->Cells[i + 1][j] = Form16->Grid1->Cells[i + 1][j] +
										circulo[ndent1].DevolverEtiqueta1() +
										"-" +
										circulo[ndent2].DevolverEtiqueta1() +
										" ";
								}
							}

					}
					else if(j < i)
					{
							int alright = 1;
							int nn = celda[ndsal1][ndsal2].obtenerNumpares();

							for(int a = 0; a <= nn; a++)
							{
								if
								(
									(celda[ndsal1][ndsal2].obtenerPrimero(a) == ndent1)
								&&	(celda[ndsal1][ndsal2].obtenerSegundo(a) == ndent2)
								) alright = 0;
							}

							if(alright == 1)
							{
								celda[ndsal2][ndsal1].AnyadirPar(ndent2, ndent1);
								celda[ndsal2][ndsal1].setNoOk();
								if(conTabla == 1)
								{
									Form16->Grid1->Cells[ndsal2 + 1][ndsal1] = Form16->Grid1->Cells[ndsal2 + 1][
											ndsal1] +
										circulo[ndent2].DevolverEtiqueta1() +
										"-" +
										circulo[ndent1].DevolverEtiqueta1() +
										" ";
								}
							}

					}
				}

        }     */
        }
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::tablaTerminada(void)
{
	/*~~~~*/
	int mod;
	/*~~~~*/

	do
	{
		mod = 0;
		for(int i = 0; i < numcirculos; i++)
		{
			for(int j = i + 1; j < numcirculos; j++)
			{
				if(celda[i][j].esTachado() == 0)
				{
					/*~~~~~~~*/
					int np = 0;
					/*~~~~~~~*/

					np = celda[i][j].obtenerNumpares();
					if(np > -1)
					{
						for(int k = 0; k <= np; k++)
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							int prim = celda[i][j].obtenerPrimero(k);
							int seg = celda[i][j].obtenerSegundo(k);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(celda[prim][seg].esTachado() == 1)
							{
								celda[i][j].Tachar();
								if(conTabla == 1)
									Form16->Grid1->Cells[i + 1][j] = Form16->Grid1->Cells[i + 1][j] + "tach";
								mod = 1;
							}
						}
					}
				}
			}
		}
	} while(mod == 1);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::comprobarTabla(void)
{
	for(int i = 0; i < numcirculos; i++)
	{
		/*~~~~~~~~~~*/
		SOLUCION	s;
		/*~~~~~~~~~~*/

		solucion[i] = s;
		for(int j = i + 1; j < numcirculos; j++)
		{
			if(celda[i][j].esTachado() == 0)
			{
				solucion[i].AnyadirEquivalentes(i, j);
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::pertenece(int a)
{
	/*~~~~~~~~~~~*/
	int pert = 100;
	/*~~~~~~~~~~~*/

	for(int i = 0; i < a; i++)
	{
		/*~~*/
		int e;
		/*~~*/

		e = solucion[i].getNumeroEquivalentes();
		for(int j = 0; j <= e; j++)
		{
			if(a == (solucion[i].obtenerSegundoEq(j)))
			{
				pert = i;
			}
		}
	}

	return pert;
}

int SISTEMA::pertenece2(int a)
{
	/*~~~~~~~~~~~*/
	int pert = 100;
	/*~~~~~~~~~~~*/

	for(int i = 0; i < a; i++)
	{
		/*~~*/
		int e;
		/*~~*/

		e = solucion2[i].getNumeroEquivalentes();
		for(int j = 0; j <= e; j++)
		{
			if(a == (solucion2[i].obtenerSegundoEq(j)))
			{
				pert = solucion2[i].obtenerPrimerEq(j);
			}
		}
	}

	return pert;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::particionEquivalencia(void)
{
	numcirculos2 = 0;
	numflechas2 = 0;

	//
	// Form16->Edit1->Text ="Particion de equivalencia: "; Form16->Edit2->Text ="Nodos
	// finales: ";
	//
	for(int i = 0; i < numcirculos; i++)	// tiene que haber num nodos -1
	{
		if(pertenece(i) == 100)
		{
			/*~~*/
			int e;
			/*~~*/

			e = solucion[i].getNumeroEquivalentes();
			Form16->Edit1->Text = Form16->Edit1->Text + "(" + cogerEtiq(i);
			Form16->Edit2->Text = Form16->Edit2->Text + cogerEtiq(i) + "' ";	// nodos finales

			circulo2[numcirculos2] = getCirculo(i);
                        solucion2[numcirculos2] = solucion[i];
			Form16->ListBox1->Items->Add(cogerEtiqPrima(numcirculos2));
			numcirculos2++;
			for(int j = 0; j <= e; j++)
			{
				Form16->Edit1->Text = Form16->Edit1->Text + cogerEtiq(solucion[i].obtenerSegundoEq(j));
			}

			Form16->Edit1->Text = Form16->Edit1->Text + ")";
		}
	}

	for(int k = 0; k < numflechas; k++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	in1, out1;
		int			ndsal1, ndent1;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		in1 = flecha[k].DevolverEtiqueta1();
		out1 = flecha[k].DevolverEtiqueta2();
		ndsal1 = flecha[k].FlechaCirculoSale();
		ndent1 = flecha[k].FlechaCirculoEntra();
		if(pertenece(ndsal1) == 100)
		{
			flecha2[numflechas2] = getFlecha(k);
			numflechas2++;

			/*~~~~~~~~~~~~~~~~~*/
			AnsiString	ndantsal;
			/*~~~~~~~~~~~~~~~~~*/

			ndantsal = circulo[ndsal1].DevolverEtiqueta1();
			for(int l = 0; l < numcirculos2; l++)
			{
				/*~~~~~~~~~~~~~~~~~*/
				AnsiString	ndactsal;
				/*~~~~~~~~~~~~~~~~~*/

				ndactsal = circulo2[l].DevolverEtiqueta1();
				if(AnsiCompareStr(ndantsal, ndactsal) == 0)
                                	flecha2[numflechas2 - 1].ActualizarCirculoSale(l);
			}

			/*~~~~~~~~~~~~~~*/
			AnsiString	ndant;
			/*~~~~~~~~~~~~~~*/

			if(pertenece2(ndent1) != 100)
				ndant = circulo[pertenece2(ndent1)].DevolverEtiqueta1();
			else
				ndant = circulo[ndent1].DevolverEtiqueta1();
			for(int l = 0; l < numcirculos2; l++)
			{
				/*~~~~~~~~~~~~~~*/
				AnsiString	ndact;
				/*~~~~~~~~~~~~~~*/

				ndact = circulo2[l].DevolverEtiqueta1();
				if(AnsiCompareStr(ndant, ndact) == 0) flecha2[numflechas2 - 1].ActualizarCirculoEntra(l);
			}

			Form16->ListBox2->Items->Add(CogerFlecha2(numflechas2 - 1));
		}
	}

	// Form16->Edit3->Text = numcirculos;
	Form16->Edit4->Text = numcirculos2;

	// Form16->Edit5->Text = numflechas;
	Form16->Edit6->Text = numflechas2;
}


void SISTEMA::tablaMinimaAutomataNoEspecif(void)
{
	numcirculos2 = 0;
	numflechas2 = 0;

        list<set<int>* > compatMaximal;
        list<set<int>* > incompatMaximal;

	for(int circ1 = numcirculos-1; circ1 >= 0; circ1--)
	{
                int numClasesCompat = 0;
                int numClasesIncompat = 0;

               	for(list<set<int>* >::iterator clase = compatMaximal.begin(); clase != compatMaximal.end(); clase++)
                {
	              	bool compatibleTodos = true;
                        bool compatibleAlgunos = false;
                        set<int> *nuevaClase = new set<int>();
                        nuevaClase->insert(circ1);
                       	for(set<int>::iterator j = (*clase)->begin(); j != (*clase)->end(); j++)
				if (celda[circ1][*j].esTachado())
					compatibleTodos = false;
                                else
                                {
					compatibleAlgunos = true;
                                        nuevaClase->insert(*j);
                                }

                        if (compatibleTodos)
                        {
                              (*clase)->insert(circ1);
                              delete nuevaClase;
                        }
                        else if (compatibleAlgunos)
			{
	                        bool incluidoAlguno = false;
		               	for(list<set<int>* >::iterator clase = compatMaximal.begin(); clase != compatMaximal.end() && !incluidoAlguno; clase++)
					if (includes((*clase)->begin(),(*clase)->end(),nuevaClase->begin(),nuevaClase->end()))
	                                	incluidoAlguno = true;
	                        if(!incluidoAlguno)
                                {
					compatMaximal.push_back(nuevaClase);
                                        numClasesCompat++;
                                }
                                else
                                	delete nuevaClase;
                        }
                        else
                        	delete nuevaClase;
                }

               	for(list<set<int>* >::iterator clase = incompatMaximal.begin(); clase != incompatMaximal.end(); clase++)
                {
	              	bool incompatibleTodos = true;
                        bool incompatibleAlgunos = false;
                        set<int> *nuevaClase = new set<int>();
                        nuevaClase->insert(circ1);
                       	for(set<int>::iterator j = (*clase)->begin(); j != (*clase)->end(); j++)
				if (!celda[circ1][*j].esTachado())
					incompatibleTodos = false;
                                else
                                {
					incompatibleAlgunos = true;
                                        nuevaClase->insert(*j);
                                }

                        if (incompatibleTodos)
                        {
                              (*clase)->insert(circ1);
                              delete nuevaClase;
                        }
                        else if (incompatibleAlgunos)
			{
	                        bool incluidoAlguno = false;
		               	for(list<set<int>* >::iterator clase = incompatMaximal.begin(); clase != incompatMaximal.end() && !incluidoAlguno; clase++)
					if (includes((*clase)->begin(),(*clase)->end(),nuevaClase->begin(),nuevaClase->end()))
	                                	incluidoAlguno = true;
	                        if(!incluidoAlguno)
                                {
                                	numClasesIncompat++;
					incompatMaximal.push_back(nuevaClase);
                                }
                                else
                                	delete nuevaClase;
                        }
                        else
                        	delete nuevaClase;
                }



		for(int circ2 = circ1 + 1; circ2 < numcirculos; circ2++)
                	if(!celda[circ1][circ2].esTachado())
			{
	                	set<int> *par = new set<int>();
	       	                par->insert(circ1);
	               	        par->insert(circ2);
	                        bool incluidoAlguno = false;
		               	for(list<set<int>* >::iterator clase = compatMaximal.begin(); clase != compatMaximal.end() && !incluidoAlguno; clase++)
					if (includes((*clase)->begin(),(*clase)->end(),par->begin(),par->end()))
	                                	incluidoAlguno = true;
	                        if(!incluidoAlguno)
                                {
                                	numClasesCompat++;
                                	compatMaximal.push_back(par);
                                }
                                else
                                {
                                	delete par;
                                }
       			}
                        else
                        {
	                	set<int> *par = new set<int>();
	       	                par->insert(circ1);
	               	        par->insert(circ2);
	                        bool incluidoAlguno = false;
		               	for(list<set<int>* >::iterator clase = incompatMaximal.begin(); clase != incompatMaximal.end() && !incluidoAlguno; clase++)
					if (includes((*clase)->begin(),(*clase)->end(),par->begin(),par->end()))
	                                	incluidoAlguno = true;
	                        if(!incluidoAlguno)
                                {
                                	numClasesIncompat++;
                                	incompatMaximal.push_back(par);
                                }
                                else
                                {
                                	delete par;
                                }
                        }

                        if(numClasesCompat==0)
                        {
				set<int> *claseEstado = new set<int>();
                                claseEstado->insert(circ1);
	                        bool incluidoAlguno = false;
		               	for(list<set<int>* >::iterator clase = compatMaximal.begin(); clase != compatMaximal.end() && !incluidoAlguno; clase++)
					if (includes((*clase)->begin(),(*clase)->end(),claseEstado->begin(),claseEstado->end()))
	                                	incluidoAlguno = true;
	                        if(!incluidoAlguno)
        	                        compatMaximal.push_back(claseEstado);
                                else
                                	delete claseEstado;
                        }
                        if(numClasesIncompat==0)
                        {
				set<int> *claseEstado = new set<int>();
                                claseEstado->insert(circ1);
	                        bool incluidoAlguno = false;
		               	for(list<set<int>* >::iterator clase = incompatMaximal.begin(); clase != incompatMaximal.end() && !incluidoAlguno; clase++)
					if (includes((*clase)->begin(),(*clase)->end(),claseEstado->begin(),claseEstado->end()))
	                                	incluidoAlguno = true;
	                        if(!incluidoAlguno)
        	                        incompatMaximal.push_back(claseEstado);
                                else
                                	delete claseEstado;
                        }
	}

	list<set<int>* >::iterator i;

        i = compatMaximal.begin();
        while(i!=compatMaximal.end())
        {
		bool incluidoAlguno = false;
	        for(list<set<int>* >::iterator j = compatMaximal.begin(); j != compatMaximal.end(); j++)
			if (i!=j)
				if (includes((*j)->begin(),(*j)->end(),(*i)->begin(),(*i)->end()))
		                       	incluidoAlguno = true;
		if(incluidoAlguno)
                	i=compatMaximal.erase(i);
                else
                	i++;
	}

        i = incompatMaximal.begin();
        while(i!=incompatMaximal.end())
        {
		bool incluidoAlguno = false;
	        for(list<set<int>* >::iterator j = incompatMaximal.begin(); j != incompatMaximal.end(); j++)
			if (i!=j)
                        	if (includes((*j)->begin(),(*j)->end(),(*i)->begin(),(*i)->end()))
		                       	incluidoAlguno = true;
		if(incluidoAlguno)
                	i=incompatMaximal.erase(i);
                else
                	i++;
	}


	for(list<set<int>* >::iterator i = compatMaximal.begin(); i != compatMaximal.end(); i++)
        {
		Form16->Edit2->Text = Form16->Edit2->Text + "(";
                for(set<int>::iterator j = (*i)->begin(); j != (*i)->end(); j++)
                	Form16->Edit2->Text = Form16->Edit2->Text + cogerEtiq(*j);
                Form16->Edit2->Text = Form16->Edit2->Text + ")";
        }

	for(list<set<int>* >::iterator i = incompatMaximal.begin(); i != incompatMaximal.end(); i++)
        {
		Form16->Edit1->Text = Form16->Edit1->Text + "(";
                for(set<int>::iterator j = (*i)->begin(); j != (*i)->end(); j++)
                	Form16->Edit1->Text = Form16->Edit1->Text + cogerEtiq(*j);
                Form16->Edit1->Text = Form16->Edit1->Text + ")";
        }

        int cotaMinima;
        int cotaMaxima;

        cotaMaxima = compatMaximal.size();
        cotaMinima = 0;
	for(list<set<int>* >::iterator i = incompatMaximal.begin(); i != incompatMaximal.end(); i++)
		if ((*i)->size() > cotaMinima)
                        cotaMinima = (*i)->size();


	int maximo = ElevarBase2(NumCarEnt);
        int circ=0;
        for(list<set<int>* >::iterator i = compatMaximal.begin(); i != compatMaximal.end(); i++,circ++)
	{
        	set<int>* clase = *i;//compatMaximal[circ];

        	circulo2[numcirculos2].Etiqueta1 = circulo[*(clase->begin())].Etiqueta1;
        	circulo2[numcirculos2].CirculoX = circulo[*(clase->begin())].CirculoX;
        	circulo2[numcirculos2].CirculoY = circulo[*(clase->begin())].CirculoY;

                if (Tipo==MOORE)
                {
	                AnsiString	salida = AnsiString::StringOfChar('X', NumCarSal);
			for(int j = 0; j < numcirculos; j++)
			{
                                if (clase->count(j))
                                {
	                        	CIRCULO c = circulo[j];
                                        for (int i = 1; i <= c.Etiqueta2.Length(); i++)
                                               	if (salida[i]=='X' && (c.Etiqueta2[i] == '0' || c.Etiqueta2[i] == '1'))
                                                       	salida[i] = c.Etiqueta2[i];
                                }
                        }
                        circulo2[numcirculos2].Etiqueta2 = salida;
                }

                numcirculos2++;

		for(int ent = 0; ent < maximo; ent++)
		{
			AnsiString	entBin = Dec2BinAcot(ent, NumCarEnt);
                        AnsiString	salida = AnsiString::StringOfChar('X', NumCarSal);
                        set<int>	estadosSiguientes;
                        int		estadoSiguiente;

			for(int j = 0; j < numflechas; j++)
			{
                        	FLECHA f = flecha[j];
                                if (f.Etiqueta1 == entBin && clase->count(f.CirculoSale))
                                {
					estadosSiguientes.insert(f.CirculoEntra);
                                        if (Tipo==MEALY)
	                                        for (int i = 1; i <= f.Etiqueta2.Length(); i++)
                                                	if (salida[i]=='X' && (f.Etiqueta2[i] == '0' || f.Etiqueta2[i] == '1'))
                                                        	salida[i] = f.Etiqueta2[i];
                                }
                        }

                        if (!estadosSiguientes.empty())
                        {
                        	bool encontrado = false;
                                int circ2=0;
			        for(list<set<int>* >::iterator j = compatMaximal.begin(); j != compatMaximal.end() && !encontrado; j++,circ2++)
					if (includes((*j)->begin(),(*j)->end(),estadosSiguientes.begin(),estadosSiguientes.end()))
					{
                                        	encontrado = true;
                                                estadoSiguiente = circ2;
                                        }
				flecha2[numflechas2].Etiqueta1 = entBin;
                                flecha2[numflechas2].Etiqueta2 = salida;
                                flecha2[numflechas2].CirculoSale = circ;
                                flecha2[numflechas2].CirculoEntra = estadoSiguiente;
				flecha2[numflechas2].FlechaX = 100;
                                flecha2[numflechas2].FlechaY = 100;
				numflechas2++;
                        }

                }

	}



        for(int i=0;i<numflechas2;i++)
	{
	        int desplazamientoY=(40 + random(10))*(i%2?1:-1);
        	flecha2[i].FlechaX = (circulo2[flecha2[i].CirculoSale].CirculoX + circulo2[flecha2[i].CirculoEntra].CirculoX)/2;
		flecha2[i].FlechaY = (circulo2[flecha2[i].CirculoSale].CirculoY + circulo2[flecha2[i].CirculoEntra].CirculoY)/2 + desplazamientoY;
	}


        if (cotaMinima < numcirculos2)
        {
        	Form16->lblAviso->Visible=true;
		Form16->lblAviso->Caption=MENSAJE(msgAvisoAutIncEspNoMinimo);
        }

	// Form16->Edit3->Text = numcirculos;
	Form16->Edit4->Text = numcirculos2;

	// Form16->Edit5->Text = numflechas;
	Form16->Edit6->Text = numflechas2;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::cambiarCirculos(void)
{
	numcirculos = numcirculos2;
	for(int i = 0; i < numcirculos; i++) circulo[i] = circulo2[i];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::cambiarFlechas(void)
{
	numflechas = numflechas2;
	for(int i = 0; i < numflechas; i++) flecha[i] = flecha2[i];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::mostrarCambios(void)
{
	/*
	 * for (int i=0;i<=numcirculos;i++) Form4->ListBox1->Items->Add(cogerEtiq(i)); for
	 * (int j=0;j<=numflechas;j++) Form4->ListBox2->Items->Add(CogerFlecha(j));
	 * Form4->ShowModal();
	 */
}

/*
 =======================================================================================================================
    void AnyadirCirculo ( AnsiString e) { numcirculos++; CIRCULO c; c.ActualizarEtiqueta1(e); circulo[numcirculos]= c;
    } £
    void AnyadirFlecha ( AnsiString o, AnsiString i, AnsiString E1, AnsiString E2){ numflechas++; FLECHA f; for (int
    j=0;j<=numcirculos;j++) if (AnsiCompareStr(circulo[j].DevolverEtiqueta1(),o)==0) f.ActualizarCirculoSale(j); for
    (int h=0;h<=numcirculos;h++) if (AnsiCompareStr(circulo[h].DevolverEtiqueta1(),i)==0) f.ActualizarCirculoEntra(h);
    f.ActualizarEtiqueta1(E1); f.ActualizarEtiqueta2(E2); flecha[numflechas]=f; }
 =======================================================================================================================
 */
CIRCULO SISTEMA::getCirculo(int a)
{
	return circulo[a];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLECHA SISTEMA::getFlecha(int a)
{
	return flecha[a];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLECHA SISTEMA::getFlechaActual(void)
{
	return flecha[indiceFlechaActual];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::CogerFlecha(int a)
{
	return
		(
			circulo[flecha[a].FlechaCirculoSale()].DevolverEtiqueta1() +
				"        " +
				circulo[flecha[a].FlechaCirculoEntra()].DevolverEtiqueta1() +
				"      " +
				flecha[a].DevolverEtiqueta1() +
				"   " +
				flecha[a].DevolverEtiqueta2()
		);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::CogerFlecha2(int a)
{
	return
		(
			circulo2[flecha2[a].FlechaCirculoSale()].DevolverEtiqueta1() +
				"        " +
				circulo2[flecha2[a].FlechaCirculoEntra()].DevolverEtiqueta1() +
				"      " +
				flecha2[a].DevolverEtiqueta1() +
				"   " +
				flecha2[a].DevolverEtiqueta2()
		);
}

/*
 =======================================================================================================================
    void ActualizarEtiqueta1Circulo(int num,AnsiString a) //Actualiza la etiqueta del circulo num desde la clase
    Sistema { circulo[num].ActualizarEtiqueta1(a); grabaste=0; } £
    void ActualizarEtiqueta1Flecha(int num,AnsiString a) //Actualiza la etiqueta1 de la flecha num desde la clase
    Sistema { flecha[num].ActualizarEtiqueta1(a); grabaste=0; }
 =======================================================================================================================
 */
int SISTEMA::GetNumCirculos(void)
{
	return numcirculos;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::GetNumFlechas(void)
{
	return numflechas;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::CogerEntradaActual(void)
{
  return entrada;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::CogerSalidaActual(void)
{
	if(Tipo == MOORE)
		return circulo[indiceActual].DevolverEtiqueta2();
	else if(Tipo == MEALY)
		return flecha[indiceFlechaActual].DevolverEtiqueta2();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::CogerNombreCirculoActual(void)
{
	return circulo[indiceActual].DevolverEtiqueta1();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::CogerNombreCirculoSiguiente(void)
{
	return circulo[getFlechaActual().FlechaCirculoEntra()].DevolverEtiqueta1();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::cogerEtiq(int b)
{
	return circulo[b].DevolverEtiqueta1();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::cogerEtiqPrima(int b)
{
	return circulo2[b].DevolverEtiqueta1();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::cogerEtiqF(int b)
{
	return flecha[b].DevolverEtiqueta1();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::cogerEtiqF2(int b)
{
	return flecha[b].DevolverEtiqueta2();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::cogerEtiqF3(int b)
{
	return flecha[b].FlechaCirculoEntra();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString SISTEMA::cogerEtiqF4(int b)
{
	return flecha[b].FlechaCirculoSale();
}

//
// =======================================================================================================================
//    fin modificado Ainara
// =======================================================================================================================
//
bool SISTEMA::PuedeSeguir(AnsiString &ent, AnsiString &barrera)
{
	/*~~~~~~~~~~~~~~~~~*/
	bool	sigue = true;
	/*~~~~~~~~~~~~~~~~~*/

	if(ent.Length() != barrera.Length()) return false;

	for(int i = 1; i <= ent.Length(); i++)
		if(ent[i] != barrera[i] && barrera[i] != 'X') sigue = false;

	return sigue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::VerificarAutomata(int &estado, int &transicion, AnsiString &entrada)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	bool	bien = true, demasiadas, falta;
	int		error;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// Verificamos que todos los estados/transiciones tienen salida
	if(Tipo == MOORE)
	{
		for(int i = 0; i < numcirculos && bien; i++)
		{
			bien = bien && circulo[i].DevolverEtiqueta2() != "";
			if(!bien) estado = i;
		}

		if(!bien) return MOORE_ESTADO_SIN_SALIDA;
	}
	else if(Tipo == MEALY)
	{
		for(int i = 0; i < numflechas && bien; i++)
		{
			bien = bien && flecha[i].DevolverEtiqueta2() != "";
			if(!bien) estado = i;
		}

		if(!bien) return MEALY_TRANSICION_SIN_SALIDA;
	}

	// Verificamos que todas las posibles entradas pueden seguirse en todos los estados
	falta = false;
	demasiadas = false;
	bien = true;
	for(int i = 0; i < numcirculos && bien; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int maximo = ElevarBase2(NumCarEnt);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int ent = 0; ent < maximo && bien; ent++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	entBin = Dec2BinAcot(ent, NumCarEnt);
			int			numFlechas = 0;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for(int j = 0; j < numflechas && bien; j++)
			{
				/*~~~~~~~~~~~~~~~~~~*/
				FLECHA	f = flecha[j];
				/*~~~~~~~~~~~~~~~~~~*/

				if(f.FlechaCirculoSale() == i)
				{
					if(PuedeSeguir(entBin, f.DevolverEtiqueta1()))
					{
						numFlechas++;
						if(numFlechas > 1)
						{
							estado = i;
							transicion = j;
							entrada = entBin;
							demasiadas = true;
							bien = false;
						}
					}
				}
			}

			if(numFlechas == 0 && bien)
			{
				estado = i;
				entrada = entBin;
				falta = true;
			}
		}
	}

	if(demasiadas)
		return DEMASIADAS_TRANSICIONES;
	else if(bien)
		if(falta)
			return AUTOMATA_CORRECTO_FALTA_TRANSICION;
		else
			return AUTOMATA_COMPLETO;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ConvertirMooreAMealy(void)
{
	Tipo = MEALY;
	for(int i = 0; i < numflechas; i++) flecha[i].Etiqueta2 = circulo[flecha[i].CirculoEntra].Etiqueta2;
	for(int i = 0; i < numcirculos; i++) circulo[i].Etiqueta2 = "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SISTEMA::ConvertirMealyAMoore(void)
{
	Tipo = MOORE;
	CIRCULO	circuloMoore[MaxCir];
	FLECHA flechaMoore[MaxFle];
        int numcirculosMoore=0, numflechasMoore=0;

        for(int i = 0; i< numcirculos; i++)
        {
                int salidasPosibles=ElevarBase2(NumCarSal);
                int desplazamientoX = 0;
                for(int j=0;j<salidasPosibles;j++)
                {
                        AnsiString salida = Dec2BinAcot(j,NumCarSal);
                        bool tieneSalida = false;
                        for(int k=0; k<numflechas && !tieneSalida;k++)
                                if (flecha[k].CirculoEntra == i && flecha[k].Etiqueta2 == salida)
                                {
                                        circuloMoore[numcirculosMoore]=circulo[i];
                                        circuloMoore[numcirculosMoore].Etiqueta2=salida;
                                        circuloMoore[numcirculosMoore].CirculoX += desplazamientoX;
                                        tieneSalida = true;
                                        numcirculosMoore++;
                                }
                        desplazamientoX += 150;
                }
        }


        for(int i = 0; i< numcirculosMoore; i++)
        {
                int entradasPosibles=ElevarBase2(NumCarEnt);
                int desplazamientoY=(40 + random(10))*(i%2?1:-1);
                for(int j=0;j<entradasPosibles;j++)
                {
                        AnsiString entrada = Dec2BinAcot(j,NumCarEnt);
                        FLECHA nuevaFlecha;
                        nuevaFlecha.CirculoSale = i;
                        nuevaFlecha.Etiqueta1 = entrada;
                        bool encontrado = false;
                        for(int k=0;k<numflechas && !encontrado;k++)
                                if(circulo[flecha[k].CirculoSale].Etiqueta1==circuloMoore[i].Etiqueta1 && PuedeSeguir(entrada,flecha[k].Etiqueta1))
                                {
                                        bool circuloencontrado = false;
                                        for(int l=0;l<numcirculosMoore && !circuloencontrado;l++)
                                                if(circulo[flecha[k].CirculoEntra].Etiqueta1==circuloMoore[l].Etiqueta1 && circuloMoore[l].Etiqueta2==flecha[k].Etiqueta2)
                                                {
                                                        nuevaFlecha.CirculoEntra=l;
                                                        encontrado = true;
                                                        circuloencontrado=true;
                                                        if (nuevaFlecha.CirculoEntra != nuevaFlecha.CirculoSale)
                                                        {
                                                                nuevaFlecha.FlechaX = (circuloMoore[nuevaFlecha.CirculoSale].CirculoX + circuloMoore[nuevaFlecha.CirculoEntra].CirculoX)/2;
                                                                nuevaFlecha.FlechaY = (circuloMoore[nuevaFlecha.CirculoSale].CirculoY + circuloMoore[nuevaFlecha.CirculoEntra].CirculoY)/2 + desplazamientoY;
                                                                desplazamientoY+=20;
                                                        }
                                                        else
                                                        {
                                                                nuevaFlecha.FlechaX = circuloMoore[nuevaFlecha.CirculoSale].CirculoX + 80;
                                                                nuevaFlecha.FlechaY = circuloMoore[nuevaFlecha.CirculoSale].CirculoY + 80;
                                                        }
                                                }
                                }
                        flechaMoore[numflechasMoore]=nuevaFlecha;
                        numflechasMoore++;
                }

        }

        for(int i=0; i<numcirculos; i++)
        {
                char sufijo = 'A';
                int numCirculos=0;
                for(int j=0;j<numcirculosMoore;j++)
                        if (circulo[i].Etiqueta1==circuloMoore[j].Etiqueta1)
                                numCirculos++;
                if(numCirculos>1)
                        for(int j=0;j<numcirculosMoore;j++)
                                if (circulo[i].Etiqueta1==circuloMoore[j].Etiqueta1)
                                        circuloMoore[j].Etiqueta1+=sufijo++;
        }


        // Algoritmo de transiciones salientes.
        /*
        for(int i = 0; i< numcirculos; i++)
        {
                int salidasPosibles=ElevarBase2(NumCarSal);
                int desplazamientoX = 0;
                for(int j=0;j<salidasPosibles;j++)
                {
                        AnsiString salida = Dec2BinAcot(j,NumCarSal);
                        bool tieneSalida = false;
                        for(int k=0; k<numflechas && !tieneSalida;k++)
                                if (flecha[k].CirculoSale == i && flecha[k].Etiqueta2 == salida)
                                {
                                        circuloMoore[numcirculosMoore]=circulo[i];
                                        circuloMoore[numcirculosMoore].Etiqueta2=salida;
                                        circuloMoore[numcirculosMoore].CirculoX += desplazamientoX;
                                        tieneSalida = true;
                                        numcirculosMoore++;
                                }
                        desplazamientoX += 150;
                }
        }

        for(int i = 0; i< numcirculosMoore; i++)
        {
                int entradasPosibles=ElevarBase2(NumCarEnt);
                for(int j=0;j<entradasPosibles;j++)
                {
                        AnsiString entrada = Dec2BinAcot(j,NumCarSal);
                        FLECHA nuevaFlecha;
                        nuevaFlecha.CirculoSale = i;
                        nuevaFlecha.Etiqueta1 = entrada;
                        bool encontrado = false;
                        for(int k=0;k<numflechas && !encontrado;k++)
                                if(circulo[flecha[k].CirculoSale].Etiqueta1==circuloMoore[i].Etiqueta1 && PuedeSeguir(entrada,flecha[k].Etiqueta1))
                                {
                                        bool circuloencontrado = false;
                                        for(int l=0;l<numcirculosMoore && !circuloencontrado;l++)
                                                if(circulo[flecha[k].CirculoEntra].Etiqueta1==circuloMoore[l].Etiqueta1 && circuloMoore[l].Etiqueta2==flecha[k].Etiqueta2)
                                                {
                                                        nuevaFlecha.CirculoEntra=l;
                                                        encontrado = true;
                                                        circuloencontrado=true;
                                                        nuevaFlecha.FlechaX = 200;
                                                        nuevaFlecha.FlechaY = 200;
                                                }
                                }
                        flechaMoore[numflechasMoore]=nuevaFlecha;
                        numflechasMoore++;
                }

        }
        */

        for(int i=0; i<numcirculosMoore; i++)
                circulo[i]=circuloMoore[i];
        for(int i=0; i<numflechasMoore; i++)
                flecha[i]=flechaMoore[i];

        numcirculos = numcirculosMoore;
        numflechas = numflechasMoore;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int SISTEMA::ReconvertirMealyAMoore(void)
{
	if(!ReconversibleMealyAMoore())
		return NO_RECONVERTIBLE;
	else
	{
		for(int i = 0; i < numcirculos; i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	salida = "";
			/*~~~~~~~~~~~~~~~~~~~~*/

			for(int j = 0; j < numflechas && salida == ""; j++)
				if(flecha[j].FlechaCirculoSale() == i) salida = flecha[j].DevolverEtiqueta2();
			circulo[i].ActualizarEtiqueta2(salida);
		}

		for(int j = 0; j < numflechas; j++) flecha[j].ActualizarEtiqueta2("");
		Tipo = MOORE;
		return RECONVERSION_CORRECTA;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool SISTEMA::ReconversibleMealyAMoore(void)
{
	/*~~~~~~~~~~~~~~~~*/
	bool	bien = true;
	/*~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < numcirculos && bien; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	salida = "";
		/*~~~~~~~~~~~~~~~~~~~~*/

		for(int j = 0; j < numflechas && bien; j++)
		{
			if(flecha[j].FlechaCirculoSale() == i)
				if(salida == "")
					salida = flecha[j].DevolverEtiqueta2();
				else
					bien = (flecha[j].DevolverEtiqueta2() == salida);
		}

		if(salida == "") bien = false;
	}

	return bien;
}


// Expande las transiciones con X
// P.ej. --> X1 = 11 + 01
void SISTEMA::Expandir(void)
{
	for(int flech = 0; flech < numflechas; flech++)
        {
        	int divisible;
                do
                {
                	int posX = flecha[flech].Etiqueta1.Pos("X");
                	if (posX > 0)
                        {
                        	flecha[numflechas] = flecha[flech];
                                flecha[flech].Etiqueta1[posX] = '0';
                                flecha[numflechas].Etiqueta1[posX] = '1';
                                posX = flecha[flech].Etiqueta1.Pos("X");
                                numflechas++;
                        }
                        if (posX == 0)
                        	divisible = false;
                        else
                        	divisible = true;
                } while (divisible);
        }
}


// Junta las transiciones combinables
// P.ej. --> 01 + 11 = X1
void SISTEMA::Contraer(void)
{
	for(int circ = 0; circ < numcirculos; circ++)
	{
        	int combinaciones;
                do
                {
                	combinaciones = 0;
        		for(int flech = 0; flech < numflechas-1; flech++)
        		{
                                if(flecha[flech].CirculoSale == circ)
                                {
                                        int circuloEntra = flecha[flech].CirculoEntra;
                                        AnsiString barrera = flecha[flech].Etiqueta1;
                                        AnsiString salida = flecha[flech].Etiqueta2;
                                        for(int flech2 = flech + 1; flech2 < numflechas; flech2++)
                                                if (flecha[flech2].CirculoSale == circ && flecha[flech2].CirculoEntra == circuloEntra && ((Tipo==MEALY && flecha[flech2].Etiqueta2==salida) || Tipo==MOORE) )
                                                        if (flecha[flech].CombinableCon(flecha[flech2]))
                                                        {
                                                                flecha[flech].CombinarCon(flecha[flech2]);
                                                        	for(int p = flech2; p < numflechas; p++)
                                                        		flecha[p] = flecha[p + 1];
                                                                flech2--;
                                                                numflechas--;
                                                                combinaciones++;
                                                        }
                                }
        		}
                } while (combinaciones > 0);
       	}

}


bool SISTEMA::EsIncompletamenteEspecificado(void)
{
	int dummy1, dummy2;
        AnsiString dummy3;
	if (VerificarAutomata(dummy1, dummy2, dummy3)==AUTOMATA_CORRECTO_FALTA_TRANSICION)
        	return true;
        else
        {
		bool completo = true;

		if (Tipo==MOORE)
	        	for(int i=0; i<numcirculos && completo;i++)
	                {
	                	if(circulo[i].Etiqueta2.Pos("X")>0)
	                        	completo = false;
	                }
	        else if (Tipo==MEALY)
	        {
	        	for(int i=0; i<numflechas && completo;i++)
	                {
	                	if(flecha[i].Etiqueta2.Pos("X")>0)
	                        	completo = false;
	                }
	        }
                        return !completo;
        }
}


