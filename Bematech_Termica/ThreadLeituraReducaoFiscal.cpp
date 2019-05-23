//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadLeituraReducaoFiscal.h"
#include "Gerencia.h"
#include "ClientSocket.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TLeituraReducaoFiscalThread::TLeituraReducaoFiscalThread( String* ReducaoInicial, String* ReducaoFinal, bool CreateSuspended ): TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;
  this->ReducaoInicial = new AnsiString( *ReducaoInicial );
  this->ReducaoFinal = new AnsiString( *ReducaoFinal );
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TLeituraReducaoFiscalThread::~TLeituraReducaoFiscalThread( void ) {

  delete this->ReducaoInicial;
  delete this->ReducaoFinal;
}
//---------------------------------------------------------------------------
void __fastcall TLeituraReducaoFiscalThread::Execute( ) {

  TStringList *Request;
  TConsigoClientSocket *ConexaoServidor;

  try {
    FormGerencia->DesabilitarButoesFuncoesImpressora( );
    Request = new TStringList( );
    Request->Sorted = false;

    Request->Add( "IP=" + *FormPrincipal->ServerSocketIP );
    Request->Add( "Funcao=LeituraMemoriaFiscal" );
    Request->Add( "ReducaoInicial=" + *this->ReducaoInicial );
    Request->Add( "ReducaoFinal=" + *this->ReducaoFinal );

    ConexaoServidor = new TConsigoClientSocket( Application, Request, FormPrincipal->ServerSocketIP );
  }
  __finally {
    if( ConexaoServidor != NULL ) {
      delete ConexaoServidor;
    }
    delete Request;
    FormGerencia->AbilitarButoesFuncoesImpressora( );
  }
}
//---------------------------------------------------------------------------
 