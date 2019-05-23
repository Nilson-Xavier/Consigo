//---------------------------------------------------------------------------
#ifndef ThreadTefAdmTecbanH
#define ThreadTefAdmTecbanH
//---------------------------------------------------------------------------
class TTefAdmTecBanThread : public TThread {
  private:

    void __fastcall Execute( );
  public:

    __fastcall TTefAdmTecBanThread( bool CreateSuspended );
    __fastcall ~TTefAdmTecBanThread( void );
};
//---------------------------------------------------------------------------
#endif
