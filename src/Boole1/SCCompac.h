/*$T boole/Boole1/SCCompac.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef SCCompacH
#define SCCompacH
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
#include <vcl/Buttons.hpp>
#include <ExtCtrls.hpp>
class TSCFormasCompactas : public TForm
{
__published:	// IDE-managed Components
	TGroupBox		*Funciones;
	TLabel			*Funcion;
	TLabel			*X;
	TScrollBar		*ScrollBar1;
	TRadioButton	*Disyuntivo;
	TRadioButton	*Conjuntivo;
	TEdit			*Edit1;
	TEdit			*Edit2;
	TStringGrid		*StringGrid1;
	TStringGrid		*StringGrid2;
	TLabel			*Label1;
	TButton			*Button1;
	TBitBtn			*BitBtn1;
	TBitBtn			*BitBtn2;
	TBitBtn			*BitBtn3;
	TBitBtn			*BitBtn4;
	TLabel			*Label2;
	TBitBtn			*Visualizar;
	TPanel			*Panel1;
	void __fastcall SalirClick(TObject *Sender);

	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);

	void __fastcall FormShow(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall StringGrid1DblClick(TObject *Sender);

	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall StringGrid2Click(TObject *Sender);
	void __fastcall StringGrid2DblClick(TObject *Sender);
	void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
	void __fastcall EvaluarClick(TObject *Sender);

	void __fastcall BorrarClick(TObject *Sender);
	void __fastcall StringGrid1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StringGrid2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

	void __fastcall StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall StringGrid2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall StringGrid2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);
	void __fastcall VisualizarClick(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);

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
	__fastcall		TSCFormasCompactas(TComponent *Owner);
};
extern TSCFormasCompactas	*SCFormasCompactas;
#endif
