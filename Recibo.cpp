//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Recibo.h"
#include "ImpressoraMecaf.h"
#include "Main.h"
#include "SecaoCritica.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TRecibo::TRecibo( TStringList* ReciboInfo ) {

  this->ReciboInfo = new TStringList( );
  this->ReciboInfo->Assign( ReciboInfo );
  this->Vendedor = new AnsiString( ReciboInfo->Values["Vendedor"] );
  this->Cliente = new AnsiString( ReciboInfo->Values["Cliente"] );
  this->Valor = new AnsiString( ReciboInfo->Values["Preco"] );
  this->Referente = new AnsiString( StringReplace( ReciboInfo->Values["Referente"], "||", "\r\n", TReplaceFlags( ) << rfReplaceAll ) );
}
//---------------------------------------------------------------------------
__fastcall TRecibo::~TRecibo( void ) {

  delete this->Vendedor;
  delete this->Cliente;
  delete this->Valor;
  delete this->Referente;
}
//---------------------------------------------------------------------------
void TRecibo::Imprimir( String* &Retorno ) {

  TImpressoraMecaf *Impressora;

  try {
    while( !*FormPrincipal->ImpressoraMecafSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = false;
    SecaoCritica->Release( );

    Impressora = new TImpressoraMecaf( );
    Impressora->CarregarDll( Retorno );

    try {
      *Retorno = "";
      Impressora->Iniciar( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      Impressora->AbrirRecibo( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      Impressora->ImprimirRecibo( this->Vendedor, this->Cliente, this->Valor,
                                  this->Referente, Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      Impressora->FecharRecibo( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    Impressora->Finalizar( );
    delete Impressora;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
