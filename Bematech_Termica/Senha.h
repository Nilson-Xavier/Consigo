//---------------------------------------------------------------------------
#ifndef SenhaH
#define SenhaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormPassword : public TForm {
  __published:	// IDE-managed Components
    TLabel *LabelSenhaDeAcesso;
    TEdit *EditSenhaDeAcesso;
    void __fastcall EditSenhaDeAcessoKeyDown( TObject *Sender, WORD &Key,
      TShiftState Shift );
  private:	// User declarations
  public:		// User declarations
    bool *Accept;
    __fastcall TFormPassword( TComponent* Owner );
     __fastcall ~TFormPassword( );
};
//---------------------------------------------------------------------------
#endif
