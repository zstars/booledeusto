/*$T boole/Boole2/Unit3.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit3H
#define Unit3H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TEdit			*Edit1;
	TButton			*Button1;
	TButton			*Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

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
	__fastcall		TForm3(TComponent *Owner);
};
extern TForm3	*Form3;
#endif
