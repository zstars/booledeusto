/*$T boole/Boole2/Unit4.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit4H
#define Unit4H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TButton			*Button1;
	TButton			*Button2;
	TComboBox		*ComboBox1;
	TLabel			*Label1;
	TLabel			*Label2;
	TEdit			*Edit1;
	TLabel			*Label3;
	TComboBox		*ComboBox2;
	TLabel			*Label4;
	TComboBox		*ComboBox3;
	TEdit			*Entrada1;
	TEdit			*Entrada2;
	TEdit			*Entrada3;
	TEdit			*Entrada4;
	TEdit			*Entrada5;
	TEdit			*Salida1;
	TEdit			*Salida2;
	TEdit			*Salida3;
	TEdit			*Salida4;
	TEdit			*Salida5;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);

	void __fastcall FormShow(TObject *Sender);

	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall ComboBox3Change(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
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
	__fastcall		TForm4(TComponent *Owner);
};
extern TForm4	*Form4;
#endif
