//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Dmod1.h"
#include "Dmod2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::SedexClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetSedex;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditClienteKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    this->ConsultarSedex( &( EditCliente->Text ), NULL, NULL, NULL, NULL, NULL );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditCepKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditCep->Text.Length( ) <= 8 ) ) {
    if( this->EditCep->Text.Length( ) >= 5 ) {
      this->EditCep->Text = this->EditCep->Text.Delete( this->EditCep->Text.Pos( "-" ), 1 );
      this->EditCep->Text = this->EditCep->Text.Insert( "-", 6 );
      this->EditCep->SelStart = this->EditCep->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    this->ConsultarSedex( NULL, &( EditCep->Text ), NULL, NULL, NULL, NULL );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditObjetoKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    this->ConsultarSedex( NULL, NULL, &( EditObjeto->Text ), NULL, NULL, NULL );
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
void __fastcall TFormGerencia::EditCupomKeyPress( TObject *Sender, char &Key ) {

  if( !( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ||
         ( Key == '\b' ) || ( Key == '\r') ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    this->ConsultarSedex( NULL, NULL, NULL, &( EditCupom->Text ), NULL, NULL );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditDataInicialKeyPress( TObject *Sender, char &Key ) {

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
void __fastcall TFormGerencia::EditDataFinalKeyPress(TObject *Sender, char &Key ) {

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
      this->ConsultarSedex( NULL, NULL, NULL, NULL, &( EditDataInicial->Text ), &( EditDataFinal->Text ) );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditCadastroCepKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditCadastroCep->Text.Length( ) <= 8 ) ) {
    if( this->EditCadastroCep->Text.Length( ) >= 5 ) {
      this->EditCadastroCep->Text = this->EditCadastroCep->Text.Delete( this->EditCadastroCep->Text.Pos( "-" ), 1 );
      this->EditCadastroCep->Text = this->EditCadastroCep->Text.Insert( "-", 6 );
      this->EditCadastroCep->SelStart = this->EditCadastroCep->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditCadastroObjeto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditCadastroObjetoKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    EditSedexPreco->SetFocus( );
  }
  if( this->EditCadastroObjeto->Text.Length( ) < 2 ) {
    if( !( ( AnsiCompareStr( Key, "a" ) >= 0 ) && ( AnsiCompareStr( Key, "z" ) <= 0 ) &&
           ( AnsiCompareStr( Key, "A" ) >= 0 ) && ( AnsiCompareStr( Key, "Z" ) <= 0 ) ||
           ( Key == '\b' ) || ( Key == '\r') ) ) {
      Key = NULL;
    }
  }
  else if( ( this->EditCadastroObjeto->Text.Length( ) >= 2 ) &&
           ( this->EditCadastroObjeto->Text.Length( ) <= 10 ) ) {
    if( !( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) ||
           ( Key == '\b' ) || ( Key == '\r') ) ) {
      Key = NULL;
    }
  }
  else if( this->EditCadastroObjeto->Text.Length( ) >= 11 ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditSedexPrecoKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    ComboBoxCupom->SetFocus( );
  }
  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditSedexPreco->Text.Length( ) <= 7 ) || ( Key == '\b' ) ) {
    if( this->EditSedexPreco->Text.Length( ) >= 2 ) {
      this->EditSedexPreco->Text = this->EditSedexPreco->Text.Delete( this->EditSedexPreco->Text.Pos( "," ), 1 );
      if( ( Key == '\b' ) && ( this->EditSedexPreco->Text.Length( ) >= 4 ) ) {
        this->EditSedexPreco->Text = this->EditSedexPreco->Text.Insert( ",", this->EditSedexPreco->Text.Length( ) - 2 );
      }
      if( Key != '\b' ) {
        this->EditSedexPreco->Text = this->EditSedexPreco->Text.Insert( ",", this->EditSedexPreco->Text.Length( ) );
      }
      this->EditSedexPreco->SelStart = this->EditSedexPreco->Text.Length( );
    }
    if( this->EditSedexPreco->Text.Length( ) >= 8 ) {
      Key = NULL;
    }
  }
  else if( Key != '\b' ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ComboBoxCupomKeyDown(TObject *Sender, WORD &Key,
  TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( !ComboBoxCupom->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxCupom->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT DISTINCT Vendem2.Numero_nota" );
        Query->SQL->Add( "FROM Clientes, Vendem2" );
        Query->SQL->Add( "WHERE Cep = '" + EditCadastroCep->Text + "'" );
        Query->SQL->Add( "AND Clientes.RG = Vendem2.RG_Cliente" );
        Query->SQL->Add( "AND Clientes.EERG = Vendem2.EERG_Cliente" );
        Query->SQL->Add( "ORDER BY Numero_nota DESC" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            this->ComboBoxCupom->Items->Append( Query->FieldByName( "Numero_nota" )->AsString );
            Query->Next( );
          }
          ComboBoxCupom->DroppedDown = true;
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Sedex - Cadastro", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxCnpj->DroppedDown ) ) {
    ComboBoxCupom->Clear( );
  }
  if( Key == VK_RETURN ) {
    ComboBoxRG->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ComboBoxRGKeyDown(TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( !ComboBoxRG->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxRG->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	DISTINCT Nome, RG, EERG" );
        Query->SQL->Add( "FROM Clientes, Vendem2" );
        Query->SQL->Add( "WHERE Cep = '" + EditCadastroCep->Text  + "'" );
        if( ComboBoxCupom->Text.IsEmpty( ) ) {
          Query->SQL->Add( "AND   CAST( Numero_nota AS char ) LIKE '%'" );
        }
        else {
          Query->SQL->Add( "AND   CAST( Numero_nota AS char ) LIKE '" + ComboBoxCupom->Text + "'" );
        }
        Query->SQL->Add( "AND Clientes.RG = Vendem2.RG_Cliente" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            this->ComboBoxRG->Items->Append( Query->FieldByName( "Nome" )->AsString + " " +
            Query->FieldByName( "RG" )->AsString + Query->FieldByName( "EERG" )->AsString );
            Query->Next( );
          }
          ComboBoxRG->Font->Size = 8;
          ComboBoxRG->Width = 500;
          ComboBoxRG->DroppedDown = true;
          ComboBoxRG->BringToFront( );
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Sedex - Cadastro", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( ComboBoxRG->DroppedDown ) ) {
    ComboBoxRG->Font->Size = 12;
    ComboBoxRG->Width = 225;
    for( i = ComboBoxRG->Text.Length( ); i >= 1; i-- ) {
      if( ComboBoxRG->Text[i] == ' ' ) {
        ComboBoxEerg->ItemIndex = ComboBoxEerg->Items->IndexOf( UpperCase( ComboBoxRG->Text.SubString( ComboBoxRG->Text.Length( ) - 1, 2 ) ) );
        ComboBoxRG->Text = ComboBoxRG->Text.SubString( i + 1, ( ComboBoxRG->Text.Length( ) -  i ) - 2 );
        break;
      }
    }
  }
  if( ( Key == VK_ESCAPE ) && ( ComboBoxCnpj->DroppedDown ) ) {
    ComboBoxCnpj->Font->Size = 12;
    ComboBoxCnpj->Width = 225;
    ComboBoxCnpj->Clear( );
  }
  if( ( Key == VK_RETURN ) && ( !ComboBoxRG->DroppedDown ) ) {
    ComboBoxEerg->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ComboBoxEergKeyDown(TObject *Sender,
  WORD &Key, TShiftState Shift ) {

	if( Key == VK_RETURN ) {
  	BitBtnSedexConfirmar->SetFocus( );
  }
  else if( ( ( Key == VK_SPACE ) || ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
           ( !ComboBoxEerg->DroppedDown ) ) {
   	 ComboBoxEerg->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ConsultarSedex( String* Nome, String* Cep,
  String* Objeto, String* Cupom, String* DataInicial, String* DataFinal ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  int i;

  try {
    Data = new TDateTime( );
    Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    try {
      for( i = 1; i < StringGridSedex->RowCount; i++ ) {
         StringGridSedex->Rows[i]->Clear( );
      }
      StringGridSedex->RowCount = 2;
      EditTotalSedex->Clear( );

      Query->SQL->Add( "SELECT Clientes.Nome, Sedex.Data, Sedex.Cep, Sedex.Objeto," );
      Query->SQL->Add( "  Sedex.Preco, Sedex.Numero_nota" );
      Query->SQL->Add( " FROM Sedex, Clientes" );
      if( Nome == NULL ) {
        Query->SQL->Add( " WHERE Clientes.Nome LIKE '%'" );
      }
      else {
        Query->SQL->Add( " WHERE Clientes.Nome LIKE '%" + *Nome + "%'" );
      }
      Query->SQL->Add( " AND   Clientes.RG = Sedex.RG_Cliente" );
      Query->SQL->Add( " AND   Clientes.EERG = Sedex.EERG_Cliente" );
      if( Cep == NULL ) {
        Query->SQL->Add( " AND   Sedex.Cep LIKE '%'" );
      }
      else {
        Query->SQL->Add( " AND   Sedex.Cep LIKE '%" + *Cep + "'" );
      }
      if( Objeto == NULL ) {
        Query->SQL->Add( " AND   Objeto LIKE '%'" );
      }
      else {
        Query->SQL->Add( " AND   Objeto LIKE '%" + *Objeto + "'" );
      }
      if( Cupom == NULL ) {
        Query->SQL->Add( " AND   CAST( Numero_nota AS char ) LIKE '%'" );
      }
      else {
        Query->SQL->Add( " AND   CAST( Numero_nota AS char ) LIKE '%" + *Cupom + "'" );
      }
      if( DataInicial == NULL ) {
        Query->SQL->Add( " AND   Data >= '1900/01/01 7:00:00'" );
      }
      else {
        *Data = StrToDateTime( *DataInicial + " 7:00:00" );
        Query->SQL->Add( " AND   Data >= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      if( DataFinal == NULL ) {
        Query->SQL->Add( " AND   Data <= '" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
      }
      else {
      *Data = StrToDateTime( *DataFinal + " 21:00:00" );
      Query->SQL->Add( " AND   Data <= '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'" );
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
          StringGridSedex->Cells[0][StringGridSedex->RowCount - 1] = Query->FieldByName( "Data" )->AsDateTime.FormatString( "dd/mm/yyyy hh:mm:ss" );
          StringGridSedex->Cells[1][StringGridSedex->RowCount - 1] = Query->FieldByName( "Cep" )->AsString;
          StringGridSedex->Cells[2][StringGridSedex->RowCount - 1] = Query->FieldByName( "Objeto" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator= ',';
          StringGridSedex->Cells[3][StringGridSedex->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          StringGridSedex->Cells[4][StringGridSedex->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          StringGridSedex->Cells[5][StringGridSedex->RowCount - 1] = Query->FieldByName( "Numero_nota" )->AsString;

	        if( EditTotalSedex->Text.IsEmpty( ) ) {
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
        StringGridSedex->SetFocus( );
      }
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Sedex", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete Data;
    Query->Close( );
    delete Query;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnSedexConfirmarClick( TObject *Sender ) {

  TConsigoQuery *Query;
  TDateTime *Data;

  if( ( ( EditCadastroCep->Text ).Length( ) < 9 ) || ( Trim( EditCadastroObjeto->Text ).IsEmpty( ) ) ||
      ( Trim( EditSedexPreco->Text ).Length( ) < 3 ) ) {
    Application->MessageBox( "Faltam Campos a serem Preenchidos !", "Sedex", MB_OK | MB_ICONERROR );
  }
  else {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      Data = new TDateTime;

      try {
        Query->SQL->Add( "SELECT *" );
        Query->SQL->Add( "FROM Clientes" );
        if( ComboBoxRG->Text.IsEmpty( ) ) {
          Query->SQL->Add( "WHERE RG = 'Sem RG'" );
          Query->SQL->Add( "AND EERG = 'SP'" );
        }
        else {
          Query->SQL->Add( "WHERE RG = '" + ComboBoxRG->Text + "'" );
          Query->SQL->Add( "AND EERG = '" + ComboBoxEerg->Text + "'" );
        }

        Query->SQL->Add( "ORDER BY Nome ASC" );
        Query->Open( );
		    if( Query->IsEmpty( ) ) {
    		  throw Exception( "O RG e EERG Digitados são Inexistentes !" );
		    }
        Query->Close( );
        Query->SQL->Clear( );
        Query->SQL->Add( "BEGIN TRANSACTION" );
        Query->SQL->Add( "INSERT INTO Sedex ( Data, Cep, Objeto, Preco," );
        Query->SQL->Add( "  RG_Cliente, EERG_Cliente, Numero_nota )" );
        Query->SQL->Add( "VALUES ( '" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'," );
        Query->SQL->Add( "'" + EditCadastroCep->Text + "','" + UpperCase( EditCadastroObjeto->Text ) + "'," );
        Query->SQL->Add( StringReplace( StringReplace( EditSedexPreco->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
        if( ComboBoxRG->Text.IsEmpty( ) ) {
          Query->SQL->Add( "'Sem RG','SP'," );
        }
        else {
          Query->SQL->Add( "'" + ComboBoxRG->Text + "','" + ComboBoxEerg->Text + "'," );
        }
        if( ComboBoxCupom->Text.IsEmpty( ) ) {
          Query->SQL->Add( "0 )" );
        }
        else {
          Query->SQL->Add( ComboBoxCupom->Text + ")" );
        }
        Query->SQL->Add( "COMMIT TRANSACTION" );
        Query->ExecSQL( );
        Application->MessageBox( "A Encomenda Foi Inserida Com Sucesso !", "Sedex", MB_OK | MB_ICONINFORMATION );

        EditCadastroCep->Clear( );
        EditCadastroObjeto->Clear( );
        EditSedexPreco->Clear( );
        ComboBoxCupom->Clear( );
        ComboBoxRG->Clear( );
        EditCadastroCep->SetFocus( );
      }
      catch( Exception &e ) {
        if( DataModuleQuery->consigo_BD->InTransaction ) {
          DataModuleQuery->consigo_BD->Rollback( );
        }
        Application->MessageBox( e.Message.c_str( ), "Sedex", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Data;
      Query->Close( );
      delete Query;
    }
  }
}
//---------------------------------------------------------------------------

