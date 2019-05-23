//---------------------------------------------------------------------------
#ifndef AdministracaoVisanetRedecardAmexH
#define AdministracaoVisanetRedecardAmexH
//---------------------------------------------------------------------------
class TTefAdmVisanet : public TObject {
  private:

    TStringList *Cupom;

    void ImprimirCupomTef( String* &Retorno );
  public:

    __fastcall TTefAdmVisanet( );
    __fastcall ~TTefAdmVisanet( void );
    void ExecutarAdm( String* &Retorno );
};
//---------------------------------------------------------------------------
#endif
