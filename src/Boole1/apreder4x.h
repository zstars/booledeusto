/*$T boole/Boole1/apreder4x.h GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef apreder4xH
#define apreder4xH
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include "Grids.hpp"
#include <vcl/ExtCtrls.hpp>
#include <vcl/Buttons.hpp>
class Tapreder4 : public TForm
{
__published:	// IDE-managed Components
	TLabel			*Label4;
	TLabel			*Label6;
	TScrollBar		*ScrollBar1;
	TGroupBox		*Funciones;
	TLabel			*Funcion;
	TLabel			*X;
	TLabel			*Label1;
	TLabel			*Label2;
	TLabel			*Label3;
	TLabel			*Label5;
	TRadioButton	*Disyuntivo;
	TRadioButton	*Conjuntivo;
	TStringGrid		*StringGrid1;
	TStringGrid		*StringGrid2;
	TStringGrid		*StringGridVK;
	TPanel			*Panel1;
	TPanel			*Panel3;
	TPanel			*Panel5;
	TStringGrid		*StringGrid3;
	TBitBtn			*EvaluarExp;
	TBitBtn			*SalirExp;
	TBitBtn			*BorrarExp;
	TStringGrid		*StringGrid4;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:	// User declarations

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public: // User declarations
	__fastcall		Tapreder4(TComponent *Owner);
};
extern Tapreder4	*apreder4;
#endif
