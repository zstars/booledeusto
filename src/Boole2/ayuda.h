/*$T boole/Boole2/ayuda.h GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef ayudaH
#define ayudaH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
class TfAyuda : public TForm
{
__published:	// IDE-managed Components
	TLabel			*Label1;
	TStaticText		*StaticText1;
	TMemo			*Memo1;
	TLabel			*Label2;
	TMemo			*Memo2;
	TMemo			*Memo3;
	TMemo			*Memo4;
	TMemo			*Memo5;
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
	__fastcall		TfAyuda(TComponent *Owner);
};
extern PACKAGE TfAyuda	*fAyuda;
#endif
