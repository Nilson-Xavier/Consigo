//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DescontoProduto.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFormDescontoProduto::TFormDescontoProduto( TComponent* Owner )
  : TForm( Owner ) {

}
//---------------------------------------------------------------------------
void __fastcall TFormDescontoProduto::RadioButtonDescontoKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift ) {

  if( Key == VK_RETURN ) {
    this->RadioButtonDesconto->Checked = true;
    this->ModalResult = 1;
  }
  if( Key == VK_SPACE ) {
    this->RadioButtonDesconto->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormDescontoProduto::RadioButtonAcrescimoKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift ) {

  if( Key == VK_RETURN ) {
    this->RadioButtonAcrescimo->Checked = true;
    this->ModalResult = 1;
  }
  if( Key == VK_SPACE ) {
    this->RadioButtonDesconto->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormDescontoProduto::EditDescontoProdutoKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift ) {

  if( ( Key == VK_RETURN ) ) {
    this->ModalResult = 1;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormDescontoProduto::EditDescontoProdutoKeyPress(
      TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditDescontoProduto->Text.Length( ) <= 7 ) || ( Key == '\b' ) ) {
    if( this->EditDescontoProduto->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
    else if( this->EditDescontoProduto->Text.Length( ) >= 2 ) {
      this->EditDescontoProduto->Text = this->EditDescontoProduto->Text.Delete( this->EditDescontoProduto->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditDescontoProduto->Text.Length( ) >= 4 ) ) {
        this->EditDescontoProduto->Text = this->EditDescontoProduto->Text.Insert( ",", this->EditDescontoProduto->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditDescontoProduto->Text = this->EditDescontoProduto->Text.Insert( ",", this->EditDescontoProduto->Text.Length( ) );
      }
      this->EditDescontoProduto->SelStart = this->EditDescontoProduto->Text.Length( );
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------

