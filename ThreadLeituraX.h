//---------------------------------------------------------------------------
#ifndef ThreadLeituraXH
#define ThreadLeituraXH
//---------------------------------------------------------------------------
class TLeituraXThread : public TThread {
  private:

    void __fastcall Execute( );
  public:

    __fastcall TLeituraXThread( bool CreateSuspended );
    __fastcall ~TLeituraXThread( void );
};
//---------------------------------------------------------------------------
#endif
