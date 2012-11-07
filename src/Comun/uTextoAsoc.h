//---------------------------------------------------------------------------

#ifndef uTextoAsocH
#define uTextoAsocH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfTextoAsoc : public TForm
{
__published:	// IDE-managed Components
  TMemo *txAsociado;
private:	// User declarations
public:		// User declarations
  __fastcall TfTextoAsoc(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfTextoAsoc *fTextoAsoc;
//---------------------------------------------------------------------------
#endif
