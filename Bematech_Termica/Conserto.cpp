//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Conserto.h"
#include "Main.h"
#include "Dmod1.h"
#include "OrdemDeServico.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditOrdemServicoKeyPress(TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    this->ConsultarConserto( &(EditOrdemServico->Text), NULL, NULL, NULL );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) &&
      ( AnsiCompareStr( Key, "9" ) <= 0 ) ) {
    if( ( this->EditOrdemServico->Text.Length( ) == 0 ) && ( AnsiCompareStr( Key, "0" ) == 0 ) ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditConsertoNumeroSerieKeyPress( TObject *Sender,
  char &Key ) {

  if( ( Key == ' ' ) && ( ( EditConsertoNumeroSerie->Text.IsEmpty( ) ) ||
      ( EditConsertoNumeroSerie->Text[EditConsertoNumeroSerie->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    this->ConsultarConserto( NULL, &(EditConsertoNumeroSerie->Text), NULL, NULL );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ComboBoxConsertoClienteKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ( ComboBoxConsertoCliente->Text ).Length( ) > 2 ) &&
        ( !ComboBoxConsertoCliente->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxConsertoCliente->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome" );
        Query->SQL->Add( "FROM Clientes" );
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( Trim( ComboBoxConsertoCliente->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            FormPrincipal->ComboBoxConsertoCliente->Items->Append( Query->FieldByName( "Nome" )->AsString );
            Query->Next( );
          }
          ComboBoxConsertoCliente->Font->Size = 8;
          ComboBoxConsertoCliente->DroppedDown = true;
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
  if( ( Key == VK_RETURN ) && ( ComboBoxConsertoCliente->DroppedDown ) ) {
    ComboBoxConsertoCliente->Font->Size = 12;
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxConsertoCliente->DroppedDown ) ) {
    ComboBoxConsertoCliente->Font->Size = 12;
    ComboBoxConsertoCliente->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxConsertoCliente->DroppedDown ) ) {
    this->ConsultarConserto( NULL, NULL, &(ComboBoxConsertoCliente->Text), NULL );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditConsertoDataKeyPress(TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditConsertoData->Text.Length( ) <= 7 ) ) {
    if( this->EditConsertoData->Text.Length( ) >= 2 ) {
      this->EditConsertoData->Text = this->EditConsertoData->Text.Delete( this->EditConsertoData->Text.Pos( "/" ), 1 );
      this->EditConsertoData->Text = this->EditConsertoData->Text.Insert( "/", 3 );
      this->EditConsertoData->SelStart = this->EditConsertoData->Text.Length( );
      if( this->EditConsertoData->Text.Length( ) >= 5 ) {
        this->EditConsertoData->Text = this->EditConsertoData->Text.Delete( 6, 1 );
        this->EditConsertoData->Text = this->EditConsertoData->Text.Insert( "/", 6 );
        this->EditConsertoData->SelStart = this->EditConsertoData->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    this->ConsultarConserto( NULL, NULL, NULL, &(EditConsertoData->Text) );
  }
}
//---------------------------------------------------------------------------
void TFormPrincipal::ConsultarConserto( String* OrdemServico, String* NumeroSerie,
  String* Cliente, String* Data ) {

  TConsigoQuery *Query;
  TDateTime *Date;
  int i;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Date = new TDateTime( );

    try {
    	for( i = 1; i < FormPrincipal->StringGridConserto->RowCount; i++ ) {
  		 	FormPrincipal->StringGridConserto->Rows[i]->Clear( );
			}
			FormPrincipal->StringGridConserto->RowCount = 2;
      Query->SQL->Add( "SELECT Conserto.Ordem_Servico, Conserto.Data, Conserto.Data_Entrega, Conserto_Status.Status," );
      Query->SQL->Add( "       Produtos.Marca, Produtos.Nome AS Produto, Conserto.Numero_Serie," );
      Query->SQL->Add( "       Conserto.Preco, Clientes.Nome AS Cliente, Vendedores.Nome AS Vendedor, Conserto.Observacao" );
      Query->SQL->Add( "FROM Conserto, Conserto_Status, Produtos, Clientes, Vendedores" );
      if( Cliente == NULL ) {
        Query->SQL->Add( "WHERE Clientes.Nome LIKE '%'" );
      }
      else {
        Query->SQL->Add( "WHERE Clientes.Nome LIKE '%" + StringReplace( *Cliente, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
      }
      Query->SQL->Add( "AND   Clientes.RG = Conserto.RG_Cliente" );
      Query->SQL->Add( "AND   Clientes.EERG = Conserto.EERG_Cliente" );
      Query->SQL->Add( "AND   Vendedores.RG = Conserto.RG_Vendedor" );
      Query->SQL->Add( "AND   Vendedores.EERG = Conserto.EERG_Vendedor" );
      Query->SQL->Add( "AND   Produtos.Codigo = Conserto.Codigo" );
      Query->SQL->Add( "AND   Conserto_Status.Codigo = Conserto.Status" );
      if( NumeroSerie != NULL ) {
        Query->SQL->Add( "AND   Conserto.Numero_Serie LIKE '%" + StringReplace( *NumeroSerie, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
      }
      if( OrdemServico != NULL ) {
        Query->SQL->Add( "AND   Conserto.Ordem_Servico = " + *OrdemServico );
      }
      if( Data != NULL ) {
        *Date = StrToDateTime( *Data + " 7:00:00" );
        Query->SQL->Add( "AND   Data >= '" + Date->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
        *Date = StrToDateTime( *Data + " 21:00:00" );
        Query->SQL->Add( "AND   Data <= '" + Date->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      Query->SQL->Add( "ORDER BY Conserto.Ordem_Servico, Conserto.Data, Clientes.Nome DESC" );
      Query->Open( );
      if( Query->IsEmpty( ) ) {
        FormPrincipal->MemoConsertoDefeito->Clear( );
        throw Exception( "Não Há Nenhuma Ordem De Serviço com Estes Dados !" );
      }
      else {
        Query->First( );
        while( !Query->Eof ) {
          if( !FormPrincipal->StringGridConserto->Cells[0][1].IsEmpty( ) ) {
            FormPrincipal->StringGridConserto->RowCount++;
          }
          else {
            FormPrincipal->MemoConsertoDefeito->Text = Query->FieldByName( "Observacao" )->AsString;
          }
          FormPrincipal->StringGridConserto->Cells[0][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Ordem_Servico" )->AsString;
          FormPrincipal->StringGridConserto->Cells[1][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Data" )->AsDateTime.FormatString( "dd/mm/yy" );
          if( Query->FieldByName( "Data_Entrega" )->AsDateTime.FormatString( "dd/mm/yy" ) != "30/12/99" ) {
            FormPrincipal->StringGridConserto->Cells[2][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Data_Entrega" )->AsDateTime.FormatString( "dd/mm/yy" );
          }
          FormPrincipal->StringGridConserto->Cells[3][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Status" )->AsString;
          FormPrincipal->StringGridConserto->Cells[4][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          FormPrincipal->StringGridConserto->Cells[5][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Produto" )->AsString;
          FormPrincipal->StringGridConserto->Cells[6][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Numero_Serie" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          FormPrincipal->StringGridConserto->Cells[7][FormPrincipal->StringGridConserto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          FormPrincipal->StringGridConserto->Cells[8][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Cliente" )->AsString;
          FormPrincipal->StringGridConserto->Cells[9][FormPrincipal->StringGridConserto->RowCount - 1] = Query->FieldByName( "Vendedor" )->AsString;
          MemoDefeito[FormPrincipal->StringGridConserto->RowCount - 2] = new TMemo( FormPrincipal );
          MemoDefeito[FormPrincipal->StringGridConserto->RowCount - 2]->Text = Query->FieldByName( "Observacao" )->AsString;
          Query->Next( );
        }
        MemoConsertoDefeito->Text = MemoDefeito[0]->Text;
        FormPrincipal->StringGridConserto->SetFocus( );
      }
    }
    catch( Exception &e ) {
    	for( i = 1; i < FormPrincipal->StringGridConserto->RowCount; i++ ) {
  		 	FormPrincipal->StringGridConserto->Rows[i]->Clear( );
			}
      FormPrincipal->StringGridConserto->RowCount = 2;
      Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete Date;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::StringGridConsertoSelectCell( TObject *Sender,
  int ACol, int ARow, bool &CanSelect) {

    if( MemoDefeito[ARow - 1] != NULL ) {
      if( !MemoDefeito[ARow - 1]->Text.IsEmpty( ) ) {
        MemoConsertoDefeito->Text = MemoDefeito[ARow - 1]->Text;
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::BitBtnInserirOrdemServicoClick( TObject *Sender) {

	try {
    FormOrdemDeServico = new TFormOrdemDeServico( FormPrincipal );
		FormOrdemDeServico->Show( );
    FormOrdemDeServico->ComboBoxVendedor->SetFocus( );
  }
  catch( Exception &e ) {
  	Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------

