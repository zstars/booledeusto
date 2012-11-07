/*$T boole/Boole2/Unit15.cpp GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/printers.hpp>
#include <vcl/vcl.h>
#pragma hdrstop
#include "Unit15.h"
#include "V_Boole2.h"
#pragma resource "*.dfm"
TForm15 *Form15;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TForm15::TForm15(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm15::Button1Click(TObject *Sender)
{
	if(CheckBox1->Checked == true)
	{
		Form1Boole2->ImprimirAUT();
	}

	if(CheckBox2->Checked == true)
	{
		Form1Boole2->ImprimirPLD();
	}

	if(CheckBox3->Checked == true)
	{
		Form1Boole2->ImprimirAutomata();
	}

	if(CheckBox4->Checked == true)
	{
		Form1Boole2->ImprimirResultados();
	}

	Form1Boole2->Timer1->Enabled = true;
	Form1Boole2->Enabled = True;
	Form1Boole2->SetFocus();
	Form15->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm15::Button2Click(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = true;
	Form1Boole2->Enabled = True;
	Form1Boole2->SetFocus();
	Form15->Hide();
}
