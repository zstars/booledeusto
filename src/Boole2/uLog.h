/*$T boole/uLog.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef uLogH
#define uLogH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

#define LINEA				'-'
#define LINEA_DOBLE			'='
#define BARRA				'|'
#define BARRA_DOBLE			"||"

#define LINEAS				0
#define LINEAS_DOBLES		1
#define TITULO			2
#define TEXTO				4
#define RESET_MEALY 5
#define RESET_MOORE 6
#define CLOCK_MEALY 7
#define CLOCK_MOORE 8




#define ENTRADAS			0
#define SALIDAS				1

#define RESET				true
#define NO_RESET			false

#define CLK					true
#define NO_CLK				false

#define LLAMA_INTERACTIVA	0
#define LLAMA_BATCH			1
class TfLog : public TForm
{
__published:	// IDE-managed Components
	TMemo					*memoLog;
	TPanel					*Panel1;
	TButton					*Button1;
	TButton					*Button2;
	TButton					*Button3;
	TButton					*Button4;
	TSaveDialog				*saveLog;
	TPrintDialog			*printLog;
	void __fastcall			Button1Click(TObject *Sender);
	void __fastcall			Button3Click(TObject *Sender);
	void __fastcall			Button4Click(TObject *Sender);
	void __fastcall			Button2Click(TObject *Sender);
	void __fastcall			FormClose(TObject *Sender, TCloseAction &Action);

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
	__fastcall				TfLog(TComponent *Owner);
	void __fastcall			EscribirLinea
							(
								int			tipo,
                int     tipoAutomata,
                int     tipoSimulacion,
								int			paso = 0,
								bool		reset = false,
								bool		clk = false,
								AnsiString	estado = "",
								AnsiString	ent = "",
								AnsiString	estadosig = "",
								AnsiString	sal = ""
							);
	AnsiString __fastcall	EscribirColumna(int tipo, AnsiString texto, AnsiString titulo);
	AnsiString __fastcall	EscribirEntSal(int tipo, AnsiString texto, int entsal);
	void __fastcall			EscribirCabecera(int tipoAutomata, int tipoSimulacion);
	int						llamador;
	int						pasoActual;
};
extern PACKAGE TfLog	*fLog;
#endif
