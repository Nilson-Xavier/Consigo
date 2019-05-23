//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ClientSocket.h"
#include "Main.h"
#include "OrdemDeServico.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TConsigoClientSocket::TConsigoClientSocket( TComponent* AOwner,
	TStringList* Request, String* HostIP ) : TClientSocket( AOwner ) {

	this->Host = *HostIP;
  this->Port = 1903; // Porta para Impressora Ecf;
  this->ClientType = ctBlocking;
  this->OnConnect = ClientSocketConnect;
  this->OnError = ClientSocketError;
  this->Request = new TStringList( );
  this->Request->Sorted = false;
  this->Request->Assign( Request );
  this->Active = true;
}
//---------------------------------------------------------------------------
__fastcall TConsigoClientSocket::~TConsigoClientSocket( void ) {

	if( this->Active ) {
  	this->Active = false;
  }
  delete Request;
}
//---------------------------------------------------------------------------
void __fastcall TConsigoClientSocket::ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket ) {

  TWinSocketStream *Stream;
  String *Buffer;
  TStringList *Response;
  int i;

  try {
    Stream = new TWinSocketStream( Socket, 60000 );
    Buffer = new String( );
    Response = new TStringList( );

    try {
    	*Buffer = this->Request->Text;
    	if( Stream->Write( Buffer->c_str( ), Buffer->Length( ) ) == 0 ) {
      	this->Active = false;
        throw Exception( "Problema ou Erro ao Enviar Comando para o Servidor de Impressão!" );
      }
      if( Stream->WaitForData( 1800000 ) ) {
      	char buffer[500];
      	if( Stream->Read( buffer, 500 ) == 0 ) {
          throw Exception( "Não Houve Retorno de Comando do Servidor de Impressão!!!" );
        }
        else {
        	Response->Text = buffer;
          if( Response->IndexOfName( "Retorno" ) != -1 ) {
            if( Response->Values["Retorno"] != "" ) {
            	throw Exception( Response->Values["Retorno"] );
            }
            else {
              if( this->Request->Values["Funcao"] == "Vender" ) {
                for( i = 1; i < FormPrincipal->StrGridVendaProduto->RowCount; i++ ) {
      			    	FormPrincipal->StrGridVendaProduto->Rows[i]->Clear( );
		    				}
                FormPrincipal->StrGridVendaProduto->RowCount = 2;
                FormPrincipal->EditTotal2->Clear( );
                FormPrincipal->ComboBoxRgCnpj->Clear( );
                FormPrincipal->EditEntrada->Clear( );
                FormPrincipal->EditParcela->Clear( );
                throw Exception( "A Venda Foi Realizada com Sucesso !" );
              }
              else if( ( this->Request->Values["Funcao"] == "AdmVisanet" ) ||
                       ( this->Request->Values["Funcao"] == "AdmTecBan" ) ) {
                throw Exception( "Função de Administração TEF Realizada com Sucesso !" );
              }
              else if ( this->Request->Values["Funcao"] == "ConsultarCheque" ) {
                throw Exception( "Consulta de Cheque Aprovada !" );
              }
              if( this->Request->Values["Funcao"] == "OrcamentoConserto" ) {
                for( i = 1; i < FormOrdemDeServico->StringGridConserto->RowCount; i++ ) {
      			    	FormOrdemDeServico->StringGridConserto->Rows[i]->Clear( );
		    				}
                FormOrdemDeServico->StringGridConserto->RowCount = 2;
                FormOrdemDeServico->EditTotal->Clear( );
                FormOrdemDeServico->MemoDefeito->Clear( );
                FormOrdemDeServico->ComboBoxCliente->Clear( );
                throw Exception( "Ordem De Serviço Impressa com Sucesso !" );
              }
              if( this->Request->Values["Funcao"] == "Recibo" ) {
                FormPrincipal->ComboBoxReciboVendedor->Clear( );
                FormPrincipal->ComboBoxRecebemos->Clear( );
                FormPrincipal->EditReciboValor->Clear( );
                FormPrincipal->MemoReciboReferente->Clear( );
                throw Exception( "Recibo Impresso com Sucesso !" );
              }
            }
            Socket->Close( );
          }
          else {
          	throw Exception( "Não Houve Retorno de Comando do Servidor de Impressão!!!" );
          }
        }
      }
      else {
      	throw Exception( "Excedeu o Tempo de Espera de Resposta do Servidor de Impressão!!!" );
      }
    }
	  __finally {
    	delete Response;
  		delete Buffer;
  		delete Stream;
	  }
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "Vendas", MB_OK | MB_ICONWARNING );
  }
}
//---------------------------------------------------------------------------
void __fastcall TConsigoClientSocket::ClientSocketError( System::TObject* Sender,
	TCustomWinSocket* Socket,	TErrorEvent ErrorEvent, int &ErrorCode ) {

  ErrorCode = 0;
	if( Active ) {
  	Active = false;
  }
	throw Exception( "Erro ou Problema na Conexão com o Servidor!" );
}
//---------------------------------------------------------------------------
