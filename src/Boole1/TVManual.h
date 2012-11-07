/*$T boole/Boole1/TVManual.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef TVManualH
#define TVManualH
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
#include <vcl/ExtCtrls.hpp>
#include "Grids.hpp"
#include <vcl/Buttons.hpp>
class TTablaVerdadManual : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup		*Completar;
	TGroupBox		*TablaVerdad;
	TStringGrid		*StringGrid1;
	TStringGrid		*StringGrid2;
	TBitBtn			*BitBtn1;
	TBitBtn			*BitBtn2;
	TBitBtn			*BitBtn3;
	TBitBtn			*BitBtn4;
	TBitBtn			*BitBtn5;
	TRadioButton	*RadioButton1;
	TRadioButton	*RadioButton2;
	TRadioButton	*RadioButton3;
	void __fastcall EvaluarClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall Button1Click(TObject *Sender);

	void __fastcall SalirClick(TObject *Sender);
	void __fastcall StringGrid1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

	void __fastcall StringGrid2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall StringGrid1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StringGrid2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StringGrid1TopLeftChanged(TObject *Sender);
	void __fastcall StringGrid2TopLeftChanged(TObject *Sender);

	void __fastcall CompletarUnosClick(TObject *Sender);
	void __fastcall CompletarCerosClick(TObject *Sender);
	void __fastcall CompletarCondLibresClick(TObject *Sender);
	void __fastcall BorrarClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);

	void __fastcall BitBtn5Click(TObject *Sender);

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
	__fastcall		TTablaVerdadManual(TComponent *Owner);
};
extern TTablaVerdadManual	*TablaVerdadManual;
#endif
