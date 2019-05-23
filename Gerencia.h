//---------------------------------------------------------------------------
#ifndef GerenciaH
#define GerenciaH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\DBGrids.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\Mask.hpp>
#include <vcl\DBCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormGerencia : public TForm {

  __published:	// IDE-managed Components
  	TPageControl *PageControl1;
	  TMainMenu *MainMenu1;
    TMenuItem *MenuItemAtalhos;
	  TMenuItem *Sair1;
    TTabSheet *TabSheetFornecedores;
    TMenuItem *MenuItemFornecedores;
  	TEdit *EditNomeFornecedor;
    TLabel *LabelNomeFornecedor;
    TBitBtn *BitBtnInserirFornecedor;
    TBitBtn *BitBtnRemoverFornecedor;
    TTabSheet *TabSheetEntrada;
	  TLabel *Label3;
    TLabel *LabelCnpj;
    TLabel *LabelNumeroNotaFiscal;
  	TEdit *EditNotaFiscal;
    TLabel *LabelCodigoProduto;
    TLabel *LabelQuantidade;
    TLabel *LabelPrecoUnitario;
  	TBitBtn *BitBtnConfirmaCompra;
	  TBitBtn *BitBtnCancelaCompra;
  	TBitBtn *BitBtnConfirmaProduto;
	  TBitBtn *BitBtnCancelaProduto;
    TLabel *LabelEntradaTotal;
    TMenuItem *MenuItemEntradas;
    TTabSheet *TabSheetPrecos;
	  TLabel *Label12;
  TLabel *LabelPrecoNome;
  TEdit *EditPrecoMarca;
    TMenuItem *MenuItemPrecos;
    TTabSheet *TabSheetEmFalta;
    TLabel *LabelEmFalta;
    TLabel *LabelEmFaltaQuantidade;
    TMenuItem *MenuItemEmFalta;
    TLabel *LabelMarca;
    TEdit *EditMarca;
    TTabSheet *TabSheetFechamento;
    TMenuItem *MenuItemFechamento;
    TLabel *LabelFechamento;
    TLabel *LabelFechamentoDataInicial;
    TLabel *LabelFechamentoDataFinal;
    TLabel *LabelFechamentoTotalGeral;
    TBitBtn *BitBtnFechamentoVendedor;
    TBitBtn *BitBtnEntradaProduto;
    TTabSheet *TabSheetDespesas;
    TMenuItem *MenuItemDespesas;
  	TImage *Image1;
	  TLabel *Label31;
  	TImage *Image2;
	  TLabel *Label32;
  	TImage *Image3;
	  TLabel *Label33;
  	TImage *Image4;
	  TLabel *Label34;
  	TImage *Image5;
	  TLabel *Label35;
    TLabel *LabelFechamentoTotal;
    TLabel *LabelFechamentoTotalOk;
    TTabSheet *TabSheetImpressora;
    TLabel *LblImpressoraFiscal;
    TBitBtn *BitBtnCancelarCupom;
    TBitBtn *BtnLeituraX;
    TBitBtn *BtnReducaoZ;
    TBitBtn *BtnMensagemPromocional;
    TMenuItem *MenuItemSedex;
  	TMaskEdit *MaskEditDataInicial;
	  TMaskEdit *MaskEditDataFinal;
  	TMaskEdit *MaskEditReducaoInicial;
	  TMaskEdit *MaskEditReducaoFinal;
  	TBitBtn *BitBtnLeituraMemoriaFiscalData;
	  TBitBtn *BitBtnLeituraMemoriaFiscalReducao;
  	TLabel *LabelDataInicial;
	  TLabel *LabelDataFinal;
  	TLabel *LabelReducaoInicial;
	  TLabel *LabelReducaoFinal;
  	TStringGrid *StringGridEntradaProduto;
	  TEdit *EditTotalEntrada;
  	TStringGrid *StringGridFornecedor;
    TLabel *LabelObservacoes;
  	TMemo *MemoObservacaoFornecedor;
    TLabel *LabelPrecoMarca;
  TEdit *EditPrecoNome;
	  TStringGrid *StringGridProduto;
  	TStringGrid *StringGridFechamento;
    TEdit *EditFechamentoTotalOk;
    TEdit *EditFechamentoTotal;
    TEdit *EditFechamentoTotalGeral;
    TTabSheet *TabSheetSedex;
    TMenuItem *MenuItemImpressora;
    TGroupBox *GroupBoxConsulta;
    TStringGrid *StringGridSedex;
    TLabel *LabelCliente;
    TEdit *EditCliente;
    TLabel *LabelCep;
    TLabel *LabelObjeto;
    TLabel *LabelCupom;
    TEdit *EditCupom;
    TGroupBox *GroupBoxCadastro;
    TLabel *LabelCep2;
    TLabel *LabelObjeto2;
    TLabel *LabelPreco;
    TEdit *EditSedexPreco;
    TLabel *LabelCupom2;
    TLabel *LabelRG;
    TComboBox *ComboBoxRG;
    TLabel *LabelEERG;
    TBitBtn *BitBtnSedexConfirmar;
    TLabel *LabelSedexDataInicial;
    TLabel *LabelSedexDataFinal;
    TEdit *EditObjeto;
    TBitBtn *BitBtnImprimirListaPreco;
    TGroupBox *GroupBoxDespesa;
    TLabel *LabelDespesaDataInicial;
    TLabel *LabelDespesaDataFinal;
    TStringGrid *StringGridDespesa;
    TLabel *LabelDespesaTotal;
    TEdit *EditTotal;
    TEdit *EditDespesa;
    TLabel *LabelNome;
    TGroupBox *GroupBoxDespesa2;
    TLabel *LabelDespesaNome;
    TEdit *EditNome;
    TLabel *LabelDespesaValor;
    TEdit *EditValor;
    TLabel *LabelDespesaVencimento;
    TBitBtn *BitBtnInserirDespesa;
    TEdit *EditTotalSedex;
    TLabel *LabelTotalSedex;
    TTabSheet *TabSheetTef;
    TLabel *LabelAdministracaoTef;
    TBitBtn *BitBtnAdministracaoTefVisanet;
    TBitBtn *BitBtnAdministracaoTefTecBan;
    TBitBtn *BitBtnConsultarCheque;
    TMenuItem *MenuItemTef;
    TComboBox *ComboBoxCnpj;
    TComboBox *ComboBoxCodigoProduto;
    TEdit *EditQuantidade;
    TEdit *EditEntradaPreco;
    TEdit *EditCep;
    TEdit *EditDataInicial;
    TEdit *EditDataFinal;
    TEdit *EditCadastroCep;
    TEdit *EditCadastroObjeto;
    TComboBox *ComboBoxCupom;
    TComboBox *ComboBoxEerg;
    TEdit *EditEmFaltaQuantidade;
    TEdit *EditDespesaDataInicial;
    TEdit *EditDespesaDataFinal;
    TEdit *EditVencimento;
    TEdit *EditFechamentoDataInicial;
    TEdit *EditFechamentoDataFinal;
  TStringGrid *StringGridAlteracaoProduto;
  TTabSheet *TabSheetConserto;
  TMenuItem *MenuItemConserto;
  TGroupBox *GroupBoxOrdemDeServico;
  TLabel *LabelOrdemServico;
  TEdit *EditOrdemServico;
  TLabel *LabelNumeroSerie;
  TEdit *EditConsertoNumeroSerie;
  TLabel *LabelConsertoCliente;
  TComboBox *ComboBoxConsertoCliente;
  TLabel *LabelConsertoData;
  TEdit *EditConsertoData;
  TStringGrid *StringGridConserto;
  TLabel *LabelDefeito;
  TMemo *MemoConsertoDefeito;

  	void __fastcall BitBtnInserirFornecedorClick(TObject *Sender);
    void __fastcall BitBtnRemoverFornecedorClick(TObject *Sender);
  	void __fastcall BitBtnConfirmaProdutoClick(TObject *Sender);
	  void __fastcall MenuItemEntradasClick(TObject *Sender);
  	void __fastcall BitBtnCancelaProdutoClick(TObject *Sender);
	  void __fastcall BitBtnConfirmaCompraClick(TObject *Sender);
  	void __fastcall BitBtnCancelaCompraClick(TObject *Sender);
	  void __fastcall MenuItemPrecosClick(TObject *Sender);
  	void __fastcall MenuItemEmFaltaClick(TObject *Sender);
	  void __fastcall MenuItemFechamentoClick(TObject *Sender);
  	void __fastcall BitBtnFechamentoVendedorClick(TObject *Sender);
	  void __fastcall BitBtnEntradaProdutoClick(TObject *Sender);
  	void __fastcall MenuItemDespesasClick(TObject *Sender);
	  void __fastcall BitBtnInserirDespesaClick(TObject *Sender);
  	void __fastcall EditNomeFornecedorKeyPress(TObject *Sender, char &Key);
	  void __fastcall EditNotaFiscalKeyPress(TObject *Sender, char &Key);
  	void __fastcall EditMarcaKeyPress(TObject *Sender, char &Key);
	  void __fastcall EditNomeKeyPress(TObject *Sender, char &Key);
	  void __fastcall TabSheetPrecosExit(TObject *Sender);
  	void __fastcall TabSheetPrecosEnter(TObject *Sender);
    void __fastcall BitBtnCancelarCupomClick(TObject *Sender);
    void __fastcall BtnLeituraXClick(TObject *Sender);
    void __fastcall BtnReducaoZClick(TObject *Sender);
    void __fastcall BtnMensagemPromocionalClick(TObject *Sender);
	  void __fastcall SedexClick(TObject *Sender);
  	void __fastcall BitBtnLeituraMemoriaFiscalDataClick(TObject *Sender);
	  void __fastcall BitBtnLeituraMemoriaFiscalReducaoClick(TObject *Sender);
  	void __fastcall FormCreate(TObject *Sender);
	  void __fastcall EditPrecoMarcaKeyPress(TObject *Sender, char &Key);
  	void __fastcall EditPrecoNomeKeyPress(TObject *Sender, char &Key);
    void __fastcall ImpressoraClick(TObject *Sender);
    void __fastcall BitBtnSedexConfirmarClick(TObject *Sender);
    void __fastcall ConsultarSedex( String* Nome, String* Cep, String* Objeto,
      String* Cupom, String* DataInicial, String* DataFinal );
    void __fastcall EditClienteKeyPress(TObject *Sender, char &Key);
    void __fastcall EditObjetoKeyPress(TObject *Sender, char &Key);
    void __fastcall EditCupomKeyPress(TObject *Sender, char &Key);
    void __fastcall BitBtnImprimirListaPrecoClick(TObject *Sender);
    void __fastcall EditSedexPrecoKeyPress(TObject *Sender, char &Key);
    void __fastcall MenuItemTefClick(TObject *Sender);
    void __fastcall BitBtnAdministracaoTefVisanetClick(TObject *Sender);
    void __fastcall BitBtnAdministracaoTefTecBanClick(TObject *Sender);
    void __fastcall BitBtnConsultarChequeClick(TObject *Sender);
    void __fastcall StringGridFornecedorKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall ComboBoxCnpjKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall ComboBoxCodigoProdutoKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall EditQuantidadeKeyPress(TObject *Sender, char &Key);
    void __fastcall EditEntradaPrecoKeyPress(TObject *Sender, char &Key);
    void __fastcall StringGridEntradaProdutoKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift);
    void __fastcall EditCepKeyPress(TObject *Sender, char &Key);
    void __fastcall EditDataInicialKeyPress(TObject *Sender, char &Key);
    void __fastcall EditDataFinalKeyPress(TObject *Sender, char &Key);
    void __fastcall EditCadastroCepKeyPress(TObject *Sender, char &Key);
    void __fastcall EditCadastroObjetoKeyPress(TObject *Sender, char &Key);
    void __fastcall ComboBoxCupomKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall ComboBoxRGKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall ComboBoxEergKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall EditEmFaltaQuantidadeKeyPress(TObject *Sender,
      char &Key);
    void __fastcall EditDespesaDataInicialKeyPress(TObject *Sender,
      char &Key);
    void __fastcall EditDespesaDataFinalKeyPress(TObject *Sender, char &Key);
    void __fastcall EditDespesaKeyPress(TObject *Sender, char &Key);
    void __fastcall EditVencimentoKeyPress(TObject *Sender, char &Key);
    void __fastcall EditValorKeyPress(TObject *Sender, char &Key);
    void __fastcall EditFechamentoDataInicialKeyPress(TObject *Sender,
      char &Key);
    void __fastcall EditFechamentoDataFinalKeyPress(TObject *Sender,
      char &Key);
    void __fastcall Sair1Click( TObject *Sender );
    void __fastcall MenuItemFornecedoresClick( TObject *Sender );
  void __fastcall StringGridAlteracaoProdutoSelectCell(TObject *Sender,
          int ACol, int ARow, bool &CanSelect);
  void __fastcall StringGridAlteracaoProdutoKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift);
  void __fastcall StringGridAlteracaoProdutoGetEditText(TObject *Sender,
          int ACol, int ARow, AnsiString &Value);
  void __fastcall StringGridAlteracaoProdutoKeyPress(TObject *Sender,
          char &Key);
  void __fastcall MenuItemConsertoClick(TObject *Sender);
  void __fastcall EditOrdemServicoKeyPress(TObject *Sender, char &Key);
  void __fastcall EditConsertoNumeroSerieKeyPress(TObject *Sender,
          char &Key);
  void __fastcall ComboBoxConsertoClienteKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift);
  void __fastcall EditConsertoDataKeyPress(TObject *Sender, char &Key);
  void __fastcall StringGridConsertoSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall StringGridConsertoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall StringGridConsertoGetEditMask(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
  void __fastcall MemoConsertoDefeitoKeyPress(TObject *Sender, char &Key);
  void __fastcall MemoConsertoDefeitoExit(TObject *Sender);
    
  private:	// User declarations
    TMemo *MemoDefeito[16];
    TListBox *ListBoxConsertoGrid;

    void __fastcall ConsultarProdutoEmFalta( String* Quantidade, String* Marca );
    void __fastcall ConsultarDespesa( String* DataInicial, String* DataFinal, String* Nome );
    void __fastcall ListarFechamento( String* DataInicial, String* DataFinal );
    void __fastcall ConsultarProduto( String* Marca, String* Nome );
    void ConsultarConserto( String* OrdemServico, String* NumeroSerie,
      String* Cliente, String* Data );
    void __fastcall ListBoxConsertoStatusKeyPress( TObject* Sender, char &Key );
    void __fastcall TFormGerencia::ListBoxConsertoVendedorKeyPress( TObject* Sender, char &Key );
    void __fastcall TFormGerencia::ListBoxConsertoClienteKeyPress( TObject* Sender, char &Key );
    
  public:		// User declarations
    bool *SecurityFlag;

	  __fastcall TFormGerencia( TComponent* Owner );
    __fastcall TFormGerencia::~TFormGerencia( void );
};
//---------------------------------------------------------------------------
extern TFormGerencia *FormGerencia;
//---------------------------------------------------------------------------
#endif
