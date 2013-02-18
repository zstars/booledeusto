/*$T boole/Boole1/aprender3x.h GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef aprender3xH
#define aprender3xH
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include "Grids.hpp"
#include <vcl/ExtCtrls.hpp>
#include <vcl/Buttons.hpp>
class Taprender3 : public TForm
{
__published:	// IDE-managed Components
	TScrollBar		*ScrollBar1;
	TGroupBox		*Funciones;
	TLabel			*Funcion;
	TLabel			*X;
	TLabel			*Label1;
	TRadioButton	*Disyuntivo;
	TRadioButton	*Conjuntivo;
	TStringGrid		*StringGrid1;
	TStringGrid		*StringGrid2;
	TLabel			*Label2;
	TLabel			*Label3;
	TLabel			*Label5;
	TStringGrid		*StringGridVK;
	TPanel			*Panel1;
	TPanel			*Panel3;
	TPanel			*Panel5;
	TLabel			*Label4;
	TLabel			*Label6;
	TStringGrid		*StringGrid3;
	TBitBtn			*EvaluarExp;
	TBitBtn			*SalirExp;
	TBitBtn			*BorrarExp;
	TStringGrid		*StringGrid4;
	TBitBtn			*BitBtn4;
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall StringGrid3KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall BorrarExpClick(TObject *Sender);
	void __fastcall SalirExpClick(TObject *Sender);
	void __fastcall EvaluarExpClick(TObject *Sender);

	void __fastcall BitBtn4Click(TObject *Sender);

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
	__fastcall		Taprender3(TComponent *Owner);
};
extern Taprender3	*aprender3;
#endif
