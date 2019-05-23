//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GerenciaConserto.h"
#include "Gerencia.h"
#include "Dmod1.h"
#include <conio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemConsertoClick( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetConserto;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::EditOrdemServicoKeyPress(TObject *Sender, char &Key ) {

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
void __fastcall TFormGerencia::EditConsertoNumeroSerieKeyPress( TObject *Sender, char &Key ) {

  if( ( Key == ' ' ) && ( ( EditConsertoNumeroSerie->Text.IsEmpty( ) ) ||
      ( EditConsertoNumeroSerie->Text[EditConsertoNumeroSerie->Text.Length( )] == ' ' ) ) ) {
    Key = NULL;
  }
  if( Key == 13 ) {
    this->ConsultarConserto( NULL, &(EditConsertoNumeroSerie->Text), NULL, NULL );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ComboBoxConsertoClienteKeyDown( TObject *Sender,
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
            FormGerencia->ComboBoxConsertoCliente->Items->Append( Query->FieldByName( "Nome" )->AsString );
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
void __fastcall TFormGerencia::EditConsertoDataKeyPress(TObject *Sender, char &Key ) {

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
void __fastcall TFormGerencia::StringGridConsertoSelectCell( TObject *Sender,
  int ACol, int ARow, bool &CanSelect) {

  if( MemoDefeito[ARow - 1] != NULL ) {
    if( !MemoDefeito[ARow - 1]->Text.IsEmpty( ) ) {
      MemoConsertoDefeito->Text = MemoDefeito[ARow - 1]->Text;
    }
  }
  if( ( ACol == 1 ) || ( ACol == 2 ) || ( ACol == 6 ) || ( ACol == 7 ) ||
      ( ACol == 8 ) ) {
    this->StringGridConserto->Options << goEditing;
  }
  else {
    this->StringGridConserto->Options >> goEditing;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridConsertoKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  int i, j;

  if( ( Key == VK_DELETE ) && ( !StringGridConserto->EditorMode ) ) {
    if( Application->MessageBox( "Deseja Realmente Apagar Este Item ?", "Conserto", MB_YESNOCANCEL | MB_ICONQUESTION ) == 6 ) {
      try {
        Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

        try {
          Query->SQL->Add( "BEGIN TRANSACTION" );
          Query->SQL->Add( "DELETE FROM CONSERTO" );
          Query->SQL->Add( "  WHERE Ordem_Servico =" + StringGridConserto->Cells[0][StringGridConserto->Row] );
          Query->SQL->Add( "  AND   Codigo IN ( SELECT Codigo" );
          Query->SQL->Add( "                    FROM Produtos" );
          Query->SQL->Add( "                    WHERE Marca = '" + StringGridConserto->Cells[4][StringGridConserto->Row] + "'" );
          Query->SQL->Add( "                    AND Nome = '" + StringGridConserto->Cells[5][StringGridConserto->Row] + "' )" );
          Query->SQL->Add( "  AND   Numero_Serie = '" + StringGridConserto->Cells[6][StringGridConserto->Row] + "'" );
          Query->SQL->Add( "COMMIT TRANSACTION" );
          Query->Prepare( );
          Query->ExecSQL( );

          for( i = StringGridConserto->Row + 1; i <= StringGridConserto->RowCount; i++ ) {
            for( j = 0; j <= 9; j++ ) {
              StringGridConserto->Cells[j][i-1] = StringGridConserto->Cells[j][i];
              if( i == 2 ) {
                MemoDefeito[i-2]->Text = "";
              }
              else {
                MemoDefeito[i-2]->Text = MemoDefeito[i-1]->Text;
              }
            }
          }
          if( StringGridConserto->RowCount != 2 ) {
            StringGridConserto->RowCount --;
            MemoConsertoDefeito->Text = MemoDefeito[StringGridConserto->Row - 1]->Text;
          }
          else {
            MemoConsertoDefeito->Clear( );
          }
        }
        catch( Exception &e ) {
          Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
        }
      }
      __finally {
        delete Query;
      }
    }
  }
  if( ( Key == VK_RETURN ) && ( StringGridConserto->Col == 3 ) ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

      try {
        Query->SQL->Add( "SELECT Status" );
        Query->SQL->Add( "  FROM Conserto_Status" );
        Query->Open( );
        if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            ListBoxConsertoGrid->Items->Append( Query->FieldByName( "Status" )->AsString );
            Query->Next( );
          }
          ListBoxConsertoGrid->OnKeyPress = ListBoxConsertoStatusKeyPress;
          ListBoxConsertoGrid->SetBounds( StringGridConserto->Left + 500, StringGridConserto->Top + 100, 150, 68 );
          ListBoxConsertoGrid->Show( );
          ListBoxConsertoGrid->BringToFront( );
          ListBoxConsertoGrid->SetFocus( );
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
  if( ( Key == VK_RETURN ) && ( StringGridConserto->Col == 9 ) ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

      try {
        Query->SQL->Add( "SELECT Nome" );
        Query->SQL->Add( "  FROM Vendedores" );
        Query->Open( );
        if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            ListBoxConsertoGrid->Items->Append( Query->FieldByName( "Nome" )->AsString );
            Query->Next( );
          }
          ListBoxConsertoGrid->OnKeyPress = ListBoxConsertoVendedorKeyPress;
          ListBoxConsertoGrid->SetBounds( StringGridConserto->Left + 500, StringGridConserto->Top + 100, 190, 68 );
          ListBoxConsertoGrid->Show( );
          ListBoxConsertoGrid->BringToFront( );
          ListBoxConsertoGrid->SetFocus( );
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( StringGridConserto->Col == 8 ) &&
      ( StringGridConserto->Cells[8][StringGridConserto->Row].Length( ) > 2 ) &&
      ( StringGridConserto->EditorMode ) ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

      try {
        Query->SQL->Add( "SELECT Nome" );
        Query->SQL->Add( "  FROM Clientes" );
        Query->SQL->Add( "  WHERE Nome LIKE '%" + StringReplace( StringGridConserto->Cells[8][StringGridConserto->Row], " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "  ORDER BY NOME ASC" );
        Query->Open( );
        if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            ListBoxConsertoGrid->Items->Append( Query->FieldByName( "Nome" )->AsString );
            Query->Next( );
          }
          ListBoxConsertoGrid->OnKeyPress = ListBoxConsertoClienteKeyPress;
          ListBoxConsertoGrid->SetBounds( StringGridConserto->Left + 500, StringGridConserto->Top + 100, 300, 68 );
          ListBoxConsertoGrid->Show( );
          ListBoxConsertoGrid->BringToFront( );
          ListBoxConsertoGrid->SetFocus( );
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
  if( ( ( Key == VK_RETURN ) || ( Key == VK_UP ) || ( Key == VK_DOWN ) ) &&
      ( StringGridConserto->EditorMode ) ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      Data = new TDateTime( );

      try {
        Query->SQL->Add( "UPDATE Conserto" );
        *Data = StringGridConserto->Cells[1][StringGridConserto->Row] + " " + Time( ).FormatString( "hh:mm:ss" );
        Query->SQL->Add( "SET Data = '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'," );
        *Data = StringGridConserto->Cells[2][StringGridConserto->Row] + " " + Time( ).FormatString( "hh:mm:ss" );
        Query->SQL->Add( "    Data_Entrega = '" + Data->FormatString( "yyyy/mm/dd hh:mm:ss" ) + "'," );
        Query->SQL->Add( "    Numero_Serie = '" + StringGridConserto->Cells[6][StringGridConserto->Row] + "'," );
        Query->SQL->Add( "    Preco = " + StringReplace( StringReplace( StringGridConserto->Cells[7][StringGridConserto->Row], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ), ",", ".", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) );
        Query->SQL->Add( "  FROM Conserto, Produtos" );
        Query->SQL->Add( "  WHERE Ordem_Servico = " + StringGridConserto->Cells[0][StringGridConserto->Row] );
        Query->SQL->Add( "  AND   Produtos.Marca = '" + StringGridConserto->Cells[4][StringGridConserto->Row] + "'" );
        Query->SQL->Add( "  AND Produtos.Nome = '" + StringGridConserto->Cells[5][StringGridConserto->Row] + "'" );
        Query->SQL->Add( "  AND Produtos.Codigo = Conserto.Codigo" );
        Query->Prepare( );
        Query->ExecSQL( );

        StringGridConserto->EditorMode = false;
        StringGridConserto->Options >> goEditing;
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Data;
      delete Query;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::StringGridConsertoGetEditMask( TObject *Sender,
  int ACol, int ARow, AnsiString &Value ) {

  if( ( ACol == 2 ) || ( ACol == 1 ) ) {
    Value = "!00/00/00;1; ";
  }
  if( ACol == 7 ) {
    Value = "!99990,00;1; ";
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ListBoxConsertoStatusKeyPress( TObject* Sender, char &Key ) {

  TConsigoQuery *Query;

  if( Key == 13 ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

      try {
        StringGridConserto->Options << goEditing;
        ListBoxConsertoGrid = (TListBox*)Sender;
        StringGridConserto->Cells[3][StringGridConserto->Row] = ListBoxConsertoGrid->Items->Strings[ListBoxConsertoGrid->ItemIndex];
        StringGridConserto->Options >> goEditing;
        ListBoxConsertoGrid->Items->Clear( );
        ListBoxConsertoGrid->SendToBack( );
        GroupBoxOrdemDeServico->SetFocus( );
        StringGridConserto->SetFocus( );
        Query->SQL->Add( "UPDATE Conserto" );
        Query->SQL->Add( "SET Status = Conserto_Status.Codigo" );
        Query->SQL->Add( "  FROM Conserto, Conserto_Status" );
        Query->SQL->Add( "  WHERE Conserto_Status.Status = '" + StringGridConserto->Cells[3][StringGridConserto->Row] + "'" );
        Query->SQL->Add( "  AND   Conserto.Ordem_Servico = " + StringGridConserto->Cells[0][StringGridConserto->Row] );
        Query->SQL->Add( "  AND   Conserto.Numero_Serie = '" + StringGridConserto->Cells[6][StringGridConserto->Row] + "'" );
        Query->Prepare( );
        Query->ExecSQL( );
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
  if( Key == '\x1B' ) {
    ListBoxConsertoGrid->Items->Clear( );
    ListBoxConsertoGrid->SendToBack( );
    GroupBoxOrdemDeServico->SetFocus( );
    StringGridConserto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ListBoxConsertoVendedorKeyPress( TObject* Sender, char &Key ) {

  TConsigoQuery *Query;

  if( Key == 13 ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

     try {
        StringGridConserto->Options << goEditing;
        ListBoxConsertoGrid = (TListBox*)Sender;
        StringGridConserto->Cells[9][StringGridConserto->Row] = ListBoxConsertoGrid->Items->Strings[ListBoxConsertoGrid->ItemIndex];
        StringGridConserto->Options >> goEditing;
        ListBoxConsertoGrid->Items->Clear( );
        ListBoxConsertoGrid->SendToBack( );
        GroupBoxOrdemDeServico->SetFocus( );
        StringGridConserto->SetFocus( );
        Query->SQL->Add( "UPDATE Conserto" );
        Query->SQL->Add( "SET RG_Vendedor = Vendedores.RG, EERG_Vendedor = Vendedores.EERG" );
        Query->SQL->Add( "  FROM Conserto, Vendedores" );
        Query->SQL->Add( "  WHERE Vendedores.Nome = '" + StringGridConserto->Cells[9][StringGridConserto->Row] + "'" );
        Query->SQL->Add( "  AND   Conserto.Ordem_Servico = " + StringGridConserto->Cells[0][StringGridConserto->Row] );
        Query->SQL->Add( "  AND   Conserto.Numero_Serie = '" + StringGridConserto->Cells[6][StringGridConserto->Row] + "'" );
        Query->Prepare( );
        Query->ExecSQL( );
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
  if( Key == '\x1B' ) {
    ListBoxConsertoGrid->Items->Clear( );
    ListBoxConsertoGrid->SendToBack( );
    GroupBoxOrdemDeServico->SetFocus( );
    StringGridConserto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ListBoxConsertoClienteKeyPress( TObject* Sender, char &Key ) {

  TConsigoQuery *Query;

  if( Key == 13 ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

     try {
        StringGridConserto->Options << goEditing;
        ListBoxConsertoGrid = (TListBox*)Sender;
        StringGridConserto->Cells[8][StringGridConserto->Row] = ListBoxConsertoGrid->Items->Strings[ListBoxConsertoGrid->ItemIndex];
        StringGridConserto->Options >> goEditing;
        ListBoxConsertoGrid->Items->Clear( );
        ListBoxConsertoGrid->SendToBack( );
        GroupBoxOrdemDeServico->SetFocus( );
        StringGridConserto->SetFocus( );
        Query->SQL->Add( "UPDATE Conserto" );
        Query->SQL->Add( "SET RG_Cliente = Clientes.RG, EERG_Cliente = Clientes.EERG" );
        Query->SQL->Add( "  FROM Conserto, Clientes" );
        Query->SQL->Add( "  WHERE Clientes.Nome = '" + StringGridConserto->Cells[8][StringGridConserto->Row] + "'" );
        Query->SQL->Add( "  AND   Conserto.Ordem_Servico = " + StringGridConserto->Cells[0][StringGridConserto->Row] );
        Query->Prepare( );
        Query->ExecSQL( );
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
  if( Key == '\x1B' ) {
    ListBoxConsertoGrid->Items->Clear( );
    ListBoxConsertoGrid->SendToBack( );
    GroupBoxOrdemDeServico->SetFocus( );
    StringGridConserto->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MemoConsertoDefeitoKeyPress(TObject *Sender, char &Key ) {

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
  if( ( Key == 13 ) && ( MemoConsertoDefeito->Text.IsEmpty( ) ) ) {
    Key = NULL;
  }
  else if( ( Key == 13 ) && ( MemoConsertoDefeito->Lines->Strings[MemoConsertoDefeito->Lines->Count - 1].IsEmpty( ) ) ) {
    Key = NULL;
  }
  if( ( Key == ' ' ) && ( ( MemoConsertoDefeito->Lines->Text.IsEmpty( ) )
      || ( MemoConsertoDefeito->Lines->Strings[MemoConsertoDefeito->Lines->Count - 1].SubString( MemoConsertoDefeito->Lines->Strings[MemoConsertoDefeito->Lines->Count - 1].Length( ), 1 ) == " " ) ) ) {
    Key = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MemoConsertoDefeitoExit(TObject *Sender) {

  TConsigoQuery *Query;

  if( ( !MemoConsertoDefeito->Text.IsEmpty( ) ) &&
      ( Application->MessageBox( "Deseja Realmente Alterar os Dados da Observação do Conserto ?", "Conserto", MB_YESNOCANCEL | MB_ICONQUESTION ) == 6 ) ) {
    try {
      Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

     try {
        Query->SQL->Add( "UPDATE Conserto" );
        Query->SQL->Add( "  SET Observacao = '" + MemoConsertoDefeito->Text + "'" );
        Query->SQL->Add( "  WHERE Ordem_Servico = " + StringGridConserto->Cells[0][StringGridConserto->Row] );
        Query->SQL->Add( "  AND Numero_Serie = '" + StringGridConserto->Cells[6][StringGridConserto->Row] + "'" );
        Query->Prepare( );
        Query->ExecSQL( );
        MemoDefeito[StringGridConserto->Row - 1]->Text = MemoConsertoDefeito->Text;
        StringGridConserto->SetFocus( );
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Conserto", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      delete Query;
    }
  }
}
//---------------------------------------------------------------------------
void TFormGerencia::ConsultarConserto( String* OrdemServico, String* NumeroSerie,
  String* Cliente, String* Data ) {

  TConsigoQuery *Query;
  TDateTime *Date;
  int i;

  try {
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Date = new TDateTime( );

    try {
    	for( i = 1; i < StringGridConserto->RowCount; i++ ) {
  		 	FormGerencia->StringGridConserto->Rows[i]->Clear( );
			}
			FormGerencia->StringGridConserto->RowCount = 2;
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
        MemoConsertoDefeito->Clear( );
        throw Exception( "Não Há Nenhuma Ordem De Serviço com Estes Dados !" );
      }
      else {
        Query->First( );
        while( !Query->Eof ) {
          if( !FormGerencia->StringGridConserto->Cells[0][1].IsEmpty( ) ) {
            FormGerencia->StringGridConserto->RowCount++;
          }
          else {
            MemoConsertoDefeito->Text = Query->FieldByName( "Observacao" )->AsString;
          }
          FormGerencia->StringGridConserto->Cells[0][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Ordem_Servico" )->AsString;
          FormGerencia->StringGridConserto->Cells[1][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Data" )->AsDateTime.FormatString( "dd/mm/yy" );
          if( Query->FieldByName( "Data_Entrega" )->AsDateTime.FormatString( "dd/mm/yy" ) != "30/12/99" ) {
            FormGerencia->StringGridConserto->Cells[2][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Data_Entrega" )->AsDateTime.FormatString( "dd/mm/yy" );
          }
          FormGerencia->StringGridConserto->Cells[3][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Status" )->AsString;
          FormGerencia->StringGridConserto->Cells[4][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Marca" )->AsString;
          FormGerencia->StringGridConserto->Cells[5][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Produto" )->AsString;
          FormGerencia->StringGridConserto->Cells[6][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Numero_Serie" )->AsString;
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          FormGerencia->StringGridConserto->Cells[7][FormGerencia->StringGridConserto->RowCount - 1] = FormatFloat( "#,##0.00", Query->FieldByName( "Preco" )->AsFloat );
          FormGerencia->StringGridConserto->Cells[8][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Cliente" )->AsString;
          FormGerencia->StringGridConserto->Cells[9][FormGerencia->StringGridConserto->RowCount - 1] = Query->FieldByName( "Vendedor" )->AsString;
          MemoDefeito[FormGerencia->StringGridConserto->RowCount - 2] = new TMemo( FormGerencia );
          MemoDefeito[FormGerencia->StringGridConserto->RowCount - 2]->Text = Query->FieldByName( "Observacao" )->AsString;
          Query->Next( );
        }
        MemoConsertoDefeito->Text = MemoDefeito[0]->Text;
        FormGerencia->StringGridConserto->SetFocus( );
      }
    }
    catch( Exception &e ) {
    	for( i = 1; i < FormGerencia->StringGridConserto->RowCount; i++ ) {
  		 	FormGerencia->StringGridConserto->Rows[i]->Clear( );
			}
      FormGerencia->StringGridConserto->RowCount = 2;
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
