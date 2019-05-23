//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadCancelamentoCupom.h"
#include "Gerencia.h"
#include "ClientSocket.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TCancelamentoCupomThread::TCancelamentoCupomThread( bool CreateSuspended ): TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TCancelamentoCupomThread::~TCancelamentoCupomThread( void ) {


}
//---------------------------------------------------------------------------
void __fastcall TCancelamentoCupomThread::Execute( ) {

  TStringList *Request;
  TConsigoClientSocket *ConexaoServidor;

  try {
    FormGerencia->BtnLeituraX->Enabled = false;
    FormGerencia->BtnReducaoZ->Enabled = false;
    FormGerencia->BitBtnLeituraMemoriaFiscalData->Enabled = false;
    FormGerencia->BitBtnLeituraMemoriaFiscalReducao->Enabled = false;
    FormGerencia->BitBtnCancelarCupom->Enabled = false;

    Request = new TStringList( );
    Request->Sorted = false;

    Request->Add( "IP=" + *FormPrincipal->ServerSocketIP );
    Request->Add( "Funcao=CancelarCupom" );

    ConexaoServidor = new TConsigoClientSocket( Application, Request, FormPrincipal->ServerSocketIP );
  }
  __finally {
    if( ConexaoServidor != NULL ) {
      delete ConexaoServidor;
    }
    delete Request;

    FormGerencia->BtnLeituraX->Enabled = true;
    FormGerencia->BtnReducaoZ->Enabled = true;
    FormGerencia->BitBtnLeituraMemoriaFiscalData->Enabled = true;
    FormGerencia->BitBtnLeituraMemoriaFiscalReducao->Enabled = true;
    FormGerencia->BitBtnCancelarCupom->Enabled = true;
  }
}
//---------------------------------------------------------------------------