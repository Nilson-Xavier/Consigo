//---------------------------------------------------------------------------

#ifndef FormaPagamentoH
#define FormaPagamentoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormFormaPagamento : public TForm
{
__published:	// IDE-managed Components
  TLabel *LabelFormaPagamento1;
  TLabel *LabelFormaPagamento2;
  TComboBox *ComboBoxFormaPagamento;
  TLabel *LabelFormaPagamento3;
  TLabel *LabelFormaPagamento4;
  TEdit *EditValorFormaPagamento;
  void __fastcall EditValorFormaPagamentoKeyPress(TObject *Sender,
          char &Key);
  void __fastcall ComboBoxFormaPagamentoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
  __fastcall TFormFormaPagamento(TComponent* Owner);
  __fastcall ~TFormFormaPagamento( );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormFormaPagamento *FormFormaPagamento;
//---------------------------------------------------------------------------
#endif
