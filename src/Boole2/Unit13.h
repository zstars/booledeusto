/*$T boole/Boole2/Unit13.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit13H
#define Unit13H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
class TForm13 : public TForm
{
__published:	// IDE-managed Components
	TLabel			*Label1;
	TEdit			*Edit2;
	TEdit			*Edit1;
	TButton			*Button2;
	TButton			*Button1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);

	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Edit2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

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
	__fastcall		TForm13(TComponent *Owner);
};
extern TForm13	*Form13;
#endif
