//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Senha.h"
#include "Main.h"
#include "Gerencia.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define SENHA "naox"
#define SENHA2 "aox"
//---------------------------------------------------------------------------
__fastcall TFormPassword::TFormPassword( TComponent* Owner ) : TForm( Owner ) {

  this->Accept = new bool( false );
}
//---------------------------------------------------------------------------
__fastcall TFormPassword::~TFormPassword( ) {

  delete this->Accept;
}
//---------------------------------------------------------------------------
void __fastcall TFormPassword::EditSenhaDeAcessoKeyDown( TObject *Sender,
      WORD &Key, TShiftState Shift ) {

  if( Key == VK_RETURN ) {
    if( ( this->EditSenhaDeAcesso->Text != SENHA ) && ( this->EditSenhaDeAcesso->Text != SENHA2 ) ) {
      Application->MessageBox( "Senha Incorreta!\r\rTente Novamente.",
        "Administração - Senha de Acesso", MB_OK | MB_ICONERROR );
      this->EditSenhaDeAcesso->Clear( );
    }
    else {
      if( this->EditSenhaDeAcesso->Text == SENHA2 ) {
        *FormGerencia->SecurityFlag = true;
      }
      else {
        *FormGerencia->SecurityFlag = false;
      }
      *this->Accept = true;
      this->ModalResult = 1;
    }
  }
  if( Key == VK_ESCAPE ) {
    this->ModalResult = 1;
    *this->Accept = false;
  }
}
//---------------------------------------------------------------------------
void TFormPrincipal::SenhaExibir( bool *&Accept ) {

  TFormPassword *FormPassword;

  try {
    FormPassword = new TFormPassword( FormPrincipal );

    if( FormPassword->ShowModal( ) == 1 ) {
      *Accept = *FormPassword->Accept;
    }
  }
  __finally {
    FormPassword = NULL;
    delete FormPassword;
  }
}
//---------------------------------------------------------------------------
