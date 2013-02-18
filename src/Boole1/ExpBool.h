/*$T boole/Boole1/ExpBool.h GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef ExpBoolH
#define ExpBoolH
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include "Grids.hpp"
#include <vcl/Buttons.hpp>
class TExprBooleana : public TForm
{
__published:	// IDE-managed Components
	TScrollBar		*ScrollBar1;
	TLabel			*Label1;
	TStringGrid		*StringGrid1;
	TLabel			*Funcion;
	TBitBtn			*EvaluarExp;
	TBitBtn			*BorrarExp;
	TBitBtn			*SalirExp;
	TBitBtn			*BitBtn4;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BorrarClick(TObject *Sender);
	void __fastcall SalirClick(TObject *Sender);
	void __fastcall StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall EvaluarClick(TObject *Sender);

	void __fastcall EvaluarExpClick(TObject *Sender);
	void __fastcall BorrarExpClick(TObject *Sender);
	void __fastcall SalirExpClick(TObject *Sender);
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
	__fastcall		TExprBooleana(TComponent *Owner);
};
extern TExprBooleana	*ExprBooleana;
#endif
