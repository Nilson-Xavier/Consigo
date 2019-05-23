//---------------------------------------------------------------------------
#ifndef VendaH
#define VendaH
//---------------------------------------------------------------------------
#include "ServerSocket.h"
//---------------------------------------------------------------------------
class TVenda : public TObject {

	private:
    TStringList *VendaInfo;
    TStringList *CupomTef;
    String *NumeroCupom;
    String *NomeCliente;
    String *Telefone;

    void ImprimirVendaFiscal( String* &Retorno );
    void ImprimirVenda( String* &Retorno );
    void ImprimirEcfCupomTef( bool *LeituraX, String* &Retorno );
    void ImprimirCupomTef( String* Cupom, String* Total, String* &Retorno );
    void InserirVendaFiscal( String* &Retorno );
    void InserirVenda( String* &Retorno );
    void ConsultarCheque( String* &Retorno );
    void ExecutarTef( String* &Retorno );
    void CapturarFormaPagamento( String* &Modo, String* &Valor );
    void BufferTefCopiar( String* &Retorno );
    void BufferTefApagar( String* &Retorno );
    void CloseScreenSaver( void );
  public:
    __fastcall TVenda( TStringList* VendaInfo );
    __fastcall ~TVenda( void );
    void RealizarVenda( String* &Retorno );
};
//---------------------------------------------------------------------------
#endif
