/*$T boole/Circuito/V_Imprimir.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "V_Imprimir.h"
#include "V_Circuito.h"
#include <vcl/printers.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormI		*FormI;
TPrinter	*Impresora = Printer();

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TFormI::TFormI(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormI::AceptarClick(TObject *Sender)
{
	FormI->Aceptar->Enabled = false;

	Graphics::TBitmap * bmp = new Graphics::TBitmap();
	bmp = FormR->Image1->Picture->Bitmap;
	bmp->Width = FormR->tamanioCircuito.x;
	bmp->Height = FormR->tamanioCircuito.y;

	/*~~~~~~~*/
	TRect	rc;
	/*~~~~~~~*/

	rc.Left = 0;
	rc.Top = 0;

	if(FormI->Orientacion->ItemIndex == 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		TPrinter	*I = Printer();
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		Graphics::TBitmap * bmp = new Graphics::TBitmap();
		bmp = FormR->Image1->Picture->Bitmap;

		// Impresion en vertical.
		I->Orientation = poPortrait;
		bmp->Width = FormR->tamanioCircuito.x;
		bmp->Height = FormR->tamanioCircuito.y;

		/*~~~~~~~*/
		TRect	rc;
		/*~~~~~~~*/

		rc.Left = 0;
		rc.Top = 0;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		double	proporcionI = (double) ((double) I->PageHeight / (double) I->PageWidth);
		double	factor = 2.3;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(FormI->Tamanio->ItemIndex == 0)
		{
			rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
			rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
		}
		else
		{			// maximizado
			factor = 1.0;
			rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
			rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
			while(rc.Right < I->PageWidth - 100 && rc.Bottom < I->PageHeight - 100)
			{
				factor += 0.05;
				rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
				rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
			}		// end-while
		}

		/*~~~~~~~~~~~~~~~~~~~~*/
		bool	imprimir = true;
		/*~~~~~~~~~~~~~~~~~~~~*/

		if(rc.Right >= I->PageWidth || rc.Bottom >= I->PageHeight)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	m = "Ha habido un problema con la impresora, posiblemente se deba a que:\n\n     1. el tamaño del circuito es mayor que el papel.\n     2. existen trabajos en la cola de impresora.\n\nSolución:\n\n     1. reiniciar el ordenador para eliminar los trabajos de la cola. \n     2. intentar imprimirlo con otras opciones.\n     3. copiar el circuito al portapapeles y editarlo desde otra aplicación.\n     4. imprimir un circuito más pequeño que el de la pantalla. \n\n ¿Imprimir un circuito más pequeño?";
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
			FormI->Caption = "Imprimiendo...";
			I->BeginDoc();
			I->Canvas->StretchDraw(rc, bmp);

			// int pos=I->PageHeight;
			if(FormR->tipoCircuito == false)
				// Form9->Solucion->Items->Strings[i]
				I->Canvas->TextOut(100, 30, FormR->ecuacion->Text);
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int solucionNum = FormR->solucionNum;
				int nLineas = FormR->Lista->Items->Count + 1;
				int altura = I->Canvas->TextHeight("XXX");
				int pos = I->PageHeight - altura * nLineas;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				I->Canvas->TextOut(100, pos, FormR->ListaSol->Items->Strings[solucionNum]);
				for(int i = 0; i < nLineas - 1; i++)
				{
					pos = pos + altura;
					I->Canvas->TextOut(100, pos, FormR->Lista->Items->Strings[i]);
				}
			}

			I->EndDoc();
			ProgressBar1->Min = 0;
			ProgressBar1->Max = 200;
			for(int i = ProgressBar1->Min; i <= ProgressBar1->Max; i++) ProgressBar1->Position = i;
			if(Impresora->Printing == false) FormI->Close();
		}			// end-if
	}				// end-if Orientacion.
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// SE IMPRIME EN HORIZONTAL.
		TPrinter	*I = Printer();
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		Graphics::TBitmap * bmp = new Graphics::TBitmap();
		bmp = FormR->Image1->Picture->Bitmap;

		// Impresion en vertical.
		I->Orientation = poLandscape;
		bmp->Width = FormR->tamanioCircuito.x;
		bmp->Height = FormR->tamanioCircuito.y;

		/*~~~~~~~*/
		TRect	rc;
		/*~~~~~~~*/

		rc.Left = 0;
		rc.Top = 0;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		double	proporcionI = (double) ((double) I->PageWidth / (double) I->PageHeight);
		double	factor = 2.3;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(FormI->Tamanio->ItemIndex == 0)
		{
			rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
			rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
		}
		else
		{			// maximizado
			factor = 1.0;
			rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
			rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
			while(rc.Right < I->PageWidth - 40 && rc.Bottom < I->PageHeight - 40)
			{
				factor += 0.05;
				rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
				rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
			}		// end-while
		}

		/*~~~~~~~~~~~~~~~~~~~~*/
		bool	imprimir = true;
		/*~~~~~~~~~~~~~~~~~~~~*/

		if(rc.Right >= I->PageWidth || rc.Bottom >= I->PageHeight)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	m = "Ha habido un problema con la impresora, posiblemente se deba a que:\n\n     1. el tamaño del circuito es mayor que el papel.\n     2. existen trabajos en la cola de impresora.\n\nSolución:\n\n     1. reiniciar el ordenador para eliminar los trabajos de la cola. \n     2. intentar imprimirlo con otras opciones.\n     3. copiar el circuito al portapapeles y editarlo desde otra aplicación.\n     4. imprimir un circuito más pequeño que el de la pantalla. \n\n ¿Imprimir un circuito más pequeño?";
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(MessageDlg(m, mtError, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
			{
				while(rc.Right >= I->PageWidth || rc.Bottom >= I->PageHeight)
				{
					factor -= 0.1;
					rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
					rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
				}	// en-while
				imprimir = true;
			}
			else
				imprimir = false;
		}			// end-if

		if(imprimir == true)
		{
			FormI->Caption = "Imprimiendo...";
			I->BeginDoc();
			I->Canvas->StretchDraw(rc, bmp);
			I->EndDoc();
			ProgressBar1->Min = 0;
			ProgressBar1->Max = 100;

			for(int i = ProgressBar1->Min; i <= ProgressBar1->Max; i++)
			{
				if(i >= 20) FormI->Cancelar->Enabled == false;
				ProgressBar1->Position = i;
			}

			if(Impresora->Printing == false) FormI->Close();
		}			// end-if
	}				// end-else.

	FormI->Cancelar->Enabled == true;
	FormI->Aceptar->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormI::CancelarClick(TObject *Sender)
{
	FormI->Close();
	if(Impresora->Printing)
	{
		Impresora->Abort();
		FormR->Show();
	}

	FormR->Show();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormI::FormShow(TObject *Sender)
{
	ProgressBar1->Position = 0;
	FormI->Aceptar->Enabled = true;
}
