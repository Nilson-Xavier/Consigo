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
    	Msg = "Fun��o da Impressora Ainda em Execu��o!";
    }
    else if( ret == 2 ) {
    	Msg = "Uma Outra Fun��o da Impressora est� sendo Executada!";
    }
    else if( ret == 3 ) {
    	Msg = "A Fun��o da Impressora foi Cancelada!";
    }
    else if( ret == 4 ) {
    	Msg = "A Impressora n�o est� Pronta para Uso!";
    }
    else if( ret == 5 ) {
    	Msg = "A Impressora N�o foi Iniciada!";
    }
    else if( ret == 6 ) {
    	Msg = "N�o h� Comando em Execu��o!";
    }
    else if( ret == 7 ) {
    	Msg = "A Fun��o da Impressora N�o foi Iniciada!";
    }
    else if( ret == 8 ) {
    	Msg = "A Impressora N�o foi Encontrada!";
    }
    else if( ret == 9 ) {
    	Msg = "Time Out de Valida��o de Documento!";
    }
    else if( ret == 10 ) {
    	Msg = "Impressora sem Papel!\r\rColoque uma Nova Bobina e Refa�a a Opera��o.";
    }
    else if( ret == 50 ) {
    	Msg = "Ocorreu um Erro na Execu��o da Fun��o!";
    }
    else if( ret == 51 ) {
    	Msg = "Ocorreu um Erro na Aloca��o de Recurso do Windows!";
    }
    else if( ret == 52 ) {
    	Msg = "Par�metro da Fun��o da Impressora Inv�lido!";
    }
    else if( ret == 53 ) {
    	Msg = "Erro no Arquivo de Configura��o: MECAF.INI!";
    }
    else if( ret == 54 ) {
    	Msg = "Time Out de Execu��o da Fun��o!";
    }
    else if( ret == 55 ) {
    	Msg = "Erro de Comunica��o com a Impressora!";
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
    	Msg = "A Impressora Pode estar Desligada, com o Cabo de Comunica��o Desconectado ou com Alguns dos Sinais da Interface Inoperante.";
    }
  	else if( ret == 2 ) {
    	Msg = "A Impressora Ocupada ou Buffer de Recep��o Est� Cheio!";
    }
  	else if( ret == 3 ) {
    	Msg = "A Impressora Est� sem Papel!\r\rColoque uma Nova Bobina e Refa�a a Opera��o.";
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
        throw Exception( "Erro ao Carregar as Fun��es da Biblioteca MECAFW32.DLL!\r\r\Favor Verificar." );
      }
      else {
        return( "Erro ao Carregar as Fun��es da Biblioteca MECAFW32.DLL!\r\rFavor Verificar." );
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

