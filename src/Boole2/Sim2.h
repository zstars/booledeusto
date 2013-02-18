/*$T boole/Boole2/Sim2.h GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Sim2H
#define Sim2H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
class TFormMealy : public TForm
{
__published:	// IDE-managed Components
	TLabel			*Label1;
	TLabel			*Label2;
	TLabel			*Label3;
	TLabel			*Label4;
	TLabel			*Label5;
	TLabel			*Label6;
	TLabel			*Label7;
	TLabel			*Label8;
	TLabel			*Label9;
	TLabel			*Label10;
	TPanel			*Panel1;
	TEdit			*Fs1;
	TEdit			*Fs2;
	TEdit			*Fs3;
	TEdit			*Fs4;
	TEdit			*Fea;
	TPanel			*Panel2;
	TEdit			*Fe1;
	TEdit			*Fe2;
	TEdit			*Fe3;
	TEdit			*Fe4;
	TEdit			*Fes;
	TButton			*Button1;
	TButton			*Button2;
	TButton			*Button4;
	TButton			*Button5;
	TEdit			*Fe5;
	TEdit			*Fs5;
	TLabel			*Label13;
	TLabel			*Label14;
	TButton			*Button3;
	void __fastcall Button1Click(TObject *Sender);

	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);

	void __fastcall Button3Click(TObject *Sender);

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
	int				Salidas;
	int				Entradas;
	struct Est
	{
		AnsiString	Nombre;
		AnsiString	Enlace[32][3];
		int			Enlaces;
	};
	Est			Estados[20];
	__fastcall	TFormMealy(TComponent *Owner);
};
extern PACKAGE TFormMealy	*FormMealy;
#endif
