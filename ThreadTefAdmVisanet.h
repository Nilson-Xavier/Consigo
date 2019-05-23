//---------------------------------------------------------------------------
#ifndef ThreadTefAdmVisanetH
#define ThreadTefAdmVisanetH
//---------------------------------------------------------------------------
class TTefAdmVisanetThread : public TThread {
  private:

    void __fastcall Execute( );
  public:
  
    __fastcall TTefAdmVisanetThread( bool CreateSuspended );
    __fastcall ~TTefAdmVisanetThread( void );
};
//---------------------------------------------------------------------------
#endif
