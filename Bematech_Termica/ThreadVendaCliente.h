//---------------------------------------------------------------------------
#ifndef ThreadVendaClienteH
#define ThreadVendaClienteH

#include "ValorCartao.h"
//---------------------------------------------------------------------------
class TVendaClienteThread : public TThread {
  private:
    String *Impressora, *ValorCartao; // 1 - ECF ; 2 - Mecaf
    TFormValorCartao *FormValorCartao;

    void __fastcall Execute( );
    void __fastcall CapturarValorCartao( );
    void __fastcall BotaoDesabilitar( );
    void __fastcall BotaoAbilitar( );
  public:
    __fastcall TVendaClienteThread( bool CreateSuspended, String* Impressora );
    __fastcall ~TVendaClienteThread( void );
};
//---------------------------------------------------------------------------
#endif
