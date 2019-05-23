//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Main.h"
#include "Dmod1.h"
#include <vcl\inifiles.hpp>
//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TFormGerencia *FormGerencia;
//---------------------------------------------------------------------------
__fastcall TFormGerencia::TFormGerencia( TComponent* Owner ): TForm( Owner ) {

  ListBoxConsertoGrid = new TListBox( FormGerencia );
  ListBoxConsertoGrid->MultiSelect = false;
  ListBoxConsertoGrid->ExtendedSelect = false;
  ListBoxConsertoGrid->Sorted = true;
  ListBoxConsertoGrid->Style = lbStandard;
  ListBoxConsertoGrid->Visible = false;
  ListBoxConsertoGrid->Font->Size = 10;
  ListBoxConsertoGrid->ParentWindow = FormGerencia->Handle;
}
//---------------------------------------------------------------------------
__fastcall TFormGerencia::~TFormGerencia( void ) {

  delete SecurityFlag;
  delete ListBoxConsertoGrid;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::Sair1Click( TObject *Sender ) {

  // Remover depois o Close( )!!!
  DataModuleQuery->Query15->Close( );
  DataModuleQuery->Produtos->Close( );
  FormPrincipal->PageControl1->ActivePage = FormPrincipal->TabSheetProdutos;
  this->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::FormCreate( TObject *Sender ) {

	TIniFile *OptionsIni;
  TStringList *OptionsList;
  String *Retorno;

  StringGridDespesa->RowCount = 2;
  StringGridDespesa->ColCount = 4;
  StringGridDespesa->Cells[0][0] = "Vencimento";
  StringGridDespesa->ColWidths[0] = 122;
  StringGridDespesa->Cells[1][0] = "Nome";
  StringGridDespesa->ColWidths[1] = 550;
  StringGridDespesa->Cells[2][0] = "Valor R$";
  StringGridDespesa->ColWidths[2] = 96;
  StringGridDespesa->Cells[3][0] = "Data";
  StringGridDespesa->ColWidths[3] = 170;

  StringGridEntradaProduto->RowCount = 2;
  StringGridEntradaProduto->ColCount = 7;
  StringGridEntradaProduto->Cells[0][0] = "Marca";
  StringGridEntradaProduto->ColWidths[0] = 180;
  StringGridEntradaProduto->Cells[1][0] = "Nome";
  StringGridEntradaProduto->ColWidths[1] = 424;
  StringGridEntradaProduto->Cells[2][0] = "Qtd";
  StringGridEntradaProduto->ColWidths[2] = 52;
  StringGridEntradaProduto->Cells[3][0] = "Preço Unit U$";
  StringGridEntradaProduto->ColWidths[3] = 115;
  StringGridEntradaProduto->Cells[4][0] = "Preço U$";
  StringGridEntradaProduto->ColWidths[4] = 115;
  StringGridEntradaProduto->Cells[5][0] = "Data";
  StringGridEntradaProduto->ColWidths[5] = 160;
  StringGridEntradaProduto->Cells[6][0] = "Código";
  StringGridEntradaProduto->ColWidths[6] = 180;

  StringGridFornecedor->RowCount = 2;
  StringGridFornecedor->ColCount = 10;
  StringGridFornecedor->Cells[0][0] = "Nome";
  StringGridFornecedor->ColWidths[0] = 559;
  StringGridFornecedor->Cells[1][0] = "Endereço";
  StringGridFornecedor->ColWidths[1] = 547;
  StringGridFornecedor->Cells[2][0] = "Bairro";
  StringGridFornecedor->ColWidths[2] = 268;
  StringGridFornecedor->Cells[3][0] = "Cidade";
  StringGridFornecedor->ColWidths[3] = 306;
  StringGridFornecedor->Cells[4][0] = "Estado";
  StringGridFornecedor->ColWidths[4] = 130;
  StringGridFornecedor->Cells[5][0] = "CEP";
  StringGridFornecedor->ColWidths[5] = 105;
  StringGridFornecedor->Cells[6][0] = "Telefone";
  StringGridFornecedor->ColWidths[6] = 144;
  StringGridFornecedor->Cells[7][0] = "Telefone Fax";
  StringGridFornecedor->ColWidths[7] = 144;
  StringGridFornecedor->Cells[8][0] = "CNPJ";
  StringGridFornecedor->ColWidths[8] = 224;
  StringGridFornecedor->Cells[9][0] = "Inscrição Estadual";
  StringGridFornecedor->ColWidths[9] = 186;

  StringGridProduto->RowCount = 2;
  StringGridProduto->ColCount = 4;
  StringGridProduto->Cells[0][0] = "Marca";
  StringGridProduto->ColWidths[0] = 180;
  StringGridProduto->Cells[1][0] = "Nome";
  StringGridProduto->ColWidths[1] = 424;
  StringGridProduto->Cells[2][0] = "Qtd";
  StringGridProduto->ColWidths[2] = 52;
  StringGridProduto->Cells[3][0] = "Qtd*";
  StringGridProduto->ColWidths[3] = 52;

  StringGridFechamento->RowCount = 2;
  StringGridFechamento->ColCount = 14;
  StringGridFechamento->Cells[0][0] = "Data";
  StringGridFechamento->ColWidths[0] = 170;
  StringGridFechamento->Cells[1][0] = "Marca";
  StringGridFechamento->ColWidths[1] = 180;
  StringGridFechamento->Cells[2][0] = "Nome";
  StringGridFechamento->ColWidths[2] = 424;
  StringGridFechamento->Cells[3][0] = "Qtd";
  StringGridFechamento->ColWidths[3] = 52;
  StringGridFechamento->Cells[4][0] = "Preço Unit R$";
  StringGridFechamento->ColWidths[4] = 115;
  StringGridFechamento->Cells[5][0] = "Preço R$";
  StringGridFechamento->ColWidths[5] = 115;
  StringGridFechamento->Cells[6][0] = "Tipo de Venda";
  StringGridFechamento->ColWidths[6] = 180;
  StringGridFechamento->Cells[7][0] = "Entrada R$";
  StringGridFechamento->ColWidths[7] = 115;
  StringGridFechamento->Cells[8][0] = "Parcela R$";
  StringGridFechamento->ColWidths[8] = 115;
  StringGridFechamento->Cells[9][0] = "Número de Série";
  StringGridFechamento->ColWidths[9] = 180;
  StringGridFechamento->Cells[10][0] = "Cupom Fiscal nº";
  StringGridFechamento->ColWidths[10] = 154;
  StringGridFechamento->Cells[11][0] = "Tipo de Nota Fiscal";
  StringGridFechamento->ColWidths[11] = 180;
  StringGridFechamento->Cells[12][0] = "Cliente";
  StringGridFechamento->ColWidths[12] = 430;
  StringGridFechamento->Cells[13][0] = "Vendedor";
  StringGridFechamento->ColWidths[13] = 180;

  StringGridSedex->RowCount = 2;
  StringGridSedex->ColCount = 6;
  StringGridSedex->Cells[0][0] = "Data";
  StringGridSedex->ColWidths[0] = 170;
  StringGridSedex->Cells[1][0] = "CEP";
  StringGridSedex->ColWidths[1] = 105;
  StringGridSedex->Cells[2][0] = "Objeto";
  StringGridSedex->ColWidths[2] = 415;
  StringGridSedex->Cells[3][0] = "Preco";
  StringGridSedex->ColWidths[3] = 115;
  StringGridSedex->Cells[4][0] = "Cliente";
  StringGridSedex->ColWidths[4] = 500;
  StringGridSedex->Cells[5][0] = "Cupom Fiscal nº";
  StringGridSedex->ColWidths[5] = 154;

  StringGridAlteracaoProduto->RowCount = 2;
  StringGridAlteracaoProduto->ColCount = 10;
  StringGridAlteracaoProduto->Cells[0][0] = "Marca";
  StringGridAlteracaoProduto->ColWidths[0] = 180;
  StringGridAlteracaoProduto->Cells[1][0] = "Nome";
  StringGridAlteracaoProduto->ColWidths[1] = 424;
  StringGridAlteracaoProduto->Cells[2][0] = "Qtd";
  StringGridAlteracaoProduto->ColWidths[2] = 52;
  StringGridAlteracaoProduto->Cells[3][0] = "Qtd*";
  StringGridAlteracaoProduto->ColWidths[3] = 52;
  StringGridAlteracaoProduto->Cells[4][0] = "Custo Anterior U$";
  StringGridAlteracaoProduto->ColWidths[4] = 125;
  StringGridAlteracaoProduto->Cells[5][0] = "Custo Atual U$";
  StringGridAlteracaoProduto->ColWidths[5] = 120;
  StringGridAlteracaoProduto->Cells[6][0] = "Preço U$";
  StringGridAlteracaoProduto->ColWidths[6] = 115;
  StringGridAlteracaoProduto->Cells[7][0] = "Garantia";
  StringGridAlteracaoProduto->ColWidths[7] = 100;
  StringGridAlteracaoProduto->Cells[8][0] = "Dólar U$";
  StringGridAlteracaoProduto->ColWidths[8] = 115;
  StringGridAlteracaoProduto->Cells[9][0] = "Código";
  StringGridAlteracaoProduto->ColWidths[9] = 180;

  StringGridConserto->ColCount = 10;
  StringGridConserto->RowCount = 2;
  StringGridConserto->Cells[0][0] = "Ordem Serviço";
  StringGridConserto->ColWidths[0] = 170;
  StringGridConserto->Cells[1][0] = "Data";
  StringGridConserto->ColWidths[1] = 170;
  StringGridConserto->Cells[2][0] = "Entrega";
  StringGridConserto->ColWidths[2] = 170;
  StringGridConserto->Cells[3][0] = "Status";
  StringGridConserto->ColWidths[3] = 200;
  StringGridConserto->Cells[4][0] = "Marca";
  StringGridConserto->ColWidths[4] = 140;
  StringGridConserto->Cells[5][0] = "Nome";
  StringGridConserto->ColWidths[5] = 580;
  StringGridConserto->Cells[6][0] = "Número Série";
  StringGridConserto->ColWidths[6] = 180;
  StringGridConserto->Cells[7][0] = "Preço R$";
  StringGridConserto->ColWidths[7] = 115;
  StringGridConserto->Cells[8][0] = "Cliente";
  StringGridConserto->ColWidths[8] = 500;
  StringGridConserto->Cells[9][0] = "Vendedor";
  StringGridConserto->ColWidths[9] = 180;

  try {
    this->SecurityFlag = new bool( false );
    Retorno = new AnsiString( );
  	OptionsList = new TStringList( );
  	OptionsIni = new TIniFile( "C:\\Consigo.ini" );

    try {
  	  if( OptionsIni->SectionExists( "SERVER" ) ) {
	  	  OptionsIni->ReadSectionValues( "SERVER", OptionsList );
	    }
  	  else {
    		throw Exception( "O Arquivo: Consigo.ini está Incorreto!" );
	    }
      if( OptionsList->Values["Servidor"] != "true" ) {
        delete TabSheetImpressora;
        MenuItemImpressora->Visible = false;
        delete TabSheetTef;
        MenuItemTef->Visible = false;
      }
      if( OptionsList->Values["Administrador"] != "true" ) {
        delete TabSheetPrecos;
        MenuItemPrecos->Visible = false;
        delete TabSheetSedex;
        MenuItemSedex->Visible = false;
        delete TabSheetEmFalta;
        MenuItemEmFalta->Visible = false;
      }
      else {
        if( OptionsList->Values["Servidor"] != "true" ) {
          FormPrincipal->BitBtnCancelarVenda->Visible = true;
        }
      }
      if( OptionsList->Values["SuperUser"] != "true" ) {
        delete TabSheetFornecedores;
        MenuItemFornecedores->Visible = false;
        delete TabSheetDespesas;
        MenuItemDespesas->Visible = false;
        delete TabSheetEntrada;
        MenuItemEntradas->Visible = false;
        delete TabSheetFechamento;
        MenuItemFechamento->Visible = false;
      }
    }
    catch( String &Error ) {
	  	Application->MessageBox( Error.c_str( ), "Consigo DataBase Manager V1.0", MB_OK | MB_ICONERROR );
  	  Application->Terminate( );
    }
  }
  __finally {
    delete Retorno;
  	delete OptionsIni;
    delete OptionsList;
  }
}
//---------------------------------------------------------------------------
