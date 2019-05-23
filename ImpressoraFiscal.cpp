//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <vcl\Dialogs.hpp>
#include <systdate.h>
#include <vcl\Forms.hpp>
#include "Main.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ImpressoraFiscal.h"
//---------------------------------------------------------------------------

HINSTANCE iHandleDll;

void TImpressoraFiscal::CarregaDll( String* &Retorno ) {

  Boolean Ok;

  iHandleDll = LoadLibrary( "ECF3E32.DLL" );
  if( iHandleDll != 0 ) {
    PCAbre                   = ( OPENCIF ) GetProcAddress( iHandleDll , "OPENCIF" );
    PCFecha                  = ( CLOSECIF ) GetProcAddress( iHandleDll , "CLOSECIF" );
    PCAbreCupom              = ( ABRECUPOMFISCAL ) GetProcAddress( iHandleDll , "ABRECUPOMFISCAL" );
    PCLancaItem              = ( VENDAITEM ) GetProcAddress( iHandleDll , "VENDAITEM" );
    PCCancItem               = ( CANCELAMENTOITEM )GetProcAddress( iHandleDll , "CANCELAMENTOITEM" );
    PCTotalCupom             = ( TOTALIZARCUPOM ) GetProcAddress( iHandleDll , "TOTALIZARCUPOM" );
    PCPagamento              = ( PAGAMENTO ) GetProcAddress( iHandleDll , "PAGAMENTO" );
    PCFechaCupom             = ( FECHACUPOMFISCAL ) GetProcAddress( iHandleDll , "FECHACUPOMFISCAL" );
    PCCancelaCupom           = ( CANCELACUPOMFISCAL ) GetProcAddress( iHandleDll , "CANCELACUPOMFISCAL" );
    PCLeituraX               = ( LEITURAX ) GetProcAddress( iHandleDll , "LEITURAX" );
    PCReducaoZ               = ( REDUCAOZ ) GetProcAddress( iHandleDll , "REDUCAOZ" );
    PCLerData                = ( LEMEMFISCALDATA ) GetProcAddress( iHandleDll , "LEMEMFISCALDATA" );
    PCLerReducao             = ( LEMEMFISCALREDUCAO ) GetProcAddress( iHandleDll , "LEMEMFISCALREDUCAO" );
    PCAbreNaoFiscal          = ( ABRECUPOMNAOVINCULADO ) GetProcAddress( iHandleDll , "ABRECUPOMNAOVINCULADO" );
    PCAbreNaoFiscalVinculado = ( ABRECUPOMVINCULADO ) GetProcAddress( iHandleDll , "ABRECUPOMVINCULADO" );
    PCEncerraNaoFiscal       = ( ENCERRARCUPOM ) GetProcAddress( iHandleDll , "ENCERRARCUPOM" );
    PCImprimeNaoFiscal       = ( IMPRIMELINHANAOFISCAL ) GetProcAddress( iHandleDll , "IMPRIMELINHANAOFISCAL" );
    PCTransStatus            = ( TRANSSTATUS ) GetProcAddress( iHandleDll , "TRANSSTATUS" );
    PCObtemRetorno           = ( OBTEMRETORNO ) GetProcAddress( iHandleDll , "OBTEMRETORNO" );
    PCEcfParEsp              = ( ECFPARESP ) GetProcAddress( iHandleDll , "ECFPARESP" );
    PCAvancaLinha            = ( AVANCALINHA ) GetProcAddress( iHandleDll, "AVANCALINHA" );
    PCProgLegenda            = ( PROGRAMALEGENDA ) GetProcAddress( iHandleDll, "PROGRAMALEGENDA" );
    if( ( PCAbre             == NULL ) ||
        ( PCFecha            == NULL ) ||
        ( PCAbreCupom        == NULL ) ||
        ( PCLancaItem        == NULL ) ||
        ( PCCancItem         == NULL ) ||
        ( PCTotalCupom       == NULL ) ||
        ( PCPagamento        == NULL ) ||
        ( PCFechaCupom       == NULL ) ||
        ( PCCancelaCupom     == NULL ) ||
        ( PCLeituraX         == NULL ) ||
        ( PCReducaoZ         == NULL ) ||
        ( PCLerData          == NULL ) ||
        ( PCLerReducao       == NULL ) ||
        ( PCAbreNaoFiscal    == NULL ) ||
        ( PCEncerraNaoFiscal == NULL ) ||
        ( PCImprimeNaoFiscal == NULL ) ||
        ( PCTransStatus      == NULL ) ||
        ( PCObtemRetorno     == NULL ) ||
        ( PCEcfParEsp        == NULL ) ||
        ( PCAvancaLinha      == NULL ) ||
        ( PCAbreNaoFiscalVinculado == NULL ) ) {
      FreeLibrary( iHandleDll );
      *Retorno = "Erro ao carregar as funções da biblioteca ECF3E32.DLL.\r\rFavor verificar!";
    }
    else {
      LeProComp( PCAbre( ), false, Retorno );
      if( *Retorno != "" ) {
      	//FreeLibrary( iHandleDll );
       	*Retorno = "Erro de comunicação com a impressora fiscal.\r\rFavor verificar!";
      }
    }
  }
  else {
    *Retorno = "Erro ao carregar a biblioteca ECF3E32.DLL.\r\rFavor verificar!";
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::FechaSerial( ) {

  PCFecha( );
  if( iHandleDll != 0 ) {
	  FreeLibrary( iHandleDll );
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::AbreCupom( String* &Retorno ) {

  int iRetorno;

  iRetorno = PCAbreCupom( );
  Sleep( 1500 );
  LeProComp( iRetorno, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::AbreCupomNaoFiscal( String* &Retorno ) {

  int iRetorno;

  iRetorno = PCAbreNaoFiscal( );
  Sleep( 1600 );
  LeProComp( iRetorno, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::AbreCupomNaoFiscalVinculado( String* &Retorno ) {
  int iRetorno;

  iRetorno = PCAbreNaoFiscalVinculado( );
  Sleep( 1600 );
  LeProComp( iRetorno, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::FechaCupom( String* Vendedor, String* &Retorno ) {

  String *TamMensagem, *Mensagem;
  int iRetorno;

  try {
    TamMensagem = new AnsiString( );
    Mensagem = new AnsiString( );

    *Mensagem = "Vendedor: " + *Vendedor;
    while( Mensagem->Length( ) <= 48 ) {
      *Mensagem = *Mensagem + " ";
    }
    *Mensagem = *Mensagem + "                                                ";
    *Mensagem = *Mensagem + "       Concorra a um Colete Profissional!       ";
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

    iRetorno = PCFechaCupom( TamMensagem->c_str( ), Mensagem->c_str( ) );
    Sleep( 4200 );
    LeProComp( iRetorno, true, Retorno );
  }
  __finally {
    delete TamMensagem;
    delete Mensagem;
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::FechaCupomNaoFiscal( String* &Retorno ) {

  int iRetorno;

  iRetorno = PCEncerraNaoFiscal( );
  Sleep( 1500 );
  LeProComp( iRetorno, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LancaItem( String* sQtde, String* sPrecoUnit, String* sCodigo,
                                   String* sDescricao, String* &Retorno ) {
/*
  String sFormato, sQtde, sPrecoUnit, sCodFiscal, sTipoDesc, sVlrDesc, sUnidade,
         sCodigo, sTamDescr, sDescricao, sLegendaOp;

  sFormato   := '0';
  sQtde      := '001000';
  sPrecoUnit := '00000000100';
  sCodFiscal := 'T01';
  sTipoDesc  := '&';
  sVlrDesc   := '000000000000000';
  sUnidade   := 'PC';
  sCodigo    := '0017600010101';
  sTamDescr  := '0';
  sDescricao := 'CAMISA DE MANGA LONG';
  sLegendaOp := '              ';
*/
	int Retorno_;
  String *sFormato;
  String *sCodFiscal;
  String *sTipoDesc;
  String *sVlrDesc;
  String *sUnidade;
  String *sTamDescr;
  String *sLegendaOp;

  try {
    sFormato = new AnsiString( "0" );
    // icms 2,15% - simples paulista
    // sCodFiscal = new AnsiString( "T01" );

    // isencao tributaria - simples nacional
    sCodFiscal = new AnsiString( "I00" );

    sTipoDesc = new AnsiString( "&" );
    sVlrDesc = new AnsiString( "000000000000000" );
    sUnidade = new AnsiString( "PC" );
    sTamDescr = new AnsiString( "3" );
    sLegendaOp = new AnsiString( "              " );

    *sQtde = *sQtde + "000";
    while( sQtde->Length( ) < 6 ) {
      *sQtde = "0" + *sQtde;
    }
    *sPrecoUnit = StringReplace( *sPrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll );
    *sPrecoUnit = StringReplace( *sPrecoUnit, ",", "", TReplaceFlags( ) << rfReplaceAll );
    while( sPrecoUnit->Length( ) < 11 ) {
      *sPrecoUnit = "0" + *sPrecoUnit;
    }
    if( sCodigo->Length( ) > 13 ) {
      *sCodigo = sCodigo->Delete( 14, sCodigo->Length( ) - 13 );
    }
    else while( sCodigo->Length( ) < 13 ) {
      *sCodigo = *sCodigo + " ";
    }
    if( sDescricao->Length( ) < 114 ) {
      while( sDescricao->Length( ) < 114 ) {
        *sDescricao = *sDescricao + " ";
      }
    }
    else if( sDescricao->Length( ) > 114 ) {
     	*sDescricao = sDescricao->Delete( 115, sDescricao->Length( ) - 114 );
    }

    Retorno_ = PCLancaItem( sFormato->c_str( ) , sQtde->c_str( ), sPrecoUnit->c_str( ),
                           sCodFiscal->c_str( ), sTipoDesc->c_str( ), sVlrDesc->c_str( ),
                           sUnidade->c_str( ), sCodigo->c_str( ), sTamDescr->c_str( ),
                           sDescricao->c_str( ), sLegendaOp->c_str( ) );
    Sleep( 900 );
    LeProComp( Retorno_, true, Retorno );
  }
  __finally {
    delete sFormato;
    delete sCodFiscal;
    delete sTipoDesc;
    delete sVlrDesc;
    delete sUnidade;
    delete sTamDescr;
    delete sLegendaOp;
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LancaItemNaoFiscal( String* pAtrib, String* pString, String* &Retorno ) {

	int Retorno_;

  if( pString->Length( ) < 48 ) {
    while( pString->Length( ) < 48 ) {
      *pString = *pString + " ";
    }
  }
  Retorno_ = PCImprimeNaoFiscal( pAtrib->c_str( ), pString->c_str( ) );
  Sleep( 600 );
  LeProComp( Retorno_, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::TotalizaCupom( String* &Retorno ) {

  String *Oper, *TipoDesc, *ValorVenda, *LegOper;
  int Retorno_;

  try {
    Oper = new AnsiString( "" );
    ValorVenda = new AnsiString( "000000000000000" );
    LegOper = new AnsiString( "              " );
    TipoDesc = new AnsiString( "&" );

    Retorno_ = PCTotalCupom( Oper->c_str( ), TipoDesc->c_str( ), ValorVenda->c_str( ), LegOper->c_str( ) );
	  Sleep( 1200 );
    LeProComp( Retorno_, true, Retorno );
  }
  __finally {
    delete Oper;
    delete TipoDesc;
    delete ValorVenda;
    delete LegOper;
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::Pagamento( String* Reg, String* VPgto, String* Subtr, String* &Retorno ) {

	int Retorno_;

  *VPgto = StringReplace( *VPgto, ".", "", TReplaceFlags( ) << rfReplaceAll );
  *VPgto = StringReplace( *VPgto, ",", "", TReplaceFlags( ) << rfReplaceAll );
  while( VPgto->Length( ) < 15 ) {
    *VPgto = "0" + *VPgto;
  }
  Retorno_ = PCPagamento( Reg->c_str( ), VPgto->c_str( ), Subtr->c_str( ) );
  Sleep( 1300 );
  LeProComp( Retorno_, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::CancelaCupom( String* &Retorno ) {

  int iRetorno;

  iRetorno = PCCancelaCupom( );
  Sleep( 7000 );
  LeProComp( iRetorno, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LeituraX( String* Relatorio, String* &Retorno ) {

	int Retorno_;
  Retorno_ = PCLeituraX( Relatorio->c_str( ) );
  Sleep( 23000 );
  LeProComp( Retorno_, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::ReducaoZ( String* &Retorno ) {

	int Retorno_;
  // Não haverá Relatório Gerencial!
  Retorno_ = PCReducaoZ( "0" );
  Sleep( 23000 );
  LeProComp( Retorno_, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LeituraMemoriaFiscal( String* DataInic, String* DataFinal, String* &Retorno ) {

 	int Retorno_;

	if( StrToDate( *DataInic ) >= StrToDate( *DataFinal ) ) {
   	*Retorno = "A Data Inicial Não Pode Ser Maior ou Igual à Data Final para a Leitura da Memória Fiscal!";
  }
  else {
  	*DataInic = StringReplace( *DataInic, "/", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase );
    *DataFinal = StringReplace( *DataFinal, "/", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase );
	  // A Leitura será Completa!!!
    Retorno_ = PCLerData( DataInic->c_str( ), DataFinal->c_str( ), "0" );
    Sleep( 25000 );
  	LeProComp( Retorno_, true, Retorno );
	}
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LeituraReducaoFiscal( String* RedInic, String* RedFin, String* &Retorno ) {

  int Retorno_;

  if( RedInic->ToInt( ) >= RedFin->ToInt( ) ) {
   	*Retorno = "A Redução Inicial Não pode ser maior ou igual que a Redução Final!";
  }
  else {
  	while( RedInic->Length( ) < 4 ) {
    	*RedInic = "0" + *RedInic;
    }
  	while( RedFin->Length( ) < 4 ) {
    	*RedFin = "0" + *RedFin;
    }
	  // A Leitura será Completa!!!
    Retorno_ = PCLerReducao( RedInic->c_str( ), RedFin->c_str( ), "0" );
    Sleep( 25000 );
  	LeProComp( Retorno_, true, Retorno );
	}
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::UltimoCupomFiscal( int &Cupom, String* &Retorno ) {

  int Retorno_, i;
  char BufRetorno[2048];
  String *Numero;

  try {
    Numero = new AnsiString( );

    Retorno_ = PCEcfParEsp( "41" );
    if( Retorno_ != 0 ) {
  	  MensagemProComp( Retorno_, Retorno );
    }
    else {
      //Sleep( 1000 );
      //Retorno_ = PCObtemRetorno( BufRetorno );
      for( i = 0; i < 3; i++ ) {
        Retorno_ = PCObtemRetorno( BufRetorno );
        if( Retorno_ == 0 ) {
          break;
        }
        Sleep( 1000 );
      }
      if( Retorno_ != 0 ) {
    	  MensagemProComp( Retorno_, Retorno );
      }
      else {
        *Numero = BufRetorno;
        /*
        for( i = Numero->Length( ); i >= Numero->Length( ) - 4; i-- ) {
  	      NumeroCupom->Insert( Numero[i], 1 );
        }
        */
        *Numero = Numero->SubString( 6, 6 );
        Cupom = Numero->ToInt( );
        Cupom++;
        *Retorno = "";
      }
    }
  }
  __finally {
    delete Numero;
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::ProgramarLegenda( String* &Retorno ) {

  LeProComp( PCProgLegenda( "00", "Dinheiro        " ), true, Retorno );
  if( *Retorno == "0" ) {
    LeProComp( PCProgLegenda( "01", "Cheque          " ), true, Retorno );
    if( *Retorno == "0" ) {
      LeProComp( PCProgLegenda( "02", "Cartao Debito   " ), true, Retorno );
      if( *Retorno == "0" ) {
        LeProComp( PCProgLegenda( "02", "Cartao Debito   " ), true, Retorno );
        if( *Retorno == "0" ) {
          LeProComp( PCProgLegenda( "03", "Cartao Credito  " ), true, Retorno );
          if( *Retorno == "0" ) {
            LeProComp( PCProgLegenda( "04", "Financiado      " ), true, Retorno );
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::PulaLinha( String* &Retorno ) {
  int iRetorno;

  iRetorno = PCAvancaLinha( );
  Sleep( 800 );
  LeProComp( iRetorno, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::ObterStatus( String* &Retorno ) {

	char BufStat[40];

  //LeProComp( PCTransStatus( 0, BufStat ), false );
  if( PCTransStatus( 1, BufStat ) ) {
		*Retorno = "Cupom Fiscal Aberto!!!";
  }
  else if( PCTransStatus( 2, BufStat ) ) {
		*Retorno = "Cupom Não Fiscal Aberto!!!";
  }
  else if( PCTransStatus( 4, BufStat ) ) {
		*Retorno = "Em intervenção Fiscal!!!";
  }
  else if( PCTransStatus( 5, BufStat ) ) {
		*Retorno = "Em Impressão Fiscal!!!";
  }
  else if( PCTransStatus( 6, BufStat ) ) {
		*Retorno = "Redução Z Pendente!!!";
  }
  else if( PCTransStatus( 9, BufStat ) ) {
		*Retorno = "Em Início de Cupom de Venda!!!";
  }
  else if( PCTransStatus( 10, BufStat ) ) {
		*Retorno = "Em venda de Item!!!";
  }
  else if( PCTransStatus( 11, BufStat ) ) {
		*Retorno = "Em Cancelamento de Item!!!";
  }
  else if( PCTransStatus( 12, BufStat ) ) {
		*Retorno = "Em Cancelamento de Cupom!!!";
  }
  else if( PCTransStatus( 13, BufStat ) ) {
		*Retorno = "Em Fechamento de Cupom!!!";
  }
  else if( PCTransStatus( 14, BufStat ) ) {
		*Retorno = "Em Redução Z!!!";
  }
  else if( PCTransStatus( 15, BufStat ) ) {
		*Retorno = "Em Leitura X!!!";
  }
  else if( PCTransStatus( 16, BufStat ) ) {
		*Retorno = "Em Leitura da Memória Fiscal!!!";
  }
  else if( PCTransStatus( 17, BufStat ) ) {
  	*Retorno = "A Tampa da Impressora Fiscal está Aberta!!!";
  }
  else if( PCTransStatus( 19, BufStat ) ) {
		*Retorno = "Buffer Cheio!!!";
  }
  else if( PCTransStatus( 20, BufStat ) ) {
    *Retorno = "Erro Irrecuperável!!!";
  }
  else if( PCTransStatus( 21, BufStat ) ) {
    *Retorno = "Erro Mecânico!!!";
  }
  else if( PCTransStatus( 22, BufStat ) ) {
    *Retorno = "Temperatura da Cabeça de Impressão Alta!!!\r\r Espere Alguns Minutos.";
  }
  else if( PCTransStatus( 23, BufStat ) ) {
    *Retorno = "O Papel da Impressora Fiscal está Acabando!!!";
  }
  else if( PCTransStatus( 24, BufStat ) ) {
		*Retorno = "Comando em Execução!!!";
  }
  else if( PCTransStatus( 26, BufStat ) ) {
		*Retorno = "Esperando Inserção de Cheque!!!";
  }
  else if( PCTransStatus( 27, BufStat ) ) {
		*Retorno = "Cheque Detectado!!!";
  }
  else if( PCTransStatus( 28, BufStat ) ) {
  	*Retorno = "Não há Papel na Impressora Fiscal!!!";
  }
  else if( PCTransStatus( 30, BufStat ) ) {
		*Retorno = "Esperando Inserção do Documento para Validação!!!";
  }
  else if( PCTransStatus( 31, BufStat ) ) {
		*Retorno = "Documento para Validação Detectado!!!";
  }
  else if( PCTransStatus( 32, BufStat ) ) {
    *Retorno = "Leitura X Pendente!!!";
  }
  else if( PCTransStatus( 33, BufStat ) ) {
		*Retorno = "Em Totalização!!!";
  }
  else if( PCTransStatus( 34, BufStat ) ) {
		*Retorno = "Em Pagamento!!!";
  }
}
//---------------------------------------------------------------------------
bool TImpressoraFiscal::ObterStatusBit( int Bit ) {

	char BufStat[40];

  PCTransStatus( 0, BufStat );
  Bit--;
  if( BufStat[Bit] == '1' ) {
    return( true );
  }
  else {
    return( false );
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LeProComp( int iRetorno, Boolean lProcessaRet, String* &Retorno ) {

  char BufRetorno[2048];
  int i;

  *Retorno = "";
  if( iRetorno != 0 ) {
    MensagemProComp( iRetorno, Retorno );
  }
  if( lProcessaRet ) {
    for( i = 0; i < 3; i++ ) {
      iRetorno = PCObtemRetorno( BufRetorno );
      if( iRetorno == 0 ) {
        break;
      }
      else if( ( iRetorno > 0 ) || ( iRetorno != -26 ) ) {
        MensagemProComp( iRetorno, Retorno );
      }
      Sleep( 1000 );
    }
    // Ultrapassou o time-out de retorno da impressora
    if( iRetorno == -26 ) {
    	*Retorno = "Erro de comunicação com a impressora fiscal ProComp!";
    }
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::MensagemProComp( int iRetorno, String* &Retorno ) {

  if( iRetorno == -1 ) {
    *Retorno = "Erro genérico na execução da função. Perda de comunicação com a impressora.";
  }
  else if( iRetorno == -3 ) {
    *Retorno = "Leitura assíncrona em andamento. Comando sendo executado.";
  }
  else if( iRetorno == -4 ) {
    *Retorno = "TimeOut na execução do comando.";
  }
  else if( iRetorno == -5 ) {
    *Retorno = "Tamanho da mensagem enviada pela impressora é maior que o buffer de recepção fornecido pela aplicação.";
  }
  else if( iRetorno == -7 ) {
    *Retorno = "Erro no arquivo de configuração CIF.INI.";
  }
  else if( iRetorno == -8 ) {
    *Retorno = "Falha na abertura da serial.";
  }
  else if( iRetorno == -11 ) {
    *Retorno = "Tampa aberta.";
  }
  else if( iRetorno == -12 ) {
    *Retorno = "Erro mecânico.";
  }
  else if( iRetorno == -13 ) {
    *Retorno = "Erro irrecuperavel.";
  }
  else if( iRetorno == -14 ) {
    *Retorno = "Temperatura da cabeça de impressão está alta.";
  }
  else if( iRetorno == -15 ) {
    *Retorno = "Pouco papel.";
  }
  else if( iRetorno == -16 ) {
    *Retorno = "Em inicio de cupom de venda.";
  }
  else if( iRetorno == -17 ) {
    *Retorno = "Em venda de item.";
  }
  else if( iRetorno == -18 ) {
    *Retorno = "Em cancelamento de item.";
  }
  else if( iRetorno == -19 ) {
    *Retorno = "Em cancelamento de cupom.";
  }
  else if( iRetorno == -20 ) {
    *Retorno = "Em fechamento de cupom.";
  }
  else if( iRetorno == -21 ) {
    *Retorno = "Em Reducao Z.";
  }
  else if( iRetorno == -22 ) {
    *Retorno = "Em Leitura X.";
  }
  else if( iRetorno == -23 ) {
    *Retorno = "Em leitura de memória fiscal.";
  }
  else if( iRetorno == -24 ) {
    *Retorno = "Em totalização.";
  }
  else if( iRetorno == -25 ) {
    *Retorno = "Em pagamento.";
  }
  else if( iRetorno == -26 ) {
    *Retorno = "Ainda não obteve retorno.";
  }
  else if( iRetorno == 1 ) {
    *Retorno = "O cabeçalho contém caracteres inválidos.";
  }
  else if( iRetorno == 2 ) {
    *Retorno = "Comando inexistente.";
  }
  else if( iRetorno == 3 ) {
    *Retorno = "Valor não numérico em campo numérico.";
  }
  else if( iRetorno == 4 ) {
    *Retorno = "Valor fora da faixa entre 20h e 7Fh.";
  }
  else if( iRetorno == 5 ) {
    *Retorno = "Campo de iniciar com @, & ou %.";
  }
  else if( iRetorno == 6 ) {
    *Retorno = "Campo de iniciar com $, # ou ?.";
  }
  else if( iRetorno == 7 ) {
    *Retorno = "O intervalo é inconsistente. O primeiro deve ser menor que o segundo.";
  }
  else if( iRetorno == 8 ) {
    *Retorno = "Tributo inválido.";
  }
  else if( iRetorno == 9 ) {
    *Retorno = "A string TOTAL não é aceita.";
  }
  else if( iRetorno == 10 ) {
    *Retorno = "A sintaxe do comando está errada.";
  }
  else if( iRetorno == 11 ) {
    *Retorno = "Excedeu o número máximo de linhas permitidas pelo comando.";
  }
  else if( iRetorno == 12 ) {
    *Retorno = "O terminador enviado não obedece o protocolo de comunicação.";
  }
  else if( iRetorno == 13 ) {
    *Retorno = "O checksum enviado está incorreto.";
  }
  else if( iRetorno == 15 ) {
    *Retorno = "A situação tributária deve iniciar com T, F ou N.";
  }
  else if( iRetorno == 16 ) {
    *Retorno = "Data inválida.";
  }
  else if( iRetorno == 17 ) {
    *Retorno = "Hora inválida.";
  }
  else if( iRetorno == 18 ) {
    *Retorno = "Aliquota não programada ou fora do intervalo.";
  }
  else if( iRetorno == 19 ) {
    *Retorno = "O campo de sinal está incorreto.";
  }
  else if( iRetorno == 20 ) {
    *Retorno = "Comando só aceito em intervenção fiscal.";
  }
  else if( iRetorno == 21 ) {
    *Retorno = "Comando só aceito em modo normal.";
  }
  else if( iRetorno == 22 ) {
    *Retorno = "Necessário abrir cupom fiscal.";
  }
  else if( iRetorno == 23 ) {
    *Retorno = "Comando não aceito durante cupom fiscal.";
  }
  else if( iRetorno == 24 ) {
    *Retorno = "Necessário abrir cupom não fiscal.";
  }
  else if( iRetorno == 25 ) {
    *Retorno = "Comando não aceito durante cupom não fiscal.";
  }
  else if( iRetorno == 26 ) {
    *Retorno = "O relógio está em horário de verão.";
  }
  else if( iRetorno == 27 ) {
    *Retorno = "O relógio não está em horário de verão.";
  }
  else if( iRetorno == 28 ) {
    *Retorno = "Necessário realizar redução Z.";
  }
  else if( iRetorno == 29 ) {
    *Retorno = "Fechamento do dia (Redução Z) já executado.";
  }
  else if( iRetorno == 30 ) {
    *Retorno = "Necessário programar legenda.";
  }
  else if( iRetorno == 31 ) {
    *Retorno = "Item inexistente ou já cancelado.";
  }
  else if( iRetorno == 32 ) {
    *Retorno = "O cupom anterior não pode ser cancelado.";
  }
  else if( iRetorno == 33 ) {
    *Retorno = "Detectado falta de papel.";
  }
  else if( iRetorno == 36 ) {
    *Retorno = "Necessário programar os dados do estabelecimento.";
  }
  else if( iRetorno == 37 ) {
    *Retorno = "Necessário realizar intervenção técnica.";
  }
  else if( iRetorno == 38 ) {
    *Retorno = "A memória fiscal não permite mais realizar vendas.";
  }
  else if( iRetorno == 39 ) {
    *Retorno = "Ocorreu algum problema na memória fiscal.";
  }
  else if( iRetorno == 40 ) {
    *Retorno = "Necessário programar a data do relógio.";
  }
  else if( iRetorno == 41 ) {
    *Retorno = "Número máximo de ítens por cupom ultrapassado.";
  }
  else if( iRetorno == 42 ) {
    *Retorno = "Já foi realizado o ajuste de hora diário.";
  }
  else if( iRetorno == 43 ) {
    *Retorno = "Comando válido ainda em execução.";
  }
  else if( iRetorno == 44 ) {
    *Retorno = "Está em estado de impressão de cheque.";
  }
  else if( iRetorno == 45 ) {
    *Retorno = "Não está em estado de impressão de cheque.";
  }
  else if( iRetorno == 46 ) {
    *Retorno = "Necessário inserir o cheque.";
  }
  else if( iRetorno == 47 ) {
    *Retorno = "Necessário inserir nova bobina.";
  }
  else if( iRetorno == 48 ) {
    *Retorno = "Necessário executar leitura X.";
  }
  else if( iRetorno == 49 ) {
    *Retorno = "Detectado algum problema na impressora.";
  }
  else if( iRetorno == 50 ) {
    *Retorno = "Cupom já foi totalizado.";
  }
  else if( iRetorno == 51 ) {
    *Retorno = "Necessário totalizar cupom antes de fechar.";
  }
  else if( iRetorno == 52 ) {
    *Retorno = "Necessário finalizar cupom com comando correto.";
  }
  else if( iRetorno == 53 ) {
    *Retorno = "Ocorreu erro de gravação na memória fiscal.";
  }
  else if( iRetorno == 54 ) {
    *Retorno = "Excedeu número máximo de estabelecimentos.";
  }
  else if( iRetorno == 55 ) {
    *Retorno = "Memória fiscal não inicializada completamente.";
  }
  else if( iRetorno == 56 ) {
    *Retorno = "Ultrapassou valor do pagamento.";
  }
  else if( iRetorno == 57 ) {
    *Retorno = "Registrador não programado ou troco já realizado.";
  }
  else if( iRetorno == 58 ) {
    *Retorno = "Falta completar valor do pagamento.";
  }
  else if( iRetorno == 59 ) {
    *Retorno = "Campo somente de caracteres não numéricos.";
  }
  else if( iRetorno == 60 ) {
    *Retorno = "Excedeu campo máximo de caracteres.";
  }
  else if( iRetorno == 61 ) {
    *Retorno = "Troco não realizado.";
  }
  else if( iRetorno == 62 ) {
    *Retorno = "Comando desabilitado.";
  }
  else {
    *Retorno = "Erro da impressora fiscal. Retorno desconhecido : " + IntToStr( iRetorno );
  }
}
//---------------------------------------------------------------------------

