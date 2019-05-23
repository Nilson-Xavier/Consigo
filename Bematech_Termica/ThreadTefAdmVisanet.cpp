//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadTefAdmVisanet.h"
#include "ClientSocket.h"
#include "Gerencia.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TTefAdmVisanetThread::TTefAdmVisanetThread( bool CreateSuspended ): TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TTefAdmVisanetThread::~TTefAdmVisanetThread( void ) {


}
//---------------------------------------------------------------------------
void __fastcall TTefAdmVisanetThread::Execute( ) {

  TStringList *Request;
  TConsigoClientSocket *ConexaoServidor;

  try {
    FormGerencia->BitBtnAdministracaoTefVisanet->Enabled = false;
    FormGerencia->BitBtnAdministracaoTefTecBan->Enabled = false;
    FormGerencia->BitBtnConsultarCheque->Enabled = false;

    Request = new TStringList( );
    Request->Sorted = false;

    Request->Add( "IP=" + *FormPrincipal->ServerSocketIP );
    Request->Add( "Funcao=AdmVisanet" );

    ConexaoServidor = new TConsigoClientSocket( Application, Request, FormPrincipal->ServerSocketIP );
  }
  __finally {
    if( ConexaoServidor != NULL ) {
      delete ConexaoServidor;
    }
    delete Request;

    FormGerencia->BitBtnAdministracaoTefVisanet->Enabled = true;
    FormGerencia->BitBtnAdministracaoTefTecBan->Enabled = true;
    FormGerencia->BitBtnConsultarCheque->Enabled = true;
  }
}
//---------------------------------------------------------------------------
