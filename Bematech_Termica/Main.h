//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\DBGrids.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\DBCtrls.hpp>
#include <vcl\Mask.hpp>
#include <Graphics.hpp>
#include "jpeg.hpp"
#include "ClientSocket.h"
#include "ServerSocket.h"
//---------------------------------------------------------------------------

class TFormPrincipal : public TForm {
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
  TMenuItem *MenuItemSair;
  TPageControl *PageControl1;
  TTabSheet *TabSheetProdutos;
  TTabSheet *TabSheetClientes;
  TTabSheet *TabSheetVendas;
  TTabSheet *TabSheetCotacaoPreco;
	TLabel *Label1;
  TEdit *EditCodigoProduto;
	TLabel *Label3;
  TEdit *EditNomeProduto;
	TImage *Image1;
	TLabel *Label4;
	TLabel *Label5;
  TEdit *EditNomeCliente;
	TLabel *Label6;
  TEdit *EditRgCnpj;
	TLabel *Label7;
  TEdit *EditCep;
	TLabel *Label8;
  TEdit *EditTelefone2;
	TImage *Image2;
	TLabel *Label9;
	TBitBtn *BitBtnInserirCliente;
	TBitBtn *BitBtnInformacaoAdicionalCliente;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
  TComboBox *ComboBoxVendedor;
  TComboBox *ComboBoxRgCnpj;
	TLabel *Label15;
  TComboBox *ComboBoxTipoVenda;
	TLabel *Label16;
  TBitBtn *BitBtnConfirmarProduto;
	TBitBtn *BitBtnCancelarProduto;
  TBitBtn *BitBtnConfirmarVenda;
  TBitBtn *BitBtnCancelarVenda;
	TImage *Image3;
	TLabel *Label17;
  TMenuItem *MenuItemGerencia;
	TPanel *Panel1;
	TLabel *Label18;
  TLabel *LabelCodigoProduto;
  TLabel *LabelQuantidade;
	TMaskEdit *MaskEditQuantidade;
  TLabel *LabelAt;
  TLabel *LabelValidade;
  TEdit *EditAt;
  TLabel *LabelPrazoEntrega;
  TLabel *LabelCondicoesPagamento;
  TLabel *LabelFrete;
	TLabel *LabelEndereco;
  TEdit *EditEndereco;
  TLabel *LabelCep2;
  TLabel *LabelVendedor;
  TComboBox *ComboBoxVendedor2;
	TImage *Image4;
	TLabel *Label31;
  TBitBtn *BitBtnConfirmaProduto;
  TBitBtn *BitBtnImprimirCotacao;
  TLabel *LabelCotacaoTotal;
  TMenuItem *MenuItemProdutos;
  TMenuItem *MenuItemConsultadeProdutos;
  TMenuItem *MenuItemClientes;
  TMenuItem *MenuItemConsultadeClientes;
  TMenuItem *MenuItemFuncoesGerencias;
  TMenuItem *MenuItemInserirClientes;
  TMenuItem *MenuItemInformacoesAdicionais;
  TMenuItem *MenuItemVendas;
  TMenuItem *MenuItemConfirmaProduto;
  TMenuItem *MenuItemEfetuarVenda;
  TMenuItem *MenuItemCancelarProduto;
  TMenuItem *MenuItemConfirmaVenda;
  TMenuItem *MenuItemCotacoes;
  TMenuItem *MenuItemEfetuarCotao;
  TMenuItem *MenuItemConfirmarProduto;
  TMenuItem *MenuItemConfirmarCotacao;
  TMenuItem *MenuItemCancelarCotacao;
  TComboBox *ComboBoxFrete;
  TComboBox *ComboBoxPrazoEntrega;
  TMenuItem *MenuItemAdministrador;
  TMenuItem *MenuItemFerramentasAdministrativas;
	TLabel *Label33;
  TComboBox *ComboBoxTipoNotaFiscal;
	TLabel *Label34;
	TLabel *Label35;
  TImage *Image5;
  TLabel *Label10;
  TEdit *EditNumeroSerie;
  TStringGrid *StrGridVendaProduto;
  TEdit *EditTotal2;
	TStringGrid *StringGridConsultaProduto;
	TStringGrid *StringGridCliente;
	TStringGrid *StringGridProdutoCotacao;
	TEdit *EditTotal;
	TLabel *Label23;
	TEdit *EditNomeEmpresa;
  TLabel *LabelFax;
	TEdit *EditFax;
  TLabel *LabelTelefone;
	TEdit *EditTelefone;
  TLabel *LabelCidade;
	TEdit *EditCidade;
  TLabel *LabelEstado;
  TLabel *LabelPreco;
	TEdit *EditPreco;
	TBitBtn *BitBtnCancelaProdutoCotacao;
	TComboBox *ComboBoxValidade;
  TLabel *LabelCnpj;
	TEdit *EditCNPJ;
  TLabel *LabelInscricaoEstadual;
	TEdit *EditInscricaoEstadual;
  TLabel *LabelEntrada;
  TLabel *LabelParcela;
	TEdit *EditEntrada;
	TEdit *EditParcela;
  TTabSheet *TabSheetSedex;
  TGroupBox *GroupBoxConsulta;
  TLabel *LabelCliente;
  TLabel *LabelCep;
  TLabel *LabelObjeto;
  TLabel *LabelCupom;
  TLabel *Label43;
  TLabel *Label44;
  TStringGrid *StringGridSedex;
  TEdit *EditCliente;
  TEdit *EditCupom;
  TEdit *EditObjeto;
  TMenuItem *MenuItemSedex;
  TComboBox *ComboBoxCondicaoPagamento;
  TEdit *EditTotalSedex;
  TLabel *LabelTotal;
  TComboBox *ComboBoxCodigoProduto;
  TComboBox *ComboBoxEERG;
  TEdit *EditQuantidade;
  TLabel *LabelMarca;
  TEdit *EditMarca;
  TComboBox *ComboBoxEERG2;
  TComboBox *ComboBoxCotacaoCodigoProduto;
  TComboBox *ComboBoxEstado;
  TEdit *EditCotacaoCep;
  TEdit *EditSedexCep;
  TEdit *EditDataInicial;
  TEdit *EditDataFinal;
  TTabSheet *TabSheetConserto;
  TGroupBox *GroupBoxConsertoConsulta;
  TEdit *EditOrdemServico;
  TEdit *EditConsertoNumeroSerie;
  TEdit *EditConsertoData;
  TLabel *LabelOrdemServico;
  TLabel *LabelNumeroSerie;
  TLabel *LabelConsertoCliente;
  TLabel *LabelConsertoData;
  TComboBox *ComboBoxConsertoCliente;
  TStringGrid *StringGridConserto;
  TMemo *MemoConsertoDefeito;
  TLabel *LabelDefeito;
  TMenuItem *Conserto1;
  TMenuItem *MenuItemConsultadeServico;
  TBitBtn *BitBtnInserirOrdemServico;
  TMenuItem *MenuItemOrdemDeServio;
  TTabSheet *TabSheetRecibo;
  TMenuItem *MenuItemRecibo;
  TMenuItem *MenuItemEmissaoRecibo;
  TGroupBox *GroupBoxRecibo;
  TLabel *LabelReciboVendedor;
  TComboBox *ComboBoxReciboVendedor;
  TLabel *LabelRecebemos;
  TComboBox *ComboBoxRecebemos;
  TLabel *LabelReciboValor;
  TEdit *EditReciboValor;
  TLabel *Label2;
  TMemo *MemoReciboReferente;
  TBitBtn *BitBtnReciboImprimir;
  TMenuItem *MenuItemImprimirRecibo;

	void __fastcall MenuItemSairClick(TObject *Sender);
	void __fastcall BitBtnInserirClienteClick(TObject *Sender);
	void __fastcall BitBtnInformacaoAdicionalClienteClick(TObject *Sender);
	void __fastcall BitBtnConfirmarProdutoClick(TObject *Sender);
	void __fastcall BitBtnCancelarProdutoClick(TObject *Sender);
	void __fastcall BitBtnCancelarVendaClick(TObject *Sender);
	void __fastcall BitBtnConfirmarVendaClick(TObject *Sender);
	void __fastcall BitBtnConfirmaProdutoClick(TObject *Sender);
	void __fastcall BitBtnImprimirCotacaoClick(TObject *Sender);
	void __fastcall MenuItemConsultadeProdutosClick(TObject *Sender);
	void __fastcall MenuItemConsultadeClientesClick(TObject *Sender);
	void __fastcall MenuItemEfetuarCotaoClick(TObject *Sender);
	void __fastcall MenuItemFuncoesGerenciasClick(TObject *Sender);
	void __fastcall MenuItemEfetuarVendaClick(TObject *Sender);
	void __fastcall EditCodigoProdutoKeyPress(TObject *Sender, char &Key);
	void __fastcall EditNomeProdutoKeyPress(TObject *Sender, char &Key);
	void __fastcall EditNomeClienteKeyPress(TObject *Sender, char &Key);
	void __fastcall EditRgCnpjKeyPress(TObject *Sender, char &Key);
	void __fastcall EditCepKeyPress(TObject *Sender, char &Key);
	void __fastcall EditTelefone2KeyPress(TObject *Sender, char &Key);
	void __fastcall EditNumeroSerieKeyPress(TObject *Sender, char &Key);
	void __fastcall MaskEditQuantidadeKeyPress(TObject *Sender, char &Key);
	void __fastcall EditAtKeyPress(TObject *Sender, char &Key);
	void __fastcall ComboBoxPrazoEntregaKeyPress(TObject *Sender, char &Key);
	void __fastcall ComboBoxCondicaoPagamentoKeyPress(TObject *Sender, char &Key);
	void __fastcall EditEnderecoKeyPress(TObject *Sender, char &Key);
	void __fastcall ComboBoxFreteKeyPress(TObject *Sender, char &Key);
	void __fastcall MenuItemFerramentasAdministrativasClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ComboBoxRgCnpjChange(TObject *Sender);
	void __fastcall BitBtnCancelaProdutoCotacaoClick(TObject *Sender);
	void __fastcall EditFaxKeyPress(TObject *Sender, char &Key);
	void __fastcall EditTelefoneKeyPress(TObject *Sender, char &Key);
	void __fastcall EditCidadeKeyPress(TObject *Sender, char &Key);
	void __fastcall ComboBoxValidadeKeyPress(TObject *Sender, char &Key);
	void __fastcall EditNomeEmpresaKeyPress(TObject *Sender, char &Key);
	void __fastcall EditInscricaoEstadualKeyPress(TObject *Sender, char &Key);
	void __fastcall EditCNPJKeyPress(TObject *Sender, char &Key);
	void __fastcall EditPrecoKeyPress(TObject *Sender, char &Key);
	void __fastcall EditEntradaKeyPress(TObject *Sender, char &Key);
	void __fastcall EditParcelaKeyPress(TObject *Sender, char &Key);
  void __fastcall ConsultarSedex( String Nome, String Cep, String Objeto, String Cupom, String DataInicial, String DataFinal );
  void __fastcall EditClienteKeyPress(TObject *Sender, char &Key);
  void __fastcall EditObjetoKeyPress(TObject *Sender, char &Key);
  void __fastcall EditCupomKeyPress(TObject *Sender, char &Key);
  void __fastcall MenuItemSedexClick(TObject *Sender);
  void __fastcall StringGridConsultaProdutoSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
  void __fastcall ComboBoxCodigoProdutoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall StrGridVendaProdutoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall ComboBoxTipoNotaFiscalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall ComboBoxVendedorKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
  void __fastcall ComboBoxRgCnpjKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  void __fastcall ComboBoxEERGKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  void __fastcall ComboBoxEERG2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall ComboBoxTipoVendaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall ComboBoxTipoVendaChange(TObject *Sender);
  void __fastcall EditQuantidadeKeyPress(TObject *Sender, char &Key);
  void __fastcall EditMarcaKeyPress(TObject *Sender, char &Key);
  void __fastcall StringGridClienteSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
  void __fastcall ComboBoxCotacaoCodigoProdutoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall EditCotacaoCepKeyPress(TObject *Sender, char &Key);
  void __fastcall ComboBoxVendedor2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall ComboBoxEstadoKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  void __fastcall StringGridProdutoCotacaoSelectCell( TObject *Sender, int ACol, int ARow, bool &CanSelect );
  void __fastcall EditSedexCepKeyPress(TObject *Sender, char &Key);
  void __fastcall EditDataInicialKeyPress(TObject *Sender, char &Key);
  void __fastcall EditDataFinalKeyPress(TObject *Sender, char &Key);
  void __fastcall StringGridProdutoCotacaoKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift);
  void __fastcall MenuItemConsultadeServicoClick(TObject *Sender);
  void __fastcall EditOrdemServicoKeyPress(TObject *Sender, char &Key);
  void __fastcall ComboBoxConsertoClienteKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift);
  void __fastcall EditConsertoDataKeyPress(TObject *Sender, char &Key);
  void __fastcall BitBtnInserirOrdemServicoClick(TObject *Sender);
  void __fastcall EditConsertoNumeroSerieKeyPress(TObject *Sender,
          char &Key);
  void __fastcall StringGridConsertoSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall MenuItemEmissaoReciboClick(TObject *Sender);
  void __fastcall ComboBoxReciboVendedorKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ComboBoxRecebemosKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall EditReciboValorKeyPress(TObject *Sender, char &Key);
  void __fastcall MemoReciboReferenteKeyPress(TObject *Sender, char &Key);
  void __fastcall BitBtnReciboImprimirClick(TObject *Sender);
  void __fastcall ComboBoxReciboVendedorKeyPress(TObject *Sender,
          char &Key);
  void __fastcall ComboBoxRecebemosKeyPress(TObject *Sender, char &Key);
private:	// User declarations
    TJPEGImage *JpegImage3;
    TJPEGImage *JpegImage1;
    TMemo *MemoDefeito[16];

    void DescontoExibir( String* &Valor, bool &Desconto );
    void SenhaExibir( bool *&Accept );
    void CancelarVendaFiscal( int NumeroCupomFiscal );
    void CancelarVenda( int NumeroCupom );
    void ChecarErroTefTemp( void );
    void ConsultarConserto( String* OrdemServico, String* NumeroSerie,
      String* Cliente, String* Data );
public:		// User declarations
	AnsiString *ServerSocketIP;
  TConsigoServerSocket *ServerSocket;
	TConsigoClientSocket *ClientSocket;
  bool *ImpressoraMecafSemaforo;
  bool *ImpressoraEcfSemaforo;
  bool *TefSemaforo;
  bool *QuerySemaforo;

	__fastcall TFormPrincipal( TComponent* Owner );
  __fastcall ~TFormPrincipal( void );
};
//---------------------------------------------------------------------------
extern TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------
#endif
