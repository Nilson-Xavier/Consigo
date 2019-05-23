//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThreadVenda.h"
#include "Main.h"
#include "ClientSocket.h"
#include "Dmod1.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TVendaThread::TVendaThread( bool CreateSuspended, String* Impressora ): TThread( CreateSuspended ) {

  this->Suspended = true;
  this->FreeOnTerminate = true;
  this->Priority = tpNormal;
  this->Impressora = new AnsiString( *Impressora );
  this->Resume( );
}
//------------------------------------------------------------------------
__fastcall TVendaThread::~TVendaThread( void ) {

  delete this->Impressora;
}
//------------------------------------------------------------------------
void __fastcall TVendaThread::Execute( ) {

  TStringList *Request;
  String *ValorCartao, *Garantia;
  TConsigoClientSocket *ConexaoServidor;
  int i;

  try {
    this->Synchronize( this->BotaoDesabilitar );

    ValorCartao = new AnsiString( );
    Garantia = new AnsiString( " Garantia " );
    Request = new TStringList( );
    Request->Sorted = false;

    try {
      Request->Append( "IP=" + *FormPrincipal->ServerSocketIP );
      Request->Append( "Funcao=Vender" );
      Request->Append( "TipoNota=" + FormPrincipal->ComboBoxTipoNotaFiscal->Text );
      Request->Append( "Vendedor=" + FormPrincipal->ComboBoxVendedor->Text );
      if( ( FormPrincipal->ComboBoxRgCnpj->Text == "Sem RG" ) ||
          ( FormPrincipal->ComboBoxRgCnpj->Text.IsEmpty( ) ) ) {
        Request->Append( "Cliente=Sem RGSP" );
      }
      else {
        Request->Append( "Cliente=" + FormPrincipal->ComboBoxRgCnpj->Text + FormPrincipal->ComboBoxEERG->Text );
      }
      Request->Append( "TipoVenda=" + FormPrincipal->ComboBoxTipoVenda->Text );
      if( ( Request->Values["TipoVenda"] == "Cheque" ) ||
          ( Request->Values["TipoVenda"].SubString( 1, 7 ) == "A Prazo" ) ||
          ( Request->Values["TipoVenda"].SubString( 1, 14 ) == "Cartao Debito " ) ||
          ( Request->Values["TipoVenda"].SubString( 1, 15 ) == "Cartao Credito " ) ||
          ( Request->Values["TipoVenda"].SubString( 1, 18 ) == "Cheque Eletronico " ) ) {
        if( Application->MessageBox( "Deseja Consultar o Cheque ?", "Vendas",
                                     MB_YESNO | MB_ICONQUESTION ) == ID_YES ) {
          Request->Append( "ConsultarCheque=1" );
        }
        else {
          Request->Append( "ConsultarCheque=0" );
        }
      }
      if( ( !FormPrincipal->EditEntrada->Text.IsEmpty( ) ) && ( !FormPrincipal->EditParcela->Text.IsEmpty( ) ) ) {
        Request->Append( "Entrada=" + FormPrincipal->EditEntrada->Text );
        Request->Append( "Parcela=" + FormPrincipal->EditParcela->Text );
      }
      Request->Append( "Impressora=" + *this->Impressora );
      Request->Append( "ValorTotal=" + FormPrincipal->EditTotal2->Text );
      if( ( Request->Values["TipoVenda"] == "Cartao Credito" ) ||
          ( Request->Values["TipoVenda"] == "Cartao Debito" ) ||
          ( Request->Values["TipoVenda"] == "Cheque Eletronico" ) ||
          ( Request->Values["TipoVenda"].SubString( 1, 14 ) == "Cartao Debito " ) ||
          ( Request->Values["TipoVenda"].SubString( 1, 15 ) == "Cartao Credito " ) ||
          ( Request->Values["TipoVenda"].SubString( 1, 18 ) == "Cheque Eletronico " ) ) {

        do {
          this->CapturarValorCartao( ValorCartao );
          DecimalSeparator = ',';
          ThousandSeparator = '.';
          if( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) > StringReplace( FormPrincipal->EditTotal2->Text, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) ) {
            Application->MessageBox( "O Valor do Cartão Não Pode Ser Maior que o Total da Venda !", "Vendas", MB_OK | MB_ICONWARNING );
          }
        } while( StringReplace( *ValorCartao, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) > StringReplace( FormPrincipal->EditTotal2->Text, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) );
        Request->Append( "ValorCartao=" + *ValorCartao );
      }
      Request->Append( "ItemQtd=" + IntToStr( FormPrincipal->StrGridVendaProduto->RowCount - 1 ) );
      for( i = 1; i < FormPrincipal->StrGridVendaProduto->RowCount; i++ ) {

        Request->Append( "Codigo" + IntToStr( i ) + "=" + FormPrincipal->StrGridVendaProduto->Cells[5][i] );
        Request->Append( "Qtd" + IntToStr( i ) + "=" + FormPrincipal->StrGridVendaProduto->Cells[2][i] );
        Request->Append( "PrecoUnit" + IntToStr( i ) + "=" + FormPrincipal->StrGridVendaProduto->Cells[3][i] );
        if( !FormPrincipal->StrGridVendaProduto->Cells[7][i].IsEmpty( ) ) {
          Request->Append( "Descricao" + IntToStr( i ) + "=" + FormPrincipal->StrGridVendaProduto->Cells[0][i] + " " +
                            FormPrincipal->StrGridVendaProduto->Cells[1][i] + *Garantia + FormPrincipal->StrGridVendaProduto->Cells[7][i] );
        }
        else {
          Request->Append( "Descricao" + IntToStr( i ) + "=" + FormPrincipal->StrGridVendaProduto->Cells[0][i] + " " +
                           FormPrincipal->StrGridVendaProduto->Cells[1][i] );
        }
        Request->Append( "NumeroSerie" + IntToStr( i ) + "=" + FormPrincipal->StrGridVendaProduto->Cells[6][i] );
      }

      ConexaoServidor = new TConsigoClientSocket( Application, Request, FormPrincipal->ServerSocketIP );
    }
    catch( Exception &e ) {
      Application->MessageBox( e.Message.c_str( ), "Vendas", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    delete ValorCartao;
    delete Garantia;
    delete Request;

    this->Synchronize( this->BotaoAbilitar );
  }
}
//------------------------------------------------------------------------
void TVendaThread::CapturarValorCartao( String* &Valor ) {

  try {
    this->FormValorCartao = new TFormValorCartao( FormPrincipal );

    this->FormValorCartao->EditValorCartao->Text = FormPrincipal->EditTotal2->Text;
    if( this->FormValorCartao->ShowModal( ) == 1 ) {
      *Valor = this->FormValorCartao->EditValorCartao->Text;
    }
  }
  __finally {
    this->FormValorCartao = NULL;
    delete this->FormValorCartao;
  }
}
//------------------------------------------------------------------------
void __fastcall TVendaThread::BotaoDesabilitar( ) {

  FormPrincipal->BitBtnConfirmarProduto->Enabled = false;
  FormPrincipal->BitBtnCancelarProduto->Enabled = false;
  FormPrincipal->BitBtnConfirmarVenda->Enabled = false;
  FormPrincipal->BitBtnCancelarVenda->Enabled = false;
  FormPrincipal->StrGridVendaProduto->Enabled = false;
  FormPrincipal->EditTotal2->Enabled = false;
}
//------------------------------------------------------------------------
void __fastcall TVendaThread::BotaoAbilitar( ) {

  FormPrincipal->BitBtnConfirmarProduto->Enabled = true;
  FormPrincipal->BitBtnCancelarProduto->Enabled = true;
  FormPrincipal->BitBtnConfirmarVenda->Enabled = true;
  FormPrincipal->BitBtnCancelarVenda->Enabled = true;
  FormPrincipal->StrGridVendaProduto->Enabled = true;
  FormPrincipal->EditTotal2->Enabled = true;
}
//------------------------------------------------------------------------
