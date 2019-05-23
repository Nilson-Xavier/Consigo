//---------------------------------------------------------------------------
#ifndef ThreadReducaoZH
#define ThreadReducaoZH
//---------------------------------------------------------------------------
class TReducaoZThread : public TThread {
  private:

    void __fastcall Execute( );
  public:

    __fastcall TReducaoZThread( bool CreateSuspended );
    __fastcall ~TReducaoZThread( void );
};
//---------------------------------------------------------------------------
#endif
