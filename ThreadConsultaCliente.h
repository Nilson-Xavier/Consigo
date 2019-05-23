//---------------------------------------------------------------------------
#ifndef ThreadConsultaClienteH
#define ThreadConsultaClienteH
//---------------------------------------------------------------------------
class TThreadConsultaCliente : public TThread {
  private:
    String *Nome;
    String *RG;
    String *EERG;
    String *Telefone;
    String *CEP;

    void __fastcall DisableEditControl( );
    void __fastcall EnableEditControl( );
    void __fastcall Execute( );
  public:
    __fastcall TThreadConsultaCliente( String* Nome, String* RG, String* EERG,
      String* Telefone, String* Cep, bool CreateSuspended );
    __fastcall ~TThreadConsultaCliente( void );
};
//---------------------------------------------------------------------------
#endif
