//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "CadastroFornecedor.h"
#include "Gerencia.h"
#include "DMod1.h"
#include "DMod2.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormInserirFornecedor *FormInserirFornecedor;
//---------------------------------------------------------------------------
__fastcall TFormInserirFornecedor::TFormInserirFornecedor( TComponent* Owner )
  : TForm( Owner ) {

}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::SairESC1Click( TObject *Sender ) {

  this->BitBtnVoltarClick( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::BitBtnVoltarClick( TObject *Sender ) {

  this->Close( );
  FormInserirFornecedor = NULL;
  delete FormInserirFornecedor;
  FormGerencia->PageControl1->ActivePage = FormGerencia->TabSheetFornecedores;
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::BitBtnInserirFornecedorClick( TObject *Sender ) {

  TConsigoQuery *Query;

	if( ( Trim( EditNome->Text ).IsEmpty( ) ) || ( Trim( EditCnpj->Text ).Length( ) < 14 ) ||
  		( Trim( EditInscricaoEstadual->Text ).Length( ) < 12 ) || ( Trim( EditEndereco->Text ).IsEmpty( ) ) ||
      ( Trim( EditCidade->Text ).IsEmpty( ) ) || ( Trim( ComboBoxEstado->Text ).IsEmpty( ) ) ||
      ( EditCep->Text.Length( ) < 9 ) || EditTelefone->Text.Length( ) < 12 ) {
  	Application->MessageBox( "Faltam Dados para a Inser��o do Fornecedor!!!",
    												 "Inser��o de Fornecedores", MB_OK | MB_ICONERROR );
  }
  else {
		if ( MessageBox( Handle, "Voc� Digitou Todos os Campos CORRETAMENTE?",
  	                 "Inser��o de Fornecedores", MB_YESNO | MB_ICONQUESTION ) == ID_YES ) {
      try {
        Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
        BitBtnInserirFornecedor->Enabled = false;
        BitBtnVoltar->Enabled = false;

			  try {
          if( !DataModuleQuery->consigo_BD->Connected ) {
            DataModuleQuery->consigo_BD->Open( );
          }
          Query->SQL->Add( "BEGIN TRANSACTION" );
          Query->SQL->Add( "INSERT INTO Fornecedores ( Nome, CGC, Inscricao," );
          Query->SQL->Add( " Endereco, Bairro,Cidade, Estado, Cep, Telefone," );
          Query->SQL->Add( " Telefone_Fax, Observacao )" );
          Query->SQL->Add( "VALUES ( '" + LowerCase( Trim( EditNome->Text ) ) + "','" + Trim( EditCnpj->Text ) + "'," );
          Query->SQL->Add( "'" + Trim( EditInscricaoEstadual->Text ) + "','" + LowerCase( Trim( EditEndereco->Text ) ) + "'," );
          Query->SQL->Add( "'" + LowerCase( Trim( EditBairro->Text ) ) + "','" + LowerCase( Trim( EditCidade->Text ) ) + "'," );
          Query->SQL->Add( "'" + ComboBoxEstado->Text + "','" + EditCep->Text + "'," );
          Query->SQL->Add( "'" + Trim( EditTelefone->Text ) + "','" + Trim( EditFax->Text ) + "'," );
          Query->SQL->Add( "'" + LowerCase( Trim( MemoObservacao->Text ) ) + "' )" );
          Query->SQL->Add( "COMMIT TRANSACTION" );
          Query->Prepare( );
		  	  Query->ExecSQL( );
			  }
			  catch( Exception &e ) {
        	if( DataModuleQuery->consigo_BD->InTransaction ) {
	    			DataModuleQuery->consigo_BD->Rollback( );
          }
		  	  Application->MessageBox( e.Message.c_str( ), "Inser��o de Fornecedores", MB_OK | MB_ICONERROR );
			  }

			  EditNome->Clear( );
        EditCnpj->Clear( );
        EditInscricaoEstadual->Clear( );
        EditEndereco->Clear( );
        EditBairro->Clear( );
        EditCidade->Clear( );
        EditCep->Clear( );
        EditTelefone->Clear( );
        EditFax->Clear( );
        MemoObservacao->Clear( );

        Application->MessageBox( "O Fornecedor Foi Inserido com Sucesso!",
					    	                 "Inser��o de Fornecedores", MB_OK | MB_ICONINFORMATION );
      }
      __finally {
        delete Query;
        BitBtnInserirFornecedor->Enabled = true;
        BitBtnVoltar->Enabled = true;
      }
    }
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditNomeKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '�': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case ',': Key = NULL; break; case '_': Key = NULL; break;
  }
	if( Key == 13 ) {
  	EditCnpj->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditCnpjKeyPress( TObject *Sender, char &Key ) {

  if( !( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
       ( this->EditCnpj->Text.Length( ) <= 13 ) || ( Key == '\b' ) || ( Key == '\r') ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditInscricaoEstadual->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditInscricaoEstadualKeyPress( TObject *Sender, char &Key ) {

  if( !( ( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
       ( this->EditInscricaoEstadual->Text.Length( ) <= 11 ) ) || ( Key == '\b' ) ||
       ( Key == '\r') ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditEndereco->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditEnderecoKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '�': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case '&': Key = NULL; break; case '_': Key = NULL; break;
  }
  if( Key == 13 ) {
    EditBairro->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditBairroKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '�': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case ',': Key = NULL; break; case '&': Key = NULL; break;
    case '_': Key = NULL; break; case '/': Key = NULL; break;
  }
  if( Key == 13 ) {
    EditCidade->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditCidadeKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '�': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '�': Key = NULL; break; case '�': Key = NULL; break; case '�': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case ',': Key = NULL; break; case '&': Key = NULL; break;
    case '_': Key = NULL; break; case '/': Key = NULL; break;
  }
  if( Key == 13 ) {
    ComboBoxEstado->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::ComboBoxEstadoKeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ) {
    ComboBoxEstado->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditCepKeyPress(TObject *Sender, char &Key ) {

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
    EditTelefone->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditTelefoneKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditTelefone->Text.Length( ) <= 12 ) ) {
    if( this->EditTelefone->Text.IsEmpty( ) ) {
      this->EditTelefone->Text = this->EditTelefone->Text.Insert( "(", this->EditTelefone->Text.Length( ) - 1 );
      this->EditTelefone->SelStart = this->EditTelefone->Text.Length( );
    }
    if( this->EditTelefone->Text.Length( ) >= 3 ) {
      this->EditTelefone->Text = this->EditTelefone->Text.Delete( this->EditTelefone->Text.Pos( ")" ), 1 );
      this->EditTelefone->Text = this->EditTelefone->Text.Insert( ")", 4 );
      this->EditTelefone->SelStart = this->EditTelefone->Text.Length( );
    }
    if( this->EditTelefone->Text.Length( ) >= 7 ) {
      this->EditTelefone->Text = this->EditTelefone->Text.Delete( this->EditTelefone->Text.Pos( "-" ), 1 );
      if( this->EditTelefone->Text.Length( ) < 11 ) {
        this->EditTelefone->Text = this->EditTelefone->Text.Insert( "-", 8 );
      }
      else {
        this->EditTelefone->Text = this->EditTelefone->Text.Insert( "-", 9 );
      }
      this->EditTelefone->SelStart = this->EditTelefone->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditFax->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInserirFornecedor::EditFaxKeyPress(TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditFax->Text.Length( ) <= 12 ) ) {
    if( this->EditFax->Text.IsEmpty( ) ) {
      this->EditFax->Text = this->EditFax->Text.Insert( "(", this->EditFax->Text.Length( ) - 1 );
      this->EditFax->SelStart = this->EditFax->Text.Length( );
    }
    if( this->EditFax->Text.Length( ) >= 3 ) {
      this->EditFax->Text = this->EditFax->Text.Delete( this->EditFax->Text.Pos( ")" ), 1 );
      this->EditFax->Text = this->EditFax->Text.Insert( ")", 4 );
      this->EditFax->SelStart = this->EditFax->Text.Length( );
    }
    if( this->EditFax->Text.Length( ) >= 7 ) {
      this->EditFax->Text = this->EditFax->Text.Delete( this->EditFax->Text.Pos( "-" ), 1 );
      if( this->EditFax->Text.Length( ) < 11 ) {
        this->EditFax->Text = this->EditFax->Text.Insert( "-", 8 );
      }
      else {
        this->EditFax->Text = this->EditFax->Text.Insert( "-", 9 );
      }
      this->EditFax->SelStart = this->EditFax->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    MemoObservacao->SetFocus( );
  }
}
//---------------------------------------------------------------------------

