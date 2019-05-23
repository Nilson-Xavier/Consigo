//---------------------------------------------------------------------------
#ifndef ServiceThreadH
#define ServiceThreadH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <vcl.h>

#include "ServerSocket.h"
//---------------------------------------------------------------------------
class TMecafPrinterService : public TService {
	private:

	__published:
   void __fastcall MecafPrinterServiceStart(	TService *Sender, bool &Started );
   void __fastcall MecafPrinterServiceStop( TService *Sender, bool &Stopped );
   void __fastcall MecafPrinterServicePause( TService *Sender, bool &Paused );
   void __fastcall MecafPrinterServiceContinue( TService *Sender, bool &Continued );
	public:
  	__fastcall TMecafPrinterService( TComponent* Owner );
  	TServiceController __fastcall GetServiceController( void );
   	friend void __stdcall ServiceController( unsigned CtrlCode );
};

class TMecafPrinterServiceThread : public TThread {
	private:
   	TImpressoraMecafServerSocket *servidorImpressao;
   	void __fastcall BuildServerSocket( void );
  public:
  	__fastcall TMecafPrinterServiceThread( bool CreateSuspended );
    void __fastcall Execute( void );
};
//---------------------------------------------------------------------------
extern PACKAGE TMecafPrinterService *MecafPrinterService;
extern int __thread busyCompact;
//---------------------------------------------------------------------------
#endif
