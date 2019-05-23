//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include "ThreadGerarArquivoRfd.h"
#include "AdministracaoImpressoraEcf.h"
#include "Gerencia.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TThreadGerarArquivoRfd::TThreadGerarArquivoRfd( String *Data,
    String *CaminhoDaPastaDestino, bool CreateSuspended ): TThread( CreateSuspended ) {

  this->Data = new AnsiString( *Data );
  this->CaminhoDaPastaDestino = new AnsiString( *CaminhoDaPastaDestino );
  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TThreadGerarArquivoRfd::~TThreadGerarArquivoRfd( void ) {

  delete this->Data;
  delete this->CaminhoDaPastaDestino;
}
//---------------------------------------------------------------------------
void __fastcall TThreadGerarArquivoRfd::Execute( ) {

  TAdministracaoImpressoraEcf *AdmImpressora;
  String *Erro;

  try {
    FormGerencia->DesabilitarButoesFuncoesImpressora( );
    AdmImpressora = new TAdministracaoImpressoraEcf( );
    Erro = new AnsiString( );

    AdmImpressora->GerarArquivoRfd( this->Data, this->CaminhoDaPastaDestino, Erro );
    if( !Erro->IsEmpty( ) ) {
      Application->MessageBox( Erro->c_str( ), "Gerência - Impressora", MB_OK | MB_ICONERROR );
    }

  }
  __finally {
    delete AdmImpressora;
    delete Erro;
    FormGerencia->AbilitarButoesFuncoesImpressora( );
  }
}
//---------------------------------------------------------------------------
