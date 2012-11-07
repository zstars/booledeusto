/*$T boole/Boole2/Unit4.cpp GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "Unit4.h"
#include "V_Boole2.h"
#include "SistemaSecuencial.h"
#include "mensajes.inc"
#pragma resource "*.dfm"
TForm4	*Form4;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PonVar(int Ent, int Sal, boolean st)
// st sirve para saber si debemos poner lo que hay en el array de VArs o dejar lo que hay en los edit st=false=DEJAR LO DE LOS EDIT
{
	if(Ent >= 1)
	{
		if(st) Form4->Entrada1->Text = Form1Boole2->DevuelveVar(0);
	}

	if(Ent >= 2)
	{
		Form4->Entrada2->Enabled = true;
		if(st) Form4->Entrada2->Text = Form1Boole2->DevuelveVar(1);
	}
	else
		Form4->Entrada2->Enabled = false;
	if(Ent >= 3)
	{
		Form4->Entrada3->Enabled = true;
		if(st) Form4->Entrada3->Text = Form1Boole2->DevuelveVar(2);
	}
	else
		Form4->Entrada3->Enabled = false;
	if(Ent >= 4)
	{
		Form4->Entrada4->Enabled = true;
		if(st) Form4->Entrada4->Text = Form1Boole2->DevuelveVar(3);
	}
	else
		Form4->Entrada4->Enabled = false;
	if(Ent == 5)
	{
		Form4->Entrada5->Enabled = true;
		if(st) Form4->Entrada5->Text = Form1Boole2->DevuelveVar(4);
	}
	else
		Form4->Entrada5->Enabled = false;

	if(Sal >= 1)
	{
		if(st) Form4->Salida1->Text = Form1Boole2->DevuelveVar(5);
	}

	if(Sal >= 2)
	{
		Form4->Salida2->Enabled = true;
		if(st) Form4->Salida2->Text = Form1Boole2->DevuelveVar(6);
	}
	else
		Form4->Salida2->Enabled = false;
	if(Sal >= 3)
	{
		Form4->Salida3->Enabled = true;
		if(st) Form4->Salida3->Text = Form1Boole2->DevuelveVar(7);
	}
	else
		Form4->Salida3->Enabled = false;
	if(Sal >= 4)
	{
		Form4->Salida4->Enabled = true;
		if(st) Form4->Salida4->Text = Form1Boole2->DevuelveVar(8);
	}
	else
		Form4->Salida4->Enabled = false;
	if(Sal == 5)
	{
		Form4->Salida5->Enabled = true;
		if(st) Form4->Salida5->Text = Form1Boole2->DevuelveVar(9);
	}
	else
		Form4->Salida5->Enabled = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TForm4::TForm4(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::Button1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~*/
	// los de mealy tienen 2 etiquetas en las flechas
	AnsiString	Titulo;
	/*~~~~~~~~~~~~~~~*/

	Form1Boole2->Nuevo();
	if(Edit1->Text == "")
	{
		Titulo = MENSAJE(msgSinTitulo);
                Sistema.Titulo = Titulo;
		Titulo += " (";
		Titulo += ComboBox1->Text;
		Titulo += ")";
		Form1Boole2->Caption = Titulo;
	}
	else
	{
		Titulo = Edit1->Text;
                Sistema.Titulo = Titulo;
		Titulo += " (";
		Titulo += ComboBox1->Text;
		Titulo += ")";
		Form1Boole2->Caption = Titulo;
	}

	if(ComboBox1->Text == "Moore")
	{
		Form1Boole2->PonerTipo(0);
	}
	else
	{
		Form1Boole2->PonerTipo(1);
	}

	Form1Boole2->PonerNumCarEnt(ComboBox2->Text.ToInt());
	Form1Boole2->PonerNumCarSal(ComboBox3->Text.ToInt());

	// Devolvemos los nombres de las varibles de entrada Salida
	Form1Boole2->PonVar(0, Form4->Entrada1->Text);
	Form1Boole2->PonVar(1, Form4->Entrada2->Text);
	Form1Boole2->PonVar(2, Form4->Entrada3->Text);
	Form1Boole2->PonVar(3, Form4->Entrada4->Text);
	Form1Boole2->PonVar(4, Form4->Entrada5->Text);
	Form1Boole2->PonVar(5, Form4->Salida1->Text);
	Form1Boole2->PonVar(6, Form4->Salida2->Text);
	Form1Boole2->PonVar(7, Form4->Salida3->Text);
	Form1Boole2->PonVar(8, Form4->Salida4->Text);
	Form1Boole2->PonVar(9, Form4->Salida5->Text);
	Form1Boole2->Enabled = true;

	// Form1Boole2->SetFocus();
	Form4->Hide();
	Form1Boole2->Tablero->Visible = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::Button2Click(TObject *Sender)
{
	Form1Boole2->Enabled = True;
	Form1Boole2->SetFocus();
	Form4->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::FormShow(TObject *Sender)
{
	ComboBox2->Text = 1;	// Form1Boole2->DameNumCarEnt();
	ComboBox3->Text = 1;	// Form1Boole2->DameNumCarSal();
	ActiveControl = Button1;
	PonVar(1, 1, true);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::ComboBox1Change(TObject *Sender)
{
	ComboBox1->Text = "Moore";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::ComboBox2Change(TObject *Sender)
{
	if
	(
		(ComboBox2->Text != "5")
	&&	(ComboBox2->Text != "4")
	&&	(ComboBox2->Text != "3")
	&&	(ComboBox2->Text != "2")
	&&	(ComboBox2->Text != "1")
	)
	{
		ComboBox2->Text = "1";
	}

	PonVar(ComboBox2->Text.ToInt(), ComboBox3->Text.ToInt(), false);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::ComboBox3Change(TObject *Sender)
{
	if
	(
		(ComboBox3->Text != "5")
	&&	(ComboBox3->Text != "4")
	&&	(ComboBox3->Text != "3")
	&&	(ComboBox3->Text != "2")
	&&	(ComboBox3->Text != "1")
	)
	{
		ComboBox3->Text = "1";
	}

	PonVar(ComboBox2->Text.ToInt(), ComboBox3->Text.ToInt(), false);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::FormActivate(TObject *Sender)
{
	if(Form1Boole2->DarTipo() == 1)
	{
		ComboBox1->Text = "Mealy";
	}
	else
	{
		ComboBox1->Text = "Moore";
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm4::FormHide(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = true;
}
