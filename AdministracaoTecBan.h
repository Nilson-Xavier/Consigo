//---------------------------------------------------------------------------
#ifndef AdministracaoTecBanH
#define AdministracaoTecBanH
//---------------------------------------------------------------------------
class TTefAdmTecBan : public TObject {
  private:

    TStringList *Cupom;

    void ImprimirCupomTef( String* &Retorno );
  public:

    __fastcall TTefAdmTecBan( );
    __fastcall ~TTefAdmTecBan( );
    void ExecutarAdm( String* &Retorno );
};
//---------------------------------------------------------------------------
#endif
