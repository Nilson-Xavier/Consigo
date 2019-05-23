//---------------------------------------------------------------------------
#ifndef ImpressoraFiscalBematechH
#define ImpressoraFiscalBematechH

#include <vcl\StrUtils.hpp>
//---------------------------------------------------------------------------
class TImpressoraFiscalBematech : public TObject {
  private:
    bool ObterRespostaComando( int CodigoRetornoComando, String *Erro );

  public:
    __fastcall TImpressoraFiscalBematech( void );
    __fastcall ~TImpressoraFiscalBematech( void );

    bool AbrirCupomFiscal( String *CpfCnpj, String *Erro );
    bool LancarItemFiscal( String *Qtd, String *PrecoUnit, String *TaxaImposto, String *Codigo,
                           String *DescricaoProduto, String *Erro );
    bool TotalizarCupom( String *Erro );
    bool Pagamento( String *ModoPagamento, String *VPgto, String *Erro );
    bool FecharCupomFiscal( String *Vendedor, String *Erro );
    bool CancelarCupomFiscal( String *Erro );
    bool LeituraX( String *Erro );
    bool ReducaoZ( String *Erro );
    bool AbrirCupomNaoFiscalVinculado( String *FormaPagamento, String *Valor, String *NumeroCupom, String *Erro );
    bool ImprimirLinhaNaoFiscal( String *Texto, String *Erro );
    bool FecharCupomNaoFiscal( String *Erro );
    bool ObterNumeroUltimoCupomFiscal( int &UltimoCupom, String *Erro );
    bool GerarArquivoRfd( String *ArquivoMfd, String *Data, String *Erro );
};
//---------------------------------------------------------------------------

//--------------- Declaração das funções da DLL BemaFI32 --------------------
extern "C" __stdcall int Bematech_FI_GeraRegistrosCAT52MFD( char* Arquivo, char* Data );
extern "C" __stdcall int Bematech_FI_LeituraX(void);
extern "C" __stdcall int Bematech_FI_FechaPortaSerial(void);
extern "C" __stdcall int Bematech_FI_VerificaImpressoraLigada(void);
extern "C" __stdcall int Bematech_FI_RetornoImpressora (int* ACK, int* ST1, int* ST2);
extern "C" __stdcall int Bematech_FI_AumentaDescricaoItem (char* Descricao);
extern "C" __stdcall int Bematech_FI_AbrePortaSerial(void);
extern "C" __stdcall int Bematech_FI_ProgramaAliquota (char* Aliquota, int Tipo);
extern "C" __stdcall int Bematech_FI_ProgramaHorarioVerao(void);
extern "C" __stdcall int Bematech_FI_NomeiaTotalizadorNaoSujeitoIcms(int Indice, char* Totalizador);
extern "C" __stdcall int Bematech_FI_ProgramaArredondamento(void);
extern "C" __stdcall int Bematech_FI_ProgramaTruncamento (void);
extern "C" __stdcall int Bematech_FI_NomeiaDepartamento (int Indice, char* Departamento);
extern "C" __stdcall int Bematech_FI_LinhasEntreCupons (int Linhas);
extern "C" __stdcall int Bematech_FI_EspacoEntreLinhas (int Dots);
extern "C" __stdcall int Bematech_FI_ForcaImpactoAgulhas (int ForcaImpacto);
extern "C" __stdcall int Bematech_FI_ResetaImpressora(void);
extern "C" __stdcall int Bematech_FI_AbreCupom (char* CGC);
extern "C" __stdcall int Bematech_FI_VendeItem (char* Codigo, char* Descricao, char* Aliquota,char* TipoQuantidade, char* Quantidade,short CasasDecimais,char* ValorUnitario,char* TipoDesconto, char* ValorDesconto );
extern "C" __stdcall int Bematech_FI_VendeItemDepartamento (char* Codigo, char* Descricao,char* Aliquota, char* ValorUnitario,char* Quantidade, char* Acrescimo,char* Desconto, char* IndiceDepartamento,char* cUnidadeMedida);
extern "C" __stdcall int Bematech_FI_CupomResumido (char* FormaPagamento,char* Mensagem);
extern "C" __stdcall int Bematech_FI_CancelaCupom(void);
extern "C" __stdcall int Bematech_FI_CancelaItemAnterior ( void );
extern "C" __stdcall int Bematech_FI_CancelaItemGenerico ( char * NumeroItem );
extern "C" __stdcall int Bematech_FI_FechaCupomResumido ( char * FormaPagamento,char * Mensagem );
extern "C" __stdcall int Bematech_FI_UsaUnidadeMedida (char* UnidadeMedida);
extern "C" __stdcall int Bematech_FI_ReducaoZ (char* Data, char* Hora);
extern "C" __stdcall int Bematech_FI_LeituraXSerial(void);
extern "C" __stdcall int Bematech_FI_LeituraMemoriaFiscalData (char* DataInicial, char* DataFinal);
extern "C" __stdcall int Bematech_FI_LeituraMemoriaFiscalReducao (char* ReducaoInicial,char* ReducaoFinal);
extern "C" __stdcall int Bematech_FI_LeituraMemoriaFiscalSerialData (char* DataInicial,char* DataFinal);
extern "C" __stdcall int Bematech_FI_LeituraMemoriaFiscalSerialReducao (char* ReducaoInicial,char* ReducaoFinal);
extern "C" __stdcall int Bematech_FI_RelatorioGerencial (char* Texto);
extern "C" __stdcall int Bematech_FI_FechaRelatorioGerencial(void);
extern "C" __stdcall int Bematech_FI_RecebimentoNaoFiscal (char* IndiceTotalizador,char* ValorRecebimento,char* FormaPagamento);
extern "C" __stdcall int Bematech_FI_AbreComprovanteNaoFiscalVinculado(char* FormaPagamento,char* Valor,char* NumeroCupom);
extern "C" __stdcall int Bematech_FI_AbreComprovanteNaoFiscalVinculadoMFD( char* FormaPagamento, char* Valor, char* NumeroCupom, char* CGC, char* nome, char* Endereco );
extern "C" __stdcall int Bematech_FI_IniciaFechamentoCupom( char * cAcrescimoDesconto,char * cTipoAcrescimoDesconto,char * cValorAcrescimoDesconto );
extern "C" __stdcall int Bematech_FI_EfetuaFormaPagamentoDescricaoForma(char * cFormaPagamento,char * cValorFormaPagamento,char * cDescricaoForma );
extern "C" __stdcall int Bematech_FI_EfetuaFormaPagamento( char * cFormaPagamento,char * cValorFormaPagamento );
extern "C" __stdcall int Bematech_FI_EfetuaFormaPagamentoIndice( char * cFormaPagamentoIndice,char * cValorFormaPagamento );
extern "C" __stdcall int Bematech_FI_TerminaFechamentoCupom ( char * cMensagem );
extern "C" __stdcall int Bematech_FI_UsaComprovanteNaoFiscalVinculado (char* Texto);
extern "C" __stdcall int Bematech_FI_FechaComprovanteNaoFiscalVinculado(void);
extern "C" __stdcall int Bematech_FI_Sangria (char* Valor);
extern "C" __stdcall int Bematech_FI_Suprimento (char* Valor, char* FormaPagamento);
extern "C" __stdcall int Bematech_FI_Autenticacao(void);
extern "C" __stdcall int Bematech_FI_ProgramaCaracterAutenticacao(char* Coordenadas);
extern "C" __stdcall int Bematech_FI_AcionaGaveta(void);
extern "C" __stdcall int Bematech_FI_VerificaEstadoGaveta (short int* Estado);
extern "C" __stdcall int Bematech_FI_VerificaEstadoImpressora (short int* ACK,short int* ST1,short int* ST2);
extern "C" __stdcall int Bematech_FI_RetornoAliquotas(char* Aliquotas);
extern "C" __stdcall int Bematech_FI_SubTotal (char* SubTotal);
extern "C" __stdcall int Bematech_FI_MonitoramentoPapel (int* LinhasImpressas);
extern "C" __stdcall int Bematech_FI_DadosUltimaReducao (char* DadosReducao);
extern "C" __stdcall int Bematech_FI_NumeroSerie (char* NumeroSerie);
extern "C" __stdcall int Bematech_FI_VersaoFirmware (char* VersaoFirmware);
extern "C" __stdcall int Bematech_FI_CGC_IE (char* CGC, char* IE);
extern "C" __stdcall int Bematech_FI_GrandeTotal (char* GrandeTotal);
extern "C" __stdcall int Bematech_FI_Descontos (char* Descontos);
extern "C" __stdcall int Bematech_FI_Cancelamentos (char* Cancelamentos);
extern "C" __stdcall int Bematech_FI_NumeroCupom (char* NumeroCupom);
extern "C" __stdcall int Bematech_FI_NumeroOperacoesNaoFiscais (char* Operacoes);
extern "C" __stdcall int Bematech_FI_NumeroCuponsCancelados (char* CuponsCancelados);
extern "C" __stdcall int Bematech_FI_NumeroReducoes (char* Reducoes);
extern "C" __stdcall int Bematech_FI_NumeroIntervencoes (char* Intervencoes);
extern "C" __stdcall int Bematech_FI_NumeroSubstituicoesProprietario (char* Substituicoes);
extern "C" __stdcall int Bematech_FI_UltimoItemVendido (char* UltimoItem);
extern "C" __stdcall int Bematech_FI_ClicheProprietario(char* ClicheProprietario);
extern "C" __stdcall int Bematech_FI_NumeroCaixa (char* NumeroCaixa);
extern "C" __stdcall int Bematech_FI_NumeroLoja (char* NumeroLoja);
extern "C" __stdcall int Bematech_FI_AlteraSimboloMoeda (char* SimboloMoeda);
extern "C" __stdcall int Bematech_FI_SimboloMoeda (char* SimboloMoeda);
extern "C" __stdcall int Bematech_FI_FlagsFiscais (int* FlagFiscal);
extern "C" __stdcall int Bematech_FI_MinutosLigada (char* MinutosLigada);
extern "C" __stdcall int Bematech_FI_MinutosImprimindo (char* MinutosImprimindo);
extern "C" __stdcall int Bematech_FI_ModoOperacao (char* ModoOperacao);
extern "C" __stdcall int Bematech_FI_VerificaEpromConectada (char* FlagEprom );
extern "C" __stdcall int Bematech_FI_ValorPagoUltimoCupom (char* Valor);
extern "C" __stdcall int Bematech_FI_DataHoraImpressora (char* Data, char* Hora);
extern "C" __stdcall int Bematech_FI_ContadoresTotalizadoresNaoFiscais (char* Contadores);
extern "C" __stdcall int Bematech_FI_VerificaTotalizadoresNaoFiscais (char* Totalizadores);
extern "C" __stdcall int Bematech_FI_VerificaTotalizadoresParciais ( char * cTotalizadores );
extern "C" __stdcall int Bematech_FI_VerificaModoOperacao( char * cModo );
extern "C" __stdcall int Bematech_FI_DataHoraReducao (char* DataReducao, char* HoraReducao);
extern "C" __stdcall int Bematech_FI_VerificaIndiceAliquotasIss ( char * cIndices );
extern "C" __stdcall int Bematech_FI_VerificaFormasPagamento ( char * cFormas );
extern "C" __stdcall int Bematech_FI_VerificaDepartamentos ( char * cDepartamentos );
extern "C" __stdcall int Bematech_FI_DataMovimento (char* DataMovimento);
extern "C" __stdcall int Bematech_FI_VerificaTruncamento (char* FlagTruncamento);
extern "C" __stdcall int Bematech_FI_VerificaAliquotasIss (char* AliquotasIss);
extern "C" __stdcall int Bematech_FI_Acrescimos (char* ValorAcrescimo);
extern "C" __stdcall int Bematech_FI_ContadorBilhetePassagem (char* NumeroBilhetes);
extern "C" __stdcall int Bematech_FI_VerificaFormasPagamento (char* FormasPagamento);
extern "C" __stdcall int Bematech_FI_VerificaRecebimentoNaoFiscal (char* Recebimentos);
extern "C" __stdcall int Bematech_FI_VerificaDepartamentos (char* Departamentos);
extern "C" __stdcall int Bematech_FI_VerificaTipoImpressora (int* TipoImpressora );
extern "C" __stdcall int Bematech_FI_ProgramaMoedaSingular (char* MoedaSingular);
extern "C" __stdcall int Bematech_FI_ProgramaMoedaPlural (char* MoedaPlural);
extern "C" __stdcall int Bematech_FI_VerificaStatusCheque (short int * StatusCheque);
extern "C" __stdcall int Bematech_FI_CancelaImpressaoCheque(void);
extern "C" __stdcall int Bematech_FI_ImprimeCheque (char* NumeroBanco, char* Valor,char* Favorecido, char* Cidade,char* Data, char*  Mensagem);
extern "C" __stdcall int Bematech_FI_IncluiCidadeFavorecido (char* Cidade, char* Favorecido);
extern "C" __stdcall int Bematech_FI_EstornoFormasPagamento (char * FormaOrigem, char * FormaDestino, char * Valor );
extern "C" __stdcall int Bematech_FI_AbreBilhetePassagem( char * ImprimeValorFinal, char * ImprimeEnfatizado,
                                                          char * Embarque, char * Destino, char * Linha,
                                                          char * Prefixo, char * Agente, char * Agencia,
                                                          char * Data, char * Hora, char * Poltrona, char * Plataforma );
extern "C" __stdcall int Bematech_FI_MapaResumo(void);
extern "C" __stdcall int Bematech_FI_RelatorioTipo60Analitico(void);
extern "C" __stdcall int Bematech_FI_RelatorioTipo60Mestre(void);
extern "C" __stdcall int Bematech_FI_AberturaDoDia(char* Valor, char* FormaPagamento);
extern "C" __stdcall int Bematech_FI_FechamentoDoDia(void);
extern "C" __stdcall int Bematech_FI_VerificaIndiceAliquotasIss( char * IndiceAliquotasISS );
extern "C" __stdcall int Bematech_FI_ImprimeConfiguracoesImpressora( void );
extern "C" __stdcall int Bematech_FI_ImprimeDepartamentos( void );

// Funções para a impressora restaurante

extern "C" __stdcall int Bematech_FIR_RegistraVenda (char* Mesa, char* Codigo, char* Descricao,char *  Aliquota,  char  *  Quantidade,char* ValorUnitario, char* FlagAcrescimoDesconto,char* ValorAcrescimoDesconto);
extern "C" __stdcall int Bematech_FIR_CancelaVenda(char*,char*,char*,char*,char*,char*,char*,char*);
extern "C" __stdcall int Bematech_FIR_AbreConferenciaMesa (char* Mesa);
extern "C" __stdcall int Bematech_FIR_FechaConferenciaMesa (char* FlagAcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto);
extern "C" __stdcall int Bematech_FIR_ConferenciaMesa(char* Mesa,char* FlagAcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto);
extern "C" __stdcall int Bematech_FIR_TransferenciaMesa(char* MesaOrigem, char* MesaDestino);
extern "C" __stdcall int Bematech_FIR_TransferenciaItem (char* MesaOrigem, char* Codigo,char* Descricao, char *  Aliquota,char* Quantidade,  char* ValorUnitario,char* FlagAcrescimoDesconto,char* ValorAcrescimoDesconto,char* MesaDestino);
extern "C" __stdcall int Bematech_FIR_AbreCupomRestaurante (char* Mesa, char* CPF);
extern "C" __stdcall int Bematech_FIR_FechaCupomRestaurante (char* FormaPagamento,char* AcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto,char* ValorPago,char* Mensagem);
extern "C" __stdcall int Bematech_FIR_FechaCupomResumidoRestaurante(char* FormaPagamento,char* Mensagem);
extern "C" __stdcall int Bematech_FIR_ContaDividida (char* NumeroCupons,  char* ValorPago,char* CPF);
extern "C" __stdcall int Bematech_FIR_FechaCupomContaDividida (char* NumeroCupons,char* AcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto,char* FormaPagamento,char* ValorFormaPagamento,char* ValorPagoCliente,char* CPF);
extern "C" __stdcall int Bematech_FIR_RelatorioMesasAbertas (short int TipoRelatorio);
extern "C" __stdcall int Bematech_FIR_RelatorioMesasAbertasSerial (void);
extern "C" __stdcall int Bematech_FIR_ImprimeCardapio (void);
extern "C" __stdcall int Bematech_FIR_CardapioPelaSerial (void);
extern "C" __stdcall int Bematech_FIR_RegistroVendaSerial (char* Mesa);
extern "C" __stdcall int Bematech_FIR_VerificaMemoriaLivre(char* Bytes);
extern "C" __stdcall int Bematech_FIR_TransferenciaItem( char * cMesaOrigem,char * cCodigo,char * cDescricao,char * cAliquota,char * cQuantidade,char * cValorUnitario,char * cFlagAcrescimoDesconto,char * cValorAcrescimoDesconto,char * cMesaDestino );
//---------------------------------------------------------------------------
#endif
