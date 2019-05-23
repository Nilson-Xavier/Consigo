//---------------------------------------------------------------------------
#ifndef ThreadTefConsultaChequeH
#define ThreadTefConsultaChequeH
//---------------------------------------------------------------------------
class TTefConsultaChequeThread : public TThread {
  private:

    void __fastcall Execute( );
  public:

    __fastcall TTefConsultaChequeThread( bool CreateSuspended );
    __fastcall ~TTefConsultaChequeThread( void );
};
//---------------------------------------------------------------------------
#endif
