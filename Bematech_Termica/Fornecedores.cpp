//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Main.h"
#include "Dmod1.h"
#include "Dmod2.h"
#include "CadastroFornecedor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemFornecedoresClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetFornecedores;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnInserirFornecedorClick( TObject *Sender ) {

  try {
    FormInserirFornecedor = new TFormInserirFornecedor( FormPrincipal );
    FormInserirFornecedor->Show( );
  }
  catch( Exception &e ) {
  	Application->MessageBox( e.Message.c_str( ), "Inserção de Fornecedores",
     												 MB_OK | MB_ICONERROR );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnRemoverFornecedorClick( TObject *Sender ) {

  TConsigoQuery *Query;
  int i, j;

	if( this->StringGridFornecedor->Cells[0][1].IsEmpty( ) ) {
  	Application->MessageBox( "Não Há Fornecedor na Tabela para Remover !", "Fornecedores",
      												 MB_OK | MB_ICONERROR );
    EditNomeFornecedor->SetFocus( );
  }
  else {
		if( Application->MessageBox( ( "Você tem Certeza que Deseja Remover o Fornecedor:\r\r"  + this->StringGridFornecedor->Cells[0][1] ).c_str( ),
  	                						 "Fornecedores", MB_YESNO | MB_ICONWARNING ) == ID_YES ) {
      try {
        Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

		    try {
          if( !DataModuleQuery->consigo_BD->Connected ) {
            DataModuleQuery->consigo_BD->Open( );
          }
  		    DataModuleQuery->consigo_BD->StartTransaction( );
          Query->SQL->Add( "BEGIN TRANSACTION" );
          Query->SQL->Add( "DELETE FROM Fornecedores" );
          Query->SQL->Add( "WHERE  Fornecedores.CGC = '" + this->StringGridFornecedor->Cells[8][1] + "'" );
          Query->SQL->Add( "COMMIT TRANSACTION" );
	  	  	Query->ExecSQL( );
	  	    DataModuleQuery->consigo_BD->Commit( );

          for( i = 1; i < this->StringGridFornecedor->RowCount; i++ ) {
            for( j = 0; j <= 7; j++ ) {
              this->StringGridFornecedor->Cells[j][i] = this->StringGridFornecedor->Cells[j][i+1];
            }
          }
          if( this->StringGridFornecedor->RowCount != 2 ) {
            this->StringGridFornecedor->RowCount --;
          }
          EditNomeFornecedor->Clear( );
					Application->MessageBox( "Fornecedor Foi Removido com Sucesso!", "Fornecedores",
    	    												 MB_OK | MB_ICONINFORMATION );
	    	}
	  	  catch( Exception &e ) {
  	    	if( DataModuleQuery->consigo_BD->InTransaction ) {
	  	  	  DataModuleQuery->consigo_BD->Rollback( );
      	  }
      		Application->MessageBox( e.Message.c_str( ), "Fornecedores", MB_OK | MB_ICONERROR );
		    }
      }
      __finally {
        delete Query;
      }
  	}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridFornecedorKeyDown(TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  int i, j;

  if( Key == VK_DELETE ) {
		if( Application->MessageBox( ( "Você tem Certeza que Deseja Remover o Fornecedor:\r\r"  + this->StringGridFornecedor->Cells[0][this->StringGridFornecedor->Row] ).c_str( ),
  	                						 "Fornecedores", MB_YESNO | MB_ICONWARNING ) == ID_YES ) {
      try {
        Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

		    try {
          if( !DataModuleQuery->consigo_BD->Connected ) {
            DataModuleQuery->consigo_BD->Open( );
          }
  		    DataModuleQuery->consigo_BD->StartTransaction( );
          Query->SQL->Add( "BEGIN TRANSACTION" );
          Query->SQL->Add( "DELETE FROM Fornecedores" );
          Query->SQL->Add( "WHERE  Fornecedores.CGC = '" + this->StringGridFornecedor->Cells[8][this->StringGridFornecedor->Row] + "'" );
          Query->SQL->Add( "COMMIT TRANSACTION" );
	  	  	Query->ExecSQL( );
	  	    DataModuleQuery->consigo_BD->Commit( );

          for( i = this->StringGridFornecedor->Row; i < this->StringGridFornecedor->RowCount; i++ ) {
            for( j = 0; j <= 7; j++ ) {
              this->StringGridFornecedor->Cells[j][i] = this->StringGridFornecedor->Cells[j][i+1];
            }
          }
          if( this->StringGridFornecedor->RowCount != 2 ) {
            this->StringGridFornecedor->RowCount --;
          }
          EditNomeFornecedor->Clear( );
	    	}
	  	  catch( Exception &e ) {
  	    	if( DataModuleQuery->consigo_BD->InTransaction ) {
	  	  	  DataModuleQuery->consigo_BD->Rollback( );
      	  }
      		Application->MessageBox( e.Message.c_str( ), "Fornecedores", MB_OK | MB_ICONERROR );
		    }
      }
      __finally {
        delete Query;
      }
  	}
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditNomeFornecedorKeyPress( TObject *Sender, char &Key ) {

  TConsigoQuery *Query;
	int i;

	if( Key == 13 ) {
  	if( Trim( EditNomeFornecedor->Text ).Length( ) > 2 )  {
      try {
        Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      	try {
        	for( i = 1; i < StringGridFornecedor->RowCount; i++ ) {
     	      StringGridFornecedor->Rows[i]->Clear( );
      		}
        	StringGridFornecedor->RowCount = 2;

          Query->SQL->Add( "SELECT *" );
          Query->SQL->Add( "FROM Fornecedores" );
          Query->SQL->Add( "WHERE Fornecedores.Nome LIKE '%" +
            StringReplace( Trim( EditNomeFornecedor->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
          Query->SQL->Add( "ORDER BY Nome ASC" );
          Query->Prepare( );
          Query->Open( );
    	    if( Query->IsEmpty( ) ) {
          	throw Exception( "Fornecedor Inexistente!\r\rVerifique os Dados Digitados." );
        	}
	        else {
            Query->First( );
    	      MemoObservacaoFornecedor->Text = Query->FieldByName( "Observacao" )->Text;
    	      while( !Query->Eof ) {
              if( !StringGridFornecedor->Cells[0][1].IsEmpty( ) ) {
        	      StringGridFornecedor->RowCount++;
              }
              StringGridFornecedor->Cells[0][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Nome" )->AsString;
           	  StringGridFornecedor->Cells[1][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Endereco" )->AsString;
             	StringGridFornecedor->Cells[2][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Bairro" )->AsString;
	            StringGridFornecedor->Cells[3][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Cidade" )->AsString;
  	          StringGridFornecedor->Cells[4][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Estado" )->AsString;
    	        StringGridFornecedor->Cells[5][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Cep" )->AsString;
        	    StringGridFornecedor->Cells[6][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Telefone" )->AsString;
              StringGridFornecedor->Cells[7][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Telefone_Fax" )->AsString;
           	  StringGridFornecedor->Cells[8][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "CGC" )->AsString;
             	StringGridFornecedor->Cells[9][StringGridFornecedor->RowCount - 1] = Query->FieldByName( "Inscricao" )->AsString;
	            Query->Next( );
      	    }
          }
        }
        catch( Exception &e ) {
		  	 	for( i = 1; i < StringGridFornecedor->RowCount; i++ ) {
     	  		StringGridFornecedor->Rows[i]->Clear( );
				  }
          StringGridFornecedor->RowCount = 2;
          Application->MessageBox( e.Message.c_str( ), "Fornecedores", MB_OK | MB_ICONERROR );
        }
      }
      __finally {
        Query->Close( );
        delete Query;
      }
    }
	}
}
//---------------------------------------------------------------------------

