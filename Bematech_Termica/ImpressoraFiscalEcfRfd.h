//---------------------------------------------------------------------------
#include <vcl\StrUtils.hpp>

#ifndef ImpressoraFiscalEcfRfdH
#define ImpressoraFiscalEcfRfdH

// Funções da impressora PROCOMP

typedef int ( far pascal *OPENCIF ) ( void );
typedef int ( far pascal *CLOSECIF ) ( void );
typedef int ( far pascal *ESPERARESPOSTA ) ( char* );
typedef int ( far pascal *ABRECUPOM ) ( char*, char* );
typedef int ( far pascal *VENDA ) ( char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char* );
typedef int ( far pascal *CANCELAMENTO ) ( char* );
typedef int ( far pascal *TOTALIZA ) ( void );
typedef int ( far pascal *PGTO ) ( char*, char*, char* );
typedef int ( far pascal *FECHACUPOM ) ( char*, char* );
typedef int ( far pascal *CANCELACUPOM ) ( void );
typedef int ( far pascal *LEITURAX ) ( char* );
typedef int ( far pascal *REDUCAOZ ) ( char* );
typedef int ( far pascal *ABRECUPV ) ( void );
typedef int ( far pascal *ABRECUPNV ) ( void );
typedef int ( far pascal *IMPLIN ) ( char*, char* );
typedef int ( far pascal *IMPLINTEXTO ) ( char*, char* );
typedef int ( far pascal *ENCCUPOM ) ( void );
typedef int ( far pascal *ESPERARESPOSTA ) ( char* );
typedef int ( far pascal *TXPARECF ) ( char* );
typedef int ( far pascal *GerarArquivoRFD ) ( char*, char* );
typedef int ( far pascal *ValidarArquivoRFD ) ( char*, char*, int );

//---------------------------------------------------------------------------
class TImpressoraFiscalRfd : public TObject {
  private:
    HINSTANCE iHandleDll;
    OPENCIF OpenCif;
    CLOSECIF CloseCif;
    ABRECUPOM AbreCupomFiscalCpfCnpjNome;
    ESPERARESPOSTA RespostaComando;
    VENDA VendaItem;
    CANCELAMENTO CancelamentoItem;
    TOTALIZA TotCupomSemDescAcres;
    PGTO Pgto;
    FECHACUPOM FechaCupom;
    CANCELACUPOM CancelaCupomFiscal;
    LEITURAX PLeituraX;
    REDUCAOZ PReducaoZ;
    ABRECUPV AbreCupomVinculado;
    ABRECUPNV AbreCupomNaoVinculado;
    IMPLIN ImprimeLinhaNaoFiscal;
    IMPLINTEXTO ImprimeTextoNaoFiscal;
    ENCCUPOM EncerraCupomNaoFiscal;
    ESPERARESPOSTA EsperaResposta;
    TXPARECF ObterParEcf;
    GerarArquivoRFD pGerarArquivoRfd;
    ValidarArquivoRFD pValidarArquivoRfd;

    String ObterMensagemRetorno( int CodigoRetornoComando );
    bool TImpressoraFiscalRfd::ObterRespostaComando( String *Erro );

  public:
    __fastcall TImpressoraFiscalRfd( void );
    __fastcall ~TImpressoraFiscalRfd( void );

    bool AbrirCoxexaoSerial( String *Erro );
    void __fastcall FecharConexaoSerial( );
    bool AbrirCupomFiscal( String *CpfCnpj, String *Nome, String *Erro );
    bool LancarItemFiscal( String *Qtd, String *PrecoUnit, String *TaxaImposto, String *Codigo,
                          String *DescricaoProduto, String *Erro );
    bool CancelarItem( int IndexItem, String *Erro );
    bool TotalizarCupom( String *Erro );
    bool Pagamento( String *ModoPagamento, String *VPgto, String *Erro );
    bool FecharCupomFiscal( String *Vendedor, String *Erro );
    bool CancelarCupomFiscal( String *Erro );
    bool LeituraX( String *Erro );
    bool ReducaoZ( String *Erro );
    bool AbrirCupomNaoFiscalVinculado( String *Erro );
    bool AbrirCupomNaoFiscalNaoVinculado( String *Erro );
    bool ImprimirLinhaNaoFiscal( String *Texto, String *Erro );
    bool ImprimirTextoNaoFiscal( String *Texto, String *Erro );
    bool FecharCupomNaoFiscal( String *Erro );
    bool ObterNumeroUltimoCupomFiscal( int &UltimoCupom, String *Erro );
    bool GerarArquivoRfd( String *Data, String *CaminhoDaPastaDestino, String *Erro );
    bool ValidarArquivoRfd( String *CaminhoDoArquivo, String *RetornoMd5, String *Erro );
};
//---------------------------------------------------------------------------
#endif
