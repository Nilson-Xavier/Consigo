//---------------------------------------------------------------------------
#ifndef ThreadVendaServidorH
#define ThreadVendaServidorH
//---------------------------------------------------------------------------
#include "ServerSocket.h"
#include "FormaPagamento.h"
//---------------------------------------------------------------------------
class TVendaServidorThread : public TThread {

	private:
    TStringList *VendaInfo;
    TStringList *CupomTef;
    String *NumeroCupom;
    String *NomeCliente;
    String *CpfCnpjCliente;
    String *Telefone;
    String *FormaPagamento;
    String *ValorPagamento;
    TFormFormaPagamento *FormFormaPagamento;

    void ImprimirVendaFiscal( );
    void ImprimirVenda( );
    void ImprimirEcfCupomTef( bool *LeituraX );
    void ImprimirCupomTef( String* Cupom, String* Total );
    void InserirVendaFiscal( );
    void InserirVenda( );
    void ConsultarCheque( );
    void BufferTefCopiar( );
    void BufferTefApagar( );
    void __fastcall CloseScreenSaver( void );
    void __fastcall ExecutarTef( );
    void __fastcall CapturarFormaPagamento( );
    void __fastcall Execute( void );

  public:
    String *Erro;

    __fastcall TVendaServidorThread::TVendaServidorThread( bool CreateSuspended, TStringList *VendaInfo );
    __fastcall ~TVendaServidorThread( void );
};
//---------------------------------------------------------------------------
#endif
