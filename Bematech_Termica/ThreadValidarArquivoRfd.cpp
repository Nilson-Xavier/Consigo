//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include "ThreadValidarArquivoRfd.h"
#include "AdministracaoImpressoraEcf.h"
#include "Gerencia.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TThreadValidarArquivoRfd::TThreadValidarArquivoRfd( String *CaminhoDoArquivo,
  bool CreateSuspended ): TThread( CreateSuspended ) {

  this->CaminhoDoArquivo = new AnsiString( *CaminhoDoArquivo );
  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TThreadValidarArquivoRfd::~TThreadValidarArquivoRfd( void ) {

  delete this->CaminhoDoArquivo;
}
//---------------------------------------------------------------------------
void __fastcall TThreadValidarArquivoRfd::Execute( ) {

  TAdministracaoImpressoraEcf *AdmImpressora;
  String *Erro, *Md5;

  try {
    FormGerencia->DesabilitarButoesFuncoesImpressora( );
    AdmImpressora = new TAdministracaoImpressoraEcf( );
    Erro = new AnsiString( );
    Md5 = new AnsiString( );

    AdmImpressora->ValidarArquivoRfd( this->CaminhoDoArquivo, Md5, Erro );
    if( !Erro->IsEmpty( ) ) {
      Application->MessageBox( Erro->c_str( ), "Gerência - Impressora", MB_OK | MB_ICONERROR );
    }
    else{
      *Md5 = "Validacao do Arquivo OK !\r\rCodigo de Controle MD5: " + *Md5;
      Application->MessageBox(  Md5->c_str( ), "Gerência - Impressora", MB_OK | MB_ICONWARNING );
    }

  }
  __finally {
    delete AdmImpressora;
    delete Erro;
    delete Md5;
    FormGerencia->AbilitarButoesFuncoesImpressora( );
  }
}
//---------------------------------------------------------------------------
