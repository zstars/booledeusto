/*$T boole/Boole2/ayuda.cpp GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "ayuda.h"
#include "V_Boole2.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TfAyuda *fAyuda;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TfAyuda::TfAyuda(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TfAyuda::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form1Boole2->Enabled = true;
	Form1Boole2->SetFocus();
}
