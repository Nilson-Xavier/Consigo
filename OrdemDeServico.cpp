//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OrdemDeServico.h"
#include "Dmod1.h"
#include "Main.h"
#include "ClientSocket.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOrdemDeServico *FormOrdemDeServico;
//---------------------------------------------------------------------------
__fastcall TFormOrdemDeServico::TFormOrdemDeServico( TComponent* Owner ) : TForm( Owner ) {

  TConsigoQuery *Query;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    try {
      Query->SQL->Add( "SELECT Nome" );
      Query->SQL->Add( "FROM Vendedores" );
      Query->SQL->Add( "ORDER BY Nome" );
      Query->Prepare( );
      Query->Open( );
      Query->First( );
      while( !Query->Eof ) {
        this->ComboBoxVendedor->Items->Add( Query->FieldByName( "Nome" )->AsString );
        Query->Next( );
      }
    }
    catch( String &Error ) {
	  	Application->MessageBox( Error.c_str( ), "Ordem De Serviço", MB_OK | MB_ICONERROR );
  	  this->Close( );
      delete this;
    }
  }
  __finally {
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
__fastcall TFormOrdemDeServico::~TFormOrdemDeServico( ) {

  if( GridMemoDefeitoArray != NULL ) {
    delete GridMemoDefeitoArray;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::FormCreate( TObject *Sender ) {

  StringGridConserto->ColCount = 5;
  StringGridConserto->RowCount = 2;
  StringGridConserto->Cells[0][0] = "Marca";
  StringGridConserto->ColWidths[0] = 140;
  StringGridConserto->Cells[1][0] = "Nome";
  StringGridConserto->ColWidths[1] = 580;
  StringGridConserto->Cells[2][0] = "Número Série";
  StringGridConserto->ColWidths[2] = 180;
  StringGridConserto->Cells[3][0] = "Preço R$";
  StringGridConserto->ColWidths[3] = 115;
  StringGridConserto->Cells[4][0] = "Codigo";
  StringGridConserto->ColWidths[4] = 180;
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::BitBtnVoltarClick( TObject *Sender ) {

  this->Close( );
  FormOrdemDeServico = NULL;
  delete FormOrdemDeServico;
  FormPrincipal->PageControl1->ActivePage = FormPrincipal->TabSheetConserto;
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::ComboBoxVendedorKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  if( ( Key == VK_RETURN ) && ( !ComboBoxVendedor->DroppedDown ) ) {
    ComboBoxCliente->SetFocus( );
  }
  else if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( !ComboBoxVendedor->DroppedDown ) ) {
    ComboBoxVendedor->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::ComboBoxClienteKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ( ComboBoxCliente->Text ).Length( ) > 2 ) &&
        ( !ComboBoxCliente->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxCliente->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome" );
        Query->SQL->Add( "FROM Clientes" );
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( Trim( ComboBoxCliente->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            ComboBoxCliente->Items->Append( Query->FieldByName( "Nome" )->AsString );
            Query->Next( );
          }
          ComboBoxCliente->Font->Size = 8;
          ComboBoxCliente->DroppedDown = true;
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( ComboBoxCliente->DroppedDown ) ) {
    ComboBoxCliente->Font->Size = 12;
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxCliente->DroppedDown ) ) {
    ComboBoxCliente->Font->Size = 12;
    ComboBoxCliente->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxCliente->DroppedDown ) ) {
    MemoDefeito->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::MemoDefeitoKeyPress(TObject *Sender, char &Key ) {

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
  if( ( Key == 13 ) && ( MemoDefeito->Text.IsEmpty( ) ) ) {
    Key = NULL;
  }
  else if( ( Key == 13 ) && ( MemoDefeito->Lines->Strings[MemoDefeito->Lines->Count - 1].IsEmpty( ) ) ) {
    Key = NULL;
  }
  if( ( Key == ' ' ) && ( ( MemoDefeito->Lines->Text.IsEmpty( ) )
      || ( MemoDefeito->Lines->Strings[MemoDefeito->Lines->Count - 1].SubString( MemoDefeito->Lines->Strings[MemoDefeito->Lines->Count - 1].Length( ), 1 ) == " " ) ) ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::ComboBoxCodigoProdutoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
        ( ( ComboBoxCodigoProduto->Text ).Length( ) > 2 ) && ( !ComboBoxCodigoProduto->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxCodigoProduto->Items->Clear( );
      try {
        Query->SQL->Add( "SELECT 	Codigo, Marca, Nome" );
        Query->SQL->Add( "FROM Produtos" );
        Query->SQL->Add( "WHERE Produtos.Marca LIKE '" + StringReplace( Trim( ComboBoxCodigoProduto->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "OR Produtos.Nome LIKE '%" + StringReplace( Trim( ComboBoxCodigoProduto->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Marca, Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            ComboBoxCodigoProduto->Items->Append( Query->FieldByName( "Marca" )->AsString + " " +
            Query->FieldByName( "Nome" )->AsString + " " + Query->FieldByName( "Codigo" )->AsString );
            Query->Next( );
          }
          ComboBoxCodigoProduto->Font->Size = 10;
          ComboBoxCodigoProduto->Width = 500;
          ComboBoxCodigoProduto->DroppedDown = true;
          ComboBoxCodigoProduto->BringToFront( );
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Ordem De Serviço", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( ComboBoxCodigoProduto->DroppedDown ) ) {
    ComboBoxCodigoProduto->Font->Size = 14;
    ComboBoxCodigoProduto->Width = 225;
    while( ( ComboBoxCodigoProduto->Text ).Pos( " " ) != 0 ) {
      ComboBoxCodigoProduto->Text = ( ComboBoxCodigoProduto->Text ).SubString( ( ComboBoxCodigoProduto->Text ).Pos( " " ) + 1, ( ComboBoxCodigoProduto->Text ).Length( ) );
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxCodigoProduto->DroppedDown ) ) {
    ComboBoxCodigoProduto->Font->Size = 14;
    ComboBoxCodigoProduto->Width = 225;
    ComboBoxCodigoProduto->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxCodigoProduto->DroppedDown ) ) {
    EditNumeroSerie->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::EditNumeroSerieKeyPress( TObject *Sender,
  char &Key ) {

  if( ( Key == ' ' ) && ( ( EditNumeroSerie->Text.IsEmpty( ) )
      || ( EditNumeroSerie->Text[EditNumeroSerie->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditPreco->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::EditPrecoKeyPress(TObject *Sender, char &Key ) {

  if( Key == 13 ) {
  	BitBtnConfirmarProduto->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) &&
      ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditPreco->Text.Length( ) <= 8 ) || ( Key == '\b' ) ) {
    if( this->EditPreco->Text.Length( ) >= 2 ) {
      this->EditPreco->Text = this->EditPreco->Text.Delete( this->EditPreco->Text.Pos( "," ), 1 );
      this->EditPreco->Text = this->EditPreco->Text.Insert( ",", this->EditPreco->Text.Length( ) );
      this->EditPreco->SelStart = this->EditPreco->Text.Length( );
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::StringGridConsertoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift) {

  TMemo *GridMemo;
  int i, j;

  if( Key == VK_DELETE ) {

    if( StringGridConserto->RowCount == 2 ) {
     	EditTotal->Clear( );
    }
    else {
      DecimalSeparator = ',';
      ThousandSeparator = '.';
      EditTotal->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) - StringReplace( StringGridConserto->Cells[3][StringGridConserto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) );
    }
    for( i = StringGridConserto->Row + 1; i <= StringGridConserto->RowCount; i++ ) {
      for( j = 0; j <= 7; j++ ) {
        StringGridConserto->Cells[j][i-1] = StringGridConserto->Cells[j][i];
      }
      GridMemoDefeitoArray[i - 2] = GridMemoDefeitoArray[i - 1];
    }
    if( StringGridConserto->RowCount != 2 ) {
      StringGridConserto->RowCount --;
    }
    ComboBoxCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::BitBtnConfirmarProdutoClick( TObject *Sender ) {

  int i;
  TDateTime *Data;
  TConsigoQuery *Query;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Data = new TDateTime( );

    try {
  	  if( ( ComboBoxCodigoProduto->Text.IsEmpty( ) ) || ( EditNumeroSerie->Text.IsEmpty( ) ) ||
          ( EditPreco->Text.Length( ) < 4 ) || ( MemoDefeito->Text.IsEmpty( ) ) ) {
  	    throw Exception( "Faltam Dados para o Produto!!!" );
  	  }
      else if( StringGridConserto->RowCount == 17 ) {
        throw Exception( "A Ordem De Serviço NÃO Pode Ter Mais que 16 Itens !!!" );
      }
    	else {
        Query->SQL->Add( "SELECT 	Codigo, Marca, Nome" );
        Query->SQL->Add( "FROM Produtos" );
        Query->SQL->Add( "WHERE Codigo = '" + Trim( ComboBoxCodigoProduto->Text ) + "'" );
        Query->Prepare( );
        Query->Open( );
        if( Query->IsEmpty( ) ) {
          throw Exception( "O Produto com Código: " + Trim( ComboBoxCodigoProduto->Text ) + " NÃO Existe!!!" );
        }
          if( StringGridConserto->Cells[0][1] != "" ) {
          	StringGridConserto->RowCount ++;
          }
	        StringGridConserto->Cells[0][StringGridConserto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
  	      StringGridConserto->Cells[1][StringGridConserto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
   	      StringGridConserto->Cells[2][StringGridConserto->RowCount - 1] = Trim( EditNumeroSerie->Text );
    	    DecimalSeparator = ',';
      	  ThousandSeparator = '.';
         	StringGridConserto->Cells[3][StringGridConserto->RowCount - 1] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( EditPreco->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
          StringGridConserto->Cells[4][StringGridConserto->RowCount - 1] = Query->FieldByName( "Codigo" )->AsString;
          GridMemoDefeitoArray[StringGridConserto->RowCount - 2] = new TMemo( FormOrdemDeServico );
          GridMemoDefeitoArray[StringGridConserto->RowCount - 2]->Text = this->MemoDefeito->Text;

	        if( EditTotal->Text.IsEmpty( ) ) {
  	        DecimalSeparator = ',';
    	      ThousandSeparator = '.';
            EditTotal->Text = StringGridConserto->Cells[3][StringGridConserto->RowCount - 1];
        	}
	        else {
      	    DecimalSeparator = ',';
        	  ThousandSeparator = '.';
          	EditTotal->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) + StrToFloat( StringReplace( StringGridConserto->Cells[3][StringGridConserto->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
	        }
    	    EditNumeroSerie->Clear( );
        	EditPreco->Clear( );
       	  ComboBoxCodigoProduto->Clear( );
          ComboBoxCodigoProduto->SetFocus( );
          MemoDefeito->Clear( );
      }

    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Ordem De Serviço", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete Data;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOrdemDeServico::BitBtnImprimirOrcamentoClick( TObject *Sender ) {

  TStringList *Request;
  TConsigoClientSocket *ConexaoServidor;
  int i;

  try {
    BitBtnImprimirOrcamento->Enabled = false;
    BitBtnVoltar->Enabled = false;
    MenuItemSair->Enabled = false;
    MenuItemAtalhos->Enabled = false;
    BitBtnConfirmarProduto->Enabled = false;
    Request = new TStringList( );
    Request->Sorted = false;

    try {
      if( ( StringGridConserto->Cells[0][1].IsEmpty( ) ) || ( ComboBoxVendedor->Text.IsEmpty( ) ) ||
          ( ComboBoxCliente->Text.IsEmpty( ) ) ) {
        throw Exception( "Faltam Dados para a Ordem de Serviço!!!" );
      }
      else {
        Request->Append( "IP=" + *FormPrincipal->ServerSocketIP );
        Request->Append( "Funcao=OrcamentoConserto" );
        Request->Append( "Vendedor=" + ComboBoxVendedor->Text );
        Request->Append( "Cliente=" + ComboBoxCliente->Text );
        Request->Append( "ItemQtd=" + IntToStr( StringGridConserto->RowCount - 1 ) );
        for( i = 1; i < StringGridConserto->RowCount; i++ ) {
          Request->Append( "Codigo" + IntToStr( i ) + "=" + StringGridConserto->Cells[4][i] );
          Request->Append( "Descricao" + IntToStr( i ) + "=" + StringGridConserto->Cells[0][i] + " " + StringGridConserto->Cells[1][i] );
          Request->Append( "NumeroSerie" + IntToStr( i ) + "=" + StringGridConserto->Cells[2][i] );
          Request->Append( "Preco" + IntToStr( i ) + "=" + StringGridConserto->Cells[3][i] );
          Request->Append( "Defeito" + IntToStr( i ) + "=" + StringReplace( GridMemoDefeitoArray[i-1]->Text, "\r\n", "||", TReplaceFlags( ) << rfReplaceAll ) );
        }

        ConexaoServidor = new TConsigoClientSocket( Application, Request, FormPrincipal->ServerSocketIP );
      }
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Ordem De Serviço", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete Request;
    BitBtnVoltar->Enabled = true;
    MenuItemSair->Enabled = true;
    MenuItemAtalhos->Enabled = true;
    BitBtnConfirmarProduto->Enabled = true;
    BitBtnImprimirOrcamento->Enabled = true;
  }
}
//---------------------------------------------------------------------------


