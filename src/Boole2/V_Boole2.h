
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>/*$T boole/Boole2/V_Boole2.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Form1Boole2H
#define Form1Boole2H
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include <vcl/ExtCtrls.hpp>
#include <vcl/Menus.hpp>
#include <vcl/ComCtrls.hpp>
#include <vcl/Dialogs.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
class TForm1Boole2 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar					*BarraEstado;
	TMainMenu					*MainMenu1;
	TMenuItem					*Archivo1;
	TMenuItem					*Nuevo1;
	TMenuItem					*Salir1;
	TMenuItem					*Ver1;
	TMenuItem					*BarradeBotones1;
	TMenuItem					*General1;
	TMenuItem					*N1;
	TMenuItem					*N2;
	TMenuItem					*Cargar1;
	TMenuItem					*Salvar1;
	TMenuItem					*N3;
	TMenuItem					*Guardar1;
	TSaveDialog					*SaveDialog1;
	TOpenDialog					*OpenDialog1;
	TTimer						*Timer1;
	TMenuItem					*Tablas1;
	TMenuItem					*Resultados1;
	TMenuItem					*ExportaraPDL1;
	TMenuItem					*N4;
	TMenuItem					*CodigoPDL1;
	TMenuItem					*N5;
	TSaveDialog					*SaveDialog2;
	TMenuItem					*Imprimir1;
	TMenuItem					*N6;
	TMenuItem					*Circuito1;
	TMenuItem					*ConflipflopsJK1;
	TMenuItem					*ConflipflopsD1;
	TMenuItem					*Simulacion;
	TMenuItem					*Reduccion;
	TMenuItem					*N7;
	TMenuItem					*N8;
	TMenuItem					*Ayuda1;
	TScrollBox					*TableroBox;
	TImage						*Tablero;
	TMenuItem					*Verificar;
	TMenuItem					*N9;
	TMenuItem					*Batch;
	TMenuItem					*VerificarCompletitud;
	TMenuItem					*N10;
	TMenuItem					*Equivalente;
  TMenuItem *Edicin1;
  TMenuItem *CopiarAutomata;
  TTimer *TimerParpadeoEstado;
  TMenuItem *CopiarTablas;
  TMenuItem *mnTextoAsociado;
  TPanel *pTextAsoc;
  TPanel *pSimulacion;
  TLabel *Label1;
  TButton *Button1;
  TComboBox *comboInicial;
  TButton *Button2;
  TButton *btReset;
  TGroupBox *GroupBox2;
  TLabel *Label2;
  TStringGrid *gridVarsSal;
  TEdit *edEstadoActual;
  TButton *Button4;
  TGroupBox *GroupBox1;
  TStringGrid *gridVarsEnt;
  TBitBtn *btAplicar;
  TEdit *edEntrada;
  TSplitter *Splitter1;
  TMemo *txAsociado;
        TMenuItem *InteractivaRapida;
        TMenuItem *BatchRapida;
        TMenuItem *Contraer1;
	TMenuItem *Expandir1;
	TMenuItem *ExportaraVHDL1;
	TMenuItem *CodigoVHDL1;
	TMenuItem *ExportaraJEDEC1;
        TMenuItem *ExporttoWeblabVHDL1;
	void __fastcall				TableroMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall				FormCreate(TObject *Sender);

	void __fastcall				TableroMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall				TableroMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall				BorrarClick(TObject *Sender);

	void __fastcall				FormShow(TObject *Sender);

	void __fastcall				TableroDblClick(TObject *Sender);

	void __fastcall				Nuevo1Click(TObject *Sender);
	void __fastcall				Salir1Click(TObject *Sender);
	void __fastcall				BarradeBotones1Click(TObject *Sender);

	void __fastcall				General1Click(TObject *Sender);

	void __fastcall				Salvar1Click(TObject *Sender);

	void __fastcall				Guardar1Click(TObject *Sender);
	void __fastcall				Cargar1Click(TObject *Sender);

	void __fastcall				Timer1Timer(TObject *Sender);

	void __fastcall				Tablas1Click(TObject *Sender);
	void __fastcall				Resultados1Click(TObject *Sender);
	void __fastcall				ExportaraPDL1Click(TObject *Sender);

	void __fastcall				CodigoPDL1Click(TObject *Sender);
	void __fastcall				Ver1Click(TObject *Sender);
	void __fastcall				Archivo1Click(TObject *Sender);
	void __fastcall				Imprimir1Click(TObject *Sender);

	void __fastcall				FormClose(TObject *Sender, TCloseAction &Action);

	void __fastcall				ConflipflopsJK1Click(TObject *Sender);

	void __fastcall				ConflipflopsD1Click(TObject *Sender);

	void __fastcall				Reducir1Click(TObject *Sender);
	void __fastcall				SimulacionClick(TObject *Sender);
	void __fastcall				ReduccionClick(TObject *Sender);
	void __fastcall				Circuito1Click(TObject *Sender);
	void __fastcall				Ayuda1Click(TObject *Sender);
	void __fastcall				Button1Click(TObject *Sender);
	void __fastcall				comboInicialChange(TObject *Sender);
	void __fastcall				btAplicarClick(TObject *Sender);
	void __fastcall				gridVarsEntMouseDown
								(
									TObject			*Sender,
									TMouseButton	Button,
									TShiftState		Shift,
									int				X,
									int				Y
								);
	void __fastcall				Button2Click(TObject *Sender);
	void __fastcall				btResetClick(TObject *Sender);
	void __fastcall				VerificarClick(TObject *Sender);
	void __fastcall				BatchClick(TObject *Sender);
	void __fastcall				VerificarCompletitudClick(TObject *Sender);
	void __fastcall				Button4Click(TObject *Sender);
	void __fastcall				EquivalenteClick(TObject *Sender);
  void __fastcall CopiarAutomataClick(TObject *Sender);
  void __fastcall TimerParpadeoEstadoTimer(TObject *Sender);
  void __fastcall CopiarTablasClick(TObject *Sender);
  void __fastcall Edicin1Click(TObject *Sender);
  void __fastcall mnTextoAsociadoClick(TObject *Sender);
        void __fastcall InteractivaRapidaClick(TObject *Sender);
        void __fastcall BatchRapidaClick(TObject *Sender);
        void __fastcall Contraer1Click(TObject *Sender);
	void __fastcall Expandir1Click(TObject *Sender);
	void __fastcall ExportaraVHDL1Click(TObject *Sender);
	void __fastcall CodigoVHDL1Click(TObject *Sender);
	void __fastcall ExportaraJEDEC1Click(TObject *Sender);
        void __fastcall ExporttoWeblabVHDL1Click(TObject *Sender);

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
	__fastcall					TForm1Boole2(TComponent *Owner);
	void TForm1Boole2::			PonerTipo(int);
	void TForm1Boole2::			Nuevo(void);
	void TForm1Boole2::			PonEtEstadoMoore(AnsiString, AnsiString);
	void TForm1Boole2::			PonEtTransicionMoore(AnsiString);
	void TForm1Boole2::			PonEtTransicionMealy(AnsiString, AnsiString);
	void TForm1Boole2::			PonEtEstadoMealy(AnsiString);
	void TForm1Boole2::			Deseleccionar(void);
	int TForm1Boole2::			DameRadio(void);
	void TForm1Boole2::			PonRadio(int);
	void TForm1Boole2::			Redibuja(void);
	void TForm1Boole2::			PonObjMov(int);
	void TForm1Boole2::			PonObjSel(int);
	int TForm1Boole2::			DameObjMov(void);
	int TForm1Boole2::			DameObjSel(void);
	int TForm1Boole2::			DameNumCarEnt(void);
	void TForm1Boole2::			PonerNumCarEnt(int);
	int TForm1Boole2::			DameNumCarSal(void);
	void TForm1Boole2::			PonerNumCarSal(int);
	void TForm1Boole2::			PonColFon(int c);
	int TForm1Boole2::			DameColFon(void);
	int TForm1Boole2::			DarTipo(void);
	AnsiString TForm1Boole2::	DevuelveVar(int i);
	void TForm1Boole2::			PonVar(int i, AnsiString S);
	void TForm1Boole2::			ImprimirPLD(void);
	void TForm1Boole2::			ImprimirAUT(void);
	void TForm1Boole2::			ImprimirAutomata(void);
	void TForm1Boole2::			ImprimirResultados(void);
	void TForm1Boole2::			ResultadosAPortapapeles(void);
	AnsiString TForm1Boole2::	darFormato(AnsiString s);
	int TForm1Boole2::			Num(void);
	int TForm1Boole2::			NumF(void);
	AnsiString TForm1Boole2::	EtiqCirc(int a);

	//
	// void TForm1Boole2::NuevaFlecha(AnsiString a,AnsiString b,AnsiString
	// c,AnsiString d);
	//
	AnsiString TForm1Boole2::	VerFlecha(int i);
	void TForm1Boole2::			simplificar(void);
	void TForm1Boole2::			pasos(void);
	void TForm1Boole2::			continuar(void);
	void TForm1Boole2::			cambiar(void);
	int TForm1Boole2::			HacerVerificacion(bool mostrarSiEsCorrecto, int tipoVerificacion);
  void  __fastcall TForm1Boole2::			DibujarTablaConStrings(TStringList *l, TStringGrid *t, int ancho);

        void TForm1Boole2::IniciarSimulacionInteractiva(int tipoSimulacion);
        void TForm1Boole2::IniciarSimulacionBatch(int tipoSimulacion);

        void TForm1Boole2::CrearCodigoVHDL();

        bool mWeblabMode;

        int tipoSimulacion;
        };
extern TForm1Boole2 *Form1Boole2;

#define CORRECCION	0
#define COMPLETITUD 1

#define IMPRESORA 1
#define PORTAPAPELES 2

#define NORMAL 1
#define RAPIDA 2

#endif
