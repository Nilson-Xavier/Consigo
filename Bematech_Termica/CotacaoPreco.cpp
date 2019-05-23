//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Dmod1.h"
#include "ImpressaoCotacaoPreco.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditNomeEmpresaKeyPress( TObject *Sender, char &Key ) {

  if( ( Key == ' ' ) && ( ( EditNomeEmpresa->Text.IsEmpty( ) ) || ( EditNomeEmpresa->Text[EditNomeEmpresa->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
  	EditCNPJ->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditCNPJKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditCNPJ->Text.Length( ) <= 15 ) ) {
    if( this->EditCNPJ->Text.Length( ) >= 8 ) {
      this->EditCNPJ->Text = this->EditCNPJ->Text.Delete( this->EditCNPJ->Text.Pos( "/" ), 1 );
      this->EditCNPJ->Text = this->EditCNPJ->Text.Insert( "/", 9 );
      this->EditCNPJ->SelStart = this->EditCNPJ->Text.Length( );
    }
    if( this->EditCNPJ->Text.Length( ) >= 13 ) {
      this->EditCNPJ->Text = this->EditCNPJ->Text.Delete( this->EditCNPJ->Text.Pos( "-" ), 1 );
      this->EditCNPJ->Text = this->EditCNPJ->Text.Insert( "-", 14 );
      this->EditCNPJ->SelStart = this->EditCNPJ->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
  	EditInscricaoEstadual->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditInscricaoEstadualKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditInscricaoEstadual->Text.Length( ) <= 11 ) ) {

  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
  	EditAt->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditAtKeyPress( TObject *Sender, char &Key )	{

  if( ( Key == ' ' ) && ( ( EditAt->Text.IsEmpty( ) ) || ( EditAt->Text[EditAt->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
	if( Key == 13 ) {
  	EditFax->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditFaxKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditFax->Text.Length( ) <= 12 ) ) {
    if( this->EditFax->Text.IsEmpty( ) ) {
      this->EditFax->Text = this->EditFax->Text.Insert( "(", this->EditFax->Text.Length( ) - 1 );
      this->EditFax->SelStart = this->EditFax->Text.Length( );
    }
    if( this->EditFax->Text.Length( ) >= 3 ) {
      this->EditFax->Text = this->EditFax->Text.Delete( this->EditFax->Text.Pos( ")" ), 1 );
      this->EditFax->Text = this->EditFax->Text.Insert( ")", 4 );
      this->EditFax->SelStart = this->EditFax->Text.Length( );
    }
    if( this->EditFax->Text.Length( ) >= 7 ) {
      this->EditFax->Text = this->EditFax->Text.Delete( this->EditFax->Text.Pos( "-" ), 1 );
      if( this->EditFax->Text.Length( ) < 11 ) {
        this->EditFax->Text = this->EditFax->Text.Insert( "-", 8 );
      }
      else {
        this->EditFax->Text = this->EditFax->Text.Insert( "-", 9 );
      }
      this->EditFax->SelStart = this->EditFax->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
	if( Key == 13 ) {
  	EditTelefone->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditTelefoneKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditTelefone->Text.Length( ) <= 12 ) ) {
    if( this->EditTelefone->Text.IsEmpty( ) ) {
      this->EditTelefone->Text = this->EditTelefone->Text.Insert( "(", this->EditTelefone->Text.Length( ) - 1 );
      this->EditTelefone->SelStart = this->EditTelefone->Text.Length( );
    }
    if( this->EditTelefone->Text.Length( ) >= 3 ) {
      this->EditTelefone->Text = this->EditTelefone->Text.Delete( this->EditTelefone->Text.Pos( ")" ), 1 );
      this->EditTelefone->Text = this->EditTelefone->Text.Insert( ")", 4 );
      this->EditTelefone->SelStart = this->EditTelefone->Text.Length( );
    }
    if( this->EditTelefone->Text.Length( ) >= 7 ) {
      this->EditTelefone->Text = this->EditTelefone->Text.Delete( this->EditTelefone->Text.Pos( "-" ), 1 );
      if( this->EditTelefone->Text.Length( ) < 11 ) {
        this->EditTelefone->Text = this->EditTelefone->Text.Insert( "-", 8 );
      }
      else {
        this->EditTelefone->Text = this->EditTelefone->Text.Insert( "-", 9 );
      }
      this->EditTelefone->SelStart = this->EditTelefone->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
	if( Key == 13 ) {
  	EditEndereco->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditEnderecoKeyPress( TObject *Sender, char &Key ) {

  if( ( Key == ' ' ) && ( ( EditEndereco->Text.IsEmpty( ) ) || ( EditEndereco->Text[EditEndereco->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
	if( Key == 13 ) {
  	EditCidade->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditCidadeKeyPress( TObject *Sender, char &Key ) {

  if( ( Key == ' ' ) && ( ( EditCidade->Text.IsEmpty( ) ) || ( EditCidade->Text[EditCidade->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
	if( Key == 13 ) {
  	ComboBoxEstado->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxEstadoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift ) {

	if( Key == VK_RETURN ) {
  	EditCotacaoCep->SetFocus( );
  }
  else if( ( ( Key == VK_SPACE ) || ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
           ( !ComboBoxEstado->DroppedDown ) ) {
   	 ComboBoxEstado->DroppedDown = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditCotacaoCepKeyPress(TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditCotacaoCep->Text.Length( ) <= 8 ) ) {
    if( this->EditCotacaoCep->Text.Length( ) >= 5 ) {
      this->EditCotacaoCep->Text = this->EditCotacaoCep->Text.Delete( this->EditCotacaoCep->Text.Pos( "-" ), 1 );
      this->EditCotacaoCep->Text = this->EditCotacaoCep->Text.Insert( "-", 6 );
      this->EditCotacaoCep->SelStart = this->EditCotacaoCep->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxPrazoEntregaKeyPress( TObject *Sender, char &Key ) {

   if( Key == 13 ) {
   	ComboBoxCondicaoPagamento->SetFocus( );
   }
   else if ( Key == ' ' ) {
   	 ComboBoxPrazoEntrega->DroppedDown = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxCondicaoPagamentoKeyPress( TObject *Sender, char &Key ) {

	if( Key == 13 ) {
  	ComboBoxFrete->SetFocus( );
  }
  else if ( Key == ' ' ) {
  	ComboBoxCondicaoPagamento->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxFreteKeyPress( TObject *Sender, char &Key ) {

	if ( Key == 13 ) {
  	ComboBoxValidade->SetFocus( );
  }
  else if ( Key == ' ' ) {
    ComboBoxFrete->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxValidadeKeyPress(TObject *Sender,
	char &Key ) {

  if( Key == 13 ) {
  	ComboBoxVendedor2->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxVendedor2KeyDown(TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  if( ( Key == VK_RETURN ) && ( !ComboBoxVendedor2->DroppedDown ) ) {
    ComboBoxCotacaoCodigoProduto->SetFocus( );
  }
  else if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) || ( Key == VK_LEFT ) ||
             ( Key == VK_RIGHT ) ) && ( !ComboBoxVendedor2->DroppedDown ) ) {
    ComboBoxVendedor2->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxCotacaoCodigoProdutoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ( ComboBoxCotacaoCodigoProduto->Text ).Length( ) > 2 ) &&
        ( !ComboBoxCotacaoCodigoProduto->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxCotacaoCodigoProduto->Items->Clear( );
      try {
        Query->SQL->Add( "SELECT 	Codigo, Marca, Nome" );
        Query->SQL->Add( "FROM Produtos" );
        Query->SQL->Add( "WHERE Produtos.Marca LIKE '" + StringReplace( Trim( ComboBoxCotacaoCodigoProduto->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "OR Produtos.Nome LIKE '%" + StringReplace( Trim( ComboBoxCotacaoCodigoProduto->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Marca, Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            FormPrincipal->ComboBoxCotacaoCodigoProduto->Items->Append( Query->FieldByName( "Marca" )->AsString + " " +
              Query->FieldByName( "Nome" )->AsString + " " + Query->FieldByName( "Codigo" )->AsString );
            Query->Next( );
          }
          ComboBoxCotacaoCodigoProduto->Font->Size = 8;
          ComboBoxCotacaoCodigoProduto->Width = 500;
          ComboBoxCotacaoCodigoProduto->DroppedDown = true;
          ComboBoxCotacaoCodigoProduto->BringToFront( );
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Vendas", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( ComboBoxCotacaoCodigoProduto->DroppedDown ) ) {
    ComboBoxCotacaoCodigoProduto->Font->Size = 12;
    ComboBoxCotacaoCodigoProduto->Width = 225;
    while( ( ComboBoxCotacaoCodigoProduto->Text ).Pos( " " ) != 0 ) {
      ComboBoxCotacaoCodigoProduto->Text = ( ComboBoxCotacaoCodigoProduto->Text ).SubString( ( ComboBoxCotacaoCodigoProduto->Text ).Pos( " " ) + 1, ( ComboBoxCotacaoCodigoProduto->Text ).Length( ) );
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxCotacaoCodigoProduto->DroppedDown ) ) {
    ComboBoxCotacaoCodigoProduto->Font->Size = 12;
    ComboBoxCotacaoCodigoProduto->Width = 225;
    ComboBoxCotacaoCodigoProduto->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxCotacaoCodigoProduto->DroppedDown ) ) {
    MaskEditQuantidade->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MaskEditQuantidadeKeyPress(TObject *Sender, char &Key)
{
   if ( Key == 13 ){
      EditPreco->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditPrecoKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditPreco->Text.Length( ) <= 8 ) || ( Key == '\b' ) ) {
    if( this->EditPreco->Text.Length( ) >= 2 ) {
      this->EditPreco->Text = this->EditPreco->Text.Delete( this->EditPreco->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditPreco->Text.Length( ) >= 4 ) ) {
        this->EditPreco->Text = this->EditPreco->Text.Insert( ",", this->EditPreco->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditPreco->Text = this->EditPreco->Text.Insert( ",", this->EditPreco->Text.Length( ) );
      }
      this->EditPreco->SelStart = this->EditPreco->Text.Length( );
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
  if( Key == 13 ) {
  	StringGridProdutoCotacao->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::StringGridProdutoCotacaoSelectCell(
  TObject *Sender, int ACol, int ARow, bool &CanSelect ) {

  if( ACol == 1 ) {
    this->StringGridProdutoCotacao->Options << goEditing;
  }
  else {
    this->StringGridProdutoCotacao->Options >> goEditing;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::StringGridProdutoCotacaoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  int i, j;

  if( Key == VK_DELETE ) {
    if( StringGridProdutoCotacao->RowCount == 2 ) {
     	EditTotal->Clear( );
    }
    else {
      DecimalSeparator = ',';
      ThousandSeparator = '.';
      EditTotal->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) - StringReplace( StringGridProdutoCotacao->Cells[4][StringGridProdutoCotacao->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) );
    }
    for( i = StringGridProdutoCotacao->Row + 1; i <= StringGridProdutoCotacao->RowCount; i++ ) {
      for( j = 0; j <= 7; j++ ) {
        StringGridProdutoCotacao->Cells[j][i-1] = StringGridProdutoCotacao->Cells[j][i];
      }
    }
    if( StringGridProdutoCotacao->RowCount != 2 ) {
      StringGridProdutoCotacao->RowCount --;
    }
    ComboBoxCotacaoCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnConfirmaProdutoClick( TObject *Sender ) {

  String Qtd;

  if( ( Trim( ComboBoxCotacaoCodigoProduto->Text ).IsEmpty( ) ) || ( Trim( MaskEditQuantidade->Text ).IsEmpty( ) ) ) {
  	Application->MessageBox( "Você Deve Digitar o Código e a Quantidade do Produto!!!",
    												 "Cotação de Produto", MB_OK | MB_ICONERROR );
    ComboBoxCotacaoCodigoProduto->SetFocus( );
  }
  else {
	  try {
    	try {
	    	DataModuleQuery->Produtos->ParamByName( "Codigo" )->AsString = Trim( ComboBoxCotacaoCodigoProduto->Text );
  	    DataModuleQuery->Produtos->ParamByName( "Marca" )->AsString = "%";
    	  DataModuleQuery->Produtos->ParamByName( "Nome" )->AsString = "%";
      	DataModuleQuery->Produtos->Open( );
	      if( DataModuleQuery->Produtos->IsEmpty( ) ) {
  	    	throw Exception( "Produto Inexistente!!!\r\rVerifique o Código Digitado." );
    	  }
      	else {
          if( !StringGridProdutoCotacao->Cells[0][1].IsEmpty( ) ) {
  	  	    StringGridProdutoCotacao->RowCount++;
          }
      	  StringGridProdutoCotacao->Cells[0][StringGridProdutoCotacao->RowCount-1] = DataModuleQuery->Produtos->FieldByName( "Marca" )->AsString;
        	StringGridProdutoCotacao->Cells[1][StringGridProdutoCotacao->RowCount-1] = DataModuleQuery->Produtos->FieldByName( "Nome" )->AsString;
	        Qtd = Trim( MaskEditQuantidade->Text );
  	   	  while( Qtd.SubString( 1, 1 ) == '0' ) {
	  	   		Qtd.Delete( 1, 1 );
	    	  }
        	StringGridProdutoCotacao->Cells[2][StringGridProdutoCotacao->RowCount-1] = Qtd;
	        if( Trim( EditPreco->Text ) != "" ) {
  	      	ThousandSeparator = '.';
    	      DecimalSeparator = ',';
						StringGridProdutoCotacao->Cells[3][StringGridProdutoCotacao->RowCount-1] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( Trim( EditPreco->Text ), ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
        	  if( Trim( EditTotal->Text ) == "" ) {
          	  EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( Qtd ) * StrToFloat( StringReplace( Trim( EditPreco->Text ), ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
	          }
  	        else {
    	        EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( Trim( EditTotal->Text ), ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + ( StrToFloat( Qtd ) * StrToFloat( StringReplace( Trim( EditPreco->Text ), ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) ) );
      	    }
        		StringGridProdutoCotacao->Cells[4][StringGridProdutoCotacao->RowCount-1] = FormatFloat( "#,##0.00", ( StrToFloat( Qtd ) * StrToFloat( StringReplace( Trim( EditPreco->Text ), ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
	        }
  	      else {
    	    	ThousandSeparator = '.';
      	    DecimalSeparator = ',';
	      	  StringGridProdutoCotacao->Cells[3][StringGridProdutoCotacao->RowCount-1] = FormatFloat( "#,##0.00", DataModuleQuery->Produtos->FieldByName( "Preco" )->AsFloat );
          	StringGridProdutoCotacao->Cells[4][StringGridProdutoCotacao->RowCount-1] = FormatFloat( "#,##0.00", ( StrToFloat( Qtd ) * DataModuleQuery->Produtos->FieldByName( "Preco" )->AsFloat ) );
	          if( Trim( EditTotal->Text ) == "" ) {
  	          EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( Qtd ) * DataModuleQuery->Produtos->FieldByName( "Preco" )->AsFloat ) );
    	      }
      	    else {
        	    EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( Trim( EditTotal->Text ), ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + ( StrToFloat( Trim( MaskEditQuantidade->Text ) ) * DataModuleQuery->Produtos->FieldByName( "Preco" )->AsFloat ) ) );
          	}
	        }
  	      StringGridProdutoCotacao->Cells[5][StringGridProdutoCotacao->RowCount-1] = DataModuleQuery->Produtos->FieldByName( "Garantia" )->AsString;
    	    StringGridProdutoCotacao->Cells[6][StringGridProdutoCotacao->RowCount-1] = DataModuleQuery->Produtos->FieldByName( "Codigo" )->AsString;
      	}
	      DataModuleQuery->Produtos->Close( );
        ComboBoxCotacaoCodigoProduto->Clear( );
        MaskEditQuantidade->Clear( );
        EditPreco->Clear( );
  	  }
    	catch( Exception &e ) {
    		DataModuleQuery->Produtos->Close( );
	    	Application->MessageBox( e.Message.c_str( ), "Cotação de Produto", MB_OK | MB_ICONERROR );
    	  ComboBoxCotacaoCodigoProduto->SetFocus( );
	    }
  	}
	  __finally {
    	ComboBoxCotacaoCodigoProduto->SetFocus( );
	  }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnCancelaProdutoCotacaoClick( TObject *Sender ) {

  int i, j, k;
  bool Ok;

  if( Trim( ComboBoxCotacaoCodigoProduto->Text ) == "" ) {
  	Application->MessageBox( "Você Deve Digitar o Código do Produto!!!", "Cotação de Produto",
    												 MB_OK | MB_ICONERROR );
    ComboBoxCotacaoCodigoProduto->SetFocus( );
  }
  else {
  	for( i = 1; i < StringGridProdutoCotacao->RowCount; i++ ) {
    	if( LowerCase( StringGridProdutoCotacao->Cells[6][i] ) == LowerCase( Trim( ComboBoxCotacaoCodigoProduto->Text ) ) ) {
      	Ok = true;
      	break;
      }
      else {
	      Ok = false;
      }
    }
    if( !Ok ) {
	  	Application->MessageBox( "O Código do Produto Não Está Na Cotação!!!", "Cotação de Produto",
  	  												 MB_OK | MB_ICONERROR );
    	ComboBoxCotacaoCodigoProduto->SetFocus( );
    }
    else {
    	if( StringGridProdutoCotacao->RowCount == 2 ) {
      	EditTotal->Text = "";
      }
      else {
      	ThousandSeparator = '.';
        DecimalSeparator = ',';
      	EditTotal->Text = FormatFloat( "#,##0.00", StrToFloat( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) - StrToFloat( StringReplace( StringGridProdutoCotacao->Cells[4][i], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
      }

      for( j = i + 1; j < StringGridProdutoCotacao->RowCount; j++ ) {
        for( k = 0; k <= 7; k++ ) {
          StringGridProdutoCotacao->Cells[k][j-1] = StringGridProdutoCotacao->Cells[k][j];
        }
      }
      if( StringGridProdutoCotacao->RowCount > 2 ) {
        StringGridProdutoCotacao->RowCount --;
      }
      else {
        StringGridProdutoCotacao->Rows[1]->Clear( );
      }
      ComboBoxCotacaoCodigoProduto->SetFocus( );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnImprimirCotacaoClick( TObject *Sender ) {

  int i, j, k, l;
	TCursor SaveCursor = Screen->Cursor;
  TDateTime *Data;
  String Produto;

	if( ( ( Trim( EditNomeEmpresa->Text ).IsEmpty( ) ) && ( Trim( EditAt->Text ).IsEmpty( ) ) ) ||
  		( Trim( EditFax->Text ).Length( ) < 12 ) || ( Trim( ComboBoxCondicaoPagamento->Text ).IsEmpty( ) ) ||
      ( Trim( ComboBoxFrete->Text ).IsEmpty( ) ) || ( ComboBoxVendedor2->Text.IsEmpty( ) ) ||
      ( StringGridProdutoCotacao->Cells[0][1].IsEmpty( ) ) ) {
  	Application->MessageBox( "Você Deve Completar Todos os Campos Necessários para a Cotação!!!",
    												 "Cotação de Produto", MB_OK | MB_ICONERROR );
    EditNomeEmpresa->SetFocus( );
  }
  else {
  	try {
    	Screen->Cursor = crHourGlass;
      this->Enabled = false;
      Data = new TDateTime( );
      try {
	      Application->CreateForm( __classid( TFormCotacaoPreco ), &FormCotacaoPreco );
        LongMonthNames[0] = "Janeiro";
        LongMonthNames[1] = "Fevereiro";
        LongMonthNames[2] = "Março";
        LongMonthNames[3] = "Abril";
        LongMonthNames[4] = "Maio";
        LongMonthNames[5] = "Junho";
        LongMonthNames[6] = "Julho";
        LongMonthNames[7] = "Agosto";
        LongMonthNames[8] = "Setembro";
        LongMonthNames[9] = "Outubro";
        LongMonthNames[10] = "Novembro";
        LongMonthNames[11] = "Dezembro";

        *Data = Data->CurrentDate( );
        FormCotacaoPreco->QRLabelData->Caption = "São Paulo, " + Data->FormatString( "dd 'de' mmmm 'de' yyyy" );

        if( Trim( EditNomeEmpresa->Text ).IsEmpty( ) ) {
					FormCotacaoPreco->QRLabel3->Enabled = false;
      		FormCotacaoPreco->QRLabelEmpresa->Enabled = false;
	      }
  	    else {
	  	    FormCotacaoPreco->QRLabelEmpresa->Caption = Trim( EditNomeEmpresa->Text );
      	}
	      if( Trim( EditAt->Text ).IsEmpty( ) ) {
  	      FormCotacaoPreco->QRLabel4->Enabled = false;
    	  	FormCotacaoPreco->QRLabelNome->Enabled = false;
      	}
	      else {
  	    	FormCotacaoPreco->QRLabelNome->Caption = Trim( EditAt->Text );
    	  }
      	if( EditCNPJ->Text.IsEmpty( ) ) {
					FormCotacaoPreco->QRLabel8->Enabled = false;
	        FormCotacaoPreco->QRLabelCNPJ->Enabled = false;
  	    }
    	  else {
      	  FormCotacaoPreco->QRLabelCNPJ->Caption = Trim( EditCNPJ->Text );
	      }
  	    if( EditInscricaoEstadual->Text.IsEmpty( ) ) {
    	    FormCotacaoPreco->QRLabel17->Enabled = false;
      	  FormCotacaoPreco->QRLabelInscricaoEstadual->Enabled = false;
	      }
  	    else {
    	    FormCotacaoPreco->QRLabelInscricaoEstadual->Caption = Trim( EditInscricaoEstadual->Text );
      	}
	      FormCotacaoPreco->QRLabelFax->Caption = Trim( EditFax->Text );
  	    if( EditTelefone->Text.IsEmpty( ) ) {
    	    FormCotacaoPreco->QRLabel6->Enabled = false;
      	  FormCotacaoPreco->QRLabelTel->Enabled = false;
	      }
  	    else {
    	    FormCotacaoPreco->QRLabelTel->Caption = Trim( EditTelefone->Text );
      	}
	      if( EditEndereco->Text.IsEmpty( ) ) {
  	      FormCotacaoPreco->QRLabelEndereco->Enabled = false;
    	  }
      	else {
        	FormCotacaoPreco->QRLabelEndereco->Caption = Trim( EditEndereco->Text );
	      }
  	    if( EditCidade->Text.IsEmpty( ) ) {
    	    FormCotacaoPreco->QRLabelCidade->Enabled = false;
      	}
	      else {
  	      FormCotacaoPreco->QRLabelCidade->Caption = Trim( EditCidade->Text );
    	  }
      	if( ComboBoxEstado->Text.IsEmpty( ) ) {
        	FormCotacaoPreco->QRLabelEstado->Enabled = false;
	      }
  	    else {
    	    FormCotacaoPreco->QRLabelEstado->Caption = Trim( ComboBoxEstado->Text );
      	}
	      if( Trim( EditCotacaoCep->Text ).Length( ) < 9 ) {
  	      FormCotacaoPreco->QRLabel2->Enabled = false;
    	    FormCotacaoPreco->QRLabelCep->Enabled = false;
      	}
	      else {
  	      FormCotacaoPreco->QRLabelCep->Caption = Trim( EditCotacaoCep->Text );
    	  }
      	if( ComboBoxPrazoEntrega->Text.IsEmpty( ) ) {
	        FormCotacaoPreco->QRLabelPrazoEntrega->Enabled = false;
  	    }
    	  else {
      	  FormCotacaoPreco->QRLabelPrazoEntrega->Caption = Trim( ComboBoxPrazoEntrega->Text );
	      }
  	    if( ComboBoxCondicaoPagamento->Text.IsEmpty( ) ) {
      	  FormCotacaoPreco->QRRichTextPagamento->Enabled = false;
	      }
  	    else {
    	    FormCotacaoPreco->QRRichTextPagamento->Lines->Text = Trim( ComboBoxCondicaoPagamento->Text );
      	}
	      if( ComboBoxFrete->Text.IsEmpty( ) ) {
    	    FormCotacaoPreco->QRLabelFrete->Enabled = false;
      	}
	      else {
  	      FormCotacaoPreco->QRLabelFrete->Caption = Trim( ComboBoxFrete->Text );
    	  }
      	if( ComboBoxValidade->Text.IsEmpty( ) ) {
	        FormCotacaoPreco->QRLabelValidade->Enabled = false;
  	    }
    	  else {
       	  FormCotacaoPreco->QRLabelValidade->Caption = Trim( ComboBoxValidade->Text );
	      }
      	if( ComboBoxVendedor2->Text.IsEmpty( ) ) {
      	  FormCotacaoPreco->QRLabelVendedor->Enabled = false;
	      }
  	    else {
    	    FormCotacaoPreco->QRLabelVendedor->Caption = Trim( ComboBoxVendedor2->Text );
      	}

        FormCotacaoPreco->QRStringsBand1->Items->Append( "XXX" );

        k = 0;
	      for( i = 1; i < StringGridProdutoCotacao->RowCount; i++ ) {
  	      FormCotacaoPreco->QRMemoMarca->Lines->Append( StringGridProdutoCotacao->Cells[0][i] );
          Produto = StringGridProdutoCotacao->Cells[1][i];
          while( Produto.Length( ) > 43 ) {
	    	    FormCotacaoPreco->QRMemoNome->Lines->Append( Produto.SubString( 1, 43 ) );
            Produto.Delete( 1, 43 );
          }
          FormCotacaoPreco->QRMemoNome->Lines->Append( Produto );
      	  FormCotacaoPreco->QRMemoQuantidade->Lines->Append( StringGridProdutoCotacao->Cells[2][i] );
        	FormCotacaoPreco->QRMemoPrecoUnit->Lines->Append( StringGridProdutoCotacao->Cells[3][i] );
	        FormCotacaoPreco->QRMemoPreco->Lines->Append( StringGridProdutoCotacao->Cells[4][i] );
  	      FormCotacaoPreco->QRMemoGarantia->Lines->Append( StringGridProdutoCotacao->Cells[5][i] );
          if( FormCotacaoPreco->QRMemoNome->Lines->Count > ( i + k ) ) {
            l = FormCotacaoPreco->QRMemoNome->Lines->Count - ( i + k );
          	k = FormCotacaoPreco->QRMemoNome->Lines->Count - i;
            for( j = 0; j < l; j++ ) {
	          	FormCotacaoPreco->QRMemoMarca->Lines->Append( " " );
              if( i == 1 ) {
								FormCotacaoPreco->QRMemoQuantidade->Lines->Insert( 0, " " );
								FormCotacaoPreco->QRMemoGarantia->Lines->Insert( 0, " " );
      	  	  	FormCotacaoPreco->QRMemoPrecoUnit->Lines->Insert( 0, " " );
        	    	FormCotacaoPreco->QRMemoPreco->Lines->Insert( 0, " " );
              }
              else {
								FormCotacaoPreco->QRMemoQuantidade->Lines->Insert( ( FormCotacaoPreco->QRMemoQuantidade->Lines->Count - 1 ), " " );
								FormCotacaoPreco->QRMemoGarantia->Lines->Insert( ( FormCotacaoPreco->QRMemoGarantia->Lines->Count - 1 ), " " );
      	  	  	FormCotacaoPreco->QRMemoPrecoUnit->Lines->Insert( ( FormCotacaoPreco->QRMemoPrecoUnit->Lines->Count - 1 ), " " );
        	    	FormCotacaoPreco->QRMemoPreco->Lines->Insert( ( FormCotacaoPreco->QRMemoPreco->Lines->Count - 1 ), " " );
              }
            }
          }
          // Mudança de Página. Tem que Cortar o Resto dos Itens!!!
          if( FormCotacaoPreco->QRMemoNome->Lines->Count > 39 ) {
           	break;
          }
        }

	      FormCotacaoPreco->QRLabelAssinatura->Caption = Trim( ComboBoxVendedor2->Text );
  	    FormCotacaoPreco->QRLabelTotal->Caption = EditTotal->Text;

        FormCotacaoPreco->QuickRepCotacao->PrinterSetup( );
        FormCotacaoPreco->QuickRepCotacao->Print( );

        if( Application->MessageBox( "A Impressão da Cotação de Preços Está Correta?",
    												         "Cotação de Produto", MB_YESNO | MB_ICONQUESTION ) == 6 ) {
          EditNomeEmpresa->Clear( );
          EditCNPJ->Clear( );
          EditInscricaoEstadual->Clear( );
          EditAt->Clear( );
          EditFax->Clear( );
          EditTelefone->Clear( );
          EditEndereco->Clear( );
          EditCidade->Clear( );
          ComboBoxEstado->Text = "";
          ComboBoxPrazoEntrega->Text = "";
          ComboBoxCondicaoPagamento->Text = "";
          ComboBoxFrete->Text = "";
          ComboBoxValidade->Text = "";
          ComboBoxCotacaoCodigoProduto->Text = "";
          MaskEditQuantidade->Clear( );
          EditPreco->Clear( );
          EditTotal->Clear( );
	        for( i = 1; i < StringGridProdutoCotacao->RowCount; i++ ) {
  		    	StringGridProdutoCotacao->Rows[i]->Clear( );
  				}
          StringGridProdutoCotacao->RowCount = 2;
        }
      }
      catch( Exception &e ) {
      	Application->MessageBox( e.Message.c_str( ), "Cotação de Preço",
        												 MB_OK | MB_ICONERROR );
      }
    }
    __finally {
    	delete Data;
      delete FormCotacaoPreco;
      Screen->Cursor = SaveCursor;
      this->Enabled = true;
      PageControl1->ActivePage = TabSheetCotacaoPreco;
      EditNomeEmpresa->SetFocus( );
    }
  }
}
//---------------------------------------------------------------------------
