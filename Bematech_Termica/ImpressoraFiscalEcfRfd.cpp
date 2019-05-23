//---------------------------------------------------------------------------
#pragma hdrstop

#include "ImpressoraFiscalEcfRfd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TImpressoraFiscalRfd::TImpressoraFiscalRfd( void ) {

}
//---------------------------------------------------------------------------
__fastcall TImpressoraFiscalRfd::~TImpressoraFiscalRfd( void ) {

}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::AbrirCoxexaoSerial ( String *Erro ) {

  int CodigoRetorno;
  char Buffer[2048];

  this->iHandleDll = LoadLibrary( "ECF32M.dll" );
  if( iHandleDll == NULL ) {
    *Erro = "Erro ao carregar a biblioteca ECF3E32.DLL.\r\rFavor verificar!";
    return( false );
  }
  else {
      OpenCif = ( OPENCIF ) GetProcAddress( iHandleDll , "OpenCif" );
      CloseCif = ( CLOSECIF ) GetProcAddress( iHandleDll , "CloseCif" );
      RespostaComando = ( ESPERARESPOSTA ) GetProcAddress( iHandleDll , "EsperaResposta" );
      //AbreCupomFiscal = ( ABRECUPOM ) GetProcAddress( iHandleDll , "AbreCupomFiscal" );
      AbreCupomFiscalCpfCnpjNome = ( ABRECUPOM ) GetProcAddress( iHandleDll , "AbreCupomFiscalCPF_CNPJ_NOME" );
      VendaItem = ( VENDA ) GetProcAddress( iHandleDll , "VendaItemStr" );
      CancelamentoItem = ( CANCELAMENTO ) GetProcAddress( iHandleDll , "CancelamentoItem" );
      TotCupomSemDescAcres = ( TOTALIZA ) GetProcAddress( iHandleDll , "TotCupomSemDescAcres" );
      Pgto = ( PGTO ) GetProcAddress( iHandleDll , "Pagamento" );
      FechaCupom = ( FECHACUPOM ) GetProcAddress( iHandleDll , "FechaCupomFiscal" );
      CancelaCupomFiscal = ( CANCELACUPOM ) GetProcAddress( iHandleDll , "CancelaCupomFiscal" );
      PLeituraX = ( LEITURAX ) GetProcAddress( iHandleDll , "LeituraX" );
      PReducaoZ = ( REDUCAOZ ) GetProcAddress( iHandleDll , "ReducaoZ" );
      AbreCupomVinculado = ( ABRECUPV ) GetProcAddress( iHandleDll , "AbreCupomVinculado" );
      AbreCupomNaoVinculado = ( ABRECUPNV ) GetProcAddress( iHandleDll , "AbreCupomNaoVinculado" );
      ImprimeLinhaNaoFiscal = ( IMPLIN ) GetProcAddress( iHandleDll , "ImprimeLinhaNaoFiscal" );
      ImprimeTextoNaoFiscal = ( IMPLINTEXTO ) GetProcAddress( iHandleDll , "ImprimeLinhaNaoFiscal" );
      EncerraCupomNaoFiscal = ( ENCCUPOM ) GetProcAddress( iHandleDll , "EncerraCupomNaoFiscal" );
      EsperaResposta = ( ESPERARESPOSTA ) GetProcAddress( iHandleDll , "EsperaResposta" );
      ObterParEcf = ( TXPARECF ) GetProcAddress( iHandleDll , "EcfPar" );
      pGerarArquivoRfd = ( GerarArquivoRFD ) GetProcAddress( iHandleDll , "GerarArquivoRFD" );
      pValidarArquivoRfd = ( ValidarArquivoRFD ) GetProcAddress( iHandleDll , "ValidarArquivoRFD" );

      if( ( OpenCif == NULL ) || ( CloseCif == NULL ) || ( RespostaComando == NULL ) ||
          ( AbreCupomFiscalCpfCnpjNome == NULL ) || ( VendaItem == NULL ) ||
          ( CancelamentoItem == NULL ) || ( TotCupomSemDescAcres == NULL ) ||
          ( Pgto == NULL ) || ( FechaCupom == NULL ) || ( CancelaCupomFiscal == NULL ) ||
          ( PLeituraX == NULL ) || ( PReducaoZ == NULL ) || ( AbreCupomVinculado == NULL ) ||
          ( AbreCupomNaoVinculado == NULL ) || ( ImprimeLinhaNaoFiscal == NULL ) ||
          ( ImprimeTextoNaoFiscal == NULL ) || ( EncerraCupomNaoFiscal == NULL ) ||
          ( EsperaResposta == NULL ) || ( ObterParEcf == NULL ) || ( pGerarArquivoRfd == NULL ) ||
          ( pValidarArquivoRfd == NULL ) ) {
          FreeLibrary( this->iHandleDll );
          *Erro = "Erro ao carregar as fun��es da biblioteca ECF32M.dll.\r\rFavor verificar!";
          return( false );
      }
      else {
        OpenCif( );
        CodigoRetorno = RespostaComando( Buffer );
        if( CodigoRetorno >= 0 ) {
          return( true );
        }
        else {
          *Erro = this->ObterMensagemRetorno( CodigoRetorno ) + String(Buffer);
          return( false );
        }
      }
  }
}
//---------------------------------------------------------------------------
void __fastcall TImpressoraFiscalRfd::FecharConexaoSerial( ) {

  CloseCif( );
  if( this->iHandleDll != NULL ) {
	  FreeLibrary( this->iHandleDll );
  }
}
//---------------------------------------------------------------------------
/*
bool TImpressoraFiscalRfd::AbrirCupomFiscal( String *Erro ) {

  this->AbreCupomFiscal( );
  return( this->ObterRespostaComando( Erro ) );
}
*/
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::AbrirCupomFiscal( String *CpfCnpj, String *Nome, String *Erro ) {

  int i;
  String *CpfCnpjFmt;

  try {
    CpfCnpjFmt = new AnsiString( );

    if( !CpfCnpj->IsEmpty( ) ) {
      for( i = 1; i <= CpfCnpj->Length( ); i++ ) {
        if( ( ( AnsiCompareStr( CpfCnpj->SubString( i, 1 ), "0" ) >= 0 ) && ( AnsiCompareStr( CpfCnpj->SubString( i, 1 ), "9" ) <= 0 ) ) ) {
          *CpfCnpjFmt = *CpfCnpjFmt + CpfCnpj->SubString( i, 1 );
        }
      }
      *CpfCnpjFmt = LeftStr( *CpfCnpjFmt, 14 );
    }
    *Nome = LeftStr( *Nome, 14 );

    this->AbreCupomFiscalCpfCnpjNome( CpfCnpjFmt->c_str( ), Nome->c_str( ) );
    return( this->ObterRespostaComando( Erro ) );
  }
  __finally {
    delete CpfCnpjFmt;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::LancarItemFiscal( String *Qtd, String *PrecoUnit, String *TaxaImposto,
                                            String *Codigo, String *DescricaoProduto,
                                            String *Erro ) {

  String *Formato, *TipoDesconto, *ValorDesconto, *Unidade, *TamanhoDescricaoItem,
         *LegendaOperacao;

  try {
    //formato dos digitos inteiros e decimais p/ quantidade e preco unitario
    Formato = new AnsiString( "G" );
    // formatando quantidade 4 dig inteiro e 3 dig decimais
    while( Qtd->Length( ) < 4 ) {
      Qtd->Insert( "0", 1 );
    }
    *Qtd = *Qtd + "000";
    // formatando preco unitario 9 dig inteiro e 2 dig decimais
    *PrecoUnit = StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll );
    *PrecoUnit = StringReplace( *PrecoUnit, ",", "", TReplaceFlags( ) << rfReplaceAll );
    while( PrecoUnit->Length( ) < 11 ) {
      PrecoUnit->Insert( "0", 1 );
    }
    // formatando taxa imposto icms
    if( *TaxaImposto == "0" ) {
      *TaxaImposto = "I00";
    }
    else if( *TaxaImposto == "2,15" ) {
      *TaxaImposto = "T01";
    }
    else if( *TaxaImposto == "3,10" ) {
      *TaxaImposto =="T02";
    }
    else if( *TaxaImposto == "5,00" ) {
      *TaxaImposto = "T00";
    }
    else if( *TaxaImposto == "7,00" ) {
      *TaxaImposto = "T04";
    }
    else if( *TaxaImposto == "12,00" ) {
      *TaxaImposto = "T05";
    }
    else if( *TaxaImposto == "18,00" ) {
      *TaxaImposto = "T03";
    }
    else {
      *TaxaImposto = "I00";
    }
    //formato tipo de desconto
    TipoDesconto = new AnsiString( "1" );
    //formato valor do desconto
    ValorDesconto = new AnsiString( "000000000000000" );
    //formato da unidade do item
    Unidade = new AnsiString( "pc" );
    //formato do codigo do item
    *Codigo = LeftStr( *Codigo, 13 );
    while( Codigo->Length( ) < 13 ) {
      Codigo->Insert( " ", 1 );
    }
    //formato do tamanho da descricao do item
    if( DescricaoProduto->Length( ) < 20 ) {
      TamanhoDescricaoItem = new AnsiString( "0" );
      while( DescricaoProduto->Length( ) < 20 ) {
        DescricaoProduto->Insert( " ", 1 );
      }
    }
    else if( DescricaoProduto->Length( ) < 38 ) {
      TamanhoDescricaoItem = new AnsiString( "1" );
      while( DescricaoProduto->Length( ) < 38 ) {
        DescricaoProduto->Insert( " ", 1 );
      }
    }
    else if( DescricaoProduto->Length( ) < 76 ) {
      TamanhoDescricaoItem = new AnsiString( "2" );
      while( DescricaoProduto->Length( ) < 76 ) {
        DescricaoProduto->Insert( " ", 1 );
      }
    }
    else if( DescricaoProduto->Length( ) < 114 ) {
      TamanhoDescricaoItem = new AnsiString( "3" );
      while( DescricaoProduto->Length( ) < 114 ) {
        DescricaoProduto->Insert( " ", 1 );
      }
    }
    else if( DescricaoProduto->Length( ) < 152 ) {
      TamanhoDescricaoItem = new AnsiString( "4" );
      while( DescricaoProduto->Length( ) < 152 ) {
        DescricaoProduto->Insert( " ", 1 );
      }
    }
    else if( DescricaoProduto->Length( ) < 190 ) {
      TamanhoDescricaoItem = new AnsiString( "5" );
      while( DescricaoProduto->Length( ) < 190 ) {
        DescricaoProduto->Insert( " ", 1 );
      }
    }
    else {
      TamanhoDescricaoItem = new AnsiString( "5" );
      *DescricaoProduto = LeftStr( *DescricaoProduto, 190 );
    }
    LegendaOperacao = new AnsiString( );

    this->VendaItem( Formato->c_str( ), Qtd->c_str( ), PrecoUnit->c_str( ), TaxaImposto->c_str( ), TipoDesconto->c_str( ), ValorDesconto->c_str( ), Unidade->c_str( ), Codigo->c_str( ), TamanhoDescricaoItem->c_str( ), DescricaoProduto->c_str( ), LegendaOperacao->c_str( ) );
    return( this->ObterRespostaComando( Erro ) );
  }
  __finally {
    delete Formato;
    delete TipoDesconto;
    delete ValorDesconto;
    delete Unidade;
    delete TamanhoDescricaoItem;
    delete LegendaOperacao;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::CancelarItem( int IndexItem, String *Erro ) {

  this->CancelamentoItem( String(IndexItem).c_str( ) );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::TotalizarCupom( String *Erro ) {

  this->TotCupomSemDescAcres( );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::Pagamento( String *ModoPagamento, String *VPgto, String *Erro ) {

  // formatando o modo de pagamento
  if( *ModoPagamento == "Dinheiro" ) {
    *ModoPagamento = "00";
  }
  else if( *ModoPagamento == "Cheque" ) {
    *ModoPagamento = "01";
  }
  else if( *ModoPagamento == "Cartao Debito" ) {
    *ModoPagamento = "02";
  }
  else if( *ModoPagamento == "Cartao Credito" ) {
    *ModoPagamento = "03";
  }
  else if( *ModoPagamento == "Financiado" ) {
    *ModoPagamento = "04";
  }
  else {
    *ModoPagamento = "00";
  }
  // formatando o valor do pagamento
  *VPgto = StringReplace( *VPgto, ".", "", TReplaceFlags( ) << rfReplaceAll );
  *VPgto = StringReplace( *VPgto, ",", "", TReplaceFlags( ) << rfReplaceAll );
  while( VPgto->Length( ) < 15 ) {
    VPgto->Insert( "0", 1 );
  }

  this->Pgto( ModoPagamento->c_str( ), VPgto->c_str( ), "1" );
  return( this->ObterRespostaComando( Erro ) );
}  
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::FecharCupomFiscal( String *Vendedor, String *Erro ) {

  String *TamMensagem, *Mensagem;

  try {
    TamMensagem = new AnsiString( );
    Mensagem = new AnsiString( );

    *Mensagem = "Vendedor: " + *Vendedor;
    while( Mensagem->Length( ) <= 48 ) {
      *Mensagem = *Mensagem + " ";
    }
    *Mensagem = *Mensagem + "                                                ";
    *Mensagem = *Mensagem + "    Visite Nosso Salao de Exposicao Consigo!    ";
    *Mensagem = *Mensagem + "     CONSIGO - A CERTEZA DE UM BOM NEGOCIO      ";
    *Mensagem = *Mensagem + "     TEL: (11)3214-2660  FAX: (11)3214-5896     ";

    if( Mensagem->Length( ) >= 100 ) {
      *TamMensagem = "S" + String( Mensagem->Length( ) );
    }
    else if( Mensagem->Length( ) >= 10 ) {
      *TamMensagem = "S0" + String( Mensagem->Length( ) );
    }
    else{
      *TamMensagem = "S00" + String( Mensagem->Length( ) );
    }

    this->FechaCupom( TamMensagem->c_str( ), Mensagem->c_str( ) );
    return( this->ObterRespostaComando( Erro ) );
  }
  __finally {
    delete TamMensagem;
    delete Mensagem;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::CancelarCupomFiscal( String *Erro ) {

  this->CancelaCupomFiscal( );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::LeituraX( String *Erro ) {

  AnsiString *RelatorioGerencial;

  try {
    RelatorioGerencial = new AnsiString( "0" );
    this->PLeituraX( RelatorioGerencial->c_str( ) );
    return( this->ObterRespostaComando( Erro ) );
  }
  __finally {
    delete RelatorioGerencial;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::ReducaoZ( String *Erro ) {

  AnsiString *RelatorioGerencial;

  try {
    RelatorioGerencial = new AnsiString( "0" );
    this->PReducaoZ( RelatorioGerencial->c_str( ) );
    return( this->ObterRespostaComando( Erro ) );
  }
  __finally {
    delete RelatorioGerencial;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::AbrirCupomNaoFiscalVinculado( String *Erro ) {

  this->AbreCupomVinculado( );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::AbrirCupomNaoFiscalNaoVinculado( String *Erro ) {

  this->AbreCupomNaoVinculado( );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::ImprimirLinhaNaoFiscal( String *Texto, String *Erro ) {

  *Texto = LeftStr( *Texto, 48 );
  if( Texto->Length( ) < 48 ) {
    while( Texto->Length( ) < 48 ) {
      *Texto = *Texto + " ";
    }
  }
  this->ImprimeLinhaNaoFiscal( "0", Texto->c_str( ) );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::ImprimirTextoNaoFiscal( String *Texto, String *Erro ) {

  this->ImprimeTextoNaoFiscal( "0", (LeftStr( *Texto, 999 )).c_str( ) );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::FecharCupomNaoFiscal( String *Erro ) {

  this->EncerraCupomNaoFiscal( );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::ObterNumeroUltimoCupomFiscal( int &UltimoCupom, String *Erro ) {

  int CodRetorno, i;
  char BufferRetorno[2048];
  String *Numero;

  try {
    Numero = new AnsiString( );

    CodRetorno = this->ObterParEcf( "41" );
    if( CodRetorno < 0 ) {
  	  *Erro = this->ObterMensagemRetorno( CodRetorno );
      return( false );
    }
    else {
      CodRetorno = this->EsperaResposta( BufferRetorno );
      if( CodRetorno >= 0 ) {
        *Numero = BufferRetorno;
        *Numero = Numero->SubString( 6, 6 );
        UltimoCupom = Numero->ToInt( );
        UltimoCupom++;
        *Erro = "";
        return( true );
      }
      else {
    	  *Erro = this->ObterMensagemRetorno( CodRetorno );
        return( false );
      }
    }
  }
  __finally {
    delete Numero;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::GerarArquivoRfd( String *Data, String *CaminhoDaPastaDestino, String *Erro ) {

  //StringReplace( *Data, "/", "", TReplaceFlags( ) << rfReplaceAll );
  *Data = "";
  this->pGerarArquivoRfd( Data->c_str( ), CaminhoDaPastaDestino->c_str( ) );
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::ValidarArquivoRfd( String *CaminhoDoArquivo, String *RetornoMd5, String *Erro ) {

  char Buffer[32+1];

  this->pValidarArquivoRfd( CaminhoDoArquivo->c_str( ), &Buffer[0], 32 );
  *RetornoMd5 = Buffer;
  return( this->ObterRespostaComando( Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalRfd::ObterRespostaComando( String *Erro ) {

  char Buffer[2048];
  int CodigoRetornoComando;

  CodigoRetornoComando = this->EsperaResposta( Buffer );
  if( CodigoRetornoComando >= 0 ) {
    *Erro = "";
    return( true );
  }
  else {
    *Erro = this->ObterMensagemRetorno( CodigoRetornoComando );
    *Erro = *Erro + String(Buffer);
    return( false );
  }
}
//---------------------------------------------------------------------------
String TImpressoraFiscalRfd::ObterMensagemRetorno( int CodigoRetornoComando ) {

  switch( char(CodigoRetornoComando) ) {
    case 0: return( "Fun��o executada com sucesso" );
    case 1: return( "Fun��o executada com sucesso. Detectado pouco papel");
    case 2: return( "Fun��o executada com sucesso. Cancelando Cupom");
    case 3: return( "Fun��o executada com sucesso.Abrindo Cupom Rel Gerencial");

    case -1: return( "O cabe�alho cont�m caracteres inv�lidos");
    case -2: return( "Comando inexistente");
    case -3: return( "Valor n�o num�rico em campo num�rico");
    case -4: return( "Valor fora da faixa entre 20h e 7Fh");
    case -5: return( "Campo deveria iniciar com @, & ou %");
    case -6: return( "Troco j� realizado.");
    case -7: return( "O intervalo � inconsistente. No caso de datas, valores anteriores a 01/01/1995 ser�o considerados como pertencentes ao intervalo 2000-2094");
    case -9: return( "A string TOTAL n�o � aceita");
    case -10: return( "A sintaxe do comando est� errada");
    case -11: return( "Execedeu o n�mero m�ximo de linhas permitido pelo comando");
    case -12: return( "O terminador enviado n�o est� obedecendo o protocolo de comunica��o");
    case -13: return( "O checksum enviado est� incorreto");
    case -15: return( "A situa��o tribut�ria deve iniciar com T, F ou N");
    case -16: return( "Data inv�lida");
    case -17: return( "Hora inv�lida");
    case -18: return( "Al�quota n�o programada ou fora da intervalo");
    case -19: return( "O campo de sinal est� incorreto");
    case -20: return( "Comando s� aceito durante Interven��o Fiscal");
    case -21: return( "Comando s� aceito durante Modo Normal");
    case -22: return( "Necess�rio abrir Cupom Fiscal");
    case -23: return( "Comando n�o aceito durante Cupom Fiscal");
    case -24: return( "Necess�rio abrir Cupom N�o Fiscal");
    case -25: return( "Comando n�o aceito durante Cupom N�o Fiscal");
    case -26: return( "O rel�gio j� est� em hor�rio de ver�o");
    case -27: return( "O rel�gio n�o est� em hor�rio de ver�o");
    case -28: return( "Necess�rio realizar Redu��o Z");
    case -29: return( "Fechamento do dia (Redu��o Z) j� executado");
    case -30: return( "Necess�rio programar legenda");
    case -31: return( "Item j� cancelado ou item inexistente");
    case -32: return( "Cupom anterior n�o pode ser cancelado");
    case -33: return( "Detectado Falta de Papel");
    case -36: return( "Necess�rio programar os dados do estabelecimento");
    case -37: return( "Necess�rio realizar Interven��o Fiscal");
    case -38: return( "A Mem�ria Fiscal n�o permite mais realizar vendas.S� � poss�vel executar Leitura X ou Leitura da Mem�ria Fiscal");
    case -39: return( "A Mem�ria Fiscal n�o permite mais realizar vendas.S� � poss�vel executar Leitura X ou Leitura da Mem�ria Fiscal.Ocorreu algum problema na mem�ria NOVRAM.Ser� necess�rio realizar uma Interven��o Fiscal");
    case -40: return( "Necess�rio programar a data do rel�gio");
    case -41: return( "N�mero m�ximo de itens por cupom ultrapassado");
    case -42: return( "J� foi realizado o ajuste de hora di�rio");
    case -43: return( "Comando v�lido ainda em execu��o");
    case -44: return( "Est� em estado de impress�o de cheques");
    case -45: return( "N�o est� em estado de impress�o de cheques");
    case -46: return( "Necess�rio inserir o cheque");
    case -47: return( "Necess�rio inserir nova bobina");
    case -48: return( "Necess�rio executar uma Leitura X");
    case -49: return( "Detectado algum problema na impressora (paper jam, sobretens�o, etc)");
    case -50: return( "Cupom j� foi totalizado");
    case -51: return( "Necess�rio totalizar Cupom antes de fechar");
    case -52: return( "Necess�rio finalizar Cupom antes de fechar");
    case -53: return( "Ocorreu erro de grava��o da mem�ria fiscal");
    case -54: return( "Excedeu n�mero m�ximo de estabelecimentos");
    case -55: return( "Mem�ria Fiscal n�o iniciada");
    case -56: return( "Ultrapassou valor do pagamento");
    case -57: return( "Registrador n�o programado ou troco j� realizado");
    case -58: return( "Falta completar valor do pagamento");
    case -59: return( "Campo somente de caracteres n�o-num�ricos");
    case -60: return( "Excedeu campo m�ximo de caracteres");
    case -61: return( "Troco n�o realizado");
    case -62: return( "Comando desabilitado");
    case -83: return( "Ocorreu Fim de Papel");
    case -84: return( "Falha Geral");
    case -85: return( "Comando nao recebido pelo ECF");
    case -86: return( "Erro no arquivo Cif.ini");
    case -87: return( "Erro na abertura da serial");
    case -88: return( "Erro na alocacao de recursos do windows");
    case -89: return( "Retorno nao identificado");
    case -90: return( "Falha na leitura da serial");
    case -91: return( "Temperatura da cabe�a est� alta");
    case -92: return( "Detectado pouco papel");
    case -94: return( "Erro Irrecuperavel");
    case -95: return( "Erro Mec�nico");
    case -96: return( "A tampa est� aberta. Verifique a impressora");
    case -97: return( "Ainda n�o obteve retorno");
    case -98: return( "Overflow");
    case -99: return( "TimeOut na execucao do comando");
  }
}
//---------------------------------------------------------------------------