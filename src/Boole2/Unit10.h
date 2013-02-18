/*$T boole/Boole2/Unit10.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Unit10H
#define Unit10H
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
class TForm10 : public TForm
{
__published:	// IDE-managed Components
	TButton			*Button1;
	TGroupBox		*GroupBox1;
	TStringGrid		*Tabla;
	TGroupBox		*GroupBox2;
	TListBox		*Errores;
	TGroupBox		*GroupBox3;
	TStringGrid		*Codifica;
	TGroupBox		*GroupBox4;
	TStringGrid		*Tablacod;
	TGroupBox		*GroupBox5;
	TStringGrid		*Excitacion;
	TGroupBox		*GroupBox6;
	TListBox		*Solucion;
	TListBox		*ListaJK;
	TListBox		*ListaD;
	TListBox		*ListaSol;
	TStatusBar		*StatusBar1;
	void __fastcall Button1Click(TObject *Sender);

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
	__fastcall		TForm10(TComponent *Owner);
};
extern TForm10	*Form10;
#endif
