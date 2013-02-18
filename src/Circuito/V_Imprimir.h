/*$T boole/Circuito/V_Imprimir.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef V_ImprimirH
#define V_ImprimirH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
class TFormI : public TForm
{
__published:	// IDE-managed Components
	TGroupBox		*GroupBox1;
	TButton			*Aceptar;
	TButton			*Cancelar;
	TProgressBar	*ProgressBar1;
	TRadioGroup		*Tamanio;
	TRadioGroup		*Orientacion;
	void __fastcall AceptarClick(TObject *Sender);
	void __fastcall CancelarClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

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
	__fastcall		TFormI(TComponent *Owner);
};
extern PACKAGE TFormI	*FormI;
#endif
