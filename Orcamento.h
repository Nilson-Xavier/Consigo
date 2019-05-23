//---------------------------------------------------------------------------
#ifndef OrcamentoH
#define OrcamentoH
//---------------------------------------------------------------------------
class TOrcamento : public TObject {

	private:
    TStringList *OrcamentoInfo;
    String *NumeroOrcamento;
    String *NomeCliente;
    String *Telefone;

    void ImprimirOrcamento( String* &Retorno );
    void InserirOrcamento( String* &Retorno );

  public:
    __fastcall TOrcamento( TStringList* OrcamentoInfo );
    __fastcall ~TOrcamento( void );
    void RealizarOrdemDeServico( String* &Retorno );
};
//---------------------------------------------------------------------------
#endif
