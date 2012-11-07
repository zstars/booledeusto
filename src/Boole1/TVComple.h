/*$T boole/Boole1/TVComple.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef TVCompleH
#define TVCompleH
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
class TTablaVerdadCompleta : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup		*CompletarTabla;
	TStringGrid		*StringGridEntrada;
	TStringGrid		*StringGridSalida;
	TLabel			*Label1;
	TLabel			*Label2;
	TButton			*libres;
	TButton			*ceros;
	TButton			*unos;
	TBitBtn			*BitBtn1;
	TBitBtn			*BitBtn2;
	TBitBtn			*BitBtn3;
	void __fastcall SalirClick(TObject *Sender);

	void __fastcall FormShow(TObject *Sender);

	void __fastcall EvaluarClick(TObject *Sender);
	void __fastcall BorrarClick(TObject *Sender);

	void __fastcall libresClick(TObject *Sender);
	void __fastcall cerosClick(TObject *Sender);
	void __fastcall unosClick(TObject *Sender);

	void __fastcall StringGridSalidaTopLeftChanged(TObject *Sender);
	void __fastcall StringGridEntradaTopLeftChanged(TObject *Sender);

	void __fastcall StringGridEntradaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall StringGridSalidaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall StringGridSalidaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);

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
	__fastcall		TTablaVerdadCompleta(TComponent *Owner);
};
extern TTablaVerdadCompleta *TablaVerdadCompleta;
#endif
