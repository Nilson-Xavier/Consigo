//---------------------------------------------------------------------------
#ifndef ThreadLeituraReducaoFiscalH
#define ThreadLeituraReducaoFiscalH
//---------------------------------------------------------------------------
class TLeituraReducaoFiscalThread : public TThread {
  private:
    String *ReducaoInicial;
    String *ReducaoFinal;

    void __fastcall Execute( );
  public:

    __fastcall TLeituraReducaoFiscalThread( String* ReducaoInicial, String* ReducaoFinal, bool CreateSuspended );
    __fastcall ~TLeituraReducaoFiscalThread( void );
};
//---------------------------------------------------------------------------
#endif
