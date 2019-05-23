//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Dmod1.h"
#include "ThreadConsultaProduto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TFormPrincipal::EditCodigoProdutoKeyPress( TObject *Sender, char &Key ) {

  TThreadConsultaProduto *ConsultaProduto;

  try {
    if( ( Key == 13 ) && ( Trim( EditCodigoProduto->Text ) != "" ) ) {
      ConsultaProduto = new TThreadConsultaProduto( &( Trim( EditCodigoProduto->Text ) ),
        NULL, NULL, true );
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Produtos", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditMarcaKeyPress( TObject *Sender, char &Key ) {

  TThreadConsultaProduto *ConsultaProduto;

  try {
    if( ( Key == 13 ) && ( Trim( EditMarca->Text ) != "" ) && ( Trim( EditMarca->Text ).Length( ) >= 2 ) ) {
      ConsultaProduto = new TThreadConsultaProduto( NULL, &( Trim( EditMarca->Text ) ),
        NULL, true );
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Produtos", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditNomeProdutoKeyPress( TObject *Sender, char &Key ) {

  TThreadConsultaProduto *ConsultaProduto;

  try {
    if( ( Key == 13 ) && ( Trim( EditNomeProduto->Text ) != "" ) && ( EditNomeProduto->Text.Length( ) >= 2 ) ) {
      ConsultaProduto = new TThreadConsultaProduto( NULL, &( Trim( EditMarca->Text ) ), &( Trim( EditNomeProduto->Text ) ), true );
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Produtos", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::StringGridConsultaProdutoSelectCell(
  TObject *Sender, int ACol, int ARow, bool &CanSelect ) {

  if( ACol == 6 ) {
    this->StringGridConsultaProduto->Options << goEditing;
  }
  else {
    this->StringGridConsultaProduto->Options >> goEditing;
  }
}
//---------------------------------------------------------------------------
