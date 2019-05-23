//---------------------------------------------------------------------------
#ifndef ThreadValidarArquivoRfdH
#define ThreadValidarArquivoRfdH
//---------------------------------------------------------------------------
class TThreadValidarArquivoRfd : public TThread {
  private:
    String *CaminhoDoArquivo;

    void __fastcall Execute( );
  public:

    __fastcall TThreadValidarArquivoRfd( String *CaminhoDoArquivo, bool CreateSuspended );
    __fastcall ~TThreadValidarArquivoRfd( void );
};
//---------------------------------------------------------------------------
#endif
