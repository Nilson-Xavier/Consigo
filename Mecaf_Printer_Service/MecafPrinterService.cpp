#include <SysUtils.hpp>
#include <SvcMgr.hpp>
#pragma hdrstop
#define Application Svcmgr::Application

USERES( "MecafPrinterService.res" );
USEFORM( "ServiceThread.cpp", MecafPrinterService ); /* TService: File Type */
USEUNIT( "ImpressoraMecaf.cpp" );
USEUNIT( "ServerSocket.cpp" );
//---------------------------------------------------------------------------
WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {

	try {
		Application->Initialize( );
		Application->CreateForm( __classid( TMecafPrinterService ), &MecafPrinterService );
    Application->Run( );
	}
	catch( Exception &exception ) {
		Sysutils::ShowException( &exception, Sysutils::ExceptAddr( ) );
	}
	return 0;
}
