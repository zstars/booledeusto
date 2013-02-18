//---------------------------------------------------------------------------

#ifndef uKarnaughH
#define uKarnaughH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Karnaugh.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <set>
#include <vector>
using namespace std;
#include "reductio\cubobool.h"

#define FORMATO_POS (1)
#define FORMATO_SOP (2)

#define MODO_EDITABLE (1)
#define MODO_NOEDITABLE (2)
#define MODO_APRENDIZAJE_EXPR (3)
#define MODO_APRENDIZAJE_LAZOS  (4)

//---------------------------------------------------------------------------
class TfKarnaugh : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TRadioGroup *tipoVK;
	TRadioGroup *tipoVisu;
	TPanel *pMostrarLazos;
	TCheckBox *ckMostrarLazos;
	TButton *bAceptar;
	TButton *Button2;
	TButton *bCancelar;
	TGroupBox *grpCompletar;
	TButton *Button1;
	TButton *Button3;
	TButton *Button4;
        TPanel *Panel3;
        TGroupBox *gbSalida;
        TListBox *listVarSal;
        TGroupBox *gbLazos;
        TListBox *listLazos;
        TPanel *Panel4;
        TKarnaugh *Mapa;
        TGroupBox *gbExprBool;
        TEdit *edExprBool;
        TButton *Button5;
        TGroupBox *gbDibujarLazos;
        TButton *Button7;
        TButton *Button6;
        TButton *Button8;
        TButton *Button9;
        TSpeedButton *SpeedButton1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tipoVKClick(TObject *Sender);
	void __fastcall tipoVisuClick(TObject *Sender);
	void __fastcall ckMostrarLazosClick(TObject *Sender);
	void __fastcall bAceptarClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall listVarSalClick(TObject *Sender);
	void __fastcall bCancelarClick(TObject *Sender);
	void __fastcall MapaMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
        void __fastcall listLazosClick(TObject *Sender);
        void __fastcall MapaPaint(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
	vector<set<CuboBool> > *vectorMint, *vectorMaxt, *vectorTIs, *vectorIPs, *vectorIPsDibujados, *vectorLazo;
        vector<CuboBool> *vectorIPsLazos;
        vector<int> *vectorLiteralesSoluciones;
        size numVars;

        void ParametrosIniciales();
        void CargarFunciones();
        void CargarSoluciones();
        void CambiarTamanyo();
        void CrearLazo();
        void MostrarFuncion(int numFuncion);
        int modo;
        bool dibujar;
        int formato;


public:		// User declarations
	__fastcall TfKarnaugh(TComponent* Owner);
         __fastcall ~TfKarnaugh();
	void setNumVars(size numVars);
        void setModo(int modo);
        void setFormato(int formato);
protected:
        AnsiString IP2Expresion(CuboBool & c);
};
//---------------------------------------------------------------------------
extern PACKAGE TfKarnaugh *fKarnaugh;
//---------------------------------------------------------------------------
#endif
