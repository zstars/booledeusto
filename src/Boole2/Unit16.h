/*$T boole/Boole2/Unit16.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit16H
#define Unit16H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
class TForm16 : public TForm
{
__published:	// IDE-managed Components
	TButton			*Button1;
	TListBox		*ListBox3;
	TListBox		*ListBox4;
	TLabel			*Label1;
	TLabel			*Label2;
	TEdit			*Edit1;
	TEdit			*Edit2;
	TStringGrid		*Grid1;
	TButton			*Button2;
	TButton			*Button3;
	TLabel *lblInferior;
	TLabel *lblSuperior;
	TLabel			*Label6;
	TListBox		*ListBox1;
	TLabel			*Label7;
	TListBox		*ListBox2;
	TLabel			*Label8;
	TLabel			*Label9;
	TButton			*Button4;
	TLabel			*Label10;
	TLabel			*Label11;
	TEdit			*Edit3;
	TEdit			*Edit4;
	TEdit			*Edit6;
	TEdit			*Edit5;
	TBitBtn			*BitBtn3;
	TGroupBox		*Label3;
	TGroupBox		*GroupBox1;
	TLabel *lblAviso;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BitBtn3Click(TObject *Sender);

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
	__fastcall		TForm16(TComponent *Owner);
};
extern PACKAGE TForm16	*Form16;
#endif
