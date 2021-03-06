//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AdministracaoVisanetRedecardAmex.h"
#include "TefVisanetRedecardAmex.h"
#include "ImpressoraFiscal.h"
#include "ImpressoraMecaf.h"
#include "FormTef.h"
#include "Gerencia.h"
#include "SecaoCritica.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TTefAdmVisanet::TTefAdmVisanet( ) {

  this->Cupom = new TStringList( );
  this->Cupom->Sorted = false;
}
//---------------------------------------------------------------------------
__fastcall TTefAdmVisanet::~TTefAdmVisanet( void ) {

  delete this->Cupom;
}
//---------------------------------------------------------------------------
void TTefAdmVisanet::ExecutarAdm( String* &Retorno ) {

  TTefVisaNetRedeCardAmex *Tef;
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
    Tef = new TTefVisaNetRedeCardAmex( );
    Ok = new bool( false );

    try {
      Tef->Atv( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( "" );
      }
      *Ok = Tef->Adm( Retorno, this->Cupom );
      SetForegroundWindow( Application->Handle );
      if( ( *Ok ) && ( !this->Cupom->Text.IsEmpty( ) ) ) {
        if( Retorno->IsEmpty( ) ) {
          *Retorno = "Imprimindo Relat�rio";
        }
        FormMensagemTef->LabelMensagemTEF->Caption = *Retorno;
        FormMensagemTef->Show( );
        FormMensagemTef->Update( );
        while( ( !Retorno->IsEmpty( ) ) && ( Resposta == ID_YES ) ) {
          this->ImprimirCupomTef( Retorno );
          //Sleep( 5000 );
          //*Retorno = "";
          if( !Retorno->IsEmpty( ) ) {
            FormMensagemTef->Close( );
            Resposta = Application->MessageBox( "Impressora N�o Responde !\r\rTentar Novamente ?", "Fun��es Administrativas TEF Discado", MB_YESNO | MB_ICONQUESTION );
          }
        }
        if( ( !Retorno->IsEmpty( ) ) && ( !this->Cupom->Text.IsEmpty( ) ) ) {
          if( Tef->Ncn( Retorno ) == true ) {
            SetForegroundWindow( Application->Handle );
            Application->MessageBox( Retorno->c_str( ), "Fun��es Administrativas TEF Discado", MB_OK | MB_ICONWARNING );
            *Retorno = "";
          }
        }
        else if( ( Retorno->IsEmpty( ) ) && ( !this->Cupom->Text.IsEmpty( ) ) ) {
          SetForegroundWindow( Application->Handle );
          Tef->Cnf( Retorno );
          if( ( !Retorno->IsEmpty( ) ) && ( this->Cupom->Text != "" ) ) {
            Tef->Ncn( Retorno );
            SetForegroundWindow( Application->Handle );
          }
        }
      }
      else if( ( *Ok ) && ( this->Cupom->Text.IsEmpty( ) ) ) {
        Application->MessageBox( Retorno->c_str( ), "Fun��es Administrativas TEF Discado", MB_OK | MB_ICONWARNING );
        *Retorno = "";
      }
      else if( !( *Ok ) && ( this->Cupom->Text.IsEmpty( ) ) ) {
        Application->MessageBox( Retorno->c_str( ), "Fun��es Administrativas TEF Discado", MB_OK | MB_ICONWARNING );
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
void TTefAdmVisanet::ImprimirCupomTef( String* &Retorno ) {

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
        throw( "" );
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

  //Para Impressora Fiscal !
  /*
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
