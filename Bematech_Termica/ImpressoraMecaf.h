//---------------------------------------------------------------------------
#ifndef ImpressoraMecafH
#define ImpressoraMecafH
//---------------------------------------------------------------------------
#include <vcl\Windows.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Sysutils.hpp>
#include <vcl\StrUtils.hpp>
//---------------------------------------------------------------------------
// Funções da Impressora MECAF

// Obtém Status da Impressora
typedef int ( WINAPI *CPByteStatus ) ( void );
// Obtém o Estado da Impressora
typedef int ( WINAPI *CPStatusImp ) ( void );
// Inicia a Impressora
typedef int ( WINAPI *CPReset ) ( void );
// Inicia a Impressora pela Interface Paralela
typedef int ( WINAPI *CPInit ) ( void );
// Imprime
typedef int ( WINAPI *CPImprime ) ( char far *, int );
// Modo Documento da Impressora
typedef int ( WINAPI *CPModoDoc ) ( void );
// Modo Normal da Impressora
typedef int ( WINAPI *CPModoPE ) ( void );
// Validação ou Autenticação de Documentos
typedef int ( WINAPI *CPValidaDoc ) ( char far *, int );
// Validação de Documentos e Bobina
typedef int ( WINAPI *CPValidaDupla ) ( char far *, int );
// Cancela a Validação de Documentos e Bobina
typedef int ( WINAPI *CPCancelCmd ) ( void );

class TImpressoraMecaf : public TObject {
  private:
    CPByteStatus CPByteStatusImpressora;
    CPStatusImp CPStatusImpressora;
    CPReset CPResetImpressora;
    CPInit CPInitImpressora;
    CPImprime CPImprimeTexto;
		CPModoDoc CPModoDocImpressora;
    CPModoPE CPModoPEImpressora;
    CPValidaDoc CPValidaDocImpressora;
    CPValidaDupla CPValidaDuplaImpressora;
    CPCancelCmd CPCancelCmdImpressora;
    
    int *Itens;
    bool *FilmeRebobinado;
    String *NumeroCupom;
    String *ValorTotal;
  public:
    __property String *Cupom = { read=NumeroCupom, write=NumeroCupom };
    __property String *Total = { read=ValorTotal, write=ValorTotal };

    __fastcall TImpressoraMecaf( );
    __fastcall TImpressoraMecaf::~TImpressoraMecaf( );
    void ObterRetornoComando( int CodRetorno, String* &Retorno );
    void ObterStatus( String* &Retorno );
    void CarregarDll( String* &Retorno );
    void Iniciar( String* &Retorno );
    void AbrirCupom( String* Cupom, String *CpfCnpj, String *Nome, String* &Retorno );
    void LancarItem( String* Qtd, String* PrecoUnit, String* Codigo,
      String* Descricao, String* &Retorno );
    void TotalizarCupom( String* &Retorno );
    void Pagamento( String* FormaPagamento, String* Entrada, String* QtdParcela,
      String* Parcela, String* &Retorno );
    void FecharCupom( String* Vendedor, String* Cliente, String* Telefone,
      String* &Retorno );
    void AbrirCupomVinculado( String* &Retorno );
    void ImprimirTextoTEF( TStringList* Texto, String* &Retorno );
    void FecharCupomVinculado( String* &Retorno );
    void AbrirOrcamentoConserto( String* &NumeroOrcamento, String* &Retorno );
    void LancarItemOrcamento( String* PrecoUnit, String* Codigo,
      String* Descricao, String* NumeroSerie, String* Defeito, String* &Retorno );
    void TotalizarOrcamento( String* &Retorno );
    void FecharOrcamento( String* Vendedor, String* Cliente, String* Telefone,
      String* &Retorno );
    void AbrirRecibo( String* &Retorno );
    void ImprimirRecibo( String* Vendedor, String* Cliente, String* Valor, String* Referente,
      String* &Retorno);
    void FecharRecibo( String* &Retorno );
    void ValorExtenso( String* Preco, String* ValorExtenso );
    void Finalizar( );
};
//---------------------------------------------------------------------------
#endif
