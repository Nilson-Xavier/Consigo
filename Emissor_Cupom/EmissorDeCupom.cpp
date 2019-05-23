//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

USERES( "EmissorDeCupom.res" );
USEFORM( "ImpressoraFiscal.cpp", FormImpressora );
USEUNIT( "ImpressoraFiscalECF.cpp" );
//---------------------------------------------------------------------------
WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	try
	{
		Application->Initialize( );
		Application->CreateForm( __classid( TFormImpressora ), &FormImpressora );
		Application->Run( );
	}
	catch ( Exception &exception )
	{
		Application->ShowException( &exception );
	}
	return 0;
}
//---------------------------------------------------------------------------
