//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Dmod1.h"
#include "Dmod2.h"
#include "ImpressaoDespesa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemDespesasClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetDespesas;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditDespesaDataInicialKeyPress( TObject *Sender,
  char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditDespesaDataInicial->Text.Length( ) <= 7 ) ) {
    if( this->EditDespesaDataInicial->Text.Length( ) >= 2 ) {
      this->EditDespesaDataInicial->Text = this->EditDespesaDataInicial->Text.Delete( this->EditDespesaDataInicial->Text.Pos( "/" ), 1 );
      this->EditDespesaDataInicial->Text = this->EditDespesaDataInicial->Text.Insert( "/", 3 );
      this->EditDespesaDataInicial->SelStart = this->EditDespesaDataInicial->Text.Length( );
      if( this->EditDespesaDataInicial->Text.Length( ) >= 5 ) {
        this->EditDespesaDataInicial->Text = this->EditDespesaDataInicial->Text.Delete( 6, 1 );
        this->EditDespesaDataInicial->Text = this->EditDespesaDataInicial->Text.Insert( "/", 6 );
        this->EditDespesaDataInicial->SelStart = this->EditDespesaDataInicial->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( this->EditDespesaDataInicial->Text.Length( ) == 7 ) {
    this->EditDespesaDataFinal->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditDespesaDataFinalKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditDespesaDataFinal->Text.Length( ) <= 7 ) ) {
    if( this->EditDespesaDataFinal->Text.Length( ) >= 2 ) {
      this->EditDespesaDataFinal->Text = this->EditDespesaDataFinal->Text.Delete( this->EditDespesaDataFinal->Text.Pos( "/" ), 1 );
      this->EditDespesaDataFinal->Text = this->EditDespesaDataFinal->Text.Insert( "/", 3 );
      this->EditDespesaDataFinal->SelStart = this->EditDespesaDataFinal->Text.Length( );
      if( this->EditDespesaDataFinal->Text.Length( ) >= 5 ) {
        this->EditDespesaDataFinal->Text = this->EditDespesaDataFinal->Text.Delete( 6, 1 );
        this->EditDespesaDataFinal->Text = this->EditDespesaDataFinal->Text.Insert( "/", 6 );
        this->EditDespesaDataFinal->SelStart = this->EditDespesaDataFinal->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    if( StrToDate( EditDespesaDataInicial->Text ) > StrToDate( EditDespesaDataFinal->Text ) ) {
      Application->MessageBox( "A Data Inicial Não Pode Ser Maior que a Data Final !", "Despesas", MB_OK | MB_ICONERROR );
    }
    else if( ( EditDespesaDataInicial->Text.Length( ) < 8 ) ||
             ( EditDespesaDataFinal->Text.Length( ) < 8 ) ) {
      Application->MessageBox( "É Necassário a Data Completa para a Consulta !", "Despesas", MB_OK | MB_ICONERROR );
    }
    else {
      this->ConsultarDespesa( &(EditDespesaDataInicial->Text), &(EditDespesaDataFinal->Text),
        &(EditDespesa->Text) );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditDespesaKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    if( ( EditDespesaDataInicial->Text.Length( ) < 8 ) || ( EditDespesaDataFinal->Text.Length( ) < 8 ) ) {
      this->ConsultarDespesa( NULL, NULL, &(EditDespesa->Text) );
    }
    else {
      this->ConsultarDespesa( &(EditDespesaDataInicial->Text), &(EditDespesaDataFinal->Text),
        &(EditDespesa->Text) );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditNomeKeyPress( TObject *Sender, char &Key ) {

	if( Key == 13 ) {
  	EditValor->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditValorKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
  	EditVencimento->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditValor->Text.Length( ) <= 8 ) || ( Key == '\b' ) ) {
    if( this->EditValor->Text.Length( ) >= 2 ) {
      this->EditValor->Text = this->EditValor->Text.Delete( this->EditValor->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditValor->Text.Length( ) >= 4 ) ) {
        this->EditValor->Text = this->EditValor->Text.Insert( ",", this->EditValor->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditValor->Text = this->EditValor->Text.Insert( ",", this->EditValor->Text.Length( ) );
      }
      this->EditValor->SelStart = this->EditValor->Text.Length( );
    }
    if( this->EditValor->Text.Length( ) >= 9 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditVencimentoKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditVencimento->Text.Length( ) <= 7 ) ) {
    if( this->EditVencimento->Text.Length( ) >= 2 ) {
      this->EditVencimento->Text = this->EditVencimento->Text.Delete( this->EditVencimento->Text.Pos( "/" ), 1 );
      this->EditVencimento->Text = this->EditVencimento->Text.Insert( "/", 3 );
      this->EditVencimento->SelStart = this->EditVencimento->Text.Length( );
      if( this->EditVencimento->Text.Length( ) >= 5 ) {
        this->EditVencimento->Text = this->EditVencimento->Text.Delete( 6, 1 );
        this->EditVencimento->Text = this->EditVencimento->Text.Insert( "/", 6 );
        this->EditVencimento->SelStart = this->EditVencimento->Text.Length( );
      }
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( this->EditVencimento->Text.Length( ) == 7 ) {
    this->BitBtnInserirDespesa->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ConsultarDespesa( String* DataInicial, String* DataFinal,
  String* Nome ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  int i;

  try {

    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Data = new TDateTime( );
    FormImpressaoDespesa = new TFormImpressaoDespesa( FormGerencia );

    try {

      for( i = 1; i < StringGridDespesa->RowCount; i++ ) {
   	    StringGridDespesa->Rows[i]->Clear( );
    	}
      StringGridDespesa->RowCount = 2;
      EditTotal->Clear( );
      Query->SQL->Add( "SELECT Despesas.Vencimento, Despesas.Nome, Despesas.Valor," );
      Query->SQL->Add( "       Despesas.Data" );
      Query->SQL->Add( "  FROM Despesas" );
      if( DataInicial == NULL ) {
        Query->SQL->Add( "  WHERE Despesas.Vencimento >= '1900/01/01 7:00:00'" );
      }
      else {
        *Data = StrToDateTime( *DataInicial + " 7:00:00" );
        Query->SQL->Add( "  WHERE Despesas.Vencimento >= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      if( DataFinal == NULL ) {
        Query->SQL->Add( "  AND   Despesas.Vencimento <= '" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      else {
        *Data = StrToDateTime( *DataFinal + " 21:00:00" );
        Query->SQL->Add( "  AND   Despesas.Vencimento <= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      Query->SQL->Add( "  AND   Despesas.Nome LIKE '%" + StringReplace( *Nome, " ", "%", TReplaceFlags( ) << rfReplaceAll ) + "%'" );
      Query->SQL->Add( "ORDER BY Despesas.Vencimento ASC" );
      Query->Open( );
      if( Query->IsEmpty( ) ) {
        throw Exception( "Não Há Despesas Neste Intervalo de Data!" );
      }
      else {
        Query->First( );
        while( !Query->Eof ) {
          if( !StringGridDespesa->Cells[0][1].IsEmpty( ) ) {
            StringGridDespesa->RowCount++;
          }
          StringGridDespesa->Cells[0][StringGridDespesa->RowCount - 1] = FormatDateTime( "dd/mm/yyyy", Query->FieldByName( "Vencimento" )->AsDateTime );
          StringGridDespesa->Cells[1][StringGridDespesa->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          StringGridDespesa->Cells[2][StringGridDespesa->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Valor" )->AsFloat );
          StringGridDespesa->Cells[3][StringGridDespesa->RowCount - 1] = FormatDateTime( "dd/mm/yyyy h:nn", Query->FieldByName( "Data" )->AsDateTime );
          if( Trim( EditTotal->Text ) == "" ) {
          	EditTotal->Text = FormatFloat( "#,##0.00", Query->FieldByName( "Valor" )->AsFloat );
          }
          else {
            EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + Query->FieldByName( "Valor" )->AsFloat ) );
          }
          Query->Next( );
        }

        if( ( DataInicial != NULL ) && ( DataFinal != NULL ) ) {
          if( Application->MessageBox( "Você Deseja Imprimir as Despesas?", "Despesas", MB_YESNO | MB_ICONQUESTION ) == IDYES ) {
            FormImpressaoDespesa->QRLabelDataInicial->Caption = FormatDateTime( "dd/mm/yyyy", StrToDate( *DataInicial ) );
            FormImpressaoDespesa->QRLabelDataFinal->Caption = FormatDateTime( "dd/mm/yyyy", StrToDate( *DataFinal ) );
            *Data = StrToDate( *DataInicial );
            FormImpressaoDespesa->QueryDespesa->ParamByName( "Data_Inicial" )->AsDate = Data->FormatString( "dd/mm/yy" );
            *Data = StrToDate( *DataFinal );
            FormImpressaoDespesa->QueryDespesa->ParamByName( "Data_Final" )->AsDate = Data->FormatString( "dd/mm/yy" );
          }
          FormImpressaoDespesa->QueryDespesa->ParamByName( "Nome" )->AsString = "%" + StringReplace( *Nome, " ", "%", TReplaceFlags( ) << rfReplaceAll ) + "%";
          FormImpressaoDespesa->QueryDespesa->Open( );
          FormImpressaoDespesa->QuickRepDespesa->Preview( );
        }
      }
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Despesas", MB_OK | MB_ICONERROR );
      EditDespesaDataInicial->SetFocus( );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete Data;
    FormImpressaoDespesa->QueryDespesa->Close( );
    delete FormImpressaoDespesa;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnInserirDespesaClick( TObject *Sender ) {

  TDateTime *Data;
  TConsigoQuery *Query;

	if( ( Trim( EditNome->Text ).IsEmpty( ) ) || ( Trim( EditValor->Text ).Length( ) < 4 ) ||
  		( Trim( EditVencimento->Text ).Length( ) < 8 ) ) {
  	Application->MessageBox( "Você Deve Preencher Todos os Campos para Inserir a Despesa!!!",
    												 "Despesas", MB_OK | MB_ICONERROR );
    EditNome->SetFocus( );
  }
  else {
		try {
      Data = new TDateTime( );
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

  	  try {
        Query->SQL->Add( "BEGIN TRANSACTION" );
        Query->SQL->Add( "INSERT INTO Despesas ( Vencimento, Nome, Valor, Data )" );
        *Data = EditVencimento->Text;
        Query->SQL->Add( "VALUES ( '" + Data->FormatString( "yyyy/mm/dd" ) + "'," );
        Query->SQL->Add( "'" + LowerCase( Trim( EditNome->Text ) ) + "'," );
        Query->SQL->Add( StringReplace( StringReplace( EditValor->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
        Query->SQL->Add( "'" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "' )" );
        Query->SQL->Add( "COMMIT TRANSACTION" );
        Query->Prepare( );
        Query->ExecSQL( );

        EditNome->Clear( );
        EditValor->Clear( );
        EditVencimento->Clear( );

		  	Application->MessageBox( "Despesa Inserida com Sucesso!",
    	   												 "Despesas", MB_OK | MB_ICONINFORMATION );

	    }
  	  catch( Exception &e ) {
	  		if( DataModuleQuery->consigo_BD->InTransaction ) {
  	  		DataModuleQuery->consigo_BD->Rollback( );
			  }
  	    Application->MessageBox( e.Message.c_str( ), "Despesas", MB_OK | MB_ICONERROR );
    	  EditNome->SetFocus( );
	    }
  	}
  	__finally {
    	delete Data;
  	  PageControl1->ActivePage = TabSheetDespesas;
    	EditNome->SetFocus( );
	  }
  }
}
//---------------------------------------------------------------------------



