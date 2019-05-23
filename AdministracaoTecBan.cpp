//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AdministracaoTecBan.h"
#include "TefTecBan.h"
#include "ImpressoraFiscal.h"
#include "ImpressoraMecaf.h"
#include "FormTef.h"
#include "Gerencia.h"
#include "SecaoCritica.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TTefAdmTecBan::TTefAdmTecBan( ) {

  this->Cupom = new TStringList( );
  this->Cupom->Sorted = false;
}
//---------------------------------------------------------------------------
__fastcall TTefAdmTecBan::~TTefAdmTecBan( ) {

  delete this->Cupom;
}
//---------------------------------------------------------------------------
void TTefAdmTecBan::ExecutarAdm( String* &Retorno ) {

  TTefTecBan *Tef;
  //TStringList *Cupom;
  TFormMensagemTef *FormMensagemTef;
  bool *Ok;
  int Resposta = ID_YES;

  try {
    while( !*FormPrincipal->TefSemaforo ) {
      //Espera !
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->TefSemaforo = false;
    SecaoCritica->Release( );

    FormMensagemTef = new TFormMensagemTef( FormGerencia );
    Tef = new TTefTecBan( );
    Ok = new bool( false );

    try {
      Tef->Atv( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( "" );
      }
      *Ok = Tef->Adm( Retorno, this->Cupom );
      SetForegroundWindow( Application->Handle );
      if( ( *Ok ) && ( !this->Cupom->Text.IsEmpty( ) ) ) {
        FormMensagemTef->LabelMensagemTEF->Caption = *Retorno;
        FormMensagemTef->Show( );
        FormMensagemTef->Update( );
        while( ( !Retorno->IsEmpty( ) ) && ( Resposta == ID_YES ) ) {
          this->ImprimirCupomTef( Retorno );
          //*Retorno = "";
          //Sleep( 5000 );
          if( !Retorno->IsEmpty( ) ) {
            FormMensagemTef->Close( );
            Resposta = Application->MessageBox( "Impressora Não Responde !\r\rTentar Novamente ?", "Funções Administrativas TEF Discado", MB_YESNO | MB_ICONQUESTION );
          }
        }
        if( ( !Retorno->IsEmpty( ) ) && ( !this->Cupom->Text.IsEmpty( ) ) ) {
          if( Tef->Ncn( Retorno ) == true ) {
            SetForegroundWindow( Application->Handle );
            Application->MessageBox( Retorno->c_str( ), "Funções Administrativas TEF Discado", MB_OK | MB_ICONWARNING );
            *Retorno = "";
          }
        }
        else if( ( Retorno->IsEmpty( ) ) && ( !this->Cupom->Text.IsEmpty( ) ) ) {
          Tef->Cnf( Retorno );
          SetForegroundWindow( Application->Handle );
          if( ( !Retorno->IsEmpty( ) ) && ( this->Cupom->Text != "" ) ) {
            Tef->Ncn( Retorno );
            SetForegroundWindow( Application->Handle );
          }
        }
      }
      else if( ( *Ok ) && ( this->Cupom->Text.IsEmpty( ) ) ) {
        Application->MessageBox( Retorno->c_str( ), "Funções Administrativas TEF Discado", MB_OK | MB_ICONWARNING );
        *Retorno = "";
      }
      else if( !( *Ok ) && ( this->Cupom->Text.IsEmpty( ) ) ) {
        Application->MessageBox( Retorno->c_str( ), "Funções Administrativas TEF Discado", MB_OK | MB_ICONWARNING );
      }
    }
    catch( ... ) {

    }
  }
  __finally {
    delete FormMensagemTef;
    delete Tef;
    delete Ok;

    SecaoCritica->Acquire( );
    *FormPrincipal->TefSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TTefAdmTecBan::ImprimirCupomTef( String* &Retorno ) {

  //TImpressoraFiscal *ImpressoraEcf;
  String *Relatorio, *Expandido;
  int i, j;
  TImpressoraMecaf *ImpressoraMecaf;

  try {
    while( !*FormPrincipal->ImpressoraMecafSemaforo ) {
      //Espera !
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraMecaf = new TImpressoraMecaf( );
    ImpressoraMecaf->CarregarDll( Retorno );

    try {
      *Retorno = "";
      ImpressoraMecaf->Iniciar( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( "" );
      }
      this->Cupom->Add( "\x0A" );
      this->Cupom->Add( "\x0A" );
      this->Cupom->Add( "\x0A" );
      this->Cupom->Add( "\x0A" );
      this->Cupom->Add( "\x0A" );
      this->Cupom->Add( "\x0A" );
      this->Cupom->Add( "\x0A" );
      ImpressoraMecaf->ImprimirTextoTEF( this->Cupom, Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
    }
    catch( ... ) {

    }
  }
  __finally {
    ImpressoraMecaf->Finalizar( );
    delete ImpressoraMecaf;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = true;
    SecaoCritica->Release( );
  }

  /*
  // Para Impressora Fiscal !
  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      //Espera !
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    ImpressoraEcf = new TImpressoraFiscal( );
    Relatorio = new AnsiString( "1" );
    Expandido = new AnsiString( "0" );

    try {
      ImpressoraEcf->CarregaDll( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( "" );
      }
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( "" );
        }
      }
      ImpressoraEcf->LeituraX( Relatorio, Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( "" );
      }
      for( j = 0; j < 2; j++ ) {
        for( i = 0; i < this->Cupom->Count; i++ ) {
          ImpressoraEcf->LancaItemNaoFiscal( Expandido, &( this->Cupom->Strings[i] ), Retorno );
          if( !Retorno->IsEmpty( ) ) {
            throw( "" );
          }
        }
      }
      ImpressoraEcf->FechaCupomNaoFiscal( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( "" );
      }
    }
    catch( ... ) {

    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;
    delete Relatorio;
    delete Expandido;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
  */
}
//---------------------------------------------------------------------------
