/*$T boole/Boole2/SimulacionMoore.h GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef SimulacionMooreH
#define SimulacionMooreH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
class TFormMoore : public TForm
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

	TBitBtn			*BitBtn3;
	void __fastcall Button1Click(TObject *Sender);

	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);

	void __fastcall FormShow(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:	// User declarations

	// User declarations
	struct Est
	{
		AnsiString	Nombre;
		AnsiString	Salida;
		AnsiString	Enlace[32][2];
		int			Enlaces;
	};
	Est			Estados[20];
	int			Salidas;
	int			Entradas;

	AnsiString	AFea;
	AnsiString	AFs1;
	AnsiString	AFs2;
	AnsiString	AFs3;
	AnsiString	AFs4;
	AnsiString	AFs5;
	AnsiString	AFe1;
	AnsiString	AFe2;
	AnsiString	AFe3;
	AnsiString	AFe4;
	AnsiString	AFe5;
	AnsiString	AFe1sin;
	AnsiString	AFe2sin;
	AnsiString	AFe3sin;
	AnsiString	AFe4sin;
	AnsiString	AFe5sin;
	AnsiString	AFes;
	int			cont;
	__fastcall	TFormMoore(TComponent *Owner);
};
extern PACKAGE TFormMoore	*FormMoore;
#endif
