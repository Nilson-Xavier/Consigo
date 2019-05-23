//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Dmod1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditClienteKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    this->ConsultarSedex( Trim( EditCliente->Text ), "", "", "", "", "" );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditSedexCepKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditSedexCep->Text.Length( ) <= 8 ) ) {
    if( this->EditSedexCep->Text.Length( ) >= 5 ) {
      this->EditSedexCep->Text = this->EditSedexCep->Text.Delete( this->EditSedexCep->Text.Pos( "-" ), 1 );
      this->EditSedexCep->Text = this->EditSedexCep->Text.Insert( "-", 6 );
      this->EditSedexCep->SelStart = this->EditSedexCep->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    this->ConsultarSedex( "", Trim( EditSedexCep->Text ), "", "", "", "" );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditObjetoKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    this->ConsultarSedex( "", "", Trim( EditObjeto->Text ), "", "", "" );
  }
  if( this->EditObjeto->Text.Length( ) < 2 ) {
    if( !( ( AnsiCompareStr( Key, "a" ) >= 0 ) && ( AnsiCompareStr( Key, "z" ) <= 0 ) &&
           ( AnsiCompareStr( Key, "A" ) >= 0 ) && ( AnsiCompareStr( Key, "Z" ) <= 0 ) ||
           ( Key == '\b' ) || ( Key == '\r') ) ) {
      Key = NULL;
    }
  }
  else if( ( this->EditObjeto->Text.Length( ) >= 2 ) &&
           ( this->EditObjeto->Text.Length( ) <= 10 ) ) {
    if( !( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ||
           ( Key == '\b' ) || ( Key == '\r') ) ) {
      Key = NULL;
    }
  }
  else if( this->EditObjeto->Text.Length( ) >= 11 ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditCupomKeyPress( TObject *Sender, char &Key ) {

  if( !( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ||
         ( Key == '\b' ) || ( Key == '\r') ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    this->ConsultarSedex( "", "", "", Trim( EditCupom->Text ), "", "" );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditDataInicialKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditDataInicial->Text.Length( ) <= 7 ) ) {
    if( this->EditDataInicial->Text.Length( ) >= 2 ) {
      this->EditDataInicial->Text = this->EditDataInicial->Text.Delete( this->EditDataInicial->Text.Pos( "/" ), 1 );
      this->EditDataInicial->Text = this->EditDataInicial->Text.Insert( "/", 3 );
      this->EditDataInicial->SelStart = this->EditDataInicial->Text.Length( );
      if( this->EditDataInicial->Text.Length( ) >= 5 ) {
        this->EditDataInicial->Text = this->EditDataInicial->Text.Delete( 6, 1 );
        this->EditDataInicial->Text = this->EditDataInicial->Text.Insert( "/", 6 );
        this->EditDataInicial->SelStart = this->EditDataInicial->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( this->EditDataInicial->Text.Length( ) == 7 ) {
    this->EditDataFinal->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::EditDataFinalKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditDataFinal->Text.Length( ) <= 7 ) ) {
    if( this->EditDataFinal->Text.Length( ) >= 2 ) {
      this->EditDataFinal->Text = this->EditDataFinal->Text.Delete( this->EditDataFinal->Text.Pos( "/" ), 1 );
      this->EditDataFinal->Text = this->EditDataFinal->Text.Insert( "/", 3 );
      this->EditDataFinal->SelStart = this->EditDataFinal->Text.Length( );
      if( this->EditDataFinal->Text.Length( ) >= 5 ) {
        this->EditDataFinal->Text = this->EditDataFinal->Text.Delete( 6, 1 );
        this->EditDataFinal->Text = this->EditDataFinal->Text.Insert( "/", 6 );
        this->EditDataFinal->SelStart = this->EditDataFinal->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    if( StrToDate( EditDataInicial->Text ) > StrToDate( EditDataFinal->Text ) ) {
      Application->MessageBox( "A Data Inicial Não Pode Ser Maior que a Data Final !", "Sedex", MB_OK | MB_ICONERROR );
    }
    else {
      this->ConsultarSedex( "", "", "", "", EditDataInicial->Text, EditDataFinal->Text );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::ConsultarSedex( String Nome, String Cep,
  String Objeto, String Cupom, String DataInicial, String DataFinal ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  int i;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Data = new TDateTime( );

    try {
    	for( i = 1; i < FormPrincipal->StringGridSedex->RowCount; i++ ) {
  		 	FormPrincipal->StringGridSedex->Rows[i]->Clear( );
			}
			FormPrincipal->StringGridSedex->RowCount = 2;
      EditTotalSedex->Clear( );
      Query->SQL->Add( "SELECT Clientes.Nome, Sedex.Data, Sedex.Cep, Sedex.Objeto," );
      Query->SQL->Add( "       Sedex.Preco, Sedex.Numero_nota" );
      Query->SQL->Add( "FROM Sedex, Clientes" );
      Query->SQL->Add( "WHERE Clientes.Nome LIKE '%" + StringReplace( Nome, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
      Query->SQL->Add( "AND   Clientes.RG = Sedex.RG_Cliente" );
      Query->SQL->Add( "AND   Clientes.EERG = Sedex.EERG_Cliente" );
      Query->SQL->Add( "AND   Sedex.Cep LIKE '" + Cep + "%'" );
      Query->SQL->Add( "AND   Objeto LIKE '" + Objeto + "%'" );
      Query->SQL->Add( "AND   CAST( Numero_nota AS char ) LIKE '" + Cupom + "%'" );
      if( DataInicial.IsEmpty( ) ) {
        Query->SQL->Add( "AND   Data >= '1900/01/01 7:00:00'" );
      }
      else {
        *Data = StrToDateTime( DataInicial + " 7:00:00" );
        Query->SQL->Add( "AND   Data >= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      if( DataFinal.IsEmpty( ) ) {
        Query->SQL->Add( "AND   Data <= '" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      else {
        *Data = StrToDateTime( DataFinal + " 21:00:00" );
        Query->SQL->Add( "AND   Data <= '" +  Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      Query->SQL->Add( "ORDER BY Data, Numero_nota" );
      Query->Open( );
      if( Query->IsEmpty( ) ) {
        throw Exception( "Não Há Nenhuma Encomenda com Estes Dados !" );
      }
      else {
        Query->First( );
        while( !Query->Eof ) {
          if( !StringGridSedex->Cells[0][1].IsEmpty( ) ) {
            StringGridSedex->RowCount++;
          }
          StringGridSedex->Cells[0][StringGridSedex->RowCount - 1] = Query->FieldByName( "Data" )->AsString;
          StringGridSedex->Cells[1][StringGridSedex->RowCount - 1] = Query->FieldByName( "Cep" )->AsString;
          StringGridSedex->Cells[2][StringGridSedex->RowCount - 1] = Query->FieldByName( "Objeto" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          StringGridSedex->Cells[3][StringGridSedex->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          StringGridSedex->Cells[4][StringGridSedex->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          StringGridSedex->Cells[5][StringGridSedex->RowCount - 1] = Query->FieldByName( "Numero_nota" )->AsString;

	        if( Trim( EditTotalSedex->Text ).IsEmpty( ) ) {
  	        DecimalSeparator = ',';
    	      ThousandSeparator = '.';
      	    EditTotalSedex->Text = FormatFloat( "#,##0.00", StrToFloat( StringReplace( StringGridSedex->Cells[3][StringGridSedex->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
        	}
	        else {
      	    DecimalSeparator = ',';
        	  ThousandSeparator = '.';
          	EditTotalSedex->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotalSedex->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + StrToFloat( StringReplace( StringGridSedex->Cells[3][StringGridSedex->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
	        }

          Query->Next( );
        }
      }
    }
    catch( Exception &e ) {
    	for( i = 1; i < FormPrincipal->StringGridSedex->RowCount; i++ ) {
  		 	FormPrincipal->StringGridSedex->Rows[i]->Clear( );
			}
      StringGridSedex->RowCount = 2;
      EditTotalSedex->Clear( );
      Application->MessageBox( e.Message.c_str( ), "Sedex", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete Data;
  }
}
//---------------------------------------------------------------------------

