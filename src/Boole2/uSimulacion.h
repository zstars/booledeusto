/*$T boole/Boole2/uSimulacion.h GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef uSimulacionH
#define uSimulacionH

#define MAX_PASOS	(32)
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "CSPIN.h"
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
class TfSimulacion : public TForm
{
__published:	// IDE-managed Components
	TMainMenu		*MainMenu1;
	TMenuItem		*Cerrar1;
	TMenuItem		*Log1;
	TMenuItem		*VerLog1;
	TMenuItem		*Ayuda1;
	TPanel			*Panel1;
	TStringGrid		*gridSimulacion;
	TPanel			*Panel2;
	TBitBtn			*btIniciarSim;
	TBitBtn			*btPausarSim;
	TBitBtn			*btSiguiente;
	TBitBtn			*btPararSim;
	TBitBtn			*btRapido;
	TPanel			*Panel3;
	TLabel			*Label1;
	TComboBox		*comboInicial;
	TLabel			*Label2;
	TCSpinEdit		*spinFilas;
  TPopupMenu *PopupTabla;
  TMenuItem *menuInsertarfila;
  TMenuItem *menuEliminarfila;
	void __fastcall gridSimulacionMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall spinFilasChange(TObject *Sender);
	void __fastcall btIniciarSimClick(TObject *Sender);
	void __fastcall comboInicialChange(TObject *Sender);
	void __fastcall Cerrar1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btSiguienteClick(TObject *Sender);
	void __fastcall btPararSimClick(TObject *Sender);
	void __fastcall btPausarSimClick(TObject *Sender);
	void __fastcall gridSimulacionSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall gridSimulacionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall btRapidoClick(TObject *Sender);
	void __fastcall VerLog1Click(TObject *Sender);
  void __fastcall menuInsertarfilaClick(TObject *Sender);
  void __fastcall menuEliminarfilaClick(TObject *Sender);
  void __fastcall PopupTablaPopup(TObject *Sender);
  void __fastcall Ayuda1Click(TObject *Sender);

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
	__fastcall		TfSimulacion(TComponent *Owner);
	void			PosicionarPaso(int paso);
	int				indiceEntInicial;
	int				indiceEntFinal;
	int				indiceCLK;
	int				indiceRESET;
	int				indiceEstado;
	int				indiceEstadoSig;
	int				indiceSalInicial;
	int				indiceSalFinal;
	int				indiceActual;
	bool			pausado;
	void			BorrarTabla(void);
  void      ActualizarTablaYLog();
  void      AnyadirFila(int fila);
  void      SuprimirFila(int fila);
  void      AnyadirPaso(int fila);
  void      SuprimirPaso(int fila);
  void      Renumerar();



        };
extern PACKAGE TfSimulacion *fSimulacion;
#endif
