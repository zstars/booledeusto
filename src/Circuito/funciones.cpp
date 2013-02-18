/*$T boole/Circuito/funciones.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "funciones.h"
#include "PuertaAnd.h"
#include "PuertaOr.h"
#include "PuertaNand.h"
#include "PuertaNor.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool salidaNegada(AnsiString s)
{
	/*~~~~~~~~~~~*/
	int numNeg = 0;
	/*~~~~~~~~~~~*/

	for(int i = 1; i <= 6; i++)
		if(s[i] == '~' && s[i + 1] == '(')
		{
			numNeg++;
			i++;
		}

	if(numNeg == 3)
		return true;
	else
		return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString getNombreEntrada(AnsiString s)
{
	/*~~~~~~~~~~*/
	AnsiString	d;
	/*~~~~~~~~~~*/

	for(int i = 1; i <= s.Length(); i++)
	{
		if(esEntrada(s.SubString(i, s.Length() - i + 1)))
			d = d + s[i];
		else
			break;
	}

	return d;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int numTerminos(AnsiString s)
{
	/*~~~~~~*/
	int n = 0;
	/*~~~~~~*/

	for(int i = 1; i <= s.Length(); i++)
		if((AnsiString) s[i] == (AnsiString) "(") n++;
	return n;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool existeSim(AnsiString s, char sim)
{
	/*~~~~~~~~~~~~~~~~~~~*/
	bool	existe = false;
	int		i = 1;
	/*~~~~~~~~~~~~~~~~~~~*/

	while(i <= s.Length() && existe == false)
	{
		if(s[i] == sim) existe = true;
		i++;
	}

	return existe;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int Modo(AnsiString s)
{
	/*~~~~~~~~~*/
	int Modo = 0;
	int i = 1;
	/*~~~~~~~~~*/

	if((numTerminos(s) == 1) && (existeSim(s, '+')))
		Modo = 2;
	else if((numTerminos(s) == 1) && (existeSim(s, '*')))
		Modo = 1;
	else if((AnsiString) s[1] == (AnsiString) "~" && (AnsiString) s[2] == (AnsiString) "(")
	{
		if(existeSim(s, '*'))
			Modo = 3;		// NAND
		else if(existeSim(s, '+'))
			Modo = 4;		// NOR
	}
	else
	{
		while(Modo == 0 && i < s.Length() - 1)
		{
			if(((AnsiString) s[i] == (AnsiString) "+") && ((AnsiString) s[i + 1] == (AnsiString) "("))
			{
				Modo = 1;	// AND-OR
			}
			else if(((AnsiString) s[i] == (AnsiString) "*") && ((AnsiString) s[i + 1] == (AnsiString) "("))
			{
				Modo = 2;	// OR-AND
			}

			i++;
		}					// end-while
		}

	return Modo;
}	// fin-modo

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool mayor(AnsiString E1, AnsiString E2)
{
	if((AnsiString) E1[1] == (AnsiString) "~" && (AnsiString) E2[1] == (AnsiString) "~")
	{
		if(E1.SubString(2, E1.Length() - 1) > E2.SubString(2, E2.Length() - 1))
			return true;
		else
			return false;
	}
	else if((AnsiString) E1[1] == (AnsiString) "~" && (AnsiString) E2[1] != (AnsiString) "~")
	{
		if(E1.SubString(2, E1.Length() - 1) >= E2)
			return true;
		else
			return false;
	}
	else if((AnsiString) E1[1] != (AnsiString) "~" && (AnsiString) E2[1] == (AnsiString) "~")
	{
		if(E1 > E2.SubString(2, E2.Length() - 1))
			return true;
		else
			return false;
	}
	else	// ninguna es negada
	{
		if(E1 > E2)
			return true;
		else
			return false;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool esSimbolo(AnsiString s)
{
	if
	(
		((AnsiString) s[1] != (AnsiString) "+")
	&&	((AnsiString) s[1] != (AnsiString) "(")
	&&	((AnsiString) s[1] != (AnsiString) ")")
	&&	((AnsiString) s[1] != (AnsiString) "*")
	&&	((AnsiString) s[1] != (AnsiString) "~")
	) return false;
	else
		return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool esEntrada(AnsiString s)
{
	if
	(
		((AnsiString) s[1] != (AnsiString) "+")
	&&	((AnsiString) s[1] != (AnsiString) "(")
	&&	((AnsiString) s[1] != (AnsiString) ")")
	&&	((AnsiString) s[1] != (AnsiString) "*")
	)
	{
		if(s.Length() > 1)
		{
			if(((AnsiString) s[1] == (AnsiString) "~") && ((AnsiString) s[2] == (AnsiString) "("))
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else
		return false;
}

//
// =======================================================================================================================
//    A PARTIR DE AQUÍ SON FUNCIONES PARA DIBUJAR EL CIRCUITO.
// =======================================================================================================================
//
void limpiarCanvas(void)
{
	FormR->Image1->Canvas->Brush->Color = clWhite;
	FormR->Image1->Canvas->Pen->Color = clWhite;
	FormR->Image1->Canvas->Rectangle(0, 0, FormR->Image1->Width, FormR->Image1->Height);
	FormR->Image1->Canvas->Pen->Color = clBlack;
	FormR->Image1->Picture->Bitmap->Height = FormR->Image1->Height;
	FormR->Image1->Picture->Bitmap->Width = FormR->Image1->Width;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int crearArrayEntradas(AnsiString s, Entrada *E, int lonE)
{
	for(int i = 1; i <= s.Length(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//
		// AnsiString term=s.SubString(i,s.Length ()-i+1); con dos caracteres ya sabemos
		// si se trata de una entrada o no.
		//
		AnsiString	term = s.SubString(i, 2);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(esEntrada(term))
		{
			/*~~~~~~~~~~~~*/
			AnsiString	nom;
			/*~~~~~~~~~~~~*/

			nom = getNombreEntrada(s.SubString(i, s.Length() - i + 1));
			if(nom[1] == '~')
			{
				E[lonE] = Entrada(nom.SubString(2, nom.Length() - 1));
				lonE++;
			}

			E[lonE] = Entrada(nom);
			lonE++;

			// EC[lonEC]=nom;//añadimos un nuevo termino de la ecuacion. lonEC++;
			i = i + nom.Length() - 1;	// -1 porque luego ya se le suma uno más dentro del for.
		}
		else
		{
			/*
			 * if (modo==1 &&(AnsiString) s[i]==(AnsiString) "+") nAnd++; else if (modo==2
			 * &&(AnsiString) s[i]==(AnsiString) "*") nOr++; else if (modo==3 &&(AnsiString)
			 * s[i]==(AnsiString) "*" && (AnsiString) s[i-1]==(AnsiString) ")") nNand++; else
			 * if (modo==4 &&(AnsiString) s[i]==(AnsiString) "+" && (AnsiString)
			 * s[i-1]==(AnsiString) ")") nNor++; £
			 * EC[lonEC]=s[i]; lonEC++;
			 */
		}
	}	// end-for
	return lonE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int crearArrayEC(AnsiString s, AnsiString *EC, int lonEC)
{
	for(int i = 1; i <= s.Length(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	term = s.SubString(i, 2);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(esEntrada(term))
		{
			/*~~~~~~~~~~~~*/
			AnsiString	nom;
			/*~~~~~~~~~~~~*/

			nom = getNombreEntrada(s.SubString(i, s.Length() - i + 1));
			EC[lonEC] = nom;			// añadimos un nuevo termino de la ecuacion.
			lonEC++;
			i = i + nom.Length() - 1;	// -1 porque luego ya se le suma uno más dentro del for.
		}
		else
		{
			EC[lonEC] = s[i];
			lonEC++;
		}
	}	// end-for
	return lonEC;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int getNumeroAnds(AnsiString *EC, int lonEC, int modo)
{
	/*~~~~~~~~~*/
	int nAnd = 1;
	/*~~~~~~~~~*/

	for(int i = 0; i < lonEC; i++)
	{
		if(modo == 1 && EC[i] == (AnsiString) "+") nAnd++;
	}

	return nAnd;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int getNumeroOrs(AnsiString *EC, int lonEC, int modo)
{
	/*~~~~~~~~*/
	int nOr = 1;
	/*~~~~~~~~*/

	for(int i = 0; i < lonEC; i++)
	{
		if(modo == 2 && EC[i] == (AnsiString) "*") nOr++;
	}

	return nOr;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int getNumeroNands(AnsiString *EC, int lonEC, int modo)
{
	/*~~~~~~~~~~*/
	int nNand = 1;
	/*~~~~~~~~~~*/

	for(int i = 0; i < lonEC; i++)
	{
		if(modo == 3 && EC[i] == (AnsiString) "*" && EC[i - 1] == (AnsiString) ")") nNand++;
	}

	return nNand;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int getNumeroNors(AnsiString *EC, int lonEC, int modo)
{
	/*~~~~~~~~~*/
	int nNor = 1;
	/*~~~~~~~~~*/

	for(int i = 0; i < lonEC; i++)
	{
		if(modo == 4 && EC[i] == (AnsiString) "+" && EC[i - 1] == (AnsiString) ")") nNor++;
	}

	return nNor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int ordenarEntradas(Entrada *E, int lonE)
{
	for(int j = 0; j <= lonE; j++)
	{
		for(int i = 0; i < lonE - 1; i++)
		{
			if(mayor(E[i].getNombre(), E[i + 1].getNombre()))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	Temp = E[i + 1].getNombre();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				E[i + 1].setNombre(E[i].getNombre());
				E[i].setNombre(Temp);
			}
			else
			{	// HAY Q ELIMINAR LAS ENTRADAS Q SE REPITEN
				if(E[i].getNombre() == E[i + 1].getNombre())
				{
					for(int k = i + 1; k < lonE - 1; k++) E[k].setNombre(E[k + 1].getNombre());
					lonE--;
				}
			}
		}		// End-for2
	}			// end-for1

	// comprobamos que la primera entrada no este repetida.
	if(E[0].getNombre() == E[1].getNombre())
	{
		for(int k = 1; k < lonE - 1; k++) E[k].setNombre(E[k + 1].getNombre());
		lonE--;
	}

	return lonE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void asignarPosicionesAEntradas(Entrada *E, int lonE)
{
	/*~~~~~~~~~*/
	int posX = 0;
	/*~~~~~~~~~*/

	for(int i = 0; i < lonE; i++)
	{
		if(E[i].getNombre()[1] == '~')
		{
			E[i].setx(posX + 20);
			E[i].sety(30);
		}
		else
		{
			posX = posX + 50;
			E[i].setx(posX);
			E[i].sety(20);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void dibujarEntradas(Entrada *E, int lonE)
{
	for(int i = 0; i < lonE; i++)
	{
		if((E[i].getNombre()[1] == '~'))
		{
			E[i].DibujarNot(0);
		}
		else
			E[i].Dibujar(0);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void dibujarCircuito
(
	AnsiString	s,
	Entrada		*E,
	int			lonE,
	AnsiString	*EC,
	int			lonEC,
	int			modo,
	int			nAnd,
	int			nOr,
	int			nNor,
	int			nNand,
	AnsiString	salida,
	Punto		limite
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	*subEC = new AnsiString[s.Length()];
	char		operador;
	Puerta		*P1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// 1: SOP. 2: POS. 3: NAND. 4: NOR.
	switch(modo)
	{
	case 1: P1 = new PuertaAnd[nAnd + 1]; operador = '*'; break;
	case 2: P1 = new PuertaOr[nOr + 1]; operador = '+'; break;
	case 3: P1 = new PuertaNand[nNand + 1]; operador = '*'; break;
	case 4: P1 = new PuertaNor[nNor + 1]; operador = '+'; break;
	}

	/*~~~~~~~~~~~~~~*/
	int nPuerta = 0;	// nºde puerta And
	int lonSubEC = 0;
	int nEntradas = 0;
	/*~~~~~~~~~~~~~~*/

	for(int i = 0; i < lonEC; i++)
	{					// NOS RECORREMOS EC
		if((AnsiString) EC[i] != (AnsiString) ")")
		{
			subEC[lonSubEC] = subEC[lonSubEC] + EC[i];
			lonSubEC++;
			if((AnsiString) EC[i] == (AnsiString) operador) nEntradas++;
		}
		else
		{
			if(modo == 3 || modo == 4) i++;

			/*~~~~~~~~*/
			int pat = 2;
			/*~~~~~~~~*/

			switch(modo)
			{
			case 1:
				if(nPuerta == 0)
					P1[nPuerta] = PuertaAnd(nEntradas + 1, E[lonE - 1].getx() + 20, E[lonE - 1].gety() + 20);
				else
				{
					P1[nPuerta] = PuertaAnd
						(
							nEntradas + 1,
							E[lonE - 1].getx() + 20,
							P1[nPuerta - 1].Patita[0].y + (P1[nPuerta - 1].getN() + 1) * 10 + 10
						);
				}
				break;
			case 2:
				if(nPuerta == 0)
					P1[nPuerta] = PuertaOr(nEntradas + 1, E[lonE - 1].getx() + 20, E[lonE - 1].gety() + 20);
				else
				{
					P1[nPuerta] = PuertaOr
						(
							nEntradas + 1,
							E[lonE - 1].getx() + 20,
							P1[nPuerta - 1].Patita[0].y + (P1[nPuerta - 1].getN() + 1) * 10 + 10
						);
				}
				break;
			case 3:
				if(nPuerta == 0)
					P1[nPuerta] = PuertaNand(nEntradas + 1, E[lonE - 1].getx() + 20, E[lonE - 1].gety() + 20);
				else
				{
					P1[nPuerta] = PuertaNand
						(
							nEntradas + 1,
							E[lonE - 1].getx() + 20,
							P1[nPuerta - 1].Patita[0].y + (P1[nPuerta - 1].getN() + 1) * 10 + 10
						);
				}
				break;
			case 4:
				if(nPuerta == 0)
					P1[nPuerta] = PuertaNor(nEntradas + 1, E[lonE - 1].getx() + 20, E[lonE - 1].gety() + 20);
				else
				{
					P1[nPuerta] = PuertaNor
						(
							nEntradas + 1,
							E[lonE - 1].getx() + 20,
							P1[nPuerta - 1].Patita[0].y + (P1[nPuerta - 1].getN() + 1) * 10 + 10
						);
				}
				break;
			}

			for(int j = 0; j < lonSubEC; j++)
			{			// NOS RECORREMOS subEC PARA PINTAR
				for(int k = 0; k < lonE; k++)
				{
					if(E[k].getNombre() == subEC[j])
					{
						P1[nPuerta].Dibujar();
						E[k].Unir(P1[nPuerta].Patita[pat].x, P1[nPuerta].Patita[pat].y);
						pat++;
						break;
					}	// end-if
				}		// end-for3
				subEC[j] = "";
			}			// for2
			nPuerta++;
			lonSubEC = 0;
			nEntradas = 0;
		}				// end-else
	}					// for1

	// DIBUJAR LA PUERTA DEL SEGUNDO NIVEL: P2
	if(nPuerta > 1)
	{
		if(salidaNegada(s))
			nPuerta--;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		// nPuerta=2;
		int		y1 = (P1[0].Patita[0].y) +
			(
				((P1[nPuerta - 1].Patita[0].y + (P1[nPuerta - 1].getN() + 1) * 10) - (P1[0].Patita[0].y)) / 2 -
					(nPuerta + 1) * 5
			);
		int		x1 = P1[0].Patita[1].x + (P1[nPuerta - 1].Patita[1].y - P1[0].Patita[1].y) * 2 / nPuerta;
		Puerta	*P2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch(modo)
		{
		case 1:
			P2 = new PuertaOr
				(
					nPuerta,
					P1[0].Patita[1].x + (P1[nPuerta - 1].Patita[1].y - P1[0].Patita[1].y) * 2 / nPuerta,
					y1
				);
			break;
		case 2:
			P2 = new PuertaAnd
				(
					nPuerta,
					P1[0].Patita[1].x + (P1[nPuerta - 1].Patita[1].y - P1[0].Patita[1].y) * 2 / nPuerta,
					y1
				);
			break;
		case 3:
			P2 = new PuertaNand
				(
					nPuerta,
					P1[0].Patita[1].x + (P1[nPuerta - 1].Patita[1].y - P1[0].Patita[1].y) * 2 / nPuerta,
					y1
				);
			break;
		case 4:
			P2 = new PuertaNor(nPuerta, x1, y1);
			break;
		}

		P2->Dibujar();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Punto	*Patita = new Punto[nPuerta];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int i = 0; i < nPuerta; i++)
		{
			Patita[i] = Punto(P1[i].Patita[1].x, P1[i].Patita[1].y);
		}

		P2->Unir(Patita);

		//
		// si la salida está negada dibujamos una puerta de dos entradas para
		// representarlo.
		//
		if(salidaNegada(s))
		{
			/*~~~~~~~~*/
			Puerta	*P3;
			/*~~~~~~~~*/

			switch(modo)
			{
			case 3: P3 = new PuertaNand(2, P2->Patita[0].x + 45, P2->Patita[0].y); break;
			case 4: P3 = new PuertaNor(2, P2->Patita[0].x + 45, P2->Patita[0].y); break;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Punto	*Punto1 = new Punto[2];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			Punto1[0] = Punto(P2->Patita[1].x, P2->Patita[1].y);
			Punto1[1] = Punto(P2->Patita[1].x, P2->Patita[1].y);
			P3->Dibujar();
			P3->Unir(Punto1);
			FormR->Image1->Canvas->TextOut(P3->Patita[1].x + 5, P3->Patita[1].y - 5, salida);
			limite.x = P3->Patita[1].x + 20;
			limite.y = P1[nPuerta - 1].Patita[P1[nPuerta - 1].getN() + 1].y + 20;
		}
		else
		{
			FormR->Image1->Canvas->TextOut(P2->Patita[1].x + 5, P2->Patita[1].y - 5, salida);
			limite.x = P2->Patita[1].x + 20;
			limite.y = P1[nPuerta - 1].Patita[P1[nPuerta - 1].getN() + 1].y + 20;
		}				// else
		// delete[] Patita;
	}
	else if(nPuerta == 1)
	{
		FormR->Image1->Canvas->MoveTo(P1[0].Patita[1].x, P1[0].Patita[1].y);
		FormR->Image1->Canvas->LineTo(P1[0].Patita[1].x + 15, P1[0].Patita[1].y);
		FormR->Image1->Canvas->TextOut(P1[0].Patita[1].x + 20, P1[0].Patita[1].y - 5, salida);
		limite.x = P1[0].Patita[1].x + 30;
		limite.y = P1[0].Patita[P1[0].getN() + 1].y + 20;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	ecuacion = salida + "=" + s;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	FormR->Image1->Canvas->Font->Size = 13;
	FormR->Image1->Canvas->Font->Size = 8;

	// delete[] subEC; delete[] P1;
}
