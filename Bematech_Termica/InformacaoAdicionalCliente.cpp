//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Main.h"
#include "InformacaoAdicionalCliente.h"
#include "ThreadConsultaInformacaoAdicionalCliente.h"
#include "Dmod1.h"
//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TFormInformacaoAdicionalCliente *FormInformacaoAdicionalCliente;
//---------------------------------------------------------------------------
__fastcall TFormInformacaoAdicionalCliente::TFormInformacaoAdicionalCliente(TComponent* Owner)
 : TForm( Owner ) {

}
//---------------------------------------------------------------------------
void __fastcall TFormInformacaoAdicionalCliente::FormCreate( TObject *Sender ) {

	StringGridClienteInfo->RowCount = 2;
  StringGridClienteInfo->ColCount = 12;
  StringGridClienteInfo->Cells[0][0] = "Data da Compra";
  StringGridClienteInfo->ColWidths[0] = 160;
  StringGridClienteInfo->Cells[1][0] = "Marca";
  StringGridClienteInfo->ColWidths[1] = 130;
  StringGridClienteInfo->Cells[2][0] = "Produto";
  StringGridClienteInfo->ColWidths[2] = 455;
  StringGridClienteInfo->Cells[3][0] = "Qtd";
  StringGridClienteInfo->ColWidths[3] = 45;
  StringGridClienteInfo->Cells[4][0] = "Preço Unit R$";
  StringGridClienteInfo->ColWidths[4] = 90;
  StringGridClienteInfo->Cells[5][0] = "Preço Total R$";
  StringGridClienteInfo->ColWidths[5] = 90;
  StringGridClienteInfo->Cells[6][0] = "Tipo de Venda";
  StringGridClienteInfo->ColWidths[6] = 149;
  StringGridClienteInfo->Cells[7][0] = "Entrada R$";
  StringGridClienteInfo->ColWidths[7] = 110;
  StringGridClienteInfo->Cells[8][0] = "Parcela R$";
  StringGridClienteInfo->ColWidths[8] = 110;
  StringGridClienteInfo->Cells[9][0] = "Número de Série";
  StringGridClienteInfo->ColWidths[9] = 158;
  StringGridClienteInfo->Cells[10][0] = "Nota Fiscal nº";
  StringGridClienteInfo->ColWidths[10] = 158;
  StringGridClienteInfo->Cells[11][0] = "Vendedor";
  StringGridClienteInfo->ColWidths[11] = 200;
}
//---------------------------------------------------------------------------
void __fastcall TFormInformacaoAdicionalCliente::SairESC1Click( TObject *Sender ) {

  this->Close( );
  FormPrincipal->PageControl1->ActivePage = FormPrincipal->TabSheetClientes;
  FormInformacaoAdicionalCliente = NULL;
  delete FormInformacaoAdicionalCliente;
}
//---------------------------------------------------------------------------
void __fastcall TFormInformacaoAdicionalCliente::BitBtnVoltarClick( TObject *Sender ) {

	SairESC1Click( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TFormInformacaoAdicionalCliente::ComboBoxNomeClienteKeyDown( TObject *Sender, WORD &Key, TShiftState Shift ) {

  TThreadConsultaInfoCliente *ThreadConsultaInfoCliente;
  TConsigoQuery *Query;
  int i;

  if( ( ( Key == VK_UP ) || ( Key == VK_DOWN ) ) && ( ComboBoxNomeCliente->Text.Length( ) > 3 ) &&
        ( !ComboBoxNomeCliente->DroppedDown ) ) {
    try {
      Query= new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
      ComboBoxNomeCliente->Items->Clear( );

      try {
        Query->SQL->Add( "SELECT 	Nome" );
        Query->SQL->Add( "FROM Clientes" );
        Query->SQL->Add( "WHERE Nome LIKE '%" + StringReplace( Trim( ComboBoxNomeCliente->Text ), " ", "%", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "%'" );
        Query->SQL->Add( "ORDER BY Nome" );
        Query->Prepare( );
        Query->Open( );
	      if( !Query->IsEmpty( ) ) {
          Query->First( );
          while( !Query->Eof ) {
            ComboBoxNomeCliente->Items->Append( Query->FieldByName( "Nome" )->AsString );
            Query->Next( );
          }
          ComboBoxNomeCliente->DroppedDown = true;
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Informações Adicionais do Cliente", MB_OK | MB_ICONERROR );
      }
    }
    __finally {
      Query->Close( );
      delete Query;
    }
  }
  if( Key == VK_RETURN ) {
    try {
      ThreadConsultaInfoCliente = new TThreadConsultaInfoCliente( &( Trim( ComboBoxNomeCliente->Text ) ), true );
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Informações Adicionais do Cliente", MB_OK | MB_ICONERROR );
    }

    StringGridClienteInfo->SetFocus( );
  }
}
//---------------------------------------------------------------------------

