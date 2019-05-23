//---------------------------------------------------------------------------
#ifndef ValorCartaoH
#define ValorCartaoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormValorCartao : public TForm {

  __published:	// IDE-managed Components
    TLabel *LabelValorCartao;
    TEdit *EditValorCartao;
  void __fastcall EditValorCartaoKeyPress(TObject *Sender, char &Key);
  private:	// User declarations
  public:		// User declarations
    __fastcall TFormValorCartao( TComponent* Owner );
    __fastcall ~TFormValorCartao( );
};
//---------------------------------------------------------------------------
#endif
