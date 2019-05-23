//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FormaPagamento.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFormaPagamento *FormFormaPagamento;
//---------------------------------------------------------------------------
__fastcall TFormFormaPagamento::TFormFormaPagamento( TComponent* Owner ) : TForm( Owner ) {

  this->Height = 130;
}
//---------------------------------------------------------------------------
__fastcall TFormFormaPagamento::~TFormFormaPagamento( ) {


}
//---------------------------------------------------------------------------
void __fastcall TFormFormaPagamento::EditValorFormaPagamentoKeyPress( TObject *Sender, char &Key ) {

  DecimalSeparator = ',';
  ThousandSeparator = '.';
  if( ( Key == 13 ) && ( !this->EditValorFormaPagamento->Text.IsEmpty( ) ) ) {
    if( StrToFloat( EditValorFormaPagamento->Text ) != 0 ) {
    	this->ModalResult = 1;
    }
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) &&
      ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditValorFormaPagamento->Text.Length( ) <= 7 ) ) {
    if( this->EditValorFormaPagamento->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
    else if( this->EditValorFormaPagamento->Text.Length( ) >= 2 ) {
      this->EditValorFormaPagamento->Text = this->EditValorFormaPagamento->Text.Delete( this->EditValorFormaPagamento->Text.Pos( "," ), 1 );
      this->EditValorFormaPagamento->Text = this->EditValorFormaPagamento->Text.Insert( ",", this->EditValorFormaPagamento->Text.Length( ) );
      this->EditValorFormaPagamento->SelStart = this->EditValorFormaPagamento->Text.Length( );
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormFormaPagamento::ComboBoxFormaPagamentoKeyDown( TObject *Sender, WORD &Key, TShiftState Shift ) {

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( !ComboBoxFormaPagamento->DroppedDown ) ) {
  	ComboBoxFormaPagamento->DroppedDown = true;
  }
  if( ( ComboBoxFormaPagamento->Text == "Cartao Debito" ) ||
      ( ComboBoxFormaPagamento->Text == "Cartao Credito" ) ||
      ( ComboBoxFormaPagamento->Text == "Cheque Eletronico" ) ||
      ( ComboBoxFormaPagamento->Items->Strings[ComboBoxFormaPagamento->ItemIndex] == "Cartao Debito" ) ||
      ( ComboBoxFormaPagamento->Items->Strings[ComboBoxFormaPagamento->ItemIndex] == "Cartao Credito" ) ||
      ( ComboBoxFormaPagamento->Items->Strings[ComboBoxFormaPagamento->ItemIndex] == "Cheque Eletronico" ) ) {
    this->LabelFormaPagamento3->Visible = true;
    this->LabelFormaPagamento4->Visible = true;
    this->EditValorFormaPagamento->Visible = true;
    this->Height = 210;
  }
  else {
    this->LabelFormaPagamento3->Visible = false;
    this->LabelFormaPagamento4->Visible = false;
    this->EditValorFormaPagamento->Visible = false;
    this->Height = 130;
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxFormaPagamento->Text.IsEmpty( ) ) && ( ( ComboBoxFormaPagamento->Text == "Dinheiro" ) ||
      ( ComboBoxFormaPagamento->Text == "Cheque" ) ) ) {
    this->ModalResult = 1;
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxFormaPagamento->Text.IsEmpty( ) ) && ( ( ComboBoxFormaPagamento->Text != "Dinheiro" ) &&
      ( ComboBoxFormaPagamento->Text != "Cheque" ) ) ) {
    this->EditValorFormaPagamento->SetFocus( );
  }
}
//---------------------------------------------------------------------------
