/*$T boole/Boole2/Unit11.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit11H
#define Unit11H
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include "Grids.hpp"
#include <vcl/ExtCtrls.hpp>
class TForm11 : public TForm
{
__published:	// IDE-managed Components
	TButton					*Button1;
	TGroupBox				*GroupBox2;
	TGroupBox				*GroupBox3;
	TGroupBox				*GroupBox4;
	TListBox				*IndicesInicial;
	TListBox				*IndicesFinal;
	TListBox				*Resultado;
	TListBox				*Original;
	TGroupBox				*GroupBox1;
	TListBox				*Aux;
	TGroupBox				*GroupBox5;
	TListBox				*Implicados;
	TGroupBox				*GroupBox6;
	TGroupBox				*GroupBox7;
	TEdit					*Unos;
	TEdit					*Equis;
	TStringGrid				*Ver;
	TGroupBox				*GroupBox8;
	TStringGrid				*Tabla;
	TGroupBox				*GroupBox9;
	TEdit					*Solucion;
	TListBox				*Aux2;
	TGroupBox				*GroupBox10;
	TEdit					*NumC;
	TMemo					*Memo1;
	void __fastcall			Button1Click(TObject *Sender);

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
	__fastcall				TForm11(TComponent *Owner);
	AnsiString TForm11::	Simplifica(AnsiString, AnsiString, int);
};
extern TForm11	*Form11;
#endif
