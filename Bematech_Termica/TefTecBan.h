//---------------------------------------------------------------------------
#ifndef TefTecBanH
#define TefTecBanH
//---------------------------------------------------------------------------
class TTefTecBan {
	private:
    String *Identificacao;
    String *Transacao;
    String *Finalizacao;
    String *Cartao;
    String *Valor;

    bool CriarArquivo( TStringList *Texto );
    void LerArquivoStatus( TStringList* &Texto );
    void LerArquivoResposta( TStringList* &Texto );
  public:
    __fastcall TTefTecBan( );
    __fastcall ~TTefTecBan( );

    __property String *ValorTransacao = { read = Valor };
    __property String *NumeroTransacao = { read = Transacao };
    __property String *Rede = { read = Cartao };

    void Atv( String* &Retorno ); // Verifica se o Gerenciador Padr�o est� ATIVO !!!
    bool Adm( String* &Retorno, TStringList* &Cupom ); // Fun��es Administrativas
    void Chq( String* Total, String* &Retorno, TStringList* &Cupom ); // Consulta de Cheque
    void Crt( String* Total, String* &Retorno, TStringList* &Cupom ); // Cart�o de Cr�dito/D�bito
    void Cnc( String* &Retorno, TStringList* &Cupom ); // Cancelamento de Venda
    void Cnf( String* &Retorno ); // Confirma��o da Venda e da Impress�o
    bool Ncn( String* &Retorno ); // N�o Confirma��o da Venda ou da Impress�o
    void ChecarErro( String* &Retorno ); // Quando Desliga o Micro, Checar Erros
    void ChecarErroTemp( String* &Retorno );
};
//---------------------------------------------------------------------------
#endif
