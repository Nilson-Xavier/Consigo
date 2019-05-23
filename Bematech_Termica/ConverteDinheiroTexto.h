//---------------------------------------------------------------------------
#ifndef ConverteDinheiroTextoH
#define ConverteDinheiroTextoH
//---------------------------------------------------------------------------
class TValorUnidade : private TObject {

	private:

  public:
    String ConverterUnidadeTexto( String* Unidade );
};
//---------------------------------------------------------------------------
class TValorDezena : private TObject {

	private:

  public:
    String ConverterDezenaTexto( String* Dezena );
};
//---------------------------------------------------------------------------
class TValorCentena : private TObject {

	private:

  public:
    String ConverterCentenaTexto( String* Centena );
};
//---------------------------------------------------------------------------
class TDinheiroTexto : public TObject {

	private:
    String *ValorArray[11];
    TValorUnidade *Unidade;
    TValorDezena *Dezena;
    TValorCentena *Centena;

  public:
    __fastcall TDinheiroTexto( void );
    __fastcall ~TDinheiroTexto( void );
    void ConverterDinheiroTexto( String* Valor, String* ValorExtenso );
};
//---------------------------------------------------------------------------
#endif
