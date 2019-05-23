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
      *Retorno = "Erro ao carregar as fun��es da biblioteca ECF3E32.DLL.\r\rFavor verificar!";
    }
    else {
      LeProComp( PCAbre( ), false, Retorno );
      if( *Retorno != "" ) {
      	//FreeLibrary( iHandleDll );
       	*Retorno = "Erro de comunica��o com a impressora fiscal.\r\rFavor verificar!";
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
  // N�o haver� Relat�rio Gerencial!
  Retorno_ = PCReducaoZ( "0" );
  Sleep( 23000 );
  LeProComp( Retorno_, true, Retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LeituraMemoriaFiscal( String* DataInic, String* DataFinal, String* &Retorno ) {

 	int Retorno_;

	if( StrToDate( *DataInic ) >= StrToDate( *DataFinal ) ) {
   	*Retorno = "A Data Inicial N�o Pode Ser Maior ou Igual � Data Final para a Leitura da Mem�ria Fiscal!";
  }
  else {
  	*DataInic = StringReplace( *DataInic, "/", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase );
    *DataFinal = StringReplace( *DataFinal, "/", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase );
	  // A Leitura ser� Completa!!!
    Retorno_ = PCLerData( DataInic->c_str( ), DataFinal->c_str( ), "0" );
    Sleep( 25000 );
  	LeProComp( Retorno_, true, Retorno );
	}
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::LeituraReducaoFiscal( String* RedInic, String* RedFin, String* &Retorno ) {

  int Retorno_;

  if( RedInic->ToInt( ) >= RedFin->ToInt( ) ) {
   	*Retorno = "A Redu��o Inicial N�o pode ser maior ou igual que a Redu��o Final!";
  }
  else {
  	while( RedInic->Length( ) < 4 ) {
    	*RedInic = "0" + *RedInic;
    }
  	while( RedFin->Length( ) < 4 ) {
    	*RedFin = "0" + *RedFin;
    }
	  // A Leitura ser� Completa!!!
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
		*Retorno = "Cupom N�o Fiscal Aberto!!!";
  }
  else if( PCTransStatus( 4, BufStat ) ) {
		*Retorno = "Em interven��o Fiscal!!!";
  }
  else if( PCTransStatus( 5, BufStat ) ) {
		*Retorno = "Em Impress�o Fiscal!!!";
  }
  else if( PCTransStatus( 6, BufStat ) ) {
		*Retorno = "Redu��o Z Pendente!!!";
  }
  else if( PCTransStatus( 9, BufStat ) ) {
		*Retorno = "Em In�cio de Cupom de Venda!!!";
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
		*Retorno = "Em Redu��o Z!!!";
  }
  else if( PCTransStatus( 15, BufStat ) ) {
		*Retorno = "Em Leitura X!!!";
  }
  else if( PCTransStatus( 16, BufStat ) ) {
		*Retorno = "Em Leitura da Mem�ria Fiscal!!!";
  }
  else if( PCTransStatus( 17, BufStat ) ) {
  	*Retorno = "A Tampa da Impressora Fiscal est� Aberta!!!";
  }
  else if( PCTransStatus( 19, BufStat ) ) {
		*Retorno = "Buffer Cheio!!!";
  }
  else if( PCTransStatus( 20, BufStat ) ) {
    *Retorno = "Erro Irrecuper�vel!!!";
  }
  else if( PCTransStatus( 21, BufStat ) ) {
    *Retorno = "Erro Mec�nico!!!";
  }
  else if( PCTransStatus( 22, BufStat ) ) {
    *Retorno = "Temperatura da Cabe�a de Impress�o Alta!!!\r\r Espere Alguns Minutos.";
  }
  else if( PCTransStatus( 23, BufStat ) ) {
    *Retorno = "O Papel da Impressora Fiscal est� Acabando!!!";
  }
  else if( PCTransStatus( 24, BufStat ) ) {
		*Retorno = "Comando em Execu��o!!!";
  }
  else if( PCTransStatus( 26, BufStat ) ) {
		*Retorno = "Esperando Inser��o de Cheque!!!";
  }
  else if( PCTransStatus( 27, BufStat ) ) {
		*Retorno = "Cheque Detectado!!!";
  }
  else if( PCTransStatus( 28, BufStat ) ) {
  	*Retorno = "N�o h� Papel na Impressora Fiscal!!!";
  }
  else if( PCTransStatus( 30, BufStat ) ) {
		*Retorno = "Esperando Inser��o do Documento para Valida��o!!!";
  }
  else if( PCTransStatus( 31, BufStat ) ) {
		*Retorno = "Documento para Valida��o Detectado!!!";
  }
  else if( PCTransStatus( 32, BufStat ) ) {
    *Retorno = "Leitura X Pendente!!!";
  }
  else if( PCTransStatus( 33, BufStat ) ) {
		*Retorno = "Em Totaliza��o!!!";
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
    	*Retorno = "Erro de comunica��o com a impressora fiscal ProComp!";
    }
  }
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::MensagemProComp( int iRetorno, String* &Retorno ) {

  if( iRetorno == -1 ) {
    *Retorno = "Erro gen�rico na execu��o da fun��o. Perda de comunica��o com a impressora.";
  }
  else if( iRetorno == -3 ) {
    *Retorno = "Leitura ass�ncrona em andamento. Comando sendo executado.";
  }
  else if( iRetorno == -4 ) {
    *Retorno = "TimeOut na execu��o do comando.";
  }
  else if( iRetorno == -5 ) {
    *Retorno = "Tamanho da mensagem enviada pela impressora � maior que o buffer de recep��o fornecido pela aplica��o.";
  }
  else if( iRetorno == -7 ) {
    *Retorno = "Erro no arquivo de configura��o CIF.INI.";
  }
  else if( iRetorno == -8 ) {
    *Retorno = "Falha na abertura da serial.";
  }
  else if( iRetorno == -11 ) {
    *Retorno = "Tampa aberta.";
  }
  else if( iRetorno == -12 ) {
    *Retorno = "Erro mec�nico.";
  }
  else if( iRetorno == -13 ) {
    *Retorno = "Erro irrecuperavel.";
  }
  else if( iRetorno == -14 ) {
    *Retorno = "Temperatura da cabe�a de impress�o est� alta.";
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
    *Retorno = "Em leitura de mem�ria fiscal.";
  }
  else if( iRetorno == -24 ) {
    *Retorno = "Em totaliza��o.";
  }
  else if( iRetorno == -25 ) {
    *Retorno = "Em pagamento.";
  }
  else if( iRetorno == -26 ) {
    *Retorno = "Ainda n�o obteve retorno.";
  }
  else if( iRetorno == 1 ) {
    *Retorno = "O cabe�alho cont�m caracteres inv�lidos.";
  }
  else if( iRetorno == 2 ) {
    *Retorno = "Comando inexistente.";
  }
  else if( iRetorno == 3 ) {
    *Retorno = "Valor n�o num�rico em campo num�rico.";
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
    *Retorno = "O intervalo � inconsistente. O primeiro deve ser menor que o segundo.";
  }
  else if( iRetorno == 8 ) {
    *Retorno = "Tributo inv�lido.";
  }
  else if( iRetorno == 9 ) {
    *Retorno = "A string TOTAL n�o � aceita.";
  }
  else if( iRetorno == 10 ) {
    *Retorno = "A sintaxe do comando est� errada.";
  }
  else if( iRetorno == 11 ) {
    *Retorno = "Excedeu o n�mero m�ximo de linhas permitidas pelo comando.";
  }
  else if( iRetorno == 12 ) {
    *Retorno = "O terminador enviado n�o obedece o protocolo de comunica��o.";
  }
  else if( iRetorno == 13 ) {
    *Retorno = "O checksum enviado est� incorreto.";
  }
  else if( iRetorno == 15 ) {
    *Retorno = "A situa��o tribut�ria deve iniciar com T, F ou N.";
  }
  else if( iRetorno == 16 ) {
    *Retorno = "Data inv�lida.";
  }
  else if( iRetorno == 17 ) {
    *Retorno = "Hora inv�lida.";
  }
  else if( iRetorno == 18 ) {
    *Retorno = "Aliquota n�o programada ou fora do intervalo.";
  }
  else if( iRetorno == 19 ) {
    *Retorno = "O campo de sinal est� incorreto.";
  }
  else if( iRetorno == 20 ) {
    *Retorno = "Comando s� aceito em interven��o fiscal.";
  }
  else if( iRetorno == 21 ) {
    *Retorno = "Comando s� aceito em modo normal.";
  }
  else if( iRetorno == 22 ) {
    *Retorno = "Necess�rio abrir cupom fiscal.";
  }
  else if( iRetorno == 23 ) {
    *Retorno = "Comando n�o aceito durante cupom fiscal.";
  }
  else if( iRetorno == 24 ) {
    *Retorno = "Necess�rio abrir cupom n�o fiscal.";
  }
  else if( iRetorno == 25 ) {
    *Retorno = "Comando n�o aceito durante cupom n�o fiscal.";
  }
  else if( iRetorno == 26 ) {
    *Retorno = "O rel�gio est� em hor�rio de ver�o.";
  }
  else if( iRetorno == 27 ) {
    *Retorno = "O rel�gio n�o est� em hor�rio de ver�o.";
  }
  else if( iRetorno == 28 ) {
    *Retorno = "Necess�rio realizar redu��o Z.";
  }
  else if( iRetorno == 29 ) {
    *Retorno = "Fechamento do dia (Redu��o Z) j� executado.";
  }
  else if( iRetorno == 30 ) {
    *Retorno = "Necess�rio programar legenda.";
  }
  else if( iRetorno == 31 ) {
    *Retorno = "Item inexistente ou j� cancelado.";
  }
  else if( iRetorno == 32 ) {
    *Retorno = "O cupom anterior n�o pode ser cancelado.";
  }
  else if( iRetorno == 33 ) {
    *Retorno = "Detectado falta de papel.";
  }
  else if( iRetorno == 36 ) {
    *Retorno = "Necess�rio programar os dados do estabelecimento.";
  }
  else if( iRetorno == 37 ) {
    *Retorno = "Necess�rio realizar interven��o t�cnica.";
  }
  else if( iRetorno == 38 ) {
    *Retorno = "A mem�ria fiscal n�o permite mais realizar vendas.";
  }
  else if( iRetorno == 39 ) {
    *Retorno = "Ocorreu algum problema na mem�ria fiscal.";
  }
  else if( iRetorno == 40 ) {
    *Retorno = "Necess�rio programar a data do rel�gio.";
  }
  else if( iRetorno == 41 ) {
    *Retorno = "N�mero m�ximo de �tens por cupom ultrapassado.";
  }
  else if( iRetorno == 42 ) {
    *Retorno = "J� foi realizado o ajuste de hora di�rio.";
  }
  else if( iRetorno == 43 ) {
    *Retorno = "Comando v�lido ainda em execu��o.";
  }
  else if( iRetorno == 44 ) {
    *Retorno = "Est� em estado de impress�o de cheque.";
  }
  else if( iRetorno == 45 ) {
    *Retorno = "N�o est� em estado de impress�o de cheque.";
  }
  else if( iRetorno == 46 ) {
    *Retorno = "Necess�rio inserir o cheque.";
  }
  else if( iRetorno == 47 ) {
    *Retorno = "Necess�rio inserir nova bobina.";
  }
  else if( iRetorno == 48 ) {
    *Retorno = "Necess�rio executar leitura X.";
  }
  else if( iRetorno == 49 ) {
    *Retorno = "Detectado algum problema na impressora.";
  }
  else if( iRetorno == 50 ) {
    *Retorno = "Cupom j� foi totalizado.";
  }
  else if( iRetorno == 51 ) {
    *Retorno = "Necess�rio totalizar cupom antes de fechar.";
  }
  else if( iRetorno == 52 ) {
    *Retorno = "Necess�rio finalizar cupom com comando correto.";
  }
  else if( iRetorno == 53 ) {
    *Retorno = "Ocorreu erro de grava��o na mem�ria fiscal.";
  }
  else if( iRetorno == 54 ) {
    *Retorno = "Excedeu n�mero m�ximo de estabelecimentos.";
  }
  else if( iRetorno == 55 ) {
    *Retorno = "Mem�ria fiscal n�o inicializada completamente.";
  }
  else if( iRetorno == 56 ) {
    *Retorno = "Ultrapassou valor do pagamento.";
  }
  else if( iRetorno == 57 ) {
    *Retorno = "Registrador n�o programado ou troco j� realizado.";
  }
  else if( iRetorno == 58 ) {
    *Retorno = "Falta completar valor do pagamento.";
  }
  else if( iRetorno == 59 ) {
    *Retorno = "Campo somente de caracteres n�o num�ricos.";
  }
  else if( iRetorno == 60 ) {
    *Retorno = "Excedeu campo m�ximo de caracteres.";
  }
  else if( iRetorno == 61 ) {
    *Retorno = "Troco n�o realizado.";
  }
  else if( iRetorno == 62 ) {
    *Retorno = "Comando desabilitado.";
  }
  else {
    *Retorno = "Erro da impressora fiscal. Retorno desconhecido : " + IntToStr( iRetorno );
  }
}
//---------------------------------------------------------------------------

