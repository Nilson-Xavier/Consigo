//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadConsultaCliente.h"
#include "Dmod1.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TThreadConsultaCliente::TThreadConsultaCliente( String* Nome, String* RG,
  String* EERG, String* Telefone, String* Cep, bool CreateSuspended ) : TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;

  if( Nome != NULL ) {
    this->Nome = new AnsiString( *Nome );
  }
  else {
    this->Nome = new AnsiString( );
  }
  if( RG != NULL ) {
    this->RG = new AnsiString( *RG );
  }
  else {
    this->RG = new AnsiString( );
  }
  if( EERG != NULL ) {
    this->EERG = new AnsiString( *EERG );
  }
  else {
    this->EERG = new AnsiString( );
  }
  if( Telefone != NULL ) {
    this->Telefone = new AnsiString( *Telefone );
  }
  else {
    this->Telefone = new AnsiString( );
  }
  if( Cep != NULL ) {
    this->CEP = new AnsiString( *Cep );
  }
  else {
    this->CEP = new AnsiString( );
  }
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TThreadConsultaCliente::~TThreadConsultaCliente( void ) {

  delete this->Nome;
  delete this->RG;
  delete this->EERG;
  delete this->Telefone;
  delete this->CEP;
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaCliente::Execute( ) {

  TConsigoQuery *Query;
  int i;

  try {
    this->Synchronize( this->DisableEditControl );

    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

    try {
    	for( i = 1; i < FormPrincipal->StringGridCliente->RowCount; i++ ) {
  		 	FormPrincipal->StringGridCliente->Rows[i]->Clear( );
			}
			FormPrincipal->StringGridCliente->RowCount = 2;
      FormPrincipal->StringGridCliente->FixedRows = 1;

      Query->SQL->Add( "SELECT *" );
      Query->SQL->Add( "FROM Clientes" );
      if( this->Nome->IsEmpty( ) ) {
        Query->SQL->Add( "WHERE Nome LIKE '%'" );
      }
      else {
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( *this->Nome, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
      }
      if( this->RG->IsEmpty( ) ) {
        Query->SQL->Add( "AND   RG LIKE '%'" );
      }
      else {
        Query->SQL->Add( "AND   RG = '" + *this->RG + "'" );
      }
      if( this->EERG->IsEmpty( ) ) {
        Query->SQL->Add( "AND   EERG LIKE '%'" );
      }
      else {
        Query->SQL->Add( "AND   EERG = '" + *this->EERG + "'" );
      }
      if( this->Telefone->IsEmpty( ) ) {
        Query->SQL->Add( "AND ( Telefone LIKE '%'" );
        Query->SQL->Add( "OR   Telefone_Comercial LIKE '%'" );
        Query->SQL->Add( "OR   Telefone_Fax LIKE '%' )" );
      }
      else {
        Query->SQL->Add( "AND ( Telefone LIKE '%" + StringReplace( *this->Telefone, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "OR   Telefone_Comercial LIKE '%" + StringReplace( *this->Telefone, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "OR   Telefone_Fax LIKE '%" + StringReplace( *this->Telefone, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%' )" );
      }
      if( this->CEP->IsEmpty( ) ) {
        Query->SQL->Add( "AND   Cep LIKE '%'" );
      }
      else {
        Query->SQL->Add( "AND   Cep = '" + *this->CEP + "'" );
      }
      Query->SQL->Add( "ORDER BY Nome ASC" );
      Query->Prepare( );
      Query->Open( );
	    if( Query->IsEmpty( ) ) {
      	throw Exception( "Cliente Inexistente!!!\r\rConfirme os Dados Digitados !" );
    	}
	    else {
        Query->First( );
        while( !Query->Eof ) {
        	FormPrincipal->StringGridCliente->Cells[0][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          FormPrincipal->StringGridCliente->Cells[1][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Endereco" )->AsString;
          FormPrincipal->StringGridCliente->Cells[2][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Bairro" )->AsString;
          FormPrincipal->StringGridCliente->Cells[3][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Cidade" )->AsString;
          FormPrincipal->StringGridCliente->Cells[4][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Estado" )->AsString;
          FormPrincipal->StringGridCliente->Cells[5][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Cep" )->AsString;
          FormPrincipal->StringGridCliente->Cells[6][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Telefone" )->AsString;
          FormPrincipal->StringGridCliente->Cells[7][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Telefone_Comercial" )->AsString;
          FormPrincipal->StringGridCliente->Cells[8][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Telefone_Fax" )->AsString;
         	FormPrincipal->StringGridCliente->Cells[9][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "RG" )->AsString;
         	FormPrincipal->StringGridCliente->Cells[10][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "EERG" )->AsString;
          FormPrincipal->StringGridCliente->Cells[11][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "CPF" )->AsString;
         	FormPrincipal->StringGridCliente->Cells[12][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "Inscricao_Estadual" )->AsString;
          FormPrincipal->StringGridCliente->Cells[13][FormPrincipal->StringGridCliente->RowCount - 1] = Query->FieldByName( "email" )->AsString;

          Query->Next( );
          if( !Query->Eof ) {
            FormPrincipal->StringGridCliente->RowCount++;
          }
        }
        FormPrincipal->StringGridCliente->SetFocus( );
    	}
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Clientes", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    this->Synchronize( this->EnableEditControl );
  }
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaCliente::DisableEditControl( ) {

  FormPrincipal->EditNomeCliente->Enabled = false;
  FormPrincipal->EditRgCnpj->Enabled = false;
  FormPrincipal->ComboBoxEERG2->Enabled = false;
  FormPrincipal->EditTelefone2->Enabled = false;
  FormPrincipal->EditCep->Enabled = false;
  FormPrincipal->BitBtnInserirCliente->Enabled = false;
  FormPrincipal->BitBtnInformacaoAdicionalCliente->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaCliente::EnableEditControl( ) {

  FormPrincipal->EditNomeCliente->Enabled = true;
  FormPrincipal->EditRgCnpj->Enabled = true;
  FormPrincipal->ComboBoxEERG2->Enabled = true;
  FormPrincipal->EditTelefone2->Enabled = true;
  FormPrincipal->EditCep->Enabled = true;
  FormPrincipal->BitBtnInserirCliente->Enabled = true;
  FormPrincipal->BitBtnInformacaoAdicionalCliente->Enabled = true;
}
//---------------------------------------------------------------------------
