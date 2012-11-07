/*$T boole/Boole1/Vkar6.h GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Vkar6H
#define Vkar6H
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
class TVK6 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid		*StringGridVK;
	TScrollBar		*ScrollBar1;
	TPanel			*Panel1;
	TPanel			*Panel2;
	TLabel			*Label1;
	TLabel			*Label2;
	TPanel			*Panel3;
	TLabel			*Label3;
	TPanel			*Panel4;
	TLabel			*Label4;
	TPanel			*Panel5;
	TPanel			*Panel6;
	TLabel			*Label5;
	TLabel			*Label6;
	TPanel			*Panel7;
	TLabel			*Label7;
	TPanel			*Panel8;
	TLabel			*Label8;
	TLabel			*FuncionLabel;
	TLabel			*Funcion;
	TRadioGroup		*CompletarTabla;
	TButton			*ceros;
	TButton			*libres;
	TButton			*unos;
	TBitBtn			*BitBtn1;
	TBitBtn			*BitBtn2;
	TBitBtn			*BitBtn3;
	void __fastcall StringGridVKMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall SalirClick(TObject *Sender);

	void __fastcall FormShow(TObject *Sender);

	void __fastcall Button2Click(TObject *Sender);

	void __fastcall FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FuncionLabelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ScrollBar1Change(TObject *Sender);

	void __fastcall StringGridVKKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall Button1Click(TObject *Sender);

	void __fastcall libresClick(TObject *Sender);
	void __fastcall cerosClick(TObject *Sender);
	void __fastcall unosClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);

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
	__fastcall		TVK6(TComponent *Owner);
};
extern TVK6 *VK6;
#endif
