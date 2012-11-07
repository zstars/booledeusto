/*$T boole/Boole1/NandNor.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef NandNorH
#define NandNorH
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
class TNANDyNOR : public TForm
{
__published:	// IDE-managed Components
	TLabel			*Label1;
	TLabel			*Label2;
	TScrollBar		*ScrollBar1;
	TLabel			*F;
	TLabel			*Funcion;
	TStringGrid		*StringGrid;
	TEdit			*Edit1;
	TEdit			*Edit2;
	TLabel			*Label3;
	TLabel			*Label4;
	TEdit			*Edit3;
	TEdit			*Edit4;
	TLabel			*Label5;
	TBitBtn			*BitBtn1;
	TRadioButton	*Exp;
	TBitBtn			*VisualizarNand;
	TBitBtn			*VisualizarNor;
	void __fastcall FMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);

	void __fastcall VisualizarNandClick(TObject *Sender);
	void __fastcall VisualizarNorClick(TObject *Sender);

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

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
	__fastcall		TNANDyNOR(TComponent *Owner);
	AnsiString		corregirEcuacion(AnsiString e);
};
extern TNANDyNOR	*NANDyNOR;
#endif
