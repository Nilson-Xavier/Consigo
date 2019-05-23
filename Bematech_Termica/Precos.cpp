//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Dmod1.h"
#include "Dmod2.h"
#include "ImpressaoListaPreco.h"
#include "Precos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemPrecosClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetPrecos;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::TabSheetPrecosEnter( TObject *Sender ) {

}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::TabSheetPrecosExit( TObject *Sender ) {

	DataModuleQuery->Query15->Close( );
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditPrecoMarcaKeyPress( TObject *Sender, char &Key ) {

	if( Key == 13 ) {
    this->ConsultarProduto( &(EditPrecoMarca->Text), NULL );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditPrecoNomeKeyPress( TObject *Sender, char &Key ) {

	if( Key == 13 ) {
    this->ConsultarProduto( &(EditPrecoMarca->Text), &(EditPrecoNome->Text) );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnImprimirListaPrecoClick( TObject *Sender ) {

  TCursor SaveCursor;

  try {
    FormImpressaoListaPreco = new TFormImpressaoListaPreco( FormGerencia );
    SaveCursor = Screen->Cursor;
	  Screen->Cursor = crHourGlass;
    this->Enabled = false;
    try {
      DataModuleQuery->Produtos->Close( );
      DataModuleQuery->Produtos->ParamByName( "Codigo" )->AsString = "%";
      DataModuleQuery->Produtos->ParamByName( "Marca" )->AsString = "%";
      DataModuleQuery->Produtos->ParamByName( "Nome" )->AsString = "%";
      DataModuleQuery->Produtos->Open( );

      FormImpressaoListaPreco->QuickRepListaPreco->Preview( );

      DataModuleQuery->Produtos->Close( );
    }
    catch( Exception &e ) {
      DataModuleQuery->Produtos->Close( );
      Application->MessageBox( e.Message.c_str( ), "Preços", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete FormImpressaoListaPreco;
   	Screen->Cursor = SaveCursor;
    this->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ConsultarProduto( String* Marca, String* Nome ) {

  TConsigoQuery *Query;
  int i;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

  	try {
      for( i = 1; i < StringGridAlteracaoProduto->RowCount; i++ ) {
   	    StringGridAlteracaoProduto->Rows[i]->Clear( );
    	}
      StringGridAlteracaoProduto->RowCount = 2;

      Query->SQL->Add( "SELECT *" );
      Query->SQL->Add( "  FROM Produtos" );
      if( Marca == NULL ) {
        Query->SQL->Add( "  WHERE Marca LIKE '%'" );
      }
      else {
        Query->SQL->Add( "  WHERE Marca LIKE '" + *Marca + "%'" );
      }
      if( Nome == NULL ) {
        Query->SQL->Add( "  AND Nome LIKE '%'" );
      }
      else {
        Query->SQL->Add( "  AND Nome LIKE '%" + StringReplace( *Nome, " ", "%", TReplaceFlags( ) << rfReplaceAll ) + "%'" );
      }
      Query->SQL->Add( "ORDER BY Marca, Nome" );
			Query->Open( );
      if( Query->IsEmpty( ) ) {
        throw Exception( "Não Há Produtos Com Esta Marca ou Nome !" );
      }
      else {
        Query->First( );
        while( !Query->Eof ) {
          if( !StringGridAlteracaoProduto->Cells[0][1].IsEmpty( ) ) {
            StringGridAlteracaoProduto->RowCount++;
          }
          StringGridAlteracaoProduto->Cells[0][StringGridAlteracaoProduto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          StringGridAlteracaoProduto->Cells[1][StringGridAlteracaoProduto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          StringGridAlteracaoProduto->Cells[2][StringGridAlteracaoProduto->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
          StringGridAlteracaoProduto->Cells[3][StringGridAlteracaoProduto->RowCount - 1] = Query->FieldByName( "Quantidade_" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          StringGridAlteracaoProduto->Cells[4][StringGridAlteracaoProduto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Custo_Anterior" )->AsFloat );
          StringGridAlteracaoProduto->Cells[5][StringGridAlteracaoProduto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Custo_Atual" )->AsFloat );
          StringGridAlteracaoProduto->Cells[6][StringGridAlteracaoProduto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          StringGridAlteracaoProduto->Cells[7][StringGridAlteracaoProduto->RowCount - 1] = Query->FieldByName( "Garantia" )->AsString;
          StringGridAlteracaoProduto->Cells[8][StringGridAlteracaoProduto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Dolar" )->AsFloat );
          StringGridAlteracaoProduto->Cells[9][StringGridAlteracaoProduto->RowCount - 1] = Query->FieldByName( "Codigo" )->AsString;
          Query->Next( );
        }
        StringGridAlteracaoProduto->SetFocus( );
      }
    }
    catch( Exception &e ) {
  	  Application->MessageBox( e.Message.c_str( ), "Preços", MB_OK | MB_ICONERROR );
    }
  } __finally {
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridAlteracaoProdutoSelectCell( TObject *Sender,
  int ACol, int ARow, bool &CanSelect ) {

  if( ACol != 9 ) {
    this->StringGridAlteracaoProduto->Options << goEditing;
  }
  else {
    this->StringGridAlteracaoProduto->Options >> goEditing;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridAlteracaoProdutoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;

  if( ( ( Key == VK_DOWN ) || ( Key == VK_UP ) || ( Key == VK_RETURN ) ) &&
      ( StringGridAlteracaoProduto->EditorMode ) ) {

    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

      try {
        Query->SQL->Add( "UPDATE Produtos" );
        Query->SQL->Add( "  SET Marca = '" + StringGridAlteracaoProduto->Cells[0][StringGridAlteracaoProduto->Row] + "'," );
        Query->SQL->Add( "      Nome = '" + StringGridAlteracaoProduto->Cells[1][StringGridAlteracaoProduto->Row] + "'," );
        Query->SQL->Add( "      Quantidade = " + StringGridAlteracaoProduto->Cells[2][StringGridAlteracaoProduto->Row] + "," );
        Query->SQL->Add( "      Quantidade_ = " + StringGridAlteracaoProduto->Cells[3][StringGridAlteracaoProduto->Row] + "," );
        Query->SQL->Add( "      Custo_Anterior = " + StringReplace( StringReplace( StringGridAlteracaoProduto->Cells[4][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
        Query->SQL->Add( "      Custo_Atual = " + StringReplace( StringReplace( StringGridAlteracaoProduto->Cells[5][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
        Query->SQL->Add( "      Preco = " + StringReplace( StringReplace( StringGridAlteracaoProduto->Cells[6][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
        Query->SQL->Add( "      Garantia = '" + StringGridAlteracaoProduto->Cells[7][StringGridAlteracaoProduto->Row] + "'," );
        Query->SQL->Add( "      Dolar = " + StringReplace( StringReplace( StringGridAlteracaoProduto->Cells[8][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) );
        Query->SQL->Add( "  WHERE Codigo = '" + StringGridAlteracaoProduto->Cells[9][StringGridAlteracaoProduto->Row] + "'" );
        Query->Prepare( );
        Query->ExecSQL( );

        ThousandSeparator = '.';
        DecimalSeparator = ',';
        StringGridAlteracaoProduto->Cells[4][StringGridAlteracaoProduto->Row] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( StringGridAlteracaoProduto->Cells[4][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
        StringGridAlteracaoProduto->Cells[5][StringGridAlteracaoProduto->Row] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( StringGridAlteracaoProduto->Cells[5][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
        StringGridAlteracaoProduto->Cells[6][StringGridAlteracaoProduto->Row] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( StringGridAlteracaoProduto->Cells[6][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
        StringGridAlteracaoProduto->Cells[8][StringGridAlteracaoProduto->Row] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( StringGridAlteracaoProduto->Cells[8][StringGridAlteracaoProduto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
        StringGridAlteracaoProduto->EditorMode = false;
      }
      catch( Exception &e ) {
        StringGridAlteracaoProduto->Cells[0][StringGridAlteracaoProduto->Row] = GridUndoValues[0];
        StringGridAlteracaoProduto->Cells[1][StringGridAlteracaoProduto->Row] = GridUndoValues[1];
        StringGridAlteracaoProduto->Cells[2][StringGridAlteracaoProduto->Row] = GridUndoValues[2];
        StringGridAlteracaoProduto->Cells[3][StringGridAlteracaoProduto->Row] = GridUndoValues[3];
        StringGridAlteracaoProduto->Cells[4][StringGridAlteracaoProduto->Row] = GridUndoValues[4];
        StringGridAlteracaoProduto->Cells[5][StringGridAlteracaoProduto->Row] = GridUndoValues[5];
        StringGridAlteracaoProduto->Cells[6][StringGridAlteracaoProduto->Row] = GridUndoValues[6];
        StringGridAlteracaoProduto->Cells[7][StringGridAlteracaoProduto->Row] = GridUndoValues[7];
        StringGridAlteracaoProduto->Cells[8][StringGridAlteracaoProduto->Row] = GridUndoValues[8];
        Application->MessageBox( e.Message.c_str( ), "Preços", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridAlteracaoProdutoKeyPress( TObject *Sender,
  char &Key ) {

  if( ( StringGridAlteracaoProduto->Col == 2 ) || ( StringGridAlteracaoProduto->Col == 3 ) ) {
    if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ) {
      if( ( StringGridAlteracaoProduto->Cells[StringGridAlteracaoProduto->Col][StringGridAlteracaoProduto->Row].Length( ) == 0 ) &&
          ( AnsiCompareStr( Key, "0" ) == 0 ) ) {
        Key = NULL;
      }
      if( StringGridAlteracaoProduto->Cells[StringGridAlteracaoProduto->Col][StringGridAlteracaoProduto->Row].Length( ) >= 4 ) {
        Key = NULL;
      }
    }
    else if( Key != '\b' ) {
      Key = NULL;
    }
  }
  if( ( StringGridAlteracaoProduto->Col == 4 ) || ( StringGridAlteracaoProduto->Col == 5 ) ||
      ( StringGridAlteracaoProduto->Col == 6 ) || ( StringGridAlteracaoProduto->Col == 8 ) ) {
    if( !( ( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ||
             ( Key == ',' ) || ( Key == '\b' ) ) &&
           ( StringGridAlteracaoProduto->Cells[StringGridAlteracaoProduto->Col][StringGridAlteracaoProduto->Row].Length( ) <= 7 ) ) ) {
      Key = NULL;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridAlteracaoProdutoGetEditText( TObject *Sender,
  int ACol, int ARow, AnsiString &Value ) {

  GridUndoValues[0] = StringGridAlteracaoProduto->Cells[0][StringGridAlteracaoProduto->Row];
  GridUndoValues[1] = StringGridAlteracaoProduto->Cells[1][StringGridAlteracaoProduto->Row];
  GridUndoValues[2] = StringGridAlteracaoProduto->Cells[2][StringGridAlteracaoProduto->Row];
  GridUndoValues[3] = StringGridAlteracaoProduto->Cells[3][StringGridAlteracaoProduto->Row];
  GridUndoValues[4] = StringGridAlteracaoProduto->Cells[4][StringGridAlteracaoProduto->Row];
  GridUndoValues[5] = StringGridAlteracaoProduto->Cells[5][StringGridAlteracaoProduto->Row];
  GridUndoValues[6] = StringGridAlteracaoProduto->Cells[6][StringGridAlteracaoProduto->Row];
  GridUndoValues[7] = StringGridAlteracaoProduto->Cells[7][StringGridAlteracaoProduto->Row];
  GridUndoValues[8] = StringGridAlteracaoProduto->Cells[8][StringGridAlteracaoProduto->Row];
}
//---------------------------------------------------------------------------

