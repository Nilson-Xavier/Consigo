//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Dmod1.h"
#include "ImpressaoFechamentoVendedor.h"
#include "ImpressaoFechamentoVendedor2.h"
#include "ImpressaoEntradaProduto.h"
#include "ImpressaoEntradaProduto2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemFechamentoClick( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetFechamento;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditFechamentoDataInicialKeyPress( TObject *Sender,
  char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditFechamentoDataInicial->Text.Length( ) <= 7 ) ) {
    if( this->EditFechamentoDataInicial->Text.Length( ) >= 2 ) {
      this->EditFechamentoDataInicial->Text = this->EditFechamentoDataInicial->Text.Delete( this->EditFechamentoDataInicial->Text.Pos( "/" ), 1 );
      this->EditFechamentoDataInicial->Text = this->EditFechamentoDataInicial->Text.Insert( "/", 3 );
      this->EditFechamentoDataInicial->SelStart = this->EditFechamentoDataInicial->Text.Length( );
      if( this->EditFechamentoDataInicial->Text.Length( ) >= 5 ) {
        this->EditFechamentoDataInicial->Text = this->EditFechamentoDataInicial->Text.Delete( 6, 1 );
        this->EditFechamentoDataInicial->Text = this->EditFechamentoDataInicial->Text.Insert( "/", 6 );
        this->EditFechamentoDataInicial->SelStart = this->EditFechamentoDataInicial->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( this->EditFechamentoDataInicial->Text.Length( ) == 7 ) {
    this->EditFechamentoDataFinal->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditFechamentoDataFinalKeyPress( TObject *Sender,
  char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditFechamentoDataFinal->Text.Length( ) <= 7 ) ) {
    if( this->EditFechamentoDataFinal->Text.Length( ) >= 2 ) {
      this->EditFechamentoDataFinal->Text = this->EditFechamentoDataFinal->Text.Delete( this->EditFechamentoDataFinal->Text.Pos( "/" ), 1 );
      this->EditFechamentoDataFinal->Text = this->EditFechamentoDataFinal->Text.Insert( "/", 3 );
      this->EditFechamentoDataFinal->SelStart = this->EditFechamentoDataFinal->Text.Length( );
      if( this->EditFechamentoDataFinal->Text.Length( ) >= 5 ) {
        this->EditFechamentoDataFinal->Text = this->EditFechamentoDataFinal->Text.Delete( 6, 1 );
        this->EditFechamentoDataFinal->Text = this->EditFechamentoDataFinal->Text.Insert( "/", 6 );
        this->EditFechamentoDataFinal->SelStart = this->EditFechamentoDataFinal->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    if( StrToDate( EditFechamentoDataInicial->Text ) > StrToDate( EditFechamentoDataFinal->Text ) ) {
      Application->MessageBox( "A Data Inicial Não Pode Ser Maior que a Data Final !", "Fechamento de Vendas", MB_OK | MB_ICONERROR );
    }
    else if( ( EditFechamentoDataInicial->Text.Length( ) < 8 ) ||
             ( EditFechamentoDataFinal->Text.Length( ) < 8 ) ) {
      Application->MessageBox( "É Necassário a Data Completa para o Fechamento !", "Fechamento de Vendas", MB_OK | MB_ICONERROR );
    }
    else {
      this->ListarFechamento( &(EditFechamentoDataInicial->Text), &(EditFechamentoDataFinal->Text) );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ListarFechamento( String* DataInicial, String* DataFinal ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  bool *Vazio1, *Vazio2;
  int i;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Data = new TDateTime( );
    Vazio1 = new bool( false );
    Vazio2 = new bool( false );

    try {
      for( i = 1; i < StringGridFechamento->RowCount; i++ ) {
	      StringGridFechamento->Rows[i]->Clear( );
      }
      StringGridFechamento->RowCount = 2;
      EditFechamentoTotalOk->Clear( );
      EditFechamentoTotal->Clear( );
      EditFechamentoTotalGeral->Clear( );

      Query->SQL->Add( "SELECT Vendem.Data, Produtos.Marca, Produtos.Nome," );
      Query->SQL->Add( "Vendem.Quantidade, Vendem.Preco, Vendem.Tipo," );
      Query->SQL->Add( "Vendedores.Nome AS Vendedor, Vendem.Numero_nota," );
      Query->SQL->Add( "Vendem.Talao, Vendem.Entrada, Vendem.Parcelas," );
      Query->SQL->Add( "Vendem.Numero_Serie, Clientes.Nome AS Cliente" );
      Query->SQL->Add( "  FROM Produtos, Vendedores, Vendem, Clientes" );
      *Data = *DataInicial + " 7:00:00";
      Query->SQL->Add( "  WHERE Vendem.Data >= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      *Data = *DataFinal + " 21:00:00";
      Query->SQL->Add( "  AND   Vendem.Data <= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      Query->SQL->Add( "  AND   Vendem.Codigo = Produtos.Codigo" );
      Query->SQL->Add( "  AND   Vendem.RG_Vendedor = Vendedores.RG" );
      Query->SQL->Add( "  AND   Vendem.EERG_Vendedor = Vendedores.EERG" );
      Query->SQL->Add( "  AND   Vendem.RG_Cliente = Clientes.RG" );
      Query->SQL->Add( "  AND   Vendem.EERG_Cliente = Clientes.EERG" );
      Query->SQL->Add( "ORDER BY Vendedores.Nome, Vendem.Numero_nota ASC" );
      Query->Open( );
      if( Query->IsEmpty( ) ) {
          *Vazio1 = true;
      }
      else {
        Query->First( );
        while( !Query->Eof ) {
          if( !StringGridFechamento->Cells[0][1].IsEmpty( ) ) {
            StringGridFechamento->RowCount ++;
          }
          StringGridFechamento->Cells[0][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Data" )->AsString;
          StringGridFechamento->Cells[1][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          StringGridFechamento->Cells[2][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          StringGridFechamento->Cells[3][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          StringGridFechamento->Cells[4][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", ( Query->FieldByName( "Preco" )->AsFloat / Query->FieldByName( "Quantidade" )->AsInteger ) );
          StringGridFechamento->Cells[5][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          StringGridFechamento->Cells[6][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Tipo" )->AsString;
          if( !Query->FieldByName( "Entrada" )->IsNull ) {
            StringGridFechamento->Cells[7][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Entrada" )->AsFloat );
          }
          if( !Query->FieldByName( "Parcelas" )->IsNull ) {
            StringGridFechamento->Cells[8][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Parcelas" )->AsFloat );
          }
          StringGridFechamento->Cells[9][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Numero_Serie" )->AsString;
          StringGridFechamento->Cells[10][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Numero_nota" )->AsString;
          StringGridFechamento->Cells[11][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Talao" )->AsString;
          StringGridFechamento->Cells[12][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Cliente" )->AsString;
          StringGridFechamento->Cells[13][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Vendedor" )->AsString;
          if( EditFechamentoTotalOk->Text.IsEmpty( ) ) {
          	EditFechamentoTotalOk->Text = StringGridFechamento->Cells[5][StringGridFechamento->RowCount - 1];
          }
          else {
            EditFechamentoTotalOk->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditFechamentoTotalOk->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + StrToFloat( StringReplace( StringGridFechamento->Cells[5][StringGridFechamento->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
          }
          Query->Next( );
        }
      }
      Query->Close( );
      Query->SQL->Clear( );
      if( !*this->SecurityFlag ) {
        if( !*Vazio1 ) {
          StringGridFechamento->RowCount ++;
        }

      Query->SQL->Add( "SELECT Vendem2.Data, Produtos.Marca, Produtos.Nome," );
      Query->SQL->Add( "       Vendem2.Quantidade, Vendem2.Preco, Vendem2.Tipo," );
      Query->SQL->Add( "       Vendedores.Nome AS Vendedor, Vendem2.Numero_nota," );
      Query->SQL->Add( "       Vendem2.Talao, Vendem2.Entrada, Vendem2.Parcelas," );
      Query->SQL->Add( "       Vendem2.Numero_Serie, Clientes.Nome AS Cliente" );
      Query->SQL->Add( "  FROM Produtos, Vendedores, Vendem2, Clientes" );
      *Data = *DataInicial + " 7:00:00";
      Query->SQL->Add( "  WHERE Vendem2.Data >= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      *Data = *DataFinal + " 21:00:00";
      Query->SQL->Add( "  AND   Vendem2.Data <= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      Query->SQL->Add( "  AND   Vendem2.Codigo = Produtos.Codigo" );
      Query->SQL->Add( "  AND   Vendem2.RG_Vendedor = Vendedores.RG" );
      Query->SQL->Add( "  AND   Vendem2.EERG_Vendedor = Vendedores.EERG" );
      Query->SQL->Add( "  AND   Vendem2.RG_Cliente = Clientes.RG" );
      Query->SQL->Add( "  AND   Vendem2.EERG_Cliente = Clientes.EERG" );
      Query->SQL->Add( "ORDER BY Vendedores.Nome, Vendem2.Numero_nota ASC" );
    	Query->Open( );
      if( Query->IsEmpty( ) ) {
        *Vazio2 = true;
      }
      else {
      	Query->First( );
        while( !Query->Eof ) {
          if( !StringGridFechamento->Cells[0][1].IsEmpty( ) ) {
          	StringGridFechamento->RowCount ++;
          }
          StringGridFechamento->Cells[0][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Data" )->AsString;
          StringGridFechamento->Cells[1][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          StringGridFechamento->Cells[2][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          StringGridFechamento->Cells[3][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          StringGridFechamento->Cells[4][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", ( Query->FieldByName( "Preco" )->AsFloat / Query->FieldByName( "Quantidade" )->AsInteger ) );
          StringGridFechamento->Cells[5][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          StringGridFechamento->Cells[6][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Tipo" )->AsString;
          if( !Query->FieldByName( "Entrada" )->IsNull ) {
            StringGridFechamento->Cells[7][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Entrada" )->AsFloat );
          }
          if( !Query->FieldByName( "Parcelas" )->IsNull ) {
            StringGridFechamento->Cells[8][StringGridFechamento->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Parcelas" )->AsFloat );
          }
          StringGridFechamento->Cells[9][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Numero_Serie" )->AsString;
          StringGridFechamento->Cells[10][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Numero_nota" )->AsString;
          StringGridFechamento->Cells[11][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Talao" )->AsString;
          StringGridFechamento->Cells[12][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Cliente" )->AsString;
          StringGridFechamento->Cells[13][StringGridFechamento->RowCount - 1] = Query->FieldByName( "Vendedor" )->AsString;
          if( EditFechamentoTotal->Text.IsEmpty( ) ) {
          	EditFechamentoTotal->Text = StringGridFechamento->Cells[5][StringGridFechamento->RowCount - 1];
          }
          else {
            EditFechamentoTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditFechamentoTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + StrToFloat( StringReplace( StringGridFechamento->Cells[5][StringGridFechamento->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
          }
         	Query->Next( );
        }
      }
      Query->Close( );
      }
      if( ( *Vazio1 ) && ( *Vazio2 ) ) {
        	throw Exception( "Não Há Nenhuma Venda Realizada Neste Intervalo de Data!" );
      }

      if( EditFechamentoTotalOk->Text.IsEmpty( ) ) {
      	EditFechamentoTotalGeral->Text = EditFechamentoTotal->Text;
      }
      else if( EditFechamentoTotal->Text.IsEmpty( ) ) {
        EditFechamentoTotalGeral->Text = EditFechamentoTotalOk->Text;
      }
      else {
	      EditFechamentoTotalGeral->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditFechamentoTotalOk->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + StrToFloat( StringReplace( EditFechamentoTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
      }
    }
    catch( Exception &e ) {
      for( i = 1; i < StringGridFechamento->RowCount; i++ ) {
				StringGridFechamento->Rows[i]->Clear( );
  	  }
      StringGridFechamento->RowCount = 2;
      EditFechamentoTotalOk->Clear( );
      EditFechamentoTotal->Clear( );
      EditFechamentoTotalGeral->Clear( );
      Application->MessageBox( e.Message.c_str( ), "Fechamento de Vendas", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete Data;
    delete Vazio1;
    delete Vazio2;
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnFechamentoVendedorClick( TObject *Sender ) {

  String Kind;

  if( StrToDateTime( EditFechamentoDataInicial->Text ) > StrToDateTime( EditFechamentoDataFinal->Text ) ) {
  	Application->MessageBox( "A Data Inicial NÃO Pode Ser Maior que a Data Final!",
    												 "Fechamento", MB_OK | MB_ICONERROR );
    EditFechamentoDataInicial->SetFocus( );
  }
  else {
    try {
      FormImpressaoFechamentoVendedor = new TFormImpressaoFechamentoVendedor( FormGerencia );
      FormImpressaoFechamentoVendedor2 = new TFormImpressaoFechamentoVendedor2( FormGerencia );

      try {
        FormImpressaoFechamentoVendedor->QRLabelDataInicial->Caption = FormatDateTime( "dd/mm/yyyy", StrToDate( EditFechamentoDataInicial->Text ) );
        FormImpressaoFechamentoVendedor->QRLabelDataFinal->Caption = FormatDateTime( "dd/mm/yyyy", StrToDate( EditFechamentoDataFinal->Text ) );
        FormImpressaoFechamentoVendedor2->QRLabelDataInicial->Caption = FormatDateTime( "dd/mm/yyyy", StrToDate( EditFechamentoDataInicial->Text ) );
        FormImpressaoFechamentoVendedor2->QRLabelDataFinal->Caption = FormatDateTime( "dd/mm/yyyy", StrToDate( EditFechamentoDataFinal->Text ) );

        FormImpressaoFechamentoVendedor->QueryFechamentoVendedor->Prepare( );
        FormImpressaoFechamentoVendedor->QueryFechamentoVendedor->ParamByName( "DataInicial" )->AsDateTime = StrToDateTime( EditFechamentoDataInicial->Text + " 7:00:00 AM" );
        FormImpressaoFechamentoVendedor->QueryFechamentoVendedor->ParamByName( "DataFinal" )->AsDateTime = StrToDateTime( EditFechamentoDataFinal->Text + " 9:00:00 PM" );
        FormImpressaoFechamentoVendedor->QueryFechamentoVendedor->Open( );
        if( !FormImpressaoFechamentoVendedor->QueryFechamentoVendedor->IsEmpty( ) ) {
          FormImpressaoFechamentoVendedor2->QRBand1->Enabled = false;
        }

        FormImpressaoFechamentoVendedor2->QueryFechamentoVendedor2->Prepare( );
        FormImpressaoFechamentoVendedor2->QueryFechamentoVendedor2->ParamByName( "DataInicial" )->AsDateTime = StrToDateTime( EditFechamentoDataInicial->Text + " 7:00:00 AM" );
        FormImpressaoFechamentoVendedor2->QueryFechamentoVendedor2->ParamByName( "DataFinal" )->AsDateTime = StrToDateTime( EditFechamentoDataFinal->Text + " 9:00:00 PM" );
        FormImpressaoFechamentoVendedor2->QueryFechamentoVendedor2->Open( );

        FormImpressaoFechamentoVendedor->QRCompositeReportFechamentoVendedor->Preview( );

        FormImpressaoFechamentoVendedor->QueryFechamentoVendedor->Close( );
        FormImpressaoFechamentoVendedor2->QueryFechamentoVendedor2->Close( );
      }
      catch( Exception &e ) {
        FormImpressaoFechamentoVendedor->QueryFechamentoVendedor->Close( );
        FormImpressaoFechamentoVendedor2->QueryFechamentoVendedor2->Close( );
        Application->MessageBox( e.Message.c_str( ), "Impressão do Fechamento dos Vendedores",
                                 MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete FormImpressaoFechamentoVendedor;
      delete FormImpressaoFechamentoVendedor2;
      EditFechamentoDataInicial->SetFocus( );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnEntradaProdutoClick( TObject *Sender ) {

  TCursor SaveCursor;

  if( StrToDateTime( EditFechamentoDataInicial->Text ) > StrToDateTime( EditFechamentoDataFinal->Text ) ) {
  	Application->MessageBox( "A Data Inicial NÃO Pode Ser Maior que a Data Final!",
    												 "Fechamento", MB_OK | MB_ICONERROR );
    EditFechamentoDataInicial->SetFocus( );
  }
  else {
    try {
      SaveCursor = Screen->Cursor;
      Screen->Cursor = crHourGlass;
      this->Enabled = false;

      try {
        FormImpressaoEntradaProduto = new TFormImpressaoEntradaProduto( FormGerencia );
        FormImpressaoEntradaProduto2 = new TFormImpressaoEntradaProduto2( FormGerencia );

        FormImpressaoEntradaProduto->QRLabelDataInicial->Caption = FormatDateTime( "dd/mm/yyyy", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto->QRLabelDataFinal->Caption = FormatDateTime( "dd/mm/yyyy", StrToDateTime( EditFechamentoDataFinal->Text ) );
        FormImpressaoEntradaProduto2->QRLabelDataInicial->Caption = FormatDateTime( "dd/mm/yyyy", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto2->QRLabelDataFinal->Caption = FormatDateTime( "dd/mm/yyyy", StrToDateTime( EditFechamentoDataFinal->Text ) );

        FormImpressaoEntradaProduto->QueryEntradaFornecedores->Prepare( );
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->ParamByName( "DiaI" )->AsString = FormatDateTime( "dd", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->ParamByName( "MesI" )->AsString = FormatDateTime( "mm", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->ParamByName( "AnoI" )->AsString = FormatDateTime( "yyyy", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->ParamByName( "DiaF" )->AsString = FormatDateTime( "dd", StrToDateTime( EditFechamentoDataFinal->Text ) );
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->ParamByName( "MesF" )->AsString = FormatDateTime( "mm", StrToDateTime( EditFechamentoDataFinal->Text ) );
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->ParamByName( "AnoF" )->AsString = FormatDateTime( "yyyy", StrToDateTime( EditFechamentoDataFinal->Text ) );
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->Open( );

        FormImpressaoEntradaProduto->QueryEntradaItens->Prepare( );
        FormImpressaoEntradaProduto->QueryEntradaItens->Open( );

        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->Prepare( );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->ParamByName( "DiaI" )->AsString = FormatDateTime( "dd", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->ParamByName( "MesI" )->AsString = FormatDateTime( "mm", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->ParamByName( "AnoI" )->AsString = FormatDateTime( "yyyy", StrToDateTime( EditFechamentoDataInicial->Text ) );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->ParamByName( "DiaF" )->AsString = FormatDateTime( "dd", StrToDateTime( EditFechamentoDataFinal->Text ) );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->ParamByName( "MesF" )->AsString = FormatDateTime( "mm", StrToDateTime( EditFechamentoDataFinal->Text ) );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->ParamByName( "AnoF" )->AsString = FormatDateTime( "yyyy", StrToDateTime( EditFechamentoDataFinal->Text ) );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->Open( );

        FormImpressaoEntradaProduto2->QueryEntradaItens->Prepare( );
        FormImpressaoEntradaProduto2->QueryEntradaItens->Open( );

        if( !FormImpressaoEntradaProduto->QueryEntradaFornecedores->IsEmpty( ) ) {
          FormImpressaoEntradaProduto2->QRBand1->Enabled = false;
          //FormImpressaoEntradaProduto2->QRLabelTotalOk2->Caption = FormImpressaoEntradaProduto->QRExprTotalOk->Lines->
        }

        FormImpressaoEntradaProduto->QRCompositeReportEntradaProduto->Preview( );

        FormImpressaoEntradaProduto->QueryEntradaFornecedores->Close( );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->Close( );
        FormImpressaoEntradaProduto->QueryEntradaItens->Close( );
        FormImpressaoEntradaProduto2->QueryEntradaItens->Close( );
      }
      catch( Exception &e ) {
        FormImpressaoEntradaProduto->QueryEntradaFornecedores->Close( );
        FormImpressaoEntradaProduto2->QueryEntradaFornecedores->Close( );
        FormImpressaoEntradaProduto->QueryEntradaItens->Close( );
        FormImpressaoEntradaProduto2->QueryEntradaItens->Close( );
        Application->MessageBox( e.Message.c_str( ), "Impressão de Entrada de Produtos",
                                 MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete FormImpressaoEntradaProduto;
      delete FormImpressaoEntradaProduto2;
      Screen->Cursor = SaveCursor;
      this->Enabled = true;
      EditFechamentoDataInicial->SetFocus( );
    }
  }
}
//---------------------------------------------------------------------------
