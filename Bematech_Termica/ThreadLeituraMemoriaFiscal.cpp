//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadLeituraMemoriaFiscal.h"
#include "Gerencia.h"
#include "ClientSocket.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TLeituraMemoriaFiscalThread::TLeituraMemoriaFiscalThread( String* DataInicial, String* DataFinal, bool CreateSuspended ): TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;
  this->DataInicial = new AnsiString( *DataInicial );
  this->DataFinal = new AnsiString( *DataFinal );
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TLeituraMemoriaFiscalThread::~TLeituraMemoriaFiscalThread( void ) {

  delete this->DataInicial;
  delete this->DataFinal;
}
//---------------------------------------------------------------------------
void __fastcall TLeituraMemoriaFiscalThread::Execute( ) {

  TStringList *Request;
  TConsigoClientSocket *ConexaoServidor;

  try {
    FormGerencia->DesabilitarButoesFuncoesImpressora( );
    Request = new TStringList( );
    Request->Sorted = false;

    Request->Add( "IP=" + *FormPrincipal->ServerSocketIP );
    Request->Add( "Funcao=LeituraMemoriaFiscal" );
    Request->Add( "DataInicial=" + *this->DataInicial );
    Request->Add( "DataFinal=" + *this->DataFinal );

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
