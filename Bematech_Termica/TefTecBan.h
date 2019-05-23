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

    void Atv( String* &Retorno ); // Verifica se o Gerenciador Padrão está ATIVO !!!
    bool Adm( String* &Retorno, TStringList* &Cupom ); // Funções Administrativas
    void Chq( String* Total, String* &Retorno, TStringList* &Cupom ); // Consulta de Cheque
    void Crt( String* Total, String* &Retorno, TStringList* &Cupom ); // Cartão de Crédito/Débito
    void Cnc( String* &Retorno, TStringList* &Cupom ); // Cancelamento de Venda
    void Cnf( String* &Retorno ); // Confirmação da Venda e da Impressão
    bool Ncn( String* &Retorno ); // Não Confirmação da Venda ou da Impressão
    void ChecarErro( String* &Retorno ); // Quando Desliga o Micro, Checar Erros
    void ChecarErroTemp( String* &Retorno );
};
//---------------------------------------------------------------------------
#endif
