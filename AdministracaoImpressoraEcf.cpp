//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AdministracaoImpressoraEcf.h"
#include "ImpressoraFiscal.h"
#include "Main.h"
#include "SecaoCritica.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TAdministracaoImpressoraEcf::TAdministracaoImpressoraEcf( ) {

}
//---------------------------------------------------------------------------
__fastcall TAdministracaoImpressoraEcf::~TAdministracaoImpressoraEcf( void ) {

}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::LeituraX( String* &Retorno ) {

  TImpressoraFiscal *ImpressoraEcf;
  String *Relatorio;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    Relatorio = new AnsiString( "0" );
    ImpressoraEcf = new TImpressoraFiscal( );

    try {
      ImpressoraEcf->CarregaDll( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
      }
      ImpressoraEcf->LeituraX( Relatorio, Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;
    delete Relatorio;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::ReducaoZ( String* &Retorno ) {

  TImpressoraFiscal *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscal( );

    try {
      ImpressoraEcf->CarregaDll( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
      }
      ImpressoraEcf->ReducaoZ( Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::LeituraMemoriaFiscal( String* DataInicial, String* DataFinal, String* &Retorno ) {

  TImpressoraFiscal *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscal( );

    try {
      ImpressoraEcf->CarregaDll( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
      }
      ImpressoraEcf->LeituraMemoriaFiscal( DataInicial, DataFinal, Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::LeituraReducaoFiscal( String* ReducaoInicial, String* ReducaoFinal, String* &Retorno ) {

  TImpressoraFiscal *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscal( );

    try {
      ImpressoraEcf->CarregaDll( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
      }
      ImpressoraEcf->LeituraReducaoFiscal( ReducaoInicial, ReducaoFinal, Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::CancelarCupom( String* &Retorno ) {

  TImpressoraFiscal *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscal( );

    try {
      ImpressoraEcf->CarregaDll( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
      }
      ImpressoraEcf->CancelaCupom( Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
