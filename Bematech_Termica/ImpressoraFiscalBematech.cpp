//---------------------------------------------------------------------------
#pragma hdrstop

#include "ImpressoraFiscalBematech.h"
#include <Classes.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TImpressoraFiscalBematech::TImpressoraFiscalBematech( void ) {

}
//---------------------------------------------------------------------------
__fastcall TImpressoraFiscalBematech::~TImpressoraFiscalBematech( void ) {

}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::AbrirCupomFiscal( String *CpfCnpj, String *Erro ) {

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

    return( this->ObterRespostaComando( Bematech_FI_AbreCupom( CpfCnpjFmt->c_str( ) ), Erro ) );
  }
  __finally {
    delete CpfCnpjFmt;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::LancarItemFiscal( String *Qtd, String *PrecoUnit, String *TaxaImposto, String *Codigo,
                                                  String *DescricaoProduto, String *Erro ) {

  String *ValorDesconto, *TipoQtd, *TipoDesconto, *IndiceTaxaImposto;

  try {
    ValorDesconto = new AnsiString( "0000" );
    TipoQtd = new AnsiString( "I" );
    TipoDesconto = new AnsiString( "$" );
    IndiceTaxaImposto = new AnsiString( );
    *PrecoUnit = StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll );

    // formatando taxa imposto icms
    if( *TaxaImposto == "0" ) {
      *IndiceTaxaImposto = "00";
    }
    else if( *TaxaImposto == "18,00" ) {
      *IndiceTaxaImposto = "01";
    }
    else if( *TaxaImposto == "7,00" ) {
      *IndiceTaxaImposto = "02";
    }
    else if( *TaxaImposto == "12,00" ) {
      *IndiceTaxaImposto = "03";
    }
    else if( *TaxaImposto == "25,00" ) {
      *IndiceTaxaImposto = "04";
    }
    /*
    else if( *TaxaImposto == "2,15" ) {
      *TaxaImposto = "01";
    }
    else if( *TaxaImposto == "3,10" ) {
      *TaxaImposto =="02";
    }
    else if( *TaxaImposto == "5,00" ) {
      *TaxaImposto = "03";
    }
    */
    else {
      *TaxaImposto = "00";
    }

    return( this->ObterRespostaComando( Bematech_FI_VendeItem( LeftStr( *Codigo, 13 ).c_str( ), LeftStr( *DescricaoProduto, 29 ).c_str( ), IndiceTaxaImposto->c_str( ), TipoQtd->c_str( ), LeftStr( *Qtd, 4 ).c_str( ), 2, LeftStr( *PrecoUnit, 8 ).c_str( ), TipoDesconto->c_str( ), ValorDesconto->c_str( ) ), Erro ) );
  }
  __finally {
    delete TipoDesconto;
    delete ValorDesconto;
    delete TipoQtd;
    delete IndiceTaxaImposto;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::TotalizarCupom( String *Erro ) {

  String *ValorAcrescimoDesconto, *AcrescimoDesconto, *TipoAcrescimoDesconto;

  try {
    AcrescimoDesconto = new AnsiString( "D" );
    TipoAcrescimoDesconto = new AnsiString( "$" );
    ValorAcrescimoDesconto = new AnsiString( "0000" );

    return( this->ObterRespostaComando( Bematech_FI_IniciaFechamentoCupom( AcrescimoDesconto->c_str( ), TipoAcrescimoDesconto->c_str( ), ValorAcrescimoDesconto->c_str( ) ), Erro ) );
  }
  __finally {
    delete AcrescimoDesconto;
    delete ValorAcrescimoDesconto;
    delete TipoAcrescimoDesconto;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::Pagamento( String *ModoPagamento, String *VPgto, String *Erro ) {

  // formatando o modo de pagamento
  // "Dinheiro" "Cheque" "Cartao Debito" "Cartao Credito" "Financiado" "Dep. Bancario"

  // formatando o valor do pagamento
  *VPgto = StringReplace( *VPgto, ".", "", TReplaceFlags( ) << rfReplaceAll );

//return( this->ObterRespostaComando( Bematech_FI_EfetuaFormaPagamentoIndice( IndicePagamento->c_str( ), LeftStr( *VPgto, 14 ).c_str( ) ), Erro ) );
  return( this->ObterRespostaComando( Bematech_FI_EfetuaFormaPagamento( LeftStr( *ModoPagamento, 14 ).c_str( ), LeftStr( *VPgto, 14 ).c_str( ) ), Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::FecharCupomFiscal( String *Vendedor, String *Erro ) {

  TStringList *MensagemPromocional;

  try {
    MensagemPromocional = new TStringList( );

    MensagemPromocional->Sorted = false;
    MensagemPromocional->Add( "Vendedor: " + *Vendedor );
    while( MensagemPromocional->Strings[0].Length( ) <= 48 ) {
      MensagemPromocional->Strings[0] = MensagemPromocional->Strings[0] + " ";
    }
    MensagemPromocional->Add( "                                                " );
    MensagemPromocional->Add( "    Visite Nosso Salao de Exposicao Consigo!    " );
    MensagemPromocional->Add( "     CONSIGO - A CERTEZA DE UM BOM NEGOCIO      " );
    MensagemPromocional->Add( "     TEL: (11)3214-2660  FAX: (11)3214-5896     " );
    return( this->ObterRespostaComando( Bematech_FI_TerminaFechamentoCupom ( MensagemPromocional->Text.c_str( ) ), Erro ) );
  }
  __finally {
    delete MensagemPromocional;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::CancelarCupomFiscal( String *Erro ) {

  return( this->ObterRespostaComando( Bematech_FI_CancelaCupom( ), Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::LeituraX( String *Erro ) {

  return( this->ObterRespostaComando( Bematech_FI_LeituraX( ), Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::ReducaoZ( String *Erro ) {

  AnsiString *Data, *Hora;

  try {
    Data = new AnsiString( "" );
    Hora = new AnsiString( "" );

    return( this->ObterRespostaComando( Bematech_FI_ReducaoZ( Data->c_str( ), Hora->c_str( ) ), Erro ) );
  }
  __finally {
    delete Data;
    delete Hora;
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::AbrirCupomNaoFiscalVinculado( String *FormaPagamento, String *Valor, String *NumeroCupom, String *Erro ) {

  *Valor = StringReplace( *Valor, ".", "", TReplaceFlags( ) << rfReplaceAll );

  return( this->ObterRespostaComando( Bematech_FI_AbreComprovanteNaoFiscalVinculado( LeftStr( *FormaPagamento, 16 ).c_str( ), LeftStr( *Valor, 14 ).c_str( ), LeftStr( *NumeroCupom, 6 ).c_str( ) ), Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::ImprimirLinhaNaoFiscal( String *Texto, String *Erro ) {

  *Texto = LeftStr( *Texto, 48 );
  if( Texto->Length( ) < 48 ) {
    while( Texto->Length( ) < 48 ) {
      *Texto = *Texto + " ";
    }
  }
  return( this->ObterRespostaComando( Bematech_FI_UsaComprovanteNaoFiscalVinculado( Texto->c_str( ) ), Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::FecharCupomNaoFiscal( String *Erro ) {

  return( this->ObterRespostaComando( Bematech_FI_FechaComprovanteNaoFiscalVinculado( ), Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::ObterNumeroUltimoCupomFiscal( int &UltimoCupom, String *Erro ) {

  char NumeroCupom[7];
  bool retorno;

  try {
    memset( NumeroCupom, '\0', 7 );
    retorno = this->ObterRespostaComando( Bematech_FI_NumeroCupom( NumeroCupom ), Erro );
    if( Erro->IsEmpty( ) ) {
      UltimoCupom = (String(NumeroCupom)).ToInt( );
      UltimoCupom++;
    }
    else {
      UltimoCupom = 0;
    }

    return( retorno );
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::GerarArquivoRfd( String *ArquivoMfd, String *Data, String *Erro ) {

//  return( this->ObterRespostaComando( Bematech_FI_GeraRegistrosCAT52MFD( ArquivoMfd->c_str( ), Data->c_str( ) ), Erro ) );
}
//---------------------------------------------------------------------------
bool TImpressoraFiscalBematech::ObterRespostaComando( int CodigoRetornoComando, String *Erro ) {

    //int  RetornoStatus = 0;   // retorno da função que le o status da impressora
    //char StringStatus[12];    // status da impressora em string (ACK, ST1, ST2)
    //char StringRetorno[450];  // descrição por extenso dos status da impressora + StatusString (450 posicoes)
    //char *StringRetorno;      // descrição por extenso dos status da impressora + StatusString (450 posicoes)
    //int Tamanho = 0;          // qtde de bytes que devem ser alocados para a variável StringRetorno

    int  ACK = 0, ST1 = 0, ST2 = 0, CodigoRetorno;   // variáveis de status da impressora
    //String *CodigoRetorno;

    //ACK = 0; ST1 = 0; ST2 = 0;
    //memset( StringRetorno, 0, 450 );
    //memset( StringStatus,  0,  12 );
    //Tamanho = strlen( Mensagem ) + strlen( Informacao ) + 450 + 5; // tamanho da var. Mensagem + tam. da var. Informacao + 450 (descrição por extenso dos status da impressora + StatusString) + 5 ( LF + nulo )
    // tenta alocar memória pra variável StringRetorno, se der erro retorna
    //if ( ( StringRetorno = new char[ Tamanho ] ) == NULL )
        //return;
    //memset( StringRetorno, '\0', Tamanho );

  try{
    //CodigoRetorno = new AnsiString( );

    switch( char(CodigoRetornoComando) ) {
      case 0:      // erro de comunicação
        *Erro = "Erro de comunicação com a impressora";
        return false;
      case -1:      // erro de execução
        *Erro = "Erro de execução da função";
        return false;
      case -2:      // parâmetro inválido
        *Erro = "Parâmetro inválido na função";
        return false;
      case -3:      // alíquota não programada
        *Erro = "Alíquota não programada";
        return false;
      case -4:      // Arquivo de inicialização BemaFI32.ini não foi encontrado
        *Erro = "O arquivo de inicialização BemaFI32.ini não foi encontrado";
        return false;
      case -5:      // erro na abertura da porta serial
        *Erro = "Erro ao tentar abrir a porta de comunicação";
        return false;
      case -6:      // impressora desligada ou cabo desconectado
        *Erro = "impressora desligada ou cabo de comunicação desconectado";
        return false;
      case -7:      // banco não encontrado no arquivo 'BemaFI32.ini'
        *Erro = "banco não encontrado no arquivo 'BemaFI32.ini'";
        return false;
      case -8:      // erro ao criar ou gravar no arquivo 'Status.txt'ou 'Retorno.txt'
        *Erro = "Erro ao criar ou gravar no arquivo 'Status.txt'ou 'Retorno.txt'";
        return false;
      case 1:       // le o status da impressora
        CodigoRetorno = Bematech_FI_RetornoImpressora( &ACK, &ST1, &ST2 );
        if( ACK == 21 ) {
          *Erro = "Status da impressora: 21 \n Comando não executado";
          return false;
        }
        if( ST1 != 0 || ST2 != 0 ) {
          //sprintf( StringRetorno, "%s%d,%d,%d\n", "Status da Impressora: ", ACK, ST1, ST2 );
          if( ST1 >= 128 ) {
            *Erro = "Fim de Papel\n";
            ST1 -= 128;
            return false;
          }
          /*
          if( ST1 == 64 ) {
            strcat( StringRetorno, "Pouco Papel\n" );
            ST1 -= 64;
          }
          */
          if( ST1 == 32 ) {
            *Erro = "Erro no relógio\n";
            ST1 -= 32;
            return false;
          }
          if( ST1 == 16 ) {
            *Erro = "Impressora em erro\n";
            ST1 -= 16;
            return false;
          }
          if( ST1 == 8 ) {
            *Erro = "Primeiro dado do comando não foi Esc\n";
            ST1 -= 8;
            return false;
          }
          if( ST1 == 4 ) {
            *Erro = "Comando inexistente\n";
            ST1 -= 4;
            return false;
          }
          if( ST1 == 2 ) {
            *Erro = "Cupom fiscal aberto\n";
            ST1 -= - 2;
            return false;
          }
          if( ST1 == 1 ) {
            *Erro = "Número de parâmetros inválido no comando\n";
            ST1 -= - 1;
            return false;
          }
          if( ST2 >= 128 ) {
            *Erro = "Tipo de Parâmetro de comando inválido\n";
            ST2 -= 128;
            return false;
          }
          if( ST2 >= 64 ) {
            *Erro = "Memória fiscal lotada\n";
            ST2 -= 64;
            return false;
          }
          if( ST2 >= 32 ) {
            *Erro = "Erro na CMOS\n";
            ST2 -= 32;
            return false;
          }
          if( ST2 >= 16 ) {
            *Erro = "Alíquota não programada\n";
            ST2 -= 16;
            return false;
          }
          if( ST2 >= 8 ) {
            *Erro = "Capacidade de alíquota programáveis lotada\n";
            ST2 -= 8;
            return false;
          }
          if( ST2 >= 4 ) {
            *Erro = "Cancelamento não permitido\n";
            ST2 -= 4;
            return false;
          }
          if( ST2 >= 2 ) {
            *Erro = "CGC/IE do proprietário não programados\n";
            ST2 -= 2;
            return false;
          }
          if( ST2 >= 1 ) {
            *Erro = "Comando não executado\n";
            ST2 -= 1;
            return false;
          }

        }
        return true;
        /*
         //fim do ST1 <> 0 and ST2 <> 0
            // se houver informação pra ser mostrada, concatena com o status
            if ( strlen( Mensagem ) > 0 || strlen( Informacao ) > 0 )
                sprintf( StringRetorno + strlen( StringRetorno ), "\n%s%s", Mensagem, Informacao );

            // se houver alguma informação mostra em tela
            if ( strlen( StringRetorno ) > 0 )
                Application->MessageBox(StringRetorno, TituloJanela, MB_OK);

            break;
        */
    } // end switch
  }
  __finally {
    //delete CodigoRetorno;
  }
}
//---------------------------------------------------------------------------
