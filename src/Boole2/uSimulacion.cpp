/*$T boole/Boole2/uSimulacion.cpp GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "uSimulacion.h"
#include "SistemaSecuencial.h"
#include "uLog.h"
#include "V_Boole2.h"
#include "mensajes.inc"
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfSimulacion	*fSimulacion;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TfSimulacion::TfSimulacion(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::gridSimulacionMouseDown
(
	TObject			*Sender,
	TMouseButton	Button,
	TShiftState		Shift,
	int				X,
	int				Y
)
{

  if (Button == mbLeft)
  {
	/*~~~~~~~~~~~~~~~~~~*/
	int			col, row;
	AnsiString	contenido;
	/*~~~~~~~~~~~~~~~~~~*/

	gridSimulacion->MouseToCell(X, Y, col, row);
	if((!pausado && row > 0) || (pausado && row > indiceActual))
	{
		contenido = gridSimulacion->Cells[col][row];

		if(col >= indiceEntInicial && col <= indiceEntFinal)
		{
      if(Form1Boole2->tipoSimulacion == RAPIDA || (gridSimulacion->Cells[indiceRESET][row-1] != "RESET" && gridSimulacion->Cells[indiceCLK][row-1] != "CLK"))
      {
			if(contenido == "1")
				gridSimulacion->Cells[col][row] = AnsiString("0");
			else if(contenido == "0")
				gridSimulacion->Cells[col][row] = AnsiString("1");
      }
		}

		if(col == indiceCLK && Form1Boole2->tipoSimulacion == NORMAL && gridSimulacion->Cells[indiceRESET][row-1] != "RESET" && gridSimulacion->Cells[indiceCLK][row-1] != "CLK" && gridSimulacion->Cells[indiceRESET][row] != "RESET")
		{
			if(contenido == "CLK")
      {
        SuprimirFila(row+1);
        SuprimirFila(row);
      }
			else if(contenido == "")
      {
        for(int i=indiceRESET;i<=gridSimulacion->ColCount;i++)
  				gridSimulacion->Cells[i][row] = AnsiString("");
				gridSimulacion->Cells[col][row] = AnsiString("CLK");
        AnyadirFila(row);
        for(int i=indiceRESET;i<=gridSimulacion->ColCount;i++)
  				gridSimulacion->Cells[i][row+1] = AnsiString("");
        gridSimulacion->Cells[indiceEstado][row+1]="[CLK]";
      }
		}

		if(col == indiceRESET && Form1Boole2->tipoSimulacion == NORMAL && gridSimulacion->Cells[indiceRESET][row-1] != "RESET" && gridSimulacion->Cells[indiceCLK][row-1] != "CLK" && gridSimulacion->Cells[indiceCLK][row] != "CLK")
		{
			if(contenido == "RESET")
      {
        SuprimirFila(row+1);
        SuprimirFila(row);
      }
			else if(contenido == "")
      {
        for(int i=indiceRESET;i<=gridSimulacion->ColCount;i++)
  				gridSimulacion->Cells[i][row] = AnsiString("");
				gridSimulacion->Cells[col][row] = AnsiString("RESET");
        AnyadirFila(row);
        for(int i=indiceRESET;i<=gridSimulacion->ColCount;i++)
  				gridSimulacion->Cells[i][row+1] = AnsiString("");
        gridSimulacion->Cells[indiceEstado][row+1]="[RESET]";
      }
		}
    Renumerar();
	}
  }
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::spinFilasChange(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int filasActual = gridSimulacion->RowCount;
	int filasNuevo = spinFilas->Value + 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	gridSimulacion->RowCount = spinFilas->Value + 1;
	if(filasNuevo > filasActual)
	{
		fSimulacion->gridSimulacion->Cells[0][spinFilas->Value] = AnsiString(spinFilas->Value);
		for(int i = fSimulacion->indiceEntInicial; i <= fSimulacion->indiceEntFinal; i++)
			fSimulacion->gridSimulacion->Cells[i][spinFilas->Value] = "0";
		for(int i = fSimulacion->indiceSalInicial; i <= fSimulacion->indiceSalFinal; i++)
			fSimulacion->gridSimulacion->Cells[i][spinFilas->Value] = "";
		fSimulacion->gridSimulacion->Cells[indiceCLK][spinFilas->Value] = Form1Boole2->tipoSimulacion == RAPIDA?"CLK":"";
		fSimulacion->gridSimulacion->Cells[indiceRESET][spinFilas->Value] = "";
		fSimulacion->gridSimulacion->Cells[indiceEstado][spinFilas->Value] = "";
		fSimulacion->gridSimulacion->Cells[indiceEstadoSig][spinFilas->Value] = "";
	}
  Renumerar();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::btIniciarSimClick(TObject *Sender)
{
	if(!pausado)
	{
		fLog->memoLog->Clear();
    fLog->pasoActual = 0;
		fLog->EscribirCabecera(Sistema.Tipo, Form1Boole2->tipoSimulacion);

		// Borramos los resultados
  	for(int fila = 3; fila <= gridSimulacion->RowCount; fila++)
  	{
 		  for(int col = indiceSalInicial; col <= indiceSalFinal; col++) gridSimulacion->Cells[col][fila] = "";
		  if (gridSimulacion->Cells[indiceEstado][fila] != "[RESET]" && gridSimulacion->Cells[indiceEstado][fila] != "[CLK]")
        gridSimulacion->Cells[indiceEstado][fila] = "";
      if(Form1Boole2->tipoSimulacion==NORMAL)
    		gridSimulacion->Cells[indiceEstadoSig][fila] = "";
  	}

		btIniciarSim->Caption = MENSAJE(msgReanudar);
		indiceActual = 1;
	}
	else
	{
		pausado = false;
	}

	btSiguiente->Enabled = true;
	btRapido->Enabled = true;
	btPausarSim->Enabled = true;
	btIniciarSim->Enabled = false;
	btPararSim->Caption = MENSAJE(msgPararYReiniciar);
	simulacion = BATCH_ACTIVO;
	comboInicial->Enabled = false;
	spinFilas->Enabled = false;
	gridSimulacion->Enabled = false;
	Sistema.indiceActual = Sistema.indiceInicial;

	//if(TfSimulacion::AplicarEntradas(false))
		TfSimulacion::PosicionarPaso(indiceActual);
	/*else
	{
		Application->MessageBox
			(
				"La simulación no puede comenzar. La entrada aplicada en el primer paso (al estado inicial) no activa ninguna transicion).",
				"ERROR!",
				MB_OK
			);
		btPararSim->Click();
	} */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::comboInicialChange(TObject *Sender)
{
	Sistema.indiceInicial = comboInicial->ItemIndex;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::Cerrar1Click(TObject *Sender)
{
	Close();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::FormClose(TObject *Sender, TCloseAction &Action)
{
	simulando = false;
	simulacion = NO_SIMULANDO;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::btSiguienteClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~*/
	bool	Clock = false;
	/*~~~~~~~~~~~~~~~~~~*/

	if(indiceActual < gridSimulacion->RowCount)
	{
    if(gridSimulacion->Cells[indiceRESET][indiceActual] == "RESET")
    {
      Sistema.Resetear();
      indiceActual++;
      ActualizarTablaYLog();
      indiceActual++;
      TfSimulacion::PosicionarPaso(indiceActual);
    }
    else if (gridSimulacion->Cells[indiceCLK][indiceActual] == "CLK")
    {
  		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  		FLECHA	f;
  		bool	flechaEncontrada = false;
  		int		i = 0, indice, indiceEntradas;
      AnsiString entrada;
  		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

      // En la simulacion normal las entradas estan en la fila anterior.
      indiceEntradas = Form1Boole2->tipoSimulacion==RAPIDA?indiceActual:indiceActual-1;
  		for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
  			entrada = entrada + gridSimulacion->Cells[indiceEntInicial + i][indiceEntradas];

      // En la simulacion rapida primero tenemos que aplicar las entradas.
      if (Form1Boole2->tipoSimulacion==RAPIDA)
      {
     		indice = Sistema.indiceActual;
        if (Sistema.AplicarEntrada(entrada))
     		{
          Sistema.Clk();
          ActualizarTablaYLog();
          if (Sistema.indiceActual == Sistema.indiceAnterior)
          {
            Form1Boole2->TimerParpadeoEstado->Tag = 0;
            Form1Boole2->TimerParpadeoEstado->Enabled = true;
          }
          indiceActual++;
          TfSimulacion::PosicionarPaso(indiceActual);
    		  Clock = true;
     		}
     		else
    			Application->MessageBox((ANSIMENSAJE(msgErrorAplicarEntrada1)+ " " + entrada + " " + MENSAJE(msgErrorAplicarEntrada2) +" "+Sistema.CogerNombreCirculoActual()).c_str(), "ERROR!", MB_OK);
      }
      // En la simulacion normal se supone que las entradas ya han sido aplicadas.
      // Solo hay que hacer el clock.
      else if (Form1Boole2->tipoSimulacion==NORMAL)
      {
        Sistema.Clk();
        ActualizarTablaYLog();
        if (Sistema.indiceActual == Sistema.indiceAnterior)
        {
          Form1Boole2->TimerParpadeoEstado->Tag = 0;
          Form1Boole2->TimerParpadeoEstado->Enabled = true;
        }
        indiceActual++;
        TfSimulacion::PosicionarPaso(indiceActual);
   		  Clock = true;
      }
    }
    else // Simple aplicación de entradas (siempre simulacion normal)
    {
  		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  		FLECHA	f;
  		bool	flechaEncontrada = false;
  		int		i = 0, indice;
      AnsiString entrada;
  		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  		for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
  			entrada = entrada + gridSimulacion->Cells[indiceEntInicial + i][indiceActual];


     		indice = Sistema.indiceActual;
        if (Sistema.AplicarEntrada(entrada))
     		{
          ActualizarTablaYLog();
          if (Sistema.indiceActual == Sistema.indiceAnterior)
          {
            Form1Boole2->TimerParpadeoEstado->Tag = 0;
            Form1Boole2->TimerParpadeoEstado->Enabled = true;
          }
          indiceActual++;
          TfSimulacion::PosicionarPaso(indiceActual);
    		  Clock = true;
     		}
     		else
    			Application->MessageBox((ANSIMENSAJE(msgErrorAplicarEntrada1)+ " " + entrada + " " + MENSAJE(msgErrorAplicarEntrada2) +" "+Sistema.CogerNombreCirculoActual()).c_str(), "ERROR!", MB_OK);
      /*
  		for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
  			entrada = entrada + gridSimulacion->Cells[indiceEntInicial + i][indiceActual];

  		indice = Sistema.indiceActual;

  		while(!flechaEncontrada && i < Sistema.GetNumFlechas())
  		{
  			f = Sistema.DevolverFlecha(i);
  			if(f.FlechaCirculoSale() == indice && Sistema.PuedeSeguir(entrada, f.DevolverEtiqueta1()))
  				flechaEncontrada = true;
  			i++;
  		}

  		if(flechaEncontrada)
  		{
  			indiceActual++;

        //TfSimulacion::AplicarEntradas(entrada);

  			if(gridSimulacion->Cells[indiceCLK][indiceActual - 1] == "CLK")
  			{
          Sistema.indiceAnterior = Sistema.indiceActual;
  				Sistema.indiceActual = Sistema.getFlechaActual().FlechaCirculoEntra();
          if (Sistema.indiceActual == Sistema.indiceAnterior)
          {
            Form1Boole2->TimerParpadeoEstado->Tag = 0;
            Form1Boole2->TimerParpadeoEstado->Enabled = true;
          }

  				Clock = true;
  			}
  			TfSimulacion::PosicionarPaso(indiceActual);
	  	}
  		else
		  	Application->MessageBox(("Imposible aplicar la entrada " + entrada + " en el estado "+Sistema.CogerNombreCirculoActual()).c_str(), "ERROR!", MB_OK);
        */
    }
  }
	if (indiceActual == gridSimulacion->RowCount)
		btPararSim->Click();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::btPararSimClick(TObject *Sender)
{
	if(simulacion == BATCH_ACTIVO || pausado)
	{
		simulacion = BATCH_PARADO;
		pausado = false;
		PosicionarPaso(MAX_PASOS + 1);
		gridSimulacion->TopRow = 1;
		btSiguiente->Enabled = false;
		btRapido->Enabled = false;
		btPausarSim->Enabled = false;
		btIniciarSim->Enabled = true;
		btIniciarSim->Caption = MENSAJE(msgIniciarSimu);
		btPararSim->Caption = MENSAJE(msgBorrarTabla);
		comboInicial->Enabled = true;
		spinFilas->Enabled = true;
		gridSimulacion->Enabled = true;
		spinFilas->MinValue = 3;
	}
	else
	{
		BorrarTabla();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::btPausarSimClick(TObject *Sender)
{
	simulacion = BATCH_PARADO;
	btSiguiente->Enabled = false;
	btRapido->Enabled = false;
	btPausarSim->Enabled = false;
	btIniciarSim->Enabled = true;
	comboInicial->Enabled = false;
	spinFilas->Enabled = true;
	spinFilas->MinValue = indiceActual;
	gridSimulacion->Enabled = true;
	pausado = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::gridSimulacionSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	CanSelect = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TfSimulacion::PosicionarPaso(int paso)
{
	/*~~~~~~~~~~~~~*/
	TGridRect	rect;
	/*~~~~~~~~~~~~~*/

	rect.Left = 0;
	rect.Right = fSimulacion->indiceSalFinal;
	rect.Top = paso;
	rect.Bottom = paso;
	gridSimulacion->Selection = rect;
	if(paso > (gridSimulacion->TopRow + gridSimulacion->VisibleRowCount - 1)) gridSimulacion->TopRow++;
        else if (paso < gridSimulacion->TopRow) gridSimulacion->TopRow = paso;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::FormShow(TObject *Sender)
{
	spinFilas->MinValue = 3;
	spinFilas->MaxValue = MAX_PASOS;
	pausado = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TfSimulacion::BorrarTabla(void)
{
  for(int i=1;i<gridSimulacion->RowCount;i++)
    for(int j=0;j<gridSimulacion->ColCount;j++)
      gridSimulacion->Cells[j][i] = "";

	fSimulacion->gridSimulacion->Cells[0][1] = "0";
	fSimulacion->gridSimulacion->Cells[0][2] = "0";
  fSimulacion->gridSimulacion->Cells[fSimulacion->indiceRESET][1]="RESET";
  fSimulacion->gridSimulacion->Cells[fSimulacion->indiceEstado][1]="";
  fSimulacion->gridSimulacion->Cells[fSimulacion->indiceEstado][2]="[RESET]";

	for(int fila = 3; fila <= gridSimulacion->RowCount; fila++)
	{
		for(int col = indiceEntInicial; col <= indiceEntFinal; col++) gridSimulacion->Cells[col][fila] = "0";
		gridSimulacion->Cells[indiceRESET][fila] = "";
		gridSimulacion->Cells[indiceCLK][fila] = Form1Boole2->tipoSimulacion == RAPIDA?"CLK":"";
 		for(int col = indiceSalInicial; col <= indiceSalFinal; col++) gridSimulacion->Cells[col][fila] = "";
		if (gridSimulacion->Cells[indiceEstado][fila] != "[RESET]" && gridSimulacion->Cells[indiceEstado][fila] != "[CLK]")
      gridSimulacion->Cells[indiceEstado][fila] = "";
		gridSimulacion->Cells[indiceEstadoSig][fila] = "";
	}
  Renumerar();
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::gridSimulacionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	/*~~~~~~~~~~~~~~~~~*/
	int col, row, rowMin;
	/*~~~~~~~~~~~~~~~~~*/

	gridSimulacion->MouseToCell(X, Y, col, row);

	if(pausado)
		rowMin = indiceActual + 1;
	else
		rowMin = 1;

	if(row >= rowMin && col >= indiceEntInicial && col <= indiceRESET)
		gridSimulacion->Cursor = crHandPoint;
	else
		gridSimulacion->Cursor = crDefault;
	Application->ProcessMessages();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TfSimulacion::ActualizarTablaYLog()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	salida, entrada;
	bool	reset, clock;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		entrada = Sistema.CogerEntradaActual();
		/*for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
			gridSimulacion->Cells[indiceEntInicial + i][indiceActual] = entrada[i + 1];*/
 		salida = Sistema.CogerSalidaActual();

		reset = (gridSimulacion->Cells[indiceRESET][indiceActual-1] == "RESET");
		clock = (gridSimulacion->Cells[indiceCLK][indiceActual] == "CLK");

    if (reset) // El reset se hace igual en todas las simulaciones
    {
      gridSimulacion->Cells[indiceEstado][indiceActual] = Sistema.CogerNombreCirculoActual();
      if (Sistema.Tipo == MOORE)
    		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	    		gridSimulacion->Cells[indiceSalInicial + i][indiceActual] = Sistema.CogerSalidaActual()[i + 1];
    }
    else if (Form1Boole2->tipoSimulacion == RAPIDA)
    {
  		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	  		gridSimulacion->Cells[indiceSalInicial + i][indiceActual] = salida[i + 1];
  		gridSimulacion->Cells[indiceEstado][indiceActual] = Sistema.CogerNombreCirculoActual();
    }
    else if (Form1Boole2->tipoSimulacion == NORMAL)
    {
      if (clock)
      {
        indiceActual++;
        gridSimulacion->Cells[indiceEstado][indiceActual] = Sistema.CogerNombreCirculoActual();
        if (Sistema.Tipo == MOORE)
      		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	      		gridSimulacion->Cells[indiceSalInicial + i][indiceActual] = salida[i + 1];
      }
      else
      {
        gridSimulacion->Cells[indiceEstado][indiceActual] = Sistema.CogerNombreCirculoActual();
        gridSimulacion->Cells[indiceEstadoSig][indiceActual] = Sistema.CogerNombreCirculoSiguiente();
      		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	      		gridSimulacion->Cells[indiceSalInicial + i][indiceActual] = salida[i + 1];
      }
    }

    // Actualización del log
    if (!clock && !reset)
    {
      // Es una simple aplicacion de entradas
   		fLog->EscribirLinea
			(
				TEXTO,
        Sistema.Tipo,
        NORMAL,
				fLog->pasoActual++,
				false,
				false,
				Sistema.CogerNombreCirculoActual(),
				entrada,
				Sistema.CogerNombreCirculoSiguiente(),
				Sistema.CogerSalidaActual()
			);
    }
    else if (clock && !reset)
    {
      // Un clock. En este caso, el log es diferente en la simulacion normal y en la detallada

      if(Form1Boole2->tipoSimulacion == RAPIDA)
      {
      // En la simulacion rapida escribimos una unica linea 'resumida'
      // Muestra el estado al que hemos llegado, con que entrada,
      // y que salida ha habido en ese cambio de estado (en Moore, la
      // del estado destino, y en Mealy la salida de la transicion
      // que hemos seguido)
      // Se supone que tras la transicion no hay entrada estable
        fLog->EscribirLinea
        (
          TEXTO,
          Sistema.Tipo,
          Form1Boole2->tipoSimulacion,
          fLog->pasoActual,
          false,
          true,
          Sistema.CogerNombreCirculoActual(),
          entrada,
          " ",
          Sistema.CogerSalidaActual()
        );
      }
      else if (Form1Boole2->tipoSimulacion == NORMAL)
      {
      // En la simulacion normal mostramos dos lineas:
      // La primera simplemente indica que hemos hecho un clock.
      // La segunda muestra el estado despues del clock,
      // suponiendo que no hay una entrada estable.
        fLog->EscribirLinea
        (
          TEXTO,
          Sistema.Tipo,
          Form1Boole2->tipoSimulacion,
          fLog->pasoActual,
          false,
          true,
          " ",
          AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
          " ",
          AnsiString::StringOfChar(' ', Sistema.NumCarSal)
        );
        fLog->EscribirLinea
        (
          TEXTO,
          Sistema.Tipo,
          Form1Boole2->tipoSimulacion,
          fLog->pasoActual,
          false,
          false,
          Sistema.CogerNombreCirculoActual(),
          AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
          " ",
          Sistema.Tipo==MOORE?salida:AnsiString::StringOfChar(' ', Sistema.NumCarSal)
        );
      }
      fLog->pasoActual++;
    }
    else if (!clock && reset)
    {
      // Es un reset. Se hace igual en ambas simulaciones
      fLog->EscribirLinea(
      TEXTO,
      Sistema.Tipo,
      Form1Boole2->tipoSimulacion,
      fLog->pasoActual,
      true,
      false,
      " ",
      AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
      " ",
      AnsiString::StringOfChar(' ', Sistema.NumCarSal)

      );
        fLog->EscribirLinea(
        TEXTO,
        Sistema.Tipo,
        Form1Boole2->tipoSimulacion,
        fLog->pasoActual++,
        false,
        false,
        Sistema.CogerNombreCirculoActual(),
        AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
        " ",
        Sistema.Tipo==MOORE?salida:AnsiString::StringOfChar(' ', Sistema.NumCarSal)
        );


    }

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::btRapidoClick(TObject *Sender)
{
	while(indiceActual < gridSimulacion->RowCount) btSiguiente->Click();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfSimulacion::VerLog1Click(TObject *Sender)
{
	fLog->llamador = LLAMA_BATCH;
	fSimulacion->Enabled = false;
	fLog->Show();
	fLog->SetFocus();
}


void      TfSimulacion::AnyadirFila(int fila)
{
  spinFilas->Value++;
	//gridSimulacion->RowCount++;

  for(int i=gridSimulacion->RowCount-1; i>fila; i--)
  	for(int j = 0; j < gridSimulacion->ColCount; j++)
			fSimulacion->gridSimulacion->Cells[j][i] = fSimulacion->gridSimulacion->Cells[j][i-1];

		for(int i = fSimulacion->indiceEntInicial; i <= fSimulacion->indiceEntFinal; i++)
			fSimulacion->gridSimulacion->Cells[i][fila+1] = "0";
		for(int i = fSimulacion->indiceSalInicial; i <= fSimulacion->indiceSalFinal; i++)
			fSimulacion->gridSimulacion->Cells[i][fila+1] = "";
		fSimulacion->gridSimulacion->Cells[indiceCLK][fila+1] = Form1Boole2->tipoSimulacion == RAPIDA?"CLK":"";
		fSimulacion->gridSimulacion->Cells[indiceRESET][fila+1] = "";
		fSimulacion->gridSimulacion->Cells[indiceEstado][fila+1] = "";
    if(Form1Boole2->tipoSimulacion==NORMAL)
  		fSimulacion->gridSimulacion->Cells[indiceEstadoSig][spinFilas->Value] = "";
}

void      TfSimulacion::SuprimirFila(int fila)
{
  spinFilas->Value--;
  for(int i=fila; i<gridSimulacion->RowCount-1; i++)
  	for(int j = 0; j < gridSimulacion->ColCount; j++)
			fSimulacion->gridSimulacion->Cells[j][i] = fSimulacion->gridSimulacion->Cells[j][i+1];

  //gridSimulacion->RowCount--;
}

void      TfSimulacion::AnyadirPaso(int fila)
{
  AnsiString pasoSeleccionado = fSimulacion->gridSimulacion->Cells[0][fila];
  int filaReal = fila;

  while (fSimulacion->gridSimulacion->Cells[0][filaReal] == pasoSeleccionado)
    filaReal++;

  AnyadirFila(filaReal - 1);
  Renumerar();
}

void      TfSimulacion::SuprimirPaso(int fila)
{
  if (Form1Boole2->tipoSimulacion==NORMAL)
  {
    if (fSimulacion->gridSimulacion->Cells[indiceRESET][fila] == "RESET" || fSimulacion->gridSimulacion->Cells[indiceCLK][fila] == "CLK")
    {
      SuprimirFila(fila+1);
      SuprimirFila(fila);
    }
    else if (fSimulacion->gridSimulacion->Cells[indiceRESET][fila-1] == "RESET" || fSimulacion->gridSimulacion->Cells[indiceCLK][fila-1] == "CLK")
    {
      SuprimirFila(fila);
      SuprimirFila(fila -1);
    }
  }
  else if (Form1Boole2->tipoSimulacion==RAPIDA)
  {
    SuprimirFila(fila);
  }
  Renumerar();
}


void __fastcall TfSimulacion::menuInsertarfilaClick(TObject *Sender)
{
  extern int filaSelec;
  AnyadirPaso(filaSelec);
}
//---------------------------------------------------------------------------

void __fastcall TfSimulacion::menuEliminarfilaClick(TObject *Sender)
{
  extern int filaSelec;
  SuprimirPaso(filaSelec);
}
//---------------------------------------------------------------------------

int filaSelec;

void __fastcall TfSimulacion::PopupTablaPopup(TObject *Sender)
{
  int X, Y, col, row;

  X = gridSimulacion->ScreenToClient(Mouse->CursorPos).x;
  Y = gridSimulacion->ScreenToClient(Mouse->CursorPos).y;
  gridSimulacion->MouseToCell(X, Y, col, row);
  filaSelec=row;
  if (row <= 3)
  {
    menuInsertarfila->Enabled = false;
    menuEliminarfila->Enabled = false;
  }
  else
  {
    menuInsertarfila->Enabled = true;
    menuEliminarfila->Enabled = true;
  }


}
//---------------------------------------------------------------------------

void TfSimulacion::Renumerar()
{
  int paso=0;
  for (int i=1; i<gridSimulacion->RowCount; i++)
  {
    gridSimulacion->Cells[0][i] = AnsiString(paso);
    if (gridSimulacion->Cells[indiceRESET][i] == "RESET" || (gridSimulacion->Cells[indiceCLK][i] == "CLK" && Form1Boole2->tipoSimulacion==NORMAL))
      ;
    else
      paso++;
  }
}
void __fastcall TfSimulacion::Ayuda1Click(TObject *Sender)
{
AnsiString mensaje = ANSIMENSAJE(msgAyudaBatch) + ANSIMENSAJE(msgAyudaBatch2);

  Application->MessageBox(mensaje.c_str(), "");
}
//---------------------------------------------------------------------------


