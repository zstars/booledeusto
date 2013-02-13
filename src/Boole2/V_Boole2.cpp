/*$T boole/Boole2/V_Boole2.cpp GC! 1.116 05/02/01 18:53:26 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


//
// COSAS QUE FALTAN mejorar el control de los botones del raton bobadas de la
// barra de estado dar un titulo a la impresion del automata
//
#include <vcl/vcl.h>
#include <vcl/printers.hpp>
#include <vcl\Clipbrd.hpp>

#pragma hdrstop
#include <stdlib.h>
#include <math.h>

#include <string>
#include <sstream>

#include "Unit11.h"

// Modificado Ricardo.
#include "Main.h"
#include "V_Boole2.h"
#include "V_Circuito.h"

// Modificado Ricardo.
#include "S.h"
#include "Sim2.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"

#include "Unit8.h"
#include "Unit9.h"
#include "Unit10.h"

#include "Unit12.h"
#include "Unit13.h"
#include "Unit14.h"
#include "Unit15.h"
#include "Unit16.h"
#include "FCalculando.h"
#include "ayuda.h"

// modificado Ainara
#include "SistemaSecuencial.h"
#include "uSimulacion.h"
#include "uLog.h"
#include "mensajes.inc"

#include "claseJedec.h"
#include "reductio\rdsimplificador.h"

#define max(a,b) ((a)>(b)?a:b)

#pragma resource "*.dfm"
TForm1Boole2	*Form1Boole2;

AnsiString		Vars[10];
AnsiString		Titulo;

//
// =======================================================================================================================
//    las variables de Entrada y de salida
// =======================================================================================================================
//
__fastcall TForm1Boole2::TForm1Boole2(TComponent *Owner) :
	TForm(Owner)
{
	Vars[0] = ANSIMENSAJE(msgPrefijoEntrada)+"0";
	Vars[1] = ANSIMENSAJE(msgPrefijoEntrada)+"1";
	Vars[2] = ANSIMENSAJE(msgPrefijoEntrada)+"2";
	Vars[3] = ANSIMENSAJE(msgPrefijoEntrada)+"3";
	Vars[4] = ANSIMENSAJE(msgPrefijoEntrada)+"4";
	Vars[5] = ANSIMENSAJE(msgPrefijoSalida)+"0";
	Vars[6] = ANSIMENSAJE(msgPrefijoSalida)+"1";
	Vars[7] = ANSIMENSAJE(msgPrefijoSalida)+"2";
	Vars[8] = ANSIMENSAJE(msgPrefijoSalida)+"3";
	Vars[9] = ANSIMENSAJE(msgPrefijoSalida)+"4";

        mWeblabMode = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::TableroMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if(!simulando)
	{
		if(X < 0) X = 0;
		if(Y < 0) Y = 0;
		if(X > Tablero->Width) X = Tablero->Width;
		if(Y > Tablero->Height) Y = Tablero->Height;

		// if ((X>0)&&(Y>0)&&(X<Tablero->Width)&&(Y<Tablero->Height))
		{
			Sistema.ActualizarRaton(X, Y);
		}

		if(Sistema.EstaCirculoMoviendose() == true)
		{
			Sistema.MoverCirculo();
		}

		if(Sistema.EstaFlechaMoviendose() == true)
		{
			Sistema.MoverFlecha();
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::FormCreate(TObject *Sender)
{
	Tablero->Refresh();

	Sistema.SeleccionarCirculo(-1);
	Sistema.SeleccionarFlecha(-1);

	// Al principio es moore
	Sistema.ActualizarTipo(0);
	Sistema.ActualizarNumCarEnt(5);
	Sistema.ActualizarNumCarSal(5);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BotonIzquierdoCirculo(void)
{
	// Poner Circulo
	if((Sistema.RatonEncimaCirculo() == -1) && (Sistema.RatonEncimaFlecha() == -1))
	{
		Sistema.InicializarCirculo();

		/* if (Sistema.RatonCercaAlgo(Radio*3)==true) { Sistema.CirculoMoviendo(true); } */
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BotonIzquierdoFlecha(void)
{
	if(Sistema.RatonEncimaCirculo() != -1)
	{
		Sistema.SeleccionarCirculo(Sistema.RatonEncimaCirculo());
		Sistema.InicializarFlecha();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BotonIzquierdoPuntero(void)
{
	// Mover Flecha
	if(Sistema.RatonEncimaFlecha() != -1)
	{
		Sistema.SeleccionarFlecha(Sistema.RatonEncimaFlecha());
		Sistema.FlechaMoviendo(true);
	}

	// Mover Circulo
	if(Sistema.RatonEncimaCirculo() != -1)
	{
		Sistema.SeleccionarCirculo(Sistema.RatonEncimaCirculo());
		Sistema.CirculoMoviendo(true);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BotonIzquierdo(void)
{
	if(Form2->ActiveControl == Form2->BotonCirculo) BotonIzquierdoCirculo();
	if(Form2->ActiveControl == Form2->BotonFlecha) BotonIzquierdoFlecha();
	if(Form2->ActiveControl == Form2->BotonPuntero) BotonIzquierdoPuntero();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BotonDerechoPuntero(void)
{
	// Borrar Circulo
	if(Sistema.CirculoSeleccionado() != -1)
	{
		if(Sistema.RatonEncimaCirculo() == Sistema.CirculoSeleccionado())
		{
			Sistema.BorrarCirculo();
		}
	}

	// Borrar Flecha
	if(Sistema.FlechaSeleccionada() != -1)
	{
		if(Sistema.RatonEncimaFlecha() == Sistema.FlechaSeleccionada())
		{
			Sistema.BorrarFlecha();
		}
	}

	// Si estoy en puntero siempre deseleciono al pulsar el boton derecho
	Sistema.SeleccionarCirculo(-1);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BotonDerechoOtro(void)
{
	// Poner en modo puntero
	if(Sistema.EstaFlechaMoviendose() == false)
	{
		// Si estaba en BotonFlecha Pongo a enabled los otros dos
		if(Form2->ActiveControl == Form2->BotonFlecha)
		{
			Form2->BotonPuntero->Enabled = true;
			Form2->BotonCirculo->Enabled = true;
			Sistema.ActualizarValorSale(Sistema.NumFlechas(), -1);
			Sistema.ActualizarValorEntra(Sistema.NumFlechas(), 0);
		}

		Form2->ActiveControl = Form2->BotonPuntero;

		// Y deselecciono
		Sistema.SeleccionarCirculo(-1);
		Form2->Show();
	}
	else
		Form1Boole2->BarraEstado->SimpleText = MENSAJE(msgColocarFlecha);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BotonDerecho(void)
{
	if(Form2->ActiveControl == Form2->BotonPuntero)
		BotonDerechoPuntero();
	else
		BotonDerechoOtro();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::TableroMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(!simulando)
	{
		if(Button == mbLeft) BotonIzquierdo();
		if(Button == mbRight) BotonDerecho();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::TableroMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(!simulando)
	{
		if(Sistema.RatonCercaAlgo(Radio * 3) == false)
		{
			Sistema.CirculoMoviendo(false);
		}

		Sistema.CirculoMoviendo(false);
		Sistema.FlechaMoviendo(false);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::BorrarClick(TObject *Sender)
{
	Sistema.BorrarCirculo();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::FormShow(TObject *Sender)
{


	Tablero->Visible = false;
	simulando = false;
	grabaste = 1;

	// Tablero->Height = ClientHeight; Tablero->Width = ClientWidth;
	Form1Boole2->Tablero->Canvas->Refresh();

  pTextAsoc->Visible = false;
  mnTextoAsociado->Checked = false;

	if(BarradeBotones1->Checked == true)
	{
		Form2->Show();
	}
	else
	{
		Form2->Hide();
	}
	if(mnTextoAsociado->Checked == true)
	{
		pTextAsoc->Visible = true;
	}
	else
	{
		pTextAsoc->Visible = false;
	}
  txAsociado->Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::Deseleccionar(void)
{
	Sistema.SeleccionarCirculo(-1);
	Sistema.SeleccionarFlecha(-1);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonEtEstadoMoore(AnsiString et1, AnsiString et2)
{
	if(Sistema.CirculoSeleccionado() != -1)
	{
		Sistema.ActualizarEtiqueta1Circulo(Sistema.CirculoSeleccionado(), et1);
		Sistema.ActualizarEtiqueta2Circulo(Sistema.CirculoSeleccionado(), et2);
	}

	Deseleccionar();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonEtTransicionMoore(AnsiString et)
{
	if(Sistema.FlechaSeleccionada() != -1)
	{
		Sistema.ActualizarEtiqueta1Flecha(Sistema.FlechaSeleccionada(), et);
	}

	Deseleccionar();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonEtTransicionMealy(AnsiString et1, AnsiString et2)
{
	if(Sistema.FlechaSeleccionada() != -1)
	{
		Sistema.ActualizarEtiqueta1Flecha(Sistema.FlechaSeleccionada(), et1);
		Sistema.ActualizarEtiqueta2Flecha(Sistema.FlechaSeleccionada(), et2);
	}

	Deseleccionar();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonEtEstadoMealy(AnsiString et)
{
	if(Sistema.CirculoSeleccionado() != -1)
	{
		Sistema.ActualizarEtiqueta1Circulo(Sistema.CirculoSeleccionado(), et);
	}

	Deseleccionar();
}

/*
 =======================================================================================================================
    void TForm1Boole2::PonEtMoore(AnsiString et) { if (Sistema.CirculoSeleccionado()!=-1)
    {Sistema.ActualizarEtiqueta2Circulo(Sistema.CirculoSeleccionado(),et);} if (Sistema.FlechaSeleccionada()!=-1)
    {Sistema.ActualizarEtiqueta1Flecha(Sistema.FlechaSeleccionada(),et);} Deseleccionar(); } void
    TForm1Boole2::PonEtMealy(AnsiString et1,AnsiString et2) { if (Sistema.FlechaSeleccionada()!=-1) {
    Sistema.ActualizarEtiqueta1Flecha(Sistema.FlechaSeleccionada(),et1);
    Sistema.ActualizarEtiqueta2Flecha(Sistema.FlechaSeleccionada(),et2); } Deseleccionar(); }
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::TableroDblClick(TObject *Sender)
{
	if(!simulando)
	{
		if(Form2->ActiveControl == Form2->BotonPuntero)
		{
			if((Sistema.RatonEncimaCirculo() == Sistema.CirculoSeleccionado()) && (Sistema.RatonEncimaCirculo() != -1))
			{
				if(Sistema.DevolverTipo() == 0)
				{
					// Moore circulo
					Form1Boole2->Timer1->Enabled = false;
					Form1Boole2->Enabled = false;
					Form13->Show();
					Form13->Edit2->MaxLength = Form1Boole2->DameNumCarSal();
					Form13->Edit2->Text = Sistema.DevolverCirculo(Sistema.CirculoSeleccionado()).DevolverEtiqueta2();
					Form13->Edit1->Text = Sistema.DevolverCirculo(Sistema.CirculoSeleccionado()).DevolverEtiqueta1();
					Form13->SetFocus();
				}

				if(Sistema.DevolverTipo() == 1)
				{
					// Mealy circulo
					Form1Boole2->Timer1->Enabled = false;
					Form1Boole2->Enabled = false;
					Form3->Show();
					Form3->Edit1->Text = Sistema.DevolverCirculo(Sistema.CirculoSeleccionado()).DevolverEtiqueta1();
					Form3->SetFocus();
				}
			}

			if((Sistema.RatonEncimaFlecha() == Sistema.FlechaSeleccionada()) && (Sistema.RatonEncimaFlecha() != -1))
			{
				if(Sistema.DevolverTipo() == 0)
				{
					// moore flecha
					Form1Boole2->Timer1->Enabled = false;
					Form1Boole2->Enabled = false;
					Form12->Show();
					Form12->Edit1->MaxLength = Form1Boole2->DameNumCarEnt();
					Form12->Edit1->Text = Sistema.DevolverFlecha(Sistema.FlechaSeleccionada()).DevolverEtiqueta1();
					Form12->SetFocus();
				}
				else
				// if (Sistema.DevolverTipo()==1)
				{
					// mealy flecha
					Form1Boole2->Timer1->Enabled = false;
					Form1Boole2->Enabled = false;
					Form5->Show();
					Form5->Edit1->Text = Sistema.DevolverFlecha(Sistema.FlechaSeleccionada()).DevolverEtiqueta1();
					Form5->Edit2->Text = Sistema.DevolverFlecha(Sistema.FlechaSeleccionada()).DevolverEtiqueta2();
					Form5->SetFocus();
				}
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::Nuevo(void)
{
	Sistema.SeleccionarCirculo(-1);
	Sistema.SeleccionarFlecha(-1);
	Sistema.ActualizarNumCirculos(0);
	Sistema.ActualizarNumFlechas(0);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonerTipo(int t)
{
	Sistema.ActualizarTipo(t);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::DarTipo(void)
{
	return Sistema.DevolverTipo();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Nuevo1Click(TObject *Sender)
{
	// al crear uno nuevo si no ha grabado le aviso
	if(grabaste == 0)
	{
		switch
		(
			MessageBox
				(
					Handle,
					MENSAJE(msgCrearNuevo),
					"Confimation",
					MB_YESNOCANCEL | MB_ICONQUESTION
				)
		)
		{
		case ID_YES:
			{
				Form1Boole2->Timer1->Enabled = false;
				Form1Boole2->Enabled = false;
				NewDiagramForm->Show();
				NewDiagramForm->SetFocus();
				grabaste = 1;
        txAsociado->Lines->Clear();

				break;
			}

		case ID_NO:
			Guardar1Click(Sender);
		}
	}
	else
	{
		Form1Boole2->Timer1->Enabled = false;
		Form1Boole2->Enabled = false;
		NewDiagramForm->Show();
		NewDiagramForm->SetFocus();
		grabaste = 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::BarradeBotones1Click(TObject *Sender)
{
	if(BarradeBotones1->Checked == false)
	{
		Form2->Show();
		BarradeBotones1->Checked = true;
	}
	else
	{
		Form2->Hide();
		BarradeBotones1->Checked = false;
	}

	Form1Boole2->SetFocus();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::General1Click(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	Form1Boole2->Enabled = false;
	Form6->Show();
	Form6->SetFocus();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::DameRadio(void)
{
	return Radio;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonRadio(int r)
{
	Radio = r;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonColFon(int c)
{
	ColFon = (TColor) c;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::DameColFon(void)
{
	return(TColor) ColFon;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonObjMov(int c)
{
	ObjMov = (TColor) c;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonObjSel(int c)
{
	ObjSel = (TColor) c;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::DameObjMov(void)
{
	return(TColor) ObjMov;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::DameObjSel(void)
{
	return(TColor) ObjSel;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::DameNumCarEnt(void)
{
	return Sistema.DevolverNumCarEnt();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonerNumCarEnt(int nc)
{
	Sistema.ActualizarNumCarEnt(nc);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::DameNumCarSal(void)
{
	return Sistema.DevolverNumCarSal();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonerNumCarSal(int nc)
{
	Sistema.ActualizarNumCarSal(nc);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ProcesarCodigo(AnsiString Titulo)
{
	/*~~~~~~~~~~~~*/
	AnsiString	Aux;
	/*~~~~~~~~~~~~*/

	Form8->Codigo->Lines->Clear();

	// Pongo el titulo a 15 caracteres
	if(Titulo.Length() > 15)
	{
		Titulo.SetLength(15);
	}

	// Caracteristicas
	Form8->Codigo->SelAttributes->Style = Form8->Codigo->SelAttributes->Style << fsBold;
	Form8->Codigo->SelAttributes->Color = clRed;
	Form8->Codigo->Lines->Add("[Caracteristicas]");

	Form8->Codigo->SelAttributes->Style = Form8->Codigo->SelAttributes->Style >> fsBold;
	Form8->Codigo->SelAttributes->Color = clBlack;

	// Titulo
	Aux = "  Titulo: ";
	Aux += Titulo;
	Form8->Codigo->SelAttributes->Color = clWhite;
	Form8->Codigo->Lines->Add(Aux);

	Form8->Codigo->SelAttributes->Color = clBlack;

	// Tipo de automata
	Aux = "  Tipo: ";
	if(Form1Boole2->DarTipo() == 0)
		Aux += "Moore";
	else
		Aux += "Mealy";
	Form8->Codigo->Lines->Add(Aux);

	// numero de circulos
	Aux = "  Nº Estados: ";
	Aux += Sistema.NumCirculos();
	Form8->Codigo->Lines->Add(Aux);

	// numero de flechas
	Aux = "  Nº Trans: ";
	Aux += Sistema.NumFlechas();
	Form8->Codigo->Lines->Add(Aux);

	// caracteres de entrada
	Aux = "  Vars Entrada: ";
	Aux += Sistema.DevolverNumCarEnt();
	Form8->Codigo->Lines->Add(Aux);

	// Guardo la var de entrada
	for(int i = 0; i <= Sistema.DevolverNumCarEnt() - 1; i++)
	{
		Aux = "      ";
		Aux += Vars[i];
		Form8->Codigo->Lines->Add(Aux);
	}

	// caracteres de salida
	Aux = "  Vars Salida: ";
	Aux += Sistema.DevolverNumCarSal();
	Form8->Codigo->Lines->Add(Aux);

	// guardo las var de salida
	for(int i = 0; i <= Sistema.DevolverNumCarSal() - 1; i++)
	{
		Aux = "      ";
		Aux += Vars[i + 5];

		Form8->Codigo->Lines->Add(Aux);
	}

	// Estados
	Form8->Codigo->SelAttributes->Style = Form8->Codigo->SelAttributes->Style << fsBold;
	Form8->Codigo->SelAttributes->Color = clRed;
	Form8->Codigo->Lines->Add("[Estados]");

	Form8->Codigo->SelAttributes->Style = Form8->Codigo->SelAttributes->Style >> fsBold;
	Form8->Codigo->SelAttributes->Color = clBlack;
	for(int i = 0; i < Sistema.NumCirculos(); i++)
	{
		Form8->Codigo->SelAttributes->Color = clGreen;
		Aux = "  [E";
		Aux += i;
		Aux += "]";
		Form8->Codigo->Lines->Add(Aux);

		Form8->Codigo->SelAttributes->Color = clBlack;

		// /nombre
		Aux = "    Nombre: ";
		Aux += Sistema.DevolverCirculo(i).DevolverEtiqueta1();
		Form8->Codigo->Lines->Add(Aux);

		// /x
		Aux = "    Coord X: ";
		Aux += Sistema.DevolverCirculo(i).CoordenadaCirculoX();
		Form8->Codigo->Lines->Add(Aux);

		// /y
		Aux = "    Coord Y: ";
		Aux += Sistema.DevolverCirculo(i).CoordenadaCirculoY();
		Form8->Codigo->Lines->Add(Aux);

		// variable de salida solo si es moore
		if(Form1Boole2->DarTipo() == 0)
		{
			Aux = "    Salida: ";
			Aux += Sistema.DevolverCirculo(i).DevolverEtiqueta2();
			Form8->Codigo->Lines->Add(Aux);
		}
	}

	// Transiciones
	Form8->Codigo->SelAttributes->Style = Form8->Codigo->SelAttributes->Style << fsBold;
	Form8->Codigo->SelAttributes->Color = clRed;
	Form8->Codigo->Lines->Add("[Transiciones]");

	Form8->Codigo->SelAttributes->Style = Form8->Codigo->SelAttributes->Style >> fsBold;
	Form8->Codigo->SelAttributes->Color = clBlack;
	for(int i = 0; i < Sistema.NumFlechas(); i++)
	{
		Form8->Codigo->SelAttributes->Color = clGreen;
		Aux = "  [E";
		Aux += Sistema.DevolverFlecha(i).FlechaCirculoSale();
		Aux += " - E";
		Aux += Sistema.DevolverFlecha(i).FlechaCirculoEntra();
		Aux += "]";
		Form8->Codigo->Lines->Add(Aux);

		Form8->Codigo->SelAttributes->Color = clBlack;

		// /x
		Aux = "    Coord X: ";
		Aux += Sistema.DevolverFlecha(i).CoordenadaFlechaX();
		Form8->Codigo->Lines->Add(Aux);

		// /y
		Aux = "    Coord Y: ";
		Aux += Sistema.DevolverFlecha(i).CoordenadaFlechaY();
		Form8->Codigo->Lines->Add(Aux);

		// variable de entrada
		if(Form1Boole2->DarTipo() == 0)
		{
			Aux = "    Entrada: ";
			Aux += Sistema.DevolverFlecha(i).DevolverEtiqueta1();
			Form8->Codigo->Lines->Add(Aux);
		}
		else
		// ambas variables si es mealy
		{
			Aux = "    Entrada: ";
			Aux += Sistema.DevolverFlecha(i).DevolverEtiqueta1();
			Form8->Codigo->Lines->Add(Aux);

			Aux = "    Salida: ";
			Aux += Sistema.DevolverFlecha(i).DevolverEtiqueta2();
			Form8->Codigo->Lines->Add(Aux);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Salvar(AnsiString nombre)
{
	// Salvo el fichero de texto
	Form8->Codigo->Lines->SaveToFile(nombre);

  Form1Boole2->txAsociado->Lines->SaveToFile(nombre + ".txt");

	// grabaste
	grabaste = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SalvarPDL(AnsiString nombre)
{
	// Salvo el fichero de texto del PLD
	Form14->PDL->Lines->SaveToFile(nombre);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Guardar1Click(TObject *Sender)
{
	if(SaveDialog1->Execute())
	{
		ProcesarCodigo(MENSAJE(msgSinTitulo));
		Salvar(SaveDialog1->FileName);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Salvar1Click(TObject *Sender)
{
	// Salvar el automata actual en modo texto
	Titulo = Form1Boole2->Caption;
	Titulo.Delete(Titulo.Length() - 8, 9);

	if(Titulo == MENSAJE(msgSinTitulo))
	{
		Guardar1Click(Sender);
	}
	else
	{
		ProcesarCodigo(Titulo);
		Titulo += ".aut";
		Salvar(Titulo);
	}
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString QuitaBlancosPrincipio(AnsiString a)
{
	if(a[1] == ' ')
	{
		a.TrimLeft();

		/*~~~~~~~~~~~~~~*/
		AnsiString	b = a;
		int			i = 1;
		/*~~~~~~~~~~~~~~*/

		while(a[i] == ' ')
		{
			i = i + 1;
		}

		b.Delete(1, i - 1);
		return b;
	}

	return a;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Cargar(void)
// "compila" el fichero de texto barraaux
{
	Form1Boole2->Nuevo();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	Aux, Titulo, Qsub;
	int			tipo, circ, fle, ent, sal, x, i, c, y;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Aux = Form8->Codigo->Lines->Strings[0];
	Aux = QuitaBlancosPrincipio(Aux);
	if(Aux == "[Caracteristicas]")
	{
		Aux = Form8->Codigo->Lines->Strings[1];
		Aux = QuitaBlancosPrincipio(Aux);
		Form1Boole2->Caption = Aux;
		if(Aux.SubString(1, 8) == "Titulo: ")
		{
			Titulo = Aux.SubString(9, Aux.Length());
			Aux = Form8->Codigo->Lines->Strings[2];
			Aux = QuitaBlancosPrincipio(Aux);
			if(Aux.SubString(1, 6) == "Tipo: ")
			{
				if(Aux.SubString(7, Aux.Length()) == "Mealy")
					tipo = 1;
				else
					tipo = 0;
				Aux = Form8->Codigo->Lines->Strings[3];
				Aux = QuitaBlancosPrincipio(Aux);
				if(Aux.SubString(1, 12) == "Nº Estados: ")
				{
					circ = Aux.SubString(13, Aux.Length()).ToInt();
					Aux = Form8->Codigo->Lines->Strings[4];
					Aux = QuitaBlancosPrincipio(Aux);
					if(Aux.SubString(1, 10) == "Nº Trans: ")
					{
						fle = Aux.SubString(11, Aux.Length()).ToInt();
						Aux = Form8->Codigo->Lines->Strings[5];
						Aux = QuitaBlancosPrincipio(Aux);
						if(Aux.SubString(1, 14) == "Vars Entrada: ")
						{
							ent = Aux.SubString(15, Aux.Length()).ToInt();

							// guardo los valores de las var de entrada
							for(int p = 0; p < ent; p++)
							{
								Aux = Form8->Codigo->Lines->Strings[6 + p];
								Vars[p] = QuitaBlancosPrincipio(Aux);
							}

							Aux = Form8->Codigo->Lines->Strings[6 + ent];
							Aux = QuitaBlancosPrincipio(Aux);
							if(Aux.SubString(1, 13) == "Vars Salida: ")
							{
								sal = Aux.SubString(14, Aux.Length()).ToInt();

								// guardo los valores de las var de salida
								for(int p = 0; p < sal; p++)
								{
									Aux = Form8->Codigo->Lines->Strings[7 + p + ent];
									Vars[p + 5] = QuitaBlancosPrincipio(Aux);
								}

								// Actualizo el sistema con los valores ya cargados
								Form1Boole2->PonerTipo(tipo);
								NewDiagramForm->Edit1->Text = Titulo;
                                                                Sistema.Titulo = Titulo;
								if(tipo == 1)
								{
									Titulo += " (Mealy).";
								}
								else
								{
									Titulo += " (Moore).";
								}

								Form1Boole2->Caption = Titulo;
								Sistema.ActualizarNumCarEnt(ent);
								Sistema.ActualizarNumCarSal(sal);
								Sistema.ActualizarNumCirculos(circ);
								Sistema.ActualizarNumFlechas(fle);

								//
								// con estos valores comienzo a rellenar los arrays;
								// Miro a ver si pone estados
								//
								Aux = Form8->Codigo->Lines->Strings[7 + ent + sal];
								Aux = QuitaBlancosPrincipio(Aux);
								if(Aux == "[Estados]")
								{
									// Coloco los circulos
									c = 8 + ent + sal;						// linea donde empiezan los circulos
									for(i = 0; i < circ; i++)
									{
										// miro a ver si pone el q sub algo correspondiente
										Aux = Form8->Codigo->Lines->Strings[i + c];
										c++;								// una linea mas
										Aux = QuitaBlancosPrincipio(Aux);
										Qsub = "[E";
										Qsub += i;
										Qsub += "]";
										if(Aux == Qsub)
										{
											// leo el nombre
											Aux = Form8->Codigo->Lines->Strings[i + c];
											c++;
											Aux = QuitaBlancosPrincipio(Aux);
											if(Aux.SubString(1, 8) == "Nombre: ")
											{
												Sistema.ActualizarEtiqueta1Circulo(i, Aux.SubString(9, Aux.Length()));

												// leo la x
												Aux = Form8->Codigo->Lines->Strings[i + c];
												c++;
												Aux = QuitaBlancosPrincipio(Aux);
												if(Aux.SubString(1, 9) == "Coord X: ")
												{
													x = Aux.SubString(10, Aux.Length()).ToInt();

													// leo la y
													Aux = Form8->Codigo->Lines->Strings[i + c];
													c++;
													Aux = QuitaBlancosPrincipio(Aux);
													if(Aux.SubString(1, 9) == "Coord Y: ")
													{
														y = Aux.SubString(10, Aux.Length()).ToInt();
														Sistema.ActualizarCirculo(i, x, y);

														// si es mnoore leo la etiqueta de salida
														if(tipo == 0)
														{
															Aux = Form8->Codigo->Lines->Strings[i + c];
															c++;
															Aux = QuitaBlancosPrincipio(Aux);
															if(Aux.SubString(1, 8) == "Salida: ")
															{
																Sistema.ActualizarEtiqueta2Circulo
																	(
																		i,
																		Aux.SubString(9, Aux.Length())
																	);
															}
														}

														// si no es moore quito la etiqueta
														else
														{
															Sistema.ActualizarEtiqueta2Circulo(i, "");
														}

														c--;
													}
												}
											}
										}
									}										// q sub algo
								}											// estados
								c = c + i;									// linea donde pone transicciones
								Aux = Form8->Codigo->Lines->Strings[c];
								c++;
								Aux = QuitaBlancosPrincipio(Aux);
								if(Aux == "[Transiciones]")
								{
									// Coloco las flecha
									for(int j = 0; j < fle; j++)
									{
										// leo [qsub-qsub] y proceso
										Aux = Form8->Codigo->Lines->Strings[j + c];
										c++;
										Aux = QuitaBlancosPrincipio(Aux);
										Aux.Delete(1, 2);					// quito [E
										Aux.Delete(Aux.Length(), 1);		// quito ]

										if(Aux.SubString(1, 3)[3] == '-')	// solo un digito
										{
											Sistema.ActualizarValorSale(j, (Aux.SubString(1, 1)).ToInt());
											Aux.Delete(1, 5);
										}
										else
										{
											Sistema.ActualizarValorSale(j, (Aux.SubString(1, 2)).ToInt());
											Aux.Delete(1, 6);
										}

										Sistema.ActualizarValorEntra(j, Aux.ToInt());

										// leo la x
										Aux = Form8->Codigo->Lines->Strings[j + c];
										c++;
										Aux = QuitaBlancosPrincipio(Aux);
										if(Aux.SubString(1, 9) == "Coord X: ")
										{
											x = Aux.SubString(10, Aux.Length()).ToInt();

											// leo la y
											Aux = Form8->Codigo->Lines->Strings[j + c];
											c++;
											Aux = QuitaBlancosPrincipio(Aux);
											if(Aux.SubString(1, 9) == "Coord Y: ")
											{
												y = Aux.SubString(10, Aux.Length()).ToInt();
												Sistema.ActualizarFlecha(j, x, y);

												// leo la entrada
												Aux = Form8->Codigo->Lines->Strings[j + c];
												c++;
												Aux = QuitaBlancosPrincipio(Aux);
												if(Aux.SubString(1, 9) == "Entrada: ")
												{
													Sistema.ActualizarEtiqueta1Flecha
														(
															j,
															Aux.SubString(10, Aux.Length())
														);

													// leo la salida si es mealy
													if(tipo == 1)
													{
														Aux = Form8->Codigo->Lines->Strings[j + c];
														c++;
														Aux = QuitaBlancosPrincipio(Aux);
														if(Aux.SubString(1, 8) == "Salida: ")
														{
															Sistema.ActualizarEtiqueta2Flecha
																(
																	j,
																	Aux.SubString(9, Aux.Length())
																);
														}
													}
												}

												c--;
											}
										}
									}
								}
							}
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
void __fastcall TForm1Boole2::Cargar1Click(TObject *Sender)
{
	// cargart el automata actual en modo texto
	if(grabaste == 0)
	{
		switch
		(
			MessageBox
				(
					Handle,
					MENSAJE(msgAbrirNuevo),
					"Confimation",
					MB_YESNOCANCEL | MB_ICONQUESTION
				)
		)
		{
		case ID_YES:
			{
				if(OpenDialog1->Execute())
				{
					Form8->Codigo->Lines->LoadFromFile(OpenDialog1->FileName);
					Cargar();
					Titulo = Form1Boole2->Caption;
					Titulo.Delete(Titulo.Length() - 8, 9);
					ProcesarCodigo(Titulo);
          AnsiString nombreAsoc = OpenDialog1->FileName + ".txt";
          if (FileExists(nombreAsoc))
            txAsociado->Lines->LoadFromFile(nombreAsoc);
          else
            txAsociado->Clear();
  			}
				break;
			}

		case ID_NO:
			Guardar1Click(Sender);
		}
	}
	else
	{
		if(OpenDialog1->Execute())
		{
			Form8->Codigo->Lines->LoadFromFile(OpenDialog1->FileName);
			Cargar();
			Titulo = Form1Boole2->Caption;
			Titulo.Delete(Titulo.Length() - 8, 9);
			ProcesarCodigo(Titulo);
			Tablero->Visible = true;
      AnsiString nombreAsoc = OpenDialog1->FileName + ".txt";
      if (FileExists(nombreAsoc))
        txAsociado->Lines->LoadFromFile(nombreAsoc);
      else
        txAsociado->Clear();

		}
	}

	grabaste = 1;
	Form2->Show();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Timer1Timer(TObject *Sender)
{
	Sistema.RestauraSistema();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString Dec2Bin(AnsiString Numero)
{
	/*~~~~~~*/
	int Rango;
	/*~~~~~~*/

	Rango = 1;
	while(ElevarBase2(Rango) < Sistema.NumCirculos())
	{
		Rango++;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	AnsiString	binario, b;
	/*~~~~~~~~~~~~~~~~~~~*/

	binario = "";
	b = "";

	/*~~~~~~~~~~~*/
	int num, resto;
	/*~~~~~~~~~~~*/

	num = Numero.ToInt();
	resto = 0;
	for(int j = 0; j < Rango; j++)
	{
		// calculamos el nuero en binario
		resto = num % 2;
		num = num / 2;
		binario += resto;

		// pero lo guarda al reves
	}

	// me creo una nueva var b con el mismo num de car que binario
	for(int j = 0; j < Rango; j++)
	{
		b += "p";
	}

	// con lo cual que damos la vuelta a lo de lo cual
	for(int j = 1; j <= Rango; j++)
	{
		b[j] = binario[(Rango + 1) - j];
	}

	return b;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString Dec2BinFixed(AnsiString Numero, int fix)
{
	/*~~~~~~*/
	int Rango;
	/*~~~~~~*/

	Rango = 1;
	while(ElevarBase2(Rango) < fix)
	{
		Rango++;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	AnsiString	binario, b;
	/*~~~~~~~~~~~~~~~~~~~*/

	binario = "";
	b = "";

	/*~~~~~~~~~~~*/
	int num, resto;
	/*~~~~~~~~~~~*/

	num = Numero.ToInt();
	resto = 0;
	for(int j = 0; j < Rango; j++)
	{
		// calculamos el nuero en binario
		resto = num % 2;
		num = num / 2;
		binario += resto;

		// pero lo guarda al reves
	}

	// me creo una nueva var b con el mismo num de car que binario
	for(int j = 0; j < Rango; j++)
	{
		b += "p";
	}

	// con lo cual que damos la vuelta a lo de lo cual
	for(int j = 1; j <= Rango; j++)
	{
		b[j] = binario[(Rango + 1) - j];
	}

	return b;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString Parse(AnsiString Origen)
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	Destino;
	/*~~~~~~~~~~~~~~~~*/

	Destino = "";

	if(Origen == "")
	{
		Destino = "0";
		return Destino;
	}

	/*~~~~*/
	int pos;
	/*~~~~*/

	pos = 0;

	for(int i = 1; i <= Origen.Length(); i++)
	{
		if(Origen[i] == '1')
		{
			Destino += Form9->Excitacion->Cells[pos][0];
			Destino += " ";
			pos++;
		}
		else if(Origen[i] == '0')
		{
			Destino += "-";
			Destino += Form9->Excitacion->Cells[pos][0];
			Destino += " ";
			pos++;
		}
		else if(Origen[i] == '-')
		{
			pos++;
		}
		else if(Origen[i] == ',')
		{
			Destino += " ";
			Destino += "+";
			Destino += " ";
			pos = 0;
		}
	}

	if(Destino == "") Destino = "1";

	return Destino;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString ParseS(AnsiString Origen)
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	Destino;
	/*~~~~~~~~~~~~~~~~*/

	Destino = "";

	if(Origen == "")
	{
		Destino = "0";
		return Destino;
	}

	/*~~~~*/
	int pos;
	/*~~~~*/

	pos = 0;

	for(int i = 1; i <= Origen.Length(); i++)
	{
		if(Origen[i] == '1')
		{
			Destino += Form9->Excitacion->Cells[pos + Sistema.DevolverNumCarEnt()][0];
			Destino += " ";
			pos++;
		}
		else if(Origen[i] == '0')
		{
			Destino += "-";
			Destino += Form9->Excitacion->Cells[pos + Sistema.DevolverNumCarEnt()][0];
			Destino += " ";
			pos++;
		}
		else if(Origen[i] == '-')
		{
			pos++;
		}
		else if(Origen[i] == ',')
		{
			Destino += " ";
			Destino += "+";
			Destino += " ";
			pos = 0;
		}
	}

	if(Destino == "") Destino = "1";

	return Destino;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString ParseM(AnsiString Origen)
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	Destino;
	/*~~~~~~~~~~~~~~~~*/

	Destino = "";

	if(Origen == "")
	{
		Destino = "1";
		return Destino;
	}

	/*~~~~*/
	int pos;
	/*~~~~*/

	pos = 0;

	for(int i = 1; i <= Origen.Length(); i++)
	{
		if(Origen[i] == '1')
		{
			Destino += Form10->Excitacion->Cells[pos][0];
			Destino += " ";
			pos++;
		}
		else if(Origen[i] == '0')
		{
			Destino += "-";
			Destino += Form10->Excitacion->Cells[pos][0];
			Destino += " ";
			pos++;
		}
		else if(Origen[i] == '-')
		{
			pos++;
		}
		else if(Origen[i] == ',')
		{
			Destino += " ";
			Destino += "+";
			Destino += " ";
			pos = 0;
		}
	}

	if(Destino == "") Destino = "1";

	return Destino;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
char CalculaJ(char a, char b)
{
	/*~~~~~~*/
	char	r;
	/*~~~~~~*/

	r = 'x';

	if((a == '0') && (b == '0')) r = '0';
	if((a == '0') && (b == '1')) r = '1';
	if((a == '1') && (b == '0')) r = 'x';
	if((a == '1') && (b == '1')) r = 'x';

	return r;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
char CalculaK(char a, char b)
{
	/*~~~~~~*/
	char	r;
	/*~~~~~~*/

	r = 'x';

	if((a == '0') && (b == '0')) r = 'x';
	if((a == '0') && (b == '1')) r = 'x';
	if((a == '1') && (b == '0')) r = '1';
	if((a == '1') && (b == '1')) r = '0';

	return r;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TablaMealy(void)
{
	Form10->Solucion->Items->Clear();

	/*~~~~~~~*/
	/*
	 * for (int i=Form10->ListaJK->Items->Count-1;i>=0;i--){
	 * Form10->ListaJK->Items->Strings [i]=""; } for (int
	 * i=Form10->ListaD->Items->Count-1;i>=0;i--){ Form10->ListaD->Items->Strings
	 * [i]=""; } for (int i=Form10->ListaSol->Items->Count-1;i>=0;i--){
	 * Form10->ListaSol->Items->Strings [i]=""; } £
	 * ponemos los estados
	 */
	int Rango;
	int Limite;
	/*~~~~~~~*/

	Rango = 1;
	while(ElevarBase2(Rango) < Sistema.NumCirculos())
	{
		Rango++;
	}

	Limite = ElevarBase2(Rango);

	Form10->Errores->Items->Clear();

	/*~~~~~~~~~~~*/
	int col, row;
	int colc, rowc;
	/*~~~~~~~~~~~*/

	row = Sistema.NumCirculos();
	col = ElevarBase2(Sistema.DevolverNumCarEnt());
	colc = col;
	rowc = Limite;

	Form10->Tabla->ColCount = col + 1;
	Form10->Tabla->RowCount = row + 1;

	Form10->Tablacod->ColCount = colc + 1;
	Form10->Tablacod->RowCount = rowc + 1;

	// Limpiamos toda la tabla
	for(int i = 0; i <= col + 1; i++)
		for(int j = 0; j <= row + 1; j++) Form10->Tabla->Cells[i][j] = "";

	for(int i = 0; i <= colc + 1; i++)
		for(int j = 0; j <= rowc + 1; j++) Form10->Tablacod->Cells[i][j] = "";

	/*~~~~~~~~~~~~~~~*/
	AnsiString	estado;
	/*~~~~~~~~~~~~~~~*/

	for(int i = 1; i < row + 1; i++) Form10->Tabla->Cells[0][i] = Sistema.DevolverCirculo(i - 1).DevolverEtiqueta1();
	for(int i = 1; i < rowc + 1; i++) Form10->Tablacod->Cells[0][i] = Dec2Bin(i - 1);

	for(int i = 1; i <= col + 1; i++)
		Form10->Tabla->Cells[i][0] = Dec2BinFixed(i - 1, ElevarBase2(Sistema.DevolverNumCarEnt()));

	for(int i = 1; i <= colc + 1; i++)
		Form10->Tablacod->Cells[i][0] = Dec2BinFixed(i - 1, ElevarBase2(Sistema.DevolverNumCarEnt()));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// RELLENAMOS SEGUN el ARRAY DE FLECHAS
	int			e, s, n, numx, cuadrado;
	AnsiString	etiqueta, etiqueta2, et, error;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// recorremos todas las flechas
	for(int i = 0; i < Sistema.NumFlechas(); i++)
	{
		s = Sistema.DevolverFlecha(i).FlechaCirculoSale();
		etiqueta = Sistema.DevolverFlecha(i).DevolverEtiqueta1();
		etiqueta2 = Sistema.DevolverFlecha(i).DevolverEtiqueta2();
		e = Sistema.DevolverFlecha(i).FlechaCirculoEntra();
		if(etiqueta != "")
		{
			// miro el numero de x en la etiqueta
			numx = 0;

			for(int k = 0; k < Sistema.DevolverNumCarEnt(); k++)
			{
				if(etiqueta[k + 1] == 'X') numx++;
			}

			// calculo 2 a la numero de x
			cuadrado = 1;
			for(int p = 0; p < numx; p++)
			{
				cuadrado = 2 * cuadrado;
			}

			// el bucle segun el numero de x
			for(int buclex = 0; buclex < cuadrado; buclex++)
			{
				// me creo una nueva var et con el mismo num de car que etiqueta
				et = "";
				for(int j = 0; j < Sistema.DevolverNumCarEnt(); j++)
				{
					et += "e";
				}

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				//
				// coloco en las x por orden desde la parte derecha de la leyenda es decir 1x00x1
				// -> 100001 ->100011 -> 110001 ->....
				//
				int pos = Sistema.DevolverNumCarEnt();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				for(int k = 0; k < Sistema.DevolverNumCarEnt(); k++)
				{
					if(etiqueta[k + 1] == 'X')
					{
						et[k + 1] = Form10->Tabla->Cells[buclex + 1][0][pos];
						pos--;
					}
					else
					{
						et[k + 1] = etiqueta[k + 1];
					}
				}

				// busco la etiqueta entre todas las posibles
				for(int j = 0; j < col; j++)
				{
					if(et == Form10->Tabla->Cells[j + 1][0])
					{
						n = j;
					}
				}

				estado = "";
				estado += Sistema.DevolverCirculo(s).DevolverEtiqueta1();
				if(Form10->Tabla->Cells[n + 1][s + 1] != "")
				{
					error = "ERROR: Del estado ";
					error += estado;
					error += " salen al menos dos transacciones con ";
					error += et;
					error += ".";
					Form10->Errores->Items->Add(error);
				}

				estado = "";
				estado += Sistema.DevolverCirculo(e).DevolverEtiqueta1();
				estado += "/";
				estado += etiqueta2;
				Form10->Tabla->Cells[n + 1][s + 1] = estado;

				estado = "";
				estado += Dec2Bin(e);
				estado += "/";
				estado += etiqueta2;
				Form10->Tablacod->Cells[n + 1][s + 1] = estado;
			}	// fin bucle flechas
		}		// fin if flecha vacia
		else
		{
			estado = "";
			estado += Sistema.DevolverCirculo(s).DevolverEtiqueta1();
			error = "ERROR: Una transicion entre el estado ";
			error += estado;
			estado = "";
			estado += Sistema.DevolverCirculo(e).DevolverEtiqueta1();
			error += " y ";
			error += estado;
			error += " esta en blanco.";
			Form10->Errores->Items->Add(error);
		}
	}			// fin buclex

	for(int i = 0; i < col; i++)
		for(int j = 0; j < row; j++)
		{
			if(Form10->Tabla->Cells[i + 1][j + 1] == "") Form10->Tabla->Cells[i + 1][j + 1] = "X";
		}

	for(int i = 0; i < colc; i++)
	{
		for(int j = 0; j < rowc; j++)
		{
			/*~~~~~~~~~~~*/
			AnsiString	pa;
			/*~~~~~~~~~~~*/

			pa = "";
			for(int k = 0; k < Rango; k++) pa += "x";
			if(Form10->Tablacod->Cells[i + 1][j + 1] == "") Form10->Tablacod->Cells[i + 1][j + 1] = pa;
		}
	}

	// Warning int err; si no hay errores no muestro ni el label3 ni los errores
	if(Form10->Errores->Items->Count > 0)
	{
		Form10->GroupBox2->Show();
		Form10->Errores->Show();

		// Warning err=0;
	}
	else
	{
		Form10->GroupBox2->Hide();
		Form10->Errores->Hide();

		// Warning err=1;
	}

	// Tabla de codificacion de estados
	row = Limite;
	col = 1;

	Form10->Codifica->RowCount = row + 1;
	Form10->Codifica->ColCount = col + 1;

	Form10->Codifica->Cells[1][0] = "Qi";

	for(int i = 1; i < row + 1; i++)
	{
		if(i < Sistema.NumCirculos() + 1)
			Form10->Codifica->Cells[0][i] = Sistema.DevolverCirculo(i - 1).DevolverEtiqueta1();
		else
			Form10->Codifica->Cells[0][i] = "X";
		Form10->Codifica->Cells[1][i] = Dec2Bin(i - 1);
	}

	// Tabla de excitacion de biestables
	col = Sistema.DevolverNumCarEnt() + (Rango * 5) + Sistema.DevolverNumCarSal();
	row = ElevarBase2(Sistema.DevolverNumCarEnt() + Rango);

	Form10->Excitacion->ColCount = col;
	Form10->Excitacion->RowCount = row + 1;

	// Limpiamos toda la tabla
	for(int i = 0; i <= col; i++)
		for(int j = 0; j <= row + 1; j++)
		{
			Form10->Excitacion->Cells[i][j] = "";
		}

	for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
		Form10->Excitacion->Cells[Sistema.DevolverNumCarEnt() - i - 1][0] = Vars[i];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int sd = Sistema.DevolverNumCarEnt();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < Rango; i++)
	{
		/*~~~~~~~~~~*/
		AnsiString	a;
		/*~~~~~~~~~~*/

		a = "q";
		a += i;
		Form10->Excitacion->Cells[sd + Rango - i - 1][0] = a;

		a = "Q";
		a += i;

		// a+=" (t+1)";
		Form10->Excitacion->Cells[sd + Rango + Rango - i - 1][0] = a;

		a = "J";
		a += i;
		Form10->Excitacion->Cells[sd + Rango + Rango + Rango - i - 1][0] = a;

		a = "K";
		a += i;
		Form10->Excitacion->Cells[sd + Rango + Rango + Rango + Rango - i - 1][0] = a;

		a = "D";
		a += i;
		Form10->Excitacion->Cells[sd + Rango + Rango + Rango + Rango + Rango - i - 1][0] = a;
	}

	for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	{
		Form10->Excitacion->Cells[sd + Rango + Rango + Rango + Rango + Rango + i][0] = Vars[5 + Sistema.DevolverNumCarSal() - i - 1];
	}

	for(int j = 0; j < row; j++)
	{
		/*~~~~~~~~~~*/
		AnsiString	a;
		/*~~~~~~~~~~*/

		a = Dec2BinFixed(j, row);
		for(int i = 0; i < (Sistema.DevolverNumCarEnt() + Rango); i++) Form10->Excitacion->Cells[i][j + 1] = a[i + 1];
	}

	/*~~~*/
	int sx;
	/*~~~*/

	sx = Sistema.DevolverNumCarEnt() + Rango;

	for(int j = 0; j < row; j++)
	{
		/*~~~~~*/
		int x, y;
		/*~~~~~*/

		x = j / (Form10->Tablacod->RowCount - 1);
		y = j % (Form10->Tablacod->RowCount - 1);

		/*~~~~~~~~~~*/
		AnsiString	a;
		/*~~~~~~~~~~*/

		a = Form10->Tablacod->Cells[x + 1][y + 1];

		for(int i = 0; i < Rango; i++) Form10->Excitacion->Cells[sx + i][j + 1] = a[i + 1];
	}

	sx += Rango;

	for(int j = 0; j < row; j++)
	{
		// js
		for(int i = 0; i < Rango; i++)
		{
			/*~~~~~~~~~~~~~*/
			AnsiString	a, b;
			/*~~~~~~~~~~~~~*/

			a = Form10->Excitacion->Cells[sx - Rango - Rango + i][j + 1];
			b = Form10->Excitacion->Cells[sx - Rango + i][j + 1];
			Form10->Excitacion->Cells[sx + i][j + 1] = CalculaJ(a[1], b[1]);
		}

		// ks
		for(int i = 0; i < Rango; i++)
		{
			/*~~~~~~~~~~~~~*/
			AnsiString	a, b;
			/*~~~~~~~~~~~~~*/

			a = Form10->Excitacion->Cells[sx - Rango - Rango + i][j + 1];
			b = Form10->Excitacion->Cells[sx - Rango + i][j + 1];
			Form10->Excitacion->Cells[sx + Rango + i][j + 1] = CalculaK(a[1], b[1]);
		}

		// ds
		for(int i = 0; i < Rango; i++)
		{
			/*~~~~~~~~~~~~~*/
			AnsiString	a, b;
			/*~~~~~~~~~~~~~*/

			a = Form10->Excitacion->Cells[sx - Rango - Rango + i][j + 1];
			b = Form10->Excitacion->Cells[sx - Rango + i][j + 1];
			Form10->Excitacion->Cells[sx + Rango + Rango + i][j + 1] = b[1];
		}
	}

	for(int j = 0; j < row; j++)
	{
		/*~~~~~*/
		int x, y;
		/*~~~~~*/

		x = j / (Form10->Tablacod->RowCount - 1);
		y = j % (Form10->Tablacod->RowCount - 1);

		/*~~~~~~~~~~*/
		AnsiString	a;
		/*~~~~~~~~~~*/

		a = Form10->Tablacod->Cells[x + 1][y + 1];

		if(Rango >= a.Length()) a = a + " ";

		if(a[Rango + 1] == '/')
			a = a.SubString(Rango + 1 + 1, Sistema.DevolverNumCarSal());
		else
		{
			a = "";
			for(int k = 0; k < Sistema.DevolverNumCarSal(); k++) a += "x";
		}

		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
			Form10->Excitacion->Cells[sx + (Rango * 3) + i][j + 1] = a[i + 1];
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	un, eq, solu, solp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Form10->ListaJK->Items->Clear();
	Form10->ListaD->Items->Clear();
	Form10->ListaSol->Items->Clear();

	for(int i = 0; i < (Rango + 1) * 2; i++)
	{
		Form10->ListaJK->Items->Add("");
	}

	for(int i = 0; i < (Rango + 1); i++)
	{
		Form10->ListaD->Items->Add("");
	}

	for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	{
		Form10->ListaSol->Items->Add("");
	}

	for(int i = 0; i < Rango; i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 0; j < row; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	t = Form10->Excitacion->Cells[sx + i][j + 1];	// Modificado Ricardo.
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			if(Form10->Excitacion->Cells[sx + i][j + 1] == "1")
			{
				un += j;
				if(j < (row - 1)) un += ",";
			}

			if(Form10->Excitacion->Cells[sx + i][j + 1] == "x")
			{
				eq += j;
				if(j < (row - 1)) eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',') un = un.SubString(1, un.Length() - 1);

		solu = "J";

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// Modificado Ricardo
		int indice = Rango - 1 - i;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		solu += indice;

		// Modificado Ricardo
		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango+Sistema.DevolverNumCarEnt());
		solp = ParseM(solp);
		solu += solp;
		Form10->Solucion->Items->Add(solu);

		Form10->ListaJK->Items->Strings[indice * 2] = solu;
	}

	// kkkkkkkkkkkkkkkk
	for(int i = 0; i < Rango; i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 0; j < row; j++)
		{
			if(Form10->Excitacion->Cells[sx + Rango + i][j + 1] == "1")
			{
				un += j;
				if(j < (row - 1)) un += ",";
			}

			if(Form10->Excitacion->Cells[sx + Rango + i][j + 1] == "x")
			{
				eq += j;
				if(j < (row - 1)) eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',') un = un.SubString(1, un.Length() - 1);
		solu = "K";

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// Modificado Ricardo
		int indice = Rango - 1 - i;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		solu += indice;

		// Modificado Ricardo
		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango+Sistema.DevolverNumCarEnt());
		solp = ParseM(solp);
		solu += solp;
		Form10->Solucion->Items->Add(solu);
		Form10->ListaJK->Items->Strings[indice * 2 + 1] = solu;
	}

	// dddddddddddddddd
	for(int i = 0; i < Rango; i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 0; j < row; j++)
		{
			if(Form10->Excitacion->Cells[sx + Rango + Rango + i][j + 1] == "1")
			{
				un += j;
				if(j < (row - 1)) un += ",";
			}

			if(Form10->Excitacion->Cells[sx + Rango + Rango + i][j + 1] == "x")
			{
				eq += j;
				if(j < (row - 1)) eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',') un = un.SubString(1, un.Length() - 1);
		solu = "D";

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// Modificado Ricardo
		int indice = Rango - 1 - i;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		solu += indice;

		// Modificado Ricardo
		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango+Sistema.DevolverNumCarEnt());
		solp = ParseM(solp);
		solu += solp;
		Form10->Solucion->Items->Add(solu);

		// Form10->ListaD->Items->Add(solu);
		Form10->ListaD->Items->Strings[indice] = solu;
	}

	// ssssssssssssssssssss
	for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 0; j < row; j++)
		{
			if(Form10->Excitacion->Cells[sx + Rango + Rango + Rango + i][j + 1] == "1")
			{
				un += j;
				if(j < (row - 1)) un += ",";
			}

			if(Form10->Excitacion->Cells[sx + Rango + Rango + Rango + i][j + 1] == "x")
			{
				eq += j;
				if(j < (row - 1)) eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',') un = un.SubString(1, un.Length() - 1);

		solu = Vars[5 + Sistema.DevolverNumCarSal() - 1 - i];
		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango+Sistema.DevolverNumCarEnt());
		solp = ParseM(solp);
		solu += solp;
		Form10->Solucion->Items->Add(solu);
		Form10->ListaSol->Items->Strings[Sistema.DevolverNumCarSal() - 1 - i] = solu;
	}	// end-for.

	//
	// Modificado Ricardo
	// Se borran las posiciones que esten vacías y se da el formato necesario para que
	// el módulo de visualización del circuito reconozca las ecuaciones.
	//
	for(int i = Form10->ListaJK->Items->Count - 1; i >= 0; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	s = Form10->ListaJK->Items->Strings[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(s == "")
			Form10->ListaJK->Items->Delete(i);
		else
			Form10->ListaJK->Items->Strings[i] = Form1Boole2->darFormato(s);
	}

	for(int i = Form10->ListaD->Items->Count - 1; i >= 0; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	s = Form10->ListaD->Items->Strings[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(s == "")
			Form10->ListaD->Items->Delete(i);
		else
			Form10->ListaD->Items->Strings[i] = Form1Boole2->darFormato(s);;
	}

	for(int i = Form10->ListaSol->Items->Count - 1; i >= 0; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	s = Form10->ListaSol->Items->Strings[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(s == "")
			Form10->ListaSol->Items->Delete(i);
		else
			Form10->ListaSol->Items->Strings[i] = Form1Boole2->darFormato(s);
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	// Ponemos la tabla bonita...Las Js con las Ks...
	TStrings	**nuevosJK;
	/*~~~~~~~~~~~~~~~~~~~*/

	s = Sistema.DevolverNumCarEnt();
	nuevosJK = new TStrings *[2 * Rango];

	for(int i = 0; i < Rango; i++)
	{
		nuevosJK[2 * i] = new TStringList;
		nuevosJK[2 * i]->AddStrings(Form10->Excitacion->Cols[s + Rango + Rango + i]);
		nuevosJK[2 * i + 1] = new TStringList;
		nuevosJK[2 * i + 1]->AddStrings(Form10->Excitacion->Cols[s + Rango + Rango + Rango + i]);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	j = nuevosJK[2 * i]->Strings[0];
		AnsiString	k = nuevosJK[2 * i + 1]->Strings[0];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	}

	for(int i = 0; i < 2 * Rango; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int			col = s + Rango + Rango + i;
		AnsiString	actual = Form10->Excitacion->Cols[col]->Strings[0];
		AnsiString	nuevo = nuevosJK[i]->Strings[0];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Form10->Excitacion->Cols[col]->Clear();
		Form10->Excitacion->Cols[col]->AddStrings(nuevosJK[i]);
		delete nuevosJK[i];
	}

	delete nuevosJK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TablaMoore(void)
{
	Form9->Solucion->Items->Clear();

	/*~~~~~~~*/
	// ponemos los estados
	int Rango;
	int Limite;
	/*~~~~~~~*/

	Rango = 1;
	while(ElevarBase2(Rango) < Sistema.NumCirculos())
	{
		Rango++;
	}

	Limite = ElevarBase2(Rango);

	Form9->Errores->Items->Clear();

	/*~~~~~~~~~~~*/
	int col, row;
	int colc, rowc;
	/*~~~~~~~~~~~*/

	row = Sistema.NumCirculos();
	col = ElevarBase2(Sistema.DevolverNumCarEnt());
	colc = col;
	rowc = Limite;

	Form9->Tabla->ColCount = col + 1;
	Form9->Tabla->RowCount = row + 1;

	Form9->Tablacod->ColCount = colc + 1;
	Form9->Tablacod->RowCount = rowc + 1;

	// Limpiamos toda la tabla
	for(int i = 0; i <= col + 1; i++)
		for(int j = 0; j <= row + 1; j++) Form9->Tabla->Cells[i][j] = "";

	for(int i = 0; i <= colc + 1; i++)
		for(int j = 0; j <= rowc + 1; j++) Form9->Tablacod->Cells[i][j] = "";

	/*~~~~~~~~~~~~~~~*/
	AnsiString	estado;
	/*~~~~~~~~~~~~~~~*/

	for(int i = 1; i < row + 1; i++) Form9->Tabla->Cells[0][i] = Sistema.DevolverCirculo(i - 1).DevolverEtiqueta1();
	for(int i = 1; i < rowc + 1; i++) Form9->Tablacod->Cells[0][i] = Dec2Bin(i - 1);

	for(int i = 1; i <= col + 1; i++)
		Form9->Tabla->Cells[i][0] = Dec2BinFixed(i - 1, ElevarBase2(Sistema.DevolverNumCarEnt()));

	for(int i = 1; i <= colc + 1; i++)
		Form9->Tablacod->Cells[i][0] = Dec2BinFixed(i - 1, ElevarBase2(Sistema.DevolverNumCarEnt()));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// RELLENAMOS SEGUN el ARRAY DE FLECHAS
	int			e, s, n, numx, cuadrado;
	AnsiString	etiqueta, et, error;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// recorremos todas las flechas
	for(int i = 0; i < Sistema.NumFlechas(); i++)
	{
		s = Sistema.DevolverFlecha(i).FlechaCirculoSale();
		etiqueta = Sistema.DevolverFlecha(i).DevolverEtiqueta1();
		e = Sistema.DevolverFlecha(i).FlechaCirculoEntra();
		if(etiqueta != "")
		{
			// miro el numero de x en la etiqueta
			numx = 0;

			for(int k = 0; k < Sistema.DevolverNumCarEnt(); k++)
			{
				if(etiqueta[k + 1] == 'X') numx++;
			}

			// calculo 2 a la numero de x
			cuadrado = 1;
			for(int p = 0; p < numx; p++)
			{
				cuadrado = 2 * cuadrado;
			}

			// el bucle segun el numero de x
			for(int buclex = 0; buclex < cuadrado; buclex++)
			{
				// me creo una nueva var et con el mismo num de car que etiqueta
				et = "";
				for(int j = 0; j < Sistema.DevolverNumCarEnt(); j++)
				{
					et += "e";
				}

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				//
				// coloco en las x por orden desde la parte derecha de la leyenda es decir 1x00x1
				// -> 100001 ->100011 -> 110001 ->....
				//
				int pos = Sistema.DevolverNumCarEnt();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				for(int k = 0; k < Sistema.DevolverNumCarEnt(); k++)
				{
					if(etiqueta[k + 1] == 'X')
					{
						et[k + 1] = Form9->Tabla->Cells[buclex + 1][0][pos];
						pos--;
					}
					else
					{
						et[k + 1] = etiqueta[k + 1];
					}
				}

				// busco la etiqueta entre todas las posibles
				for(int j = 0; j < col; j++)
				{
					if(et == Form9->Tabla->Cells[j + 1][0])
					{
						n = j;
					}
				}

				estado = "";
				estado += Sistema.DevolverCirculo(s).DevolverEtiqueta1();
				if(Form9->Tabla->Cells[n + 1][s + 1] != "")
				{
					error = "ERROR: Del estado ";
					error += estado;
					error += " salen al menos dos transacciones con ";
					error += et;
					error += ".";
					Form9->Errores->Items->Add(error);
				}

				// estado="Q"; estado+=e;
				estado = Dec2Bin(e);
				Form9->Tabla->Cells[n + 1][s + 1] = Sistema.DevolverCirculo(e).DevolverEtiqueta1();
				Form9->Tablacod->Cells[n + 1][s + 1] = Dec2Bin(e);
			}	// fin bucle flechas
		}		// fin if flecha vacia
		else
		{
			estado = "";
			estado += Sistema.DevolverCirculo(s).DevolverEtiqueta1();
			error = "ERROR: Una transicion entre el estado ";
			error += estado;
			estado = "";
			estado += Sistema.DevolverCirculo(e).DevolverEtiqueta1();
			error += " y ";
			error += estado;
			error += " esta en blanco.";
			Form9->Errores->Items->Add(error);
		}
	}			// fin buclex

	for(int i = 0; i < col; i++)
		for(int j = 0; j < row; j++)
		{
			if(Form9->Tabla->Cells[i + 1][j + 1] == "") Form9->Tabla->Cells[i + 1][j + 1] = "X";
		}

	for(int i = 0; i < colc; i++)
	{
		for(int j = 0; j < rowc; j++)
		{
			/*~~~~~~~~~~~*/
			AnsiString	pa;
			/*~~~~~~~~~~~*/

			pa = "";
			for(int k = 0; k < Rango; k++) pa += "x";
			if(Form9->Tablacod->Cells[i + 1][j + 1] == "") Form9->Tablacod->Cells[i + 1][j + 1] = pa;
		}
	}

	// Tabla de salida codificada
	col = Rango + Sistema.DevolverNumCarSal();
	row = Limite;

	Form9->Salidacod->ColCount = col;
	Form9->Salidacod->RowCount = row + 1;

	for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	{
		Form9->Salidacod->Cells[col - i - 1][0] = Vars[i + 5];
	}

	for(int i = 0; i < Rango; i++) Form9->Salidacod->Cells[Rango - i - 1][0] = AnsiString("q") + i;

	for(int i = 0; i < row; i++)
	{
		/*~~~~~~~~~~~~~~~*/
		AnsiString	estado;
		/*~~~~~~~~~~~~~~~*/

		estado = Dec2Bin(i);
		for(int j = 0; j < Rango; j++) Form9->Salidacod->Cells[j][i + 1] = estado[j + 1];
	}

	for(int j = 0; j < row; j++)
	{
		/*~~~~~~~~~~*/
		AnsiString	a;
		/*~~~~~~~~~~*/

		if(j < Sistema.NumCirculos())
		{
			a = Sistema.DevolverCirculo(j).DevolverEtiqueta2();
		}

		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
		{
			if(j < Sistema.NumCirculos())
				Form9->Salidacod->Cells[col - i - 1][j + 1] = a[Sistema.DevolverNumCarSal() - i];
			else
				Form9->Salidacod->Cells[col - i - 1][j + 1] = "x";
		}
	}

	// Tabla de codificacion de estados y salidas
	row = Limite;
	col = 1;

	Form9->Codifica->RowCount = row + 1;
	Form9->Codifica->ColCount = 3;

	Form9->Codifica->Cells[1][0] = "Qi";
	Form9->Codifica->Cells[2][0] = MENSAJE(msgSalida);

	// Nombres de Estados y Codificacion
	for(int i = 1; i < row + 1; i++)
	{
		if(i < Sistema.NumCirculos() + 1)
		{
			Form9->Codifica->Cells[0][i] = Sistema.DevolverCirculo(i - 1).DevolverEtiqueta1();
			Form9->Codifica->Cells[2][i] = Sistema.DevolverCirculo(i - 1).DevolverEtiqueta2();
		}
		else
		{
			Form9->Codifica->Cells[0][i] = "X";
			Form9->Codifica->Cells[2][i] = AnsiString::StringOfChar('X', Sistema.DevolverNumCarSal());
		}

		Form9->Codifica->Cells[1][i] = Dec2Bin(i - 1);
	}

	// Salidas
	for(int i = 0; i < Sistema.NumCirculos(); i++)
	{
		if(Sistema.DevolverCirculo(i).DevolverEtiqueta2() == "")
		{
			{
				error = "ERROR: El estado ";
				error += Sistema.DevolverCirculo(i).DevolverEtiqueta1();
				error += " no tiene salida. ";
				Form9->Errores->Items->Add(error);
			}
		}
	}

	//
	// Form9->Codifica->Cells[2][Form9->Codifica->RowCount-1]="";
	// Warning int err; si no hay errores no muestro ni el label3 ni los errores
	//
	if(Form9->Errores->Items->Count > 0)
	{
		Form9->GroupBox2->Show();
		Form9->Errores->Show();

		// Warning err=0;
	}
	else
	{
		Form9->GroupBox2->Hide();
		Form9->Errores->Hide();

		// Warning err=1;
	}

	// Tabla de excitacion de biestables
	col = Sistema.DevolverNumCarEnt() + (Rango * 5);
	row = ElevarBase2(Sistema.DevolverNumCarEnt() + Rango);

	Form9->Excitacion->ColCount = col;
	Form9->Excitacion->RowCount = row + 1;

	// Limpiamos toda la tabla
	for(int i = 0; i <= col; i++)
		for(int j = 0; j <= row + 1; j++)
		{
			Form9->Excitacion->Cells[i][j] = "";
		}

	for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
		Form9->Excitacion->Cells[Sistema.DevolverNumCarEnt() - i - 1][0] = Vars[i];

	for(int i = 0; i < Rango; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int			s = Sistema.DevolverNumCarEnt();
		AnsiString	a;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		a = "q";
		a += i;
		Form9->Excitacion->Cells[s + Rango - i - 1][0] = a;

		a = "Q";
		a += i;

		// a+=" (t+1)";
		Form9->Excitacion->Cells[s + Rango + Rango - i - 1][0] = a;

		a = "J";
		a += i;
		Form9->Excitacion->Cells[s + Rango + Rango + Rango - i - 1][0] = a;

		a = "K";
		a += i;
		Form9->Excitacion->Cells[s + Rango + Rango + Rango + Rango - i - 1][0] = a;

		a = "D";
		a += i;
		Form9->Excitacion->Cells[s + Rango + Rango + Rango + Rango + Rango - i - 1][0] = a;
	}

	for(int j = 0; j < row; j++)
	{
		/*~~~~~~~~~~*/
		AnsiString	a;
		/*~~~~~~~~~~*/

		a = Dec2BinFixed(j, row);
		for(int i = 0; i < (Sistema.DevolverNumCarEnt() + Rango); i++) Form9->Excitacion->Cells[i][j + 1] = a[i + 1];
	}

	/*~~~*/
	int sx;
	/*~~~*/

	sx = Sistema.DevolverNumCarEnt() + Rango;

	for(int j = 0; j < row; j++)
	{
		/*~~~~~*/
		int x, y;
		/*~~~~~*/

		x = j / (Form9->Tablacod->RowCount - 1);
		y = j % (Form9->Tablacod->RowCount - 1);

		/*~~~~~~~~~~*/
		AnsiString	a;
		/*~~~~~~~~~~*/

		a = Form9->Tablacod->Cells[x + 1][y + 1];

		for(int i = 0; i < Rango; i++) Form9->Excitacion->Cells[sx + i][j + 1] = a[i + 1];
	}

	sx += Rango;

	for(int j = 0; j < row; j++)
	{
		// js
		for(int i = 0; i < Rango; i++)
		{
			/*~~~~~~~~~~~~~*/
			AnsiString	a, b;
			/*~~~~~~~~~~~~~*/

			a = Form9->Excitacion->Cells[sx - Rango - Rango + i][j + 1];
			b = Form9->Excitacion->Cells[sx - Rango + i][j + 1];
			Form9->Excitacion->Cells[sx + i][j + 1] = CalculaJ(a[1], b[1]);
		}

		// ks
		for(int i = 0; i < Rango; i++)
		{
			/*~~~~~~~~~~~~~*/
			AnsiString	a, b;
			/*~~~~~~~~~~~~~*/

			a = Form9->Excitacion->Cells[sx - Rango - Rango + i][j + 1];
			b = Form9->Excitacion->Cells[sx - Rango + i][j + 1];
			Form9->Excitacion->Cells[sx + Rango + i][j + 1] = CalculaK(a[1], b[1]);
		}

		// ds
		for(int i = 0; i < Rango; i++)
		{
			/*~~~~~~~~~~~~~*/
			AnsiString	a, b;
			/*~~~~~~~~~~~~~*/

			a = Form9->Excitacion->Cells[sx - Rango - Rango + i][j + 1];
			b = Form9->Excitacion->Cells[sx - Rango + i][j + 1];
			Form9->Excitacion->Cells[sx + Rango + Rango + i][j + 1] = b[1];
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	un, eq, solu, solp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Form9->ListaJK->Items->Clear();
	Form9->ListaD->Items->Clear();
	Form9->ListaSol->Items->Clear();

	for(int i = 0; i < (Rango + 1) * 2; i++)
	{
		Form9->ListaJK->Items->Add("");
	}

	for(int i = 0; i < (Rango + 1); i++)
	{
		Form9->ListaD->Items->Add("");
	}

	for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	{
		Form9->ListaSol->Items->Add("");
	}

	for(int i = 0; i < Rango; i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 0; j < row; j++)
		{
			if(Form9->Excitacion->Cells[sx + i][j + 1] == "1")
			{
				un += j;
				if(j < (row - 1)) un += ",";
			}

			if(Form9->Excitacion->Cells[sx + i][j + 1] == "x")
			{
				eq += j;
				if(j < (row - 1)) eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',') un = un.SubString(1, un.Length() - 1);

		solu = "J";

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// Modificado Ricardo
		int indice = Rango - 1 - i;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		solu += indice;

		// Modificado Ricardo
		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango+Sistema.DevolverNumCarEnt());
		solp = Parse(solp);
		solu += solp;
		Form9->Solucion->Items->Add(solu);
		Form9->ListaJK->Items->Strings[indice * 2] = solu;
	}

	// Marca kkkkkkkkkkkkkkkk
	for(int i = 0; i < Rango; i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 0; j < row; j++)
		{
			if(Form9->Excitacion->Cells[sx + Rango + i][j + 1] == "1")
			{
				un += j;
				if(j < (row - 1)) un += ",";
			}

			if(Form9->Excitacion->Cells[sx + Rango + i][j + 1] == "x")
			{
				eq += j;
				if(j < (row - 1)) eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',') un = un.SubString(1, un.Length() - 1);
		solu = "K";

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// Modificado Ricardo
		int indice = Rango - 1 - i;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		solu += indice;

		// Modificado Ricardo
		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango+Sistema.DevolverNumCarEnt());
		solp = Parse(solp);
		solu += solp;
		Form9->Solucion->Items->Add(solu);
		Form9->ListaJK->Items->Strings[indice * 2 + 1] = solu;
	}

	// dddddddddddddddd
	for(int i = 0; i < Rango; i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 0; j < row; j++)
		{
			if(Form9->Excitacion->Cells[sx + Rango + Rango + i][j + 1] == "1")
			{
				un += j;
				if(j < (row - 1)) un += ",";
			}

			if(Form9->Excitacion->Cells[sx + Rango + Rango + i][j + 1] == "x")
			{
				eq += j;
				if(j < (row - 1)) eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',') un = un.SubString(1, un.Length() - 1);
		solu = "D";

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// Modificado Ricardo
		int indice = Rango - 1 - i;
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		solu += indice;

		// Modificado Ricardo
		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango+Sistema.DevolverNumCarEnt());
		solp = Parse(solp);
		solu += solp;
		Form9->Solucion->Items->Add(solu);

		// Form9->ListaD->Items->Add(solu);
		Form9->ListaD->Items->Strings[indice] = solu;
	}

	// ssssssssssssssssssss
	for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
	{
		un = "";
		eq = "";
		solp = "";
		solu = "";

		for(int j = 1; j < Form9->Salidacod->RowCount; j++)
		{
			if(Form9->Salidacod->Cells[Rango + i][j] == "1")
			{
				un += j - 1;
				un += ",";
			}

			if(Form9->Salidacod->Cells[Rango + i][j] == "x")
			{
				eq += j - 1;
				eq += ",";
			}
		}

		if(un.Length() > 0)
			if(un[un.Length()] == ',')
				un = un.SubString(1, un.Length() - 1);

		/* solu="S"; solu+=Sistema.DevolverNumCarSal()-1-i; */
		solu = Vars[5 + Sistema.DevolverNumCarSal() - 1 - i];

		solu += "= ";
		solp = Form11->Simplifica(un, eq, Rango);
		solp = ParseS(solp);
		solu += solp;
		Form9->Solucion->Items->Add(solu);
		Form9->ListaSol->Items->Strings[Sistema.DevolverNumCarSal() - 1 - i] = solu;
	}			// end-for

	//
	// Modificado Ricardo
	// Se borran las posiciones que esten vacías y se da el formato necesario para que
	// el módulo de visualización del circuito reconozca las ecuaciones.
	//
	for(int i = Form9->ListaJK->Items->Count - 1; i >= 0; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	s = Form9->ListaJK->Items->Strings[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(s == "")
			Form9->ListaJK->Items->Delete(i);
		else
			Form9->ListaJK->Items->Strings[i] = Form1Boole2->darFormato(s);
	}

	for(int i = Form9->ListaD->Items->Count - 1; i >= 0; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	s = Form9->ListaD->Items->Strings[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(s == "")
			Form9->ListaD->Items->Delete(i);
		else
			Form9->ListaD->Items->Strings[i] = Form1Boole2->darFormato(s);;
	}

	for(int i = Form9->ListaSol->Items->Count - 1; i >= 0; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	s = Form9->ListaSol->Items->Strings[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(s == "")
			Form9->ListaSol->Items->Delete(i);
		else
			Form9->ListaSol->Items->Strings[i] = Form1Boole2->darFormato(s);
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	// Ponemos la tabla bonita...Las Js con las Ks...
	TStrings	**nuevosJK;
	/*~~~~~~~~~~~~~~~~~~~*/

	s = Sistema.DevolverNumCarEnt();
	nuevosJK = new TStrings *[2 * Rango];

	for(int i = 0; i < Rango; i++)
	{
		nuevosJK[2 * i] = new TStringList;
		nuevosJK[2 * i]->AddStrings(Form9->Excitacion->Cols[s + Rango + Rango + i]);
		nuevosJK[2 * i + 1] = new TStringList;
		nuevosJK[2 * i + 1]->AddStrings(Form9->Excitacion->Cols[s + Rango + Rango + Rango + i]);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	j = nuevosJK[2 * i]->Strings[0];
		AnsiString	k = nuevosJK[2 * i + 1]->Strings[0];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	}

	for(int i = 0; i < 2 * Rango; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int			col = s + Rango + Rango + i;
		AnsiString	actual = Form9->Excitacion->Cols[col]->Strings[0];
		AnsiString	nuevo = nuevosJK[i]->Strings[0];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Form9->Excitacion->Cols[col]->Clear();
		Form9->Excitacion->Cols[col]->AddStrings(nuevosJK[i]);
		delete nuevosJK[i];
	}

	delete nuevosJK;
}	// end-Moore.

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Tablas1Click(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	if(Sistema.DevolverTipo() == 0)
	{
		Form2->Hide();
		Form1Boole2->Enabled = false;

		//
		// FormCalculando->Show(); FormCalculando->SetFocus(); FormCalculando->Repaint();
		// Form1Boole2->Repaint();
		//
		TablaMoore();

		// FormCalculando->Close();
		Form9->Show();
		Form9->SetFocus();
	}
	else
	{
		Form2->Hide();
		Form1Boole2->Enabled = false;

		//
		// FormCalculando->Show(); FormCalculando->SetFocus(); FormCalculando->Repaint();
		// Form1Boole2->Repaint();
		//
		TablaMealy();

		// FormCalculando->Close();
		Form10->Show();
		Form10->SetFocus();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Resultados1Click(TObject *Sender)
{
	if(Sistema.NumCirculos() == 0)
	{
		Tablas1->Enabled = false;
		Reduccion->Enabled = false;
		Simulacion->Enabled = false;
		Batch->Enabled = false;
		InteractivaRapida->Enabled = false;
		BatchRapida->Enabled = false;
		Verificar->Enabled = false;
		VerificarCompletitud->Enabled = false;
		Equivalente->Enabled = false;
	}
	else
	{
		Tablas1->Enabled = true;
		Reduccion->Enabled = true;
		Simulacion->Enabled = true;
		Batch->Enabled = true;
 		InteractivaRapida->Enabled = true;
		BatchRapida->Enabled = true;
		Verificar->Enabled = true;
		VerificarCompletitud->Enabled = true;
		Equivalente->Enabled = true;

		if(Sistema.DevolverTipo() == 1)
		{	// Mealy
			Equivalente->Caption = MENSAJE(msgObtenerMoore);
		}
		else
		{	// Moore
			Equivalente->Caption = MENSAJE(msgObtenerMealy);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString TForm1Boole2::DevuelveVar(int i)
{
	return Vars[i];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::PonVar(int i, AnsiString S)
{
	Vars[i] = S;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int Cuadrado(int num)
// devuelve 2 a la num
{
	/*~~~~~~~~*/
	int cua = 1;
	/*~~~~~~~~*/

	for(int i = 0; i < num; i++)
	{
		cua = 2 * cua;
	}

	return cua;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PDLMealy(void)
{
	// Pequeño COMPILADOR :)))))
	Form14->PDL->Lines->Clear();

	/*~~~~~~~~~~~~~~~~~~*/
	AnsiString	eses, qus;
	/*~~~~~~~~~~~~~~~~~~*/

	if(Sistema.DevolverNumCarSal() == 1)
	{
		eses = "S0";
	}
	else
	{
		eses = "S[";
		eses += Sistema.DevolverNumCarSal() - 1;
		eses += "..0]";
	}

	if((Sistema.NumCirculos() == 1) || (Sistema.NumCirculos() == 2))
	{
		qus = "Q0";
	}
	else
	{
		// segun el nº de estados sran tantas ese como digitos binarios se necesiten
		qus = "Q[";

		/*~~~~~~*/
		int c = 0;
		/*~~~~~~*/

		while(Cuadrado(c) < Sistema.NumCirculos())
		{
			c++;
		}

		c--;
		qus += c;
		qus += "..0]";
	}

	/*~~~~~~~~~~~~*/
	AnsiString	aux;
	/*~~~~~~~~~~~~*/

	aux = "| ?";
	Form14->PDL->Lines->Add(aux);

	// pongo las entradas y salidas
	aux = "| in: (";
	for(int i = 1; i <= Sistema.DevolverNumCarEnt(); i++)
	{
		aux += Vars[i - 1];
		if(i != Sistema.DevolverNumCarEnt())
			aux += ",";
		else
			aux += "),	io: (";
	}

	aux += eses;
	aux += ",";
	aux += qus;
	aux += "),	clock: CLK";

	/*
	 * for (int i=1;i<=Sistema.DevolverNumCarSal();i++) { aux+=Vars[i+4]; if
	 * (i!=Sistema.DevolverNumCarSal()) aux+=","; else aux+="), clock: CLK"; }
	 */
	Form14->PDL->Lines->Add(aux);

	// pongo el reloj y las salidas
	aux = "| Register: CLK // ";

	/*
	 * for (int i=0;i<Sistema.NumCirculos();i++) {
	 * aux+=Sistema.DevolverCirculo(i).DevolverEtiqueta1(); if
	 * (i!=Sistema.NumCirculos()-1) aux+=","; }
	 */
	aux += qus;
	Form14->PDL->Lines->Add(aux);

	// linea en blanco
	Form14->PDL->Lines->Add("");

	// pongo el procedure
	aux = "| procedure: ";

	/*
	 * for (int i=0;i<Sistema.NumCirculos();i++) {
	 * aux+=Sistema.DevolverCirculo(i).DevolverEtiqueta1(); if
	 * (i!=Sistema.NumCirculos()-1) aux+=","; }
	 */
	aux += qus;
	Form14->PDL->Lines->Add(aux);
	Form14->PDL->Lines->Add("| {");

	// pongo el primer estado E0, el primero de nuestro array
	aux = "| States: ";
	aux += Sistema.DevolverCirculo(0).DevolverEtiqueta1();
	aux += " =0";
	Form14->PDL->Lines->Add(aux);

	// ahora todos los estados y sus transiciones
	Form14->PDL->Lines->Add("|");
	for(int i = 0; i < Sistema.NumCirculos(); i++)
	{
		aux = "| ";
		aux += Sistema.DevolverCirculo(i).DevolverEtiqueta1();
		aux += ".   ";
		for(int j = 0; j < Sistema.NumFlechas(); j++)
		{
			if(Sistema.DevolverFlecha(j).FlechaCirculoSale() == i)
			{
				/*~~~~~~~~~~~~~~~~*/
				AnsiString	auxf, s;
				/*~~~~~~~~~~~~~~~~*/

				auxf = Sistema.DevolverFlecha(j).DevolverEtiqueta1();

				// si el auxf esta vacio peta, con lo que lo controlo
				if(auxf != "")
				{
					s = "";
					for(int k = 0; k < Sistema.DevolverNumCarEnt(); k++)
					{
						if(auxf[k + 1] == '1')
						{
							s += Vars[k];

							// si no es el ultimo intercalo el &
							if(k != Sistema.DevolverNumCarEnt() - 1) s += " & ";
						}
						else if(auxf[k + 1] == '0')
						{
							s += Vars[k];
							s += "'";

							// si no es el ultimo intercalo el &
							if(k != Sistema.DevolverNumCarEnt() - 1) s += " & ";
						}
					}

					// controlo que no exista un & al final
					if(s.Length() > 2)
						if(s[s.Length() - 1] == '&') s = s.SubString(1, s.Length() - 3);

          if (s.Length()==0)
  					s += "     (";
          else
  					s += "   ? (";
					for(int p = 0; p < Sistema.DevolverNumCarSal(); p++)
					{
						s += "S";
						s += p;
						s += "=";
						s += Sistema.DevolverFlecha(j).DevolverEtiqueta2()[p + 1];
						if(p != Sistema.DevolverNumCarSal() - 1)
							s += " ";
						else
						{
							s += "   -> ";
							s += Sistema.DevolverCirculo(Sistema.DevolverFlecha(j).FlechaCirculoEntra()).DevolverEtiqueta1();
							s += ")";
						}
					}

					aux += s;
					Form14->PDL->Lines->Add(aux);
					aux = "|            ";
				}
			}	// if auxf=""
		}

		// el espacio entre estado y estado
		aux = "| ";
		Form14->PDL->Lines->Add(aux);
	}

	aux = "| }";
	Form14->PDL->Lines->Add(aux);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PDLMoore(void)
{
	// Otro pequeño COMPILADOR :)))))
	Form14->PDL->Lines->Clear();

	/*~~~~~~~~~~~~~~~~~~*/
	AnsiString	eses, qus;
	/*~~~~~~~~~~~~~~~~~~*/

	if(Sistema.DevolverNumCarSal() == 1)
	{
		eses = "S0";
	}
	else
	{
		eses = "S[";
		eses += Sistema.DevolverNumCarSal() - 1;
		eses += "..0]";
	}

	if((Sistema.NumCirculos() == 1) || (Sistema.NumCirculos() == 2))
	{
		qus = "Q0";
	}
	else
	{
		// segun el nº de estados sran tantas ese como digitos binarios se necesiten
		qus = "Q[";

		/*~~~~~~*/
		int c = 0;
		/*~~~~~~*/

		while(Cuadrado(c) < Sistema.NumCirculos())
		{
			c++;
		}

		c--;
		qus += c;
		qus += "..0]";
	}

	/*~~~~~~~~~~~~*/
	AnsiString	aux;
	/*~~~~~~~~~~~~*/

	aux = "| ?";
	Form14->PDL->Lines->Add(aux);

	// pongo las entradas y salidas
	aux = "| in: (";
	for(int i = 1; i <= Sistema.DevolverNumCarEnt(); i++)
	{
		aux += Vars[i - 1];
		if(i != Sistema.DevolverNumCarEnt())
			aux += ",";
		else
			aux += "),	io: (";
	}

	aux += eses;
	aux += ",";
	aux += qus;
	aux += "),	clock: CLK";

	/*
	 * for (int i=1;i<=Sistema.DevolverNumCarSal();i++) { aux+=Vars[i+4]; if
	 * (i!=Sistema.DevolverNumCarSal()) aux+=","; else aux+="), clock: CLK"; }
	 */
	Form14->PDL->Lines->Add(aux);

	// pongo el reloj y las salidas
	aux = "| Register: CLK // ";

	/*
	 * for (int i=0;i<Sistema.NumCirculos();i++) {
	 * aux+=Sistema.DevolverCirculo(i).DevolverEtiqueta1(); if
	 * (i!=Sistema.NumCirculos()-1) aux+=","; }
	 */
	aux += qus;
	Form14->PDL->Lines->Add(aux);

	// linea en blanco
	Form14->PDL->Lines->Add("");

	// pongo el procedure
	aux = "| procedure: ";

	/*
	 * for (int i=0;i<Sistema.NumCirculos();i++) {
	 * aux+=Sistema.DevolverCirculo(i).DevolverEtiqueta1(); if
	 * (i!=Sistema.NumCirculos()-1) aux+=","; }
	 */
	aux += qus;
	Form14->PDL->Lines->Add(aux);
	Form14->PDL->Lines->Add("| {");

	// pongo el primer estado E0, el primero de nuestro array
	aux = "| States: ";
	aux += Sistema.DevolverCirculo(0).DevolverEtiqueta1();
	aux += " =0";
	Form14->PDL->Lines->Add(aux);

	// ahora todos los estados y sus transiciones
	Form14->PDL->Lines->Add("|");
	for(int i = 0; i < Sistema.NumCirculos(); i++)
	{
		aux = "| ";
		aux += Sistema.DevolverCirculo(i).DevolverEtiqueta1();
		aux += "."; // el pto es para que el pdl diferencie
		aux += "	";

		// aux+="S"; aux+=i; aux+="=1";
		for(int p = 0; p < Sistema.DevolverNumCarSal(); p++)
		{
			aux += "S";
			aux += p;
			aux += "=";
			aux += Sistema.DevolverCirculo(i).DevolverEtiqueta2()[p + 1];
			if(p != Sistema.DevolverNumCarSal() - 1) aux += " ";
		}

		Form14->PDL->Lines->Add(aux);
		for(int j = 0; j < Sistema.NumFlechas(); j++)
		{
			/*~~~~~~~~~~~~~*/
			AnsiString	auxf;	// donde voy a guardar las et de las flechas
			//~~~~~~~~~~~~~

			if(Sistema.DevolverFlecha(j).FlechaCirculoSale() == i)
			{
				/*~~~~~~~~~~*/
				AnsiString	s;
				/*~~~~~~~~~~*/

				auxf = Sistema.DevolverFlecha(j).DevolverEtiqueta1();

				//
				// escaneo la cadena de la transicion
				// si el auxf esta vacio peta, con lo que lo controlo
				//
				if(auxf != "")
				{
					s = "";

					/*~~*/
					int k;
					/*~~*/

					for(k = 0; k < Sistema.DevolverNumCarEnt(); k++)
					{
						if(auxf[k + 1] == '1')
						{
							s += Vars[k];
						}
						else if(auxf[k + 1] == '0')
						{
							s += Vars[k];
							s += "'";
						}

						if(k != Sistema.DevolverNumCarSal() - 2)
						{
							// pongo siempre el &
							s += " & ";

							// pero si es una X lo quito
							if(auxf[k + 1] == 'X') s = s.SubString(1, s.Length() - 3);
						}
					}

					// controlo que no exista un & al final
          if (s.Length()==0)
  					s = "| 	" + s + "     -> ";
          else
          {
   					if(s[s.Length() - 1] == '&') s = s.SubString(1, s.Length() - 3);
  					s = "| 	" + s + "   ? -> ";
          }

 					s += Sistema.DevolverCirculo(Sistema.DevolverFlecha(j).FlechaCirculoEntra()).DevolverEtiqueta1();
					Form14->PDL->Lines->Add(s);
				}
			}					// if auxf vacio
		}

		Form14->PDL->Lines->Add("|");
	}

	aux = "| }";
	Form14->PDL->Lines->Add(aux);
}

//
// =======================================================================================================================
//    Modificado Ricardo.
// =======================================================================================================================
//
AnsiString TForm1Boole2::darFormato(AnsiString s)
{
	for(int i = 1; i < s.Length(); i++)
	{
		if(s[i] == ' ' && s[i + 1] == ' ')
		{
			s.Delete(i, 1);
		}

		if(s[i] == '-') s[i] = '~';

		if(s[i] == '=')
		{
			s[i + 1] = '(';
		}

		if(s[i] == ' ' && s[i + 1] == '+')
		{
			s[i] = ')';
		}

		if(s[i] == ' ' && s[i + 1] != ')')
		{
			s[i] = '*';
		}

		if(s[i] == '+' && s[i + 1] == ' ')
		{
			s[i + 1] = '(';
		}
	}

	if(s[s.Length()] == ' ')
		s[s.Length()] = ')';
	else
		s = s + ")";

	return s;
}

//
// =======================================================================================================================
//    Modificado Ricardo.
// =======================================================================================================================
//
void __fastcall TForm1Boole2::ExportaraPDL1Click(TObject *Sender)
{
	// El codigo PDl es diferente si se trata de Moore o Mealy
	if(Sistema.DevolverTipo() == 0)
		PDLMoore();
	else
		PDLMealy();

        
        // Bug fix: Filter needs to be set before execution. ~lrg
	SaveDialog2->Filter=MENSAJE(msgFiltroPLD);

	if(SaveDialog2->Execute())
	{
		SalvarPDL(SaveDialog2->FileName);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::CodigoPDL1Click(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	Form1Boole2->Enabled = false;
	if(Sistema.DevolverTipo() == MOORE)
		PDLMoore();
	else
		PDLMealy();
	Form14->Show();
	Form14->SetFocus();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Ver1Click(TObject *Sender)
{
	if(Sistema.NumCirculos() == 0)
        {
		CodigoPDL1->Enabled = false;
		CodigoVHDL1->Enabled = false;
        }
	else
        {
		CodigoPDL1->Enabled = true;
		CodigoVHDL1->Enabled = true;
        }
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Archivo1Click(TObject *Sender)
{
	if(Sistema.NumCirculos() == 0)
	{
		ExportaraPDL1->Enabled = false;
		ExportaraVHDL1->Enabled = false;

                ExportToWeblabInternal->Enabled = false;
                ExportToWeblabButton->Enabled = false;
                ExportToWeblabSwitch->Enabled = false;
                ExportToWeblabWeblab->Enabled = false;

		Imprimir1->Enabled = false;
                ExportaraJEDEC1->Enabled = false;
	}
	else
	{
		ExportaraPDL1->Enabled = true;
		ExportaraVHDL1->Enabled = true;
		Imprimir1->Enabled = true;
                ExportaraJEDEC1->Enabled=true;

                ExportToWeblabInternal->Enabled = true;
                ExportToWeblabButton->Enabled = true;
                ExportToWeblabSwitch->Enabled = true;
                ExportToWeblabWeblab->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Salir1Click(TObject *Sender)
{
	// al salir si no ha grabado le aviso
	if(grabaste == 0)
	{
		switch
		(
			MessageBox
				(
					Handle,
					MENSAJE(msgSalirSinGrabar),
					"Confimation",
					MB_YESNOCANCEL | MB_ICONQUESTION
				)
		)
		{
		case ID_YES:
			Form1Boole2->Close();	// exit(0); //Modificado Ricardo.
			Form2->Close();
			Principal->Show();
			break;
		case ID_NO:
			Guardar1Click(Sender);
		};
	}
	else
	{
		// exit(0); Modificado Ricardo.
		Form1Boole2->Close();
		Form2->Close();
		Principal->Show();
	}	// end-else.

	/*
	 * Form1Boole2->Timer1->Enabled=false;
	 * Form1Boole2->Tablero->Canvas->Brush->Style=bsSolid;
	 * Form1Boole2->Tablero->Canvas->Brush->Color=ColFon;
	 * Form1Boole2->Tablero->Canvas->Pen->Style=psSolid;
	 * Form1Boole2->Tablero->Canvas->Pen->Color=ColFon;
	 * Form1Boole2->Tablero->Canvas->Rectangle(0,0,Form1Boole2->Tablero->Width,Form1Boole2->Tablero->Height);
	 * Form1Boole2->Tablero->Canvas->Brush->Style=bsClear;
	 * Form1Boole2->Tablero->Canvas->Pen->Color=clBlack;
	 */
	Tablero->Refresh();

	Sistema.SeleccionarCirculo(-1);
	Sistema.SeleccionarFlecha(-1);

	// Al principio es moore
	Sistema.ActualizarTipo(0);
	Sistema.ActualizarNumCarEnt(5);
	Sistema.ActualizarNumCarSal(5);
	NewDiagramForm->Button1->Click();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Imprimir1Click(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	Form1Boole2->Enabled = false;
	Form15->Show();
	Form15->SetFocus();
}

//
// =======================================================================================================================
//    JAVI A partir de aqui comienzan los tratamientos para imprimir Se han tenido que copiar muchisimos metodos de la
//    impresión en pantalla para poderlos amoldar a la impresion por impresora
// =======================================================================================================================
//
void TForm1Boole2::ImprimirPLD(void)
{
	/*~~~~~~~~~~~~~~*/
	// Comienza la impresion de PLD
	AnsiString	Impri;
	/*~~~~~~~~~~~~~~*/

	if(Sistema.DevolverTipo() == 0)
		PDLMoore();
	else
		PDLMealy();
	Impri = ANSIMENSAJE(msgCodigoPLD) +" " + Form1Boole2->Caption;
	Form14->PDL->Print(Impri);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::ImprimirAUT(void)
{
	// Comienza la impresion de AUT
	Titulo = Form1Boole2->Caption;

	/*~~~~~~~~~~~~~~*/
	AnsiString	Impri;
	/*~~~~~~~~~~~~~~*/

	Impri = ANSIMENSAJE(msgFicheroAut)+" " + Form1Boole2->Caption;
	Titulo.Delete(Titulo.Length() - 8, 9);
	ProcesarCodigo(Titulo);
	Form8->Codigo->Print(Impri);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void DibujaSentidoImpri(int x1, int y1, int x2, int y2, int zoom)
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

	Printer()->Canvas->Brush->Style = bsSolid;
	Printer()->Canvas->Pen->Style = psSolid;

	/*~~~~~~~~~~~~*/
	TPoint	ptos[3];
	/*~~~~~~~~~~~~*/

	ptos[0].x = x2 * zoom;
	ptos[0].y = y2 * zoom;
	ptos[1].x = xf1 * zoom;
	ptos[1].y = yf1 * zoom;
	ptos[2].x = xf2 * zoom;
	ptos[2].y = yf2 * zoom;
	Printer()->Canvas->Polygon(EXISTINGARRAY(ptos));

	// Fin Flecha Form1Boole2->Tablero->Canvas->MoveTo(x2,y2);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
double Spline_CalcXI(int ApX, int BpX, int CpX, int DpX, double T, double D)
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
double Spline_CalcYI(int ApY, int BpY, int CpY, int DpY, double T, double D)
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
void SplineImpri(int x1, int y1, int x2, int y2, int x3, int y3, int zoom)
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

	Printer()->Canvas->MoveTo(x1 * zoom, y1 * zoom);
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

		Lx = Spline_CalcXI(ApX, BpX, CpX, DpX, 0, 2);
		Ly = Spline_CalcYI(ApY, BpY, CpY, DpY, 0, 2);

		for(j = 1; j <= Resolution; j++)
		{
			Xs = Spline_CalcXI(ApX, BpX, CpX, DpX, (double) j / Resolution, 2);
			Ys = Spline_CalcYI(ApY, BpY, CpY, DpY, (double) j / Resolution, 2);

			Printer()->Canvas->LineTo(Xs * zoom, Ys * zoom);
			Lx = Xs;
			Ly = Ys;
			if((i == 1) && (j == Resolution - 1)) DibujaSentidoImpri(Lx, Ly, x2, y2, zoom);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void DibujarLazoImpri(int num, int x, int y, int zoom)
// Dibuja el bucle de un estado
{
	/*~~~~~~~~~~~~~~~~~~~*/
	int		xf, yf, xm, ym;
	double	xl, yl;
	/*~~~~~~~~~~~~~~~~~~~*/

	// Warning double angulo; //el angulo en que se empieza a dibujar el lazo
	xf = Sistema.DevolverFlecha(num).CoordenadaFlechaX();
	yf = Sistema.DevolverFlecha(num).CoordenadaFlechaY();
	xm = x + ((xf - x) / 2);
	ym = y + (yf - y) / 2;

	/*~~~~~~~~~~~*/
	// Calcular ptos del lazo
	int resol = 19;
	/*~~~~~~~~~~~*/

	Printer()->Canvas->MoveTo((xm + 40) * zoom, ym * zoom);
	for(int i = 1; i <= resol; i++)
	{
		xl = (double) xm + cos((double) i * (resol - 1) * Pi / 180) * (40); // el 40 es la hipotenusa es decir el radio
																			///del lazo
		yl = (double) ym + sin((double) i * (resol - 1) * Pi / 180) * (40);
		Printer()->Canvas->LineTo(xl * zoom, yl * zoom);
	}

	Printer()->Canvas->LineTo((xm + 40) * zoom, ym * zoom);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::ImprimirAutomata(void)
{
	/*~~~~~~~~~~~~~~~~*/
	int RadioImpri = 80;
	int zoom = 3;
	/*~~~~~~~~~~~~~~~~*/

	Printer()->Title = ANSIMENSAJE(msgAutomata) +" " + Form1Boole2->Caption;
	Printer()->Orientation = poLandscape;
	Printer()->BeginDoc();
	Printer()->Canvas->Font->Name = "MS Sans Serif";

	// Printer()->Canvas->Font->Style=fsBold;
	Printer()->Canvas->Font->Size = 9;

	//
	// Anchura del papel Printer()->PageHeight Largo del papel Printer()->PageWidth;
	// Quizas con esto se puede calcular el DPI de la impresora pero no he tenido
	// tiempo de probarlo con dos impresoras diferentes. :(
	// Bucle para dibujar todas las flechas del Sistema
	//
	for(int i = 0; i < Sistema.NumFlechas(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int EntraX, EntraY, SaleX, SaleY, PuntoX, PuntoY;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		EntraX = Sistema.DevolverCirculo(Sistema.DevolverFlecha(i).FlechaCirculoEntra()).CoordenadaCirculoX();
		EntraY = Sistema.DevolverCirculo(Sistema.DevolverFlecha(i).FlechaCirculoEntra()).CoordenadaCirculoY();
		SaleX = Sistema.DevolverCirculo(Sistema.DevolverFlecha(i).FlechaCirculoSale()).CoordenadaCirculoX();
		SaleY = Sistema.DevolverCirculo(Sistema.DevolverFlecha(i).FlechaCirculoSale()).CoordenadaCirculoY();

		if(Sistema.DevolverFlecha(i).FlechaCirculoEntra() == Sistema.DevolverFlecha(i).FlechaCirculoSale())
		{
			DibujarLazoImpri(i, EntraX, EntraY, zoom);

			// El cuadradito del lazo
			PuntoX = Sistema.DevolverFlecha(i).CoordenadaFlechaX();
			PuntoY = Sistema.DevolverFlecha(i).CoordenadaFlechaY();
			Printer()->Canvas->Rectangle
				(
					(PuntoX - 3) * zoom,
					(PuntoY - 3) * zoom,
					(PuntoX + 3) * zoom,
					(PuntoY + 3) * zoom
				);
		}
		else
		{
			SplineImpri
			(
				SaleX,
				SaleY,
				Sistema.DevolverFlecha(i).CoordenadaFlechaX(),
				Sistema.DevolverFlecha(i).CoordenadaFlechaY(),
				EntraX,
				EntraY,
				zoom
			);
		}

		// Poner etiqueta en flecha
		if(Sistema.DevolverTipo() == 0)
		{
			Printer()->Canvas->TextOut
				(
					Sistema.DevolverFlecha(i).CoordenadaFlechaX() * zoom - (Sistema.DevolverNumCarEnt() * 3) * zoom,
					(Sistema.DevolverFlecha(i).CoordenadaFlechaY() - 20) * zoom,
					Sistema.DevolverFlecha(i).DevolverEtiqueta1()
				);
		}
		else
		{
			if(Sistema.DevolverFlecha(i).DevolverEtiqueta1() != "")
			{
				Printer()->Canvas->TextOut
					(
						Sistema.DevolverFlecha(i).CoordenadaFlechaX() * zoom - (Sistema.DevolverNumCarEnt() * 7) * zoom,
						(Sistema.DevolverFlecha(i).CoordenadaFlechaY() - 20) * zoom,
						Sistema.DevolverFlecha(i).DevolverEtiqueta1()
					);
				Printer()->Canvas->TextOut
					(
						Sistema.DevolverFlecha(i).CoordenadaFlechaX() * zoom,
						(Sistema.DevolverFlecha(i).CoordenadaFlechaY() - 20) * zoom,
						"/"
					);
				Printer()->Canvas->TextOut
					(
						(Sistema.DevolverFlecha(i).CoordenadaFlechaX() + 7) * zoom,
						(Sistema.DevolverFlecha(i).CoordenadaFlechaY() - 20) * zoom,
						Sistema.DevolverFlecha(i).DevolverEtiqueta2()
					);
			}
		}
	}

	// Bucle para situar todos los circulos del sistema
	for(int i = 0; i < Sistema.NumCirculos(); i++)
	{
		Printer()->Canvas->Ellipse
			(
				Sistema.DevolverCirculo(i).CoordenadaCirculoX() * zoom - RadioImpri,
				Sistema.DevolverCirculo(i).CoordenadaCirculoY() * zoom - RadioImpri,
				Sistema.DevolverCirculo(i).CoordenadaCirculoX() * zoom + RadioImpri,
				Sistema.DevolverCirculo(i).CoordenadaCirculoY() * zoom + RadioImpri
			);

		/*~~~~~~~~~~~~~~~~~*/
		// Dibujar la etiqueta Poner la etiqueta en el circulo
		AnsiString	Etiqueta;
		/*~~~~~~~~~~~~~~~~~*/

		Etiqueta = Sistema.DevolverCirculo(i).DevolverEtiqueta1();

		//
		// compruebo si la etique ta es del standar es decir E Numero y si el del estandar
		// el numero que le pongo sera el de su estado
		//
		if(Etiqueta.SubString(1, 4) == "E")
		{
			Etiqueta = "E";
			Etiqueta += i;
		}

		Printer()->Canvas->TextOut
			(
				Sistema.DevolverCirculo(i).CoordenadaCirculoX() * zoom - 45,
				Sistema.DevolverCirculo(i).CoordenadaCirculoY() * zoom - 40,
				Etiqueta
			);

		// Poner la etiqueta en el circulo
		if(Sistema.DevolverCirculo(i).DevolverEtiqueta2() != "")
		{
			Printer()->Canvas->TextOut
				(
					Sistema.DevolverCirculo(i).CoordenadaCirculoX() * zoom - 45,
					Sistema.DevolverCirculo(i).CoordenadaCirculoY() * zoom + 20,
					Sistema.DevolverCirculo(i).DevolverEtiqueta2()
				);

			// linea de separacion entre las dos etiquetas
			Printer()->Canvas->MoveTo
				(
					(Sistema.DevolverCirculo(i).CoordenadaCirculoX() - 15) * zoom,
					(Sistema.DevolverCirculo(i).CoordenadaCirculoY() - 5) * zoom + 25
				);
			Printer()->Canvas->LineTo
				(
					(Sistema.DevolverCirculo(i).CoordenadaCirculoX() + 15) * zoom,
					(Sistema.DevolverCirculo(i).CoordenadaCirculoY() - 5) * zoom + 25
				);
		}
	}

	Printer()->EndDoc();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::ResultadosAPortapapeles(void)
{
  TStringList *l = new TStringList;//lista de strings que vamos a copiar al portapapeles

  // Encontramos el numero de bits de los estados
  int numBitsEstados = 1;
  while(ElevarBase2(numBitsEstados) < Sistema.NumCirculos())
  {
  	numBitsEstados++;
  }


	if(Sistema.DevolverTipo() == MOORE)
	{
		TablaMoore();

		l->Add(MENSAJE(msgResultadosMoore));
    l->Add("");

		l->Add(MENSAJE(msgTablaTranEstSal));
    l->Add("");
    DibujarTablaConStrings(l, Form9->Tabla, 6);
    l->Add("");
    l->Add("");
		l->Add(MENSAJE(msgTablaCodifTransCodif));
    l->Add("");
    DibujarTablaConStrings(l, Form9->Codifica, 6);
    l->Add("");
    l->Add("");
    DibujarTablaConStrings(l, Form9->Tablacod, 6);
    l->Add("");
		l->Add(MENSAJE(msgTablaExcitacion));
    l->Add("");
    l->Add("");
    DibujarTablaConStrings(l, Form9->Excitacion, 4);
    l->Add("");
    l->Add("");
		l->Add(MENSAJE(msgExprSimplificadas));
    l->Add("");
		for(int i = 0; i < Form9->ListaJK->Items->Count; i++)
			l->Add(Form9->ListaJK->Items->Strings[i]);
		for(int i = 0; i < Form9->ListaD->Items->Count; i++)
			l->Add(Form9->ListaD->Items->Strings[i]);
		for(int i = 0; i < Form9->ListaSol->Items->Count; i++)
			l->Add(Form9->ListaSol->Items->Strings[i]);
	}
	else
	{	// AUTOMATA DE MEALY

		TablaMealy();

		l->Add(MENSAJE(msgResultadosMealy));
    l->Add("");

		l->Add(MENSAJE(msgTablaTranEstSal));
    l->Add("");
    DibujarTablaConStrings(l, Form10->Tabla, max(8, 6 + Sistema.DevolverNumCarSal()));
    l->Add("");
    l->Add("");
		l->Add(MENSAJE(msgTablaCodifEstados));
    l->Add("");
    DibujarTablaConStrings(l, Form10->Codifica, 6);
    l->Add("");
    l->Add("");
    DibujarTablaConStrings(l, Form10->Tablacod, numBitsEstados+Sistema.DevolverNumCarSal()+2);
    l->Add("");
		l->Add(MENSAJE(msgTablaExcitacion));
    l->Add("");
    l->Add("");
    DibujarTablaConStrings(l, Form10->Excitacion, 4);
    l->Add("");
    l->Add("");
		l->Add(MENSAJE(msgExprSimplificadas));
    l->Add("");
		for(int i = 0; i < Form10->ListaJK->Items->Count; i++)
			l->Add(Form10->ListaJK->Items->Strings[i]);
		for(int i = 0; i < Form10->ListaD->Items->Count; i++)
			l->Add(Form10->ListaD->Items->Strings[i]);
		for(int i = 0; i < Form10->ListaSol->Items->Count; i++)
			l->Add(Form10->ListaSol->Items->Strings[i]);
	}
  Clipboard()->Clear();
  Clipboard()->SetTextBuf(l->Text.c_str());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::FormClose(TObject *Sender, TCloseAction &Action)
{
	Sistema.SeleccionarCirculo(-1);
	Sistema.SeleccionarFlecha(-1);

	// Al principio es moore
	Sistema.ActualizarTipo(0);
	Sistema.ActualizarNumCarEnt(5);
	Sistema.ActualizarNumCarSal(5);
	NewDiagramForm->Button1->Click();
	Form2->Close();
	Form8->Close();
	Principal->Show();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::ConflipflopsJK1Click(TObject *Sender)
{
	// Modificado Ricardo
	Form1Boole2->Timer1->Enabled = false;
	Form2->Hide();
	Form1Boole2->Enabled = false;

	if(Sistema.DevolverTipo() == 0)
	{
		FormR->tipoCircuito = true; // Secuencial.
		FormR->tipoCS = false;		// More.
		FormR->tipoFlipFlops = true;
		TablaMoore();
	}
	else
	{
		FormR->tipoCircuito = true; // Secuencial.
		FormR->tipoCS = true;		// Mealy.
		FormR->tipoFlipFlops = true;
		TablaMealy();
	}	// end-else.

	// FormR->Lista->Items->Clear();
	FormR->Show();

	// FormR->SetFocus();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::ConflipflopsD1Click(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	Form2->Hide();
	Form1Boole2->Enabled = false;

	if(Sistema.DevolverTipo() == 0)
	{
		FormR->tipoCircuito = true; // Secuencial.
		FormR->tipoCS = false;		// More.
		FormR->tipoFlipFlops = false;
		TablaMoore();
	}
	else
	{
		FormR->tipoCircuito = true; // Secuencial.
		FormR->tipoCS = true;		// Mealy.
		FormR->tipoFlipFlops = false;
		TablaMealy();
	}	// end-else.

	// FormR->Lista->Items->Clear();
	FormR->Show();

	// FormR->SetFocus();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 *///
// =======================================================================================================================
//    inicio modificado Ainara
// =======================================================================================================================
//
int TForm1Boole2::Num(void)
{
	return Sistema.GetNumCirculos();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::NumF(void)
{
	return Sistema.GetNumFlechas();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString TForm1Boole2::EtiqCirc(int a)
{
	return Sistema.cogerEtiq(a);
}

/*
 =======================================================================================================================
    void TForm1::NuevaFlecha(AnsiString a,AnsiString b,AnsiString c,AnsiString d) { Sistema.AnyadirFlecha (a,b,c,d); }
 =======================================================================================================================
 */
AnsiString TForm1Boole2::VerFlecha(int i)
{
	return Sistema.CogerFlecha(i);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::simplificar(void)
{
	conTabla = 0;
        //Sistema.Expandir();
	Sistema.crearTablaImplicacion();
	Sistema.particionDeSalida();
	Sistema.paresImplicados();
	Sistema.tablaTerminada();
	Sistema.comprobarTabla();
        if (Sistema.EsIncompletamenteEspecificado())
        {
        	Form16->lblSuperior->Caption=MENSAJE(msgMaximalesCompat);
        	Form16->lblInferior->Caption=MENSAJE(msgMaximalesIncompat);
        	Sistema.tablaMinimaAutomataNoEspecif();
        }
        else
        {
        	Form16->lblSuperior->Caption=MENSAJE(msgNodosFinales);
        	Form16->lblInferior->Caption=MENSAJE(msgParticionEquiv);
		Sistema.particionEquivalencia();
        }

        //Sistema.Contraer();
	Form16->Button4->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::pasos(void)
{
	for(int h = 0; h <= Num(); h++)
	{
		for(int g = 0; g <= Num(); g++)
		{
			Form16->Grid1->Cells[h][g] = "";
			Form16->Edit1->Text = "";
			Form16->Edit2->Text = "";
		}
	}

	conTabla = 1;
        //Sistema.Expandir();
	Sistema.crearTablaImplicacion();
	Form16->Label3->Caption = MENSAJE(msgCreamosTabla);
	numpaso = 1;
	Form16->Button2->Enabled = false;
	Form16->Button3->Visible = true;
	Form16->Button3->Enabled = true;
	Form16->Button1->Enabled = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::continuar(void)
{
	switch(numpaso)
	{
	case 1:
		{
			Sistema.particionDeSalida();
			numpaso++;
			Form16->Label3->Caption = MENSAJE(msgParticionSalida);
			break;
		}

	case 2:
		{
			Sistema.paresImplicados();
			numpaso++;
			Form16->Label3->Caption = MENSAJE(msgParesImpl);
			break;
		}

	case 3:
		{
			Sistema.tablaTerminada();
			numpaso++;
			Form16->Label3->Caption = MENSAJE(msgTablaTerminada);
			break;
		}

	case 4:
		{
			Sistema.comprobarTabla();
		        if (Sistema.EsIncompletamenteEspecificado())
		        {
				Form16->Label3->Caption = MENSAJE(msgMaximalesCompatIncompat);
		        	Form16->lblSuperior->Caption=MENSAJE(msgMaximalesCompat);
		        	Form16->lblInferior->Caption=MENSAJE(msgMaximalesIncompat);
		        	Sistema.tablaMinimaAutomataNoEspecif();
		        }
		        else
		        {
				Form16->Label3->Caption = MENSAJE(msgParticionEquiv);
		        	Form16->lblSuperior->Caption=MENSAJE(msgNodosFinales);
		        	Form16->lblInferior->Caption=MENSAJE(msgParticionEquiv);
				Sistema.particionEquivalencia();
		        }
			numpaso = 0;
			Form16->Button3->Visible = false;
			Form16->Button3->Enabled = false;
			Form16->Button2->Enabled = true;
			Form16->Button4->Enabled = true;
			Form16->Button1->Enabled = true;
			break;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TForm1Boole2::cambiar(void)
{
	Sistema.cambiarCirculos();
	Sistema.cambiarFlechas();
        //Sistema.Contraer();
	Form16->Button4->Enabled = false;

	// Sistema.mostrarCambios();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Reducir1Click(TObject *Sender)
{
	Form16->ListBox3->Clear();
	Form16->ListBox4->Clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int num = Sistema.GetNumCirculos();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < num; i++) Form16->ListBox4->Items->Add(EtiqCirc(i));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int numf = Sistema.GetNumFlechas();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < numf; i++) Form16->ListBox3->Items->Add(VerFlecha(i));
	Form16->Edit5->Text = Sistema.GetNumFlechas();
	Form16->Edit1->Text = "";
	Form16->Edit2->Text = "";
	Form16->Edit4->Text = "";
	Form16->Edit6->Text = "";
	Form16->Edit3->Text = Sistema.GetNumCirculos();
	Form16->ListBox1->Clear();
	Form16->ListBox2->Clear();
	for(int i = 0; i < Form16->Grid1->ColCount; i++)
		for(int j = 0; j < Form16->Grid1->RowCount; j++) Form16->Grid1->Cells[i][j] = "";

	Form16->ShowModal();
}

//
// =======================================================================================================================
//    fin modificado Ainara
// =======================================================================================================================
//
void __fastcall TForm1Boole2::SimulacionClick(TObject *Sender)
{
        tipoSimulacion = NORMAL;
        IniciarSimulacionInteractiva(NORMAL);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::ReduccionClick(TObject *Sender)
{
	Form16->ListBox3->Clear();
	Form16->ListBox4->Clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int num = Sistema.GetNumCirculos();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < num; i++) Form16->ListBox4->Items->Add(EtiqCirc(i));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int numf = Sistema.GetNumFlechas();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < numf; i++) Form16->ListBox3->Items->Add(VerFlecha(i));
	Form16->Edit5->Text = Sistema.GetNumFlechas();
	Form16->Edit1->Text = "";
	Form16->Edit2->Text = "";
	Form16->Edit4->Text = "";
	Form16->Edit6->Text = "";
	Form16->Edit3->Text = Sistema.GetNumCirculos();
	Form16->ListBox1->Clear();
	Form16->ListBox2->Clear();
        Form16->lblAviso->Visible=false;
        Sistema.numcirculos2 = 0;
        Sistema.numflechas2 = 0;
        numpaso = 0;
        Form16->Button2->Visible=true;
	Form16->Button2->Enabled = true;
	Form16->Button3->Visible = false;
	Form16->Button3->Enabled = false;
	Form16->Button1->Enabled = true;
	for(int i = 0; i < Form16->Grid1->ColCount; i++)
		for(int j = 0; j < Form16->Grid1->RowCount; j++) Form16->Grid1->Cells[i][j] = "";

	Form16->ShowModal();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Circuito1Click(TObject *Sender)
{
	if(Sistema.NumCirculos() == 0)
	{
		ConflipflopsD1->Enabled = false;
		ConflipflopsJK1->Enabled = false;
	}
	else
	{
		ConflipflopsD1->Enabled = true;
		ConflipflopsJK1->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Ayuda1Click(TObject *Sender)
{
	Form1Boole2->Enabled = false;
	fAyuda->Show();
	fAyuda->SetFocus();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Button1Click(TObject *Sender)
{
	simulando = false;
	simulacion = NO_SIMULANDO;
	pSimulacion->Visible = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::comboInicialChange(TObject *Sender)
{
	Sistema.indiceInicial = comboInicial->ItemIndex;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::btAplicarClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	entrada;
	/*~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
	{
		entrada = entrada + gridVarsEnt->Cells[i][1];
	}

	if(!Sistema.AplicarEntrada(entrada))
	{
		Sistema.indiceFlechaActual = -1;
		if(pSimulacion->Visible)
		{
			Application->MessageBox
				(
					MENSAJE(msgErrorAplicarEntrada),
					"ERROR!",
					MB_OK
				);
		}
	}
	else
	{
		edEntrada->Text = entrada;
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
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::gridVarsEntMouseDown
(
	TObject			*Sender,
	TMouseButton	Button,
	TShiftState		Shift,
	int				X,
	int				Y
)
{
	/*~~~~~~~~~~~~~~~~~~*/
	int			col, row;
	AnsiString	contenido;
	/*~~~~~~~~~~~~~~~~~~*/

	gridVarsEnt->MouseToCell(X, Y, col, row);
	if(row == 1)
	{
		contenido = gridVarsEnt->Cells[col][1];
		if(contenido == "1")
			gridVarsEnt->Cells[col][1] = AnsiString("0");
		else if(contenido == "0")
			gridVarsEnt->Cells[col][1] = AnsiString("1");
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Button2Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	Entrada;
        bool            error = false;
	/*~~~~~~~~~~~~~~~~*/

        // Si estamos en la simulacion rápida, primero tenemos que aplicar
        // la entrada antes del clock.
        if (tipoSimulacion == RAPIDA)
        {
        	for(int i = 0; i < Sistema.DevolverNumCarEnt(); i++)
        	{
        		Entrada = Entrada + gridVarsEnt->Cells[i][1];
        	}

        	if(!Sistema.AplicarEntrada(Entrada))
                        Sistema.indiceFlechaActual = -1;
        }
        // En la simulacion normal, el usuario es el responsable de aplicar
        // la entrada. Si no lo ha hecho, le avisamos.
        else if (tipoSimulacion == NORMAL)
        {
                if (edEntrada->Text=="" && Sistema.indiceFlechaActual != -1)
                {
                        Application->MessageBox
	        	(
                                MENSAJE(msgNoPuedeClkNoEntrada),
                		"ERROR!",
                		 MB_OK
                        );
                        error = true;
                }
        }

        if(pSimulacion->Visible && Sistema.indiceFlechaActual == -1)
        {
                Application->MessageBox
		(
                        MENSAJE(msgNoPuedeClkNoTrans),
        		"ERROR!",
        		 MB_OK
                );
                error = true;
        }

        // Ahora mismo, la entrada está estabilizada y ya podemos aplicar
        // el clock.
        if (!error)
        {
                // Situacion del automata antes del CLK
                AnsiString	EstadoQt = Sistema.CogerNombreCirculoActual();
		AnsiString	SalidaQt = Sistema.CogerSalidaActual();
                if (tipoSimulacion == NORMAL)
                {
                        Entrada = edEntrada->Text;
                        edEntrada->Text = "";
                }

                // Esto es el CLK
                Sistema.indiceAnterior = Sistema.indiceActual;
		Sistema.indiceActual = Sistema.getFlechaActual().FlechaCirculoEntra();

                // Esto es por si el CLK nos lleva al mismo estado
                if (Sistema.indiceActual == Sistema.indiceAnterior)
                {
                        TimerParpadeoEstado->Tag = 0;
                        TimerParpadeoEstado->Enabled = true;
                }

                // Situacion del automata despues del CLK
                AnsiString	EstadoQt1 = Sistema.CogerNombreCirculoActual();
		AnsiString	SalidaQt1 = Sistema.CogerSalidaActual();

                // Actualizamos interfaz
                edEstadoActual->Text = Sistema.CogerNombreCirculoActual();
                if (Sistema.Tipo == MOORE)
                        for(int i = 1; i <= SalidaQt1.Length(); i++)
                                Form1Boole2->gridVarsSal->Cells[i - 1][1] = AnsiString(SalidaQt1[i]);
                else if (Sistema.Tipo == MEALY)
                {
                        if(tipoSimulacion == RAPIDA)
                                for(int i = 1; i <= SalidaQt.Length(); i++)
                                        Form1Boole2->gridVarsSal->Cells[i - 1][1] = AnsiString(SalidaQt[i]);
                        else
                                for(int i = 1; i <= SalidaQt1.Length(); i++)
                                        Form1Boole2->gridVarsSal->Cells[i - 1][1] = " ";
                }

                // Escribimos en el log
                if(tipoSimulacion == RAPIDA)
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
                                tipoSimulacion,
                                fLog->pasoActual,
                                false,
                                true,
                                EstadoQt1,
                                Entrada,
                                " ",
                                Sistema.Tipo==MOORE?SalidaQt1:SalidaQt
                        );
                }
                else if (tipoSimulacion == NORMAL)
                {
                        // En la simulacion normal mostramos dos lineas:
                        // La primera simplemente indica que hemos hecho un clock.
                        // La segunda muestra el estado despues del clock,
                        // suponiendo que no hay una entrada estable.
                        fLog->EscribirLinea
                        (
                                TEXTO,
                                Sistema.Tipo,
                                tipoSimulacion,
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
                                tipoSimulacion,
                                fLog->pasoActual,
                                false,
                                false,
                                EstadoQt1,
                                AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
                                " ",
                                Sistema.Tipo==MOORE?SalidaQt1:AnsiString::StringOfChar(' ', Sistema.NumCarSal)
                        );
                }
                fLog->pasoActual++;
        }








/*

  if(rapida)
  {
    btAplicar->Click();
  }

	if(Sistema.indiceFlechaActual == -1)
	{
                if(!rapida)
		Application->MessageBox
			(
				"No se puede enviar una señal de reloj. La entrada aplicada no activa ninguna transición.",
				"ERROR!",
				MB_OK
			);
	}
	else
	{
  		AnsiString	CirculoActual = Sistema.CogerNombreCirculoActual();
		AnsiString	CirculoSiguiente = Sistema.CogerNombreCirculoSiguiente();
		AnsiString	Entrada = edEntrada->Text;
		AnsiString	Salida = Sistema.CogerSalidaActual();

  			fLog->EscribirLinea
        (
          TEXTO,
          fLog->pasoActual,
          false,
          false,
          CirculoActual,
          AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
          " ",
          AnsiString::StringOfChar(' ', Sistema.NumCarSal),
          Sistema.Tipo
        );

    Sistema.indiceAnterior = Sistema.indiceActual;
		Sistema.indiceActual = Sistema.getFlechaActual().FlechaCirculoEntra();
    if (Sistema.indiceActual == Sistema.indiceAnterior)
    {
      TimerParpadeoEstado->Tag = 0;
      TimerParpadeoEstado->Enabled = true;
    }

		edEstadoActual->Text = Sistema.CogerNombreCirculoActual();


		CirculoActual = Sistema.CogerNombreCirculoActual();
		CirculoSiguiente = Sistema.CogerNombreCirculoSiguiente();
		Entrada = edEntrada->Text;
		Salida = Sistema.CogerSalidaActual();


		if(!AplicarEntrada(edEntrada->Text, true))
			Sistema.indiceFlechaActual = -1;
		else
		{

      fLog->EscribirLinea(
      TEXTO,
      fLog->pasoActual,
      false,
      true,
      " ",
      AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
      " ",
      AnsiString::StringOfChar(' ', Sistema.NumCarSal),
      Sistema.Tipo
      );

			CirculoActual = Sistema.CogerNombreCirculoActual();
			CirculoSiguiente = Sistema.CogerNombreCirculoSiguiente();
			Entrada = edEntrada->Text;
			Salida = Sistema.CogerSalidaActual();
			fLog->EscribirLinea
				(
					TEXTO,
					fLog->pasoActual,
					false,
					false,
          CirculoActual,
          AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
          " ",
          AnsiString::StringOfChar(' ', Sistema.NumCarSal),
          Sistema.Tipo
				);  */


      /*
      if (Sistema.Tipo == MEALY)
			fLog->EscribirLinea
        (
          TEXTO,
          fLog->pasoActual,
          false,
          true,
          CirculoActual,
          Entrada,
          CirculoSiguiente,
          Salida,
          Sistema.Tipo);
			CirculoActual = Sistema.CogerNombreCirculoActual();
			CirculoSiguiente = Sistema.CogerNombreCirculoSiguiente();
			Entrada = edEntrada->Text;
			Salida = Sistema.CogerSalidaActual();
      if(!rapida || (rapida && Sistema.Tipo==MOORE))
			fLog->EscribirLinea
				(
					TEXTO,
					fLog->pasoActual,
					false,
					(Sistema.Tipo==MOORE),
					CirculoActual,
					Entrada,
					CirculoSiguiente,
					Salida,
          Sistema.Tipo
				);
      */
      /*
      if(!rapida)
      {
        btAplicar->Click();
      }
      else
        fLog->pasoActual++;


		}
	}*/
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::btResetClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  fLog->EscribirLinea(
      TEXTO,
      Sistema.Tipo,
      tipoSimulacion,
      fLog->pasoActual,
      true,
      false,
      " ",
      AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
      " ",
      AnsiString::StringOfChar(' ', Sistema.NumCarSal)

      );
  Sistema.Resetear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int numVarsEnt = Sistema.DevolverNumCarEnt();
	int numVarsSal = Sistema.DevolverNumCarSal();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// Ponemos a cero las entradas
	for(int i = 0; i < numVarsEnt; i++)
    Form1Boole2->gridVarsEnt->Cells[i][1] = "0";

  Form1Boole2->edEntrada->Text = "";
  Sistema.indiceFlechaActual = -1;
  AnsiString	CirculoActual = Sistema.CogerNombreCirculoActual();
	AnsiString	Salida = Sistema.CogerSalidaActual();

  // Si es MOORE, actualizamos las salidas
  if (Sistema.Tipo == MOORE)
	  for(int i = 1; i <= numVarsSal; i++)
      Form1Boole2->gridVarsSal->Cells[i - 1][1] = AnsiString(Salida[i]);

	Form1Boole2->edEstadoActual->Text = CirculoActual;

   fLog->EscribirLinea(
        TEXTO,
        Sistema.Tipo,
        tipoSimulacion,
        fLog->pasoActual++,
        false,
        false,
        CirculoActual,
        AnsiString::StringOfChar(' ', Sistema.NumCarEnt),
        " ",
        Sistema.Tipo==MOORE?Salida:AnsiString::StringOfChar(' ', Sistema.NumCarSal)
        );
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::VerificarClick(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	HacerVerificacion(true, CORRECCION);
	Form1Boole2->Timer1->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int TForm1Boole2::HacerVerificacion(bool mostrarSiEsCorrecto, int tipoVerificacion)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int			cod, estado, transicion;
	AnsiString	entrada, mensaje, titulo;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	cod = Sistema.VerificarAutomata(estado, transicion, entrada);
	switch(cod)
	{
	case AUTOMATA_COMPLETO:
		mensaje = ANSIMENSAJE(msgAutomataCorrectoDeterminista);
		titulo = ANSIMENSAJE(msgTituloCorrectoDeterminista);;
		break;
	case MOORE_ESTADO_SIN_SALIDA:
		titulo = ANSIMENSAJE(msgError);
		mensaje = ANSIMENSAJE(msgEstadoSinSalida1);
		mensaje += Sistema.DevolverCirculo(estado).DevolverEtiqueta1();
		mensaje += ANSIMENSAJE(msgEstadoSinSalida2);
		break;
	case MEALY_TRANSICION_SIN_SALIDA:
		titulo = ANSIMENSAJE(msgError);
		mensaje = ANSIMENSAJE(msgTransicionSinSalida1);
		mensaje += Sistema.DevolverCirculo(Sistema.DevolverFlecha(transicion).FlechaCirculoSale()).DevolverEtiqueta1();
		mensaje += ANSIMENSAJE(msgTransicionSinSalida2);
		mensaje += Sistema.DevolverCirculo(Sistema.DevolverFlecha(transicion).FlechaCirculoEntra()).DevolverEtiqueta1();
		mensaje += ANSIMENSAJE(msgTransicionSinSalida3);
		break;
	case DEMASIADAS_TRANSICIONES:
		titulo = ANSIMENSAJE(msgAutomataIndeterminista);
		mensaje = ANSIMENSAJE(msgDemasiadasTransiciones1);
		mensaje += Sistema.DevolverCirculo(estado).DevolverEtiqueta1();
		mensaje += ANSIMENSAJE(msgDemasiadasTransiciones2) + entrada + ANSIMENSAJE(msgDemasiadasTransiciones3);
		mensaje += ANSIMENSAJE(msgDemasiadasTransiciones4);
		mensaje += Sistema.DevolverCirculo(Sistema.DevolverFlecha(transicion).FlechaCirculoSale()).DevolverEtiqueta1();
		mensaje += ANSIMENSAJE(msgDemasiadasTransiciones5);
		mensaje += Sistema.DevolverCirculo(Sistema.DevolverFlecha(transicion).FlechaCirculoEntra()).DevolverEtiqueta1();
		mensaje += ANSIMENSAJE(msgDemasiadasTransiciones6);
		break;
	case AUTOMATA_CORRECTO_FALTA_TRANSICION:
		if(tipoVerificacion == CORRECCION)
		{
			titulo = ANSIMENSAJE(msgCorrecto);
			mensaje += ANSIMENSAJE(msgAutomataCorrectoNoDeterminista);
		}
		else if(tipoVerificacion == COMPLETITUD)
		{
			titulo = ANSIMENSAJE(msgAutomataIndeterminista);
			mensaje = ANSIMENSAJE(msgFaltaTransicion1);
			mensaje += Sistema.DevolverCirculo(estado).DevolverEtiqueta1();
			mensaje += ANSIMENSAJE(msgFaltaTransicion2) + entrada + ANSIMENSAJE(msgFaltaTransicion3);
		}
		break;
	}

	if(cod == AUTOMATA_COMPLETO || cod == AUTOMATA_CORRECTO_FALTA_TRANSICION)
	{
		if(mostrarSiEsCorrecto) Application->MessageBox(mensaje.c_str(), titulo.c_str(), MB_OK);
	}
	else
		Application->MessageBox(mensaje.c_str(), titulo.c_str(), MB_OK);
	return cod;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::BatchClick(TObject *Sender)
{
        tipoSimulacion = NORMAL;
        IniciarSimulacionBatch(NORMAL);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::VerificarCompletitudClick(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	HacerVerificacion(true, COMPLETITUD);
	Form1Boole2->Timer1->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::Button4Click(TObject *Sender)
{
	Enabled = false;
	Timer1->Enabled = false;
	fLog->llamador = LLAMA_INTERACTIVA;
	fLog->Show();
	fLog->SetFocus();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm1Boole2::EquivalenteClick(TObject *Sender)
{
	if(Sistema.Tipo == MOORE)
		Sistema.ConvertirMooreAMealy();
	else if(Sistema.Tipo == MEALY)
                Sistema.ConvertirMealyAMoore();
}

void __fastcall TForm1Boole2::CopiarAutomataClick(TObject *Sender)
{
  TCanvas *automata = new TCanvas();
  TPicture *picture = new TPicture();
  int xMin=1200, xMax=0, yMin=1000, yMax=0;
  extern int Radio;

  Timer1->Enabled = false;

  for (int i=0;i<Sistema.NumCirculos();i++)
  {
    CIRCULO circulo = Sistema.DevolverCirculo(i);
    if (circulo.CoordenadaCirculoX()  < xMin)
      xMin = circulo.CoordenadaCirculoX();
    if (circulo.CoordenadaCirculoX() > xMax)
      xMax = circulo.CoordenadaCirculoX();
    if (circulo.CoordenadaCirculoY()  < yMin)
      yMin = circulo.CoordenadaCirculoY();
    if (circulo.CoordenadaCirculoY() > yMax)
      yMax = circulo.CoordenadaCirculoY();
  }

  xMin -= Radio;
  xMax += Radio;
  yMin -= Radio;
  yMax += Radio;

  for (int i=0;i<Sistema.NumFlechas();i++)
  {
    FLECHA flecha = Sistema.DevolverFlecha(i);
    if (flecha.CoordenadaFlechaX()  < xMin)
      xMin = flecha.CoordenadaFlechaX();
    if (flecha.CoordenadaFlechaX() > xMax)
      xMax = flecha.CoordenadaFlechaX();
    if (flecha.CoordenadaFlechaY()  < yMin)
      yMin = flecha.CoordenadaFlechaY();
    if (flecha.CoordenadaFlechaY() > yMax)
      yMax = flecha.CoordenadaFlechaY();
  }

  if (xMin > 20)
    xMin -= 20;
  else
    xMin = 0;
  xMax += 20;
  if (yMin > 20)
    yMin -= 20;
  else
    yMin = 0;
  yMax += 20;

  TRect limites(xMin,yMin,xMax,yMax);

  picture->Bitmap->Width=limites.Width();
  picture->Bitmap->Height=limites.Height();
  picture->Bitmap->Canvas->CopyRect(TRect(0,0,limites.Width(),limites.Height()),Tablero->Canvas,limites);
  Clipboard()->Assign(picture);
  delete automata;
  delete picture;
  Timer1->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::TimerParpadeoEstadoTimer(TObject *Sender)
{
  extern bool parpadeo;

  parpadeo = ! parpadeo;
  (TimerParpadeoEstado->Tag)++;
  if (TimerParpadeoEstado->Tag == 10)
  {
    TimerParpadeoEstado->Enabled = false;
    TimerParpadeoEstado->Tag = 0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::CopiarTablasClick(TObject *Sender)
{
  Form1Boole2->ResultadosAPortapapeles();
}
//---------------------------------------------------------------------------
void __fastcall TForm1Boole2::DibujarTablaConStrings(TStringList *l, TStringGrid *t, int ancho)
{
		for(int i = 0; i < t->RowCount; i++)
		{
      AnsiString temp("|");
      AnsiString sep("|");
			for(int j = 0; j < t->ColCount; j++)
			{
				temp += t->Cells[j][i] + AnsiString::StringOfChar(' ', ancho - t->Cells[j][i].Length());
        sep += AnsiString::StringOfChar('-', ancho);
        temp += "|";
        sep += "|";
			}
      l->Add(temp);
      l->Add(sep);
		}

}
void __fastcall TForm1Boole2::Edicin1Click(TObject *Sender)
{
  if(Sistema.NumCirculos() == 0)
  {
    CopiarAutomata->Enabled=false;
    CopiarTablas->Enabled=false;
  }
  else
  {
    CopiarAutomata->Enabled=true;
    CopiarTablas->Enabled=true;
  }
}
//---------------------------------------------------------------------------
void TForm1Boole2::ImprimirResultados(void)
{
	if(Sistema.DevolverTipo() == 0)
	{
		/*
		 * TablaMoore(); int m=100; int sgte=0; int izq=0; int j,i; int
		 * linea1x,linea2ax,linea2bx,linea3x; int linea1y,linea2y,linea3y; int
		 * long1,long2a,long2b,long3; Printer()->Title="Resultados "+Form1Boole2->Caption;
		 * Printer()->Orientation=poPortrait; Printer()->BeginDoc(); //Tabla
		 * Printer()->Canvas->Font->Name="MS Sans Serif";
		 * //Printer()->Canvas->Font->Style=fsBold; Printer()->Canvas->Font->Size=12; int
		 * m1=Printer()->Canvas->TextHeight("XXX")+10;
		 * Printer()->Canvas->TextOut(40,m,"Tabla de transicion de estados y salidas.");
		 * m=m+m1*2; //Printer()->Canvas->Font->Style=""; for
		 * (i=0;i<Form9->Tabla->ColCount;i++){ for (j=0;j<Form9->Tabla->RowCount;j++){
		 * Printer()->Canvas->TextOut((i*300)+200,j*m1+m,Form9->Tabla->Cells[i][j]); } }
		 * linea1x=200; linea1y=m+m1+1; sgte=sgte+(j*100)+200; long1=(i*300);
		 * Printer()->Canvas->MoveTo(linea1x,linea1y);
		 * Printer()->Canvas->LineTo(linea1x+long1,linea1y);
		 * m+=m1*(Form9->Tabla->RowCount+1); //Tabla de codificacion de estados
		 * Printer()->Canvas->TextOut(40,m,"Tabla de codificacion de estados."); m=m+m1*2;
		 * sgte=sgte+80; for (i=0;i<Form9->Codifica->ColCount;i++){ for
		 * (j=0;j<Form9->Codifica->RowCount;j++){
		 * Printer()->Canvas->TextOut((i*300)+200,j*m1+m,Form9->Codifica->Cells[i][j]); }
		 * } //m+=m1*Form9->Tabla->RowCount; long2a=(i*300); linea2ax=200; linea2y=m+m1+1;
		 * Printer()->Canvas->MoveTo(linea2ax,linea2y);
		 * Printer()->Canvas->LineTo(linea2ax+long2a,linea2y); linea2bx=(i*300)+400;
		 * izq=(i*300)+200; for (i=0;i<Form9->Tablacod->ColCount;i++){ for
		 * (j=0;j<Form9->Tablacod->RowCount;j++){
		 * Printer()->Canvas->TextOut((i*300)+200+izq,(j*m1)+m,Form9->Tablacod->Cells[i][j]);
		 * } } long2b=(i*300)+izq; Printer()->Canvas->MoveTo(linea2bx,linea2y);
		 * Printer()->Canvas->LineTo(linea2bx+long2b,linea2y);
		 * m=m+m1*(Form9->Tablacod->RowCount+1); sgte=sgte+(j*100)+200; //Tabla de
		 * excitacion de biestables Printer()->Canvas->TextOut(40,m,"Tabla de excitacion
		 * de biestables."); m=m+m1*2; sgte=sgte+80; Printer()->Canvas->Font->Size=8; for
		 * (i=0;i<Form9->Excitacion->ColCount;i++){
		 * Printer()->Canvas->TextOut((i*160)+200,i+m,Form9->Excitacion->Cells[i][0]); }
		 * sgte=sgte+100; m=m+m1; for (i=0;i<Form9->Excitacion->ColCount;i++){ for
		 * (j=1;j<Form9->Excitacion->RowCount;j++){
		 * Printer()->Canvas->TextOut((i*160)+200,(j*m1)+m,Form9->Excitacion->Cells[i][j]);
		 * } } linea3x=200; linea3y=m; long3=(i*160);
		 * Printer()->Canvas->MoveTo(linea3x,linea3y);
		 * Printer()->Canvas->LineTo(linea3x+long3,linea3y);
		 * m+=m1*(Form9->Excitacion->RowCount+1); sgte=sgte+(j*50)+100;
		 * Printer()->Canvas->Font->Size=12; //Solucion if ( m +
		 * (Form9->Solucion->Items->Count+2)*Printer()->Canvas->TextHeight("XXX") >
		 * Printer()->PageHeight ){ Printer()->NewPage(); m=100; }
		 * Printer()->Canvas->TextOut(40,m,"Solución"); m+=m1*2;
		 * Printer()->Canvas->Font->Size=10; for
		 * (i=0;i<Form9->Solucion->Items->Count;i++){
		 * Printer()->Canvas->TextOut(200,(i*m1)+m,Form9->Solucion->Items->Strings[i]); }
		 * //m+=m1*Form9->Solucion->Items->Count; Printer()->Canvas->Font->Size=12;
		 * //Lineas pra makear las tablas :) Printer()->EndDoc();
		 */
		TablaMoore();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int m = 100;
		int sgte = 0;
		int izq = 0;
		int j, i;
		int linea1x, linea2ax, linea2bx, linea3x;
		int linea1y, linea2y, linea3y;
		int long1, long2a, long2b, long3;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Printer()->Title = ANSIMENSAJE(msgResultados)+" " + Form1Boole2->Caption;
		Printer()->Orientation = poPortrait;
		Printer()->BeginDoc();

		// Tabla
		Printer()->Canvas->Font->Name = "MS Sans Serif";

		// Printer()->Canvas->Font->Style=fsBold;
		Printer()->Canvas->Font->Size = 12;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int m1 = Printer()->Canvas->TextHeight("XXX") + 10;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Printer()->Canvas->TextOut(40, m, MENSAJE(msgResultadosMoore));
		m = m + m1 * 2;

                for (int i = 0; i < txAsociado->Lines->Count; i++)
                {
        		Printer()->Canvas->TextOut(40, m, txAsociado->Lines->Strings[i]);
                        m = m + m1;
                }
		m = m + m1;

		Printer()->Canvas->TextOut(40, m, MENSAJE(msgTablaTranEstSal));
		m = m + m1 * 2;

		// Printer()->Canvas->Font->Style="";
		Printer()->Canvas->Font->Size = 8;
		for(i = 0; i < Form9->Tabla->ColCount; i++)
		{
			for(j = 0; j < Form9->Tabla->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 300) + 200, j * m1 + m, Form9->Tabla->Cells[i][j]);
			}
		}

		linea1x = 200;
		linea1y = m + m1 + 1;
		sgte = sgte + (j * 100) + 200;
		long1 = (i * 300);
		Printer()->Canvas->MoveTo(linea1x, linea1y);
		Printer()->Canvas->LineTo(linea1x + long1, linea1y);

		m += m1 * (Form9->Tabla->RowCount + 1);

		// Tabla de codificacion de estados
		Printer()->Canvas->Font->Size = 12;
		Printer()->Canvas->TextOut(40, m, MENSAJE(msgTablaCodifTransCodif));
		m = m + m1 * 2;
		sgte = sgte + 80;

		Printer()->Canvas->Font->Size = 8;
		for(i = 0; i < Form9->Codifica->ColCount; i++)
		{
			for(j = 0; j < Form9->Codifica->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 300) + 200, j * m1 + m, Form9->Codifica->Cells[i][j]);
			}
		}

		// m+=m1*Form9->Tabla->RowCount;
		long2a = (i * 300);
		linea2ax = 200;
		linea2y = m + m1 + 1;
		Printer()->Canvas->MoveTo(linea2ax, linea2y - 5);
		Printer()->Canvas->LineTo(linea2ax + long2a, linea2y - 5);
		linea2bx = (i * 300) + 400;
		izq = (i * 300) + 200;

		for(i = 0; i < Form9->Tablacod->ColCount; i++)
		{
			for(j = 0; j < Form9->Tablacod->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 300) + 200 + izq, (j * m1) + m, Form9->Tablacod->Cells[i][j]);
			}
		}

		long2b = (i * 300) + izq;

		Printer()->Canvas->MoveTo(linea2bx, linea2y - 3);
		Printer()->Canvas->LineTo(linea2bx + long2b - izq, linea2y - 3);

		m = m + m1 * (Form9->Tablacod->RowCount + 1);
		sgte = sgte + (j * 100) + 200;

		Printer()->Canvas->Font->Size = 12;

		// Tabla de excitacion de biestables
		Printer()->Canvas->TextOut(40, m, MENSAJE(msgTablaExcitacion));
		m = m + m1 * 2;
		sgte = sgte + 80;

		Printer()->Canvas->Font->Size = 8;

		for(i = 0; i < Form9->Excitacion->ColCount; i++)
		{
			Printer()->Canvas->TextOut((i * 160) + 200, i + m, Form9->Excitacion->Cells[i][0]);
		}

		sgte = sgte + 100;
		m = m + m1;

		for(i = 0; i < Form9->Excitacion->ColCount; i++)
		{
			for(j = 1; j < Form9->Excitacion->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 160) + 200, (j * m1) + m, Form9->Excitacion->Cells[i][j]);
				if
				(
					m +
						(Form9->Solucion->Items->Count + 2) *
						Printer()->Canvas->TextHeight("XXX") > Printer()->PageHeight
				)
				{
					Printer()->NewPage();
					m = 100;
				}
			}
		}

		linea3x = 200;
		linea3y = m;
		long3 = (i * 160);
		Printer()->Canvas->MoveTo(linea3x, linea3y);
		Printer()->Canvas->LineTo(linea3x + long3, linea3y);

		m += m1 * (Form9->Excitacion->RowCount + 1);

		sgte = sgte + (j * 50) + 100;
		Printer()->Canvas->Font->Size = 12;

		// Solucion
		if(m + (Form9->Solucion->Items->Count + 4) * Printer()->Canvas->TextHeight("XXX") + 5 > Printer()->PageHeight)
		{
			Printer()->NewPage();
			m = 100;
		}

		Printer()->Canvas->TextOut(40, m, MENSAJE(msgExprSimplificadas));
		m += m1 * 2;

		Printer()->Canvas->Font->Size = 10;

		/*~~~~~~~~*/
		int sig = 0;
		/*~~~~~~~~*/

		for(i = 0; i < Form9->ListaJK->Items->Count; i++)
		{
			Printer()->Canvas->TextOut(200, (i * m1) + m, Form9->ListaJK->Items->Strings[i]);
		}

		m += m1 * Form9->ListaJK->Items->Count;

		for(i = 0; i < Form9->ListaD->Items->Count; i++)
		{
			Printer()->Canvas->TextOut(200, (i * m1) + m, Form9->ListaD->Items->Strings[i]);
		}

		m += m1 * Form9->ListaD->Items->Count;

		for(i = 0; i < Form9->ListaSol->Items->Count; i++)
		{
			Printer()->Canvas->TextOut(200, (i * m1) + m, Form9->ListaSol->Items->Strings[i]);
		}

		Printer()->Canvas->Font->Size = 12;

		// Lineas pra makear las tablas :)
		Printer()->EndDoc();
	}
	else
	{	// AUTOMATA DE MEALY

		TablaMealy();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int m = 100;
		int sgte = 0;
		int izq = 0;
		int j, i;
		int linea1x, linea2ax, linea2bx, linea3x;
		int linea1y, linea2y, linea3y;
		int long1, long2a, long2b, long3;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Printer()->Title = ANSIMENSAJE(msgResultados)+" " + Form1Boole2->Caption;
		Printer()->Orientation = poPortrait;
		Printer()->BeginDoc();

		// Tabla
		Printer()->Canvas->Font->Name = "MS Sans Serif";

		// Printer()->Canvas->Font->Style=fsBold;
		Printer()->Canvas->Font->Size = 12;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int m1 = Printer()->Canvas->TextHeight("XXX") + 10;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Printer()->Canvas->TextOut(40, m, MENSAJE(msgResultadosMealy));
		m = m + m1 * 2;

                for (int i = 0; i < txAsociado->Lines->Count; i++)
                {
        		Printer()->Canvas->TextOut(40, m, txAsociado->Lines->Strings[i]);
                        m = m + m1;
                }
		m = m + m1;

		Printer()->Canvas->TextOut(40, m, MENSAJE(msgTablaTranEstSal));
		m = m + m1 * 2;

		// Printer()->Canvas->Font->Style="";
		Printer()->Canvas->Font->Size = 8;
		for(i = 0; i < Form10->Tabla->ColCount; i++)
		{
			for(j = 0; j < Form10->Tabla->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 300) + 200, j * m1 + m, Form10->Tabla->Cells[i][j]);
			}
		}

		linea1x = 200;
		linea1y = m + m1 + 1;
		sgte = sgte + (j * 100) + 200;
		long1 = (i * 300);
		Printer()->Canvas->MoveTo(linea1x, linea1y);
		Printer()->Canvas->LineTo(linea1x + long1, linea1y);

		m += m1 * (Form10->Tabla->RowCount + 1);

		// Tabla de codificacion de estados
		Printer()->Canvas->Font->Size = 12;
		Printer()->Canvas->TextOut(40, m, MENSAJE(msgTablaCodifEstados));
		m = m + m1 * 2;
		sgte = sgte + 80;

		Printer()->Canvas->Font->Size = 8;
		for(i = 0; i < Form10->Codifica->ColCount; i++)
		{
			for(j = 0; j < Form10->Codifica->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 300) + 200, j * m1 + m, Form10->Codifica->Cells[i][j]);
			}
		}

		// m+=m1*Form10->Tabla->RowCount;
		long2a = (i * 300);
		linea2ax = 200;
		linea2y = m + m1 + 1;
		Printer()->Canvas->MoveTo(linea2ax, linea2y - 5);
		Printer()->Canvas->LineTo(linea2ax + long2a, linea2y - 5);
		linea2bx = (i * 300) + 400;
		izq = (i * 300) + 200;

		for(i = 0; i < Form10->Tablacod->ColCount; i++)
		{
			for(j = 0; j < Form10->Tablacod->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 300) + 200 + izq, (j * m1) + m, Form10->Tablacod->Cells[i][j]);
			}
		}

		long2b = (i * 300) + izq;

		Printer()->Canvas->MoveTo(linea2bx, linea2y - 3);
		Printer()->Canvas->LineTo(linea2bx + long2b - izq, linea2y - 3);

		m = m + m1 * (Form10->Tablacod->RowCount + 1);
		sgte = sgte + (j * 100) + 200;

		Printer()->Canvas->Font->Size = 12;

		// Tabla de excitacion de biestables
		Printer()->Canvas->TextOut(40, m, MENSAJE(msgTablaExcitacion));
		m = m + m1 * 2;
		sgte = sgte + 80;

		Printer()->Canvas->Font->Size = 8;

		for(i = 0; i < Form10->Excitacion->ColCount; i++)
		{
			Printer()->Canvas->TextOut((i * 160) + 200, i + m, Form10->Excitacion->Cells[i][0]);
		}

		sgte = sgte + 100;
		m = m + m1;

		for(i = 0; i < Form10->Excitacion->ColCount; i++)
		{
			for(j = 1; j < Form10->Excitacion->RowCount; j++)
			{
				Printer()->Canvas->TextOut((i * 160) + 200, (j * m1) + m, Form10->Excitacion->Cells[i][j]);
				if
				(
					m +
						(Form10->Solucion->Items->Count + 2) *
						Printer()->Canvas->TextHeight("XXX") > Printer()->PageHeight
				)
				{
					Printer()->NewPage();
					m = 100;
				}
			}
		}

		linea3x = 200;
		linea3y = m;
		long3 = (i * 160);
		Printer()->Canvas->MoveTo(linea3x, linea3y);
		Printer()->Canvas->LineTo(linea3x + long3, linea3y);

		m += m1 * (Form10->Excitacion->RowCount + 1);

		sgte = sgte + (j * 50) + 100;
		Printer()->Canvas->Font->Size = 12;

		// Solucion
		if(m + (Form10->Solucion->Items->Count + 4) * Printer()->Canvas->TextHeight("XXX") + 5 > Printer()->PageHeight)
		{
			Printer()->NewPage();
			m = 100;
		}

		Printer()->Canvas->TextOut(40, m, MENSAJE(msgExprSimplificadas));
		m += m1 * 2;

		Printer()->Canvas->Font->Size = 10;

		for(i = 0; i < Form10->ListaJK->Items->Count; i++)
		{
			Printer()->Canvas->TextOut(200, (i * m1) + m, Form10->ListaJK->Items->Strings[i]);
		}

		m += m1 * Form10->ListaJK->Items->Count;

		for(i = 0; i < Form10->ListaD->Items->Count; i++)
		{
			Printer()->Canvas->TextOut(200, (i * m1) + m, Form10->ListaD->Items->Strings[i]);
		}

		m += m1 * Form10->ListaD->Items->Count;

		for(i = 0; i < Form10->ListaSol->Items->Count; i++)
		{
			Printer()->Canvas->TextOut(200, (i * m1) + m, Form10->ListaSol->Items->Strings[i]);
		}

		Printer()->Canvas->Font->Size = 12;

		// Lineas pra makear las tablas :)
		Printer()->EndDoc();

		/*
		 * ANTES IMPRIME SUPERPUESTO int sgte=0; int izq=0; TablaMealy(); int j,i; int
		 * linea1x,linea2ax,linea2bx,linea3x; int linea1y,linea2y,linea3y; int
		 * long1,long2a,long2b,long3; Printer()->Title="Resultados "+Form1Boole2->Caption;
		 * Printer()->Orientation=poPortrait; Printer()->BeginDoc(); //Tabla
		 * Printer()->Canvas->Font->Name="MS Sans Serif";
		 * //Printer()->Canvas->Font->Style=fsBold; Printer()->Canvas->Font->Size=12;
		 * Printer()->Canvas->TextOut(40,40,"Tabla de transicion de estados y salidas");
		 * //Printer()->Canvas->Font->Style=""; linea1y=275; for
		 * (i=0;i<Form10->Tabla->ColCount;i++) { for (j=0;j<Form10->Tabla->RowCount;j++) {
		 * Printer()->Canvas->TextOut((i*300)+200,(j*100)+200+sgte,Form10->Tabla->Cells[i][j]);
		 * } } linea1x=200; sgte=sgte+(j*100)+200; long1=(i*300); //Tabla de codificacion
		 * de estados Printer()->Canvas->TextOut(40,80+sgte,"Tabla de codificacion de
		 * estados"); sgte=sgte+80; linea2y=sgte+275; for
		 * (i=0;i<Form10->Codifica->ColCount;i++) { for
		 * (j=0;j<Form10->Codifica->RowCount;j++) {
		 * Printer()->Canvas->TextOut((i*300)+200,(j*100)+200+sgte,Form10->Codifica->Cells[i][j]);
		 * } } linea2ax=200; linea2bx=(i*300)+400; long2a=(i*300); izq=(i*300)+200; for
		 * (i=0;i<Form10->Tablacod->ColCount;i++) { for
		 * (j=0;j<Form10->Tablacod->RowCount;j++) {
		 * Printer()->Canvas->TextOut((i*300)+200+izq,(j*100)+200+sgte,Form10->Tablacod->Cells[i][j]);
		 * } } sgte=sgte+(j*100)+200; long2b=(i*300)+izq; //Tabla de excitacion de
		 * biestables Printer()->Canvas->TextOut(40,80+sgte,"Tabla de excitacion de
		 * biestables"); sgte=sgte+80; linea3x=200; linea3y=sgte+200;
		 * Printer()->Canvas->Font->Size=8; for (i=0;i<Form10->Excitacion->ColCount;i++) {
		 * Printer()->Canvas->TextOut((i*160)+200,150+sgte,Form10->Excitacion->Cells[i][0]);
		 * } sgte=sgte+100; for (i=0;i<Form10->Excitacion->ColCount;i++) { for
		 * (j=1;j<Form10->Excitacion->RowCount;j++) {
		 * Printer()->Canvas->TextOut((i*160)+200,(j*50)+100+sgte,Form10->Excitacion->Cells[i][j]);
		 * } } sgte=sgte+(j*50)+100; long3=(i*160); Printer()->Canvas->Font->Size=12;
		 * //Solucion Printer()->Canvas->TextOut(40,80+sgte,"Solución");
		 * Printer()->Canvas->Font->Size=10; for
		 * (i=0;i<Form10->Solucion->Items->Count;i++) {
		 * Printer()->Canvas->TextOut(200,(i*60)+200+sgte,Form10->Solucion->Items->Strings[i]);
		 * } Printer()->Canvas->Font->Size=12; //Lineas pra makear las tablas :)
		 * Printer()->Canvas->MoveTo(linea1x,linea1y);
		 * Printer()->Canvas->LineTo(linea1x+long1,linea1y);
		 * Printer()->Canvas->MoveTo(linea3x,linea3y);
		 * Printer()->Canvas->LineTo(linea3x+long3,linea3y);
		 * Printer()->Canvas->MoveTo(linea2ax,linea2y);
		 * Printer()->Canvas->LineTo(linea2ax+long2a,linea2y);
		 * Printer()->Canvas->MoveTo(linea2bx,linea2y);
		 * Printer()->Canvas->LineTo(linea2bx+long2b,linea2y); Printer()->EndDoc();
		 */
	}
}

void __fastcall TForm1Boole2::mnTextoAsociadoClick(TObject *Sender)
{
	if(mnTextoAsociado->Checked == false)
	{
    pTextAsoc->Visible = true;
		mnTextoAsociado->Checked = true;
	}
	else
	{
    pTextAsoc->Visible = false;
		mnTextoAsociado->Checked = false;
	}

	Form1Boole2->SetFocus();
}
//---------------------------------------------------------------------------


void TForm1Boole2::IniciarSimulacionInteractiva(int tipoSimulacion)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int verificacion = HacerVerificacion(false, CORRECCION);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(verificacion == AUTOMATA_COMPLETO || verificacion == AUTOMATA_CORRECTO_FALTA_TRANSICION)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int numVarsEnt = Sistema.DevolverNumCarEnt();
		int numVarsSal = Sistema.DevolverNumCarSal();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		// El estado 0 es (arbitrariamente) el inicial
		Sistema.indiceInicial = 0;
		edEstadoActual->Text = Sistema.CogerNombreCirculoActual();

		// Configuramos el grid de entrada
		gridVarsEnt->ColCount = numVarsEnt;
		gridVarsEnt->Width = (gridVarsEnt->GridLineWidth * (numVarsEnt + 1)) + (gridVarsEnt->DefaultColWidth * numVarsEnt) + 4;
		for(int i = 0; i < numVarsEnt; i++)
			gridVarsEnt->Cells[i][0] = Vars[numVarsEnt - i - 1];

		// Configuramos el grid de salida
		gridVarsSal->ColCount = numVarsSal;
		gridVarsSal->Width = (gridVarsSal->GridLineWidth * (numVarsSal + 1)) + (gridVarsSal->DefaultColWidth * numVarsSal) + 4;
		for(int i = 0; i < numVarsSal; i++)
			gridVarsSal->Cells[i][0] = Vars[numVarsSal - i - 1 + 5];

		// Configuramos el combo-box de estados iniciales
		comboInicial->Items->Clear();
		for(int i = 0; i < Sistema.numcirculos; i++) comboInicial->Items->Add(Sistema.cogerEtiq(i));
		comboInicial->ItemIndex = 0;


		// Flags
		simulando = true;
		simulacion = INTERACTIVA;
		pSimulacion->Visible = true;

                if (tipoSimulacion == NORMAL)
                {
                        btAplicar->Visible = true;
                        edEntrada->Visible = true;

                        gridVarsEnt->Top=16;
                }
                else if (tipoSimulacion == RAPIDA)
                {
                        btAplicar->Visible = false;
                        edEntrada->Visible = false;

                        gridVarsEnt->Top=48;
                }


		fLog->memoLog->Clear();
		fLog->pasoActual = 1;
		fLog->EscribirCabecera(Sistema.Tipo, tipoSimulacion);
    
		// Hacemos un RESET
		btReset->Click();
	}

}


void TForm1Boole2::IniciarSimulacionBatch(int tipoSimulacion)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int verificacion = HacerVerificacion(false, CORRECCION);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(verificacion == AUTOMATA_COMPLETO || verificacion == AUTOMATA_CORRECTO_FALTA_TRANSICION)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int numVarsEnt = Sistema.DevolverNumCarEnt();
		int numVarsSal = Sistema.DevolverNumCarSal();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		// El estado 0 es (arbitrariamente) el inicial
		Sistema.indiceInicial = 0;

		// Establecemos Indices
                if (tipoSimulacion==RAPIDA)
                {
		        fSimulacion->indiceRESET = 1;
        		fSimulacion->indiceCLK = fSimulacion->indiceRESET + 1;
           	fSimulacion->indiceEntInicial = fSimulacion->indiceCLK + 1;
        		fSimulacion->indiceEntFinal = fSimulacion->indiceEntInicial + numVarsEnt - 1;
        		fSimulacion->indiceEstado = fSimulacion->indiceEntFinal + 1;
        		fSimulacion->indiceSalInicial = fSimulacion->indiceEstado + 1;
        		fSimulacion->indiceSalFinal = fSimulacion->indiceSalInicial + numVarsSal - 1;
            fSimulacion->gridSimulacion->ColCount = fSimulacion->indiceSalFinal + 1;
        	}
                else if (tipoSimulacion==NORMAL)
                {
        		fSimulacion->indiceRESET = 1;
        		fSimulacion->indiceCLK = fSimulacion->indiceRESET + 1;
        		fSimulacion->indiceEstado = fSimulacion->indiceCLK + 1;
        		fSimulacion->indiceEntInicial = fSimulacion->indiceEstado + 1;
        		fSimulacion->indiceEntFinal = fSimulacion->indiceEntInicial + numVarsEnt - 1;
            fSimulacion->indiceSalInicial = fSimulacion->indiceEntFinal + 1;
        		fSimulacion->indiceSalFinal = fSimulacion->indiceSalInicial + numVarsSal - 1;
        		fSimulacion->indiceEstadoSig = fSimulacion->indiceSalFinal + 1;
		        fSimulacion->gridSimulacion->ColCount = fSimulacion->indiceEstadoSig + 1;
                }

		fSimulacion->gridSimulacion->RowCount = 4;

		fSimulacion->gridSimulacion->Cells[0][0] = "#";
		fSimulacion->gridSimulacion->Cells[fSimulacion->indiceCLK][0] = "CLK";
		fSimulacion->gridSimulacion->ColWidths[fSimulacion->indiceCLK] = 50;
		fSimulacion->gridSimulacion->Cells[fSimulacion->indiceRESET][0] = "RESET";
		fSimulacion->gridSimulacion->ColWidths[fSimulacion->indiceRESET] = 50;
		fSimulacion->gridSimulacion->Cells[fSimulacion->indiceEstado][0] = "Q(t)";
		fSimulacion->gridSimulacion->ColWidths[fSimulacion->indiceEstado] = 50;
    if (tipoSimulacion == NORMAL)
    {
  		fSimulacion->gridSimulacion->Cells[fSimulacion->indiceEstadoSig][0] = "Q(t+1)";
	  	fSimulacion->gridSimulacion->ColWidths[fSimulacion->indiceEstadoSig] = 50;
    }
		fSimulacion->spinFilas->Value = 3;


		for(int i = fSimulacion->indiceEntInicial; i <= fSimulacion->indiceEntFinal; i++)
			fSimulacion->gridSimulacion->Cells[i][3] = "0";

		// Configuramos el grid de entrada
		for(int i = 0; i < numVarsEnt; i++)
			fSimulacion->gridSimulacion->Cells[fSimulacion->indiceEntInicial + i][0] = Vars[numVarsEnt - i - 1];

		// Configuramos el grid de salida
		for(int i = 0; i < numVarsSal; i++)
			fSimulacion->gridSimulacion->Cells[fSimulacion->indiceSalInicial + i][0] = Vars[numVarsSal - i - 1 + 5];

		// Configuramos el combo-box de estados iniciales
		fSimulacion->comboInicial->Items->Clear();
		for(int i = 0; i < Sistema.numcirculos; i++) fSimulacion->comboInicial->Items->Add(Sistema.cogerEtiq(i));
		fSimulacion->comboInicial->ItemIndex = 0;


		fSimulacion->BorrarTabla();

		// Flags
		simulando = true;
		simulacion = BATCH_PARADO;

		fSimulacion->Show();

		fLog->memoLog->Clear();
		fLog->EscribirCabecera(Sistema.Tipo, tipoSimulacion);
}

}
void __fastcall TForm1Boole2::InteractivaRapidaClick(
      TObject *Sender)
{
        tipoSimulacion = RAPIDA;
        IniciarSimulacionInteractiva(RAPIDA);
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::BatchRapidaClick(TObject *Sender)
{
        tipoSimulacion = RAPIDA;
        IniciarSimulacionBatch(RAPIDA);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::Contraer1Click(TObject *Sender)
{
        Sistema.Contraer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::Expandir1Click(TObject *Sender)
{
	Sistema.Expandir();
}
//---------------------------------------------------------------------------


AnsiString NombreVHDL(AnsiString st)
{
	st = st.Trim();
	for(int i=1; i<=st.Length(); i++)
        	if (st[i]==' ')
                	st[i]='_';
        return st;
}


void TForm1Boole2::CrearCodigoVHDL()
{
	AnsiString Titulo = NombreVHDL(Sistema.Titulo==""?AnsiString("Sin_Titulo"):Sistema.Titulo);
        AnsiString estadoInicial = NombreVHDL(Sistema.circulo[0].Etiqueta1);

        if(mWeblabMode)
        {
                Titulo = "base";
        }

	Form14->PDL->Lines->Clear();

        if(mWeblabMode)
        {
                std::string clockLine = "-- ";
                clockLine += mWeblabClockDirective;
                Form14->PDL->Lines->Add(clockLine.c_str());
        }

        // Cabecera
        Form14->PDL->Lines->Add("library IEEE;");
        Form14->PDL->Lines->Add("use IEEE.STD_LOGIC_1164.ALL;");
        Form14->PDL->Lines->Add("use IEEE.STD_LOGIC_ARITH.ALL;");
        Form14->PDL->Lines->Add("use IEEE.STD_LOGIC_UNSIGNED.ALL;");

        Form14->PDL->Lines->Add("");

        // Nombre de la entidad
	Form14->PDL->Lines->Add("entity " + Titulo + " is");
	Form14->PDL->Lines->Add("\tPort (");

        if(!mWeblabMode)
        {
	        Form14->PDL->Lines->Add("\t\tinicio: in std_logic;");
        	Form14->PDL->Lines->Add("\t\tck: in std_logic;");
        	for (int i=0; i<Sistema.NumCarEnt;i++)
	        	Form14->PDL->Lines->Add("\t\t" + NombreVHDL(DevuelveVar(i)) + ": in std_logic;");
	        for (int i=0; i<Sistema.NumCarSal;i++)
	        	Form14->PDL->Lines->Add("\t\t" + NombreVHDL(DevuelveVar(5+i)) + ": out std_logic" + ((i==Sistema.NumCarSal-1)?"":";"));
        }
        else
        {
                Form14->PDL->Lines->Add("\t\t");
                Form14->PDL->Lines->Add("\t\tinicio : in std_logic;");

                AnsiString exeFile=Application->ExeName;
                AnsiString exePath=ExtractFilePath(exeFile);

                // Cargar la lista de entradas salidas del archivo.
                std::ifstream fin((exePath + "/weblab_inouts.dat" ).c_str());
                std::string line;
                while(std::getline(fin, line))
                {
                        Form14->PDL->Lines->Add(line.c_str());
                }
                fin.close();
        }

	Form14->PDL->Lines->Add("\t\t);");
	Form14->PDL->Lines->Add("end " + Titulo + ";");

        Form14->PDL->Lines->Add("");

        Form14->PDL->Lines->Add("architecture behavioral of " + Titulo + " is");

        Form14->PDL->Lines->Add("");

        AnsiString nombresEstados;
        nombresEstados = "(";
        nombresEstados += NombreVHDL(Sistema.circulo[0].Etiqueta1);
        for(int i = 1; i<Sistema.numcirculos; i++)
	        nombresEstados += ", " + NombreVHDL(Sistema.circulo[i].Etiqueta1);
        nombresEstados += ")";

        Form14->PDL->Lines->Add("type nombres_estados is "+nombresEstados+";");
        Form14->PDL->Lines->Add("signal estado: nombres_estados;");

	// :MOD: Fixed bug here. One-element vectors would later give compile errors. ~lrg
	int vlen = Sistema.NumCarEnt-1;
	if(vlen > 0)
        	Form14->PDL->Lines->Add("signal entrada_aux: std_logic_vector (" + AnsiString(vlen) +" downto 0);");
	else
		Form14->PDL->Lines->Add("signal entrada_aux: std_logic;");

        Form14->PDL->Lines->Add("");

        Form14->PDL->Lines->Add("begin");

        Form14->PDL->Lines->Add("");

        AnsiString entradas;

        if(!mWeblabMode)
        {
                entradas = NombreVHDL(DevuelveVar(0));
	        for (int i=1; i<Sistema.NumCarEnt;i++)
		        entradas += "&" + NombreVHDL(DevuelveVar(i));
        }
        else
        {
                std::stringstream oss;
                oss << "swi" << Sistema.NumCarEnt - 1 << "";
                for (int i=1; i<Sistema.NumCarEnt;i++)
                {
                        oss << "&" << "swi" << Sistema.NumCarEnt - i - 1 << "";
                }
                std::string str = oss.str();
                entradas = str.c_str();
        }

	// :MOD: Semicolon was not being added here. ~lrg
	Form14->PDL->Lines->Add("entrada_aux<=" + entradas + ";");

        Form14->PDL->Lines->Add("");

        if(mWeblabMode == false)
	        Form14->PDL->Lines->Add("process(inicio, ck)");
        else
                Form14->PDL->Lines->Add("process(inicio, clk)");


	Form14->PDL->Lines->Add("begin");

        if(mWeblabMode == false)
	        Form14->PDL->Lines->Add("if inicio='1' then");
        else
                Form14->PDL->Lines->Add("if but0='1' then");

        Form14->PDL->Lines->Add("\testado<="+estadoInicial+";");

        if(mWeblabMode == false)
        {
                Form14->PDL->Lines->Add("elsif ck='1' and ck'event then");
        }
        else
        {
                Form14->PDL->Lines->Add("elsif clk='1' and clk'event then");
        }

        Form14->PDL->Lines->Add("\tcase estado is");

        AnsiString com = (Sistema.NumCarEnt==1?"'":"\"");
	int maximoEntradas = ElevarBase2(Sistema.NumCarEnt);

        for (int i=0; i<Sistema.numcirculos;i++)
        {
		Form14->PDL->Lines->Add("\t\twhen "+NombreVHDL(Sistema.circulo[i].Etiqueta1)+" =>");
		Form14->PDL->Lines->Add("\t\t\tcase entrada_aux is");
		for(int ent = 0; ent < maximoEntradas; ent++)
		{
			AnsiString	entBin = Dec2BinAcot(ent, Sistema.NumCarEnt);
                        bool encontrado=false;
                        int siguienteEstado;
                        for(int j = 0; j < Sistema.numflechas && !encontrado; j++)
                        	if (Sistema.flecha[j].CirculoSale == i && Sistema.PuedeSeguir(entBin, Sistema.flecha[j].Etiqueta1))
                                {
                                	encontrado = true;
                                        siguienteEstado = Sistema.flecha[j].CirculoEntra;
                                }
                        if (encontrado)
	                        Form14->PDL->Lines->Add("\t\t\t\twhen " + com + entBin + com + " => estado<=" + NombreVHDL(Sistema.circulo[siguienteEstado].Etiqueta1) + ";");
                }
		Form14->PDL->Lines->Add("\t\t\t\twhen others => estado<="+estadoInicial+";");
		Form14->PDL->Lines->Add("\t\t\tend case;");
        }
	Form14->PDL->Lines->Add("\t\twhen others => estado<="+estadoInicial+";");
	Form14->PDL->Lines->Add("\tend case;");
	Form14->PDL->Lines->Add("end if;");
	Form14->PDL->Lines->Add("end process;");

        Form14->PDL->Lines->Add("");

        if (Sistema.Tipo == MOORE)
        {
		Form14->PDL->Lines->Add("process(estado)");
		Form14->PDL->Lines->Add("begin");
		Form14->PDL->Lines->Add("case estado is");
	        for (int i=0; i<Sistema.numcirculos;i++)
	        {
			Form14->PDL->Lines->Add("\twhen "+NombreVHDL(Sistema.circulo[i].Etiqueta1)+" =>");
	                for (int j=0; j<Sistema.NumCarSal; j++)
			{
	                	char salida = Sistema.circulo[i].Etiqueta2[j+1];
	                        AnsiString nomSalida = NombreVHDL(DevuelveVar(j+5));

                                if(mWeblabMode == true)
                                {
                                        std::ostringstream oss;
                                        oss << "led" << Sistema.NumCarSal - j - 1<< "";
                                        std::string str = oss.str();
                                        nomSalida = str.c_str();
                                }

	                        if (salida=='X')
					Form14->PDL->Lines->Add("\t\t--" +nomSalida+"<='X';");
	                        else
					Form14->PDL->Lines->Add("\t\t"+nomSalida+"<='" + salida + "';");
	                }
		}
		//when others => s<='0'; -- el tomado por inicio
		Form14->PDL->Lines->Add("end case;");
		Form14->PDL->Lines->Add("end process;");
        }
        else if (Sistema.Tipo == MEALY)
        {
		Form14->PDL->Lines->Add("process(estado, entrada_aux)");
		Form14->PDL->Lines->Add("begin");
		Form14->PDL->Lines->Add("case estado is");

	        for (int i=0; i<Sistema.numcirculos;i++)
	        {
			Form14->PDL->Lines->Add("\twhen "+NombreVHDL(Sistema.circulo[i].Etiqueta1)+" =>");
			Form14->PDL->Lines->Add("\t\tcase entrada_aux is");
	       		for(int ent = 0; ent < maximoEntradas; ent++)
			{
				AnsiString	entBin = Dec2BinAcot(ent, Sistema.NumCarEnt);
	                        bool encontrado=false;
	                        AnsiString salida;
	                        for(int j = 0; j < Sistema.numflechas && !encontrado; j++)
	                        	if (Sistema.flecha[j].CirculoSale == i && Sistema.PuedeSeguir(entBin, Sistema.flecha[j].Etiqueta1))
	                                {
	                                	encontrado = true;
	                                        salida = Sistema.flecha[j].Etiqueta2;
	                                }
	                        if (encontrado)
                                {
                      			Form14->PDL->Lines->Add("\t\t\twhen " + com + entBin + com + " =>");
			                for (int j=0; j<Sistema.NumCarSal; j++)
					{
			                	char carSalida = salida[j+1];
		       	                        AnsiString nomSalida = NombreVHDL(DevuelveVar(j+5));

			                        if (carSalida=='X')
							Form14->PDL->Lines->Add("\t\t\t\t--" +nomSalida+"<='X';");
			                        else
							Form14->PDL->Lines->Add("\t\t\t\t"+nomSalida+"<='" + carSalida + "';");
			                }

                                }
            		}
			//when others => s<='0'; --el valor de inicio
                        Form14->PDL->Lines->Add("\t\tend case;");
                }
		//when others => s<='0'; -- el tomado por inicio
		Form14->PDL->Lines->Add("end case;");
		Form14->PDL->Lines->Add("end process;");
        }

        Form14->PDL->Lines->Add("");

	Form14->PDL->Lines->Add("end behavioral;");
}


void __fastcall TForm1Boole2::ExportaraVHDL1Click(TObject *Sender)
{
        CrearCodigoVHDL();

        // Bug fix: Filter needs to be set before execution. ~lrg
	SaveDialog2->Filter=MENSAJE(msgFiltroVHDL);

	if(SaveDialog2->Execute())
	{
		SalvarPDL(SaveDialog2->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::CodigoVHDL1Click(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = false;
	Form1Boole2->Enabled = false;
        CrearCodigoVHDL();
	Form14->Show();
	Form14->SetFocus();

}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::ExportaraJEDEC1Click(TObject *Sender)
{
	SaveDialog2->Filter=MENSAJE(msgFiltroJEDEC);
	if(SaveDialog2->Execute())
	{
	       	list <list<string> > listFunciones;
		int Rango, Limite, numCubos;

                string entradas[100];

		Rango = 1;
		while(ElevarBase2(Rango) < Sistema.NumCirculos())
		{
			Rango++;
		}
		Limite = ElevarBase2(Rango);
                numCubos = ElevarBase2(Sistema.DevolverNumCarEnt() + Rango);
		if(Sistema.DevolverTipo() == MOORE)
		{
			TablaMoore();


                        int ent =0;
                        for(int k=0;k<Sistema.DevolverNumCarEnt();k++)
                        {
                        	AnsiString nombre =  Form9->Excitacion->Cells[k][0];
				entradas[ent++]=string(nombre.c_str());
                        }
                        for(int k=Sistema.DevolverNumCarEnt();k<Sistema.DevolverNumCarEnt() + Rango;k++)
                        {
                        	AnsiString nombre =  Form9->Excitacion->Cells[k][0];
				entradas[ent++]=string(nombre.c_str());
                        }

                        // Funciones D
               		for(int i = 0; i < Rango; i++)
			{
                        	// Variable "D" + i
                                int numVars = Rango + Sistema.DevolverNumCarEnt();

	                 	list<string> listCubos;
                                listCubos.push_back("s");
                                listCubos.push_back(string("Q")+AnsiString(i).c_str());


				rdSimplificador *simp;
			        simp = new rdSimplificador(numVars);
		        	// 0 --> Obtención de IPs por el método Q-M
			        simp->SetObtenedor(0);
			        // 0 --> Seleccion de IPs por método recursivo sesgado
				simp->SetSelector(0);
				for(int j = 0; j < numCubos; j++)
				{
                                	AnsiString cubo="";
                                        for(int k=0;k<Sistema.DevolverNumCarEnt();k++)
                                        	cubo+=Form9->Excitacion->Cells[k][j+1];
                                        for(int k=Sistema.DevolverNumCarEnt();k<Sistema.DevolverNumCarEnt() + Rango;k++)
                                        	cubo+=Form9->Excitacion->Cells[k][j+1];

					CuboBool cAux=CuboBool(cubo.c_str());
					cAux.literales = numVars;

					if (Form9->Excitacion->Cells[Sistema.DevolverNumCarEnt() + (5*Rango) - i - 1][j+1] == '1')
		                                simp->AnyadirMint(cAux);
					else if(Form9->Excitacion->Cells[Sistema.DevolverNumCarEnt() + (5*Rango) - i - 1][j+1] == 'X')
		                                simp->AnyadirTI(cAux);
				}
				simp->Simplificar();

                                for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
		                {
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}

                		delete simp;
                                listFunciones.push_back(listCubos);
		        }

                        // Funciones Salida
               		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
			{
	                        int numVars = Rango;
                                int numVarsFalso = Rango + Sistema.DevolverNumCarEnt();

	                 	list<string> listCubos;
                                listCubos.push_back("c");
                                listCubos.push_back(Vars[5 + Sistema.DevolverNumCarSal() - i - 1].c_str());

				rdSimplificador *simp;
			        simp = new rdSimplificador(numVarsFalso);
		        	// 0 --> Obtención de IPs por el método Q-M
			        simp->SetObtenedor(0);
			        // 0 --> Seleccion de IPs por método recursivo sesgado
				simp->SetSelector(0);
				for(int j = 0; j < Limite; j++)
				{
					CuboBool cAux=CuboBool(j);
					AnsiString cubo="";
                                        for(int k=0;k<Sistema.DevolverNumCarEnt();k++)
                                        	cubo+="-";
                                        cubo += cAux.aString(numVars).c_str();
                                        cAux=CuboBool(cubo.c_str());

					cAux.literales = numVarsFalso;

					if (Form9->Salidacod->Cells[Sistema.DevolverNumCarSal() + i][j+1] == '1')
		                                simp->AnyadirMint(cAux);
					else if(Form9->Salidacod->Cells[Sistema.DevolverNumCarSal() + i][j+1] == 'X')
		                                simp->AnyadirTI(cAux);
				}
				simp->Simplificar();

                                for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
		                {
                                	listCubos.push_back((*j).aString(numVarsFalso));
				}


				for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVarsFalso));
				}


				for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVarsFalso));
				}

                		delete simp;
                                listFunciones.push_back(listCubos);
		        }

		}
		else
		{
			TablaMealy();
                        int numVars = Rango + Sistema.DevolverNumCarEnt();

                        for(int k=0;k<numVars;k++)
                        {
                        	AnsiString nombre =  Form9->Excitacion->Cells[k][0];
				entradas[k]=string(nombre.c_str());
                        }


                        // Variables D
               		for(int i = 0; i < Rango; i++)
			{
                                // Variables "D" + i
	                 	list<string> listCubos;
                                listCubos.push_back("s");
                                listCubos.push_back(string("Q")+AnsiString(i).c_str());

				rdSimplificador *simp;
			        simp = new rdSimplificador(numVars);
		        	// 0 --> Obtención de IPs por el método Q-M
			        simp->SetObtenedor(0);
			        // 0 --> Seleccion de IPs por método recursivo sesgado
				simp->SetSelector(0);
				for(int j = 0; j < numCubos; j++)
				{
					CuboBool cAux=CuboBool(j);
					cAux.literales = numVars;

					if (Form10->Excitacion->Cells[Sistema.DevolverNumCarEnt() + (5*Rango) - i - 1][j+1] == '1')
		                                simp->AnyadirMint(cAux);
					else if(Form10->Excitacion->Cells[Sistema.DevolverNumCarEnt() + (5*Rango) - i - 1][j+1] == 'X')
		                                simp->AnyadirTI(cAux);
				}
				simp->Simplificar();

                                for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
		                {
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}

                		delete simp;
                                listFunciones.push_back(listCubos);
		        }

                        //Variables Salida
               		for(int i = 0; i < Sistema.DevolverNumCarSal(); i++)
			{
                        	// Variable Vars[5 + Sistema.DevolverNumCarSal() - i - 1]
	                 	list<string> listCubos;
                                listCubos.push_back("c");
                                listCubos.push_back(Vars[5 + Sistema.DevolverNumCarSal() - i - 1].c_str());

				rdSimplificador *simp;
			        simp = new rdSimplificador(numVars);
		        	// 0 --> Obtención de IPs por el método Q-M
			        simp->SetObtenedor(0);
			        // 0 --> Seleccion de IPs por método recursivo sesgado
				simp->SetSelector(0);
				for(int j = 0; j < numCubos; j++)
				{
					CuboBool cAux=CuboBool(j);
					cAux.literales = numVars;

					if (Form10->Excitacion->Cells[Sistema.DevolverNumCarEnt() + (5*Rango) + i][j+1] == '1')
		                                simp->AnyadirMint(cAux);
					else if(Form10->Excitacion->Cells[Sistema.DevolverNumCarEnt() + (5*Rango) + i][j+1] == 'X')
		                                simp->AnyadirTI(cAux);
				}
				simp->Simplificar();

                                for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
		                {
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}

                		delete simp;
                                listFunciones.push_back(listCubos);
		        }

		}


			Device dev("GAL22V10", 24, 5828, 44, GAL22V10_PLCC);
			Jedec jedec(listFunciones, dev, entradas, SaveDialog2->FileName.SubString(1,SaveDialog2->FileName.Length()-4).c_str());
			if(jedec.GetCodigoFlagError())
				Application->MessageBox(jedec.GetTextoFlagError(), NULL);



		//SalvarPDL(SaveDialog2->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::ExporttoWeblabVHDL1Click(TObject *Sender)
{
        mWeblabMode = true;
        CrearCodigoVHDL();
        mWeblabMode = false;

        // Bug fix: Filter needs to be set before execution. ~lrg
	SaveDialog2->Filter=MENSAJE(msgFiltroVHDL);

	if(SaveDialog2->Execute())
	{
		SalvarPDL(SaveDialog2->FileName);
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1Boole2::StartWeblabFPGAIClick(
      TObject *Sender)
{
        ShellExecute(NULL, "open", "https://www.weblab.deusto.es/weblab/client/#page=experiment&exp.category=FPGA%20experiments&exp.name=ud-fpga", NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::ExportToWeblabInternalClick(TObject *Sender)
{
        mWeblabMode = true;
        mWeblabClockDirective = "@@@CLOCK:INTERNAL@@@";
        CrearCodigoVHDL();
        mWeblabClockDirective = "";
        mWeblabMode = false;

        // Bug fix: Filter needs to be set before execution. ~lrg
	SaveDialog2->Filter=MENSAJE(msgFiltroVHDL);

	if(SaveDialog2->Execute())
	{
		SalvarPDL(SaveDialog2->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::ExportToWeblabWeblabClick(TObject *Sender)
{
        mWeblabMode = true;
        mWeblabClockDirective = "@@@CLOCK:WEBLAB@@@";
        CrearCodigoVHDL();
        mWeblabClockDirective = "";
        mWeblabMode = false;

        // Bug fix: Filter needs to be set before execution. ~lrg
	SaveDialog2->Filter=MENSAJE(msgFiltroVHDL);

	if(SaveDialog2->Execute())
	{
		SalvarPDL(SaveDialog2->FileName);
	}        
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::ExportToWeblabSwitchClick(TObject *Sender)
{
        mWeblabMode = true;
        mWeblabClockDirective = "@@@CLOCK:SWITCH@@@";
        CrearCodigoVHDL();
        mWeblabClockDirective = "";
        mWeblabMode = false;

        // Bug fix: Filter needs to be set before execution. ~lrg
	SaveDialog2->Filter=MENSAJE(msgFiltroVHDL);

	if(SaveDialog2->Execute())
	{
		SalvarPDL(SaveDialog2->FileName);
	}        
}
//---------------------------------------------------------------------------

void __fastcall TForm1Boole2::ExportToWeblabButtonClick(
      TObject *Sender)
{
        mWeblabMode = true;
        mWeblabClockDirective = "@@@CLOCK:BUTTON@@@";
        CrearCodigoVHDL();
        mWeblabClockDirective = "";
        mWeblabMode = false;

        // Bug fix: Filter needs to be set before execution. ~lrg
	SaveDialog2->Filter=MENSAJE(msgFiltroVHDL);

	if(SaveDialog2->Execute())
	{
		SalvarPDL(SaveDialog2->FileName);
	}
}
//---------------------------------------------------------------------------

