/*$T boole/Boole1/NuevoSC.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef NuevoSCH
#define NuevoSCH
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <vcl/Classes.hpp>
#include <vcl/Controls.hpp>
#include <vcl/StdCtrls.hpp>
#include <vcl/Forms.hpp>
#include "Grids.hpp"
#include <vcl/Dialogs.hpp>
#include <vcl/Buttons.hpp>
#include <ExtCtrls.hpp>
class TSistemaCombinacionalNuevo : public TForm
{
__published:	// IDE-managed Components
	TLabel			*Label1;
	TEdit			*Edit1;
	TGroupBox		*SistemaCombinacional;
	TLabel			*VariablesEntrada;
	TEdit			*NEntradas;
	TLabel			*VariablesSalida;
	TEdit			*NSalidas;
	TLabel			*Label3;
	TLabel			*Label4;
	TStringGrid		*TablaEntrada;
	TStringGrid		*TablaSalida;
	TGroupBox		*ModoEntrada;
	TButton			*TVManual;
	TButton			*TVCompacta;
	TButton			*DiagramaVK;
	TButton			*ExpBooleana;
	TButton			*Button2;
	TButton			*Button3;
	TSaveDialog		*Guardador;
	TOpenDialog		*Cargador;
	TButton			*SOPSimp;
	TButton			*POSSimp;
	TSaveDialog		*GuardaPLD;
	TPrintDialog	*impresora;
	TMemo			*CTexto;
	TBitBtn			*GuardarPLD;
	TBitBtn			*SalvarSCO;
	TBitBtn			*ImprimirDoc;
	TBitBtn			*CargarSistema;
	TBitBtn			*Cerrar;
  TButton *Button5;
  TButton *Button6;
  TBitBtn *BitBtn1;
  TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
        TButton *btApExprBool;
        TButton *Button4;
	TBitBtn *BitBtn4;
        TBitBtn *BitBtn5;
        TButton *btWeblab;
	void __fastcall NEntradasChange(TObject *Sender);

	void __fastcall NSalidasChange(TObject *Sender);

	void __fastcall TVManualClick(TObject *Sender);

	void __fastcall SalirClick(TObject *Sender);

	void __fastcall FNPOSClick(TObject *Sender);
	void __fastcall FNSOPClick(TObject *Sender);
	void __fastcall TVCompactaClick(TObject *Sender);

	void __fastcall FormShow(TObject *Sender);
	void __fastcall ExpBooleanaClick(TObject *Sender);
	void __fastcall GuardarClick(TObject *Sender);
	void __fastcall btApExprBoolClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall CargarClick(TObject *Sender);

	void __fastcall SOPSimpClick(TObject *Sender);
	void __fastcall POSSimpClick(TObject *Sender);

	void __fastcall ImprimirClick(TObject *Sender);
	void __fastcall GuardarPLDClick(TObject *Sender);
	void __fastcall SalvarSCOClick(TObject *Sender);
	void __fastcall ImprimirDocClick(TObject *Sender);
	void __fastcall CargarSistemaClick(TObject *Sender);
	void __fastcall CerrarClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);

	void __fastcall SOPSimpExit(TObject *Sender);
  void __fastcall Button5Click(TObject *Sender);
  void __fastcall Button6Click(TObject *Sender);
  void __fastcall BitBtn1Click(TObject *Sender);
  void __fastcall Edit1Change(TObject *Sender);
  void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall DiagramaVKClick(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall btWeblabClick(TObject *Sender);

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
	__fastcall		TSistemaCombinacionalNuevo(TComponent *Owner);
};
extern TSistemaCombinacionalNuevo	*SistemaCombinacionalNuevo;

void Imprimir(int destino);

#define IMPRESORA 1
#define PORTAPAPELES 2
#endif
