/*$T boole/Boole2/Unit9.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit9H
#define Unit9H
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include "Grids.hpp"
#include <ComCtrls.hpp>
class TForm9 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox		*GroupBox1;
	TStringGrid		*Tabla;
	TGroupBox		*GroupBox2;
	TListBox		*Errores;
	TGroupBox		*GroupBox;
	TStringGrid		*Excitacion;
	TGroupBox		*GroupBox4;
	TStringGrid		*Tablacod;
	TGroupBox		*GroupBox6;
	TStringGrid		*Salidacod;
	TGroupBox		*GroupBox7;
	TStringGrid		*Codifica;
	TListBox		*ListaJK;
	TListBox		*ListaD;
	TListBox		*ListaSol;
	TGroupBox		*GroupBox5;
	TListBox		*Solucion;
	TStatusBar		*StatusBar1;
	TButton			*Button1;
	void __fastcall FormHide(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

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
	__fastcall		TForm9(TComponent *Owner);
};
extern TForm9	*Form9;
#endif
