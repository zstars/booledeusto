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
TNewDiagramForm	*NewDiagramForm;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PonVar(int Ent, int Sal, boolean st)
// st sirve para saber si debemos poner lo que hay en el array de VArs o dejar lo que hay en los edit st=false=DEJAR LO DE LOS EDIT
{
	if(Ent >= 1)
	{
		if(st) NewDiagramForm->Entrada1->Text = Form1Boole2->DevuelveVar(0);
	}

	if(Ent >= 2)
	{
		NewDiagramForm->Entrada2->Enabled = true;
		if(st) NewDiagramForm->Entrada2->Text = Form1Boole2->DevuelveVar(1);
	}
	else
		NewDiagramForm->Entrada2->Enabled = false;
	if(Ent >= 3)
	{
		NewDiagramForm->Entrada3->Enabled = true;
		if(st) NewDiagramForm->Entrada3->Text = Form1Boole2->DevuelveVar(2);
	}
	else
		NewDiagramForm->Entrada3->Enabled = false;
	if(Ent >= 4)
	{
		NewDiagramForm->Entrada4->Enabled = true;
		if(st) NewDiagramForm->Entrada4->Text = Form1Boole2->DevuelveVar(3);
	}
	else
		NewDiagramForm->Entrada4->Enabled = false;
	if(Ent == 5)
	{
		NewDiagramForm->Entrada5->Enabled = true;
		if(st) NewDiagramForm->Entrada5->Text = Form1Boole2->DevuelveVar(4);
	}
	else
		NewDiagramForm->Entrada5->Enabled = false;

	if(Sal >= 1)
	{
		if(st) NewDiagramForm->Salida1->Text = Form1Boole2->DevuelveVar(5);
	}

	if(Sal >= 2)
	{
		NewDiagramForm->Salida2->Enabled = true;
		if(st) NewDiagramForm->Salida2->Text = Form1Boole2->DevuelveVar(6);
	}
	else
		NewDiagramForm->Salida2->Enabled = false;
	if(Sal >= 3)
	{
		NewDiagramForm->Salida3->Enabled = true;
		if(st) NewDiagramForm->Salida3->Text = Form1Boole2->DevuelveVar(7);
	}
	else
		NewDiagramForm->Salida3->Enabled = false;
	if(Sal >= 4)
	{
		NewDiagramForm->Salida4->Enabled = true;
		if(st) NewDiagramForm->Salida4->Text = Form1Boole2->DevuelveVar(8);
	}
	else
		NewDiagramForm->Salida4->Enabled = false;
	if(Sal == 5)
	{
		NewDiagramForm->Salida5->Enabled = true;
		if(st) NewDiagramForm->Salida5->Text = Form1Boole2->DevuelveVar(9);
	}
	else
		NewDiagramForm->Salida5->Enabled = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TNewDiagramForm::TNewDiagramForm(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNewDiagramForm::Button1Click(TObject *Sender)
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
	Form1Boole2->PonVar(0, NewDiagramForm->Entrada1->Text);
	Form1Boole2->PonVar(1, NewDiagramForm->Entrada2->Text);
	Form1Boole2->PonVar(2, NewDiagramForm->Entrada3->Text);
	Form1Boole2->PonVar(3, NewDiagramForm->Entrada4->Text);
	Form1Boole2->PonVar(4, NewDiagramForm->Entrada5->Text);
	Form1Boole2->PonVar(5, NewDiagramForm->Salida1->Text);
	Form1Boole2->PonVar(6, NewDiagramForm->Salida2->Text);
	Form1Boole2->PonVar(7, NewDiagramForm->Salida3->Text);
	Form1Boole2->PonVar(8, NewDiagramForm->Salida4->Text);
	Form1Boole2->PonVar(9, NewDiagramForm->Salida5->Text);
	Form1Boole2->Enabled = true;

	// Form1Boole2->SetFocus();
	NewDiagramForm->Hide();
	Form1Boole2->Tablero->Visible = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNewDiagramForm::Button2Click(TObject *Sender)
{
	Form1Boole2->Enabled = True;
	Form1Boole2->SetFocus();
	NewDiagramForm->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNewDiagramForm::FormShow(TObject *Sender)
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
void __fastcall TNewDiagramForm::ComboBox1Change(TObject *Sender)
{
	ComboBox1->Text = "Moore";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNewDiagramForm::ComboBox2Change(TObject *Sender)
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
void __fastcall TNewDiagramForm::ComboBox3Change(TObject *Sender)
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
void __fastcall TNewDiagramForm::FormActivate(TObject *Sender)
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
void __fastcall TNewDiagramForm::FormHide(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = true;
}
