//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Orcamento.h"
#include "Dmod1.h"
#include "Main.h"
#include "SecaoCritica.h"
#include "ImpressoraMecaf.h"
#include "ImpressoraBematech.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
 __fastcall TOrcamento::TOrcamento( TStringList* OrcamentoInfo ) {

  this->OrcamentoInfo = new TStringList( );
  this->OrcamentoInfo->Assign( OrcamentoInfo );
  this->NumeroOrcamento = new AnsiString( );
  this->NomeCliente = new AnsiString( );
  this->Telefone = new AnsiString( );
}
//---------------------------------------------------------------------------
__fastcall TOrcamento::~TOrcamento( void ) {

  delete this->OrcamentoInfo;
  delete this->NumeroOrcamento;
  delete this->NomeCliente;
  delete this->Telefone;
}
//---------------------------------------------------------------------------
void TOrcamento::RealizarOrdemDeServico( String* &Retorno ) {

  TConsigoQuery *Query;

  this->InserirOrcamento( Retorno );
  if( Retorno->IsEmpty( ) ) {
    this->ImprimirOrcamento( Retorno );
    if( !Retorno->IsEmpty( ) ) {
      try {
        while( !*FormPrincipal->QuerySemaforo ) {
          Sleep( 500 );
        }
        SecaoCritica->Acquire( );
        *FormPrincipal->QuerySemaforo = false;
        SecaoCritica->Release( );

        Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
        Query->SQL->Add( "BEGIN TRANSACTION" );
        Query->SQL->Add( "DELETE FROM Conserto" );
        Query->SQL->Add( "  WHERE Ordem_Servico = " + *this->NumeroOrcamento );
        Query->Prepare( );
        Query->ExecSQL( );
      }
      __finally {
       Query->Close( );
       delete Query;

       SecaoCritica->Acquire( );
       *FormPrincipal->QuerySemaforo = true;
       SecaoCritica->Release( );
      }
    }
  }
}
//---------------------------------------------------------------------------
void TOrcamento::InserirOrcamento( String* &Retorno ) {

  TConsigoQuery *Query;
  TDateTime *Data;
  int i;

  try {
    while( !*FormPrincipal->QuerySemaforo ) {
      Sleep( 500 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->QuerySemaforo = false;
    SecaoCritica->Release( );

    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    Data = new TDateTime( );

    try {
      Query->SQL->Add( "SELECT MAX( Ordem_Servico ) + 1 AS Servico" );
      Query->SQL->Add( "  FROM Conserto" );
      Query->Open( );
      *this->NumeroOrcamento = Query->FieldByName( "Servico" )->AsString;
      Query->Close( );

      *this->NomeCliente = this->OrcamentoInfo->Values["Cliente"];
      Query->SQL->Clear( );
      Query->SQL->Add( "SELECT Nome" );
      Query->SQL->Add( "  FROM Clientes" );
      Query->SQL->Add( "  WHERE Nome = '" + *this->NomeCliente + "'" );
      Query->Open( );
      if( Query->IsEmpty( ) ) {
        *Retorno = "Cliente Inexistente !";
        throw( *Retorno );
      }
      Query->Close( );

      Query->SQL->Clear( );
      Query->SQL->Add( "SELECT Telefone, Telefone_Comercial, Telefone_Fax" );
      Query->SQL->Add( "  FROM Clientes" );
      Query->SQL->Add( "  WHERE Nome = '" + *this->NomeCliente + "'" );
      Query->Open( );
      *this->Telefone = Query->FieldByName( "Telefone" )->AsString + " " + Query->FieldByName( "Telefone_Comercial" )->AsString + " " + Query->FieldByName( "Telefone_Fax" )->AsString;
      Query->Close( );

      for( i = 1; i <= this->OrcamentoInfo->Values["ItemQtd"] ; i++ ) {
        Query->SQL->Clear( );
        Query->SQL->Add( "BEGIN TRANSACTION" );
        Query->SQL->Add( "INSERT INTO Conserto ( Ordem_Servico, Codigo, Numero_Serie," );
        Query->SQL->Add( "  Preco, RG_Cliente, EERG_Cliente, RG_Vendedor, EERG_Vendedor," );
        Query->SQL->Add( "  Status, Data, Data_Entrega, Observacao )" );
        Query->SQL->Add( "  SELECT " + *this->NumeroOrcamento + ", '" + this->OrcamentoInfo->Values["Codigo" + IntToStr( i )] + "'," );
        Query->SQL->Add( "    '" + this->OrcamentoInfo->Values["NumeroSerie" + IntToStr( i )] + "'," );
        Query->SQL->Add(      StringReplace( StringReplace( this->OrcamentoInfo->Values["Preco" + IntToStr( i )], ".", "", TReplaceFlags( ) << rfReplaceAll ), ",", ".", TReplaceFlags( ) << rfReplaceAll ) + "," );
        Query->SQL->Add( "    Clientes.RG, Clientes.EERG, Vendedores.RG, Vendedores.EERG, 2," );
        Query->SQL->Add( "    '" + Data->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:mm:ss" ) + "',NULL," );
        Query->SQL->Add( "    '" + StringReplace( this->OrcamentoInfo->Values["Defeito" + IntToStr( i )], "||", "\r\n", TReplaceFlags( ) << rfReplaceAll ) + "'" );
        Query->SQL->Add( "  FROM Clientes, Vendedores" );
        Query->SQL->Add( "  WHERE Clientes.Nome = '" + *this->NomeCliente + "'" );
        Query->SQL->Add( "  AND   Vendedores.Nome = '" + this->OrcamentoInfo->Values["Vendedor"] + "'" );
        Query->SQL->Add( "COMMIT TRANSACTION" );
        Query->Prepare( );
        Query->ExecSQL( );
      }
    }
    catch( String &Mensagem ) {
      Query->SQL->Clear( );
      Query->SQL->Add( "BEGIN TRANSACTION" );
      Query->SQL->Add( "DELETE FROM Conserto" );
      Query->SQL->Add( "  WHERE Ordem_Servico = " + *this->NumeroOrcamento );
      Query->Prepare( );
      Query->ExecSQL( );

      *Retorno = Mensagem;
    }
  }
  __finally {
    Query->Close( );
    delete Query;
    delete Data;

    SecaoCritica->Acquire( );
    *FormPrincipal->QuerySemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TOrcamento::ImprimirOrcamento( String* &Retorno ) {

  //TImpressoraMecaf *Impressora;
  TImpressoraBematech *Impressora;

  String *NumeroSerie, *Preco, *Codigo, *Descricao, *Defeito;
  int i, j;

  try {
    while( !*FormPrincipal->ImpressoraMecafSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = false;
    SecaoCritica->Release( );

    NumeroSerie = new AnsiString( );

    //Impressora = new TImpressoraMecaf( );
    //Impressora->CarregarDll( Retorno );
    Impressora = new TImpressoraBematech( );

    Preco = new AnsiString( );
    Codigo = new AnsiString( );
    Descricao = new AnsiString( );
    Defeito = new AnsiString( );

    try {
      *Retorno = "";

      //Impressora->Iniciar( Retorno );
      Impressora->Iniciar( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }

      for( j = 0; j < 2; j++ ) {

      Impressora->AbrirOrcamentoConserto( this->NumeroOrcamento, Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }

      for( i = 1; i <= this->OrcamentoInfo->Values["ItemQtd"].ToInt( ); i++ ) {
        *Preco = this->OrcamentoInfo->Values["Preco" + IntToStr( i )];
        *Codigo = this->OrcamentoInfo->Values["Codigo" + IntToStr( i )];
        *Descricao = this->OrcamentoInfo->Values["Descricao" + IntToStr( i )];
        *NumeroSerie = this->OrcamentoInfo->Values["NumeroSerie" + IntToStr( i )];
        *Defeito = this->OrcamentoInfo->Values["Defeito" + IntToStr( i )];
        Impressora->LancarItemOrcamento( Preco, Codigo, Descricao, NumeroSerie,
          Defeito, Retorno );
        if( !Retorno->IsEmpty( ) ) {
          throw( *Retorno );
        }
      }

      Impressora->TotalizarOrcamento( Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      
      Impressora->FecharOrcamento( &( this->OrcamentoInfo->Values["Vendedor"] ),
        &( this->OrcamentoInfo->Values["Cliente"] ), this->Telefone, Retorno );
      if( !Retorno->IsEmpty( ) ) {
        throw( *Retorno );
      }
      }
    }
    catch( String &Mensagem ) {
      *Retorno = Mensagem;
    }
  }
  __finally {
    Impressora->Finalizar( );
    delete Impressora;
    delete NumeroSerie;
    delete Preco;
    delete Codigo;
    delete Descricao;
    delete Defeito;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------

