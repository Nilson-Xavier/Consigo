//---------------------------------------------------------------------------
#ifndef ServerSocketH
#define ServerSocketH
//---------------------------------------------------------------------------
#include <vcl\scktcomp.hpp>

class TImpressoraMecafServerSocket : public TServerSocket {
	private:

  public:
    __fastcall TImpressoraMecafServerSocket( TComponent *AOwner );
    void __fastcall ServerSocketClientError( TObject* Sender, TCustomWinSocket* Socket,
    	TErrorEvent ErrorEvent, int &ErrorCode );
    void __fastcall ServerSocketError( TObject* Sender, TCustomWinSocket* Socket,
    	TErrorEvent ErrorEvent, int &ErrorCode );
    void __fastcall ServerSocketGetThread( TObject *Sender,
    	TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread );
};

class PACKAGE TMecafServerThread : public TServerClientThread {
  private:

  public:
  	__fastcall TMecafServerThread( bool CreateSuspended, TServerClientWinSocket *ASocket )
    	: Scktcomp::TServerClientThread( CreateSuspended, ASocket )
      { CreateSuspended = false; KeepInCache = false; FreeOnTerminate = true; };
    void __fastcall ClientExecute( void );
};
//---------------------------------------------------------------------------
#endif
