//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FormTef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFormMensagemTef::TFormMensagemTef( TComponent* Owner ) : TForm( Owner ) {

}
//---------------------------------------------------------------------------
__fastcall TFormMensagemTef::~TFormMensagemTef( void ) {

  if( this->Visible ) {
    this->Close( );
  }
}
//---------------------------------------------------------------------------
