/*$T boole/Boole2/Unit6.cpp GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "Unit6.h"
#include "V_Boole2.h"
#pragma resource "*.dfm"
TForm6	*Form6;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TForm6::TForm6(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::FormShow(TObject *Sender)
{
	Image1->Canvas->Brush->Style = bsSolid;
	Image1->Canvas->Pen->Color = clWhite;
	Image1->Canvas->Rectangle(0, 0, 120, 120);
	Image1->Canvas->Pen->Color = clBlack;
	Bar->Position = (Form1Boole2->DameRadio() - 25);
	Image1->Refresh();
	Image1->Canvas->Ellipse
		(
			Image1->Width / 2 - (Form1Boole2->DameRadio()),
			Image1->Height / 2 - (Form1Boole2->DameRadio()),
			Image1->Width / 2 + (Form1Boole2->DameRadio()),
			Image1->Height / 2 + (Form1Boole2->DameRadio())
		);
	Sel->Brush->Color = TColor(Form1Boole2->DameObjSel());
	Mov->Brush->Color = TColor(Form1Boole2->DameObjMov());
	Fon->Brush->Color = TColor(Form1Boole2->DameColFon());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::BarChange(TObject *Sender)
{
	Image1->Canvas->Brush->Style = bsSolid;
	Image1->Canvas->Pen->Color = clWhite;
	Image1->Canvas->Rectangle(0, 0, 120, 120);
	Image1->Canvas->Pen->Color = clBlack;
	Image1->Canvas->Ellipse
		(
			Image1->Width / 2 - (Bar->Position + 25),
			Image1->Height / 2 - (Bar->Position + 25),
			Image1->Width / 2 + (Bar->Position + 25),
			Image1->Height / 2 + (Bar->Position + 25)
		);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::Button2Click(TObject *Sender)
{
	Form1Boole2->PonRadio(Bar->Position + 25);
	Form1Boole2->PonObjSel(Sel->Brush->Color);
	Form1Boole2->PonObjMov(Mov->Brush->Color);
	Form1Boole2->PonColFon(Fon->Brush->Color);
	Form1Boole2->Enabled = true;
	Form1Boole2->SetFocus();
	Form6->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::Button1Click(TObject *Sender)
{
	Form1Boole2->Enabled = true;
	Form1Boole2->SetFocus();
	Form6->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::SpeedButton1Click(TObject *Sender)
{
	ColorDialog1->Color = Sel->Brush->Color;
	ColorDialog1->Execute();
	Sel->Brush->Color = ColorDialog1->Color;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::SpeedButton2Click(TObject *Sender)
{
	ColorDialog1->Color = Mov->Brush->Color;
	ColorDialog1->Execute();
	Mov->Brush->Color = ColorDialog1->Color;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::SpeedButton3Click(TObject *Sender)
{
	ColorDialog1->Color = Fon->Brush->Color;
	ColorDialog1->Execute();
	Fon->Brush->Color = ColorDialog1->Color;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm6::FormHide(TObject *Sender)
{
	Form1Boole2->Timer1->Enabled = true;
}
