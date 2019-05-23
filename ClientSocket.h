//---------------------------------------------------------------------------
#ifndef ClientSocketH
#define ClientSocketH

#include <vcl\scktcomp.hpp>
//---------------------------------------------------------------------------
class TConsigoClientSocket : public TClientSocket {
	private:
  	TStringList *Request;
  public:
  	__property TStringList *request = { read=Request };
    __fastcall TConsigoClientSocket( TComponent* AOwner, TStringList* Request,
      String* HostIP );
    __fastcall ~TConsigoClientSocket( void );
    void __fastcall ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket );
   	void __fastcall ClientSocketError( TObject* Sender, TCustomWinSocket* Socket,
    	TErrorEvent ErrorEvent, int &ErrorCode );
};
//---------------------------------------------------------------------------
#endif
