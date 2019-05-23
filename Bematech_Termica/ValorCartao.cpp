//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ValorCartao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFormValorCartao::TFormValorCartao( TComponent* Owner ) : TForm( Owner ) {

}
//---------------------------------------------------------------------------
__fastcall TFormValorCartao::~TFormValorCartao( ) {

}
//---------------------------------------------------------------------------
void __fastcall TFormValorCartao::EditValorCartaoKeyPress( TObject *Sender, char &Key ) {

  DecimalSeparator = ',';
  ThousandSeparator = '.';
  if( ( Key == 13 ) && ( !this->EditValorCartao->Text.IsEmpty( ) ) ){
    if( StrToFloat( StringReplace( EditValorCartao->Text, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) ) {
    	this->ModalResult = 1;
    }
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditValorCartao->Text.Length( ) <= 7 ) || ( Key == '\b' ) ) {
    if( this->EditValorCartao->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
    else if( this->EditValorCartao->Text.Length( ) >= 2 ) {
      this->EditValorCartao->Text = this->EditValorCartao->Text.Delete( this->EditValorCartao->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditValorCartao->Text.Length( ) >= 4 ) ) {
        this->EditValorCartao->Text = this->EditValorCartao->Text.Insert( ",", this->EditValorCartao->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditValorCartao->Text = this->EditValorCartao->Text.Insert( ",", this->EditValorCartao->Text.Length( ) );
      }
      this->EditValorCartao->SelStart = this->EditValorCartao->Text.Length( );
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
