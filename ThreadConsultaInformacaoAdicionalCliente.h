//---------------------------------------------------------------------------
#ifndef ThreadConsultaInformacaoAdicionalClienteH
#define ThreadConsultaInformacaoAdicionalClienteH
//---------------------------------------------------------------------------
class TThreadConsultaInfoCliente : public TThread {
  private:
    String *Nome;

    void __fastcall DisableEditControl( );
    void __fastcall EnableEditControl( );
    void __fastcall Execute( );
  public:
    __fastcall TThreadConsultaInfoCliente( String* Nome, bool CreateSuspended );
    __fastcall ~TThreadConsultaInfoCliente( void );
};
//---------------------------------------------------------------------------
#endif

