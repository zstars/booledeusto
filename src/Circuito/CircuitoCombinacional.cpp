/*$T boole/Circuito/CircuitoCombinacional.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "CircuitoCombinacional.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
CircuitoCombinacional::CircuitoCombinacional(AnsiString s1)
{
	s = s1.SubString(s1.Pos("=") + 1, s1.Length());

	//
	// AEntradas=new Entrada [s1.Length ()]; EC=new AnsiString [s1.Length ()];
	// AEntradas=new Entrada [80]; int x=s1.Length ()/2;
	//
	E2 = new Entrada[s1.Length() + 10];
	lonE2 = 0;	// Longitud del array de Entradas

	// EC=new AnsiString [200];
	lonE = 0;	// Longitud del array de Entradas
	lonEC = 0;	// Longitud del array de terminos de la ecuacion.
	modo = Modo(s);
	salida.nombre = s1.SubString(1, s1.Pos("=") - 1);
	if(salida.nombre.IsEmpty()) salida.nombre = "S";
	limite = Punto(0, 0);
	nAnd = 1;
	nOr = 1;
	nNand = 1;
	nNor = 1;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CircuitoCombinacional::~CircuitoCombinacional(void)
{
	delete[] AEntradas;
	delete[] EC;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::crearArrayEntradas(void)
{
	lonE = 0;
	for(int i = 1; i <= s.Length(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		// con dos caracteres ya sabemos si se trata de una entrada o no.
		AnsiString	term = s.SubString(i, 2);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(esEntrada(term))
		{
			/*~~~~~~~~~~~~*/
			// if (existeEntrada (term)==false){
			AnsiString	nom;
			/*~~~~~~~~~~~~*/

			nom = getNombreEntrada(s.SubString(i, s.Length() - i + 1));
			if(nom[1] == '~')
			{
				E2[lonE2] = Entrada(nom.SubString(2, nom.Length() - 1));
				lonE2++;
			}

			E2[lonE2] = Entrada(nom);
			lonE2++;
			i = i + nom.Length() - 1;	// -1 porque luego ya se le suma uno más dentro del for.
			// }//end-if.
		}
		else
		{
			if(modo == 1 && (AnsiString) s[i] == (AnsiString) "+")
				nAnd++;
			else if(modo == 2 && (AnsiString) s[i] == (AnsiString) "*")
				nOr++;
			else if(modo == 3 && (AnsiString) s[i] == (AnsiString) "*" && (AnsiString) s[i - 1] == (AnsiString) ")")
				nNand++;
			else if(modo == 4 && (AnsiString) s[i] == (AnsiString) "+" && (AnsiString) s[i - 1] == (AnsiString) ")")
				nNor++;
		}	// end-else.
	}		// end-for
	eliminarEntradasRepetidas();
}	// end de crear array de entradas.

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::eliminarEntradasRepetidas(void)
{
	/*~~~~~~~~~~~~~~*/
	int		lonE3 = 0;
	Entrada *E3;
	/*~~~~~~~~~~~~~~*/

	E3 = new Entrada[40];
	for(int i = 0; i < lonE2; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~*/
		bool	yaExiste = false;
		/*~~~~~~~~~~~~~~~~~~~~~*/

		for(int k = 0; k < lonE3; k++)
			if(E2[i].getNombre() == E3[k].getNombre())
			{
				yaExiste = true;
				break;
			}

		if(yaExiste == false)
		{
			E3[lonE3] = E2[i];
			lonE3++;
		}
	}

	lonE = lonE3;

	//
	// se añaden dos posiciones de más al array de entradas AEntradas para que en caso
	// de que se trate de un circuito secuencial se puedan meter dos entradas más (CLK
	// y RESET).
	//
	AEntradas = new Entrada[lonE + 2];
	for(int i = 0; i < lonE; i++) AEntradas[i] = E3[i];

	// delete[] E3; delete[] E2;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::agregarEntrada(AnsiString nombre)
{
	AEntradas[lonE] = Entrada(nombre);
	lonE++;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::crearArrayEC(void)
{
	// delete[] EC;
	EC = new AnsiString[s.Length()];

	// EC=new AnsiString [s.Length ()];
	lonEC = 0;
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
			EC[lonEC] = nom;			// aniadimos un nuevo termino de la ecuacion.
			lonEC++;
			i = i + nom.Length() - 1;	// -1 porque luego ya se le suma uno más dentro del for.
		}
		else
		{
			EC[lonEC] = s[i];
			lonEC++;
		}
	}	// end-for
}	// end de crearArrayEC.

//
// =======================================================================================================================
//    HAY QUE MEJORARLO (A VECES REPITE LA PRIMERA ENTRADA.
// =======================================================================================================================
//
void CircuitoCombinacional::ordenarEntradas(void)
{
	for(int j = 0; j <= lonE; j++)
	{
		for(int i = 0; i < lonE - 1; i++)
		{
			if(mayor(AEntradas[i].getNombre(), AEntradas[i + 1].getNombre()))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	Temp = AEntradas[i + 1].getNombre();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				AEntradas[i + 1].setNombre(AEntradas[i].getNombre());
				AEntradas[i].setNombre(Temp);
			}	/* else { //HAY Q ELIMINAR LAS ENTRADAS Q SE REPITEN if (AEntradas[i].getNombre
				 *
				 *
				 * ()==AEntradas[i+1].getNombre()){ for (int k=i+1;k<lonE-1;k++) AEntradas[k].setNombre
				 *
				 *
				 * (AEntradas[k+1].getNombre ()); lonE--; } } */
		}		// End-for2
	}			// end-for1
	//
	// comprobamos que la primera entrada no este repetida.
	// if (AEntradas[0].getNombre ()==AEntradas[1].getNombre ()){ for (int
	// k=1;k<lonE-1;k++) AEntradas[k].setNombre (AEntradas[k+1].getNombre ()); lonE--;
	// }//end-if
	//
}	// end de ordenar entradas.

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::asignarPosicionesAEntradas(int x, int y)
{
	for(int i = 0; i < lonE; i++)
	{
		if(AEntradas[i].getNombre()[1] == '~')
		{
			AEntradas[i].setx(x + 20);
			AEntradas[i].sety(y + 10);
		}
		else
		{
			x = x + 50;
			AEntradas[i].setx(x);
			AEntradas[i].sety(y);
		}
	}
}	// end de asignarPosicionesAEntradas.

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::dibujarEntradas(int altura)
{
	for(int i = 0; i < lonE; i++)
	{
		if((AEntradas[i].getNombre()[1] == '~'))
			AEntradas[i].DibujarNot(altura);
		else
			AEntradas[i].Dibujar(altura);
	}

	limite.x = AEntradas[lonE - 1].getx() + 10;
	limite.y = AEntradas[lonE - 1].gety() + 20;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::dibujarCircuitoCombinacional(int desplazamientoX)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	*subEC = new AnsiString[s.Length()];
	char		operador;
	Puerta		*P1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(modo)
	{
	// 1: SOP.
	case 1: P1 = new PuertaAnd[nAnd + 1]; operador = '*'; break;

	// 2: POS.
	case 2: P1 = new PuertaOr[nOr + 1]; operador = '+'; break;

	// 3: NAND.
	case 3: P1 = new PuertaNand[nNand + 1]; operador = '*'; break;

	// 4: NOR.
	case 4: P1 = new PuertaNor[nNor + 1]; operador = '+'; break;
	}

	/*~~~~~~~~~~~~~~*/
	// end-switch.

	int np = 0; // nºde puerta And
	int lonSubEC = 0;
	int nEntradas = 0;
	/*~~~~~~~~~~~~~~*/

	// se recorre EC.
	for(int i = 0; i < lonEC; i++)
	{
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
			int pat = 2;	// la patita 2 es la primera entrada.
			//~~~~~~~~

			switch(modo)
			{
			case 1: P1[np] = PuertaAnd(nEntradas + 1, desplazamientoX, limite.y); break;
			case 2: P1[np] = PuertaOr(nEntradas + 1, desplazamientoX, limite.y); break;
			case 3: P1[np] = PuertaNand(nEntradas + 1, desplazamientoX, limite.y); break;
			case 4: P1[np] = PuertaNor(nEntradas + 1, desplazamientoX, limite.y); break;
			}

			// se dibuja una puerta y se une a sus correspondientes entradas.
			for(int j = 0; j < lonSubEC; j++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~*/
				bool	encontrada = false;
				int		k = 0;
				/*~~~~~~~~~~~~~~~~~~~~~~~*/

				while(encontrada == false && k < lonE)
				{
					if(AEntradas[k].getNombre() == subEC[j])
					{
						P1[np].Dibujar();

						// AQUI FALLA: UNIR
						AEntradas[k].Unir(P1[np].Patita[pat].x, P1[np].Patita[pat].y);
						pat++;
						encontrada = true;
					}		// end-if
					k++;
				}			// end-while
				subEC[j] = "";
			}				// for2
			limite.x = P1[np].Patita[pat - 1].x + 5;
			limite.y = P1[np].Patita[pat - 1].y + 15;
			np++;
			lonSubEC = 0;
			nEntradas = 0;
		}					// end-else
	}						// end-for1

	// DIBUJAR LA PUERTA DEL SEGUNDO NIVEL: P2
	if(np > 1)
	{
		if(salidaNegada(s))
			np--;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int		y1 = (P1[0].Patita[0].y) + (((P1[np - 1].Patita[0].y + (P1[np - 1].getN() + 1) * 10) - (P1[0].Patita[0].y)) / 2 - (np + 1) * 5);
		int		x1 = P1[0].Patita[1].x + (P1[np - 1].Patita[1].y - P1[0].Patita[1].y) * 2 / np;
		Puerta	*P2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch(modo)
		{
		case 1: P2 = new PuertaOr(np, x1, y1); break;
		case 2: P2 = new PuertaAnd(np, x1, y1); break;
		case 3: P2 = new PuertaNand(np, x1, y1); break;
		case 4: P2 = new PuertaNor(np, x1, y1); break;
		}					// end-switch.
		P2->Dibujar();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Punto	*Patita = new Punto[np];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int i = 0; i < np; i++) Patita[i] = Punto(P1[i].Patita[1].x, P1[i].Patita[1].y);
		P2->Unir(Patita);

		//
		// delete[] Patita; si la salida está negada dibujamos una puerta de dos entradas
		// para representarlo.
		//
		if(salidaNegada(s))
		{
			/*~~~~~~~~*/
			Puerta	*P3;
			/*~~~~~~~~*/

			switch(modo)
			{
			case 3: P3 = new PuertaNand(2, P2->Patita[1].x + 5, P2->Patita[1].y - 15); break;
			case 4: P3 = new PuertaNor(2, P2->Patita[1].x + 5, P2->Patita[1].y - 15); break;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Punto	*Punto1 = new Punto[2];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			Punto1[0] = Punto(P2->Patita[1].x, P2->Patita[1].y);
			Punto1[1] = Punto(P2->Patita[1].x, P2->Patita[1].y);
			P3->Dibujar();
			P3->Unir(Punto1);

			// se guarda la posición de la salida del circuito.
			salida.x = P3->Patita[1].x;
			salida.y = P3->Patita[1].y;

			// se guarda lo que ocupa el dibujo del circuito en pantalla.
			tamanio.x = P3->Patita[1].x + 40;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int ultimaEntrada = P1[np - 1].getN() + 1;	// última entrada de la puerta.
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			tamanio.y = P1[np - 1].Patita[ultimaEntrada].y + 20;

			// delete[] P1; delete P2; delete P3;
		}
		else
		{
			// se guarda la posición de la salida del circuito.
			salida.x = P2->Patita[1].x;
			salida.y = P2->Patita[1].y;

			// se guarda lo que ocupa el dibujo del circuito en pantalla.
			tamanio.x = P2->Patita[1].x + 40;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int ultimaEntrada = P1[np - 1].getN() + 1;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tamanio.y = P1[np - 1].Patita[ultimaEntrada].y + 20;

			// delete[] P1; delete P2;
		}	// end-else
	}
	else if(np == 1)
	{
		FormR->Image1->Canvas->MoveTo(P1[0].Patita[1].x, P1[0].Patita[1].y);
		FormR->Image1->Canvas->LineTo(P1[0].Patita[1].x + 5, P1[0].Patita[1].y);

		// se guarda la posición de la salida del circuito.
		salida.x = P1[0].Patita[1].x + 5;
		salida.y = P1[0].Patita[1].y;
		tamanio.x = P1[0].Patita[1].x + 40;
		tamanio.y = P1[0].Patita[P1[0].getN() + 1].y + 20;

		// delete[] P1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// end-if.

	AnsiString	ecuacion = salida.nombre + "=" + s;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	FormR->Image1->Hint = ecuacion;

	// delete[] subEC;
}	// end de dibujarCircuitoCombinacional.

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoCombinacional::dibujarSalida(void)
{
	FormR->Image1->Canvas->TextOut(salida.x + 5, salida.y - 5, salida.nombre);
}
