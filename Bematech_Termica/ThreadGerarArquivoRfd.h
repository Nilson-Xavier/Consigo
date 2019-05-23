//---------------------------------------------------------------------------
#ifndef ThreadGerarArquivoRfdH
#define ThreadGerarArquivoRfdH
//---------------------------------------------------------------------------
class TThreadGerarArquivoRfd : public TThread {
  private:
    String *Data;
    String *CaminhoDaPastaDestino;

    void __fastcall Execute( );
  public:

    __fastcall TThreadGerarArquivoRfd( String *Data, String *CaminhoDaPastaDestino,
      bool CreateSuspended );
    __fastcall ~TThreadGerarArquivoRfd( void );
};
//---------------------------------------------------------------------------
#endif
