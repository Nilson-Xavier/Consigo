//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "CadastroCliente.h"
#include "Main.h"
#include "Dmod1.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormInsercaoCliente *FormInsercaoCliente;
//---------------------------------------------------------------------------
__fastcall TFormInsercaoCliente::TFormInsercaoCliente( TComponent* Owner )
	: TForm( Owner ) {

}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::BitBtnVoltarClick( TObject *Sender ) {

  this->Close( );
  FormInsercaoCliente = NULL;
  delete FormInsercaoCliente;
  FormPrincipal->PageControl1->ActivePage = FormPrincipal->TabSheetClientes;
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::MenuItemSairClick( TObject *Sender ) {

	this->BitBtnVoltarClick( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::BitBtnInserirClienteClick( TObject *Sender ) {

  TConsigoQuery *Query;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    BitBtnInserirCliente->Enabled = false;
    BitBtnVoltar->Enabled = false;

    try {
    	if ( ( Trim( EditNome->Text ).IsEmpty( ) ) || ( Trim( EditRgCnpj->Text ).IsEmpty( ) ) ||
      		 ( Trim( ComboBoxEERG->Text ).IsEmpty( ) ) || ( Trim( EditTelefone->Text ).Length( ) < 12 ) ) {
		    throw Exception( "O Cliente ao ser inserido DEVE ter NOME, RG, EERG e Telefone!" );
    	}
	    else {
		    if ( Application->MessageBox( "Você Digitou Todos os Campos CORRETAMENTE?",
    	    	             							"Cadastro de Clientes",
      	    	         						    MB_YESNO | MB_ICONQUESTION ) == ID_YES ) {
            if( !DataModuleQuery->consigo_BD->Connected ) {
              DataModuleQuery->consigo_BD->Open( );
            }
            Query->SQL->Add( "BEGIN TRANSACTION" );
            Query->SQL->Add( "INSERT INTO Clientes ( Nome, Endereco, Bairro, Cidade, Estado," );
            Query->SQL->Add( "Telefone_Comercial, Telefone_Fax, RG, EERG, CPF," );
            Query->SQL->Add( "Cep, Telefone, Inscricao_estadual, Observacao, email )" );
            Query->SQL->Add( "VALUES ( '" + LowerCase( Trim( EditNome->Text ) ) + "'," );
            Query->SQL->Add( "'" + LowerCase( Trim( EditEndereco->Text ) ) + "'," );
            Query->SQL->Add( "'" + LowerCase( Trim( EditBairro->Text ) ) + "'," );
            Query->SQL->Add( "'" + LowerCase( Trim( EditCidade->Text ) ) + "'," );
            Query->SQL->Add( "'" + UpperCase( Trim( ComboBoxEstado->Text ) ) + "'," );
            Query->SQL->Add( "'" + Trim( EditTelefoneComercial->Text ) + "'," );
            Query->SQL->Add( "'" + Trim( EditTelefoneFax->Text ) + "'," );
            Query->SQL->Add( "'" + UpperCase( Trim( EditRgCnpj->Text ) ) + "'," );
            Query->SQL->Add( "'" + UpperCase( Trim( ComboBoxEERG->Text ) ) + "'," );
            Query->SQL->Add( "'" + Trim( EditCpf->Text ) + "'," );
            Query->SQL->Add( "'" + Trim( EditCep->Text ) + "'," );
            Query->SQL->Add( "'" + Trim( EditTelefone->Text ) + "'," );
            Query->SQL->Add( "'" + Trim( EditInscricaoEstadual->Text ) + "'," );
            Query->SQL->Add( "'" + LowerCase( Trim( MemoObservacaoCliente->Text ) ) + "'," );
            Query->SQL->Add( "'" + LowerCase( Trim( EditEmail->Text ) ) + "')" );
            Query->SQL->Add( "COMMIT TRANSACTION" );
            Query->Prepare( );
            Query->ExecSQL( );
    	      Application->MessageBox( "O Cliente foi Inserido com Sucesso !",
    			  										 		 "Cadastro de Clientes", MB_OK | MB_ICONINFORMATION );

	    	    EditNome->Clear( );
      	  	EditEndereco->Clear( );
  	    	  EditBairro->Clear( );
  	  	    EditCidade->Clear( );
        		ComboBoxEstado->Clear( );
  	      	EditCep->Clear( );
	  	      EditTelefone->Clear( );
        		EditTelefoneComercial->Clear( );
        		EditTelefoneFax->Clear( );
	    	    ComboBoxEERG->Clear( );
      		  EditCpf->Clear( );
        		EditInscricaoEstadual->Clear( );
            EditEmail->Clear( );
            MemoObservacaoCliente->Clear( );
        }
      }
    }
    catch( Exception &e ) {
      if( DataModuleQuery->consigo_BD->InTransaction ) {
        DataModuleQuery->consigo_BD->Rollback( );
      }
      Application->MessageBox( e.Message.c_str( ), "Cadastro de Clientes", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete Query;
    BitBtnInserirCliente->Enabled = true;
    BitBtnVoltar->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditNomeKeyPress(TObject *Sender, char &Key ) {

  switch( Key ) {
    case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
    case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
    case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
    case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
    case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
    case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
    case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
    case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case ',': Key = NULL; break; case '_': Key = NULL; break;
  }
  if( ( Key == ' ' ) && ( ( EditNome->Text.IsEmpty( ) ) || ( EditNome->Text[EditNome->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditEndereco->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditEnderecoKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
    case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
    case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
    case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
    case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
    case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
    case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
    case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case '&': Key = NULL; break; case '_': Key = NULL; break;
  }
  if( ( Key == ' ' ) && ( ( EditEndereco->Text.IsEmpty( ) ) || ( EditEndereco->Text[EditEndereco->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditBairro->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditBairroKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
    case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
    case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
    case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
    case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
    case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
    case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
    case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case ',': Key = NULL; break; case '&': Key = NULL; break;
    case '_': Key = NULL; break; case '/': Key = NULL; break;
  }
  if( ( Key == ' ' ) && ( ( EditBairro->Text.IsEmpty( ) ) || ( EditBairro->Text[EditBairro->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ){
    EditCidade->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditCidadeKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
    case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
    case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
    case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
    case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
    case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
    case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
    case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case ',': Key = NULL; break; case '&': Key = NULL; break;
    case '_': Key = NULL; break; case '/': Key = NULL; break;
  }
  if( ( Key == ' ' ) && ( ( EditCidade->Text.IsEmpty( ) ) || ( EditCidade->Text[EditCidade->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    ComboBoxEstado->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::ComboBoxEstadoKeyDown( TObject *Sender, WORD &Key, TShiftState Shift ) {

  if( Key == VK_RETURN ) {
    EditCep->SetFocus( );
  }
  else if( ( ( Key == VK_SPACE ) || ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
           ( !ComboBoxEstado->DroppedDown ) ) {
    ComboBoxEstado->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditCepKeyPress(TObject *Sender, char &Key ) {

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
void __fastcall TFormInsercaoCliente::EditTelefoneKeyPress(TObject *Sender, char &Key ) {

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
    EditTelefoneComercial->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditTelefoneComercialKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditTelefoneComercial->Text.Length( ) <= 12 ) ) {
    if( this->EditTelefoneComercial->Text.IsEmpty( ) ) {
      this->EditTelefoneComercial->Text = this->EditTelefoneComercial->Text.Insert( "(", this->EditTelefoneComercial->Text.Length( ) - 1 );
      this->EditTelefoneComercial->SelStart = this->EditTelefoneComercial->Text.Length( );
    }
    if( this->EditTelefoneComercial->Text.Length( ) >= 3 ) {
      this->EditTelefoneComercial->Text = this->EditTelefoneComercial->Text.Delete( this->EditTelefoneComercial->Text.Pos( ")" ), 1 );
      this->EditTelefoneComercial->Text = this->EditTelefoneComercial->Text.Insert( ")", 4 );
      this->EditTelefoneComercial->SelStart = this->EditTelefoneComercial->Text.Length( );
    }
    if( this->EditTelefoneComercial->Text.Length( ) >= 7 ) {
      this->EditTelefoneComercial->Text = this->EditTelefoneComercial->Text.Delete( this->EditTelefoneComercial->Text.Pos( "-" ), 1 );
      if( this->EditTelefoneComercial->Text.Length( ) < 11 ) {
        this->EditTelefoneComercial->Text = this->EditTelefoneComercial->Text.Insert( "-", 8 );
      }
      else {
        this->EditTelefoneComercial->Text = this->EditTelefoneComercial->Text.Insert( "-", 9 );
      }
      this->EditTelefoneComercial->SelStart = this->EditTelefoneComercial->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditTelefoneFax->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditTelefoneFaxKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditTelefoneFax->Text.Length( ) <= 12 ) ) {
    if( this->EditTelefoneFax->Text.IsEmpty( ) ) {
      this->EditTelefoneFax->Text = this->EditTelefoneFax->Text.Insert( "(", this->EditTelefoneFax->Text.Length( ) - 1 );
      this->EditTelefoneFax->SelStart = this->EditTelefoneFax->Text.Length( );
    }
    if( this->EditTelefoneFax->Text.Length( ) >= 3 ) {
      this->EditTelefoneFax->Text = this->EditTelefoneFax->Text.Delete( this->EditTelefoneFax->Text.Pos( ")" ), 1 );
      this->EditTelefoneFax->Text = this->EditTelefoneFax->Text.Insert( ")", 4 );
      this->EditTelefoneFax->SelStart = this->EditTelefoneFax->Text.Length( );
    }
    if( this->EditTelefoneFax->Text.Length( ) >= 7 ) {
      this->EditTelefoneFax->Text = this->EditTelefoneFax->Text.Delete( this->EditTelefoneFax->Text.Pos( "-" ), 1 );
      if( this->EditTelefoneFax->Text.Length( ) < 11 ) {
        this->EditTelefoneFax->Text = this->EditTelefoneFax->Text.Insert( "-", 8 );
      }
      else {
        this->EditTelefoneFax->Text = this->EditTelefoneFax->Text.Insert( "-", 9 );
      }
      this->EditTelefoneFax->SelStart = this->EditTelefoneFax->Text.Length( );
    }
  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditRgCnpj->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditRgCnpjKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
    case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
    case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
    case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
    case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
    case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
    case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
    case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case ',': Key = NULL; break; case '.': Key = NULL; break;
    case '&': Key = NULL; break; case '-': Key = NULL; break; case '_': Key = NULL; break;
    case '/': Key = NULL; break;
  }
  if( ( ( EditRgCnpj->Text.IsEmpty( ) ) && ( Key == '0' ) ) || Key == ' ' ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    ComboBoxEERG->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::ComboBoxEERGKeyDown(TObject *Sender, WORD &Key, TShiftState Shift ) {

  if( Key == VK_RETURN ) {
    EditCpf->SetFocus( );
  }
  else if( ( ( Key == VK_SPACE ) || ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
           ( !ComboBoxEERG->DroppedDown ) ) {
    ComboBoxEERG->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditCpfKeyPress( TObject *Sender, char &Key ) {

  if( ( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditCpf->Text.Length( ) <= 10 ) ) || ( Key == '\b' ) || ( Key == '\r') ) {

  }
  else {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditInscricaoEstadual->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditInscricaoEstadualKeyPress( TObject *Sender, char &Key ) {

  if( ( AnsiCompareStr( Key, "0" ) >= 0 ) && ( AnsiCompareStr( Key, "9" ) <= 0 ) &&
      ( this->EditInscricaoEstadual->Text.Length( ) <= 11 ) ) {

  }
  else if( ( Key != '\b' ) && ( Key != '\r') ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    EditEmail->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::EditEmailKeyPress( TObject *Sender, char &Key ) {

  if( Key == ' ' ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    MemoObservacaoCliente->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoCliente::MemoObservacaoClienteKeyPress( TObject *Sender, char &Key ) {

  switch( Key ) {
    case '´': Key = NULL; break; case '`': Key = NULL; break; case '^': Key = NULL; break;
    case '~': Key = NULL; break; case 'ã': Key = NULL; break; case 'á': Key = NULL; break;
    case 'à': Key = NULL; break; case 'â': Key = NULL; break; case 'ä': Key = NULL; break;
    case 'ê': Key = NULL; break; case 'é': Key = NULL; break; case 'è': Key = NULL; break;
    case 'ë': Key = NULL; break; case 'í': Key = NULL; break; case 'î': Key = NULL; break;
    case 'ì': Key = NULL; break; case 'ï': Key = NULL; break; case 'õ': Key = NULL; break;
    case 'ô': Key = NULL; break; case 'ó': Key = NULL; break; case 'ò': Key = NULL; break;
    case 'ö': Key = NULL; break; case 'ú': Key = NULL; break; case 'ù': Key = NULL; break;
    case 'û': Key = NULL; break; case 'ü': Key = NULL; break; case 'ç': Key = NULL; break;
    case '!': Key = NULL; break; case '@': Key = NULL; break; case '#': Key = NULL; break;
    case '$': Key = NULL; break; case '%': Key = NULL; break; case '*': Key = NULL; break;
    case '+': Key = NULL; break; case '|': Key = NULL; break; case '<': Key = NULL; break;
    case '>': Key = NULL; break; case ';': Key = NULL; break; case ':': Key = NULL; break;
    case '?': Key = NULL; break; case '"': Key = NULL; break; case '{': Key = NULL; break;
    case '}': Key = NULL; break; case '[': Key = NULL; break; case']': Key = NULL; break;
    case '=': Key = NULL; break; case '&': Key = NULL; break; case '_': Key = NULL; break;
  }
  if( ( Key == 13 ) && ( MemoObservacaoCliente->Text.IsEmpty( ) ) ) {
    Key = NULL;
  }
  else if( ( Key == 13 ) && ( MemoObservacaoCliente->Lines->Strings[MemoObservacaoCliente->Lines->Count - 1].IsEmpty( ) ) ) {
    Key = NULL;
  }
  if( ( Key == ' ' ) && ( ( MemoObservacaoCliente->Lines->Text.IsEmpty( ) )
      || ( MemoObservacaoCliente->Lines->Strings[MemoObservacaoCliente->Lines->Count - 1].SubString( MemoObservacaoCliente->Lines->Strings[MemoObservacaoCliente->Lines->Count - 1].Length( ), 1 ) == " " ) ) ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------

