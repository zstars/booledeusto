/*$T boole/Boole2/Unit6.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit6H
#define Unit6H
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include <vcl/ExtCtrls.hpp>
#include <vcl/ComCtrls.hpp>
#include <vcl/Buttons.hpp>
#include <vcl/Dialogs.hpp>
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TPanel			*Panel1;
	TTrackBar		*Bar;
	TImage			*Image1;
	TButton			*Button1;
	TButton			*Button2;
	TSpeedButton	*SpeedButton1;
	TShape			*Sel;
	TSpeedButton	*SpeedButton2;
	TShape			*Mov;
	TLabel			*Label1;
	TLabel			*Label2;
	TColorDialog	*ColorDialog1;
	TShape			*Fon;
	TLabel			*Label3;
	TSpeedButton	*SpeedButton3;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BarChange(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
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
	__fastcall		TForm6(TComponent *Owner);
};
extern TForm6	*Form6;
#endif
