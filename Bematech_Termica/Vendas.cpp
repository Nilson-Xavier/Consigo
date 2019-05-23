//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DescontoProduto.h"
#include "Dmod1.h"
#include "Dmod2.h"
#include "ThreadVendaCliente.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxTipoNotaFiscalKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift ) {

	if( ( Key == VK_RETURN ) && ( !ComboBoxTipoNotaFiscal->DroppedDown ) ) {
    ComboBoxVendedor->SetFocus( );
  }
  else if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) || ( Key == VK_LEFT ) ||
             ( Key == VK_RIGHT ) ) && ( !ComboBoxTipoNotaFiscal->DroppedDown ) ) {
  	ComboBoxTipoNotaFiscal->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxVendedorKeyDown( TObject *Sender,
      WORD &Key, TShiftState Shift ) {

  if( ( Key == VK_RETURN ) && ( !ComboBoxVendedor->DroppedDown ) ) {
    ComboBoxRgCnpj->SetFocus( );
  }
  else if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) || ( Key == VK_LEFT ) ||
             ( Key == VK_RIGHT ) ) && ( !ComboBoxVendedor->DroppedDown ) ) {
    ComboBoxVendedor->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxRgCnpjChange( TObject *Sender ) {

  if( ComboBoxRgCnpj->Text == "Sem RG" ) {
  	Label34->Visible = false;
    ComboBoxEERG->Visible = false;
  }
  else {
  	Label34->Visible = true;
    ComboBoxEERG->Visible = true;
    ComboBoxRgCnpj->BringToFront( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxRgCnpjKeyDown( TObject *Sender,
      WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
        ( ( ComboBoxRgCnpj->Text ).Length( ) > 2 ) && ( !ComboBoxRgCnpj->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxRgCnpj->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome, RG, EERG" );
        Query->SQL->Add( "FROM Clientes" );
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( Trim( ComboBoxRgCnpj->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            FormPrincipal->ComboBoxRgCnpj->Items->Append( Query->FieldByName( "Nome" )->AsString + " " +
            Query->FieldByName( "RG" )->AsString + Query->FieldByName( "EERG" )->AsString );
            Query->Next( );
          }
          ComboBoxRgCnpj->Font->Size = 8;
          ComboBoxRgCnpj->Width = 500;
          ComboBoxRgCnpj->DroppedDown = true;
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
  if( ( Key == VK_RETURN ) && ( ComboBoxRgCnpj->DroppedDown ) ) {
    ComboBoxRgCnpj->Font->Size = 12;
    ComboBoxRgCnpj->Width = 225;
    for( i = ComboBoxRgCnpj->Text.Length( ); i >= 1; i-- ) {
      if( ComboBoxRgCnpj->Text[i] == ' ' ) {
        ComboBoxEERG->ItemIndex = ComboBoxEERG->Items->IndexOf( UpperCase( ComboBoxRgCnpj->Text.SubString( ComboBoxRgCnpj->Text.Length( ) - 1, 2 ) ) );
        ComboBoxRgCnpj->Text = ComboBoxRgCnpj->Text.SubString( i + 1, ( ComboBoxRgCnpj->Text.Length( ) - i ) - 2 );
        break;
      }
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxRgCnpj->DroppedDown ) ) {
    ComboBoxRgCnpj->Font->Size = 12;
    ComboBoxRgCnpj->Width = 225;
    ComboBoxRgCnpj->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxRgCnpj->DroppedDown ) ) {
    ComboBoxCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxEERGKeyDown( TObject *Sender, WORD &Key, TShiftState Shift ) {

  if( ( ( Key == VK_SPACE ) || ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
           ( !ComboBoxEERG->DroppedDown ) ) {
   	 ComboBoxEERG->DroppedDown = true;
  }
	if( Key == VK_RETURN ) {
  	ComboBoxCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxCodigoProdutoKeyDown( TObject *Sender, WORD &Key,
    TShiftState Shift ) {

  TConsigoQuery *Query;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ( ComboBoxCodigoProduto->Text ).Length( ) > 2 ) &&
        ( !ComboBoxCodigoProduto->DroppedDown ) ) {
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
            FormPrincipal->ComboBoxCodigoProduto->Items->Append( Query->FieldByName( "Marca" )->AsString + " " +
              Query->FieldByName( "Nome" )->AsString + " " + Query->FieldByName( "Codigo" )->AsString );
            Query->Next( );
          }
          ComboBoxCodigoProduto->Font->Size = 8;
          ComboBoxCodigoProduto->Width = 500;
          ComboBoxCodigoProduto->DroppedDown = true;
          ComboBoxCodigoProduto->BringToFront( );
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
  if( ( Key == VK_RETURN ) && ( ComboBoxCodigoProduto->DroppedDown ) ) {
    ComboBoxCodigoProduto->Font->Size = 12;
    ComboBoxCodigoProduto->Width = 225;
    while( ( ComboBoxCodigoProduto->Text ).Pos( " " ) != 0 ) {
      ComboBoxCodigoProduto->Text = ( ComboBoxCodigoProduto->Text ).SubString( ( ComboBoxCodigoProduto->Text ).Pos( " " ) + 1, ( ComboBoxCodigoProduto->Text ).Length( ) );
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxCodigoProduto->DroppedDown ) ) {
    ComboBoxCodigoProduto->Font->Size = 12;
    ComboBoxCodigoProduto->Width = 225;
    ComboBoxCodigoProduto->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxCodigoProduto->DroppedDown ) ) {
    EditQuantidade->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditQuantidadeKeyPress(TObject *Sender, char &Key ) {

	if( Key == 13 ) {
  	EditNumeroSerie->SetFocus( );
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
void __fastcall TFormPrincipal::EditNumeroSerieKeyPress( TObject *Sender, char &Key ) {

	if( Key == 13 ) {
  	ComboBoxTipoVenda->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxTipoVendaKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

	if( ( Key == VK_RETURN ) && ( !ComboBoxTipoVenda->DroppedDown ) ) {
    EditEntrada->SetFocus( );
  }
  else if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) || ( Key == VK_LEFT ) ||
             ( Key == VK_RIGHT ) ) && ( !ComboBoxTipoVenda->DroppedDown ) ) {
  	ComboBoxTipoVenda->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxTipoVendaChange( TObject *Sender ) {

  if( ( ComboBoxTipoVenda->Text.SubString( 1, 7 ) == "A Prazo" ) ||
      ( ComboBoxTipoVenda->Text.SubString( 1, 14 ) == "Cartao Debito " ) ||
      ( ComboBoxTipoVenda->Text.SubString( 1, 15 ) == "Cartao Credito " ) ||
      ( ComboBoxTipoVenda->Text.SubString( 1, 18 ) == "Cheque Eletronico " ) ) {
  	LabelEntrada->Visible = true;
    LabelParcela->Visible = true;
    EditEntrada->Visible = true;
    EditParcela->Visible = true;
  }
  else {
  	LabelEntrada->Visible = false;
    LabelParcela->Visible = false;
    EditEntrada->Visible = false;
    EditParcela->Visible = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditEntradaKeyPress(TObject *Sender, char &Key ) {

  if( Key == 13 ) {
  	EditParcela->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditEntrada->Text.Length( ) <= 7 ) || ( Key == '\b' ) ) {
    if( this->EditEntrada->Text.Length( ) >= 2 ) {
      this->EditEntrada->Text = this->EditEntrada->Text.Delete( this->EditEntrada->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditEntrada->Text.Length( ) >= 4 ) ) {
        this->EditEntrada->Text = this->EditEntrada->Text.Insert( ",", this->EditEntrada->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditEntrada->Text = this->EditEntrada->Text.Insert( ",", this->EditEntrada->Text.Length( ) );
      }
      this->EditEntrada->SelStart = this->EditEntrada->Text.Length( );
    }
    if( this->EditEntrada->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditParcelaKeyPress(TObject *Sender, char &Key ) {

  if( Key == 13 ) {
  	BitBtnCancelarProduto->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditEntrada->Text.Length( ) <= 7 ) || ( Key == '\b' ) ) {
    if( this->EditParcela->Text.Length( ) >= 2 ) {
      this->EditParcela->Text = this->EditParcela->Text.Delete( this->EditParcela->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditParcela->Text.Length( ) >= 4 ) ) {
        this->EditParcela->Text = this->EditParcela->Text.Insert( ",", this->EditParcela->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditParcela->Text = this->EditParcela->Text.Insert( ",", this->EditParcela->Text.Length( ) );
      }
      this->EditParcela->SelStart = this->EditParcela->Text.Length( );
    }
    if( this->EditEntrada->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::StrGridVendaProdutoKeyDown( TObject *Sender,
      WORD &Key, TShiftState Shift ) {

  int i, j;

  if( Key == VK_DELETE ) {

    if( StrGridVendaProduto->RowCount == 2 ) {
     	EditTotal2->Clear( );
    }
    else {
      DecimalSeparator = ',';
      ThousandSeparator = '.';
      EditTotal2->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotal2->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) - StringReplace( StrGridVendaProduto->Cells[4][StrGridVendaProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) );
    }
    for( i = StrGridVendaProduto->Row + 1; i <= StrGridVendaProduto->RowCount; i++ ) {
      for( j = 0; j <= 7; j++ ) {
        StrGridVendaProduto->Cells[j][i-1] = StrGridVendaProduto->Cells[j][i];
      }
    }
    if( StrGridVendaProduto->RowCount != 2 ) {
      StrGridVendaProduto->RowCount --;
    }
    ComboBoxCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnCancelarProdutoClick( TObject *Sender ) {

  Boolean Ok;
  int i, j, k;
  String Preco, Preco2;

  if( Trim( ComboBoxCodigoProduto->Text ) == "" ) {
    Application->MessageBox( "Você precisa digitar o Codigo do Produto!",
                "Vendas", MB_OK | MB_ICONWARNING );
    ComboBoxCodigoProduto->SetFocus( );
  }
  else if ( Application->MessageBox( "Você digitou o Codigo do Produto CORRETAMENTE?",
            "Vendas", MB_YESNO | MB_ICONQUESTION ) == ID_YES ) {

    for( i = 1; i < StrGridVendaProduto->RowCount; i++ ) {
      if( LowerCase( StrGridVendaProduto->Cells[5][i] ) == LowerCase( Trim( ComboBoxCodigoProduto->Text ) ) ) {
        Ok = true;
        break;
      }
      else {
        Ok = false;
      }
    }
    if( !Ok ) {
      Application->MessageBox( "O Codigo do Produto não está na venda!", "Vendas",
                  MB_OK | MB_ICONWARNING );
      ComboBoxCodigoProduto->SetFocus( );
    }
    else {
    	if( StrGridVendaProduto->RowCount == 2 ) {
      	EditTotal2->Text = "";
      }
      else {
	      Preco = StringReplace( EditTotal2->Text, ".", "", TReplaceFlags( ) << rfReplaceAll );
  	    Preco2 = StringReplace( StrGridVendaProduto->Cells[4][i], ".", "", TReplaceFlags( ) << rfReplaceAll );
    	  DecimalSeparator = ',';
      	ThousandSeparator = '.';
      	EditTotal2->Text = FormatFloat( "#,##0.00", ( Preco.ToDouble( ) - Preco2.ToDouble( ) ) );
      }
      for( j = i + 1; j <= StrGridVendaProduto->RowCount; j++ ) {
        for( k = 0; k <= 7; k++ ) {
          StrGridVendaProduto->Cells[k][j-1] = StrGridVendaProduto->Cells[k][j];
        }
      }
      if( StrGridVendaProduto->RowCount != 2 ) {
        StrGridVendaProduto->RowCount --;
      }
      ComboBoxCodigoProduto->SetFocus( );
    }
  }
  else {
    ComboBoxCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnConfirmarProdutoClick( TObject *Sender ) {

  int i;
  bool Desconto;
  TDateTime *Data;
  String *ValorDesconto;
  TConsigoQuery *Query;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    ValorDesconto = new AnsiString( );
    Data = new TDateTime( );

    try {
  	  if( ( ComboBoxCodigoProduto->Text.IsEmpty( ) ) || ( EditQuantidade->Text.IsEmpty( ) ) ) {
    	  throw Exception( "Faltam Dados para o Produto!!!" );
  	  }
      else if( StrGridVendaProduto->RowCount == 17 ) {
        throw Exception( "A Venda NÃO Pode Ter Mais que 16 Itens !!!" );
      }
    	else {
        Query->SQL->Add( "SELECT 	Codigo, Marca, Nome, Quantidade, ( Preco * Dolar ) AS Preco, Garantia" );
        Query->SQL->Add( "FROM Produtos" );
        Query->SQL->Add( "WHERE Codigo = '" + Trim( ComboBoxCodigoProduto->Text ) + "'" );
        Query->Prepare( );
        Query->Open( );
        if( Query->IsEmpty( ) ) {
          throw Exception( "O Produto com Código: " + Trim( ComboBoxCodigoProduto->Text ) + " NÃO Existe!!!" );
        }
        else if( Trim( EditQuantidade->Text ).ToInt( ) <= Query->FieldByName( "Quantidade" )->AsInteger ) {
          if( StrGridVendaProduto->Cells[0][1] != "" ) {
          	StrGridVendaProduto->RowCount ++;
          }
	        StrGridVendaProduto->Cells[0][StrGridVendaProduto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
  	      StrGridVendaProduto->Cells[1][StrGridVendaProduto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
  	      StrGridVendaProduto->Cells[2][StrGridVendaProduto->RowCount - 1] = Trim( EditQuantidade->Text );
    	    DecimalSeparator = ',';
      	  ThousandSeparator = '.';

          do {
            this->DescontoExibir( ValorDesconto, Desconto );
          } while( ( Desconto ) && ( Query->FieldByName( "Preco" )->AsFloat - StrToFloat( *ValorDesconto ) <= 0  ) );

          if( ValorDesconto->IsEmpty( ) ) {
            StrGridVendaProduto->Cells[3][StrGridVendaProduto->RowCount - 1] = FloatToStrF( Query->FieldByName( "Preco" )->AsFloat, ffNumber, 15, 2 );
          }
          else {
  					if( Desconto ) {
	          	StrGridVendaProduto->Cells[3][StrGridVendaProduto->RowCount - 1] = FloatToStrF( ( Query->FieldByName( "Preco" )->AsFloat - StrToFloat( StringReplace( *ValorDesconto, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ), ffNumber, 15, 2 );
            }
            else {
            	StrGridVendaProduto->Cells[3][StrGridVendaProduto->RowCount - 1] = FloatToStrF( ( Query->FieldByName( "Preco" )->AsFloat + StrToFloat( StringReplace( *ValorDesconto, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ), ffNumber, 15, 2 );
            }
          }
    	    DecimalSeparator = ',';
      	  ThousandSeparator = '.';
          StrGridVendaProduto->Cells[4][StrGridVendaProduto->RowCount - 1] = FormatFloat( "#,##0.00", EditQuantidade->Text.ToDouble( ) * StrToFloat( StringReplace( StrGridVendaProduto->Cells[3][StrGridVendaProduto->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
	        StrGridVendaProduto->Cells[5][StrGridVendaProduto->RowCount - 1] = Trim( Query->FieldByName( "Codigo" )->AsString );
  	      StrGridVendaProduto->Cells[6][StrGridVendaProduto->RowCount - 1] = Trim( EditNumeroSerie->Text );
    	    StrGridVendaProduto->Cells[7][StrGridVendaProduto->RowCount - 1] = Trim( Query->FieldByName( "Garantia" )->AsString );
      	  DateSeparator = '/';
        	StrGridVendaProduto->Cells[8][StrGridVendaProduto->RowCount - 1] = Data->CurrentDate( ).DateString( );

	        if( Trim( EditTotal2->Text ) == "" ) {
  	        DecimalSeparator = ',';
    	      ThousandSeparator = '.';
            EditTotal2->Text = StrGridVendaProduto->Cells[4][StrGridVendaProduto->RowCount - 1];
        	}
	        else {
      	    DecimalSeparator = ',';
        	  ThousandSeparator = '.';
          	EditTotal2->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotal2->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) + StrToFloat( StringReplace( StrGridVendaProduto->Cells[4][StrGridVendaProduto->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
	        }
    	    EditNumeroSerie->Clear( );
        	EditQuantidade->Clear( );
       	  ComboBoxCodigoProduto->Clear( );
          ComboBoxCodigoProduto->SetFocus( );
        }
        else {
          throw Exception( "NÃO há em Estoque a Quantidade Desejada para este Produto!!!" );
        }
      }

    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Vendas", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete ValorDesconto;
    delete Data;
  }
}
//---------------------------------------------------------------------------
void TFormPrincipal::DescontoExibir( String *&Valor, bool &Desconto ) {

  TFormDescontoProduto *FormDescontoProduto;

  try {
    FormDescontoProduto = new TFormDescontoProduto( FormPrincipal );

    if( FormDescontoProduto->ShowModal( ) == 1 ) {
      if( !FormDescontoProduto->EditDescontoProduto->Text.IsEmpty( ) ) {
        *Valor = FormDescontoProduto->EditDescontoProduto->Text.Trim( );
      }
      else {
        *Valor = "0";
      }
      if( FormDescontoProduto->RadioButtonDesconto->Checked ) {
        Desconto = true;
      }
      else {
        Desconto = false;
      }
    }
  }
  __finally {
    FormDescontoProduto = NULL;
    delete FormDescontoProduto;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnCancelarVendaClick( TObject *Sender ) {

  int Resposta;
  String *NumeroCupom;
  bool *Ok;

  try {
    NumeroCupom = new AnsiString( );
    Ok = new bool( false );

    this->SenhaExibir( Ok );
    if( *Ok ) {
      Resposta = Application->MessageBox( "Deseja Realmente Cancelar o Cupom Fiscal !", "Vendas", MB_YESNOCANCEL | MB_ICONQUESTION );
      if( ( Resposta == IDYES ) || ( Resposta == IDNO ) ) {
        if( !InputQuery( "Vendas", "Digite o Número do Cupom Fiscal:", *NumeroCupom ) ) {
          Resposta = IDCANCEL;
        }
      }
      if( Resposta == IDYES ) {
        this->CancelarVendaFiscal( NumeroCupom->ToInt( ) );
      }
      else if( Resposta == IDNO ) {
        this->CancelarVenda( NumeroCupom->ToInt( ) );
      }
    }
  }
  __finally {
    delete NumeroCupom;
    delete Ok;
  }
}
//---------------------------------------------------------------------------
void TFormPrincipal::CancelarVendaFiscal( int NumeroCupomFiscal ) {

  TConsigoQuery *Query;
  String *Mensagem;

  try {
    Mensagem = new AnsiString( );
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    try {
      Query->SQL->Add( "SELECT Produtos.Marca, Produtos.Nome, Vendem.Quantidade," );
      Query->SQL->Add( "( Vendem.Preco / Vendem.Quantidade ) AS PrecoUnit," );
      Query->SQL->Add( "( Vendem.Preco ) AS PrecoTot,  Vendem.Data," );
      Query->SQL->Add( "Vendedores.Nome AS Vendedor" );
      Query->SQL->Add( "FROM Produtos, Vendedores, Vendem" );
      Query->SQL->Add( "WHERE Vendem.Numero_nota = '" + IntToStr( NumeroCupomFiscal ) + "'" );
      Query->SQL->Add( "AND Vendem.Codigo = Produtos.Codigo" );
      Query->SQL->Add( "AND Vendem.RG_Vendedor = Vendedores.RG" );
      Query->SQL->Add( "AND Vendem.EERG_Vendedor = Vendedores.EERG" );
      Query->SQL->Add( "ORDER BY Data ASC" );
      Query->Prepare( );
      Query->Open( );
      Query->First( );
      if( Query->IsEmpty( ) ) {
        *Mensagem = "Cupom Fiscal nº " + IntToStr( NumeroCupomFiscal ) + " Inexistente !";
        Application->MessageBox( Mensagem->c_str( ), "Vendas", MB_OK | MB_ICONERROR );
      }
      else {
        *Mensagem = "Você tem certeza que deseja Cancelar a Venda: \r\rCupom: " +
          IntToStr( NumeroCupomFiscal ) + "  Data: " + Query->FieldByName( "Data" )->AsString +
          "  Vendedor: " + Query->FieldByName( "Vendedor" )->AsString + "\r\r";
        while( !Query->Eof ) {
          DecimalSeparator = ',';
          ThousandSeparator = '.';
          *Mensagem = *Mensagem + Query->FieldByName( "Marca" )->AsString + " " +
             Query->FieldByName( "Nome" )->AsString + " " + Query->FieldByName( "Quantidade" )->AsString + " x " +
             FormatFloat( "#,##0.00", Query->FieldByName( "PrecoUnit" )->AsFloat ) + " = " +
             FormatFloat( "#,##0.00", Query->FieldByName( "PrecoTot" )->AsFloat ) + "\r";
          Query->Next( );
        }
        if( Application->MessageBox( Mensagem->c_str( ), "Vendas", MB_YESNO | MB_ICONQUESTION ) == IDYES ) {
          Query->Close( );
          Query->SQL->Clear( );
          Query->SQL->Add( "BEGIN TRANSACTION" );
          Query->SQL->Add( "UPDATE Produtos" );
          Query->SQL->Add( "SET Produtos.Quantidade = Produtos.Quantidade + ( SELECT Vendem.Quantidade" );
          Query->SQL->Add( "                                                  FROM Vendem, Produtos" );
          Query->SQL->Add( "                                                  WHERE Numero_nota = " + IntToStr( NumeroCupomFiscal ) );
          Query->SQL->Add( "                                                  AND Vendem.Codigo = Produtos.Codigo )," );
          Query->SQL->Add( "Produtos.Quantidade_ = Produtos.Quantidade_ + ( SELECT Vendem.Quantidade" );
          Query->SQL->Add( "                                                FROM Vendem, Produtos" );
          Query->SQL->Add( "                                                WHERE Numero_nota = " + IntToStr( NumeroCupomFiscal ) );
          Query->SQL->Add( "                                                AND Vendem.Codigo = Produtos.Codigo )" );
          Query->SQL->Add( "  FROM Vendem, Produtos" );
          Query->SQL->Add( "  WHERE Numero_nota = " + IntToStr( NumeroCupomFiscal ) );
          Query->SQL->Add( "  AND Vendem.Codigo = Produtos.Codigo" );
          Query->SQL->Add( "DELETE FROM Vendem " );
          Query->SQL->Add( "WHERE Numero_nota = '" + IntToStr( NumeroCupomFiscal ) + "'" );
          Query->Prepare( );
          Query->ExecSQL( );
          Query->SQL->Add( "COMMIT TRANSACTION" );

          Application->MessageBox( "A Venda foi Cancelada com Sucesso !", "Vendas", MB_OK | MB_ICONINFORMATION );
        }
      }
    }
    catch( Exception &e ) {
      if( DataModuleQuery->consigo_BD->InTransaction ) {
        DataModuleQuery->consigo_BD->Rollback( );
      }
      Application->MessageBox( e.Message.c_str( ), "Vendas", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete Mensagem;
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
void TFormPrincipal::CancelarVenda( int NumeroCupom ) {

  TConsigoQuery *Query;
  String *Mensagem;

  try {
    Mensagem = new AnsiString( );
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    try {
      Query->SQL->Add( "SELECT Produtos.Marca, Produtos.Nome, Vendem2.Quantidade," );
      Query->SQL->Add( "( Vendem2.Preco / Vendem2.Quantidade ) AS PrecoUnit," );
      Query->SQL->Add( "( Vendem2.Preco ) AS PrecoTot,  Vendem2.Data," );
      Query->SQL->Add( "Vendedores.Nome AS Vendedor" );
      Query->SQL->Add( "FROM Produtos, Vendedores, Vendem2" );
      Query->SQL->Add( "WHERE Vendem2.Numero_nota = '" + IntToStr( NumeroCupom ) + "'" );
      Query->SQL->Add( "AND Vendem2.Codigo = Produtos.Codigo" );
      Query->SQL->Add( "AND Vendem2.RG_Vendedor = Vendedores.RG" );
      Query->SQL->Add( "AND Vendem2.EERG_Vendedor = Vendedores.EERG" );
      Query->SQL->Add( "ORDER BY Data ASC" );
      Query->Prepare( );
      Query->Open( );
      Query->First( );
      if( Query->IsEmpty( ) ) {
        *Mensagem = "Cupom Fiscal nº " + IntToStr( NumeroCupom ) + " Inexistente !";
        Application->MessageBox( Mensagem->c_str( ), "Vendas", MB_OK | MB_ICONERROR );
      }
      else {
        *Mensagem = "Você tem certeza que deseja Cancelar a Venda: \r\rCupom: " +
          IntToStr( NumeroCupom ) + "  Data: " + Query->FieldByName( "Data" )->AsString +
          "  Vendedor: " + Query->FieldByName( "Vendedor" )->AsString + "\r\r";
        while( !Query->Eof ) {
          DecimalSeparator = ',';
          ThousandSeparator = '.';
          *Mensagem = *Mensagem + Query->FieldByName( "Marca" )->AsString + " " +
             Query->FieldByName( "Nome" )->AsString + " " + Query->FieldByName( "Quantidade" )->AsString + " x " +
             FormatFloat( "#,##0.00", Query->FieldByName( "PrecoUnit" )->AsFloat ) + " = " +
             FormatFloat( "#,##0.00", Query->FieldByName( "PrecoTot" )->AsFloat ) + "\r";
          Query->Next( );
        }
        if( Application->MessageBox( Mensagem->c_str( ), "Vendas", MB_YESNO | MB_ICONQUESTION ) == IDYES ) {

          Query->Close( );
          Query->SQL->Clear( );
          Query->SQL->Add( "BEGIN TRANSACTION" );
          Query->SQL->Add( "UPDATE Produtos" );
          Query->SQL->Add( "SET Produtos.Quantidade = Produtos.Quantidade + ( SELECT Vendem2.Quantidade" );
          Query->SQL->Add( "                                                  FROM Vendem2, Produtos" );
          Query->SQL->Add( "                                                  WHERE Numero_nota = " + IntToStr( NumeroCupom ) );
          Query->SQL->Add( "                                                  AND Vendem2.Codigo = Produtos.Codigo )" );
          Query->SQL->Add( "  FROM Vendem2, Produtos" );
          Query->SQL->Add( "  WHERE Numero_nota = " + IntToStr( NumeroCupom ) );
          Query->SQL->Add( "  AND Vendem2.Codigo = Produtos.Codigo" );
          Query->SQL->Add( "DELETE FROM Vendem2" );
          Query->SQL->Add( "WHERE Numero_nota = " + IntToStr( NumeroCupom ) );
          Query->SQL->Add( "COMMIT TRANSACTION" );
          Query->Prepare( );
          Query->ExecSQL( );

          Application->MessageBox( "A Venda foi Cancelada com Sucesso !", "Vendas", MB_OK | MB_ICONINFORMATION );
        }
      }
    }
    catch( Exception &e ) {
      if( DataModuleQuery->consigo_BD->InTransaction ) {
        DataModuleQuery->consigo_BD->Rollback( );
      }
      Application->MessageBox( e.Message.c_str( ), "Vendas", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete Mensagem;
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnConfirmarVendaClick( TObject *Sender ) {

  TVendaClienteThread *ThreadVenda;
  String *Resposta, *Impressora;
  TConsigoQuery *Query;
  int i;
  
  try {
    Resposta = new AnsiString( );
    Impressora = new AnsiString( );
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    if( ( FormPrincipal->StrGridVendaProduto->RowCount == 2 ) &&
        ( FormPrincipal->StrGridVendaProduto->Cells[1][1].IsEmpty( ) ) ) {
      Application->MessageBox( "Não há Produto(s) para Realizar uma Venda !", "Vendas",
		  				                 MB_OK | MB_ICONWARNING );
      FormPrincipal->ComboBoxCodigoProduto->SetFocus( );
    }
    else if( ( FormPrincipal->ComboBoxTipoNotaFiscal->Text.IsEmpty( ) ) ||
             ( FormPrincipal->ComboBoxVendedor->Text.IsEmpty( ) ) ||
             ( FormPrincipal->ComboBoxTipoVenda->Text.IsEmpty( ) ) ) {
      Application->MessageBox( "Faltam Campos a serem Preenchidos para a Venda !", "Vendas",
	  					                 MB_OK | MB_ICONERROR );
      FormPrincipal->ComboBoxTipoNotaFiscal->SetFocus( );
    }
    else if( ( FormPrincipal->EditTotal2->Text == "0,00" ) || ( FormPrincipal->EditTotal2->Text.IsEmpty( ) ) ) {
      Application->MessageBox( "Não é Possível Realizar a Venda com Valor Total 0,00 !", "Vendas",
	  					                 MB_OK | MB_ICONERROR );
    }
    else if( ( ( ComboBoxTipoVenda->Text.SubString( 1, 7 ) == "A Prazo" ) ||
               ( ComboBoxTipoVenda->Text.SubString( 1, 14 ) == "Cartao Debito " ) ||
               ( ComboBoxTipoVenda->Text.SubString( 1, 15 ) == "Cartao Credito " ) ||
               ( ComboBoxTipoVenda->Text.SubString( 1, 18 ) == "Cheque Eletronico " ) ) &&
             ( ( EditEntrada->Text.Length( ) < 4 ) || ( EditParcela->Text.Length( ) < 4 ) ) ) {
      Application->MessageBox( "Venda Parcelada !\r\rPreencha os Campos 'Entrada' e 'Parcela'.", "Vendas",
	  					                 MB_OK | MB_ICONWARNING );
      EditEntrada->SetFocus( );
    }
    else if( ( ( ComboBoxTipoVenda->Text == "Cheque" ) ||
               ( ComboBoxTipoVenda->Text.SubString( 1, 7 ) == "A Prazo" ) ||
               ( ComboBoxTipoVenda->Text.SubString( 1, 14 ) == "Cartao Debito " ) ||
               ( ComboBoxTipoVenda->Text.SubString( 1, 15 ) == "Cartao Credito " ) ||
               ( ComboBoxTipoVenda->Text.SubString( 1, 18 ) == "Cheque Eletronico " ) ) &&
               ( ( FormPrincipal->ComboBoxRgCnpj->Text == "Sem RG" ) ||
                 ( FormPrincipal->ComboBoxRgCnpj->Text.IsEmpty( ) ) ) ) {
      if( Application->MessageBox( "Para Pagamento com Cheque ou Parcelado,\rÉ Necessário RG/CNPJ do Cliente !\r\rDeseja Continuar com a Venda ?", "Vendas",
	  					                     MB_YESNO | MB_ICONWARNING ) == IDYES ) {
        *Resposta = Application->MessageBox( "Os Dados para a Venda Estão Corretos ?", "Vendas",
                                             MB_YESNOCANCEL | MB_ICONWARNING );
      }
    }
    else {
      *Resposta = Application->MessageBox( "Os Dados para a Venda Estão Corretos ?", "Vendas",
	  					                 MB_YESNOCANCEL | MB_ICONWARNING );
    }
    if( *Resposta == IDYES ) {
      *Impressora = "1";
      for( i = 1; i < this->StrGridVendaProduto->RowCount; i++ ) {
        Query->SQL->Clear( );
        Query->SQL->Add( "SELECT Quantidade_" );
        Query->SQL->Add( "  FROM PRODUTOS" );
        Query->SQL->Add( "  WHERE Codigo = '" + this->StrGridVendaProduto->Cells[5][i] + "'" );
        Query->Open( );
        if( this->StrGridVendaProduto->Cells[2][i].ToInt( ) > Query->FieldByName( "Quantidade_" )->AsInteger ) {
          Application->MessageBox( "NÃO Há Quantidade Em Estoque Para Os Produtos !",
                                   "Vendas", MB_OK | MB_ICONWARNING );
          *Resposta = IDNO;
          break;
        }
        Query->Close( );
      }
      if( *Resposta == IDYES ) {
        ThreadVenda = new TVendaClienteThread( false, Impressora );
      }
    }
    else if( *Resposta == IDNO ) {
      *Impressora = "2";
      ThreadVenda = new TVendaClienteThread( false, Impressora );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete Resposta;
    delete Impressora;
  }
}
//---------------------------------------------------------------------------

