/*$T boole/Circuito/V_Circuito.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>

#pragma hdrstop
#include <vcl/printers.hpp>
#include <stdlib.h>
#include "V_Circuito.h"
#include "Entrada.h"
#include "PuertaAnd.h"
#include "PuertaOr.h"
#include "PuertaNand.h"
#include "PuertaNor.h"
#include "CircuitoCombinacional.h"
#include "CircuitoSecuencial.h"
#include "FlipFlopJK.h"
#include "FlipFlopD.h"
#include "funciones.h"
#include "V_Imprimir.h"
#include "V_Boole2.h"
#include "Unit2.h"
#include "Unit9.h"
#include "Unit10.h"
#include "mensajes.inc"
#include <vcl/Clipbrd.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormR	*FormR;

double	coefi = 0;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TFormR::TFormR(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->X->SimpleText = "  X: " + (AnsiString) X;
	FormR->Y->SimpleText = "  Y: " + (AnsiString) Y;
}

//
// =======================================================================================================================
//    VISUALIZAR CIRCUITO COMBINACIONAL
// =======================================================================================================================
//
void __fastcall TFormR::VisualizarClick(TObject *Sender)
{
	if(FormR->tipoCircuito == false)
	{			// Circuito Combinacional.
		if(FormR->ecuacion->Text != "")
		{
			FormR->Image1->Picture->Bitmap->Width = 1200;
			FormR->Image1->Picture->Bitmap->Height = 1900;

			tipoCircuito = false;
			FormR->Lista->Visible = false;
			FormR->ListaSol->Visible = false;
			FormR->ecuacion->Visible = true;
			limpiarCanvas();

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			// se limpia la pantalla.

			// FormR->ecuacion->Text = LimpiarEcuacion(FormR->ecuacion->Text);
			AnsiString	ecuacion = FormR->ecuacion->Text;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			// ecuacion = LimpiarEcuacion(ecuacion);
			for(int i = 1; i <= ecuacion.Length(); i++)
			{
				if(ecuacion[i] == '-') ecuacion[i] = '~';
			}

			FormR->ecuacion->Text = ecuacion;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			CircuitoCombinacional	*CCL = new CircuitoCombinacional(ecuacion);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			CCL->crearArrayEntradas();

			// AQUI EMPIEZA LO PRINCIPAL
			if(CCL->lonE == 1 || (CCL->lonE == 2 && CCL->s.SubString(1, 2)=="(~"))
			{	// una sola entrada
                                if (CCL->lonE == 1)
                                {
           				CCL->AEntradas[0].setx(50);
          				CCL->AEntradas[0].sety(40);
          				CCL->AEntradas[0].Dibujar(0);
                                          FormR->Image1->Canvas->TextOut(47, 105, CCL->salida.nombre);
                                }
                                else
                                {
          				CCL->ordenarEntradas();
                                          CCL->asignarPosicionesAEntradas(0, 40);
          				CCL->AEntradas[0].Dibujar(0);
                                	CCL->limite.x = CCL->AEntradas[1].getx() + 10;
                                	CCL->limite.y = CCL->AEntradas[1].gety() + 20;
               				CCL->AEntradas[1].DibujarNot(0);
                                          FormR->Image1->Canvas->TextOut(67, 120, CCL->salida.nombre);
                                }

				tamanioCircuito.x = 150;
				tamanioCircuito.y = 170;
			}
			else
			{
				CCL->ordenarEntradas();
				CCL->asignarPosicionesAEntradas(0, 40);

				// se dibuja el circuito.
				CCL->dibujarEntradas(0);
				CCL->crearArrayEC();
				CCL->dibujarCircuitoCombinacional(CCL->getLimite().x + 10);
				CCL->dibujarSalida();

				// fin de dibujar el circuito.
				tamanioCircuito.x = CCL->tamanio.x + 50;
				tamanioCircuito.y = CCL->tamanio.y + 50;
			}

			FormR->Caption = FormR->Titulo + "  " + (AnsiString) FormR->ecuacion->Text;

			FormR->ScrollBox1->HorzScrollBar->Range = tamanioCircuito.x + 20;
			FormR->ScrollBox1->VertScrollBar->Range = tamanioCircuito.y + 20;

			// CCL->~CircuitoCombinacional ();
		}
		else
			limpiarCanvas();
	}
	else
	{
		FormR->Image1->Picture->Bitmap->Width = 1200;
		FormR->Image1->Picture->Bitmap->Height = 1900;

		tipoCircuito = true;
		FormR->Lista->Visible = true;
		FormR->ListaSol->Visible = true;
		FormR->ecuacion->Visible = false;
		limpiarCanvas();

		/*~~~~~~~~~~~~~~~~~~*/
		int longitudLista = 0;
		/*~~~~~~~~~~~~~~~~~~*/

		// Warning bool final=false;
		FormR->Lista->Items->Clear();
		FormR->ListaSol->Items->Clear();
		longitudLista = FormR->Lista->Items->Count;

		if(tipoCS == true)
		{		// Mealy
			if(tipoFlipFlops == true)
			{
				for(int i = 0; i < Form10->ListaJK->Items->Count; i++)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	el = Form10->ListaJK->Items->Strings[i];
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					FormR->Lista->Items->Add(el);
				}
			}
			else
			{	// rellenamos la lista con flip-flops D.
				for(int i = 0; i < Form10->ListaD->Items->Count; i++)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	el = Form10->ListaD->Items->Strings[i];
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					FormR->Lista->Items->Add(el);
				}
			}

			for(int i = 0; i < Form10->ListaSol->Items->Count; i++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	el = Form10->ListaSol->Items->Strings[i];
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				FormR->ListaSol->Items->Add(el);
			}
		}
		else
		{		// Moore
			if(tipoFlipFlops == true)
			{
				for(int i = 0; i < Form9->ListaJK->Items->Count; i++)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	el = Form9->ListaJK->Items->Strings[i];
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					FormR->Lista->Items->Add(el);
				}
			}
			else
			{	// rellenamos la lista con flip-flops D.
				for(int i = 0; i < Form9->ListaD->Items->Count; i++)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	el = Form9->ListaD->Items->Strings[i];
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					FormR->Lista->Items->Add(el);
				}
			}

			for(int i = 0; i < Form9->ListaSol->Items->Count; i++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	el = Form9->ListaSol->Items->Strings[i];
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				FormR->ListaSol->Items->Add(el);
			}
		}

		longitudLista = FormR->Lista->Items->Count;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		CircuitoSecuencial	*CS = new CircuitoSecuencial(FormR->Lista, longitudLista, tipoFlipFlops);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		CS->dibujarCircuitoSecuencial();
		tamanioCircuito.x = CS->salida->tamanio.x + 50;
		tamanioCircuito.y = CS->salida->tamanio.y + 50;

		FormR->Caption = FormR->Titulo + "  " + CS->salida->salida.nombre;

		FormR->ScrollBox1->HorzScrollBar->Range = tamanioCircuito.x + 20;
		FormR->ScrollBox1->VertScrollBar->Range = tamanioCircuito.y + 20;

		// Error: falla en el destructor de CS. CS->~CircuitoSecuencial(); delete CS;
	}			// end-else. end-circuito-secuencial.
}	// fin del boton Visualizar.

//
// =======================================================================================================================
//    VISUALIZAR CIRCUITO SECUENCIAL fin del circuito secuencial.
// =======================================================================================================================
//
void __fastcall TFormR::MenosClick(TObject *Sender)
{
	FormR->Image1->AutoSize = false;

	FormR->Image1->Height -= (int) (40 * coefi);	// +desfase;
	FormR->Image1->Width -= 40;
	FormR->ScrollBox1->HorzScrollBar->Range -= 40;
	FormR->ScrollBox1->VertScrollBar->Range -= (int) (40 * coefi);

	// VisualizarCircuitoSecuencial->Click();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::MasClick(TObject *Sender)
{
	FormR->Image1->AutoSize = false;

	FormR->Image1->Height += (int) (40 * coefi);	// +desfase;
	FormR->Image1->Width += 40;
	FormR->ScrollBox1->HorzScrollBar->Range += 40;
	FormR->ScrollBox1->VertScrollBar->Range += (int) (40 * coefi);
	FormR->Image1->AutoSize = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::CopiarClick(TObject *Sender)
{
	// FormR->Image1->Picture->Bitmap=FormR->Image1->Picture->Bitmap;
	FormR->Image1->Picture->Bitmap->Width = tamanioCircuito.x;
	FormR->Image1->Picture->Bitmap->Height = tamanioCircuito.y;

	Clipboard()->Assign(FormR->Image1->Picture->Bitmap);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::FormShow(TObject *Sender)
{
	if(FormR->ecuacion->Text != "")
		Visualizar->Click();
	else
		limpiarCanvas();
}

/*
 =======================================================================================================================
    J0=(AEntradas*Q1)+(AEntradas*~Q2) K0=(AEntradas*~Q1)+(~AEntradas*Q1) J1=(AEntradas) K1=(~AEntradas)
    J2=(AEntradas*Q0) K2=(~AEntradas*Q1) S=(Q2*~AEntradas*~Q1) £
    J0=(AEntradas*Q1)+(AEntradas*~Q2) K0=(AEntradas*~Q3)+(~AEntradas*Q1) J1=(AEntradas) K1=(~AEntradas)
    J2=(AEntradas*Q0) K2=(~AEntradas*Q6) J3=(AEntradas*Q3)+(AEntradas*~Q2) K3=(AEntradas*~Q3)+(AEntradas*~Q3)
    J4=(AEntradas*Q5)+(AEntradas*~Q2) K4=(AEntradas*~Q3)+(AEntradas*~Q4) J5=(AEntradas*Q1)+(AEntradas*~Q2)
    K5=(AEntradas*~Q3)+(~AEntradas*Q1) J6=(AEntradas*Q1)+(AEntradas*~Q2) K6=(AEntradas*~Q3)+(~AEntradas*Q1)
    S=(Q3*Q2*~AEntradas) £
    J0=(E*Q2)+(E*~Q0) K0=(E*~Q1)+(E*~Q2) J1=(E*Q0) K1=(~E) J2=(E*Q0) K2=(~E*Q1) J3=(E*Q3)+(E*~Q3) K3=(E*~Q2)+(E*~Q2)
    J4=(E*Q2)+(E*~Q4) K4=(E*~Q5)+(E*~Q6) J5=(E*Q1)+(E*~Q2) K5=(E*~Q2)+(~E*Q1) J6=(E*Q1)+(E*~Q7) K6=(E*~Q2)+(~E*Q1)
    J7=(E*Q1)+(E*~Q2) K7=(E*~Q2)+(~E*Q1) Salida=(~Q7*~E)+(Q2*~Q3*Q2*Q4)
 =======================================================================================================================
 */
void __fastcall TFormR::FormCreate(TObject *Sender)
{
	// ClientWidth = 900; ClientHeight = 900;
	FormR->Image1->Picture->Bitmap->Width = 1200;
	FormR->Image1->Picture->Bitmap->Height = 1900;
	FormR->ScrollBox1->HorzScrollBar->Range = FormR->Image1->Picture->Bitmap->Width;
	FormR->ScrollBox1->HorzScrollBar->Position = HorzScrollBar->Range - ClientWidth;
	FormR->ScrollBox1->HorzScrollBar->Increment = 10;
	FormR->ScrollBox1->HorzScrollBar->Visible = true;	// Show the scrollbar

	FormR->ScrollBox1->VertScrollBar->Range = FormR->Image1->Picture->Bitmap->Height;
	FormR->ScrollBox1->VertScrollBar->Position = VertScrollBar->Range - ClientHeight;
	FormR->ScrollBox1->VertScrollBar->Increment = 10;
	FormR->ScrollBox1->VertScrollBar->Visible = true;	// Show the scrollbar

	coefi = ((double) FormR->Image1->Height / (double) FormR->Image1->Width);
	solucionNum = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ecuacionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoIntroduce);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::Panel1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ecuacionKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoParentesis);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::VisualizarMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoVisualizar);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::VolverMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoVuelve);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ImprimirVMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoImprimeVertical);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ImprimirHMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoImprimeHorizontal);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::CopiarMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoCopia);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::MasMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoAumenta);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::MenosMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoDisminuye);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::VolverClick(TObject *Sender)
{
	if(tipoCircuito == true)
	{
		Form1Boole2->Enabled = true;
		Form1Boole2->Timer1->Enabled = true;
		Form1Boole2->Show();
		Form2->Show();
	}

	FormR->Close();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ListaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoEcuSec);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ListaClick(TObject *Sender)
{
	FormR->barraEstado->SimpleText = " " + (AnsiString) FormR->Lista->Items->Strings[FormR->Lista->ItemIndex];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ImprimirClick(TObject *Sender)
{
	FormI->ShowModal();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ImprimirVClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	TPrinter	*I = Printer();
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	Graphics::TBitmap * bmp = new Graphics::TBitmap();
	bmp = FormR->Image1->Picture->Bitmap;

	// Impresion en vertical.
	I->Orientation = poPortrait;
	bmp->Width = tamanioCircuito.x;
	bmp->Height = tamanioCircuito.y;

	/*~~~~~~~*/
	TRect	rc;
	/*~~~~~~~*/

	rc.Left = 0;
	rc.Top = 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	double	proporcionI = (double) ((double) I->PageHeight / (double) I->PageWidth);
	double	factor = 2.3;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
	rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);

	/*~~~~~~~~~~~~~~~~~~~~*/
	bool	imprimir = true;
	/*~~~~~~~~~~~~~~~~~~~~*/

	if(rc.Right >= I->PageWidth || rc.Bottom >= I->PageHeight)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	m = ANSIMENSAJE(msgVisuCircuitoErrorImprimir);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(MessageDlg(m, mtError, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		{
			while(rc.Right >= I->PageWidth || rc.Bottom >= I->PageHeight)
			{
				factor -= 0.1;
				rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
				rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
			}	// end-while
			imprimir = true;
		}
		else
			imprimir = false;
	}			// end-if

	if(imprimir == true)
	{
		I->BeginDoc();
		I->Canvas->StretchDraw(rc, bmp);
		I->EndDoc();
	}			// end-if
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ImprimirMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = ANSIMENSAJE(msgVisuCircuitoImprimir);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ecuacionClick(TObject *Sender)
{
	FormR->barraEstado->SimpleText = (AnsiString) " " + (AnsiString) FormR->ecuacion->Text;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ecuacionMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	FormR->barraEstado->SimpleText = " " + (AnsiString) FormR->ecuacion->Text;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ListaSolClick(TObject *Sender)
{
	solucionNum = FormR->ListaSol->ItemIndex;
	FormR->barraEstado->SimpleText = " " + (AnsiString) FormR->ListaSol->Items->Strings[solucionNum];
	Visualizar->Click();
}
void __fastcall TFormR::BitBtn4Click(TObject *Sender)
{
  AnsiString mensaje;

  if(tipoCircuito) // secuencial
        mensaje = ANSIMENSAJE(msgVisuCircuitoAyudaSecu);
  else // combinacional
  {
          mensaje = ANSIMENSAJE(msgVisuCircuitoAyuda);
          mensaje += "\n\r";
          mensaje += ANSIMENSAJE(msgVisuCircuitoAyudaSOP);
          mensaje += "\n\r";
          mensaje += "(A*B)+(B*C) --> " + ANSIMENSAJE(msgSi);
          mensaje += "\n\r";
          mensaje += "A*B+B*C --> " + ANSIMENSAJE(msgNo);
          mensaje += "\n\r";
          mensaje += ANSIMENSAJE(msgVisuCircuitoAyudaPOS);
          mensaje += "\n\r";
          mensaje += "(A+B)*(B+C) --> " + ANSIMENSAJE(msgSi);
          mensaje += "\n\r";
          mensaje += "A+B*B+C --> " + ANSIMENSAJE(msgNo);
          mensaje += "\n\r";
          mensaje += ANSIMENSAJE(msgVisuCircuitoAyudaNegacion);
          mensaje += "\n\r";
          mensaje += "(-A+-B)*(-B+C)";
  }
  Application->MessageBox(mensaje.c_str(), "");
}
//---------------------------------------------------------------------------

