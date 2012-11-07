/*$T boole/Boole1/Main.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef MainH
#define MainH
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
class TPrincipal : public TForm
{
__published:	// IDE-managed Components
	TMemo			*memo;
	TMemo			*memo2;
	TBitBtn			*salir;
	TPanel			*Panel1;
	TPanel			*Panel3;
	TLabel			*Label1;
	TLabel			*Label2;
	TLabel			*Label3;
	TImage			*Image1;
	TButton			*Aceptar;
	TBitBtn			*BitBtn1;
	TBitBtn			*BitBtn2;
	TBitBtn			*BitBtn3;
	TBitBtn			*BitBtn4;
	TLabel			*Label4;
	TLabel			*Label5;
	TLabel			*Label6;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall salirClick(TObject *Sender);

	void __fastcall AceptarClick(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);

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
	__fastcall		TPrincipal(TComponent *Owner);
};
extern TPrincipal	*Principal;
#endif
