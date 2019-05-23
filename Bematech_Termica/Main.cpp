//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include <vcl\inifiles.hpp>
#include "Main.h"
#include "Dmod1.h"
#include "Dmod2.h"
#include "CadastroCliente.h"
#include "Gerencia.h"
#include "ImpressaoCotacaoPreco.h"
#include "ImpressoraMecaf.h"
#include "TefTecBan.h"
#include "TefVisanetRedecardAmex.h"
#include "ClientSocket.h"
#include "ServerSocket.h"
#include "InsercaoProduto.h"
#include "InformacaoAdicionalCliente.h"
#include "SecaoCritica.h"
#include "InsercaoProduto.h"
//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TFormPrincipal *FormPrincipal;
TSecaoCritica *SecaoCritica;
//---------------------------------------------------------------------------
__fastcall TFormPrincipal::TFormPrincipal( TComponent* Owner )
 : TForm( Owner ) {

}
//---------------------------------------------------------------------------
__fastcall TFormPrincipal::~TFormPrincipal( void ) {

  delete JpegImage1;
	delete JpegImage3;

  if( ServerSocket != NULL ) {
     delete ServerSocket;
  }
  delete ServerSocketIP;

  delete SecaoCritica;
  delete ImpressoraMecafSemaforo;
  delete ImpressoraEcfSemaforo;
  delete TefSemaforo;
  delete QuerySemaforo;
  if( MemoDefeito != NULL ) {
    delete MemoDefeito;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::FormCreate( TObject *Sender ) {

	TIniFile *OptionsIni;
  TStringList *OptionsList;
  TConsigoQuery *Query;
  TServerSocket *ServerSocket;
  TTefVisaNetRedeCardAmex *TefVisaNetRedeCardAmex;
  TTefTecBan *TefTecBan;
  String *Retorno;

  StrGridVendaProduto->RowCount = 2;
  StrGridVendaProduto->ColCount = 9;
  StrGridVendaProduto->Cells[0][0] = "Marca";
  StrGridVendaProduto->ColWidths[0] = 140;
  StrGridVendaProduto->Cells[1][0] = "Nome";
  StrGridVendaProduto->ColWidths[1] = 470;
  StrGridVendaProduto->Cells[2][0] = "Qtd";
  StrGridVendaProduto->ColWidths[2] = 45;
  StrGridVendaProduto->Cells[3][0] = "Preço Unit R$";
  StrGridVendaProduto->ColWidths[3] = 110;
  StrGridVendaProduto->Cells[4][0] = "Preço R$";
  StrGridVendaProduto->ColWidths[4] = 110;
  StrGridVendaProduto->Cells[5][0] = "Código";
  StrGridVendaProduto->ColWidths[5] = 180;
  StrGridVendaProduto->Cells[6][0] = "Número de Série";
  StrGridVendaProduto->ColWidths[6] = 180;
  StrGridVendaProduto->Cells[7][0] = "Garantia";
  StrGridVendaProduto->ColWidths[7] = 100;
  StrGridVendaProduto->Cells[8][0] = "Data";
  StrGridVendaProduto->ColWidths[8] = 164;


  StringGridConsultaProduto->RowCount = 2;
  StringGridConsultaProduto->ColCount = 7;
  StringGridConsultaProduto->Cells[0][0] = "Marca";
  StringGridConsultaProduto->ColWidths[0] = 100;
  StringGridConsultaProduto->Cells[1][0] = "Nome";
  StringGridConsultaProduto->ColWidths[1] = 570;
  StringGridConsultaProduto->Cells[2][0] = "Preço R$";
  StringGridConsultaProduto->ColWidths[2] = 90;
  StringGridConsultaProduto->Cells[3][0] = "Qtd";
  StringGridConsultaProduto->ColWidths[3] = 45;
  StringGridConsultaProduto->Cells[4][0] = "Qtd*";
  StringGridConsultaProduto->ColWidths[4] = 45;
  StringGridConsultaProduto->Cells[5][0] = "Garantia";
  StringGridConsultaProduto->ColWidths[5] = 100;
  StringGridConsultaProduto->Cells[6][0] = "Codigo";
  StringGridConsultaProduto->ColWidths[6] = 180;

  StringGridCliente->RowCount = 2;
  StringGridCliente->ColCount = 14;
  StringGridCliente->Cells[0][0] = "Nome";
  StringGridCliente->ColWidths[0] = 379;
	StringGridCliente->Cells[1][0] = "Endereço";
  StringGridCliente->ColWidths[1] = 580;
  StringGridCliente->Cells[2][0] = "Bairro";
  StringGridCliente->ColWidths[2] = 300;
  StringGridCliente->Cells[3][0] = "Cidade";
  StringGridCliente->ColWidths[3] = 350;
  StringGridCliente->Cells[4][0] = "Estado";
  StringGridCliente->ColWidths[4] = 80;
  StringGridCliente->Cells[5][0] = "Cep";
  StringGridCliente->ColWidths[5] = 100;
  StringGridCliente->Cells[6][0] = "Telefone";
  StringGridCliente->ColWidths[6] = 150;
  StringGridCliente->Cells[7][0] = "Telefone Comercial";
  StringGridCliente->ColWidths[7] = 150;
  StringGridCliente->Cells[8][0] = "Telefone Fax";
  StringGridCliente->ColWidths[8] = 150;
  StringGridCliente->Cells[9][0] = "RG ou CNPJ";
  StringGridCliente->ColWidths[9] = 140;
  StringGridCliente->Cells[10][0] = "EERG";
  StringGridCliente->ColWidths[10] = 60;
  StringGridCliente->Cells[11][0] = "CPF";
  StringGridCliente->ColWidths[11] = 160;
  StringGridCliente->Cells[12][0] = "Inscrição Estadual";
  StringGridCliente->ColWidths[12] = 200;
  StringGridCliente->Cells[13][0] = "E-Mail";
  StringGridCliente->ColWidths[13] = 350;

  StringGridProdutoCotacao->RowCount = 2;
  StringGridProdutoCotacao->ColCount = 7;
  StringGridProdutoCotacao->Cells[0][0] = "Marca";
  StringGridProdutoCotacao->ColWidths[0] = 140;
  StringGridProdutoCotacao->Cells[1][0] = "Nome";
  StringGridProdutoCotacao->ColWidths[1] = 580;
  StringGridProdutoCotacao->Cells[2][0] = "Qtd";
  StringGridProdutoCotacao->ColWidths[2] = 45;
  StringGridProdutoCotacao->Cells[3][0] = "Preço Unit R$";
  StringGridProdutoCotacao->ColWidths[3] = 110;
  StringGridProdutoCotacao->Cells[4][0] = "Preço R$";
  StringGridProdutoCotacao->ColWidths[4] = 90;
  StringGridProdutoCotacao->Cells[5][0] = "Garantia";
  StringGridProdutoCotacao->ColWidths[5] = 100;
  StringGridProdutoCotacao->Cells[6][0] = "Código";
  StringGridProdutoCotacao->ColWidths[6] = 180;

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
    JpegImage1 = new TJPEGImage( );
    JpegImage3 = new TJPEGImage( );
    if( FileExists( "P:\\Consigo.jpg" ) ) {
     	JpegImage1->LoadFromFile( "P:\\Consigo.jpg" );
     	Image5->Picture->Assign( JpegImage1 );
    }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Consigo DataBase Manager V1.0", MB_OK | MB_ICONERROR );
  }

  try {
    Retorno = new AnsiString( );
    this->ServerSocketIP = new AnsiString( );
  	OptionsList = new TStringList( );
  	OptionsIni = new TIniFile( "C:\\Consigo.ini" );
    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    TefTecBan = new TTefTecBan( );
    TefVisaNetRedeCardAmex = new TTefVisaNetRedeCardAmex( );

    try {
  	  if( OptionsIni->SectionExists( "SERVER" ) ) {
	  	  OptionsIni->ReadSectionValues( "SERVER", OptionsList );
    		if( !OptionsList->Values["IP"].IsEmpty( ) ) {
	    		*this->ServerSocketIP = OptionsList->Values["IP"];
	    	}
	    }
  	  else {
    		throw Exception( "O Arquivo: Consigo.ini está Incorreto!" );
	    }

      SecaoCritica = new TSecaoCritica( );
      ImpressoraMecafSemaforo = new bool( true );
      ImpressoraEcfSemaforo = new bool( true );
      TefSemaforo = new bool( true );
      QuerySemaforo = new bool( true );

      Query->SQL->Add( "SELECT Nome" );
      Query->SQL->Add( "FROM Vendedores" );
      Query->SQL->Add( "ORDER BY Nome" );
      Query->Prepare( );
      Query->Open( );
      Query->First( );
      while( !Query->Eof ) {
        this->ComboBoxVendedor->Items->Add( Query->FieldByName( "Nome" )->AsString );
        this->ComboBoxVendedor2->Items->Add( Query->FieldByName( "Nome" )->AsString );
        Query->Next( );
      }
      Query->Close( );

      if( OptionsList->Values["Servidor"] == "true" ) {
        ServerSocket = new TConsigoServerSocket( FormPrincipal );
        /*
        TefTecBan->Atv( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
        */
        TefTecBan->ChecarErro( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
        TefTecBan->ChecarErroTemp( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
        /*
        TefVisaNetRedeCardAmex->Atv( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
        */
        TefVisaNetRedeCardAmex->ChecarErro( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
        TefVisaNetRedeCardAmex->ChecarErroTemp( Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
        delete this->TabSheetVendas;
        this->MenuItemVendas->Enabled = false;
        this->MenuItemVendas->Visible = false;
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
    delete Query;
    delete TefVisaNetRedeCardAmex;
    delete TefTecBan;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemSairClick( TObject *Sender ) {

	if( Application->MessageBox( "Tem Certeza que Deseja Sair do Aplicativo?",
  														 "CONSIGO Client DataBase Manager",
                               MB_YESNO | MB_ICONQUESTION ) == ID_YES ) {
    /*
    FormGerencia->Close( );
    FormGerencia = NULL;
    delete FormGerencia;
	  this->Close( );
    FormPrincipal = NULL;
    delete FormPrincipal;
    */
    Application->Terminate( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemConsultadeProdutosClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetProdutos;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemConsultadeClientesClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetClientes;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemEfetuarCotaoClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetCotacaoPreco;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemFuncoesGerenciasClick( TObject *Sender ) {

  bool *Ok;
  int i;

  try {
    Ok = new bool( false );

    this->SenhaExibir( Ok );
    if( *Ok ) {
      if( *FormGerencia->SecurityFlag ) {
        if( FormGerencia->TabSheetFornecedores != NULL ) {
          FormGerencia->TabSheetFornecedores->TabVisible = false;
        }
        FormGerencia->MenuItemFornecedores->Visible = false;
        if( FormGerencia->TabSheetEntrada != NULL ) {
          FormGerencia->TabSheetEntrada->TabVisible = false;
        }
        FormGerencia->MenuItemEntradas->Visible = false;
        if( FormGerencia->TabSheetPrecos != NULL ) {
          FormGerencia->TabSheetPrecos->TabVisible = false;
        }
        FormGerencia->MenuItemPrecos->Visible = false;
        if( FormGerencia->TabSheetDespesas != NULL ) {
          FormGerencia->TabSheetDespesas->TabVisible = false;
        }
        FormGerencia->MenuItemDespesas->Visible = false;
        if( FormGerencia->TabSheetFechamento != NULL ) {
          FormGerencia->BitBtnEntradaProduto->Visible = false;
          FormGerencia->BitBtnFechamentoVendedor->Visible = false;
          FormGerencia->LabelFechamentoTotalOk->Visible = false;
          FormGerencia->EditFechamentoTotalOk->Visible = false;
          FormGerencia->LabelFechamentoTotal->Visible = false;
          FormGerencia->EditFechamentoTotal->Visible = false;

          for( i = 1; i < FormGerencia->StringGridFechamento->RowCount; i++ ) {
    	      FormGerencia->StringGridFechamento->Rows[i]->Clear( );
          }
          FormGerencia->StringGridFechamento->RowCount = 2;
          FormGerencia->EditFechamentoTotalOk->Clear( );
          FormGerencia->EditFechamentoTotal->Clear( );
          FormGerencia->EditFechamentoTotalGeral->Clear( );
        }
      }
      else {
        if( FormGerencia->TabSheetFornecedores != NULL ) {
          FormGerencia->TabSheetFornecedores->TabVisible = true;
        }
        FormGerencia->MenuItemFornecedores->Visible = true;
        if( FormGerencia->TabSheetEntrada != NULL ) {
          FormGerencia->TabSheetEntrada->TabVisible = true;
        }
        FormGerencia->MenuItemEntradas->Visible = true;
        if( FormGerencia->TabSheetPrecos != NULL ) {
          FormGerencia->TabSheetPrecos->TabVisible = true;
        }
        FormGerencia->MenuItemPrecos->Visible = true;
        if( FormGerencia->TabSheetDespesas != NULL ) {
          FormGerencia->TabSheetDespesas->TabVisible = true;
        }
        FormGerencia->MenuItemDespesas->Visible = true;
        if( FormGerencia->TabSheetFechamento != NULL ) {
          FormGerencia->BitBtnEntradaProduto->Visible = true;
          FormGerencia->BitBtnFechamentoVendedor->Visible = true;
          FormGerencia->LabelFechamentoTotalOk->Visible = true;
          FormGerencia->EditFechamentoTotalOk->Visible = true;
          FormGerencia->LabelFechamentoTotal->Visible = true;
          FormGerencia->EditFechamentoTotal->Visible = true;
        }
      }
      FormGerencia->Visible = true;
      FormGerencia->PageControl1->ActivePage = FormGerencia->TabSheetFornecedores;
    }
  }
  __finally {
    delete Ok;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemEfetuarVendaClick( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetVendas;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemFerramentasAdministrativasClick( TObject *Sender ) {

  bool *Ok;

  try {
    Ok = new bool( false );
    this->SenhaExibir( Ok );
    if( *Ok ) {
      FormInsercaoProduto = new TFormInsercaoProduto( FormPrincipal );
      FormInsercaoProduto->Visible  = true;
    }
  }
  __finally {
    delete Ok;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::FormActivate( TObject *Sender ) {

  this->SetFocus( );
  this->BringToFront( );
  PageControl1->ActivePage = TabSheetProdutos;
  EditCodigoProduto->SetFocus( );
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemSedexClick( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetSedex;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemConsultadeServicoClick( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetConserto;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuItemEmissaoReciboClick( TObject *Sender ) {

  PageControl1->ActivePage = TabSheetRecibo;
}
//---------------------------------------------------------------------------
