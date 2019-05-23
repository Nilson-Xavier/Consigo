 //---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ServerSocket.h"
#include "ImpressoraMecaf.h"
#include "ServiceThread.h"
//---------------------------------------------------------------------------
#pragma link "scktcomp"
#pragma package(smart_init)

__fastcall TImpressoraMecafServerSocket::TImpressoraMecafServerSocket( TComponent *AOwner )
: TServerSocket( AOwner ) {

	ServerType = stThreadBlocking;
  Port = 1900;
  OnClientError = ServerSocketClientError;
  OnError = ServerSocketError;
  OnGetThread = ServerSocketGetThread;
  Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TImpressoraMecafServerSocket::ServerSocketError( TObject* Sender,
	TCustomWinSocket* Socket,	TErrorEvent ErrorEvent, int &ErrorCode ) {

  ErrorCode = 0;
  throw Exception( "Erro ou Problema com o Servidor de Impressão" );
}
//---------------------------------------------------------------------------
void __fastcall TImpressoraMecafServerSocket::ServerSocketClientError( TObject* Sender,
	TCustomWinSocket* Socket,	TErrorEvent ErrorEvent, int &ErrorCode ) {

  ErrorCode = 0;
  throw Exception( "Erro ou Problema com a Conexão com a Máquina: " + Socket->RemoteHost );
}
//---------------------------------------------------------------------------
void __fastcall TImpressoraMecafServerSocket::ServerSocketGetThread( TObject *Sender,
	TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread ) {

   SocketThread = new TMecafServerThread( false, ClientSocket );
}
//---------------------------------------------------------------------------
void __fastcall TMecafServerThread::ClientExecute( ) {

	TStringList *Request, *Retorno;
  TImpressoraMecaf *impressoraCompact;

	// make sure connection is active
	while( ( !Terminated ) && ( ClientSocket->Connected ) ) {
  	try {
    	// Now, use TWinSocketStream to read or write information
      // over a blocking socket connection
      TWinSocketStream *pStream = new TWinSocketStream( ClientSocket, 60000 );
      Request = new TStringList( );
      String Buffer;
      try {
      	char buffer[10000];
        memset( buffer, 0, 10000 );
        // give the client 60 seconds to start writing
        if( pStream->WaitForData( 60000 ) ) {
          if( pStream->Read( buffer, 10000 ) == 0 ) {
          // (if can't read in 60 seconds) than close the connection
	          ClientSocket->Close( );
          }
          else {
            Request->Text = buffer;
            try {
            	Retorno = new TStringList( );
              Retorno->Sorted = false;
            	while( Request->Count != 0 ) {
                if( ( this->ServerSocket->ActiveConnections > 1 ) || ( busyCompact ) ) {
                  Retorno->Append( "Retorno=Impressora Ocupada no Momento!!! Espere Alguns Segundos." );
                  Request->Clear( );
                }
	            	else if( Request->IndexOfName( "Funcao" ) != -1 ) {

                    busyCompact = 1;

  	                if( Request->Values["Funcao"] == "ObterStatus" ) {
                      try {
    	  	            	impressoraCompact = new TImpressoraMecaf( );
                        Retorno->Append( "Retorno=" + impressoraCompact->CarregarDll( false ) );
        		          	Retorno->Append( "Retorno=" + impressoraCompact->ObterStatus( false ) );
              		  	  impressoraCompact->Finalizar( );
        	        			Request->Delete( Request->IndexOfName( "Funcao" ) );
            	      	  if( Retorno->Values["Retorno"] != "0" ) {
              	         	Request->Clear( );
                	     	}
                      }
    		              __finally {
      		             	delete impressoraCompact;
        		          }
          	        }
            	      if( Request->Values["Funcao"] == "Imprimir" ) {
              	    	if( Request->IndexOfName( "Param1" ) != -1 ) {
 	              	    	try {
   	              	    	impressoraCompact = new TImpressoraMecaf( );
                          Buffer = impressoraCompact->CarregarDll( false );
                          Retorno->Append( "Retorno=" + Buffer );
                          if( Buffer == "0" ) {
                            Buffer = impressoraCompact->ObterStatus( false );
           		            	Retorno->Append( "Retorno=" + Buffer );
                          }
           	              if( Buffer == "0" ) {
      	                    Buffer = impressoraCompact->Iniciar( false );
         	                  Retorno->Append( "Retorno=" + Buffer );
               	          }
         	                if( Buffer == "0" ) {
                            while( ( Request->IndexOfName( "Param1" ) != -1 ) || ( Buffer != "0" ) ) {
             	              	Buffer = Request->Values["Param1"];
	  				  	              Buffer = StringReplace( Buffer, "~", "\r", TReplaceFlags( ) << rfReplaceAll );
 	          						      Buffer = StringReplace( Buffer, "^", "\n", TReplaceFlags( ) << rfReplaceAll );
   	              	      	  Buffer = impressoraCompact->Imprimir( Buffer, false );
                              Request->Delete( Request->IndexOfName( "Param1" ) );
                              if( Request->IndexOfName( "Param1" ) != -1 ) {
                                Sleep( 12000 );
                                //Buffer = impressoraCompact->Iniciar( false );
                              }
                            }
                            Retorno->Append( "Retorno=" + Buffer );
                   	      }
   	                	    impressoraCompact->Finalizar( );
       			        		  //Request->Delete( Request->IndexOfName( "Funcao" ) + 1 );
         	              	Request->Delete( Request->IndexOfName( "Funcao" ) );
	                      	if( Retorno->Values["Retorno"] != "0" ) {
	  	                    	Request->Clear( );
 		  	                  }
     	        	        }
       	        	      __finally {
         	        	    	delete impressoraCompact;
           	        	  }
	                    }
  	                  else {
    	                	Retorno->Append( "Retorno=Falta de parâmetro para o Comando Imprimir!!!" );
          	          }
            	      }
	              }
                else {
                  Retorno->Append( "Função Enviada Inválida!!!" );
                }
            	}
              Buffer = Retorno->Text;
              pStream->Write( Buffer.c_str( ), Buffer.Length( ) );

              Sleep( 15000 );
              busyCompact = 0;
            }
            __finally {
            	delete Retorno;
            }
          }
        }
        else {
        	ClientSocket->Close( );
        }
      }
      __finally {
      	delete pStream;
        delete Request;
      }
    }
    catch(...) {
      this->HandleException( );
    }
  }
}
//-----------------------------------------------------------------------------
