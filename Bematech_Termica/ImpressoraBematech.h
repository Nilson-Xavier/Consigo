//---------------------------------------------------------------------------
#ifndef ImpressoraBematechH
#define ImpressoraBematechH

#include <vcl\Classes.hpp>
//---------------------------------------------------------------------------
class TImpressoraBematech : public TObject {
  private:
    int *Itens;
    bool *FilmeRebobinado;
    String *NumeroCupom;
    String *ValorTotal;

  public:
    __property String *Cupom = { read=NumeroCupom, write=NumeroCupom };
    __property String *Total = { read=ValorTotal, write=ValorTotal };

    __fastcall TImpressoraBematech( void );
    __fastcall ~TImpressoraBematech( void );

    void Iniciar( String* Retorno );
    void Finalizar( );
    void AbrirCupom( String* Cupom, String *CpfCnpj, String* Retorno );
    void LancarItem( String* Qtd, String* PrecoUnit, String* Codigo,
      String* Descricao, String* Retorno );
    void TotalizarCupom( String* Retorno );
    void Pagamento( String* FormaPagamento, String* Entrada, String* QtdParcela,
      String* Parcela, String* Retorno );
    void FecharCupom( String* Vendedor, String* Cliente, String* Telefone,
      String* Retorno );
    void AbrirCupomVinculado( String* Retorno );
    void ImprimirTextoTEF( TStringList* Texto, String* Retorno );
    void FecharCupomVinculado( String* Retorno );
    void AbrirOrcamentoConserto( String* &NumeroOrcamento, String* Retorno );
    void LancarItemOrcamento( String* PrecoUnit, String* Codigo,
      String* Descricao, String* NumeroSerie, String* Defeito, String* Retorno );
    void TotalizarOrcamento( String* Retorno );
    void FecharOrcamento( String* Vendedor, String* Cliente, String* Telefone,
      String* Retorno );
    void AbrirRecibo( String* Retorno );
    void ImprimirRecibo( String* Vendedor, String* Cliente, String* Valor, String* Referente,
      String* Retorno);
    void FecharRecibo( String* Retorno );
    void ValorExtenso( String* Preco, String* ValorExtenso );
};
//---------------------------------------------------------------------------
//--------------- Declaração das funções da DLL MP2032 --------------------

extern "C" __stdcall int IniciaPorta( char* Porta );
extern "C" __stdcall int FechaPorta( void );
extern "C" __stdcall int ConfiguraModeloImpressora( int ModeloImpressora );
extern "C" __stdcall int ConfiguraTaxaSerial( int Taxa );
extern "C" __stdcall int HabilitaEsperaImpressao( int Flag );
extern "C" __stdcall int EsperaImpressao( void );
extern "C" __stdcall int HabilitaPresenterRetratil( int iFlag );
extern "C" __stdcall int ProgramaPresenterRetratil( int iTempo );
extern "C" __stdcall int VerificaPapelPresenter( void );
extern "C" __stdcall int HabilitaExtratoLongo( int Flag );
extern "C" __stdcall int ConfiguraTamanhoExtrato( int NumeroLinhas );
extern "C" __stdcall int AjustaLarguraPapel ( int width );
extern "C" __stdcall int SelecionaQualidadeImpressao( int Quality );
extern "C" __stdcall int AcionaGuilhotina( int Total );

extern "C" __stdcall int FormataTX( char* BufTras, int TpoLtra, int Italic, int Sublin, int expand, int enfat );
extern "C" __stdcall int BematechTX( char* BufTrans );
extern "C" __stdcall int EsperaImpressao( void );

//---------------------------------------------------------------------------
#endif
