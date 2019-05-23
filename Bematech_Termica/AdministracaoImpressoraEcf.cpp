//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AdministracaoImpressoraEcf.h"
#include "ImpressoraFiscalBematech.h"
#include "ImpressoraFiscalEcfRfd.h"
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

  //TImpressoraFiscalRfd *ImpressoraEcf;
  TImpressoraFiscalBematech *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscalBematech( );

    try {
      /*
      if( !ImpressoraEcf->AbrirCoxexaoSerial( Retorno ) ) {
        throw( *Retorno );
      }
      */
      if( !ImpressoraEcf->LeituraX( Retorno ) ) {
        throw( *Retorno );
      }
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    //ImpressoraEcf->FecharConexaoSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::ReducaoZ( String* &Retorno ) {

  //TImpressoraFiscalRfd *ImpressoraEcf;
  TImpressoraFiscalBematech *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscalBematech( );

    try {
      /*
      if( !ImpressoraEcf->AbrirCoxexaoSerial( Retorno ) ) {
        throw( *Retorno );
      }
      */
      if( !ImpressoraEcf->ReducaoZ( Retorno ) ) {
        throw( *Retorno );
      }
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    //ImpressoraEcf->FecharConexaoSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::LeituraMemoriaFiscal( String* DataInicial, String* DataFinal, String* &Retorno ) {

  TImpressoraFiscalRfd *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscalRfd( );

    try {
      if( !ImpressoraEcf->AbrirCoxexaoSerial( Retorno ) ) {
        throw( *Retorno );
      }
//**  ImpressoraEcf->LeituraMemoriaFiscal( DataInicial, DataFinal, Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FecharConexaoSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::LeituraReducaoFiscal( String* ReducaoInicial, String* ReducaoFinal, String* &Retorno ) {

  TImpressoraFiscalRfd *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscalRfd( );

    try {
      if( !ImpressoraEcf->AbrirCoxexaoSerial( Retorno ) ) {
        throw( *Retorno );
      }
//**  ImpressoraEcf->LeituraReducaoFiscal( ReducaoInicial, ReducaoFinal, Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FecharConexaoSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::CancelarCupom( String* &Retorno ) {

  //TImpressoraFiscalRfd *ImpressoraEcf;
  TImpressoraFiscalBematech *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscalBematech( );

    try {
      /*
      if( !ImpressoraEcf->AbrirCoxexaoSerial( Retorno ) ) {
        throw( *Retorno );
      }
      */
      ImpressoraEcf->CancelarCupomFiscal( Retorno );
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    //ImpressoraEcf->FecharConexaoSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::GerarArquivoRfd( String *Data, String *CaminhoDoArquivo, String* Retorno ) {

  TImpressoraFiscalBematech *ImpressoraEcf;
  
  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscalBematech( );

    try {
      /*
      if( !ImpressoraEcf->AbrirCoxexaoSerial( Retorno ) ) {
        throw( *Retorno );
      }
      */
      if( !ImpressoraEcf->GerarArquivoRfd( CaminhoDoArquivo, Data, Retorno ) ) {
        throw( *Retorno );
      }
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
//  ImpressoraEcf->FecharConexaoSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TAdministracaoImpressoraEcf::ValidarArquivoRfd( String *CaminhoDoArquivo, String *RetornoMd5, String *Retorno ) {

  TImpressoraFiscalRfd *ImpressoraEcf;

  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscalRfd( );

    try {
      if( !ImpressoraEcf->AbrirCoxexaoSerial( Retorno ) ) {
        throw( *Retorno );
      }
      if( !ImpressoraEcf->ValidarArquivoRfd( CaminhoDoArquivo, RetornoMd5, Retorno ) ) {
        throw( *Retorno );
      }
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FecharConexaoSerial( );
    delete ImpressoraEcf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
