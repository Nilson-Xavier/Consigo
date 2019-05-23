//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Dmod1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemEmFaltaClick( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetEmFalta;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditEmFaltaQuantidadeKeyPress( TObject *Sender,
  char &Key ) {

	if( Key == 13 ) {
		if( ( Trim( EditEmFaltaQuantidade->Text ).IsEmpty( ) ) ||
        ( Trim( EditMarca->Text ).Length( ) < 3 ) ) {
    	Application->MessageBox( "É Necessário Digitar a Quantidade e a Marca para a Consulta!!!",
                               "Produtos em Falta", MB_OK | MB_ICONERROR );
    }
    else {
      this->ConsultarProdutoEmFalta( &(EditEmFaltaQuantidade->Text), &(EditMarca->Text) );
    }
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ) {
    if( this->EditEmFaltaQuantidade->Text.Length( ) >= 4 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditMarcaKeyPress( TObject *Sender, char &Key ) {

	int i;

	if( Key == 13 ) {
		if( ( Trim( EditEmFaltaQuantidade->Text ).IsEmpty( ) ) ||
        ( Trim( EditMarca->Text ).Length( ) < 3 ) ) {
    	Application->MessageBox( "É Necessário Digitar a Quantidade e a Marca para a Consulta!!!",
                               "Produtos em Falta",
                               MB_OK | MB_ICONERROR );
    }
    else {
      this->ConsultarProdutoEmFalta( &(EditEmFaltaQuantidade->Text), &(EditMarca->Text) );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ConsultarProdutoEmFalta( String* Quantidade, String* Marca ) {

  TConsigoQuery *Query;
	int i;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    try {

		  for( i = 1; i < StringGridProduto->RowCount; i++ ) {
   			StringGridProduto->Rows[i]->Clear( );
  		}
      StringGridProduto->RowCount = 2;
      Query->SQL->Add( "SELECT *" );
      Query->SQL->Add( "FROM Produtos" );
      Query->SQL->Add( "WHERE Produtos.Quantidade <= " + *Quantidade );
      Query->SQL->Add( "AND   Produtos.Marca LIKE '" + *Marca + "%'" );
      Query->SQL->Add( "ORDER BY Produtos.Marca, Produtos.Quantidade," );
      Query->SQL->Add( "  Produtos.Nome ASC" );
      Query->Prepare( );
      Query->Open( );
  		if( Query->IsEmpty( ) ) {
       	throw Exception( "Não Há Produtos com a Quantidade Menor que a Digitada!!!" );
      }
      else {
        Query->First( );
        while( !Query->Eof ) {
          if( !StringGridProduto->Cells[0][1].IsEmpty( ) ) {
            StringGridProduto->RowCount ++;
          }
          StringGridProduto->Cells[0][StringGridProduto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          StringGridProduto->Cells[1][StringGridProduto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          StringGridProduto->Cells[2][StringGridProduto->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
          StringGridProduto->Cells[3][StringGridProduto->RowCount - 1] = Query->FieldByName( "Quantidade_" )->AsString;
          Query->Next( );
        }
      }
    }
    catch( Exception &e ) {
    	Application->MessageBox( e.Message.c_str( ), "Produtos em Falta", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
