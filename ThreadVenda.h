//---------------------------------------------------------------------------
#ifndef ThreadVendaH
#define ThreadVendaH

#include "ValorCartao.h"
//---------------------------------------------------------------------------
class TVendaThread : public TThread {
  private:
    String *Impressora; // 1 - ECF ; 2 - Mecaf
    TFormValorCartao *FormValorCartao;

    void __fastcall Execute( );
    void CapturarValorCartao( String* &Valor );
    void __fastcall BotaoDesabilitar( );
    void __fastcall BotaoAbilitar( );
  public:
    __fastcall TVendaThread( bool CreateSuspended, String* Impressora );
    __fastcall ~TVendaThread( void );
};
//---------------------------------------------------------------------------
#endif
