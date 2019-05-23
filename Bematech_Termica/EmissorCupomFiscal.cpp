//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "InsercaoProduto.h"
#include "Dmod1.h"
#include "ImpressoraFiscalBematech.h"
#include "ImpressoraFiscalEcfRfd.h"
#include "SecaoCritica.h"
#include "Main.h"
#include <vcl\StrUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::EmissorCupomFiscal1Click( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetEmissorCupomFiscal;
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::ComboBoxNomeVendedorKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift ) {

	if( ( Key == VK_RETURN ) && ( !ComboBoxNomeVendedor->DroppedDown ) ) {
    EditCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::ComboBoxDescricaoProdutoKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ( ComboBoxDescricaoProduto->Text ).Length( ) > 2 ) &&
        ( !ComboBoxDescricaoProduto->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxDescricaoProduto->Items->Clear( );
      try {
        Query->SQL->Add( "SELECT 	Codigo, Marca, Nome, Garantia, ( Preco * Dolar ) AS PrecoProduto" );
        Query->SQL->Add( "FROM Produtos" );
        Query->SQL->Add( "WHERE Produtos.Marca LIKE '" + StringReplace( Trim( ComboBoxDescricaoProduto->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "OR Produtos.Nome LIKE '%" + StringReplace( Trim( ComboBoxDescricaoProduto->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Marca, Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            if( Query->FieldByName( "Garantia" )->AsString.IsEmpty( ) ) {
              this->ComboBoxDescricaoProduto->Items->Append( Query->FieldByName( "Marca" )->AsString + " " +
                Query->FieldByName( "Nome" )->AsString + " " + Query->FieldByName( "Codigo" )->AsString );
            }
            else {
              this->ComboBoxDescricaoProduto->Items->Append( Query->FieldByName( "Marca" )->AsString + " " +
                Query->FieldByName( "Nome" )->AsString + " Garantia " + Query->FieldByName( "Garantia" )->AsString +
                " " + Query->FieldByName( "Codigo" )->AsString );
            }
            PrecoItensComboBoxDescricaoProduto->Add( FormatFloat( "0.00", Query->FieldByName( "PrecoProduto" )->AsFloat ) );
            Query->Next( );
          }
          ComboBoxDescricaoProduto->Font->Size = 8;
          ComboBoxDescricaoProduto->Width = 500;
          ComboBoxDescricaoProduto->DroppedDown = true;
          ComboBoxDescricaoProduto->BringToFront( );
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Emissor de Cupom Fiscal", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( ComboBoxDescricaoProduto->DroppedDown ) ) {
    for( i = ComboBoxDescricaoProduto->Text.Length( ); i > 0; i-- ) {
      if( ComboBoxDescricaoProduto->Text[i] == ' ' ) {
        break;
      }
    }
    ComboBoxDescricaoProduto->Font->Size = 14;
    ComboBoxDescricaoProduto->Width = 225;
    EditCodigoProduto->Text =  RightStr( ComboBoxDescricaoProduto->Text, ComboBoxDescricaoProduto->Text.Length( ) - i );
    ComboBoxDescricaoProduto->Text = ComboBoxDescricaoProduto->Text.SubString( 1, i - 1 );
    EditPreco->Text = PrecoItensComboBoxDescricaoProduto->Strings[ComboBoxDescricaoProduto->ItemIndex];
    PrecoItensComboBoxDescricaoProduto->Clear( );
    ComboBoxDescricaoProduto->Items->Clear( );
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxDescricaoProduto->DroppedDown ) ) {
    ComboBoxDescricaoProduto->Font->Size = 14;
    ComboBoxDescricaoProduto->Width = 225;
    ComboBoxDescricaoProduto->Clear( );
    ComboBoxDescricaoProduto->Items->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxDescricaoProduto->DroppedDown ) ) {
    EditQuantidade->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::EditPrecoKeyPress(TObject *Sender, char &Key ) {

  if( Key == 13 ) {
  	EditQuantidade->SetFocus( );
  }
  if( ( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
        ( this->EditPreco->Text.Length( ) <= 7 ) ) || ( Key == '\b' ) ) {
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
    if( this->EditPreco->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::EditQuantidadeKeyPress(TObject *Sender, char &Key ) {

	if( Key == 13 ) {
  	EditCpfCnpjCliente->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) &&
      ( AnsiCompareStr( Key, "9" ) <= 0 ) ) {
    if( ( this->EditQuantidade->Text.Length( ) == 0 ) && ( AnsiCompareStr( Key, "0" ) == 0 ) ) {
      Key = NULL;
    }
    if( this->EditQuantidade->Text.Length( ) >= 4 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::ComboBoxNomeClienteKeyDown( TObject *Sender,
      WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
        ( ( ComboBoxNomeCliente->Text ).Length( ) > 2 ) && ( !ComboBoxNomeCliente->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxNomeCliente->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome, RG, CPF" );
        Query->SQL->Add( "FROM Clientes" );
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( Trim( ComboBoxNomeCliente->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            if( Query->FieldByName( "CPF" )->AsString.IsEmpty( ) ) {
              this->ComboBoxNomeCliente->Items->Append( Query->FieldByName( "Nome" )->AsString + " " +
              Query->FieldByName( "RG" )->AsString );
            }
            else {
              this->ComboBoxNomeCliente->Items->Append( Query->FieldByName( "Nome" )->AsString + " " +
              Query->FieldByName( "CPF" )->AsString );
            }
            Query->Next( );
          }
          ComboBoxNomeCliente->Font->Size = 8;
          ComboBoxNomeCliente->Width = 500;
          ComboBoxNomeCliente->DroppedDown = true;
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Emissor de Cupom Fiscal", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( ComboBoxNomeCliente->DroppedDown ) ) {
    ComboBoxNomeCliente->Font->Size = 14;
    ComboBoxNomeCliente->Width = 277;
    for( i = ComboBoxNomeCliente->Text.Length( ); i > 0; i-- ) {
      if( ComboBoxNomeCliente->Text[i] == ' ' ) {
        EditCpfCnpjCliente->Text =  RightStr( ComboBoxNomeCliente->Text, ComboBoxNomeCliente->Text.Length( ) - i );
        ComboBoxNomeCliente->Text = ComboBoxNomeCliente->Text.SubString( 1, i - 1 );
        ComboBoxNomeCliente->Items->Clear( );
        break;
      }
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxNomeCliente->DroppedDown ) ) {
    ComboBoxNomeCliente->Font->Size = 14;
    ComboBoxNomeCliente->Width = 277;
    ComboBoxNomeCliente->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxNomeCliente->DroppedDown ) ) {
    ComboBoxDescricaoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::BitBtnConfirmarProdutoClick( TObject *Sender ) {

  if( ( EditCodigoProduto->Text.IsEmpty( ) ) || ( ComboBoxDescricaoProduto->Text.IsEmpty( ) ) ||
      ( EditPreco->Text.Length( ) < 4 ) || ( EditQuantidade->Text.IsEmpty( ) ) ) {
 	  Application->MessageBox( "Faltam Dados para o Produto!!!", "Emissor de Cupom Fiscal", MB_OK | MB_ICONERROR );
  }
 	else {
    if( !StringGridProdutos->Cells[0][1].IsEmpty( ) ) {
      StringGridProdutos->RowCount ++;
    }
    StringGridProdutos->Cells[0][StringGridProdutos->RowCount - 1] = Trim( ComboBoxDescricaoProduto->Text );
  	StringGridProdutos->Cells[1][StringGridProdutos->RowCount - 1] = EditQuantidade->Text;
    DecimalSeparator = ',';
    ThousandSeparator = '.';
  	StringGridProdutos->Cells[2][StringGridProdutos->RowCount - 1] = FormatFloat( "#,##0.00", EditPreco->Text.ToDouble( ) );
    StringGridProdutos->Cells[3][StringGridProdutos->RowCount - 1] = FormatFloat( "#,##0.00", EditQuantidade->Text.ToDouble( ) * StringReplace( EditPreco->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) );
    StringGridProdutos->Cells[4][StringGridProdutos->RowCount - 1] = Trim( EditCodigoProduto->Text );

    if( EditTotal->Text.IsEmpty( ) ) {
      EditTotal->Text = StringGridProdutos->Cells[3][StringGridProdutos->RowCount - 1];
    }
    else {
      DecimalSeparator = ',';
      ThousandSeparator = '.';
      EditTotal->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) + StrToFloat( StringReplace( StringGridProdutos->Cells[3][StringGridProdutos->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
    }
    EditCodigoProduto->Clear( );
    EditPreco->Clear( );
    EditQuantidade->Clear( );
    ComboBoxDescricaoProduto->Clear( );
    ComboBoxDescricaoProduto->SetFocus( );
  }    
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::StringGridProdutosKeyDown( TObject *Sender,
      WORD &Key, TShiftState Shift ) {

  int i, j;

  if( Key == VK_DELETE ) {

    if( StringGridProdutos->RowCount == 2 ) {
     	EditTotal->Clear( );
      StringGridProdutos->Rows[1]->Clear( );
    }
    else {
      ThousandSeparator = '.';
      DecimalSeparator = ',';
      EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) - StrToFloat( StringReplace( StringGridProdutos->Cells[3][StringGridProdutos->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
      for( i = StringGridProdutos->Row + 1; i < StringGridProdutos->RowCount; i++ ) {
      	  for( j = 0; j < StringGridProdutos->ColCount; j++ ) {
	      	  StringGridProdutos->Cells[j][i-1] = StringGridProdutos->Cells[j][i];
          }
        }
        if( StringGridProdutos->RowCount > 2 ) {
          StringGridProdutos->RowCount --;
        }
    }
    ComboBoxDescricaoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::BitBtnCancelarProdutoClick( TObject *Sender ) {

	int i, j, k;
  bool Ok;

	if( EditCodigoProduto->Text.IsEmpty( ) ) {
		Application->MessageBox( "O Campo Código está Vazio!!!", "Emissor de Cupom Fiscal", MB_OKCANCEL | MB_ICONERROR );
  }
  else if( StringGridProdutos->Cells[0][1].IsEmpty( ) ) {
		Application->MessageBox( "Não há Produto para ser Cancelado!!!", "Emissor de Cupom Fiscal", MB_OKCANCEL | MB_ICONERROR );
  }
  else {
    for( i = 1; i < StringGridProdutos->RowCount; i++ ) {
      if( StringGridProdutos->Cells[4][i] == Trim( EditCodigoProduto->Text ) ) {
      	if( StringGridProdutos->RowCount == 2 ) {
        	EditTotal->Clear( );
          StringGridProdutos->Rows[1]->Clear( );
        }
        else {
          ThousandSeparator = '.';
          DecimalSeparator = ',';
    	    EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) - StrToFloat( StringReplace( StringGridProdutos->Cells[3][i], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
        }
        for( j = i + 1; j < StringGridProdutos->RowCount; j++ ) {
      	  for( k = 0; k < StringGridProdutos->ColCount; k++ ) {
	      	  StringGridProdutos->Cells[k][j-1] = StringGridProdutos->Cells[k][j];
          }
        }
        if( StringGridProdutos->RowCount > 2 ) {
          StringGridProdutos->RowCount --;
        }
        EditQuantidade->Clear( );
        EditPreco->Clear( );
        ComboBoxDescricaoProduto->Clear( );
        EditCodigoProduto->Clear( );
        EditCodigoProduto->SetFocus( );
        Ok = true;
        break;
      }
      Ok = false;
    }
    if( !Ok ) {
      Application->MessageBox( "O Código Digitado não está na Venda!!!",
      												 "Emissor de Cupom Fiscal", MB_OK | MB_ICONERROR );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::BitBtnImprimirCupomFiscalClick( TObject *Sender ) {

	TCursor SaveCursor;
	//TImpressoraFiscalRfd *impressora;
  TImpressoraFiscalBematech *impressora;
  String *Erro, *TaxaIcms, *VTrocoPgto;
  int i;

  if( ( ComboBoxNomeVendedor->Text.IsEmpty( ) ) || ( ComboBoxIcms->Text.IsEmpty( ) ) ||
      ( StringGridProdutos->Cells[0][1].IsEmpty( ) ) ) {
  	Application->MessageBox( "Faltam Dados para a Venda!!!", "Emissor de Cupom Fiscal", MB_OK | MB_ICONERROR );
  }
  else {
    try {
    	SaveCursor = Screen->Cursor;
			Screen->Cursor = crHourGlass;
      BitBtnConfirmaProduto->Enabled = false;
      BitBtnCancelaProduto->Enabled = false;
      BitBtnImprimeCupom->Enabled = false;

      SecaoCritica->Acquire( );
      *FormPrincipal->ImpressoraEcfSemaforo = false;
      SecaoCritica->Release( );

    	impressora = new TImpressoraFiscalBematech( );
      Erro = new AnsiString( );
      if( ComboBoxIcms->Text == "Isento" ) {
        TaxaIcms = new AnsiString( "0" );
      }
      else {
        TaxaIcms = new AnsiString( ComboBoxIcms->Text );
      }
      VTrocoPgto = new AnsiString( "0" );

		  try {
        /*
	  		if( !impressora->AbrirCoxexaoSerial( Erro ) ) {
          throw Exception( *Erro );
        }
        */
        if( !impressora->AbrirCupomFiscal( &(EditCpfCnpjCliente->Text), Erro ) ) {
          throw Exception( *Erro );
        }
        for( i = 1; i < StringGridProdutos->RowCount; i++ ) {
          if( !impressora->LancarItemFiscal( &(StringGridProdutos->Cells[1][i]),
                                             &(StringGridProdutos->Cells[2][i]),
                                             TaxaIcms, &(StringGridProdutos->Cells[4][i]),
                                             &(StringGridProdutos->Cells[0][i]), Erro ) ) {
            throw Exception( *Erro );
          }
        }
        if( !impressora->TotalizarCupom( Erro ) ) {
          throw Exception( *Erro );
        }
        if( !impressora->Pagamento( &(ComboBoxTipoPagamento->Text), &(EditTotal->Text), Erro ) ) {
          throw Exception( *Erro );
        }
        /*
        // realiza troco
        if( !impressora->Pagamento( &(ComboBoxTipoPagamento->Text), VTrocoPgto, Erro ) ) {
          throw Exception( *Erro );
        }
        */
        if( !impressora->FecharCupomFiscal( &(Trim( ComboBoxNomeVendedor->Text )), Erro ) ) {
          throw Exception( *Erro );
        }
        //impressora->FecharConexaoSerial( );
      }
  		catch( Exception &e ) {
	    	Application->MessageBox( e.Message.c_str( ), "Emissão de Cupom", MB_OK | MB_ICONERROR );
		  }

      for( i = 1; i < StringGridProdutos->RowCount; i++ ) {
        StringGridProdutos->Rows[i]->Clear( );
      }
      StringGridProdutos->RowCount = 2;
      EditCodigoProduto->Clear( );
      ComboBoxDescricaoProduto->Clear( );
      EditPreco->Clear( );
      EditQuantidade->Clear( );
      EditCpfCnpjCliente->Clear( );
      ComboBoxNomeCliente->Clear( );
      EditTotal->Clear( );
      ComboBoxNomeVendedor->SetFocus( );
    }
    __finally {
      Screen->Cursor = SaveCursor;
      SecaoCritica->Acquire( );
      *FormPrincipal->ImpressoraEcfSemaforo = true;
      SecaoCritica->Release( );
      BitBtnConfirmaProduto->Enabled = true;
      BitBtnCancelaProduto->Enabled = true;
      BitBtnImprimeCupom->Enabled = true;
      delete impressora;
      delete TaxaIcms;
      delete VTrocoPgto;
      delete Erro;
    }
  }
}
//---------------------------------------------------------------------------




