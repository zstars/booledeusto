/*$T boole/Boole1/FormasN.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef FormasNH
#define FormasNH
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
class TFormasNormales : public TForm
{
__published:	// IDE-managed Components
	TGroupBox		*Funciones;
	TLabel			*Funcion;
	TLabel			*X;
	TLabel			*Label1;
	TRadioButton	*Disyuntivo;
	TRadioButton	*Conjuntivo;
	TScrollBar		*ScrollBar1;
	TStringGrid		*StringGrid1;
	TStringGrid		*StringGrid2;
	TBitBtn			*BitBtn1;
	TBitBtn			*BitBtn2;
	TBitBtn			*BitBtn3;
	void __fastcall FormShow(TObject *Sender);

	void __fastcall SalirClick(TObject *Sender);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall BorrarClick(TObject *Sender);
	void __fastcall Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

	void __fastcall StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall StringGrid2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EvaluarClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
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
	__fastcall		TFormasNormales(TComponent *Owner);
};
extern TFormasNormales	*FormasNormales;
#endif
