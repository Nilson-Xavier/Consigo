//---------------------------------------------------------------------------
#ifndef ImpressoraFiscalH
#define ImpressoraFiscalH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Sysutils.hpp>
#include <vcl\Windows.hpp>
#include <dstring.h>
//---------------------------------------------------------------------------
// Funções da impressora PROCOMP

// Abre a COM
typedef int ( far pascal *OPENCIF ) ( void );
// Fecha a COM
typedef int ( far pascal *CLOSECIF ) ( void );
// Abre um cupom fiscal
typedef int ( far pascal *ABRECUPOMFISCAL ) ( void );
// Lanca um item no cupom fiscal
typedef int ( far pascal *VENDAITEM ) ( char *, char *, char *, char *, char *,
                                        char *, char *, char *, char *, char *,
                                        char * );
// Cancelamento de item
typedef int ( far pascal *CANCELAMENTOITEM ) ( char * );
// Totalização do cupom
typedef int ( far pascal *TOTALIZARCUPOM ) ( PChar pOper, char *, char *, char * );
// Forma de pagamento
typedef int ( far pascal *PAGAMENTO ) ( char *, char *, char * );
// Fecha cupom fiscal
typedef int ( far pascal *FECHACUPOMFISCAL ) ( char *, char * );
// Cancela cupom fiscal
typedef int ( far pascal *CANCELACUPOMFISCAL ) ( void );
// Leitura X
typedef int ( far pascal *LEITURAX ) ( char * );
// Reducao Z
typedef int ( far pascal *REDUCAOZ ) ( char * );
// Leitura de memória fiscal por data
typedef int ( far pascal *LEMEMFISCALDATA ) ( char *, char *, char * );
// Leitura de memória fiscal por redução
typedef int ( far pascal *LEMEMFISCALREDUCAO ) ( char *, char *, char * );
// Abertura de cupom não fiscal não vinculado
typedef int ( far pascal *ABRECUPOMNAOVINCULADO ) ( void );
// Abertura de cupom não fiscal vinculado
typedef int ( far pascal *ABRECUPOMVINCULADO ) ( void );
// Encerra cupom não fiscal
typedef int ( far pascal *ENCERRARCUPOM ) ( void );
// Imprime linha não fiscal
typedef int ( far pascal *IMPRIMELINHANAOFISCAL ) ( char *, char * );
// Transmissao de status
typedef int ( far pascal *TRANSSTATUS ) ( int , char * );
// Obtem retorno
typedef int ( far pascal *OBTEMRETORNO ) ( char * );
// Parâmetros especificos da ECF
typedef int ( far pascal *ECFPARESP ) ( char * );
// Avança Linha
typedef int ( far pascal *AVANCALINHA ) ( void );
// Programa os Modos de Pagamento ( Dinheiro, Cheque, ... )
typedef int ( far pascal *PROGRAMALEGENDA ) ( char *, char * );

class TImpressoraFiscal : public TObject {
  private:
    OPENCIF PCAbre;
    CLOSECIF PCFecha;
    ABRECUPOMFISCAL PCAbreCupom;
    VENDAITEM PCLancaItem;
    CANCELAMENTOITEM PCCancItem;
    TOTALIZARCUPOM PCTotalCupom;
    PAGAMENTO PCPagamento;
    FECHACUPOMFISCAL PCFechaCupom;
    CANCELACUPOMFISCAL PCCancelaCupom;
    LEITURAX PCLeituraX;
    REDUCAOZ PCReducaoZ;
    LEMEMFISCALDATA PCLerData;
    LEMEMFISCALREDUCAO PCLerReducao;
    ABRECUPOMNAOVINCULADO PCAbreNaoFiscal;
    ABRECUPOMVINCULADO PCAbreNaoFiscalVinculado;
    ENCERRARCUPOM PCEncerraNaoFiscal;
    IMPRIMELINHANAOFISCAL PCImprimeNaoFiscal;
    TRANSSTATUS PCTransStatus;
    OBTEMRETORNO PCObtemRetorno;
    ECFPARESP PCEcfParEsp;
    AVANCALINHA PCAvancaLinha;
    PROGRAMALEGENDA PCProgLegenda;
  public:
    void CarregaDll( String* &Retorno );
    void AbreSerial( );
    void FechaSerial( );
    void AbreCupom( String* &Retorno );
    void AbreCupomNaoFiscal( String* &Retorno );
    void AbreCupomNaoFiscalVinculado( String* &Retorno );
    void FechaCupom( String* Vendedor, String* &Retorno );
    void FechaCupomNaoFiscal( String* &Retorno );
    void LancaItem( String* sQtde, String* sPrecoUnit, String* sCodigo,
                    String* sDescricao, String* &Retorno );
    void LancaItemNaoFiscal( String* pAtrib, String* pString, String* &Retorno );
    void TotalizaCupom( String* &Retorno );
    void Pagamento( String* Reg, String* VPgto, String* Subtr, String* &Retorno );
    void CancelaCupom( String* &Retorno );
    void PulaLinha( String* &Retorno );
    void LeituraX( String* Relatorio, String* &Retorno );
    void ReducaoZ( String* &Retorno );
    void LeituraMemoriaFiscal( String* DataInic, String* DataFinal, String* &Retorno );
    void LeituraReducaoFiscal( String* RedInic, String* RedFin, String* &Retorno );
    void UltimoCupomFiscal( int &Cupom, String* &Retorno );
    void ProgramarLegenda( String* &Retorno );
    void ObterStatus( String* &Retorno );
    bool ObterStatusBit( int Bit );
    void LeProComp( int iRetorno, Boolean lProcessaRet, String* &Retorno );
    void MensagemProComp( int iRetorno, String* &Retorno );
  };
//---------------------------------------------------------------------------
#endif
