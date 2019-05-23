//---------------------------------------------------------------------------
#ifndef ReciboH
#define ReciboH
//---------------------------------------------------------------------------
class TRecibo : public TObject {

	private:
    TStringList *ReciboInfo;
    String *Vendedor;
    String *Cliente;
    String *Valor;
    String *Referente;

    void ImprimirOrcamento( String* &Retorno );
    void InserirOrcamento( String* &Retorno );

  public:
    __fastcall TRecibo( TStringList* ReciboInfo );
    __fastcall ~TRecibo( void );
    void Imprimir( String* &Retorno );
};
//---------------------------------------------------------------------------
#endif
