//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Dmod1.h"
#include "Dmod2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemEntradasClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetEntrada;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ComboBoxCnpjKeyDown(TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ( ComboBoxCnpj->Text ).Length( ) > 2 ) &&
        ( !ComboBoxCnpj->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxCnpj->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome, CGC" );
        Query->SQL->Add( "FROM Fornecedores" );
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( Trim( ComboBoxCnpj->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            this->ComboBoxCnpj->Items->Append( Query->FieldByName( "Nome" )->AsString + " " +
            Query->FieldByName( "CGC" )->AsString );
            Query->Next( );
          }
          ComboBoxCnpj->Font->Size = 8;
          ComboBoxCnpj->Width = 500;
          ComboBoxCnpj->DroppedDown = true;
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Entrada de Produtos", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( ComboBoxCnpj->DroppedDown ) ) {
    ComboBoxCnpj->Font->Size = 14;
    ComboBoxCnpj->Width = 225;

    for( i = ComboBoxCnpj->Text.Length( ); i >= 1; i-- ) {
      if( ComboBoxCnpj->Text[i] == ' ' ) {
        ComboBoxCnpj->Text = ComboBoxCnpj->Text.Delete( 1, i );
        break;
      }
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxCnpj->DroppedDown ) ) {
    ComboBoxCnpj->Font->Size = 12;
    ComboBoxCnpj->Width = 225;
    ComboBoxCnpj->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxCnpj->DroppedDown ) ) {
    EditNotaFiscal->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ComboBoxCodigoProdutoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

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
            this->ComboBoxCodigoProduto->Items->Append( Query->FieldByName( "Marca" )->AsString + " " +
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
    EditQuantidade->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditNotaFiscalKeyPress( TObject *Sender, char &Key ) {

  TConsigoQuery *Query;
	int i;

	if( Key == 13 ) {
  	for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
     	StringGridEntradaProduto->Rows[i]->Clear( );
		}
    StringGridEntradaProduto->RowCount = 2;
    EditTotalEntrada->Clear( );

    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

      try {
        if( ( Trim( ComboBoxCnpj->Text ).IsEmpty( ) ) || ( Trim( EditNotaFiscal->Text ).IsEmpty( ) ) ) {
        	throw Exception( "Você Deve Digitar o CGC e o Número da Nota Fiscal" );

        }
        else {
        	if( Application->MessageBox( "A Compra Possui Nota Fiscal?", "Entrada de Produtos",
              MB_YESNO | MB_ICONQUESTION ) == IDYES ) {
            Query->SQL->Add( "SELECT Produtos.Marca, Produtos.Nome, Fornecedores_Vendem.Quantidade," );
            Query->SQL->Add( "Fornecedores_Vendem.Preco_Custo, Fornecedores_Vendem.Data," );
            Query->SQL->Add( "Fornecedores.Nome AS Fornecedor, Fornecedores_Vendem.Numero_nota," );
            Query->SQL->Add( "Produtos.Codigo" );
            Query->SQL->Add( "FROM Produtos, Fornecedores_Vendem, Fornecedores" );
            Query->SQL->Add( "WHERE Fornecedores_Vendem.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
            Query->SQL->Add( "AND   Fornecedores_Vendem.CGC = '" + ComboBoxCnpj->Text + "'" );
            Query->SQL->Add( "AND   Fornecedores_Vendem.CGC = Fornecedores.CGC" );
            Query->SQL->Add( "AND   Produtos.Codigo = Fornecedores_Vendem.Codigo" );
            Query->SQL->Add( "ORDER BY Fornecedores_Vendem.Data" );
    			  Query->Open( );
        	  if( Query->IsEmpty( ) ) {
        		  throw Exception( "Nota Fiscal de Compra Inexistente !" );
    	      }
      	    else {
              Query->First( );
              while( !Query->Eof ) {
                if( !StringGridEntradaProduto->Cells[0][1].IsEmpty( ) ) {
                	StringGridEntradaProduto->RowCount++;
                }
                StringGridEntradaProduto->Cells[0][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
                StringGridEntradaProduto->Cells[1][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
                StringGridEntradaProduto->Cells[2][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
                ThousandSeparator = '.';
                DecimalSeparator = ',';
                StringGridEntradaProduto->Cells[3][StringGridEntradaProduto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco_Custo" )->AsFloat );
                StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1] = FormatFloat( "#,##0.00", ( Query->FieldByName( "Quantidade" )->AsInteger * Query->FieldByName( "Preco_Custo" )->AsFloat ) );
                StringGridEntradaProduto->Cells[5][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Data" )->AsDateTime.FormatString( "dd/mm/yy hh:mm:ss" );
                StringGridEntradaProduto->Cells[6][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Codigo" )->AsString;
                if( EditTotalEntrada->Text.IsEmpty( ) ) {
              	  EditTotalEntrada->Text = StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1];
                }
                else {
                  EditTotalEntrada->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotalEntrada->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + StrToFloat( StringReplace( StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
                }
              	Query->Next( );
              }
            }
        	}
          else {
            Query->SQL->Add( "SELECT Produtos.Marca, Produtos.Nome, Vendem1.Quantidade," );
            Query->SQL->Add( "Vendem1.Preco, Vendem1.Data," );
            Query->SQL->Add( "Fornecedores.Nome AS Fornecedor, Vendem1.Numero_nota," );
            Query->SQL->Add( "Produtos.Codigo" );
            Query->SQL->Add( "FROM Produtos, Vendem1, Fornecedores" );
            Query->SQL->Add( "WHERE Vendem1.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
            Query->SQL->Add( "AND   Vendem1.CGC = '" + ComboBoxCnpj->Text + "'" );
            Query->SQL->Add( "AND   Vendem1.CGC = Fornecedores.CGC" );
            Query->SQL->Add( "AND   Produtos.Codigo = Vendem1.Codigo" );
            Query->SQL->Add( "ORDER BY Vendem1.Data" );
    			  Query->Open( );
        	  if( Query->IsEmpty( ) ) {
        		  throw Exception( "Nota Fiscal de Compra Inexistente !" );
    	      }
      	    else {
              Query->First( );
              while( !Query->Eof ) {
                if( !StringGridEntradaProduto->Cells[0][1].IsEmpty( ) ) {
                	StringGridEntradaProduto->RowCount++;
                }
                StringGridEntradaProduto->Cells[0][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
                StringGridEntradaProduto->Cells[1][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
                StringGridEntradaProduto->Cells[2][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
                ThousandSeparator = '.';
                DecimalSeparator = ',';
                StringGridEntradaProduto->Cells[3][StringGridEntradaProduto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
                StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1] = FormatFloat( "#,##0.00", ( Query->FieldByName( "Quantidade" )->AsInteger * Query->FieldByName( "Preco" )->AsFloat ) );
                StringGridEntradaProduto->Cells[5][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Data" )->AsDateTime.FormatString( "dd/mm/yy hh:mm:ss" );
                StringGridEntradaProduto->Cells[6][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Codigo" )->AsString;
                if( EditTotalEntrada->Text.IsEmpty( ) ) {
              	  EditTotalEntrada->Text = StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1];
                }
                else {
                  EditTotalEntrada->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotalEntrada->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + StrToFloat( StringReplace( StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
                }
              	Query->Next( );
              }
            }
        	}
        }
      }
      catch( Exception &e ) {
  	  	for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
   				StringGridEntradaProduto->Rows[i]->Clear( );
	  		}
		    StringGridEntradaProduto->RowCount = 2;
    		Application->MessageBox( e.Message.c_str( ), "Entrada de Produtos", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
  if( !( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ||
         ( Key == '\b' ) ) ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditQuantidadeKeyPress( TObject *Sender, char &Key ) {

	if( Key == 13 ) {
  	EditEntradaPreco->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ) {
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
void __fastcall TFormGerencia::EditEntradaPrecoKeyPress(TObject *Sender, char &Key ) {

  if( Key == 13 ) {
  	BitBtnConfirmaProduto->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditEntradaPreco->Text.Length( ) <= 7 ) || ( Key == '\b' ) ) {
    if( this->EditEntradaPreco->Text.Length( ) >= 2 ) {
      this->EditEntradaPreco->Text = this->EditEntradaPreco->Text.Delete( this->EditEntradaPreco->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditEntradaPreco->Text.Length( ) >= 4 ) ) {
        this->EditEntradaPreco->Text = this->EditEntradaPreco->Text.Insert( ",", this->EditEntradaPreco->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditEntradaPreco->Text = this->EditEntradaPreco->Text.Insert( ",", this->EditEntradaPreco->Text.Length( ) );
      }
      this->EditEntradaPreco->SelStart = this->EditEntradaPreco->Text.Length( );
    }
    if( this->EditEntradaPreco->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridEntradaProdutoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  int i, j;

  if( Key == VK_DELETE ) {

    if( StringGridEntradaProduto->RowCount == 2 ) {
     	EditTotalEntrada->Clear( );
    }
    else {
      DecimalSeparator = ',';
      ThousandSeparator = '.';
      EditTotalEntrada->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotalEntrada->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) - StringReplace( StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) );
    }
    for( i = StringGridEntradaProduto->Row + 1; i <= StringGridEntradaProduto->RowCount; i++ ) {
      for( j = 0; j <= 7; j++ ) {
        StringGridEntradaProduto->Cells[j][i-1] = StringGridEntradaProduto->Cells[j][i];
      }
    }
    if( StringGridEntradaProduto->RowCount != 2 ) {
      StringGridEntradaProduto->RowCount --;
    }
    ComboBoxCodigoProduto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnConfirmaProdutoClick( TObject *Sender ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  String Qtd;
  int i;

  try {
    Data = new TDateTime( );
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    try {
    	if( ( Trim( ComboBoxCodigoProduto->Text ).IsEmpty( ) ) || ( Trim( EditQuantidade->Text ).IsEmpty( ) ) ||
          ( Trim( EditEntradaPreco->Text ).Length( ) < 3 ) ) {
        throw Exception( "Você Deve Preencher Todos os Campos!!!" );
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
        if( !StringGridEntradaProduto->Cells[0][1].IsEmpty( ) ) {
        	StringGridEntradaProduto->RowCount++;
        }
        StringGridEntradaProduto->Cells[0][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
 	      StringGridEntradaProduto->Cells[1][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
 	      StringGridEntradaProduto->Cells[2][StringGridEntradaProduto->RowCount - 1] = Trim( EditQuantidade->Text );
   	    DecimalSeparator = ',';
     	  ThousandSeparator = '.';
        StringGridEntradaProduto->Cells[3][StringGridEntradaProduto->RowCount - 1] = FormatFloat( "#,##0.00", StrToFloat( EditEntradaPreco->Text ) );
        StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1] = FormatFloat( "#,##0.00", EditQuantidade->Text.ToDouble( ) * StrToFloat( StringReplace( StringGridEntradaProduto->Cells[3][StringGridEntradaProduto->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
        StringGridEntradaProduto->Cells[5][StringGridEntradaProduto->RowCount - 1] = Data->CurrentDate( ).DateString( );
 	      StringGridEntradaProduto->Cells[6][StringGridEntradaProduto->RowCount - 1] = Query->FieldByName( "Codigo" )->AsString;
        if( EditTotalEntrada->Text.IsEmpty( ) ) {
 	        DecimalSeparator = ',';
   	      ThousandSeparator = '.';
          EditTotalEntrada->Text = StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1];
       	}
        else {
     	    DecimalSeparator = ',';
       	  ThousandSeparator = '.';
         	EditTotalEntrada->Text = FormatFloat( "#,##0.00", ( StringReplace( EditTotalEntrada->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) + StrToFloat( StringReplace( StringGridEntradaProduto->Cells[4][StringGridEntradaProduto->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
        }
				EditQuantidade->Clear( );
  		  EditEntradaPreco->Clear( );
        ComboBoxCodigoProduto->Clear( );
        ComboBoxCodigoProduto->SetFocus( );
	    }
    }
    catch( Exception &e ) {
    	Application->MessageBox( e.Message.c_str( ), "Entrada de Produtos",
     													 MB_OK | MB_ICONERROR );
  	}
  }
  __finally {
  	delete Data;
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnCancelaProdutoClick( TObject *Sender ) {

  int i, j, k;
  bool Ok;

	if( Trim( ComboBoxCodigoProduto->Text ).IsEmpty( ) ) {
  	Application->MessageBox( "Você Deve Digitar o Código do Produto!!!",
    												 "Entrada de Produtos", MB_OK | MB_ICONERROR );
    ComboBoxCodigoProduto->SetFocus( );
  }
  else {
  	for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
    	if( UpperCase( Trim( ComboBoxCodigoProduto->Text ) ) == UpperCase( StringGridEntradaProduto->Cells[6][i] ) ) {
      	Ok = true;
        break;
      }
      else {
      	Ok = false;
      }
    }
    if( !Ok ) {
    	Application->MessageBox( "O Produto Não Existe na Tabela!!!",
    												 "Entrada de Produtos", MB_OK | MB_ICONERROR );
      ComboBoxCodigoProduto->SetFocus( );
    }
    else {
    	if( StringGridEntradaProduto->RowCount == 2 ) {
      	EditTotalEntrada->Clear( );
      }
      else {
      	EditTotalEntrada->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotalEntrada->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) - StrToFloat( StringReplace( StringGridEntradaProduto->Cells[4][i], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
      }
    	for( j = i + 1; j < StringGridEntradaProduto->RowCount; j++ ) {
 				for( k = 0; k <= 6; k++ ) {
          StringGridEntradaProduto->Cells[k][j-1] = StringGridEntradaProduto->Cells[k][j];
        }
      }
      if( StringGridEntradaProduto->RowCount == 2 ) {
        StringGridEntradaProduto->Rows[1]->Clear( );
      }
      else {
        StringGridEntradaProduto->RowCount--;
      }
      ComboBoxCodigoProduto->SetFocus( );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnConfirmaCompraClick( TObject *Sender ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  int Resposta, i;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Data = new TDateTime( );

    try {
      if( ( Trim( ComboBoxCnpj->Text ).IsEmpty( ) ) || ( StringGridEntradaProduto->Cells[0][1].IsEmpty( ) ) ||
          ( Trim( EditNotaFiscal->Text ).IsEmpty( ) ) ) {
        throw Exception( "Faltam Campos A Serem Preenchidos !!!" );
      }
      else {
  	   	Resposta = Application->MessageBox( "Os Produtos Possuem Nota Fiscal ?", "Entrada de Produtos",
	  				       												  MB_YESNOCANCEL | MB_ICONWARNING );

	      if( Resposta == IDYES ) {
          if( !DataModuleQuery->consigo_BD->Connected ) {
            DataModuleQuery->consigo_BD->Open( );
          }
 	    		for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
            Query->SQL->Add( "BEGIN TRANSACTION" );
            Query->SQL->Add( "INSERT INTO Fornecedores_Vendem( Numero_nota, Preco_Custo," );
            Query->SQL->Add( "Quantidade, Data, Codigo, CGC )" );
            DecimalSeparator = '.';
            Query->SQL->Add( "SELECT " + Trim( EditNotaFiscal->Text ) + "," );
            Query->SQL->Add( StringReplace( StringReplace( StringGridEntradaProduto->Cells[3][i], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
            Query->SQL->Add( StringGridEntradaProduto->Cells[2][i] + ",'" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'," );
            Query->SQL->Add( "Produtos.Codigo, Fornecedores.CGC" );
            Query->SQL->Add( "FROM  Fornecedores, Produtos" );
            Query->SQL->Add( "WHERE Produtos.Codigo = '" + StringGridEntradaProduto->Cells[6][i] + "'" );
            Query->SQL->Add( "AND   Fornecedores.CGC = '" + ComboBoxCnpj->Text + "'" );
            Query->SQL->Add( "UPDATE Produtos" );
            Query->SQL->Add( "SET Produtos.Quantidade_ = Produtos.Quantidade_ + " + StringGridEntradaProduto->Cells[2][i] + "," );
            Query->SQL->Add( "    Produtos.Quantidade = Produtos.Quantidade + " + StringGridEntradaProduto->Cells[2][i] + "," );
            Query->SQL->Add( "    Produtos.Custo_Anterior = Produtos.Custo_Atual," );
            Query->SQL->Add( "    Produtos.Custo_Atual = " + StringReplace( StringReplace( StringGridEntradaProduto->Cells[3][i], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) );
            Query->SQL->Add( "FROM Produtos" );
            Query->SQL->Add( "WHERE Produtos.Codigo = '" + StringGridEntradaProduto->Cells[6][i] + "'" );
            Query->SQL->Add( "COMMIT TRANSACTION" );
     	    	Query->ExecSQL( );
            Query->SQL->Clear( );
	       	}

      	  ComboBoxCnpj->Clear( );
        	EditNotaFiscal->Clear( );
	        ComboBoxCodigoProduto->Clear( );
  	      EditQuantidade->Clear( );
    	    EditEntradaPreco->Clear( );
      	  EditTotalEntrada->Clear( );
		      for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
    		  	StringGridEntradaProduto->Rows[i]->Clear( );
					}
        	StringGridEntradaProduto->RowCount = 2;

	        Application->MessageBox( "A Entrada dos Produtos Foi Realizada com Sucesso!", "Entrada de Produtos",
					       									 MB_OK | MB_ICONINFORMATION );
    	  }
  	    else if( Resposta == IDNO ) {
          if( !DataModuleQuery->consigo_BD->Connected ) {
            DataModuleQuery->consigo_BD->Open( );
          }
 	    		for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
            Query->SQL->Add( "BEGIN TRANSACTION" );
            Query->SQL->Add( "INSERT INTO Vendem1( Numero_nota, Preco," );
            Query->SQL->Add( "Quantidade, Data, Codigo, CGC )" );
            Query->SQL->Add( "SELECT " + Trim( EditNotaFiscal->Text ) + "," );
            Query->SQL->Add( StringReplace( StringReplace( StringGridEntradaProduto->Cells[3][i], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
            Query->SQL->Add( StringGridEntradaProduto->Cells[2][i] + ",'" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'," );
            Query->SQL->Add( "Produtos.Codigo, Fornecedores.CGC" );
            Query->SQL->Add( "FROM  Fornecedores, Produtos" );
            Query->SQL->Add( "WHERE Produtos.Codigo = '" + StringGridEntradaProduto->Cells[6][i] + "'" );
            Query->SQL->Add( "AND   Fornecedores.CGC = '" + ComboBoxCnpj->Text + "'" );
            Query->SQL->Add( "UPDATE Produtos" );
            Query->SQL->Add( "SET Produtos.Quantidade = Produtos.Quantidade + " + StringGridEntradaProduto->Cells[2][i] + ",");
            Query->SQL->Add( "    Produtos.Custo_Anterior = Produtos.Custo_Atual," );
            Query->SQL->Add( "    Produtos.Custo_Atual = " + StringReplace( StringReplace( StringGridEntradaProduto->Cells[3][i], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) );
            Query->SQL->Add( "FROM Produtos" );
            Query->SQL->Add( "WHERE Produtos.Codigo = '" + StringGridEntradaProduto->Cells[6][i] + "'" );
            Query->SQL->Add( "COMMIT TRANSACTION" );
     	    	Query->ExecSQL( );
            Query->SQL->Clear( );
	       	}

      	  ComboBoxCnpj->Clear( );
        	EditNotaFiscal->Clear( );
	        ComboBoxCodigoProduto->Clear( );
  	      EditQuantidade->Clear( );
    	    EditEntradaPreco->Clear( );
      	  EditTotalEntrada->Clear( );
		      for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
    		  	StringGridEntradaProduto->Rows[i]->Clear( );
					}
        	StringGridEntradaProduto->RowCount = 2;

	        Application->MessageBox( "A Entrada dos Produtos Foi Realizada com Sucesso!", "Entrada de Produtos",
					       									 MB_OK | MB_ICONINFORMATION );
    	  }
    	  else if( Resposta == IDCANCEL ) {
      		ComboBoxCnpj->SetFocus( );
	      }
      }
    }
    catch( Exception &e ) {
      if( DataModuleQuery->consigo_BD->InTransaction ) {
        	DataModuleQuery->consigo_BD->Rollback( );
	    }
      Application->MessageBox( e.Message.c_str( ), "Entrada de Produtos", MB_OK | MB_ICONERROR );
    }
  }
	__finally {
    delete Query;
    delete Data;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnCancelaCompraClick( TObject *Sender ) {

  TConsigoQuery *Query;
	int Resposta, i;
  TStringList *Itens;
  String *Fornecedor, *NotaFiscal, *Data, *Msg;

  if( ( Trim( EditNotaFiscal->Text ) == "" ) || ( Trim( ComboBoxCnpj->Text ) == "" ) ) {
  	Application->MessageBox( "Você Deve Digitar o CGC e o úmero da Nota Fiscal!", "Entrada de Produtos",
								  		 		   MB_OK | MB_ICONERROR );
  }
  else {
		Resposta = MessageBox( Handle, "Os Produtos possuem NOTAS FISCAIS?", "Entrada de Produtos",
  						  		 		   MB_YESNOCANCEL | MB_ICONWARNING );
	  try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      Fornecedor = new AnsiString( );
      NotaFiscal = new AnsiString( );
      Data = new AnsiString( );
      Msg = new AnsiString( );
  	  Itens = new TStringList( );

      try {
        if( !DataModuleQuery->consigo_BD->Connected ) {
          DataModuleQuery->consigo_BD->Open( );
        }
  			if( Resposta == IDYES ) {
          Query->SQL->Add( "SELECT Produtos.Marca, Produtos.Nome, Fornecedores_Vendem.Quantidade," );
          Query->SQL->Add( "Fornecedores_Vendem.Preco_Custo, Fornecedores_Vendem.Data," );
          Query->SQL->Add( "Fornecedores.Nome AS Fornecedor, Fornecedores_Vendem.Numero_nota," );
          Query->SQL->Add( "Produtos.Codigo" );
          Query->SQL->Add( "FROM Produtos, Fornecedores_Vendem, Fornecedores" );
          Query->SQL->Add( "WHERE Fornecedores_Vendem.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
          Query->SQL->Add( "AND   Fornecedores_Vendem.CGC = '" + ComboBoxCnpj->Text + "'" );
          Query->SQL->Add( "AND   Fornecedores_Vendem.CGC = Fornecedores.CGC" );
          Query->SQL->Add( "AND   Produtos.Codigo = Fornecedores_Vendem.Codigo" );
          Query->SQL->Add( "ORDER BY Fornecedores_Vendem.Data" );
          Query->Open( );
      	  if( Query->IsEmpty( ) ) {
        		throw Exception( "A Nota Fiscal Inexistente!!!\r\rVerifique os Dados Digitados." );
	        }
  	      else {
    	    	Query->First( );
      	    *Fornecedor = Query->FieldByName( "Fornecedor" )->AsString;
        	  *NotaFiscal = Query->FieldByName( "Numero_nota" )->AsString;
          	*Data = Query->FieldByName( "Data" )->AsDateTime.FormatString( "dd/mm/yyyy hh:mm:ss" );
						while( !Query->Eof ) {
              ThousandSeparator = '.';
              DecimalSeparator = ',';
  	          Itens->Append( Query->FieldByName( "Marca" )->AsString + " " + Query->FieldByName( "Nome" )->AsString + " " +
      	                     Query->FieldByName( "Quantidade" )->AsString + " x " + Query->FieldByName( "Preco_Custo" )->AsString +
                             " = " + FormatFloat( "#,##0.00", Query->FieldByName( "Quantidade" )->AsFloat * Query->FieldByName( "Preco_Custo" )->AsFloat ) );
          		Query->Next( );
	          }
  	        Query->Close( );

      	    *Msg = "Tem Certeza que Deseja Cancelar a Compra:\r\rFornecedor: " + *Fornecedor +
        	  			 "\rNota Fiscal nº: " + *NotaFiscal + "  Data: " + *Data + "\r\r" + Itens->Text;
          	if( Application->MessageBox( Msg->c_str( ), "Entrada de Produtos", MB_YESNO | MB_ICONWARNING ) == IDYES ) {
              Query->SQL->Clear( );
              Query->SQL->Add( "BEGIN TRANSACTION" );
              Query->SQL->Add( "UPDATE Produtos" );
              Query->SQL->Add( "SET Produtos.Quantidade = Produtos.Quantidade - Fornecedores_Vendem.Quantidade," );
              Query->SQL->Add( "    Produtos.Quantidade_ = Produtos.Quantidade_ - Fornecedores_Vendem.Quantidade" );
              Query->SQL->Add( " FROM Produtos, Fornecedores_Vendem" );
              Query->SQL->Add( " WHERE Produtos.Codigo = Fornecedores_Vendem.Codigo" );
              Query->SQL->Add( " AND    Fornecedores_Vendem.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
              Query->SQL->Add( " AND    Fornecedores_Vendem.CGC = '" + ComboBoxCnpj->Text + "'" );
              Query->SQL->Add( "DELETE FROM Fornecedores_Vendem" );
              Query->SQL->Add( " WHERE  Fornecedores_Vendem.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
              Query->SQL->Add( " AND    Fornecedores_Vendem.CGC = '" + ComboBoxCnpj->Text + "'" );
              Query->SQL->Add( "COMMIT TRANSACTION" );
              Query->ExecSQL( );
          	}
  		      for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
      		  	StringGridEntradaProduto->Rows[i]->Clear( );
		  			}
          	StringGridEntradaProduto->RowCount = 2;
          }
	      }
  			if( Resposta == IDNO ) {
          Query->SQL->Add( "SELECT Produtos.Marca, Produtos.Nome, Vendem1.Quantidade," );
          Query->SQL->Add( "Vendem1.Preco, Vendem1.Data," );
          Query->SQL->Add( "Fornecedores.Nome AS Fornecedor, Vendem1.Numero_nota," );
          Query->SQL->Add( "Produtos.Codigo" );
          Query->SQL->Add( "FROM Produtos, Vendem1, Fornecedores" );
          Query->SQL->Add( "WHERE Vendem1.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
          Query->SQL->Add( "AND   Vendem1.CGC = '" + ComboBoxCnpj->Text + "'" );
          Query->SQL->Add( "AND   Vendem1.CGC = Fornecedores.CGC" );
          Query->SQL->Add( "AND   Produtos.Codigo = Vendem1.Codigo" );
          Query->SQL->Add( "ORDER BY Vendem1.Data" );
          Query->Open( );
      	  if( Query->IsEmpty( ) ) {
        		throw Exception( "A Nota Fiscal Inexistente!!!\r\rVerifique os Dados Digitados." );
	        }
  	      else {
    	    	Query->First( );
      	    *Fornecedor = Query->FieldByName( "Fornecedor" )->AsString;
        	  *NotaFiscal = Query->FieldByName( "Numero_nota" )->AsString;
          	*Data = Query->FieldByName( "Data" )->AsDateTime.FormatString( "dd/mm/yyyy hh:mm:ss" );
						while( !Query->Eof ) {
              ThousandSeparator = '.';
              DecimalSeparator = ',';
  	          Itens->Append( Query->FieldByName( "Marca" )->AsString + " " + Query->FieldByName( "Nome" )->AsString + " " +
      	                     Query->FieldByName( "Quantidade" )->AsString + " x " + Query->FieldByName( "Preco" )->AsString +
                             " = " + FormatFloat( "#,##0.00", Query->FieldByName( "Quantidade" )->AsFloat * Query->FieldByName( "Preco" )->AsFloat ) );
          		Query->Next( );
	          }
  	        Query->Close( );

      	    *Msg = "Tem Certeza que Deseja Cancelar a Compra:\r\rFornecedor: " + *Fornecedor +
        	  			 "\rNota Fiscal nº: " + *NotaFiscal + "  Data: " + *Data + "\r\r" + Itens->Text;
          	if( Application->MessageBox( Msg->c_str( ), "Entrada de Produtos", MB_YESNO | MB_ICONWARNING ) == IDYES ) {
              Query->SQL->Clear( );
              Query->SQL->Add( "BEGIN TRANSACTION" );
              Query->SQL->Add( "UPDATE Produtos" );
              Query->SQL->Add( "SET Produtos.Quantidade = Produtos.Quantidade - Vendem1.Quantidade" );
              Query->SQL->Add( " FROM Produtos, Vendem1" );
              Query->SQL->Add( " WHERE Produtos.Codigo = Vendem1.Codigo" );
              Query->SQL->Add( " AND    Vendem1.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
              Query->SQL->Add( " AND    Vendem1.CGC = '" + ComboBoxCnpj->Text + "'" );
              Query->SQL->Add( "DELETE FROM Vendem1" );
              Query->SQL->Add( " WHERE  Vendem1.Numero_nota = " + Trim( EditNotaFiscal->Text ) );
              Query->SQL->Add( " AND    Vendem1.CGC = '" + ComboBoxCnpj->Text + "'" );
              Query->SQL->Add( "COMMIT TRANSACTION" );
              Query->ExecSQL( );
          	}
  		      for( i = 1; i < StringGridEntradaProduto->RowCount; i++ ) {
      		  	StringGridEntradaProduto->Rows[i]->Clear( );
		  			}
          	StringGridEntradaProduto->RowCount = 2;
          }
	      }
			  ComboBoxCnpj->Clear( );
  			EditNotaFiscal->Clear( );
	  		ComboBoxCodigoProduto->Clear( );
		  	EditQuantidade->Clear( );
			  EditEntradaPreco->Clear( );
        ComboBoxCnpj->SetFocus( );
      }
      catch( Exception &e ) {
      	if( DataModuleQuery->consigo_BD->InTransaction ) {
       		DataModuleQuery->consigo_BD->Rollback( );
        }
 	  		Application->MessageBox( e.Message.c_str( ), "Entrada de Produtos", MB_OK | MB_ICONERROR );
      }
  	}
	  __finally {
      Query->Close( );
      delete Query;
  		delete Itens;
      delete Fornecedor;
      delete NotaFiscal;
      delete Data;
      delete Msg;
  	}
  }
}
//---------------------------------------------------------------------------

