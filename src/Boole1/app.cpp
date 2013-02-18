/*$T boole/Boole1/app.cpp GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "DinArray.h";
#include "NuevoSC.h";
#include "app.h"
#include "uKarnaugh.h"

extern DinArray Tabla;
#pragma resource "*.dfm"
Tap				*ap;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall Tap::Tap(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Tap::Button1Click(TObject *Sender)
{
	        AnsiString cadena;
        	cadena = SistemaCombinacionalNuevo->NEntradas->Text;
        	long numVars = atol(cadena.c_str());
                fKarnaugh->setFormato(FORMATO_SOP);
                fKarnaugh->setNumVars(numVars);
                fKarnaugh->setModo(MODO_APRENDIZAJE_EXPR);


        	fKarnaugh->ShowModal();
                this->Close();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Tap::Button2Click(TObject *Sender)
{
	        AnsiString cadena;
        	cadena = SistemaCombinacionalNuevo->NEntradas->Text;
        	long numVars = atol(cadena.c_str());
                fKarnaugh->setFormato(FORMATO_POS);
                fKarnaugh->setNumVars(numVars);
                fKarnaugh->setModo(MODO_APRENDIZAJE_EXPR);


        	fKarnaugh->ShowModal();
                this->Close();
}
