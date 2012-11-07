/*$T boole/Circuito/V_Circuito.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef V_CircuitoH
#define V_CircuitoH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <checklst.hpp>
#include <Buttons.hpp>
struct Punto
{
public:
	int			x;
	int			y;
	AnsiString	nombre;
	Punto()
	{
	};
	Punto (int x1, int y1)
	{
		x = x1;
		y = y1;
	}
	Punto(AnsiString n, int x1, int y1)
	{
		nombre = n;
		x = x1;
		y = y1;
	}
};

class TFormR : public TForm
{
__published:	// IDE-managed Components
	TPanel			*Panel1;
	TButton			*Visualizar;
	TEdit			*ecuacion;
	TButton			*Menos;
	TButton			*Mas;
	TButton			*Copiar;
	TScrollBox		*ScrollBox1;
	TImage			*Image1;

	TStatusBar		*barraEstado;
	TStatusBar		*X;
	TStatusBar		*Y;
	TListBox		*Lista;
	TBitBtn			*Volver;
	TBitBtn			*Imprimir;
	TListBox		*ListaSol;
	TPanel			*Panel2;
  TBitBtn *BitBtn4;
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall VisualizarClick(TObject *Sender);

	void __fastcall MenosClick(TObject *Sender);
	void __fastcall MasClick(TObject *Sender);

	void __fastcall CopiarClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall FormCreate(TObject *Sender);

	void __fastcall ecuacionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Panel1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ecuacionKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall VisualizarMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall VolverMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ImprimirVMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ImprimirHMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall CopiarMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MasMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MenosMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall VolverClick(TObject *Sender);
	void __fastcall ListaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

	void __fastcall ListaClick(TObject *Sender);

	void __fastcall ImprimirClick(TObject *Sender);
	void __fastcall ImprimirVClick(TObject *Sender);

	void __fastcall ImprimirMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ecuacionClick(TObject *Sender);
	void __fastcall ecuacionMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall ListaSolClick(TObject *Sender);
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

	// AnsiString salida; Punto tamanioCircuito;
	Punto			tamanioCircuito;
	bool			tipoCircuito;	// false: combinacional, true: secuencial.
	bool			tipoCS;			// false: Moore true: Mealy.
	bool			tipoFlipFlops;	// false: flip-flop D. true: flip-flop JK.
	int				solucionNum;
	AnsiString		Titulo;
	__fastcall		TFormR(TComponent *Owner);
};
extern PACKAGE TFormR	*FormR;
#endif
