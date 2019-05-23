//---------------------------------------------------------------------------
#ifndef ServerSocketH
#define ServerSocketH
//---------------------------------------------------------------------------
#include <vcl\scktcomp.hpp>
//---------------------------------------------------------------------------
class TConsigoServerSocket : public TServerSocket {
	private:

  public:
    __fastcall TConsigoServerSocket( TComponent *AOwner );
    void __fastcall ServerSocketClientError( TObject* Sender, TCustomWinSocket* Socket,
    	TErrorEvent ErrorEvent, int &ErrorCode );
    void __fastcall ServerSocketError( TObject* Sender, TCustomWinSocket* Socket,
    	TErrorEvent ErrorEvent, int &ErrorCode );
    void __fastcall ServerSocketGetThread( TObject *Sender,
    	TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread );
};
//---------------------------------------------------------------------------
class PACKAGE TConsigoServerThread : public TServerClientThread {
  private:
    
  public:
  	__fastcall TConsigoServerThread( bool CreateSuspended, TServerClientWinSocket *ASocket )
    	: Scktcomp::TServerClientThread( CreateSuspended, ASocket )
      { CreateSuspended = false; KeepInCache = false; FreeOnTerminate = true; };
    void __fastcall ClientExecute( void );
};
//---------------------------------------------------------------------------
#endif
