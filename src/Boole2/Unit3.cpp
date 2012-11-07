/*$T boole/Boole2/Unit3.cpp GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "Unit3.h"
#include "V_Boole2.h"
#pragma resource "*.dfm"
TForm3	*Form3;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TForm3::TForm3(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm3::Button1Click(TObject *Sender)
{
	Form1Boole2->Enabled = True;
	Form1Boole2->SetFocus();
	Form1Boole2->Deseleccionar();
	Edit1->Text = "";
	Form3->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm3::Button2Click(TObject *Sender)
{
	if(Edit1->GetTextLen() > 0)
	{
		Form1Boole2->PonEtEstadoMealy(Form3->Edit1->Text);
		Form1Boole2->Enabled = True;
		Form1Boole2->SetFocus();
		Form3->Hide();
	}
	else
	{
		ActiveControl = Edit1;
		Edit1->SelStart = Edit1->GetTextLen();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm3::FormShow(TObject *Sender)
{
	Edit1->Text = "";

	// Edit1->MaxLength=Form1Boole2->DameNumCar();
	ActiveControl = Edit1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm3::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13)
	{
		Button2Click(Sender);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm3::FormHide(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = true;
}
