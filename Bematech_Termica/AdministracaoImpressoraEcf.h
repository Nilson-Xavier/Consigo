//---------------------------------------------------------------------------
#ifndef AdministracaoImpressoraEcfH
#define AdministracaoImpressoraEcfH
//---------------------------------------------------------------------------
class TAdministracaoImpressoraEcf : public TObject {
  private:

  public:
    __fastcall TAdministracaoImpressoraEcf( );
    __fastcall ~TAdministracaoImpressoraEcf( void );
    void LeituraX( String* &Retorno );
    void ReducaoZ( String* &Retorno );
    void LeituraMemoriaFiscal( String* DataInicial, String* DataFinal, String* &Retorno );
    void LeituraReducaoFiscal( String* ReducaoInicial, String* ReducaoFinal, String* &Retorno );
    void CancelarCupom( String* &Retorno );
    void GerarArquivoRfd( String *Data, String *CaminhoDoArquivo, String* Retorno );
    void ValidarArquivoRfd( String *CaminhoDoArquivo, String *RetornoMd5, String *Retorno );
};
//---------------------------------------------------------------------------
#endif
