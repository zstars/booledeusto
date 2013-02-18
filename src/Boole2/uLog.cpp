/*$T boole/uLog.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "uLog.h"
#include "uSimulacion.h"
#include "SistemaSecuencial.h"
#include "V_Boole2.h"
#include "mensajes.inc"
#include <Printers.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"
TfLog				*fLog;
extern AnsiString	Vars[10];

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TfLog::TfLog(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfLog::Button1Click(TObject *Sender)
{
	if(printLog->Execute())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int initX = 40, initY = 100, dY = Printer()->Canvas->TextHeight("X");
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Printer()->Title = "BOOLE-DEUSTO: " + ANSIMENSAJE(msgLogSimu);
		Printer()->Orientation = poPortrait;
		Printer()->BeginDoc();
		Printer()->Canvas->Font->Name = "Courier";
		Printer()->Canvas->Font->Size = 10;
		Printer()->Canvas->Font->Charset = DEFAULT_CHARSET;
		Printer()->Canvas->Font->Pitch = fpFixed;
		for(int i = 0; i < memoLog->Lines->Count; i++)
			Printer()->Canvas->TextOut(initX, initY + i * dY, memoLog->Lines->Strings[i]);
		Printer()->EndDoc();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfLog::Button3Click(TObject *Sender)
{
	Close();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfLog::Button4Click(TObject *Sender)
{
	memoLog->SelectAll();
	memoLog->CopyToClipboard();
	memoLog->SelLength = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfLog::Button2Click(TObject *Sender)
{
	if(saveLog->Execute()) memoLog->Lines->SaveToFile(saveLog->FileName);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfLog::EscribirLinea
(
	int			tipo,
  int     tipoAutomata,
  int     tipoSimulacion,
	int			paso,
	bool		reset,
	bool		clk,
	AnsiString	estado,
	AnsiString	ent,
	AnsiString	estadosig,
	AnsiString	sal
)
{
	/*~~~~~~~~~~~~~~*/
	AnsiString	linea;
	/*~~~~~~~~~~~~~~*/

        if (tipoAutomata==MEALY)
        {
        	linea += BARRA;
        	linea += EscribirColumna(tipo, AnsiString(paso), ANSIMENSAJE(msgPaso));
        	linea += BARRA;
        	linea += EscribirColumna(tipo, (reset ? "RESET" : ""), "RESET");
        	linea += BARRA;
        	linea += EscribirColumna(tipo, (clk ? "CLK" : ""), "CLK");
          if (tipoSimulacion == RAPIDA)
          {
        	linea += BARRA;
        	linea += EscribirEntSal(tipo, ent, ENTRADAS);
        	linea += BARRA_DOBLE;
        	linea += EscribirColumna(tipo, estado, "Q(t)");
        	linea += BARRA;
        	linea += EscribirEntSal(tipo, sal, SALIDAS);
          }
          else
          {
        	linea += BARRA;
        	linea += EscribirColumna(tipo, estado, "Q(t)");
        	linea += BARRA;
        	linea += EscribirEntSal(tipo, ent, ENTRADAS);
        	linea += BARRA_DOBLE;
        	linea += EscribirEntSal(tipo, sal, SALIDAS);
        	linea += BARRA;
         	linea += EscribirColumna(tipo, estadosig, "Q(t+1)");
          }
         	linea += BARRA;
        }
        else if (tipoAutomata==MOORE)
        {
        	linea += BARRA;
        	linea += EscribirColumna(tipo, AnsiString(paso), ANSIMENSAJE(msgPaso));
        	linea += BARRA;
        	linea += EscribirColumna(tipo, (reset ? "RESET" : ""), "RESET");
        	linea += BARRA;
        	linea += EscribirColumna(tipo, (clk ? "CLK" : ""), "CLK");
          if (tipoSimulacion == RAPIDA)
          {
        	linea += BARRA;
        	linea += EscribirEntSal(tipo, ent, ENTRADAS);
        	linea += BARRA_DOBLE;
        	linea += EscribirColumna(tipo, estado, "Q(t)");
        	linea += BARRA;
        	linea += EscribirEntSal(tipo, sal, SALIDAS);
          }
          else
          {
        	linea += BARRA;
        	linea += EscribirColumna(tipo, estado, "Q(t)");
        	linea += BARRA;
        	linea += EscribirEntSal(tipo, ent, ENTRADAS);
        	linea += BARRA_DOBLE;
        	linea += EscribirEntSal(tipo, sal, SALIDAS);
        	linea += BARRA;
         	linea += EscribirColumna(tipo, estadosig, "Q(t+1)");
          }
        	linea += BARRA;
        }

        memoLog->Lines->Append(linea);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfLog::EscribirCabecera(int tipoAutomata, int tipoSimulacion)
{
	EscribirLinea(LINEAS, tipoAutomata, tipoSimulacion);
 	EscribirLinea(TITULO, tipoAutomata, tipoSimulacion);
	EscribirLinea(LINEAS_DOBLES, tipoAutomata, tipoSimulacion);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString __fastcall TfLog::EscribirColumna(int tipo, AnsiString texto, AnsiString titulo)
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	retorno;
	/*~~~~~~~~~~~~~~~~*/

	switch(tipo)
	{
	case LINEAS:
		retorno = AnsiString::StringOfChar(LINEA, titulo.Length() + 2);
		break;
	case LINEAS_DOBLES:
		retorno = AnsiString::StringOfChar(LINEA_DOBLE, titulo.Length() + 2);
		break;
	case TITULO:
		retorno = " " + titulo + " ";
		break;
	case TEXTO:
		retorno = " " + texto;
		retorno += AnsiString::StringOfChar(' ', (titulo.Length() + 2) - retorno.Length());
		break;
	}

	return retorno;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString __fastcall TfLog::EscribirEntSal(int tipo, AnsiString texto, int entsal)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int			indiceInicial, indiceFinal;
	AnsiString	retorno, valor;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(entsal)
	{
	case ENTRADAS:	indiceFinal = 0; indiceInicial = indiceFinal + Sistema.DevolverNumCarEnt() - 1; break;
	case SALIDAS:	indiceFinal = 5; indiceInicial = indiceFinal + Sistema.DevolverNumCarSal() - 1; break;
	}

	for(int i = indiceInicial; i >= indiceFinal; i--)
	{
		if(indiceInicial - i > 0) retorno += BARRA;
		if(texto == "")
			valor = "";
		else
			valor = texto[indiceInicial - i + 1];
		retorno += EscribirColumna(tipo, valor, Vars[i]);
	}

	return retorno;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfLog::FormClose(TObject *Sender, TCloseAction &Action)
{
	switch(llamador)
	{
	case LLAMA_INTERACTIVA: Form1Boole2->Enabled = true; Form1Boole2->Timer1->Enabled = true; break;
	case LLAMA_BATCH:		fSimulacion->Enabled = true; fSimulacion->SetFocus(); break;
	}
}
