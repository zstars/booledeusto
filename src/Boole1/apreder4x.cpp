/*$T boole/Boole1/apreder4x.cpp GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "apreder4x.h"
#include "aprender4x.h"
#include "DinArray.h";
#include "app.h";
#include "Libreria.h";
#include "NuevoSC.h";
#include "Unit1.h"
#include "ctype.h"

extern DinArray Tabla;

DinArray		Tabla2 = DinArray();
#pragma link "Grids"
#pragma resource "*.dfm"
Tapreder4		*apreder4;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall Tapreder4::Tapreder4(TComponent *Owner) :
	TForm(Owner)
{
}
