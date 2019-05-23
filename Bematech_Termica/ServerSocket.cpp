 //---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ServerSocket.h"
#include "ImpressoraMecaf.h"
#include "AdministracaoVisanetRedecardAmex.h"
#include "AdministracaoTecBan.h"
#include "AdministracaoImpressoraEcf.h"
#include "Main.h"
#include "ThreadVendaServidor.h"
#include "Orcamento.h"
#include "Recibo.h"
//---------------------------------------------------------------------------
#pragma link "scktcomp"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TConsigoServerSocket::TConsigoServerSocket( TComponent *AOwner )
 : TServerSocket( AOwner ) {

	ServerType = stThreadBlocking;
  Port = 1903;
  OnClientError = ServerSocketClientError;
  OnError = ServerSocketError;
  OnGetThread = ServerSocketGetThread;
  Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TConsigoServerSocket::ServerSocketError( TObject* Sender,
	TCustomWinSocket* Socket,	TErrorEvent ErrorEvent, int &ErrorCode ) {

  ErrorCode = 0;
  throw Exception( "Erro ou Problema com o Servidor de Impressão" );
}
//---------------------------------------------------------------------------
void __fastcall TConsigoServerSocket::ServerSocketClientError( TObject* Sender,
	TCustomWinSocket* Socket,	TErrorEvent ErrorEvent, int &ErrorCode ) {

  ErrorCode = 0;
  throw Exception( "Erro ou Problema com a Conexão com a Máquina: " + Socket->RemoteHost );
}
//---------------------------------------------------------------------------
void __fastcall TConsigoServerSocket::ServerSocketGetThread( TObject *Sender,
	TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread ) {

   SocketThread = new TConsigoServerThread( false, ClientSocket );
}
//---------------------------------------------------------------------------
void __fastcall TConsigoServerThread::ClientExecute( ) {

  char buffer[10000];
	TStringList *Request;
  String *Retorno;
  TVendaServidorThread *Venda;
  TTefAdmVisanet *TefAdmVisanet;
  TTefAdmTecBan *TefAdmTecBan;
  TAdministracaoImpressoraEcf *AdmImpressora;
  TOrcamento *OrcamentoConserto;
  TRecibo *Recibo;
  int i;

	// make sure connection is active
	while( ( !Terminated ) && ( ClientSocket->Connected ) ) {
  	try {
    	// Now, use TWinSocketStream to read or write information
      // over a blockcing socket connection
      TWinSocketStream *pStream = new TWinSocketStream( ClientSocket, 60000 );
      Request = new TStringList( );
      Request->Sorted = false;
      Retorno = new AnsiString( );

      try {
        memset( buffer, 0, 10000 );
        // give the client 60 seconds to start writing
        if( pStream->WaitForData( 60000 ) ) {
          if( pStream->Read( buffer, 10000 ) == 0 ) {
          // (if can't read in 60 seconds) than close the connection
	          ClientSocket->Close( );
          }
          else {
            Request->Text = buffer;

              if( Request->IndexOfName( "Funcao" ) != -1 ) {
                if( Request->Values["Funcao"] == "LeituraMemoriaFiscal" ) {
                  try {
                    AdmImpressora = new TAdministracaoImpressoraEcf( );

                    AdmImpressora->LeituraMemoriaFiscal( &( Request->Values["DataInicial"] ), &( Request->Values["DataFinal"] ), Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete AdmImpressora;
                  }
                }
                if( Request->Values["Funcao"] == "LeituraReducaoFiscal" ) {
                  try {
                    AdmImpressora = new TAdministracaoImpressoraEcf( );

                    AdmImpressora->LeituraReducaoFiscal( &( Request->Values["ReducaoInicial"] ), &( Request->Values["ReducaoFinal"] ), Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete AdmImpressora;
                  }
                }
                if( Request->Values["Funcao"] == "LeituraX" ) {
                  try {
                    AdmImpressora = new TAdministracaoImpressoraEcf( );

                    AdmImpressora->LeituraX( Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete AdmImpressora;
                  }
                }
                if( Request->Values["Funcao"] == "ReducaoZ" ) {
                  try {
                    AdmImpressora = new TAdministracaoImpressoraEcf( );

                    AdmImpressora->ReducaoZ( Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete AdmImpressora;
                  }
                }
                if( Request->Values["Funcao"] == "CancelarCupom" ) {
                  try {
                    AdmImpressora = new TAdministracaoImpressoraEcf( );

                    AdmImpressora->CancelarCupom( Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete AdmImpressora;
                  }
                }
              	if( Request->Values["Funcao"] == "Vender" ) {
                  try {
                    Venda = new TVendaServidorThread( true, Request );
                    Venda->WaitFor( );
                    if( Venda->Erro->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Venda->Erro + "\r\n";
                    }
                  }
                  __finally {
                    delete Venda;
                  }
                }
                if( Request->Values["Funcao"] == "AdmVisanet" ) {
                  try {
                    TefAdmVisanet = new TTefAdmVisanet( );

                    TefAdmVisanet->ExecutarAdm( Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete TefAdmVisanet;
                  }
                }
                if( Request->Values["Funcao"] == "AdmTecBan" ) {
                  try {
                    TefAdmTecBan = new TTefAdmTecBan( );

                    TefAdmTecBan->ExecutarAdm( Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete TefAdmTecBan;
                  }
                }
                if( Request->Values["Funcao"] == "ConsultarCheque" ) {

                }
                if( Request->Values["Funcao"] == "OrcamentoConserto" ) {
                  try {
                    OrcamentoConserto = new TOrcamento( Request );
                    OrcamentoConserto->RealizarOrdemDeServico( Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete OrcamentoConserto;
                  }
                }
                if( Request->Values["Funcao"] == "Recibo" ) {
                  try {
                    Recibo = new TRecibo( Request );
                    Recibo->Imprimir( Retorno );
                    if( Retorno->IsEmpty( ) ) {
                      *Retorno = "Retorno=\r\n";
                    }
                    else {
                      *Retorno = "Retorno=" + *Retorno + "\r\n";
                    }
                  }
                  __finally {
                    delete Recibo;
                  }
                }
              }
              else {
                *Retorno = "Retorno=Função Enviada Inválida !!!";
              }

              pStream->Write( Retorno->c_str( ), Retorno->Length( ) );
          }
        }
        else {
        	ClientSocket->Close( );
        }
        if( ClientSocket->Connected ) {
          ClientSocket->Close( );
        }
      }
      __finally {
      	delete pStream;
        delete Request;
        delete Retorno;
      }
    }
    catch( ... ) {
      this->HandleException( );
    }
  }
}
//---------------------------------------------------------------------------
