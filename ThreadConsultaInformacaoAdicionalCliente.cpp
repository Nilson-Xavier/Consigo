//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadConsultaInformacaoAdicionalCliente.h"
#include "InformacaoAdicionalCliente.h"
#include "Dmod1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TThreadConsultaInfoCliente::TThreadConsultaInfoCliente( String* Nome,
  bool CreateSuspended ) : TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;

  if( Nome != NULL ) {
    this->Nome = new AnsiString( *Nome );
  }
  else {
    this->Nome = new AnsiString( );
  }
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TThreadConsultaInfoCliente::~TThreadConsultaInfoCliente( void ) {

  delete this->Nome;
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaInfoCliente::Execute( ) {

  TConsigoQuery *Query;
  bool *InfoVendem, *InfoVendem2;
  int i;

  try {
    this->Synchronize( this->DisableEditControl );

    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    InfoVendem = new bool( false );
    InfoVendem2 = new bool( false );

    try {
    	for( i = 1; i < FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount; i++ ) {
  		 	FormInformacaoAdicionalCliente->StringGridClienteInfo->Rows[i]->Clear( );
			}
			FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount = 2;
      FormInformacaoAdicionalCliente->StringGridClienteInfo->FixedRows = 1;

      Query->SQL->Add( "SELECT Vendem.Data, Produtos.Marca, Produtos.Nome, Vendem.Quantidade," );
      Query->SQL->Add( "       ( Vendem.Preco / Vendem.Quantidade ) AS PrecoUnit, Vendem.Preco AS PrecoTot," );
      Query->SQL->Add( "       Vendem.Tipo, Vendedores.Nome AS Vendedor, Vendem.Numero_nota," );
      Query->SQL->Add( "       Vendem.Numero_Serie, Clientes.Observacao, Vendem.Entrada," );
      Query->SQL->Add( "       Vendem.Parcelas" );
      Query->SQL->Add( "  FROM Vendem, Produtos, Vendedores, Clientes" );
      Query->SQL->Add( "  WHERE Clientes.Nome = '" + *this->Nome + "'" );
      Query->SQL->Add( "  AND Vendem.EERG_Cliente = Clientes.EERG" );
      Query->SQL->Add( "  AND Vendem.RG_Cliente = Clientes.RG" );
      Query->SQL->Add( "  AND Vendem.EERG_Cliente = Clientes.EERG" );
      Query->SQL->Add( "  AND Vendem.Codigo = Produtos.Codigo" );
      Query->SQL->Add( "  AND Vendem.RG_Vendedor = Vendedores.RG" );
      Query->SQL->Add( "  AND Vendem.EERG_Vendedor = Vendedores.EERG" );
      Query->SQL->Add( "  ORDER BY Vendem.Numero_nota DESC" );
      Query->Prepare( );
      Query->Open( );
	    if( Query->IsEmpty( ) ) {
        *InfoVendem = false;
    	}
	    else {
        *InfoVendem = true;
        Query->First( );
        FormInformacaoAdicionalCliente->MemoObesrvacaoCliente->Text = Query->FieldByName( "Observacao" )->AsString;
        while( !Query->Eof ) {
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[0][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Data" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[1][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[2][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[3][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[4][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "PrecoUnit" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[5][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "PrecoTot" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[6][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Tipo" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[7][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Entrada" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[8][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Parcelas" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[9][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Numero_Serie" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[10][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Numero_nota" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[11][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Vendedor" )->AsString;

          Query->Next( );
          if( !Query->Eof ) {
            FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount++;
          }
        }
      }

      Query->SQL->Clear( );
      Query->SQL->Add( "SELECT Vendem2.Data, Produtos.Marca, Produtos.Nome, Vendem2.Quantidade," );
      Query->SQL->Add( "       ( Vendem2.Preco / Vendem2.Quantidade ) AS PrecoUnit, Vendem2.Preco AS PrecoTot," );
      Query->SQL->Add( "       Vendem2.Tipo, Vendedores.Nome AS Vendedor, Vendem2.Numero_nota," );
      Query->SQL->Add( "       Vendem2.Numero_Serie, Clientes.Observacao, Vendem2.Entrada," );
      Query->SQL->Add( "       Vendem2.Parcelas" );
      Query->SQL->Add( "  FROM Vendem2, Produtos, Vendedores, Clientes" );
      Query->SQL->Add( "  WHERE Clientes.Nome = '" + *this->Nome + "'" );
      Query->SQL->Add( "  AND Vendem2.EERG_Cliente = Clientes.EERG" );
      Query->SQL->Add( "  AND Vendem2.RG_Cliente = Clientes.RG" );
      Query->SQL->Add( "  AND Vendem2.EERG_Cliente = Clientes.EERG" );
      Query->SQL->Add( "  AND Vendem2.Codigo = Produtos.Codigo" );
      Query->SQL->Add( "  AND Vendem2.RG_Vendedor = Vendedores.RG" );
      Query->SQL->Add( "  AND Vendem2.EERG_Vendedor = Vendedores.EERG" );
      Query->SQL->Add( "  ORDER BY Vendem2.Numero_nota DESC" );
      Query->Prepare( );
      Query->Open( );
	    if( Query->IsEmpty( ) ) {
        *InfoVendem2 = false;
    	}
	    else {
        *InfoVendem2 = true;
        Query->First( );
        FormInformacaoAdicionalCliente->MemoObesrvacaoCliente->Text = Query->FieldByName( "Observacao" )->AsString;
        if( *InfoVendem ) {
          FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount++;
        }
        while( !Query->Eof ) {
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[0][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Data" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[1][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[2][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[3][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[4][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "PrecoUnit" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[5][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "PrecoTot" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[6][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Tipo" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[7][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Entrada" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[8][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Parcelas" )->AsFloat );
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[9][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Numero_Serie" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[10][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Numero_nota" )->AsString;
          FormInformacaoAdicionalCliente->StringGridClienteInfo->Cells[11][FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount - 1] = Query->FieldByName( "Vendedor" )->AsString;

          Query->Next( );
          if( !Query->Eof ) {
            FormInformacaoAdicionalCliente->StringGridClienteInfo->RowCount++;
          }
        }
    	}
      if( ( !*InfoVendem ) && ( !*InfoVendem2 ) ) {
        throw Exception( "NÃO Há Nenhuma Venda Deste Cliente !!!" );
      }
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Informações Adicionais do Cliente", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete InfoVendem;
    delete InfoVendem2;
    this->Synchronize( this->EnableEditControl );
  }
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaInfoCliente::DisableEditControl( ) {

  FormInformacaoAdicionalCliente->ComboBoxNomeCliente->Enabled = false;
  FormInformacaoAdicionalCliente->BitBtnVoltar->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaInfoCliente::EnableEditControl( ) {

  FormInformacaoAdicionalCliente->ComboBoxNomeCliente->Enabled = true;
  FormInformacaoAdicionalCliente->BitBtnVoltar->Enabled = true;
}
//---------------------------------------------------------------------------