//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SecaoCritica.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TEvento::TEvento( Windows::PSecurityAttributes EventAttributes,
  bool ManualReset, bool InitialState, const System::AnsiString Name ) : TEvent( EventAttributes,
  ManualReset, InitialState, Name ) {

}
//---------------------------------------------------------------------------
__fastcall TSecaoCritica::TSecaoCritica( void ) : TCriticalSection( ) {

}
//---------------------------------------------------------------------------
