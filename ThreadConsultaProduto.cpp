//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadConsultaProduto.h"
#include "Dmod1.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TThreadConsultaProduto::TThreadConsultaProduto( String* Codigo, String* Marca,
  String* Nome, bool CreateSuspended ): TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;

  if( Codigo != NULL ) {
    this->Codigo_ = new AnsiString( *Codigo );
  }
  else {
    this->Codigo_ = new AnsiString( );
  }
  if( Marca != NULL ) {
    this->Marca_ = new AnsiString( *Marca );
  }
  else {
    this->Marca_ = new AnsiString( );
  }
  if( Nome != NULL ) {
    this->Nome_ = new AnsiString( *Nome );
  }
  else {
    this->Nome_ = new AnsiString( );
  }
  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TThreadConsultaProduto::~TThreadConsultaProduto( void ) {

  delete this->Codigo_;
  delete this->Marca_;
  delete this->Nome_;
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaProduto::Execute( ) {

  TConsigoQuery *Query;
  TJPEGImage *JpegImage;
  String *Path, *File, *Marca;
  int i, j, PalavrasQtd, Tamanho;

  try {
    this->Synchronize( this->DisableEditControl );

    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Path = new AnsiString( );
    File = new AnsiString( );
    Marca = new AnsiString( );
    JpegImage = new TJPEGImage( );

    try {
    	for( i = 1; i < FormPrincipal->StringGridConsultaProduto->RowCount; i++ ) {
  		 	FormPrincipal->StringGridConsultaProduto->Rows[i]->Clear( );
			}
			FormPrincipal->StringGridConsultaProduto->RowCount = 2;
      FormPrincipal->StringGridConsultaProduto->FixedRows = 1;

      Query->SQL->Add( "SELECT 	Codigo, Marca, Nome, Quantidade, Quantidade_," );
      Query->SQL->Add( "Garantia, ( Produtos.Preco * Produtos.Dolar ) AS Preco," );
      Query->SQL->Add( "Path, Arquivo" );
      Query->SQL->Add( "FROM Produtos" );
      if( this->Codigo_->IsEmpty( ) ) {
        Query->SQL->Add( "WHERE Codigo LIKE '%'" );
      }
      else {
        Query->SQL->Add( "WHERE Codigo = '" + *this->Codigo_ + "'" );
      }
      if( this->Marca_->IsEmpty( ) ) {
        Query->SQL->Add( "AND   Marca LIKE '%'" );
      }
      else {
        Query->SQL->Add( "AND   Marca LIKE '" + StringReplace( *this->Marca_, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
      }
      if( this->Nome_->IsEmpty( ) ) {
        Query->SQL->Add( "AND   Nome LIKE '%'" );
      }
      else {
        Query->SQL->Add( "AND   Nome LIKE '%" + StringReplace( *this->Nome_, " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
      }
      Query->SQL->Add( "ORDER BY Marca, Nome ASC" );
      Query->Prepare( );
      Query->Open( );
	    if( Query->IsEmpty( ) ) {
      	throw Exception( "Produto Inexistente!!! \r Verifique os Dados Digitados!" );
    	}
	    else {
        Query->First( );
        while( !Query->Eof ) {
          FormPrincipal->StringGridConsultaProduto->Cells[0][FormPrincipal->StringGridConsultaProduto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          FormPrincipal->StringGridConsultaProduto->Cells[1][FormPrincipal->StringGridConsultaProduto->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          FormPrincipal->StringGridConsultaProduto->Cells[2][FormPrincipal->StringGridConsultaProduto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          FormPrincipal->StringGridConsultaProduto->Cells[3][FormPrincipal->StringGridConsultaProduto->RowCount - 1] = Query->FieldByName( "Quantidade" )->AsString;
          FormPrincipal->StringGridConsultaProduto->Cells[4][FormPrincipal->StringGridConsultaProduto->RowCount - 1] = Query->FieldByName( "Quantidade_" )->AsString;
          FormPrincipal->StringGridConsultaProduto->Cells[5][FormPrincipal->StringGridConsultaProduto->RowCount - 1] = Query->FieldByName( "Garantia" )->AsString;
          FormPrincipal->StringGridConsultaProduto->Cells[6][FormPrincipal->StringGridConsultaProduto->RowCount - 1] = Query->FieldByName( "Codigo" )->AsString;

          Query->Next( );
          if( !Query->Eof ) {
            FormPrincipal->StringGridConsultaProduto->RowCount++;
          }
        }
        Query->First( );
      	*Path = Query->FieldByName( "PATH" )->AsString;
	      *File = Query->FieldByName( "ARQUIVO" )->AsString;
  	    *Marca = Query->FieldByName( "MARCA" )->AsString;
     	 	if( ( !Path->IsEmpty( ) ) && ( !File->IsEmpty( ) ) ) {
          if( FileExists( *Path + '\\' + '\\' + *Marca + '\\' + '\\' + *File ) ) {
           	JpegImage->LoadFromFile( *Path + '\\' + '\\' + *Marca + '\\' + '\\' + *File );
           	FormPrincipal->Image5->Picture->Assign( JpegImage );
          }
       	}
       	else {
        	// Ler uma Imagem da Consigo!!!
          if( FileExists( "P:\\Consigo.jpg" ) ) {
           	JpegImage->LoadFromFile( "P:\\Consigo.jpg" );
           	FormPrincipal->Image5->Picture->Assign( JpegImage );
          }
       	}
        FormPrincipal->StringGridConsultaProduto->SetFocus( );
    	}
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Produtos", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete Path;
    delete File;
    delete Marca;
    delete JpegImage;
    this->Synchronize( this->EnableEditControl );
  }
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaProduto::DisableEditControl( ) {

  FormPrincipal->EditCodigoProduto->Enabled = false;
  FormPrincipal->EditMarca->Enabled = false;
  FormPrincipal->EditNomeProduto->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TThreadConsultaProduto::EnableEditControl( ) {

  FormPrincipal->EditCodigoProduto->Enabled = true;
  FormPrincipal->EditMarca->Enabled = true;
  FormPrincipal->EditNomeProduto->Enabled = true;
}
//---------------------------------------------------------------------------
