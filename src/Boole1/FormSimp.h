/*$T boole/Boole1/FormSimp.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef FormSimpH
#define FormSimpH
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


class TExpresionSimp : public TForm
{
__published:	// IDE-managed Components
	TStringGrid		*StringGrid1;
	TLabel			*Label1;
	TLabel			*Funcion;
	TScrollBar		*ScrollBar1;
	TRadioButton	*POS;
	TMemo			*Memo1;
	TBitBtn			*BitBtn1;
	TButton			*Button1;
	TRadioButton	*nnor;
	TBitBtn			*Visualizar;
	TButton *btKarnaugh;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SalirClick(TObject *Sender);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall VisualizarClick(TObject *Sender);
	void __fastcall calcularSimplificada(TObject *Sender);
	void __fastcall btKarnaughClick(TObject *Sender);

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
	__fastcall		TExpresionSimp(TComponent *Owner);
};
extern TExpresionSimp	*ExpresionSimp;
#endif
