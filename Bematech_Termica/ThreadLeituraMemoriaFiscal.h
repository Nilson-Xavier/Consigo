//---------------------------------------------------------------------------
#ifndef ThreadLeituraMemoriaFiscalH
#define ThreadLeituraMemoriaFiscalH
//---------------------------------------------------------------------------
class TLeituraMemoriaFiscalThread : public TThread {
  private:
    String *DataInicial;
    String *DataFinal;

    void __fastcall Execute( );
  public:

    __fastcall TLeituraMemoriaFiscalThread( String* DataInicial, String* DataFinal, bool CreateSuspended );
    __fastcall ~TLeituraMemoriaFiscalThread( void );
};
//---------------------------------------------------------------------------
#endif
