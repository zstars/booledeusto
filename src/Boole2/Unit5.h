/*$T boole/Boole2/Unit5.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit5H
#define Unit5H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
class TForm5 : public TForm
{
__published:	// IDE-managed Components
	TEdit			*Edit2;
	TLabel			*Label1;
	TEdit			*Edit1;
	TButton			*Button2;
	TButton			*Button1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
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
	__fastcall		TForm5(TComponent *Owner);
};
extern TForm5	*Form5;
#endif
