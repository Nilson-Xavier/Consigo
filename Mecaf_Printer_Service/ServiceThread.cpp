//---------------------------------------------------------------------------
#include "ServiceThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMecafPrinterService *MecafPrinterService;
TMecafPrinterServiceThread *MecafPrinterServiceThread;
int __thread busyCompact;
//---------------------------------------------------------------------------
__fastcall TMecafPrinterService::TMecafPrinterService( TComponent* Owner )
	: TService( Owner ) {

  DisplayName = "Mecaf Printer Server";
  ErrorSeverity = esCritical;
  Interactive= false;
  ServiceType = stWin32;
  StartType = stAuto;
  AllowStop = true;
  OnStart = MecafPrinterServiceStart;
  OnStop = MecafPrinterServiceStop;
}
//---------------------------------------------------------------------------
TServiceController __fastcall TMecafPrinterService::GetServiceController( void ) {

	return( TServiceController ) ServiceController;
}
//---------------------------------------------------------------------------
void __stdcall ServiceController( unsigned CtrlCode ) {

	MecafPrinterService->Controller( CtrlCode );
}
//---------------------------------------------------------------------------
void __fastcall TMecafPrinterService::MecafPrinterServiceStart( TService *Sender,
	bool &Started ) {

	try {
    MecafPrinterServiceThread = new TMecafPrinterServiceThread( false );
  	Started = true;
  }
  catch( Exception &e ) {
		this->LogMessage( e.Message, EVENTLOG_ERROR_TYPE, 0, 0 );
  }
}
//--------------------------------------------------------------------------
void __fastcall TMecafPrinterService::MecafPrinterServiceStop(TService *Sender,
	bool &Stopped ) {

  try {
	  try {
 			MecafPrinterServiceThread->Terminate( );
  		if( MecafPrinterServiceThread != NULL ) {
	  		delete MecafPrinterServiceThread;
		  }
	  }
  	catch( Exception &e ) {
			this->LogMessage( e.Message, EVENTLOG_ERROR_TYPE, 0, 0 );
	  }
  }
  __finally {
    Stopped = true;
  }
}
//-------------------------------------------------------------------------
void __fastcall TMecafPrinterService::MecafPrinterServicePause( TService *Sender,
	bool &Paused ) {

  //Não faz Nada!!!
  //Paused = true;
}
//--------------------------------------------------------------------------
void __fastcall TMecafPrinterService::MecafPrinterServiceContinue( TService *Sender,
	bool &Continued ) {

  //Não faz Nada!!!
  //Continued = true;
}
//--------------------------------------------------------------------------
__fastcall TMecafPrinterServiceThread::TMecafPrinterServiceThread( bool CreateSuspended )
	: TThread( CreateSuspended ) {

  FreeOnTerminate = true;
  Priority = tpNormal;
  busyCompact = 0;
}
//--------------------------------------------------------------------------
void __fastcall TMecafPrinterServiceThread::Execute( void ) {

  Synchronize( BuildServerSocket );
}
//--------------------------------------------------------------------------
void __fastcall TMecafPrinterServiceThread::BuildServerSocket( void ) {

  try {
  	servidorImpressao = new TImpressoraMecafServerSocket( MecafPrinterService );
  }
  catch( Exception &e ) {
    MecafPrinterService->LogMessage( e.Message, EVENTLOG_ERROR_TYPE, 0, 0 );
  }
}
//---------------------------------------------------------------------------