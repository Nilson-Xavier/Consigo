//---------------------------------------------------------------------------
#ifndef ThreadCancelamentoCupomH
#define ThreadCancelamentoCupomH
//---------------------------------------------------------------------------
class TCancelamentoCupomThread : public TThread {
  private:

    void __fastcall Execute( );
  public:

    __fastcall TCancelamentoCupomThread( bool CreateSuspended );
    __fastcall ~TCancelamentoCupomThread( void );
};
//---------------------------------------------------------------------------
#endif
