//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ImpressoraMecaf.h"
#include <dstring.h>
#include <vcl\Windows.hpp>
#include <SysInit.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

HINSTANCE iHandleDllMecaf;

String TImpressoraMecaf::ObterRetornoComando( int ret, bool local ) {

	String Msg;

  if( ret != 0 ) {
  	if( ret == 1 ) {
    	Msg = "Função da Impressora Ainda em Execução!";
    }
    else if( ret == 2 ) {
    	Msg = "Uma Outra Função da Impressora está sendo Executada!";
    }
    else if( ret == 3 ) {
    	Msg = "A Função da Impressora foi Cancelada!";
    }
    else if( ret == 4 ) {
    	Msg = "A Impressora não está Pronta para Uso!";
    }
    else if( ret == 5 ) {
    	Msg = "A Impressora Não foi Iniciada!";
    }
    else if( ret == 6 ) {
    	Msg = "Não há Comando em Execução!";
    }
    else if( ret == 7 ) {
    	Msg = "A Função da Impressora Não foi Iniciada!";
    }
    else if( ret == 8 ) {
    	Msg = "A Impressora Não foi Encontrada!";
    }
    else if( ret == 9 ) {
    	Msg = "Time Out de Validação de Documento!";
    }
    else if( ret == 10 ) {
    	Msg = "Impressora sem Papel!\r\rColoque uma Nova Bobina e Refaça a Operação.";
    }
    else if( ret == 50 ) {
    	Msg = "Ocorreu um Erro na Execução da Função!";
    }
    else if( ret == 51 ) {
    	Msg = "Ocorreu um Erro na Alocação de Recurso do Windows!";
    }
    else if( ret == 52 ) {
    	Msg = "Parâmetro da Função da Impressora Inválido!";
    }
    else if( ret == 53 ) {
    	Msg = "Erro no Arquivo de Configuração: MECAF.INI!";
    }
    else if( ret == 54 ) {
    	Msg = "Time Out de Execução da Função!";
    }
    else if( ret == 55 ) {
    	Msg = "Erro de Comunicação com a Impressora!";
    }
		if( iHandleDllMecaf != 0 ) {
  		FreeLibrary( iHandleDllMecaf );
	  }
    if( local ) {
	    throw Exception( Msg );
    }
    else {
    	return( Msg );
    }
  }
  return( "0" );
}
//-----------------------------------------------------------------------------
String TImpressoraMecaf::ObterStatus( bool local ) {

	String Msg;
  int ret;

  ret = CPStatusImpressora( );
  Sleep( 1000 );
  if( ret != 1 ) {
  	if( ret == 0 ) {
    	Msg = "A Impressora Pode estar Desligada, com o Cabo de Comunicação Desconectado ou com Alguns dos Sinais da Interface Inoperante.";
    }
  	else if( ret == 2 ) {
    	Msg = "A Impressora Ocupada ou Buffer de Recepção Está Cheio!";
    }
  	else if( ret == 3 ) {
    	Msg = "A Impressora Está sem Papel!\r\rColoque uma Nova Bobina e Refaça a Operação.";
    }
  	else if( ret == 4 ) {
    	Msg = "Ocorreu um Erro no Funcionamento da Impressora!";
    }
		if( iHandleDllMecaf != 0 ) {
  		FreeLibrary( iHandleDllMecaf );
  	}
    if( local ) {
	    throw Exception( Msg );
    }
    else {
    	return( Msg );
    }
  }
  return( "0" );
}
//------------------------------------------------------------------------------
String TImpressoraMecaf::CarregarDll( bool local ) {

  iHandleDllMecaf = LoadLibrary( "MECAFW32.DLL" );
  if( iHandleDllMecaf != 0 ) {
  	CPStatusImpressora = ( CPStatusImp ) GetProcAddress( iHandleDllMecaf, "CPStatusImp" );
    CPInitImpressora   = ( CPInit ) GetProcAddress( iHandleDllMecaf, "CPInit" );
    CPImprimeTexto     = ( CPImprime ) GetProcAddress( iHandleDllMecaf, "CPImprime" );
    if( ( CPStatusImpressora == NULL ) || ( CPInitImpressora == NULL ) || ( CPImprimeTexto == NULL ) ) {
			FreeLibrary( iHandleDllMecaf );
      if( local ) {
        throw Exception( "Erro ao Carregar as Funções da Biblioteca MECAFW32.DLL!\r\r\Favor Verificar." );
      }
      else {
        return( "Erro ao Carregar as Funções da Biblioteca MECAFW32.DLL!\r\rFavor Verificar." );
      }
    }
    else {
      return( "0" );
    }
  }
  else if( local ) {
  	throw Exception( "Erro ao Carregar a Biblioteca MECAFW32.DLL!\r\rFavor Verificar." );
  }
  else {
  	return( "Erro ao Carregar a Biblioteca MECAFW32.DLL!\r\rFavor Verificar." );
  }
}
//------------------------------------------------------------------------------
String TImpressoraMecaf::Iniciar( bool local ) {

  int Retorno;

 	Retorno = CPInitImpressora( );
  Sleep( 1000 );
  return( ObterRetornoComando( Retorno, local ) );
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::Finalizar( ) {

	if( iHandleDllMecaf != 0 ) {
  	FreeLibrary( iHandleDllMecaf );
  }
}
//------------------------------------------------------------------------------
String TImpressoraMecaf::Imprimir( String Texto, bool local ) {

	int Retorno;

  Retorno = CPImprimeTexto( Texto.c_str( ), Texto.Length( ) );
  Sleep( 1000 );
	return( ObterRetornoComando( Retorno, local ) );
}
//------------------------------------------------------------------------------

