/*$T boole/Boole2/Unit5.cpp GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "V_Boole2.h"
#include "Unit5.h"
#pragma resource "*.dfm"
TForm5	*Form5;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TForm5::TForm5(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm5::Button1Click(TObject *Sender)
{
	Form1Boole2->Enabled = True;
	Form1Boole2->SetFocus();
	Form1Boole2->Deseleccionar();
	Edit1->Text = "";
	Form5->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm5::Button2Click(TObject *Sender)
{
	if(Edit1->GetTextLen() == Edit1->MaxLength)
	{
		if(Edit2->GetTextLen() == Edit2->MaxLength)
		{
			Form1Boole2->PonEtTransicionMealy(Form5->Edit1->Text, Form5->Edit2->Text);
			Form1Boole2->Enabled = True;
			Form1Boole2->SetFocus();
			Form5->Hide();
		}
		else
		{
			ActiveControl = Edit2;
			Edit2->SelStart = Edit2->GetTextLen();
		}
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
void __fastcall TForm5::FormShow(TObject *Sender)
{
	ActiveControl = Edit1;
	Edit1->MaxLength = Form1Boole2->DameNumCarEnt();
	Edit2->MaxLength = Form1Boole2->DameNumCarSal();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm5::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
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
void __fastcall TForm5::Edit2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
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
void __fastcall TForm5::Edit1Change(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~*/
	AnsiString	Frase = "";
	int			i, tam;
	/*~~~~~~~~~~~~~~~~~~~*/

	tam = Edit1->GetTextLen();
	for(i = 1; i <= tam; i++)
	{
		if((Edit1->Text[i] == '1') || (Edit1->Text[i] == '0') || (Edit1->Text[i] == 'X'))
		{
			Frase += Edit1->Text[i];
		}
	}

	Edit1->Text = Frase;
	tam = Edit1->GetTextLen();
	Edit1->SelStart = tam;

	// si se completa continua en el segundo edit
	if(tam == Form1Boole2->DameNumCarEnt())
	{
		ActiveControl = Edit2;
		Edit2->SelStart = Edit2->GetTextLen();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm5::Edit2Change(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~*/
	AnsiString	Frase = "";
	int			i, tam;
	/*~~~~~~~~~~~~~~~~~~~*/

	tam = Edit2->GetTextLen();
	for(i = 1; i <= tam; i++)
	{
		if((Edit2->Text[i] == '1') || (Edit2->Text[i] == '0') || (Edit2->Text[i] == 'X'))
		{
			Frase += Edit2->Text[i];
		}
	}

	Edit2->Text = Frase;
	tam = Edit2->GetTextLen();
	Edit2->SelStart = tam;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm5::FormHide(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = true;
}
