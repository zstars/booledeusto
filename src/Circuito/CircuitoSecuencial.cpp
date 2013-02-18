/*$T boole/Circuito/CircuitoSecuencial.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "CircuitoSecuencial.h"
#include "Unit10.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
CircuitoSecuencial::CircuitoSecuencial(TListBox *Lista1, int longitudLista, bool tipoFlipFlops1)
{
	//
	// if (tipoFlipFlops==true) numeroFlipFlops=(longitudLista)/2;//numero de
	// FlipFlops JK. else
	//
	numeroFlipFlops = (longitudLista);	// numero de FlipFlops D.
	Lista = Lista1;
	tipoFlipFlops = tipoFlipFlops1;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CircuitoSecuencial::~CircuitoSecuencial(void)
{
	salida->~CircuitoCombinacional();
	CC->~CircuitoCombinacional();

	// Error: falla el destructor de CC.
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CircuitoSecuencial::dibujarCircuitoSecuencial(void)
{
	if(tipoFlipFlops == true)
	{	// CON FLIP-FLOPS JK.

		numeroFlipFlops = (numeroFlipFlops) / 2;

		/*~~~~~~~~~~*/
		// numero de FlipFlops JK.

		// se crea un string con todos los simbolos de todas las ecuaciones.
		AnsiString	s;
		/*~~~~~~~~~~*/

		for(int k = 0; k < (numeroFlipFlops * 2); k++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	sub = Lista->Items->Strings[k];
			AnsiString	derecha = sub.SubString(sub.Pos("=") + 1, sub.Length());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			s = s + derecha;
		}

		for(int i = 0; i < Form10->ListaSol->Items->Count; i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	sub = Form10->ListaSol->Items->Strings[i];
			AnsiString	derecha = sub.SubString(sub.Pos("=") + 1, sub.Length());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			s = s + derecha;
		}

		/*~~~~~~~~~~~*/
		AnsiString	s2;
		/*~~~~~~~~~~~*/

		for(int k = 1; k <= s.Length(); k++)
		{
			if(esEntrada(s[k])) s2 = s2 + s[k];
		}

		CC = new CircuitoCombinacional(s);

		CC->crearArrayEntradas();
		CC->ordenarEntradas();
		CC->agregarEntrada("CLK");
		CC->agregarEntrada("RESET");

		CC->asignarPosicionesAEntradas(0, 20);
		CC->dibujarEntradas(numeroFlipFlops * 10);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//
		// se crea un array de puntos para guardar las posiciones de las salidas de cada
		// circuito combinacional más pequeño que forman el secuencial.
		//
		Punto	*salidasCC = new Punto[numeroFlipFlops * 2];
		int		xMaxima = 0;	// aquí se guarda la posición X de la salida más más lejana.
		int		desplazamiento = CC->getLimite().x + 30;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		//
		// con este for se dibujan todos los circuitos combinacionales que serán las
		// entradas de los flip-flops.
		//
		for(int k = 0; k < numeroFlipFlops * 2; k++)
		{
			CC->s = FormR->Lista->Items->Strings[k];
			CC->s = CC->s.SubString(CC->s.Pos("=") + 1, CC->s.Length());

			// ENTRANDO POR AQUI CON K=7 FALLA. CC->crearArrayEntradas ();
			CC->modo = 1;
			CC->crearArrayEC();

			CC->dibujarCircuitoCombinacional(desplazamiento);
			CC->limite.y += 10;
			salidasCC[k].x = CC->salida.x;
			salidasCC[k].y = CC->salida.y;
			if(CC->salida.x > xMaxima) xMaxima = CC->salida.x;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		FlipFlopJK	*flipflop = new FlipFlopJK[numeroFlipFlops];	// se crea un array de flip-flops.
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//
		// FlipFlopJK *flipflop [100]; FlipFlop* flipflop; if (tipoFlipFlops==true)
		// flipflop=new FlipFlopJK [numeroFlipFlops]; //se crea un array de flip-flops.
		// else flipflop=new FlipFlopD [numeroFlipFlops]; //se crea un array de
		// flip-flops.
		// aquí se alinean las salidas de los circuitos combinacionales para que queden
		// todas a la misma altura.
		//
		for(int k = 0; k < numeroFlipFlops * 2; k++)
		{
			if(salidasCC[k].x < xMaxima)
			{
				FormR->Image1->Canvas->MoveTo(salidasCC[k].x, salidasCC[k].y);
				FormR->Image1->Canvas->LineTo(xMaxima, salidasCC[k].y);
				salidasCC[k].x = xMaxima;
			}
		}

		/*~~~~~~~~~*/
		int nSal = 0;
		/*~~~~~~~~~*/

		//
		// con este for se dibujan los flip-flops y se unen sus salidas a las entradas del
		// circuito secuencial.
		//
		for(int k = 0; k < numeroFlipFlops; k++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int x1 = salidasCC[nSal].x + 40;
			int y1 = salidasCC[nSal].y + (salidasCC[nSal + 1].y - salidasCC[nSal].y) / 2;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			// if (tipoFlipFlops==true)
			flipflop[k] = FlipFlopJK(k, x1, y1);

			// else flipflop[k]=FlipFlopD (k,x1,y1);
			flipflop[k].Dibujar();
			if(tipoFlipFlops == true)
			{
				flipflop[k].UnirJ(salidasCC[nSal].x, salidasCC[nSal].y);
				flipflop[k].UnirK(salidasCC[nSal + 1].x, salidasCC[nSal + 1].y);
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			// else flipflop[k].UnirD (salidasCC[nSal].x,salidasCC[nSal].y);
			int ultimaEntrada = CC->getLonE() - 1;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			flipflop[k].UnirCLK(CC->AEntradas[ultimaEntrada - 1].getx(), CC->AEntradas[ultimaEntrada - 1].gety());
			flipflop[k].UnirRESET(CC->AEntradas[ultimaEntrada].getx(), CC->AEntradas[ultimaEntrada].gety());

			nSal += 2;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			// llevamos las salidas de los flip-flops hacia arriba.
			bool	encontrada = false;
			int		l = 0;
			int		lonE = CC->getLonE();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			while(encontrada == false && l < lonE)
			{
				if(CC->AEntradas[l].getNombre() == flipflop[k].Q.nombre) encontrada = true;
				l++;
			}

			if(encontrada == true) flipflop[k].UnirQ(CC->AEntradas[l - 1].getx(), numeroFlipFlops, k);
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// end-for.

		// ahora se dibuja la salida.
		AnsiString	EcuacionSalida; // ="Salida=(Entrada2*~Entrada1)";
		//~~~~~~~~~~~~~~~~~~~~~~~

		if(FormR->solucionNum < 0)
		{
			FormR->solucionNum = 0;
			EcuacionSalida = FormR->ListaSol->Items->Strings[FormR->solucionNum];
		}
		else
			EcuacionSalida = FormR->ListaSol->Items->Strings[FormR->solucionNum];

		//
		// creamos un nuevo circuito combinacional llamado "salida" que nos va a
		// proporcionar la salida del Sistema Secuencial.
		//
		salida = new CircuitoCombinacional(EcuacionSalida);

		salida->crearArrayEntradas();
		salida->ordenarEntradas();
		salida->modo = 1;
		salida->crearArrayEC();

		//
		// asignamos las posiciones de las entradas que van a ser las salidas de los
		// flip-flops.
		//
		for(int i = 0; i < salida->getLonE(); i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			bool	encontrada = false;
			int		l = 0;
			Punto	posicion = Punto(0, 0);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			while(encontrada == false && l < numeroFlipFlops)
			{
				if(salida->AEntradas[i].getNombre() == flipflop[l].Q.nombre)
				{
					encontrada = true;

					// FormR->Image1->Canvas->MoveTo (flipflop[l].Q.x,flipflop[l].Q.y);
					posicion = Punto(flipflop[l].Q.x, flipflop[l].Q.y);

					// flipflop[l].Q.x+=(l)*10; FormR->Image1->Canvas->LineTo (posicion.x,posicion.y);
				}
				else if(salida->AEntradas[i].getNombre() == flipflop[l].NQ.nombre)
				{
					encontrada = true;
					FormR->Image1->Canvas->MoveTo(flipflop[l].NQ.x, flipflop[l].NQ.y);

					//
					// posicion.x depende del numero de flip-flops que haya en el circuito (a mayor nº
					// más a la derecha estará la linea.
					//
					posicion = Punto(flipflop[l].NQ.x + (numeroFlipFlops) * 10 + (l + 1) * 10, flipflop[l].NQ.y);
					flipflop[l].NQ.x += (numeroFlipFlops) * 10 + (l + 1) * 10;
					FormR->Image1->Canvas->LineTo(posicion.x, posicion.y);
				}

				l++;
			}

			//
			// si no se ha encontrado la entrada a la puerta en ninguna de las salidas de los
			// flip-flops significa que es la entrada del sistema por lo que la buscaremos en
			// las entradas del Circuito secuencial.
			//
			if(encontrada == false)
			{
				l = 0;

				/*~~~~~~~~~~~~~~~~~~~~~*/
				int lonE = CC->getLonE();
				/*~~~~~~~~~~~~~~~~~~~~~*/

				while(encontrada == false && l < lonE)
				{
					if(salida->AEntradas[i].getNombre() == CC->AEntradas[l].getNombre()) encontrada = true;
					l++;
				}

				posicion.x = CC->AEntradas[l - 1].getx();
				posicion.y = CC->AEntradas[l - 1].gety();
			}						// end-if
			salida->AEntradas[i].setx(posicion.x);
			salida->AEntradas[i].sety(posicion.y);
		}						// end-for.

		salida->limite.y = CC->limite.y - 15;

		//
		// el desplazamiento con el que se va dibujar el Circuito Combinacional de salida,
		// dependerá de la posición de la linea de salida negada del último flip-flop.
		//
		desplazamiento = flipflop[numeroFlipFlops - 1].NQ.x + (numeroFlipFlops) * 20;
		salida->dibujarCircuitoCombinacional(desplazamiento);
		salida->dibujarSalida();
		salida->salida.nombre = Lista->Items->Strings[numeroFlipFlops * 2 - 1];

		//
		// delete[] salida->AEntradas; delete[] salida->EC; delete[] CC->AEntradas;
		// delete[] CC->EC;
		// FormR->E1->Text=flipflop[0].Q.nombre; FormR->E2->Text=flipflop[1].Q.nombre;
		//
		salida->~CircuitoCombinacional();

		// CC->~CircuitoCombinacional();
		delete[] flipflop;
	}
	else
	{							// CON FLIP-FLOPS D.

		numeroFlipFlops = (numeroFlipFlops);

		/*~~~~~~~~~~*/
		// numero de FlipFlops D.

		// se crea un string con todos los simbolos de todas las ecuaciones.
		AnsiString	s;
		/*~~~~~~~~~~*/

		for(int k = 0; k < (numeroFlipFlops); k++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	sub = Lista->Items->Strings[k];
			AnsiString	derecha = sub.SubString(sub.Pos("=") + 1, sub.Length());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			s = s + derecha;
		}

		for(int i = 0; i < Form10->ListaSol->Items->Count; i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	sub = Form10->ListaSol->Items->Strings[i];
			AnsiString	derecha = sub.SubString(sub.Pos("=") + 1, sub.Length());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			s = s + derecha;
		}

		/*~~~~~~~~~~~*/
		AnsiString	s2;
		/*~~~~~~~~~~~*/

		for(int k = 1; k <= s.Length(); k++)
		{
			if(esEntrada(s[k])) s2 = s2 + s[k];
		}

		CC = new CircuitoCombinacional(s);

		CC->crearArrayEntradas();
		CC->ordenarEntradas();
		CC->agregarEntrada("CLK");
		CC->agregarEntrada("RESET");

		CC->asignarPosicionesAEntradas(0, 20);
		CC->dibujarEntradas(numeroFlipFlops * 10);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//
		// se crea un array de puntos para guardar las posiciones de las salidas de cada
		// circuito combinacional más pequeño que forman el secuencial.
		//
		Punto	*salidasCC = new Punto[numeroFlipFlops];
		int		xMaxima = 0;	// aquí se guarda la posición X de la salida más más lejana.
		int		desplazamiento = CC->getLimite().x + 30;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		//
		// con este for se dibujan todos los circuitos combinacionales que serán las
		// entradas de los flip-flops.
		//
		for(int k = 0; k < numeroFlipFlops; k++)
		{
			CC->s = FormR->Lista->Items->Strings[k];
			CC->s = CC->s.SubString(CC->s.Pos("=") + 1, CC->s.Length());

			// ENTRANDO POR AQUI CON K=7 FALLA. CC->crearArrayEntradas ();
			CC->modo = 1;
			CC->crearArrayEC();

			CC->dibujarCircuitoCombinacional(desplazamiento);
			CC->limite.y += 10;
			salidasCC[k].x = CC->salida.x;
			salidasCC[k].y = CC->salida.y;
			if(CC->salida.x > xMaxima) xMaxima = CC->salida.x;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		FlipFlopD	*flipflop = new FlipFlopD[numeroFlipFlops]; // se crea un array de flip-flops.
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//
		// FlipFlopJK *flipflop [100]; FlipFlop* flipflop; if (tipoFlipFlops==true)
		// flipflop=new FlipFlopJK [numeroFlipFlops]; //se crea un array de flip-flops.
		// else flipflop=new FlipFlopD [numeroFlipFlops]; //se crea un array de
		// flip-flops.
		// aquí se alinean las salidas de los circuitos combinacionales para que queden
		// todas a la misma altura.
		//
		for(int k = 0; k < numeroFlipFlops; k++)
		{
			if(salidasCC[k].x < xMaxima)
			{
				FormR->Image1->Canvas->MoveTo(salidasCC[k].x, salidasCC[k].y);
				FormR->Image1->Canvas->LineTo(xMaxima, salidasCC[k].y);
				salidasCC[k].x = xMaxima;
			}
		}

		/*~~~~~~~~~*/
		int nSal = 0;
		/*~~~~~~~~~*/

		//
		// con este for se dibujan los flip-flops y se unen sus salidas a las entradas del
		// circuito secuencial.
		//
		for(int k = 0; k < numeroFlipFlops; k++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int x1 = salidasCC[nSal].x + 40;
			int y1 = salidasCC[nSal].y + 15;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			// if (tipoFlipFlops==true) flipflop[k]= FlipFlopJK (k,x1,y1); else
			flipflop[k] = FlipFlopD(k, x1, y1);

			flipflop[k].Dibujar();

			// if (tipoFlipFlops==true){
			flipflop[k].UnirD(salidasCC[nSal].x, salidasCC[nSal].y);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			//
			// flipflop[k].UnirK (salidasCC[nSal+1].x,salidasCC[nSal+1].y); } //else
			// flipflop[k].UnirD (salidasCC[nSal].x,salidasCC[nSal].y);
			//
			int ultimaEntrada = CC->getLonE() - 1;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			flipflop[k].UnirCLK(CC->AEntradas[ultimaEntrada - 1].getx(), CC->AEntradas[ultimaEntrada - 1].gety());
			flipflop[k].UnirRESET(CC->AEntradas[ultimaEntrada].getx(), CC->AEntradas[ultimaEntrada].gety());

			nSal++;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			// llevamos las salidas de los flip-flops hacia arriba.
			bool	encontrada = false;
			int		l = 0;
			int		lonE = CC->getLonE();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			while(encontrada == false && l < lonE)
			{
				if(CC->AEntradas[l].getNombre() == flipflop[k].Q.nombre) encontrada = true;
				l++;
			}

			if(encontrada == true) flipflop[k].UnirQ(CC->AEntradas[l - 1].getx(), numeroFlipFlops, k);
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// end-for.

		// ahora se dibuja la salida.
		AnsiString	EcuacionSalida; // ="Salida=(Entrada2*~Entrada1)";
		//~~~~~~~~~~~~~~~~~~~~~~~

		if(FormR->solucionNum < 0)
			EcuacionSalida = FormR->ListaSol->Items->Strings[0];
		else
			EcuacionSalida = FormR->ListaSol->Items->Strings[FormR->solucionNum];

		//
		// creamos un nuevo circuito combinacional llamado "salida" que nos va a
		// proporcionar la salida del Sistema Secuencial.
		//
		salida = new CircuitoCombinacional(EcuacionSalida);

		salida->crearArrayEntradas();
		salida->ordenarEntradas();
		salida->modo = 1;
		salida->crearArrayEC();

		//
		// asignamos las posiciones de las entradas que van a ser las salidas de los
		// flip-flops.
		//
		for(int i = 0; i < salida->getLonE(); i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			bool	encontrada = false;
			int		l = 0;
			Punto	posicion = Punto(0, 0);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			while(encontrada == false && l < numeroFlipFlops)
			{
				if(salida->AEntradas[i].getNombre() == flipflop[l].Q.nombre)
				{
					encontrada = true;

					// FormR->Image1->Canvas->MoveTo (flipflop[l].Q.x,flipflop[l].Q.y);
					posicion = Punto(flipflop[l].Q.x, flipflop[l].Q.y);

					// flipflop[l].Q.x+=(l)*10; FormR->Image1->Canvas->LineTo (posicion.x,posicion.y);
				}
				else if(salida->AEntradas[i].getNombre() == flipflop[l].NQ.nombre)
				{
					encontrada = true;
					FormR->Image1->Canvas->MoveTo(flipflop[l].NQ.x, flipflop[l].NQ.y);

					//
					// posicion.x depende del numero de flip-flops que haya en el circuito (a mayor nº
					// más a la derecha estará la linea.
					//
					posicion = Punto(flipflop[l].NQ.x + (numeroFlipFlops) * 10 + (l + 1) * 10, flipflop[l].NQ.y);
					flipflop[l].NQ.x += (numeroFlipFlops) * 10 + (l + 1) * 10;
					FormR->Image1->Canvas->LineTo(posicion.x, posicion.y);
				}

				l++;
			}

			//
			// si no se ha encontrado la entrada a la puerta en ninguna de las salidas de los
			// flip-flops significa que es la entrada del sistema por lo que la buscaremos en
			// las entradas del Circuito secuencial.
			//
			if(encontrada == false)
			{
				l = 0;

				/*~~~~~~~~~~~~~~~~~~~~~*/
				int lonE = CC->getLonE();
				/*~~~~~~~~~~~~~~~~~~~~~*/

				while(encontrada == false && l < lonE)
				{
					if(salida->AEntradas[i].getNombre() == CC->AEntradas[l].getNombre()) encontrada = true;
					l++;
				}

				posicion.x = CC->AEntradas[l - 1].getx();
				posicion.y = CC->AEntradas[l - 1].gety();
			}						// end-if
			salida->AEntradas[i].setx(posicion.x);
			salida->AEntradas[i].sety(posicion.y);
		}	// end-for.

		salida->limite.y = CC->limite.y - 15;

		//
		// el desplazamiento con el que se va dibujar el Circuito Combinacional de salida,
		// dependerá de la posición de la linea de salida negada del último flip-flop.
		//
		desplazamiento = flipflop[numeroFlipFlops - 1].NQ.x + (numeroFlipFlops) * 20;
		salida->dibujarCircuitoCombinacional(desplazamiento);
		salida->dibujarSalida();
		salida->salida.nombre = Lista->Items->Strings[numeroFlipFlops - 1];

		//
		// delete[] salida->AEntradas; delete[] salida->EC; delete[] CC->AEntradas;
		// delete[] CC->EC;
		// FormR->E1->Text=flipflop[0].Q.nombre; FormR->E2->Text=flipflop[1].Q.nombre;
		//
		salida->~CircuitoCombinacional();

		// CC->~CircuitoCombinacional();
		delete[] flipflop;
	}		// end-else.

	/*
	 * ASÍ NO FUNCIONA SE QUEDA COLGADO. //se crea un string con todos los simbolos de
	 * todas las ecuaciones. AnsiString s; for (int k=0;k<(numeroFlipFlops*2);k++){
	 * AnsiString sub=Lista->Items->Strings[k]; AnsiString derecha=sub.SubString
	 * (sub.Pos ("=")+1,sub.Length ()); s=s+derecha; } for (int
	 * i=0;i<Form10->ListaSol->Items->Count;i++){ AnsiString
	 * sub=Form10->ListaSol->Items->Strings[i]; AnsiString derecha=sub.SubString
	 * (sub.Pos ("=")+1,sub.Length ()); s=s+derecha; } AnsiString s2; for (int
	 * k=1;k<=s.Length ();k++){ if (esEntrada (s[k])) s2=s2+s[k]; } CC=new
	 * CircuitoCombinacional (s); CC->crearArrayEntradas (); CC->ordenarEntradas ();
	 * CC->agregarEntrada ("CLK"); CC->agregarEntrada ("RESET");
	 * CC->asignarPosicionesAEntradas (0,20); CC->dibujarEntradas
	 * (numeroFlipFlops*10); //se crea un array de puntos para guardar las posiciones
	 * de las salidas //de cada circuito combinacional más pequeño que forman el
	 * secuencial. Punto* salidasCC=new Punto [numeroFlipFlops*2]; int xMaxima=0;
	 * //aquí se guarda la posición X de la salida más más lejana. int
	 * desplazamiento=CC->getLimite().x+30; //con este for se dibujan todos los
	 * circuitos combinacionales que serán las //entradas de los flip-flops. for (int
	 * k=0;k<numeroFlipFlops*2;k++){ CC->s=FormR->Lista->Items->Strings[k];
	 * CC->s=CC->s.SubString (CC->s.Pos ("=")+1,CC->s.Length ()); //ENTRANDO POR AQUI
	 * CON K=7 FALLA. // CC->crearArrayEntradas (); CC->modo=1; CC->crearArrayEC ();
	 * CC->dibujarCircuitoCombinacional (desplazamiento); CC->limite.y+=10;
	 * salidasCC[k].x=CC->salida.x; salidasCC[k].y=CC->salida.y; if
	 * (CC->salida.x>xMaxima) xMaxima=CC->salida.x; } FlipFlopJK* flipflop=new
	 * FlipFlopJK [numeroFlipFlops]; //se crea un array de flip-flops. //FlipFlopJK
	 * *flipflop [100]; // FlipFlop* flipflop; // if (tipoFlipFlops==true)
	 * flipflop=new FlipFlopJK [numeroFlipFlops]; //se crea un array de flip-flops. //
	 * else flipflop=new FlipFlopD [numeroFlipFlops]; //se crea un array de
	 * flip-flops. //aquí se alinean las salidas de los circuitos combinacionales para
	 * que //queden todas a la misma altura. for (int k=0;k<numeroFlipFlops*2;k++){ if
	 * (salidasCC [k].x<xMaxima){ FormR->Image1->Canvas->MoveTo
	 * (salidasCC[k].x,salidasCC[k].y); FormR->Image1->Canvas->LineTo
	 * (xMaxima,salidasCC[k].y); salidasCC[k].x=xMaxima; } } int nSal=0; //con este
	 * for se dibujan los flip-flops y se unen sus salidas a las //entradas del
	 * circuito secuencial. for (int k=0;k<numeroFlipFlops;k++){ int
	 * x1=salidasCC[nSal].x+40; int
	 * y1=salidasCC[nSal].y+(salidasCC[nSal+1].y-salidasCC[nSal].y)/2; //if
	 * (tipoFlipFlops==true) flipflop[k]= FlipFlopJK (k,x1,y1); //else //
	 * flipflop[k]=FlipFlopD (k,x1,y1); flipflop[k].Dibujar (); if
	 * (tipoFlipFlops==true){ flipflop[k].UnirJ (salidasCC[nSal].x,salidasCC[nSal].y);
	 * flipflop[k].UnirK (salidasCC[nSal+1].x,salidasCC[nSal+1].y); } //else
	 * flipflop[k].UnirD (salidasCC[nSal].x,salidasCC[nSal].y); int
	 * ultimaEntrada=CC->getLonE ()-1; flipflop[k].UnirCLK
	 * (CC->AEntradas[ultimaEntrada-1].getx(),CC->AEntradas[ultimaEntrada-1].gety());
	 * flipflop[k].UnirRESET
	 * (CC->AEntradas[ultimaEntrada].getx(),CC->AEntradas[ultimaEntrada].gety());
	 * nSal+=2; //llevamos las salidas de los flip-flops hacia arriba. bool
	 * encontrada=false; int l=0; int lonE=CC->getLonE(); while (encontrada==false &&
	 * l<lonE) { if (CC->AEntradas[l].getNombre()==flipflop[k].Q.nombre)
	 * encontrada=true; l++; } if (encontrada==true) flipflop[k].UnirQ
	 * (CC->AEntradas[l-1].getx(),numeroFlipFlops,k); }//end-for. //ahora se dibuja la
	 * salida. AnsiString EcuacionSalida;//="Salida=(Entrada2*~Entrada1)"; if
	 * (FormR->solucionNum<0) EcuacionSalida=FormR->ListaSol->Items->Strings[0]; else
	 * EcuacionSalida=FormR->ListaSol->Items->Strings[FormR->solucionNum]; //creamos
	 * un nuevo circuito combinacional llamado "salida" que nos va a //proporcionar la
	 * salida del Sistema Secuencial. salida=new CircuitoCombinacional
	 * (EcuacionSalida); salida->crearArrayEntradas (); salida->ordenarEntradas ();
	 * salida->modo=1; salida->crearArrayEC (); //asignamos las posiciones de las
	 * entradas que van a ser las salidas de //los flip-flops. for (int
	 * i=0;i<salida->getLonE ();i++){ bool encontrada=false; int l=0; Punto
	 * posicion=Punto (0,0); while (encontrada==false && l<numeroFlipFlops) { if
	 * (salida->AEntradas[i].getNombre()==flipflop[l].Q.nombre) { encontrada=true; //
	 * FormR->Image1->Canvas->MoveTo (flipflop[l].Q.x,flipflop[l].Q.y); posicion=Punto
	 * (flipflop[l].Q.x,flipflop[l].Q.y); // flipflop[l].Q.x+=(l)*10; //
	 * FormR->Image1->Canvas->LineTo (posicion.x,posicion.y); }else if
	 * (salida->AEntradas[i].getNombre()==flipflop[l].NQ.nombre) { encontrada=true;
	 * FormR->Image1->Canvas->MoveTo (flipflop[l].NQ.x,flipflop[l].NQ.y); //posicion.x
	 * depende del numero de flip-flops que haya en //el circuito (a mayor nº más a la
	 * derecha estará la linea. posicion=Punto
	 * (flipflop[l].NQ.x+(numeroFlipFlops)*10+(l+1)*10,flipflop[l].NQ.y);
	 * flipflop[l].NQ.x+=(numeroFlipFlops)*10+(l+1)*10; FormR->Image1->Canvas->LineTo
	 * (posicion.x,posicion.y); } l++; } //si no se ha encontrado la entrada a la
	 * puerta en ninguna de las //salidas de los flip-flops significa que es la
	 * entrada del sistema //por lo que la buscaremos en las entradas del Circuito
	 * secuencial. if (encontrada==false){ l=0; int lonE=CC->getLonE(); while
	 * (encontrada==false && l<lonE) { if
	 * (salida->AEntradas[i].getNombre()==CC->AEntradas[l].getNombre())
	 * encontrada=true; l++; } posicion.x=CC->AEntradas[l-1].getx ();
	 * posicion.y=CC->AEntradas[l-1].gety (); }//end-if
	 * salida->AEntradas[i].setx(posicion.x); salida->AEntradas[i].sety(posicion.y);
	 * }//end-for. salida->limite.y=CC->limite.y-15; //el desplazamiento con el que se
	 * va dibujar el Circuito Combinacional //de salida, dependerá de la posición de
	 * la linea de salida negada del //último flip-flop.
	 * desplazamiento=flipflop[numeroFlipFlops-1].NQ.x+(numeroFlipFlops)*20;
	 * salida->dibujarCircuitoCombinacional (desplazamiento); salida->dibujarSalida();
	 * salida->salida.nombre=Lista->Items->Strings[numeroFlipFlops*2-1]; //
	 * FormR->E6->Text=CC->AEntradas[1].getx (); //
	 * FormR->E7->Text=CC->AEntradas[1].gety (); // delete[] salida->AEntradas; //
	 * delete[] salida->EC; // delete[] CC->AEntradas; // delete[] CC->EC; //
	 * FormR->E1->Text=flipflop[0].Q.nombre; // FormR->E2->Text=flipflop[1].Q.nombre;
	 * salida->~CircuitoCombinacional(); // CC->~CircuitoCombinacional(); delete
	 * []flipflop;
	 */
}	// end-dibujarCircuitoSecuencial.
