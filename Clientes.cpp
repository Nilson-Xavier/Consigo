//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Dmod1.h"
#include "ThreadConsultaCliente.h"
#include "CadastroCliente.h"
#include "InformacaoAdicionalCliente.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditNomeClienteKeyPress( TObject *Sender, char &Key ) {

  TThreadConsultaCliente *ConsultaCliente;

  try {
    if( ( Key == 13 ) && ( Trim( EditNomeCliente->Text ) != "" ) && ( Trim( EditNomeCliente->Text ).Length( ) >= 3 ) ) {
      ConsultaCliente = new TThreadConsultaCliente( &( Trim( EditNomeCliente->Text ) ), NULL, NULL,
        NULL, NULL, true );
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Clientes", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditRgCnpjKeyPress( TObject *Sender, char &Key ) {

  TThreadConsultaCliente *ConsultaCliente;

  try {
    if( ( Key == 13 ) && ( !Trim( EditRgCnpj->Text ).IsEmpty( ) ) &&
        ( !ComboBoxEERG2->Text.IsEmpty( ) ) ) {
      ConsultaCliente = new TThreadConsultaCliente( NULL, &( Trim( EditRgCnpj->Text ) ),
        &( Trim( ComboBoxEERG2->Text ) ), NULL, NULL, true );
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Clientes", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditCepKeyPress( TObject *Sender, char &Key ) {

  TThreadConsultaCliente *ConsultaCliente;

  try {
    if( ( Key == 13 ) && ( EditCep->Text.Length( ) == 9 ) ) {
      ConsultaCliente = new TThreadConsultaCliente( NULL, NULL, NULL, NULL,
        &( Trim( EditCep->Text ) ), true );
    }
    if( ( AnsiCompareStr( Key, "0" ) >= 0 ) &&
        ( AnsiCompareStr( Key, "9" ) <= 0 ) && ( this->EditCep->Text.Length( ) <= 8 ) ) {
      if( this->EditCep->Text.Length( ) >= 5 ) {
        this->EditCep->Text = this->EditCep->Text.Delete( this->EditCep->Text.Pos( "-" ), 1 );
        this->EditCep->Text = this->EditCep->Text.Insert( "-", 6 );
        this->EditCep->SelStart = this->EditCep->Text.Length( );
      }
    }
    else if( Key != '\b' ) {
      Key = NULL;
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Clientes", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditTelefone2KeyPress( TObject *Sender, char &Key ) {

  TThreadConsultaCliente *ConsultaCliente;

  try {
    if( ( Key == 13 ) && ( !Trim( EditTelefone2->Text ).IsEmpty( ) ) && ( Trim( EditTelefone2->Text ).Length( ) >= 4 ) ) {
      ConsultaCliente = new TThreadConsultaCliente( NULL, NULL, NULL,
        &( Trim( EditTelefone2->Text ) ), NULL, true );
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Clientes", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxEERG2KeyDown( TObject *Sender, WORD &Key, TShiftState Shift ) {

  TThreadConsultaCliente *ConsultaCliente;

  try {
  	if( ( Key == VK_RETURN ) && ( !EditRgCnpj->Text.IsEmpty( ) ) ) {
      ConsultaCliente = new TThreadConsultaCliente( NULL, &( Trim( EditRgCnpj->Text ) ),
        &( Trim( ComboBoxEERG2->Text ) ), NULL, NULL, true );
    }
    else if( ( ( Key == VK_SPACE ) || ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
             ( !ComboBoxEERG2->DroppedDown ) ) {
   	   ComboBoxEERG2->DroppedDown = true;
     }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Clientes", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::StringGridClienteSelectCell( TObject *Sender,
  int ACol, int ARow, bool &CanSelect ) {

  if( ACol == 9 ) {
    this->StringGridCliente->Options << goEditing;
  }
  else {
    this->StringGridCliente->Options >> goEditing;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnInserirClienteClick( TObject *Sender ) {

  try {
    FormInsercaoCliente = new TFormInsercaoCliente( FormPrincipal );
    FormInsercaoCliente->Show( );
  }
  catch( Exception &e ) {
  	Application->MessageBox( e.Message.c_str( ), "Inserção de Clientes",
     												 MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnInformacaoAdicionalClienteClick( TObject *Sender ) {

	char Key = 13;

	try {
    FormInformacaoAdicionalCliente = new TFormInformacaoAdicionalCliente( FormPrincipal );
		FormInformacaoAdicionalCliente->Show( );

    if( !StringGridCliente->Cells[0][1].IsEmpty( ) ) {
      FormInformacaoAdicionalCliente->ComboBoxNomeCliente->Text = StringGridCliente->Cells[0][1];
      FormInformacaoAdicionalCliente->ComboBoxNomeClienteKeyDown( Sender, Key, TShiftState( ) );
    }
  }
  catch( Exception &e ) {
  	Application->MessageBox( e.Message.c_str( ), "Informações Adicionais do Cliente",
     												 MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------

