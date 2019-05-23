//---------------------------------------------------------------------------

#ifndef OrdemDeServicoH
#define OrdemDeServicoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormOrdemDeServico : public TForm {

  __published:	// IDE-managed Components
    TGroupBox *GroupBoxConsertoCadastro;
    TLabel *LabelConsertoDefeito;
    TLabel *LabelConsertoCadastroCliente;
    TLabel *LabelConsertoVendedor;
    TMemo *MemoDefeito;
    TComboBox *ComboBoxCliente;
    TComboBox *ComboBoxVendedor;
    TLabel *Label13;
    TComboBox *ComboBoxCodigoProduto;
    TLabel *LabelNumeroSerie;
    TEdit *EditNumeroSerie;
    TLabel *LabelPreco;
    TEdit *EditPreco;
    TBitBtn *BitBtnConfirmarProduto;
    TStringGrid *StringGridConserto;
    TEdit *EditTotal;
    TLabel *LabelTotal;
    TBitBtn *BitBtnImprimirOrcamento;
    TBitBtn *BitBtnVoltar;
    TMainMenu *MainMenuCadastroOrdemServico;
    TMenuItem *MenuItemAtalhos;
    TMenuItem *MenuItemSair;
    TMenuItem *MenuItemImprimirRelatorio;
    TMenuItem *MenuItemConfirmarProduto;
    void __fastcall ComboBoxVendedorKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall ComboBoxClienteKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall ComboBoxCodigoProdutoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall EditNumeroSerieKeyPress(TObject *Sender, char &Key);
    void __fastcall EditPrecoKeyPress(TObject *Sender, char &Key);
    void __fastcall BitBtnConfirmarProdutoClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall StringGridConsertoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BitBtnImprimirOrcamentoClick(TObject *Sender);
    void __fastcall BitBtnVoltarClick(TObject *Sender);
    void __fastcall MemoDefeitoKeyPress(TObject *Sender, char &Key);
  private:	// User declarations
    TMemo *GridMemoDefeitoArray[16];

  public:		// User declarations
    __fastcall TFormOrdemDeServico( TComponent* Owner );
    __fastcall TFormOrdemDeServico::~TFormOrdemDeServico( );
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOrdemDeServico *FormOrdemDeServico;
//---------------------------------------------------------------------------
#endif
