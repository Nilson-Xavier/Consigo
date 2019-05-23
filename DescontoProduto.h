//---------------------------------------------------------------------------

#ifndef DescontoProdutoH
#define DescontoProdutoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormDescontoProduto : public TForm {
  __published:	// IDE-managed Components
    TPanel *PanelDescontoProduto;
    TLabel *LabelDescontoPreco;
    TRadioButton *RadioButtonDesconto;
    TRadioButton *RadioButtonAcrescimo;
    TEdit *EditDescontoProduto;
  void __fastcall RadioButtonDescontoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall RadioButtonAcrescimoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall EditDescontoProdutoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall EditDescontoProdutoKeyPress(TObject *Sender, char &Key);
  private:	// User declarations
  public:		// User declarations
    __fastcall TFormDescontoProduto( TComponent* Owner );
};
//---------------------------------------------------------------------------
#endif
