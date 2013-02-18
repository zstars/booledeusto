/*$T boole/Boole1/NandNor.cpp GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "NandNor.h"
#include "SCCompac.h"
#include "DinArray.h"
#include "Libreria.h"
#include "FormSimp.h"

// Modificado.
#include "Circuito/V_Circuito.h"
#include "limpiador.h"
#include "mensajes.inc"
// Modificado.
#include <vector>
using namespace std;
extern DinArray Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString LimpiarEcuacion(AnsiString &s)
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	aux = s;
	/*~~~~~~~~~~~~~~~~*/

	for(int i = 1; i <= aux.Length(); i++)
	{
		if(aux[i] == '-') aux[i] = '~';
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	limpiador	l = limpiador(string(aux.c_str()));
	string		limpiado = l.limpiar();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// s = aux;
	return AnsiString(limpiado.c_str());
}

TNANDyNOR	*NANDyNOR;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TNANDyNOR::TNANDyNOR(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::FMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	F->Hint = Tabla.LeerSalida(ScrollBar1->Position - 1);
	F->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(ScrollBar1->Position - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::ScrollBar1Change(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	extern vector<bool> ocultarNANDNOR;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// ajustamos el grid a la posición adecuada
	Funcion->Caption = ScrollBar1->Position;

	if(ocultarNANDNOR[ScrollBar1->Position - 1])
	{
		VisualizarNand->Visible = false;
		VisualizarNor->Visible = false;
	}
	else
	{
		VisualizarNand->Visible = true;
		VisualizarNor->Visible = true;
	}

	//
	// Modificado.
	// int scrollPos=ScrollBar1->Position - 1;
	// StringGrid->Cells[scrollPos][0]=corregirEcuacion
	// (StringGrid->Cells[scrollPos][0]);
	// StringGrid->Cells[scrollPos][2]=corregirEcuacion
	// (StringGrid->Cells[scrollPos][2]);
	// Modificado.
	// colocamos los valores del Grid (de la función) en las cajas de texto
	//
	Edit1->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][0]);
	Edit2->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][2]);
	Edit3->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][1]);
	Edit4->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][3]);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::FormShow(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	extern vector<bool> ocultarNANDNOR;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ExpresionSimp->nnor->Checked = true;
	ScrollBar1->Position = 1;

	if(ocultarNANDNOR[ScrollBar1->Position - 1])
	{
		VisualizarNand->Visible = false;
		VisualizarNor->Visible = false;
	}
	else
	{
		VisualizarNand->Visible = true;
		VisualizarNor->Visible = true;
	}

	//
	// Modificado.
	// StringGrid->Cells[0][0]=corregirEcuacion (StringGrid->Cells[0][0]);
	// StringGrid->Cells[0][2]=corregirEcuacion (StringGrid->Cells[0][2]);
	// Modificado.
	// introducimos en las cajas de texto las expresiones de la función 1
	// Edit1->Text = StringGrid->Cells[0][0]; Edit2->Text = StringGrid->Cells[0][2];
	// Edit3->Text = StringGrid->Cells[0][1]; Edit4->Text = StringGrid->Cells[0][3];
	//
	Edit1->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][0]);
	Edit2->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][2]);
	Edit3->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][1]);
	Edit4->Text = LimpiarEcuacion(StringGrid->Cells[ScrollBar1->Position - 1][3]);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::Button1Click(TObject *Sender)
{
	SCFormasCompactas->Show();
	NANDyNOR->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::BitBtn1Click(TObject *Sender)
{
	if(Exp->Checked)
		ExpresionSimp->Show();
	else
		SCFormasCompactas->Show();
	NANDyNOR->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::VisualizarNandClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// Modificado.
	AnsiString	salida = Tabla.LeerSalida(ScrollBar1->Position - 1);
	AnsiString	ecuacion = LimpiarEcuacion(NANDyNOR->StringGrid->Cells[ScrollBar1->Position - 1][0]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	FormR->Titulo = MENSAJE(msgCircuitoNand);

	FormR->ecuacion->Text = salida + "=" + ecuacion;
	FormR->tipoCircuito = false;	// Circuito Combinacional.
	FormR->ShowModal();

	// Modificado.
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::VisualizarNorClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// Modificado.
	AnsiString	salida = Tabla.LeerSalida(ScrollBar1->Position - 1);
	AnsiString	ecuacion = LimpiarEcuacion(NANDyNOR->StringGrid->Cells[ScrollBar1->Position - 1][2]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	FormR->Titulo = MENSAJE(msgCircuitoNor);

	FormR->ecuacion->Text = salida + "=" + ecuacion;
	FormR->tipoCircuito = false;	// Circuito Combinacional.
	FormR->ShowModal();

	// Modificado.
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString TNANDyNOR::corregirEcuacion(AnsiString ecuacion)
{
	if(ecuacion.Length() > 1)
	{
		if(ecuacion[1] == '~' && ecuacion[2] == '~')
		{
			ecuacion = ecuacion.Insert("(", 2);
			ecuacion = ecuacion + ")";
			StringGrid->Cells[0][0] = ecuacion;
		}
	}

	return ecuacion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TNANDyNOR::FormClose(TObject *Sender, TCloseAction &Action)
{
	ExpresionSimp->nnor->Checked = false;
}
