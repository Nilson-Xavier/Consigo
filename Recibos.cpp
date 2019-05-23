//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Recibo.h"
#include "Dmod1.h"
#include "Main.h"
#include "ConverteDinheiroTexto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxReciboVendedorKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( !ComboBoxReciboVendedor->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxReciboVendedor->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome" );
        Query->SQL->Add( "FROM Vendedores" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            FormPrincipal->ComboBoxReciboVendedor->Items->Append( Query->FieldByName( "Nome" )->AsString );
            Query->Next( );
          }
          ComboBoxReciboVendedor->DroppedDown = true;
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Recibo", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxReciboVendedor->DroppedDown ) ) {
    ComboBoxReciboVendedor->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxReciboVendedor->DroppedDown ) ) {
    ComboBoxRecebemos->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxReciboVendedorKeyPress( TObject *Sender,
 char &Key ) {

  if( !ComboBoxReciboVendedor->DroppedDown ) {
    switch( Key ) {
      case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
      case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
      case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
      case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
      case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
      case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
      case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
      case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
      case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
      case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
      case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
      case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
      case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
      case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
      case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
      case '=': Key = NULL; break; case ',': Key = NULL; break; case '_': Key = NULL; break;
    }
    if( ( Key == ' ' ) && ( ( ComboBoxReciboVendedor->Text.IsEmpty( ) ) || ( ComboBoxReciboVendedor->Text[ComboBoxReciboVendedor->Text.Length( )] == ' ' ) ) ) {
      Key = NULL;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxRecebemosKeyDown(TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ( ComboBoxRecebemos->Text ).Length( ) > 2 ) &&
        ( !ComboBoxRecebemos->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxRecebemos->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome" );
        Query->SQL->Add( "FROM Clientes" );
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( Trim( ComboBoxRecebemos->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            FormPrincipal->ComboBoxRecebemos->Items->Append( Query->FieldByName( "Nome" )->AsString );
            Query->Next( );
          }
          ComboBoxRecebemos->DroppedDown = true;
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Recibo", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxRecebemos->DroppedDown ) ) {
    ComboBoxRecebemos->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxRecebemos->DroppedDown ) ) {
    EditReciboValor->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxRecebemosKeyPress(TObject *Sender, char &Key ) {

  if( !ComboBoxRecebemos->DroppedDown ) {
    switch( Key ) {
      case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
      case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
      case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
      case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
      case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
      case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
      case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
      case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
      case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
      case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
      case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
      case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
      case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
      case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
      case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
      case '=': Key = NULL; break; case ',': Key = NULL; break; case '_': Key = NULL; break;
    }
    if( ( Key == ' ' ) && ( ( ComboBoxRecebemos->Text.IsEmpty( ) ) || ( ComboBoxRecebemos->Text[ComboBoxRecebemos->Text.Length( )] == ' ' ) ) ) {
      Key = NULL;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditReciboValorKeyPress(TObject *Sender, char &Key ) {

  if( Key == 13 ) {
  	MemoReciboReferente->SetFocus( );
  }
  if( ( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
        ( this->EditReciboValor->Text.Length( ) <= 7 ) ) || ( Key == '\b' ) ) {
    if( this->EditReciboValor->Text.Length( ) >= 2 ) {
      this->EditReciboValor->Text = this->EditReciboValor->Text.Delete( this->EditReciboValor->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditReciboValor->Text.Length( ) >= 4 ) ) {
        this->EditReciboValor->Text = this->EditReciboValor->Text.Insert( ",", this->EditReciboValor->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditReciboValor->Text = this->EditReciboValor->Text.Insert( ",", this->EditReciboValor->Text.Length( ) );
      }
      this->EditReciboValor->SelStart = this->EditReciboValor->Text.Length( );
    }
    if( this->EditReciboValor->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MemoReciboReferenteKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
    case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
    case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
    case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
    case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
    case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
    case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
    case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case '&': Key = NULL; break; case '_': Key = NULL; break;
  }
  if( ( Key == 13 ) && ( MemoReciboReferente->Text.IsEmpty( ) ) ) {
    Key = NULL;
  }
  else if( ( Key == 13 ) && ( MemoReciboReferente->Lines->Strings[MemoReciboReferente->Lines->Count - 1].IsEmpty( ) ) ) {
    Key = NULL;
  }
  if( ( Key == ' ' ) && ( ( MemoReciboReferente->Lines->Text.IsEmpty( ) )
      || ( MemoReciboReferente->Lines->Strings[MemoReciboReferente->Lines->Count - 1].SubString( MemoReciboReferente->Lines->Strings[MemoReciboReferente->Lines->Count - 1].Length( ), 1 ) == " " ) ) ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnReciboImprimirClick( TObject *Sender ) {

  TStringList *Request;
  TConsigoClientSocket *ConexaoServidor;
  int i;

  TDinheiroTexto *Conversor;
  String *Extenso, *MensagemTeste;

  try {
    BitBtnReciboImprimir->Enabled = false;
    MenuItemImprimirRecibo->Enabled = false;
    Request = new TStringList( );
    Request->Sorted = false;

    Conversor = new TDinheiroTexto( );
    Extenso = new AnsiString( );
    MensagemTeste = new AnsiString( );

    try {
      /* Para Teste !!!
      Conversor->ConverterDinheiroTexto( &(EditReciboValor->Text), Extenso );
      *MensagemTeste = "R$ " + EditReciboValor->Text + "\r\r" + *Extenso;
      MessageDlg( *MensagemTeste, mtConfirmation, TMsgDlgButtons( ) << mbOK, 0 );
      */

      if( ( ComboBoxReciboVendedor->Text.IsEmpty( ) ) || ( ComboBoxRecebemos->Text.IsEmpty( ) ) ||
          ( EditReciboValor->Text.IsEmpty( ) ) || ( MemoReciboReferente->Text.IsEmpty( ) ) ) {
        throw Exception( "Faltam Dados para o Recibo !!!" );
      }
      else {
        Request->Append( "IP=" + *FormPrincipal->ServerSocketIP );
        Request->Append( "Funcao=Recibo" );
        Request->Append( "Vendedor=" + ComboBoxReciboVendedor->Text );
        Request->Append( "Cliente=" + ComboBoxRecebemos->Text );
        Request->Append( "Preco=" + EditReciboValor->Text );
        Request->Append( "Referente=" + StringReplace( MemoReciboReferente->Text, "\r\n", "||", TReplaceFlags( ) << rfReplaceAll ) );

        ConexaoServidor = new TConsigoClientSocket( Application, Request, FormPrincipal->ServerSocketIP );


      }
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Recibo", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete Request;
    BitBtnReciboImprimir->Enabled = true;
    MenuItemImprimirRecibo->Enabled = true;

    delete Conversor;
    delete Extenso;
    delete MensagemTeste;
  }
}
//---------------------------------------------------------------------------

