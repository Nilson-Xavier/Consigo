//---------------------------------------------------------------------------
#ifndef SecaoCriticaH
#define SecaoCriticaH
//---------------------------------------------------------------------------
#include <syncobjs.hpp>
//---------------------------------------------------------------------------
class TEvento : public TEvent {

	private:

  public:
    __fastcall TEvento( Windows::PSecurityAttributes EventAttributes,
      bool ManualReset, bool InitialState, const System::AnsiString Name );
};
//---------------------------------------------------------------------------
class TSecaoCritica : public TCriticalSection {

  private:

  public:
    __fastcall TSecaoCritica( void );
};
//---------------------------------------------------------------------------
extern TEvento *ImpressoraEcfEvento;
extern TEvento *ImpressoraMecafEvento;
extern TEvento *TefEvento;
extern TSecaoCritica *SecaoCritica;
//---------------------------------------------------------------------------
#endif
