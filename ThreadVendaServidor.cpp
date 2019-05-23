//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadVendaServidor.h"
#include "SecaoCritica.h"
#include "ImpressoraFiscal.h"
#include "ImpressoraMecaf.h"
#include "Dmod1.h"
#include "TefTecBan.h"
#include "TefVisanetRedecardAmex.h"
#include "FormTef.h"
#include "Main.h"
#include "Processos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TVendaServidorThread::TVendaServidorThread( bool CreateSuspended, TStringList *VendaInfo ): TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = false;
  this->Priority = tpNormal;

  this->VendaInfo = new TStringList( );
  this->VendaInfo->Assign( VendaInfo );
  this->CupomTef = new TStringList( );
  this->NumeroCupom = new AnsiString( );
  this->NomeCliente = new AnsiString( );
  this->Telefone = new AnsiString( );
  this->FormaPagamento = new AnsiString( );
  this->ValorPagamento = new AnsiString( );
  this->Erro = new AnsiString( );

  this->Resume( );
}
//---------------------------------------------------------------------------
__fastcall TVendaServidorThread::~TVendaServidorThread( void ) {

  delete this->VendaInfo;
  delete this->CupomTef;
  delete this->NumeroCupom;
  delete this->NomeCliente;
  delete this->Telefone;
  delete this->FormaPagamento;
  delete this->ValorPagamento;
  delete this->Erro;
}
//---------------------------------------------------------------------------
void __fastcall TVendaServidorThread::Execute( ) {

  TImpressoraFiscal *ImpressoraEcf;
  TConsigoQuery *Query;
  TDateTime *DataAtual;
  int NumeroCupom, i;

  *this->Erro = "";

    try {
      *this->Erro = "";
      if( this->VendaInfo->Values["Impressora"] == "1" ) {
        this->InserirVendaFiscal( );
      }
      else if( this->VendaInfo->Values["Impressora"] == "2" ) {
        this->InserirVenda( );
      }
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }

      if( ( this->VendaInfo->Values["TipoVenda"] == "Cartao Credito" ) ||
          ( this->VendaInfo->Values["TipoVenda"] == "Cartao Debito" ) ||
          ( this->VendaInfo->Values["TipoVenda"] == "Cheque Eletronico" ) ||
          ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 14 ) == "Cartao Debito " ) ||
          ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 15 ) == "Cartao Credito " ) ||
          ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 18 ) == "Cheque Eletronico " ) ) {

        this->CloseScreenSaver( );
        this->Synchronize( this->ExecutarTef );
        if( !this->Erro->IsEmpty( ) ) {
          throw( *this->Erro );
        }
      }
      else if( ( ( this->VendaInfo->Values["TipoVenda"] == "Cheque" ) ||
                 ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 7 ) == "A Prazo" ) ) &&
                 ( this->VendaInfo->Values["ConsultarCheque"] == "1" ) ) {

        this->CloseScreenSaver( );
        this->ConsultarCheque( );

        if( !this->Erro->IsEmpty( ) ) {
          throw( *this->Erro );
        }

      }
      else {
        if( this->VendaInfo->Values["Impressora"] == "1" ) {
          this->ImprimirVendaFiscal( );

          if( !this->Erro->IsEmpty( ) ) {
            throw( *this->Erro );
          }

        }
        else if( this->VendaInfo->Values["Impressora"] == "2" ) {
          this->ImprimirVenda( );

          if( !this->Erro->IsEmpty( ) ) {
            throw( *this->Erro );
          }

        }
      }
    }
    catch( String &Message ) {
      try {
        while( !*FormPrincipal->QuerySemaforo ) {
          Sleep( 500 );
        }
        SecaoCritica->Acquire( );
        *FormPrincipal->QuerySemaforo = false;
        SecaoCritica->Release( );

        Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );

        try {
          if( !this->NumeroCupom->IsEmpty( ) ) {
            Query->SQL->Clear( );
            if( this->VendaInfo->Values["Impressora"] == "1" ) {
              Query->SQL->Add( "BEGIN TRANSACTION" );
              Query->SQL->Add( "UPDATE Produtos" );
              Query->SQL->Add( "SET Produtos.Quantidade = Produtos.Quantidade + ( SELECT Vendem.Quantidade" );
              Query->SQL->Add( "                                                  FROM Vendem, Produtos" );
              Query->SQL->Add( "                                                  WHERE Vendem.Numero_nota = " + *this->NumeroCupom );
              Query->SQL->Add( "                                                  AND Vendem.Codigo = Produtos.Codigo )," );
              Query->SQL->Add( "Produtos.Quantidade_ = Produtos.Quantidade_ + ( SELECT Vendem.Quantidade" );
              Query->SQL->Add( "                                                FROM Vendem, Produtos" );
              Query->SQL->Add( "                                                WHERE Vendem.Numero_nota = " + *this->NumeroCupom );
              Query->SQL->Add( "                                                AND Vendem.Codigo = Produtos.Codigo )" );
              Query->SQL->Add( "  FROM Vendem, Produtos" );
              Query->SQL->Add( "  WHERE Vendem.Numero_nota = " + *this->NumeroCupom );
              Query->SQL->Add( "  AND Vendem.Codigo = Produtos.Codigo" );
              Query->SQL->Add( "DELETE FROM VENDEM" );
              Query->SQL->Add( "WHERE Vendem.Numero_nota = " + *this->NumeroCupom );
              Query->SQL->Add( "COMMIT TRANSACTION" );
              Query->Prepare( );
              Query->ExecSQL( );
            }
            else {
              Query->SQL->Add( "BEGIN TRANSACTION" );
              Query->SQL->Add( "UPDATE Produtos" );
              Query->SQL->Add( "SET Produtos.Quantidade = Produtos.Quantidade + ( SELECT Vendem2.Quantidade" );
              Query->SQL->Add( "                                                  FROM Vendem2, Produtos" );
              Query->SQL->Add( "                                                  WHERE Vendem2.Numero_nota = " + *this->NumeroCupom );
              Query->SQL->Add( "                                                  AND Vendem2.Codigo = Produtos.Codigo )" );
              Query->SQL->Add( "  FROM Vendem2, Produtos" );
              Query->SQL->Add( "  WHERE Numero_nota = " + *this->NumeroCupom );
              Query->SQL->Add( "  AND Vendem2.Codigo = Produtos.Codigo" );
              Query->SQL->Add( "DELETE FROM VENDEM2" );
              Query->SQL->Add( "WHERE Vendem2.Numero_nota = " + *this->NumeroCupom );
              Query->SQL->Add( "COMMIT TRANSACTION" );
              Query->Prepare( );
              Query->ExecSQL( );
            }
          }
        }
        catch( String &Message ) {
          *this->Erro = *this->Erro + Message;
        }
      }
      __finally {
        delete Query;

        SecaoCritica->Acquire( );
        *FormPrincipal->QuerySemaforo = true;
        SecaoCritica->Release( );
      }
    }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::ImprimirVendaFiscal( ) {

  TImpressoraFiscal *ImpressoraEcf;
  String *TipoVenda, *Subtr, *ValorTotal;
  String *Qtd, *PrecoUnit, *Codigo, *Descricao;
  bool *LeituraX;
  int i, Resposta = IDYES;


  try {
    while( !*FormPrincipal->ImpressoraEcfSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = false;
    SecaoCritica->Release( );

    LeituraX = new bool( false );
    TipoVenda = new AnsiString( );
    Subtr = new AnsiString( "0" );
    ValorTotal = new AnsiString( "000000000000000" );
    Qtd = new AnsiString( );
    PrecoUnit = new AnsiString( );
    Codigo = new AnsiString( );
    Descricao = new AnsiString( );
    ImpressoraEcf = new TImpressoraFiscal( );
    ImpressoraEcf->CarregaDll( this->Erro );

    try {
      *this->Erro = "";
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( this->Erro );
      }
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      ImpressoraEcf->AbreCupom( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      for( i = 1; i <= this->VendaInfo->Values["ItemQtd"].ToInt( ); i++ ) {
        *Qtd = this->VendaInfo->Values["Qtd" + IntToStr( i )];
        *PrecoUnit = this->VendaInfo->Values["PrecoUnit" + IntToStr( i )];
        *Codigo = this->VendaInfo->Values["Codigo" + IntToStr( i )];
        *Descricao = this->VendaInfo->Values["Descricao" + IntToStr( i )];
        ImpressoraEcf->LancaItem( Qtd, PrecoUnit, Codigo, Descricao, this->Erro );
        if( !this->Erro->IsEmpty( ) ) {
          throw( *this->Erro );
        }
      }
      ImpressoraEcf->TotalizaCupom( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      if( ( this->VendaInfo->Values["TipoVenda"] == "Dinheiro" ) ||
          ( this->VendaInfo->Values["TipoVenda"] == "Deposito em Conta" ) ) {
        *TipoVenda = "00";
      }
      else if( this->VendaInfo->Values["TipoVenda"] == "Cheque" ) {
        *TipoVenda = "01";
      }
      else if( ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 7 ) == "A Prazo" ) ||
               ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 14 ) == "Cartao Debito " ) ||
               ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 15 ) == "Cartao Credito " ) ||
               ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 18 ) == "Cheque Eletronico " ) ) {
        *TipoVenda = "04";
      }
      else if( this->VendaInfo->Values["TipoVenda"] == "Cartao Credito" ) {
        *TipoVenda = "03";
      }
      else if( ( this->VendaInfo->Values["TipoVenda"] == "Cartao Debito" ) ||
               ( this->VendaInfo->Values["TipoVenda"] == "Cheque Eletronico" ) ) {
        *TipoVenda = "02";
      }
      ImpressoraEcf->Pagamento( TipoVenda, &( this->VendaInfo->Values["ValorTotal"] ), Subtr, this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      ImpressoraEcf->Pagamento( TipoVenda, ValorTotal, Subtr, this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      ImpressoraEcf->FechaCupom( &( this->VendaInfo->Values["Vendedor"] ), this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      if( !this->CupomTef->Text.IsEmpty( ) ) {
        *this->Erro = "!";
        while( ( !this->Erro->IsEmpty( ) ) && ( Resposta == IDYES ) ) {
          *this->Erro = "";
          this->ImprimirEcfCupomTef( LeituraX );
          if( !this->Erro->IsEmpty( ) ) {
            *LeituraX = true;
            Resposta = Application->MessageBox( "Impressora Não Responde !\r\rTentar Novamente ?", "Vendas - TEF Discado", MB_YESNO | MB_ICONQUESTION );
          }
        }
      }
    }
    catch( String &Mensagem ) {
      *this->Erro = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;
    delete TipoVenda;
    delete Subtr;
    delete ValorTotal;
    delete LeituraX;
    delete Qtd;
    delete PrecoUnit;
    delete Codigo;
    delete Descricao;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraEcfSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::ImprimirEcfCupomTef( bool *LeituraX ) {

  TImpressoraFiscal *ImpressoraEcf;
  String *Relatorio, *Expandido;
  TFormMensagemTef *FormMensagemTef;
  int i, j;

  try {
    Relatorio = new AnsiString( "1" );
    Expandido = new AnsiString( "0" );
    ImpressoraEcf = new TImpressoraFiscal( );
    FormMensagemTef = new TFormMensagemTef( FormPrincipal );

    try {
      *this->Erro = "";
      ImpressoraEcf->CarregaDll( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      if( ( ImpressoraEcf->ObterStatusBit( 1 ) ) || ( ImpressoraEcf->ObterStatusBit( 2 ) ) ) {
        ImpressoraEcf->FechaCupomNaoFiscal( this->Erro );
        if( !this->Erro->IsEmpty( ) ) {
          throw( *this->Erro );
        }
      }
      if( *LeituraX ) {
        ImpressoraEcf->LeituraX( Relatorio, this->Erro );
      }
      else {
        ImpressoraEcf->AbreCupomNaoFiscalVinculado( this->Erro );
      }
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      for( j = 0; j < 2; j++ ) {
        for( i = 0; i < this->CupomTef->Count; i++ ) {
          ImpressoraEcf->LancaItemNaoFiscal( Expandido, &( this->CupomTef->Strings[i] ), this->Erro );
          if( !this->Erro->IsEmpty( ) ) {
            throw( *this->Erro );
          }
        }
      }
      ImpressoraEcf->FechaCupomNaoFiscal( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
    }
    catch( String &Mensagem ) {
      *this->Erro = Mensagem;
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;
    delete Relatorio;
    delete Expandido;
    FormMensagemTef->Close( );
    delete FormMensagemTef;
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::ImprimirVenda( ) {

  TImpressoraMecaf *Impressora;
  String *FormaPagamento, *Qtd, *PrecoUnit, *Codigo, *Descricao;
  int i, Resposta = IDYES;

  try {
    while( !*FormPrincipal->ImpressoraMecafSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = false;
    SecaoCritica->Release( );

    FormaPagamento = new AnsiString( );
    Impressora = new TImpressoraMecaf( );
    Impressora->CarregarDll( this->Erro );
    Qtd = new AnsiString( );
    PrecoUnit = new AnsiString( );
    Codigo = new AnsiString( );
    Descricao = new AnsiString( );

    try {
      *this->Erro = "";
      Impressora->Iniciar( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      Impressora->AbrirCupom( this->NumeroCupom, this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      for( i = 1; i <= this->VendaInfo->Values["ItemQtd"].ToInt( ); i++ ) {
        *Qtd = this->VendaInfo->Values["Qtd" + IntToStr( i )];
        *PrecoUnit = this->VendaInfo->Values["PrecoUnit" + IntToStr( i )];
        *Codigo = this->VendaInfo->Values["Codigo" + IntToStr( i )];
        *Descricao = this->VendaInfo->Values["Descricao" + IntToStr( i )];
        Impressora->LancarItem( Qtd, PrecoUnit, Codigo, Descricao, this->Erro );
        if( !this->Erro->IsEmpty( ) ) {
          throw( *this->Erro );
        }
      }
      Impressora->TotalizarCupom( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      if( this->VendaInfo->Values["TipoVenda"] == "Dinheiro" ) {
        *FormaPagamento = "Dinheiro";
        Impressora->Pagamento( FormaPagamento, NULL, NULL, NULL, this->Erro );
      }
      else if( this->VendaInfo->Values["TipoVenda"] == "Deposito em Conta" ) {
        *FormaPagamento = "Deposito em Conta";
        Impressora->Pagamento( FormaPagamento, NULL, NULL, NULL, this->Erro );
      }
      else if( this->VendaInfo->Values["TipoVenda"] == "Cheque" ) {
        *FormaPagamento = "Cheque";
        Impressora->Pagamento( FormaPagamento, NULL, NULL, NULL, this->Erro );
      }
      else if( this->VendaInfo->Values["TipoVenda"].SubString( 1, 7 ) == "A Prazo" ) {
        *FormaPagamento = "Financiado";
        Impressora->Pagamento( FormaPagamento, &( this->VendaInfo->Values["Entrada"] ),
          &( this->VendaInfo->Values["TipoVenda"].SubString( 9, 1 ) ),
          &( this->VendaInfo->Values["Parcela"] ), this->Erro );
      }
      else if( this->VendaInfo->Values["TipoVenda"].SubString( 1, 14 ) == "Cartao Debito " ) {
        *FormaPagamento = "Financiado";
        Impressora->Pagamento( FormaPagamento, &( this->VendaInfo->Values["Entrada"] ),
          &( this->VendaInfo->Values["TipoVenda"].SubString( 15, 1 ) ),
          &( this->VendaInfo->Values["Parcela"] ), this->Erro );
      }
      else if( this->VendaInfo->Values["TipoVenda"].SubString( 1, 15 ) == "Cartao Credito " ) {
        *FormaPagamento = "Financiado";
        Impressora->Pagamento( FormaPagamento, &( this->VendaInfo->Values["Entrada"] ),
          &( this->VendaInfo->Values["TipoVenda"].SubString( 16, 1 ) ),
          &( this->VendaInfo->Values["Parcela"] ), this->Erro );
      }
      else if( this->VendaInfo->Values["TipoVenda"].SubString( 1, 18 ) == "Cheque Eletronico " ) {
        *FormaPagamento = "Financiado";
        Impressora->Pagamento( FormaPagamento, &( this->VendaInfo->Values["Entrada"] ),
          &( this->VendaInfo->Values["TipoVenda"].SubString( 19, 1 ) ),
          &( this->VendaInfo->Values["Parcela"] ), this->Erro );
      }
      else if( this->VendaInfo->Values["TipoVenda"] == "Cartao Credito" ) {
        *FormaPagamento = "Cartao Credito";
        Impressora->Pagamento( FormaPagamento, NULL, NULL, NULL, this->Erro );
      }
      else if( ( this->VendaInfo->Values["TipoVenda"] == "Cartao Debito" ) ||
               ( this->VendaInfo->Values["TipoVenda"] == "Cheque Eletronico" ) ) {
        *FormaPagamento = "Cartao Debito";
        Impressora->Pagamento( FormaPagamento, NULL, NULL, NULL, this->Erro );
      }
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      Impressora->FecharCupom( &( this->VendaInfo->Values["Vendedor"] ),
        NomeCliente, Telefone, this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      if( !this->CupomTef->Text.IsEmpty( ) ) {
        *this->Erro = "!";
        while( ( !this->Erro->IsEmpty( ) ) && ( Resposta == IDYES ) ) {
          *this->Erro = "";
          this->ImprimirCupomTef( Impressora->Cupom, Impressora->Total );
          if( !this->Erro->IsEmpty( ) ) {
            Resposta = Application->MessageBox( "Impressora Não Responde !\r\rTentar Novamente ?", "Vendas - TEF Discado", MB_YESNO | MB_ICONQUESTION );
          }
        }
      }
    }
    catch( String &Mensagem ) {
      *this->Erro = Mensagem;
    }
  }
  __finally {
    Impressora->Finalizar( );
    delete Impressora;
    delete FormaPagamento;
    delete Qtd;
    delete PrecoUnit;
    delete Codigo;
    delete Descricao;

    SecaoCritica->Acquire( );
    *FormPrincipal->ImpressoraMecafSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::ImprimirCupomTef( String* Cupom, String* Total ) {

  TImpressoraMecaf *Impressora;
  int i;

  try {
    Impressora = new TImpressoraMecaf( );
    Impressora->CarregarDll( this->Erro );

    try {
      *this->Erro = "";
      Impressora->Iniciar( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      *Impressora->Cupom = *Cupom;
      *Impressora->Total = *Total;
      Impressora->AbrirCupomVinculado( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      Impressora->ImprimirTextoTEF( this->CupomTef, this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      Impressora->FecharCupomVinculado( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
    }
    catch( String &Mensagem ) {
      *this->Erro = Mensagem;
    }
  }
  __finally {
    Impressora->Finalizar( );
    delete Impressora;
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::InserirVendaFiscal( ) {

  TConsigoQuery *Query;
  TDateTime *DataAtual;
  TImpressoraFiscal *ImpressoraEcf;
  int NumeroCupom, i;

  try {
    while( !*FormPrincipal->QuerySemaforo ) {
      Sleep( 500 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->QuerySemaforo = false;
    SecaoCritica->Release( );

    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    DataAtual = new TDateTime( );
    ImpressoraEcf = new TImpressoraFiscal( );
    ImpressoraEcf->CarregaDll( this->Erro );

    try {
      *this->Erro = "";
      ImpressoraEcf->UltimoCupomFiscal( NumeroCupom, this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      else {
        *this->NumeroCupom = NumeroCupom;
      }
      if( !DataModuleQuery->consigo_BD->Connected ) {
        DataModuleQuery->consigo_BD->Open( );
      }
      for( i = 1; i <= this->VendaInfo->Values["ItemQtd"]; i++ ) {
        Query->SQL->Clear( );
        Query->SQL->Add( "BEGIN TRANSACTION" );
        Query->SQL->Add( "INSERT INTO Vendem( Numero_nota, Talao, Preco, Quantidade, Data, Tipo," );
        Query->SQL->Add( "RG_Vendedor, EERG_Vendedor, RG_Cliente, EERG_Cliente," );
        Query->SQL->Add( "Codigo, Numero_Serie, Entrada, Parcelas )" );
        Query->SQL->Add( "SELECT " + *this->NumeroCupom + ", '" + this->VendaInfo->Values["TipoNota"] + "'," );
        Query->SQL->Add( StringReplace( FloatToStr( StrToFloat( StringReplace( this->VendaInfo->Values["PrecoUnit" + IntToStr( i )], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) * StrToFloat( this->VendaInfo->Values["Qtd" + IntToStr( i )] ) ), ",", ".",  TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "," );
        Query->SQL->Add( this->VendaInfo->Values["Qtd" + IntToStr( i )] + ", '" + DataAtual->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:nn:ss" ) + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["TipoVenda"] + "'," );
        Query->SQL->Add( "Vendedores.RG, Vendedores.EERG, '" + this->VendaInfo->Values["Cliente"].SubString( 1, this->VendaInfo->Values["Cliente"].Length( ) - 2 ) + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["Cliente"].SubString( this->VendaInfo->Values["Cliente"].Length( ) - 1, 2 ) + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["Codigo" + IntToStr( i )] + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["NumeroSerie" + IntToStr( i )] + "'," );
        if( this->VendaInfo->Values["Entrada"].IsEmpty( ) ) {
          Query->SQL->Add( "0," );
        }
        else {
          Query->SQL->Add( StringReplace( StringReplace( this->VendaInfo->Values["Entrada"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ), ",", ".", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase )+ "," ) ;
        }
        if( this->VendaInfo->Values["Parcela"].IsEmpty( ) ) {
          Query->SQL->Add( "0" );
        }
        else {
          Query->SQL->Add( StringReplace( StringReplace( this->VendaInfo->Values["Parcela"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ), ",", ".", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) );
        }
        Query->SQL->Add( "FROM Vendedores" );
        Query->SQL->Add( "WHERE Vendedores.Nome LIKE '" + this->VendaInfo->Values["Vendedor"] + "'" );
        Query->SQL->Add( "UPDATE Produtos" );
        Query->SQL->Add( "SET Quantidade = Quantidade - '" + this->VendaInfo->Values["Qtd" + IntToStr( i )] + "'," );
        Query->SQL->Add( "Quantidade_ = Quantidade_ - ' " + this->VendaInfo->Values["Qtd" + IntToStr( i )] + "'" );
        Query->SQL->Add( "WHERE Codigo = '" + this->VendaInfo->Values["Codigo" + IntToStr( i )] + "'" );
        Query->SQL->Add( "COMMIT TRANSACTION" );
        Query->Prepare( );
        Query->ExecSQL( );
      }
    }
    catch( String &Message ) {
      *this->Erro = Message;
      if( DataModuleQuery->consigo_BD->InTransaction ) {
        DataModuleQuery->consigo_BD->Rollback( );
      }
      /*
      try {
        if( !this->NumeroCupom->IsEmpty( ) ) {
          Query->SQL->Clear( );
          Query->SQL->Add( "DELETE FROM VENDEM" );
          Query->SQL->Add( "WHERE Numero_nota = " + *this->NumeroCupom );
          Query->Prepare( );
          Query->ExecSQL( );
        }
      }
      catch( String &Message ) {
        *this->Erro = *this->Erro + Message;
      }
      */
    }
  }
  __finally {
    ImpressoraEcf->FechaSerial( );
    delete ImpressoraEcf;
    delete Query;
    delete DataAtual;

    SecaoCritica->Acquire( );
    *FormPrincipal->QuerySemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::InserirVenda( ) {

  TConsigoQuery *Query;
  TDateTime *DataAtual;
  int NumeroCupom, i;

  try {
    while( !*FormPrincipal->QuerySemaforo ) {
      Sleep( 500 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->QuerySemaforo = false;
    SecaoCritica->Release( );

    Query = new TConsigoQuery( &( DataModuleQuery->consigo_BD->DatabaseName ), DataModuleQuery );
    DataAtual = new TDateTime( );

    try {
      *this->Erro = "";
      if( this->VendaInfo->Values["Cliente"].SubString( 1, this->VendaInfo->Values["Cliente"].Length( ) - 2 ) != "Sem RG" ) {
        Query->SQL->Add( "SELECT Nome, Telefone" );
        Query->SQL->Add( "FROM Clientes" );
        Query->SQL->Add( "WHERE RG = '" + this->VendaInfo->Values["Cliente"].SubString( 1, this->VendaInfo->Values["Cliente"].Length( ) - 2 ) + "'" );
        Query->SQL->Add( "AND   EERG = '" + this->VendaInfo->Values["Cliente"].SubString( this->VendaInfo->Values["Cliente"].Length( ) - 1, 2 ) + "'" );
        Query->Prepare( );
        Query->Open( );
        if( !Query->IsEmpty( ) ) {
          *this->NomeCliente = Query->FieldByName( "Nome" )->AsString;
          *this->Telefone = Query->FieldByName( "Telefone" )->AsString;
        }
        Query->Close( );
      }

      Query->SQL->Clear( );
      Query->SQL->Add( "SELECT MAX( Numero_nota ) + 1 AS NovoNumeroNota" );
      Query->SQL->Add( "FROM VENDEM2" );
      Query->Prepare( );
      Query->Open( );
      Query->First( );
      *this->NumeroCupom = Query->FieldByName( "NovoNumeroNota" )->AsString;
      Query->Close( );

      for( i = 1; i <= this->VendaInfo->Values["ItemQtd"]; i++ ) {
        Query->SQL->Clear( );
        Query->SQL->Add( "BEGIN TRANSACTION" );
        Query->SQL->Add( "INSERT INTO Vendem2( Numero_nota, Talao, Preco, Quantidade, Data, Tipo," );
        Query->SQL->Add( "RG_Vendedor, EERG_Vendedor, RG_Cliente, EERG_Cliente," );
        Query->SQL->Add( "Codigo, Numero_Serie, Entrada, Parcelas )" );
        Query->SQL->Add( "SELECT " + *this->NumeroCupom + ", '" + this->VendaInfo->Values["TipoNota"] + "'," );
        Query->SQL->Add( StringReplace( FloatToStr( StrToFloat( StringReplace( this->VendaInfo->Values["PrecoUnit" + IntToStr( i )], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) * StrToFloat( this->VendaInfo->Values["Qtd" + IntToStr( i )] ) ), ",", ".",  TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) + "," );
        Query->SQL->Add( this->VendaInfo->Values["Qtd" + IntToStr( i )] + ", '" + DataAtual->CurrentDateTime( ).FormatString( "yyyy/mm/dd hh:nn:ss" ) + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["TipoVenda"] + "'," );
        Query->SQL->Add( "Vendedores.RG, Vendedores.EERG, '" + this->VendaInfo->Values["Cliente"].SubString( 1, this->VendaInfo->Values["Cliente"].Length( ) - 2 ) + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["Cliente"].SubString( this->VendaInfo->Values["Cliente"].Length( ) - 1, 2 ) + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["Codigo" + IntToStr( i )] + "'," );
        Query->SQL->Add( "'" + this->VendaInfo->Values["NumeroSerie" + IntToStr( i )] + "'," );
        if( this->VendaInfo->Values["Entrada"].IsEmpty( ) ) {
          Query->SQL->Add( "0," );
        }
        else {
          Query->SQL->Add( StringReplace( StringReplace( this->VendaInfo->Values["Entrada"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ), ",", ".", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase )+ "," ) ;
        }
        if( this->VendaInfo->Values["Parcela"].IsEmpty( ) ) {
          Query->SQL->Add( "0" );
        }
        else {
          Query->SQL->Add( StringReplace( StringReplace( this->VendaInfo->Values["Parcela"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ), ",", ".", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) );
        }
        Query->SQL->Add( "FROM Vendedores" );
        Query->SQL->Add( "WHERE Vendedores.Nome LIKE '" + this->VendaInfo->Values["Vendedor"] + "'" );
        Query->SQL->Add( "UPDATE Produtos" );
        Query->SQL->Add( "SET Quantidade = Quantidade - '" + this->VendaInfo->Values["Qtd" + IntToStr( i )] + "'" );
        Query->SQL->Add( "WHERE Codigo = '" + this->VendaInfo->Values["Codigo" + IntToStr( i )] + "'" );
        Query->SQL->Add( "COMMIT TRANSACTION" );
        Query->Prepare( );
        Query->ExecSQL( );
      }
    }
    catch( Exception &e ) {
      *this->Erro = e.Message;
      if( DataModuleQuery->consigo_BD->InTransaction ) {
        DataModuleQuery->consigo_BD->Rollback( );
      }
      /*
      try {
        if( !this->NumeroCupom->IsEmpty( ) ) {
          Query->SQL->Clear( );
          Query->SQL->Add( "DELETE FROM VENDEM2" );
          Query->SQL->Add( "WHERE Numero_nota = " + *this->NumeroCupom );
          Query->Prepare( );
          Query->ExecSQL( );
        }
      }
      catch( Exception &e ) {
        *this->Erro = *this->Erro + e.Message;
      }
      */
    }
  }
  __finally {
    delete Query;
    delete DataAtual;

    SecaoCritica->Acquire( );
    *FormPrincipal->QuerySemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::ConsultarCheque( ) {

  TTefTecBan *TecBan;
  String *Mensagem;
  int Resposta;
  TFormMensagemTef *FormMensagemTef;

  try {
    while( !*FormPrincipal->TefSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->TefSemaforo = false;
    SecaoCritica->Release( );

    Mensagem = new AnsiString( );
    TecBan = new TTefTecBan( );
    FormMensagemTef = new TFormMensagemTef( FormPrincipal );

    try {
      TecBan->Atv( this->Erro );
      if( !this->Erro->IsEmpty( ) ) {
        throw( *this->Erro );
      }
      TecBan->Chq( &( this->VendaInfo->Values["ValorTotal"] ), this->Erro, this->CupomTef );
      SetForegroundWindow( Application->Handle );
      if( this->Erro->IsEmpty( ) ) {
        Application->MessageBox( "Consulta do Cheque Aprovada !", "Vendas - Consulta de Cheque", MB_OK | MB_ICONWARNING );
      }
      else if( ( !this->Erro->IsEmpty( ) ) && ( !this->CupomTef->Text.IsEmpty( ) ) ) {
        FormMensagemTef->LabelMensagemTEF->Caption = *this->Erro;
        FormMensagemTef->Show( );
        FormMensagemTef->Update( );
        *this->Erro = "";
      }
      else {
        *Mensagem = *this->Erro + "\r\rDeseja Continuar com a Venda ?";
        if( Application->MessageBox( Mensagem->c_str( ), "Vendas - Consulta de Cheque", MB_YESNO | MB_ICONERROR ) == IDYES ) {
          *this->Erro = "";
        }
      }
      if( this->Erro->IsEmpty( ) ) {
        if( this->VendaInfo->Values["Impressora"] == "1" ) {
          this->ImprimirVendaFiscal( );
        }
        else if( this->VendaInfo->Values["Impressora"] == "2" ) {
          this->ImprimirVenda( );
        }
      }
      if( !this->Erro->IsEmpty( ) ) {
        Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONWARNING );
        if( ( !TecBan->NumeroTransacao->IsEmpty( ) ) &&
            ( !this->Erro->IsEmpty( ) ) ) {
          if( TecBan->Ncn( this->Erro ) == true ) {
            SetForegroundWindow( Application->Handle );
            Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONWARNING );
          }
        }
      }
      else {
        TecBan->Cnf( this->Erro );
        SetForegroundWindow( Application->Handle );
      }
    }
    catch( String &Mensagem ) {
      *this->Erro = Mensagem;
    }
  }
  __finally {
    delete FormMensagemTef;
    delete Mensagem;
    delete TecBan;

    SecaoCritica->Acquire( );
    *FormPrincipal->TefSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TVendaServidorThread::ExecutarTef( ) {

  String *ValorCartao, *Mensagem, *RetornoImpressora;
  TStringList *CupomTotalTef;
  TList *TefVisanetList, *TefTecBanList, *CupomTefList;
  TTefTecBan *TefTecBan;
  TTefVisaNetRedeCardAmex *TefVisaNetRedeCardAmex;
  TFormMensagemTef *FormMensagemTef;
  bool *NcnOk;
  int i;

  try {
    while( !*FormPrincipal->TefSemaforo ) {
      Sleep( 1000 );
    }
    SecaoCritica->Acquire( );
    *FormPrincipal->TefSemaforo = false;
    SecaoCritica->Release( );

    Mensagem = new AnsiString( );
    CupomTotalTef = new TStringList( );
    CupomTotalTef->Sorted = false;
    FormaPagamento = new AnsiString( this->VendaInfo->Values["TipoVenda"] );
    CupomTefList = new TList( );
    TefTecBanList = new TList( );
    TefVisanetList = new TList( );
    TefTecBan = new TTefTecBan( );
    TefVisaNetRedeCardAmex = new TTefVisaNetRedeCardAmex( );
    ValorCartao = new AnsiString( StringReplace( this->VendaInfo->Values["ValorCartao"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) );
    ValorPagamento = new AnsiString( StringReplace( this->VendaInfo->Values["ValorCartao"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) );
    NcnOk = new bool( false );
    RetornoImpressora = new AnsiString( );
    FormMensagemTef = new TFormMensagemTef( FormPrincipal );
    /*
    while( FormMensagemTef->Canvas->LockCount != 0 ) {
        FormMensagemTef->Canvas->Unlock( );
    }
    FormMensagemTef->Canvas->Lock( );
    while( FormPrincipal->Canvas->LockCount != 0 ) {
        FormPrincipal->Canvas->Unlock( );
    }
    FormPrincipal->Canvas->Lock( );
    */
    try {
      DecimalSeparator = ',';
      ThousandSeparator = '.';

      if( ( ValorCartao->ToDouble( ) == StringReplace( this->VendaInfo->Values["ValorTotal"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) ) ||
          ( ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 14 ) == "Cartao Debito " ) ||
            ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 15 ) == "Cartao Credito " ) ||
            ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 18 ) == "Cheque Eletronico " ) ) ) {
        if( ( this->VendaInfo->Values["TipoVenda"] == "Cheque Eletronico" ) ||
            ( this->VendaInfo->Values["TipoVenda"].SubString( 1, 18 ) == "Cheque Eletronico " ) ) {
          TefTecBan->Atv( this->Erro );
          if( !this->Erro->IsEmpty( ) ) {
            throw( "" );
          }
          if( this->VendaInfo->Values["ConsultarCheque"] == "1" ) {
            TefTecBan->Chq( &( this->VendaInfo->Values["ValorTotal"] ), this->Erro, this->CupomTef );
            SetForegroundWindow( Application->Handle );
            if( this->Erro->IsEmpty( ) ) {
              Application->MessageBox( "Consulta do Cheque Aprovada !", "Vendas - Consulta de Cheque", MB_OK | MB_ICONWARNING );
            }
            else {
              if( !this->CupomTef->Text.IsEmpty( ) ) {
                if( !TefTecBan->NumeroTransacao->IsEmpty( ) ) {
                  TefTecBan->Ncn( this->Erro );
                }
              }
              *Mensagem = *this->Erro + "\r\rDeseja Continuar com a Venda ?";
              if( Application->MessageBox( Mensagem->c_str( ), "Vendas - Consulta de Cheque", MB_YESNO | MB_ICONERROR ) == IDYES ) {
                *this->Erro = "";
              }
              else {
                throw( "" );
              }
            }
          }
          TefTecBan->Crt( ValorCartao, this->Erro, this->CupomTef );
          SetForegroundWindow( Application->Handle );
          if( ( !this->Erro->IsEmpty( ) ) && ( !this->CupomTef->Text.IsEmpty( ) ) ) {
            FormMensagemTef->LabelMensagemTEF->Caption = *this->Erro;
            FormMensagemTef->Show( );
            FormMensagemTef->Update( );
            //Sleep( 5000 );
            //*this->Erro = "";
            if( this->VendaInfo->Values["Impressora"] == "1" ) {
              this->ImprimirVendaFiscal( );
            }
            else if( this->VendaInfo->Values["Impressora"] == "2" ) {
              this->ImprimirVenda( );
            }
          }
          if( !this->Erro->IsEmpty( ) ) {
            Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONWARNING );
            if( ( !TefTecBan->ValorTransacao->IsEmpty( ) ) &&
                ( !TefTecBan->NumeroTransacao->IsEmpty( ) ) &&
                ( !this->Erro->IsEmpty( ) ) ) {
              if( TefTecBan->Ncn( this->Erro ) == true ) {
                SetForegroundWindow( Application->Handle );
                Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONWARNING );
              }
            }
          }
          else {
            TefTecBan->Cnf( this->Erro );
            SetForegroundWindow( Application->Handle );
          }
        }
        else {
          if( this->VendaInfo->Values["ConsultarCheque"] == "1" ) {
            TefTecBan->Atv( this->Erro );
            if( !this->Erro->IsEmpty( ) ) {
              throw( "" );
            }
            TefTecBan->Chq( &( this->VendaInfo->Values["ValorTotal"] ), this->Erro, this->CupomTef );
            SetForegroundWindow( Application->Handle );
            if( this->Erro->IsEmpty( ) ) {
              Application->MessageBox( "Consulta do Cheque Aprovada !", "Vendas - Consulta de Cheque", MB_OK | MB_ICONWARNING );
              TefTecBan->Cnf( this->Erro );
              SetForegroundWindow( Application->Handle );
            }
            else {
              if( !this->CupomTef->Text.IsEmpty( ) ) {
                if( !TefTecBan->NumeroTransacao->IsEmpty( ) ) {
                  TefTecBan->Ncn( this->Erro );
                }
              }
              *Mensagem = *this->Erro + "\r\rDeseja Continuar com a Venda ?";
              if( Application->MessageBox( Mensagem->c_str( ), "Vendas - Consulta de Cheque", MB_YESNO | MB_ICONERROR ) == IDYES ) {
                *this->Erro = "";
              }
              else {
                throw( "" );
              }
            }
          }
          TefVisaNetRedeCardAmex->Atv( this->Erro );
          if( !this->Erro->IsEmpty( ) ) {
            throw( "" );
          }
          TefVisaNetRedeCardAmex->Crt( ValorCartao, this->Erro, this->CupomTef );
          SetForegroundWindow( Application->Handle );
          if( ( !this->Erro->IsEmpty( ) ) && ( !this->CupomTef->Text.IsEmpty( ) ) ) {
            FormMensagemTef->LabelMensagemTEF->Caption = *this->Erro;
            FormMensagemTef->Show( );
            FormMensagemTef->Update( );
            //Sleep( 5000 );
            //*this->Erro = "";
            if( this->VendaInfo->Values["Impressora"] == "1" ) {
              this->ImprimirVendaFiscal( );
            }
            else if( this->VendaInfo->Values["Impressora"] == "2" ) {
              this->ImprimirVenda( );
            }
          }
          if( !this->Erro->IsEmpty( ) ) {
            Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONWARNING );
            if( ( !TefVisaNetRedeCardAmex->ValorTransacao->IsEmpty( ) ) &&
                ( !TefVisaNetRedeCardAmex->NumeroTransacao->IsEmpty( ) ) &&
                ( !this->Erro->IsEmpty( ) ) ) {
              if( TefVisaNetRedeCardAmex->Ncn( this->Erro ) == true ) {
                SetForegroundWindow( Application->Handle );
                Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONWARNING );
              }
            }
          }
          else {
            TefVisaNetRedeCardAmex->Cnf( this->Erro );
            SetForegroundWindow( Application->Handle );
          }
        }
      }
      else {
        *ValorCartao = 0;
        while( StrToFloat( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) < StrToFloat( StringReplace( this->VendaInfo->Values["ValorTotal"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) ) {
          if( ( *this->FormaPagamento == "Cartao Debito" ) ||
              ( *this->FormaPagamento == "Cartao Credito" ) ) {
            TefVisanetList->Add( new TTefVisaNetRedeCardAmex( ) );
            TefVisaNetRedeCardAmex = (TTefVisaNetRedeCardAmex*)TefVisanetList->Items[TefVisanetList->Count - 1];
            TefVisaNetRedeCardAmex->Atv( this->Erro );
            if( this->Erro->IsEmpty( ) ) {
              CupomTefList->Add( new TStringList( ) );
              this->CupomTef = (TStringList*)CupomTefList->Items[CupomTefList->Count - 1];
              TefVisaNetRedeCardAmex->Crt( ValorPagamento, this->Erro, this->CupomTef );
            }
            SetForegroundWindow( Application->Handle );
            if( ( !this->Erro->IsEmpty( ) ) && ( this->CupomTef->Text.IsEmpty( ) ) ) {
              Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONERROR );
            }
            else if( ( !this->Erro->IsEmpty( ) ) && ( !this->CupomTef->Text.IsEmpty( ) ) ) {
              this->BufferTefCopiar( );
              TefVisaNetRedeCardAmex->Cnf( this->Erro );
              SetForegroundWindow( Application->Handle );
              if( !this->Erro->IsEmpty( ) ) {
                Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONERROR );
              }
              else {
                *ValorCartao = FloatToStrF( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) + StringReplace( *ValorPagamento, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ), ffFixed, 15, 2 );
              }
            }
          }
          else if( *this->FormaPagamento == "Cheque Eletronico" ) {
            TefTecBanList->Add( new TTefTecBan( ) );
            TefTecBan = (TTefTecBan*)TefTecBanList->Items[TefTecBanList->Count - 1];
            TefTecBan->Atv( this->Erro );
            if( this->Erro->IsEmpty( ) ) {
              CupomTefList->Add( new TStringList( ) );
              this->CupomTef = (TStringList*)CupomTefList->Items[CupomTefList->Count - 1];
              TefTecBan->Crt( ValorPagamento, this->Erro, this->CupomTef );
            }
            SetForegroundWindow( Application->Handle );
            if( ( !this->Erro->IsEmpty( ) ) && ( this->CupomTef->Text.IsEmpty( ) ) ) {
              Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONERROR );
            }
            else if( ( !this->Erro->IsEmpty( ) ) && ( !this->CupomTef->Text.IsEmpty( ) ) ) {
              this->BufferTefCopiar( );
              TefTecBan->Cnf( this->Erro );
              SetForegroundWindow( Application->Handle );
              if( !this->Erro->IsEmpty( ) ) {
                Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONERROR );
              }
              else {
                *ValorCartao = FloatToStrF( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) + StringReplace( *ValorPagamento, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ), ffFixed, 15, 2 );
              }
            }
          }
          if( StrToFloat( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) != StrToFloat( StringReplace( this->VendaInfo->Values["ValorTotal"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) ) {
            do {
              SetForegroundWindow( Application->Handle );
//****        this->Synchronize( this->CapturarFormaPagamento );
              this->CapturarFormaPagamento( );
              if( ( *this->FormaPagamento == "Dinheiro" ) || ( *this->FormaPagamento == "Cheque" ) ) {
                *ValorPagamento = "0";
                *ValorCartao = this->VendaInfo->Values["ValorTotal"];
              }
              if( ( *this->FormaPagamento != "Dinheiro" ) && ( *this->FormaPagamento != "Cheque" ) ) {
                if( ( StrToFloat( StringReplace( *ValorPagamento, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) + StrToFloat( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) ) > StrToFloat( StringReplace( this->VendaInfo->Values["ValorTotal"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) ) {
                  Application->MessageBox( "O Valor Digitado NÃO pode ser Maior que o Total da Venda !", "Vendas - TEF Discado", MB_OK | MB_ICONERROR );
                }
              }
            } while( ( StrToFloat( StringReplace( *ValorPagamento, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) + StrToFloat( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) ) > StrToFloat( StringReplace( this->VendaInfo->Values["ValorTotal"], ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ) ) );
          }
        }
        for( i = 0; i < CupomTefList->Count; i++ ) {
          this->CupomTef = (TStringList*)CupomTefList->Items[i];
          if( !this->CupomTef->Text.IsEmpty( ) ) {
            CupomTotalTef->Text = CupomTotalTef->Text + this->CupomTef->Text;
          }
        }
        this->CupomTef->Text = CupomTotalTef->Text;
        //*this->Erro = "";
        //Sleep( 1000 );

        if( this->VendaInfo->Values["Impressora"] == "1" ) {
          this->ImprimirVendaFiscal( );
        }
        else if( this->VendaInfo->Values["Impressora"] == "2" ) {
          this->ImprimirVenda( );
        }

        if( this->Erro->IsEmpty( ) ) {
          this->BufferTefApagar( );
        }
        else {
          *RetornoImpressora = *this->Erro;
          for( i = 0; i < TefVisanetList->Count; i++ ) {
            TefVisaNetRedeCardAmex = (TTefVisaNetRedeCardAmex*)TefVisanetList->Items[i];
            if( !TefVisaNetRedeCardAmex->NumeroTransacao->IsEmpty( ) ) {
              *NcnOk = TefVisaNetRedeCardAmex->Ncn( this->Erro );
              Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONERROR );
              if( *NcnOk ) {
                *this->Erro = "";
              }
            }
          }
          for( i = 0; i < TefTecBanList->Count; i++ ) {
            TefTecBan = (TTefTecBan*)TefTecBanList->Items[i];
            if( !TefTecBan->NumeroTransacao->IsEmpty( ) ) {
              *NcnOk = TefTecBan->Ncn( this->Erro );
              Application->MessageBox( this->Erro->c_str( ), "Vendas - TEF Discado", MB_OK | MB_ICONERROR );
              if( *NcnOk ) {
                *this->Erro = "";
              }
            }
          }
          if( this->Erro->IsEmpty( ) ) {
            this->BufferTefApagar( );
          }
          if( this->Erro->IsEmpty( ) ) {
            *this->Erro = *RetornoImpressora;
          }
        }
      }
    }
    catch( ... ) {

    }
  }
  __finally {
    //FormMensagemTef->Canvas->Unlock( );
    delete FormMensagemTef;
    //FormPrincipal->Canvas->Unlock( );
    delete RetornoImpressora;
    delete NcnOk;
    delete ValorCartao;
    delete CupomTefList;
    delete TefTecBanList;
    delete TefVisanetList;
    delete TefTecBan;
    delete TefVisaNetRedeCardAmex;
    delete Mensagem;
    delete CupomTotalTef;

    SecaoCritica->Acquire( );
    *FormPrincipal->TefSemaforo = true;
    SecaoCritica->Release( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TVendaServidorThread::CapturarFormaPagamento( ) {

  try {
    this->FormFormaPagamento = new TFormFormaPagamento( FormPrincipal );
    /*
    while( this->FormFormaPagamento->Canvas->LockCount != 0 ) {
      this->FormFormaPagamento->Canvas->Unlock( );
    }
    this->FormFormaPagamento->Canvas->Lock( );
    while( FormPrincipal->Canvas->LockCount != 0 ) {
      FormPrincipal->Canvas->Unlock( );
    }
    FormPrincipal->Canvas->Lock( );
    */
    if( FormFormaPagamento->ShowModal( ) == 1 ) {
      *this->FormaPagamento = FormFormaPagamento->ComboBoxFormaPagamento->Text;
      if( ( *this->FormaPagamento == "Cartao Debito" ) || ( *this->FormaPagamento == "Cartao Credito" ) ||
          ( *this->FormaPagamento == "Cheque Eletronico" ) ) {
        *this->ValorPagamento = FormFormaPagamento->EditValorFormaPagamento->Text;
      }
    }
  }
  __finally {
    //this->FormFormaPagamento->Canvas->Unlock( );
    this->FormFormaPagamento = NULL;
    delete this->FormFormaPagamento;
    //FormPrincipal->Canvas->Unlock( );
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::BufferTefCopiar( ) {

  int i = 1;
  String *ArquivoTemp;

  try {
    ArquivoTemp = new AnsiString( );

    try {
      *this->Erro = "";
      if( FileExists( "C:\\tef_dial\\resp\\IntPos.001" ) ) {
        while( FileExists( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) ) ) {
          i++;
        }
        *ArquivoTemp = "C:\\tef_temp\\IntPos.00" + IntToStr( i );
        if( !CopyFile( "C:\\tef_dial\\resp\\IntPos.001", ArquivoTemp->c_str( ), true ) ) {
          throw( "Não Foi Possível Copiar o Arquivo Temporário TEF !" );
        }
      }
      i = 1;
      if( FileExists( "C:\\tef_disc\\resp\\IntPos.001" ) ) {
        while( FileExists( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) ) ) {
          i++;
        }
        *ArquivoTemp = "C:\\tef_temp\\IntPos.00" + IntToStr( i );
        if( !CopyFile( "C:\\tef_disc\\resp\\IntPos.001", ArquivoTemp->c_str( ), true ) ) {
          throw( "Não Foi Possível Copiar o Arquivo Temporário TEF !" );
        }
      }
    }
    catch( String &Error ) {
      *this->Erro = Error;
    }
  }
  __finally {
    delete ArquivoTemp;
  }
}
//---------------------------------------------------------------------------
void TVendaServidorThread::BufferTefApagar( ) {

  int i = 1;

  try {
    *this->Erro = "";
    while( FileExists( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) ) ) {
      DeleteFile( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) );
      i++;
    }
  }
  catch( String &Error ) {
    *this->Erro = Error;
  }
}
//---------------------------------------------------------------------------
void __fastcall TVendaServidorThread::CloseScreenSaver( void ) {
  
  if( GetProcessPid( "sstext3d.scr" ) != NULL ) {
    SendMessage( Application->Handle, WM_SYSCOMMAND, SC_SCREENSAVE, WM_CLOSE );
  }
}
//---------------------------------------------------------------------------
