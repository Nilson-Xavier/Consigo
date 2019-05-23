//---------------------------------------------------------------------------
#ifndef ThreadConsultaProdutoH
#define ThreadConsultaProdutoH
//---------------------------------------------------------------------------
class TThreadConsultaProduto : public TThread {
  private:
    String *Codigo_;
    String *Marca_;
    String *Nome_;

    void __fastcall DisableEditControl( );
    void __fastcall EnableEditControl( );
    void __fastcall Execute( );
  public:
    __fastcall TThreadConsultaProduto( String* Codigo, String* Marca, String* Nome,
                                       bool CreateSuspended );
    __fastcall TThreadConsultaProduto::~TThreadConsultaProduto( void );
};
//---------------------------------------------------------------------------
#endif
