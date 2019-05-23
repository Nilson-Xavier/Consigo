//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <vcl\Dialogs.hpp>
#include <systdate.h>
#include <vcl\Forms.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ImpressoraFiscalECF.h"
//---------------------------------------------------------------------------

HINSTANCE iHandleDll;

String TImpressoraFiscal::CarregaDll( bool local ) {

  Boolean Ok;
  String retorno;

  iHandleDll = LoadLibrary( "ECF3E32.DLL" );
   if( iHandleDll != 0 ) {
      PCAbre             = ( OPENCIF ) GetProcAddress( iHandleDll , "OPENCIF" );
      PCFecha            = ( CLOSECIF ) GetProcAddress( iHandleDll , "CLOSECIF" );
      PCAbreCupom        = ( ABRECUPOMFISCAL ) GetProcAddress( iHandleDll , "ABRECUPOMFISCAL" );
      PCLancaItem        = ( VENDAITEM ) GetProcAddress( iHandleDll , "VENDAITEM" );
      PCCancItem         = ( CANCELAMENTOITEM )GetProcAddress( iHandleDll , "CANCELAMENTOITEM" );
      PCTotalCupom       = ( TOTALIZARCUPOM ) GetProcAddress( iHandleDll , "TOTALIZARCUPOM" );
      PCPagamento        = ( PAGAMENTO ) GetProcAddress( iHandleDll , "PAGAMENTO" );
      PCFechaCupom       = ( FECHACUPOMFISCAL ) GetProcAddress( iHandleDll , "FECHACUPOMFISCAL" );
      PCCancelaCupom     = ( CANCELACUPOMFISCAL ) GetProcAddress( iHandleDll , "CANCELACUPOMFISCAL" );
      PCLeituraX         = ( LEITURAX ) GetProcAddress( iHandleDll , "LEITURAX" );
      PCReducaoZ         = ( REDUCAOZ ) GetProcAddress( iHandleDll , "REDUCAOZ" );
      PCLerData          = ( LEMEMFISCALDATA ) GetProcAddress( iHandleDll , "LEMEMFISCALDATA" );
      PCLerReducao       = ( LEMEMFISCALREDUCAO ) GetProcAddress( iHandleDll , "LEMEMFISCALREDUCAO" );
      PCAbreNaoFiscal    = ( ABRECUPOMNAOVINCULADO ) GetProcAddress( iHandleDll , "ABRECUPOMNAOVINCULADO" );
      PCAbreNaoFiscalVinculado = ( ABRECUPOMVINCULADO ) GetProcAddress( iHandleDll , "ABRECUPOMVINCULADO" );
      PCEncerraNaoFiscal = ( ENCERRARCUPOM ) GetProcAddress( iHandleDll , "ENCERRARCUPOM" );
      PCImprimeNaoFiscal = ( IMPRIMELINHANAOFISCAL ) GetProcAddress( iHandleDll , "IMPRIMELINHANAOFISCAL" );
      PCTransStatus      = ( TRANSSTATUS ) GetProcAddress( iHandleDll , "TRANSSTATUS" );
      PCObtemRetorno     = ( OBTEMRETORNO ) GetProcAddress( iHandleDll , "OBTEMRETORNO" );
      PCEcfParEsp        = ( ECFPARESP ) GetProcAddress( iHandleDll , "ECFPARESP" );
      PCAvancaLinha      = ( AVANCALINHA ) GetProcAddress( iHandleDll, "AVANCALINHA" );
      PCProgLegenda      = ( PROGRAMALEGENDA ) GetProcAddress( iHandleDll, "PROGRAMALEGENDA" );
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
        if( local ) {
	        throw Exception( "Erro ao carregar as fun��es da biblioteca ECF3E32.DLL.\r\rFavor verificar!" );
        }
        else {
        	retorno = "Erro ao carregar as fun��es da biblioteca ECF3E32.DLL.\r\rFavor verificar!";
        }
      }
      else {
        if( LeProComp( PCAbre( ), false, local ) != "0" ) {
        	FreeLibrary( iHandleDll );
          if( local ) {
	          throw Exception( "Erro de comunica��o com a impressora fiscal.\r\rFavor verificar!" );
  				}
          else {
          	retorno = "Erro de comunica��o com a impressora fiscal.\r\rFavor verificar!";
          }
        }
        else {
        	return( "0" );
        }
      }
   }
   else {
   	 if( local ) {
       throw Exception( "Erro ao carregar a biblioteca ECF3E32.DLL.\r\rFavor verificar!" );
     }
     else {
     	 retorno = "Erro ao carregar a biblioteca ECF3E32.DLL.\r\rFavor verificar!";
     }
   }
   return( retorno );
}
//---------------------------------------------------------------------------
void TImpressoraFiscal::FechaSerial( ) {

  PCFecha( );
  if( iHandleDll != 0 ) {
	  FreeLibrary( iHandleDll );
  }
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::FechaCupomNaoFiscal( bool local ) {

  // Fecha o cupom n�o fiscal
  return( LeProComp( PCEncerraNaoFiscal( ), true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::AbreCupom( bool local ) {

  return( LeProComp( PCAbreCupom( ), true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::AbreCupomNaoFiscal( bool local ) {

  return( LeProComp( PCAbreNaoFiscal( ), true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::AbreCupomNaoFiscalVinculado( bool local ) {

  return( LeProComp( PCAbreNaoFiscalVinculado( ), true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::LeProComp( int iRetorno, Boolean lProcessaRet, bool local ) {

  char BufRetorno[2048];
  Boolean Ok = false;
  int i;

  if( iRetorno == 0 ) {
	  Ok = true;
  }
  if( !Ok ) {
    return( MensagemProComp( iRetorno, local ) );
  }
  else if( lProcessaRet ) {
    for( i = 0; i < 10; i++ ) {
      iRetorno = PCObtemRetorno( BufRetorno );
      if( iRetorno == 0 ) {
        Ok = true;
        break;
      }
      else if( ( iRetorno > 0 ) || ( iRetorno != -26 ) ) {
        Ok = false;
        return( MensagemProComp( iRetorno, local ) );
      }
      Sleep( 1000 );
    }
    // Ultrapassou o time-out de retorno da impressora
    if( !Ok ) {
			//MessageDlg( "Erro de comunica��o com a impressora fiscal ProComp !", mtError, TMsgDlgButtons( ) << mbOK, 0 );
      if( local ) {
	      throw Exception( "Erro de comunica��o com a impressora fiscal ProComp!" );
      }
      else {
      	return( "Erro de comunica��o com a impressora fiscal ProComp!" );
      }
    }
  }
  return( "0" );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::MensagemProComp( int iRetorno, bool local ) {

  String sMensagem;

  if( iRetorno == -1 ) {
    sMensagem = "Erro gen�rico na execu��o da fun��o. Perda de comunica��o com a impressora.";
  }
  else if( iRetorno == -3 ) {
    sMensagem = "Leitura ass�ncrona em andamento. Comando sendo executado.";
  }
  else if( iRetorno == -4 ) {
    sMensagem = "TimeOut na execu��o do comando.";
  }
  else if( iRetorno == -5 ) {
    sMensagem = "Tamanho da mensagem enviada pela impressora � maior que o buffer de recep��o fornecido pela aplica��o.";
  }
  else if( iRetorno == -7 ) {
    sMensagem = "Erro no arquivo de configura��o CIF.INI.";
  }
  else if( iRetorno == -8 ) {
    sMensagem = "Falha na abertura da serial.";
  }
  else if( iRetorno == -11 ) {
    sMensagem = "Tampa aberta.";
  }
  else if( iRetorno == -12 ) {
    sMensagem = "Erro mec�nico.";
  }
  else if( iRetorno == -13 ) {
    sMensagem = "Erro irrecuperavel.";
  }
  else if( iRetorno == -14 ) {
    sMensagem = "Temperatura da cabe�a de impress�o est� alta.";
  }
  else if( iRetorno == -15 ) {
    sMensagem = "Pouco papel.";
  }
  else if( iRetorno == -16 ) {
    sMensagem = "Em inicio de cupom de venda.";
  }
  else if( iRetorno == -17 ) {
    sMensagem = "Em venda de item.";
  }
  else if( iRetorno == -18 ) {
    sMensagem = "Em cancelamento de item.";
  }
  else if( iRetorno == -19 ) {
    sMensagem = "Em cancelamento de cupom.";
  }
  else if( iRetorno == -20 ) {
    sMensagem = "Em fechamento de cupom.";
  }
  else if( iRetorno == -21 ) {
    sMensagem = "Em Reducao Z.";
  }
  else if( iRetorno == -22 ) {
    sMensagem = "Em Leitura X.";
  }
  else if( iRetorno == -23 ) {
    sMensagem = "Em leitura de mem�ria fiscal.";
  }
  else if( iRetorno == -24 ) {
    sMensagem = "Em totaliza��o.";
  }
  else if( iRetorno == -25 ) {
    sMensagem = "Em pagamento.";
  }
  else if( iRetorno == -26 ) {
    sMensagem = "Ainda n�o obteve retorno.";
  }
  else if( iRetorno == 1 ) {
    sMensagem = "O cabe�alho cont�m caracteres inv�lidos.";
  }
  else if( iRetorno == 2 ) {
    sMensagem = "Comando inexistente.";
  }
  else if( iRetorno == 3 ) {
    sMensagem = "Valor n�o num�rico em campo num�rico.";
  }
  else if( iRetorno == 4 ) {
    sMensagem = "Valor fora da faixa entre 20h e 7Fh.";
  }
  else if( iRetorno == 5 ) {
    sMensagem = "Campo de iniciar com @, & ou %.";
  }
  else if( iRetorno == 6 ) {
    sMensagem = "Campo de iniciar com $, # ou ?.";
  }
  else if( iRetorno == 7 ) {
    sMensagem = "O intervalo � inconsistente. O primeiro deve ser menor que o segundo.";
  }
  else if( iRetorno == 8 ) {
    sMensagem = "Tributo inv�lido.";
  }
  else if( iRetorno == 9 ) {
    sMensagem = "A string TOTAL n�o � aceita.";
  }
  else if( iRetorno == 10 ) {
    sMensagem = "A sintaxe do comando est� errada.";
  }
  else if( iRetorno == 11 ) {
    sMensagem = "Excedeu o n�mero m�ximo de linhas permitidas pelo comando.";
  }
  else if( iRetorno == 12 ) {
    sMensagem = "O terminador enviado n�o obedece o protocolo de comunica��o.";
  }
  else if( iRetorno == 13 ) {
    sMensagem = "O checksum enviado est� incorreto.";
  }
  else if( iRetorno == 15 ) {
    sMensagem = "A situa��o tribut�ria deve iniciar com T, F ou N.";
  }
  else if( iRetorno == 16 ) {
    sMensagem = "Data inv�lida.";
  }
  else if( iRetorno == 17 ) {
    sMensagem = "Hora inv�lida.";
  }
  else if( iRetorno == 18 ) {
    sMensagem = "Aliquota n�o programada ou fora do intervalo.";
  }
  else if( iRetorno == 19 ) {
    sMensagem = "O campo de sinal est� incorreto.";
  }
  else if( iRetorno == 20 ) {
    sMensagem = "Comando s� aceito em interven��o fiscal.";
  }
  else if( iRetorno == 21 ) {
    sMensagem = "Comando s� aceito em modo normal.";
  }
  else if( iRetorno == 22 ) {
    sMensagem = "Necess�rio abrir cupom fiscal.";
  }
  else if( iRetorno == 23 ) {
    sMensagem = "Comando n�o aceito durante cupom fiscal.";
  }
  else if( iRetorno == 24 ) {
    sMensagem = "Necess�rio abrir cupom n�o fiscal.";
  }
  else if( iRetorno == 25 ) {
    sMensagem = "Comando n�o aceito durante cupom n�o fiscal.";
  }
  else if( iRetorno == 26 ) {
    sMensagem = "O rel�gio est� em hor�rio de ver�o.";
  }
  else if( iRetorno == 27 ) {
    sMensagem = "O rel�gio n�o est� em hor�rio de ver�o.";
  }
  else if( iRetorno == 28 ) {
    sMensagem = "Necess�rio realizar redu��o Z.";
  }
  else if( iRetorno == 29 ) {
    sMensagem = "Fechamento do dia (Redu��o Z) j� executado.";
  }
  else if( iRetorno == 30 ) {
    sMensagem = "Necess�rio programar legenda.";
  }
  else if( iRetorno == 31 ) {
    sMensagem = "Item inexistente ou j� cancelado.";
  }
  else if( iRetorno == 32 ) {
    sMensagem = "O cupom anterior n�o pode ser cancelado.";
  }
  else if( iRetorno == 33 ) {
    sMensagem = "Detectado falta de papel.";
  }
  else if( iRetorno == 36 ) {
    sMensagem = "Necess�rio programar os dados do estabelecimento.";
  }
  else if( iRetorno == 37 ) {
    sMensagem = "Necess�rio realizar interven��o t�cnica.";
  }
  else if( iRetorno == 38 ) {
    sMensagem = "A mem�ria fiscal n�o permite mais realizar vendas.";
  }
  else if( iRetorno == 39 ) {
    sMensagem = "Ocorreu algum problema na mem�ria fiscal.";
  }
  else if( iRetorno == 40 ) {
    sMensagem = "Necess�rio programar a data do rel�gio.";
  }
  else if( iRetorno == 41 ) {
    sMensagem = "N�mero m�ximo de �tens por cupom ultrapassado.";
  }
  else if( iRetorno == 42 ) {
    sMensagem = "J� foi realizado o ajuste de hora di�rio.";
  }
  else if( iRetorno == 43 ) {
    sMensagem = "Comando v�lido ainda em execu��o.";
  }
  else if( iRetorno == 44 ) {
    sMensagem = "Est� em estado de impress�o de cheque.";
  }
  else if( iRetorno == 45 ) {
    sMensagem = "N�o est� em estado de impress�o de cheque.";
  }
  else if( iRetorno == 46 ) {
    sMensagem = "Necess�rio inserir o cheque.";
  }
  else if( iRetorno == 47 ) {
    sMensagem = "Necess�rio inserir nova bobina.";
  }
  else if( iRetorno == 48 ) {
      sMensagem = "Necess�rio executar leitura X.";
  }
  else if( iRetorno == 49 ) {
    sMensagem = "Detectado algum problema na impressora.";
  }
  else if( iRetorno == 50 ) {
    sMensagem = "Cupom j� foi totalizado.";
  }
  else if( iRetorno == 51 ) {
    sMensagem = "Necess�rio totalizar cupom antes de fechar.";
  }
  else if( iRetorno == 52 ) {
    sMensagem = "Necess�rio finalizar cupom com comando correto.";
  }
  else if( iRetorno == 53 ) {
    sMensagem = "Ocorreu erro de grava��o na mem�ria fiscal.";
  }
  else if( iRetorno == 54 ) {
    sMensagem = "Excedeu n�mero m�ximo de estabelecimentos.";
  }
  else if( iRetorno == 55 ) {
    sMensagem = "Mem�ria fiscal n�o inicializada completamente.";
  }
  else if( iRetorno == 56 ) {
    sMensagem = "Ultrapassou valor do pagamento.";
  }
  else if( iRetorno == 57 ) {
    sMensagem = "Registrador n�o programado ou troco j� realizado.";
  }
  else if( iRetorno == 58 ) {
    sMensagem = "Falta completar valor do pagamento.";
  }
  else if( iRetorno == 59 ) {
    sMensagem = "Campo somente de caracteres n�o num�ricos.";
  }
  else if( iRetorno == 60 ) {
    sMensagem = "Excedeu campo m�ximo de caracteres.";
  }
  else if( iRetorno == 61 ) {
    sMensagem = "Troco n�o realizado.";
  }
  else if( iRetorno == 62 ) {
    sMensagem = "Comando desabilitado.";
  }
  else {
    sMensagem = "Erro da impressora fiscal. Retorno desconhecido : " + IntToStr( iRetorno );
  }
  if( local ) {
	  throw Exception( sMensagem );
  }
  else {
  	return( sMensagem );
  }
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::LancaItem( String sQtde, String sPrecoUnit, String sCodFiscal,
			  														 String sTipoDesc, String sVlrDesc, String sCodigo,
                                     String sDescricao, bool local ) {
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
	int Retorno;
  String sFormato = "0";
  String sTamDescr = "3";
  String sUnidade = "PC";
  String sLegendaOp = "              ";

  Retorno = PCLancaItem( sFormato.c_str( ) , sQtde.c_str( ), sPrecoUnit.c_str( ),
                         sCodFiscal.c_str( ), sTipoDesc.c_str( ), sVlrDesc.c_str( ),
                         sUnidade.c_str( ), sCodigo.c_str( ), sTamDescr.c_str( ),
                         sDescricao.c_str( ), sLegendaOp.c_str( ) );
  Sleep( 1000 );
  return( LeProComp( Retorno, true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::LancaItemNaoFiscal( String pAtrib, String pString, bool local ) {

	int Retorno;

  Retorno = PCImprimeNaoFiscal( pAtrib.c_str( ), pString.c_str( ) );
  Sleep( 1000 );
  return( LeProComp( Retorno, true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::CancelaCupom( bool local ) {

   return( LeProComp( PCCancelaCupom( ), true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::TotalizaCupom( bool local ) {

  String Oper, TipoDesc, Valor, LegOper;
  int Retorno;

  Oper = "";
  TipoDesc = "&";
  Valor = "000000000000000";
  LegOper = "              ";

  Retorno = PCTotalCupom( Oper.c_str( ), TipoDesc.c_str( ), Valor.c_str( ), LegOper.c_str( ) );
	Sleep( 3000 );
  return( LeProComp( Retorno, false, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::FechaCupom( String TamMensagem, String Mensagem, bool local ) {

  return( LeProComp( PCFechaCupom( TamMensagem.c_str( ), Mensagem.c_str( ) ), true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::PulaLinha( bool local ) {

  return( LeProComp( PCAvancaLinha( ), true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::LeituraX( bool local ) {

	int Retorno;
  // N�o haver� Relat�rio Gerencial!
  Retorno = PCLeituraX( "0" );
  Sleep( 5000 );
  return( LeProComp( Retorno, true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::ReducaoZ( bool local ) {

	int Retorno;
  // N�o haver� Relat�rio Gerencial!
  Retorno = PCReducaoZ( "0" );
  Sleep( 5000 );
  return( LeProComp( Retorno, true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::LeituraMemoriaFiscal( String DataInic, String DataFinal, bool local ) {

 	int retorno;

	if( StrToDate( DataInic ) >= StrToDate( DataFinal ) ) {
  	if( local ) {
    	throw Exception( "A Data Inicial N�o Pode Ser Maior que a Data Final para a Leitura da Mem�ria Fiscal!" );
    }
    else {
    	return( "A Data Inicial N�o Pode Ser Maior ou Igual � Data Final para a Leitura da Mem�ria Fiscal!" );
    }
  }
  else {
  	DataInic = StringReplace( DataInic, "/", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase );
    DataFinal = StringReplace( DataFinal, "/", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase );
	  // A Leitura ser� Completa!!!
    retorno = PCLerData( DataInic.c_str( ), DataFinal.c_str( ), "0" );
    Sleep( 5000 );
  	return( LeProComp( retorno, true, local ) );
	}
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::LeituraReducaoFiscal( String RedInic, String RedFin, bool local ) {

  int retorno;

  if( RedInic.ToInt( ) >= RedFin.ToInt( ) ) {
  	if( local ) {
    	throw Exception( "A Redu��o Inicial N�o pode ser maior ou igual que a Redu��o Final!" );
    }
    else {
    	return( "A Redu��o Inicial N�o pode ser maior ou igual que a Redu��o Final!" );
    }
  }
  else {
  	while( RedInic.Length( ) < 4 ) {
    	RedInic = "0" + RedInic;
    }
  	while( RedFin.Length( ) < 4 ) {
    	RedFin = "0" + RedFin;
    }
	  // A Leitura ser� Completa!!!
    retorno = PCLerReducao( RedInic.c_str( ), RedFin.c_str( ), "0" );
    Sleep( 5000 );
  	return( LeProComp( retorno, true, local ) );
	}
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::Pagamento( String Reg, String VPgto, String Subtr, bool local ) {

	int Retorno;

  Retorno = PCPagamento( Reg.c_str( ), VPgto.c_str( ), Subtr.c_str( ) );
  Sleep( 3000 );
  return( LeProComp( Retorno, true, local ) );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::UltimoCupomFiscal( int &cupom, bool local ) {

  int Retorno, i;
  char BufRetorno[2048];
  String Numero, NumeroCupom;

  Retorno = PCEcfParEsp( "41" );
  if( Retorno != 0 ) {
  	return( MensagemProComp( Retorno, local ) );
  }
  Retorno = PCObtemRetorno( BufRetorno );
  if( Retorno != 0 ) {
  	return( MensagemProComp( Retorno, local ) );
  }
  Numero = BufRetorno;
  for( i = Numero.Length( ); i >= Numero.Length( ) - 4; i-- ) {
  	NumeroCupom.Insert( Numero[i], 1 );
  }
  cupom = NumeroCupom.ToInt( );
  return( "0" );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::ProgramarLegenda( bool local ) {

	String retorno;

  retorno = LeProComp( PCProgLegenda( "00", "Dinheiro        " ), true, local );
  if( retorno != "0" ) {
  	return( retorno );
  }
  retorno = LeProComp( PCProgLegenda( "01", "Cheque          " ), true, local );
  if( retorno != "0" ) {
  	return( retorno );
  }
  retorno = LeProComp( PCProgLegenda( "02", "Cartao Debito   " ), true, local );
  if( retorno != "0" ) {
  	return( retorno );
  }
  retorno = LeProComp( PCProgLegenda( "03", "Cartao Credito  " ), true, local );
  if( retorno != "0" ) {
  	return( retorno );
  }
  retorno = LeProComp( PCProgLegenda( "04", "Financiado      " ), true, local );
  if( retorno != "0" ) {
  	return( retorno );
  }
  return( "0" );
}
//---------------------------------------------------------------------------
String TImpressoraFiscal::ObterStatus( bool local ) {

	char BufStat[40];
  String retorno;

  //LeProComp( PCTransStatus( 0, BufStat ), false );
  if( PCTransStatus( 6, BufStat ) ) {
		retorno = "Redu��o Z Pendente!!!";
  }
  else if( PCTransStatus( 17, BufStat ) ) {
  	retorno = "A Tampa da Impressora Fiscal est� Aberta!!!";
  }
  else if( PCTransStatus( 20, BufStat ) ) {
    retorno = "Erro Irrecuper�vel!!!";
  }
  else if( PCTransStatus( 21, BufStat ) ) {
    retorno = "Erro Mec�nico!!!";
  }
  else if( PCTransStatus( 22, BufStat ) ) {
    retorno = "Temperatura da Cabe�a de Impress�o Alta!!!\r\r Espere Alguns Minutos.";
  }
  else if( PCTransStatus( 23, BufStat ) ) {
    retorno = "O Papel da Impressora Fiscal est� Acabando!!!";
  }
  else if( PCTransStatus( 28, BufStat ) ) {
  	retorno = "N�o h� Papel na Impressora Fiscal!!!";
  }
  else if( PCTransStatus( 32, BufStat ) ) {
    retorno = "Leitura X Pendente!!!";
  }
  else {
  	retorno = "0";
  }
  if( ( retorno != "0" ) && ( local ) ) {
  	throw Exception( retorno );
  }
  else {
  	return( retorno );
  }
}
//---------------------------------------------------------------------------
