//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ImpressoraMecaf.h"
#include <math.h>
#include <dstring.h>
#include <vcl\Windows.hpp>
#include <SysInit.hpp>
#include "ConverteDinheiroTexto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

HINSTANCE iHandleDllMecaf;

//------------------------------------------------------------------------------
__fastcall TImpressoraMecaf::TImpressoraMecaf( ) {

  this->ValorTotal = new AnsiString( );
  this->Itens = new int( );
  this->FilmeRebobinado = new bool( false );
  this->NumeroCupom = new AnsiString( );
}
//------------------------------------------------------------------------------
__fastcall TImpressoraMecaf::~TImpressoraMecaf( ) {

  delete this->ValorTotal;
  delete this->Itens;
  delete this->FilmeRebobinado;
  delete this->NumeroCupom;
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::CarregarDll( String* &Retorno ) {

  try {
    *Retorno = "";
    iHandleDllMecaf = LoadLibrary( "MECAFW32.DLL" );
    if( iHandleDllMecaf != 0 ) {
    	CPStatusImpressora = ( CPStatusImp ) GetProcAddress( iHandleDllMecaf, "CPStatusImp" );
      CPInitImpressora   = ( CPInit ) GetProcAddress( iHandleDllMecaf, "CPInit" );
      CPImprimeTexto     = ( CPImprime ) GetProcAddress( iHandleDllMecaf, "CPImprime" );
      if( ( CPStatusImpressora == NULL ) || ( CPInitImpressora == NULL ) || ( CPImprimeTexto == NULL ) ) {
		  	FreeLibrary( iHandleDllMecaf );
        *Retorno = "Erro ao Carregar as Funções da Biblioteca MECAFW32.DLL!\r\rFavor Verificar.";
      }
    }
    else {
      *Retorno = "Erro ao Carregar a Biblioteca MECAFW32.DLL!\r\rFavor Verificar.";
   }
  }
  catch( String &Error ) {
    *Retorno = Error;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::Iniciar( String* &Retorno ) {

	int CodRetorno;

  try {
    *Retorno = "";
 	  CodRetorno = CPInitImpressora( );
    Sleep( 500 );
    return( ObterRetornoComando( CodRetorno, Retorno ) );
  }
  catch( String &Error ) {
    *Retorno = Error;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::Finalizar( ) {

	if( iHandleDllMecaf != 0 ) {
  	FreeLibrary( iHandleDllMecaf );
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::AbrirCupom( String* Cupom, String *CpfCnpj, String *Nome, String* &Retorno ) {

  int CodRetorno, i;
  TStringList *Texto;
  String *CpfCnpjFmt;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;
    CpfCnpjFmt = new AnsiString( );

    try {
      *Retorno = "";
      *this->NumeroCupom = *Cupom;
      while( Cupom->Length( ) != 6 ) {
        *Cupom = "0" + *Cupom;
      }

      Texto->Add( "   CONSIGO COMERCIO DE CINE FOTO E SOM LTDA.\x0A" );
	    Texto->Add( "\x1B\x57\x1   CONSIGO SOM IMAGEM\x1B\x57\x2\x0A" );
 	    Texto->Add( "RUA CONSELHEIRO CRISPINIANO, 105 - 1 AND.SALA 13\x0A" );
     	Texto->Add( "    CENTRO - SAO PAULO - SP - CEP: 01037-001\x0A\x0A" );
      Texto->Add( "................................................\x0A" );
 		  Texto->Add( "CNPJ:59201327/0001-74        IE:  112061543114\x0A" );
  	  DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "                 COO:" + *this->NumeroCupom + "\x0A" );
      if( !CpfCnpj->IsEmpty( ) && !Nome->IsEmpty( ) ) {
        for( i = 1; i <= CpfCnpj->Length( ); i++ ) {
          if( ( ( AnsiCompareStr( CpfCnpj->SubString( i, 1 ), "0" ) >= 0 ) && ( AnsiCompareStr( CpfCnpj->SubString( i, 1 ), "9" ) <= 0 ) ) ) {
            *CpfCnpjFmt = *CpfCnpjFmt + CpfCnpj->SubString( i, 1 );
          }
        }
        *CpfCnpjFmt = LeftStr( *CpfCnpjFmt, 14 );
        Texto->Add( "CNPJ/CPF consumidor:" + LeftStr( *CpfCnpjFmt + *Nome, 28 ) + "\x0A" );
      }
      Texto->Add( "\x1B\x57\x1      CUPOM FISCAL\x1B\x57\x2\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
    	  ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete CpfCnpjFmt;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::LancarItem( String* Qtd, String* PrecoUnit, String* Codigo,
      String* Descricao, String* &Retorno ) {

  String *Item, *PrecoTot;
  TStringList *Texto;
  int CodRetorno;

  try {
    *Retorno = "";
    Item = new AnsiString( );
    PrecoTot = new AnsiString( );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      DecimalSeparator = ',';
      ThousandSeparator = '.';
      *PrecoUnit = StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll );
      *PrecoTot = FormatFloat( "0.00",( StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) * StringReplace( *Qtd, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) );
      if( Codigo->Length( ) <= 15 ) {
        while( Codigo->Length( ) <= 15 ) {
          *Codigo = *Codigo + " ";
        }
      }
      if( Descricao->Length( ) > 114 ) {
        *Descricao = Descricao->Delete( 115, Descricao->Length( ) - 114 );
      }
      *this->Itens = *this->Itens + 1;
      *Item = *this->Itens;
      while( Item->Length( ) <= 2 ) {
        *Item = "0" + *Item;
      }
      if( *this->ValorTotal == "" ) {
        *this->ValorTotal = FormatFloat( "0.00", ( StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) * StringReplace( *Qtd, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) );
      }
      else {
        *this->ValorTotal = FormatFloat( "0.00", ( this->ValorTotal->ToDouble( ) + ( StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) * StringReplace( *Qtd, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) ) );
      }
      while( Qtd->Length( ) <= 3 ) {
        *Qtd = " " + *Qtd;
      }
      while( PrecoUnit->Length( ) <= 12 ) {
        *PrecoUnit = " " + *PrecoUnit;
      }
      while( PrecoTot->Length( ) <= 17 ) {
        *PrecoTot = " " + *PrecoTot;
      }

      Texto->Add( *Item + ")" + *Codigo + "pc\x0A" );
      if( Descricao->Pos( "Rebobinado" ) != 0 ) {
        *FilmeRebobinado = true;
      }
      if( Descricao->Length( ) <= 38 ) {
        while( Descricao->Length( ) <= 38 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( "[  " + *Descricao + "  ]\x0A" );
      }
      else if( ( Descricao->Length( ) > 38 ) && ( Descricao->Length( ) <= 76 ) ) {
        while( Descricao->Length( ) <= 76 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( "[  " + Descricao->SubString( 1, 38 ) + "  ]\x0A" );
        Texto->Add( "[  " + Descricao->SubString( 39, 38 ) + "  ]\x0A" );
      }
      else if( Descricao->Length( ) > 76 ) {
        while( Descricao->Length( ) <= 114 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( "[  " + Descricao->SubString( 1, 38 ) + "  ]\x0A" );
        Texto->Add( "[  " + Descricao->SubString( 39, 38 ) + "  ]\x0A" );
        Texto->Add( "[  " + Descricao->SubString( 77, 38 ) + "  ]\x0A" );
      }
      // texto c/ icms 2,15% - simples paulista
      // Texto->Add( *Qtd + ",000 x" + *PrecoUnit + *PrecoTot + "\xBET 2,15\x0A" );

      // texto isento icms - simples nacional
      Texto->Add( *Qtd + ",000 x" + *PrecoUnit + *PrecoTot + "\xBEI\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
  	    ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Item;
    delete Texto;
    delete PrecoTot;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::TotalizarCupom( String* &Retorno ) {

  TStringList *Texto;
  String *Total, *Item;
  int CodRetorno;

  try {
    *Retorno = "";
    Texto = new TStringList( );
    Texto->Sorted = false;
    Total = new AnsiString( );
    Item = new AnsiString( );

    try {
      if( this->ValorTotal == NULL ) {
        *Retorno = "É Preciso Lançar um Item antes de Totalizar Cupom !";
      }
      else {
        DecimalSeparator = ',';
        ThousandSeparator = '.';
        *Total = FormatFloat( "0.00", this->ValorTotal->ToDouble( ) );
        while( Total->Length( ) != 20 ) {
          *Total = " " + *Total;
        }
        *Item = *this->Itens;
        while( Item->Length( ) != 3 ) {
          *Item = "0" + *Item;
        }

        Texto->Add( "                    ---------------------\x0A" );
        Texto->Add( "\x1B\x57\x1     TOTAL\x1B\x57\x2" + *Total + "\x0A" );
        Texto->Add( "ITEM(S): " + *Item + "\x0A" );

        while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
          CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
          Sleep( 400 );
      	  ObterRetornoComando( CodRetorno, Retorno );
          Texto->Delete( 0 );
        }
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete Total;
    delete Item;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::Pagamento( String* FormaPagamento, String* Entrada,
  String* QtdParcela, String* Parcela, String* &Retorno ) {

  TStringList *Texto;
  String *ValorTotal;
  int CodRetorno;

  try {
    *Retorno = "";
    ValorTotal = new AnsiString( *this->ValorTotal );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      //Texto->Add( "PAGO EM:\x0A" );
      while( FormaPagamento->Length( ) <= 24 ) {
        *FormaPagamento = *FormaPagamento + " ";
      }
      while( ValorTotal->Length( ) <= 11 ) {
        *ValorTotal = " " + *ValorTotal;
      }
      Texto->Add( "   " + UpperCase( *FormaPagamento ) + *ValorTotal + "\x0A" );
      Texto->Add( "   VALOR RECEBIDO           " + *ValorTotal + "\x0A" );
      if( Entrada != NULL || Parcela != NULL ) {
        Texto->Add( "   ENTRADA:R$" + *Entrada + " " + *QtdParcela + " PARCELA DE:R$" + *Parcela + "\x0A" );
      }
      Texto->Add( "\x1B\x57\x1 TROCO\x1B\x57\x2                        0,00\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
    	  ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete ValorTotal;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::FecharCupom( String* Vendedor, String* Cliente, String* Telefone,
  String* &Retorno ) {

  TStringList *Texto;
  int CodRetorno;

  try {
    *Retorno = "";
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      Texto->Add( "Vendedor: " + *Vendedor + "\x0A\x0A" );
      if( *FilmeRebobinado ) {
        Texto->Add( "\x0AOBS: A Garantia dos Filmes Rebobinados NAO cobre qualquer DANO MORAL ou MATERIAL. Implica apenas na troca do mesmo.\x0A\x0A" );
      }
      Texto->Add( "  A Consigo Agradece a sua Visita e Boas Fotos! \x0A" );
      Texto->Add( "      CONSIGO - A CERTEZA DE UM BOM NEGOCIO    \x0A" );
      Texto->Add( "      TEL: (11)3214-2660  FAX: (11)3214-5896    \x0A\x0A" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "      GNF:0037   ECF:000001\x0A" );
      Texto->Add( "PROCOMP   - ECF2011             Ver.:FCP-500\x0A" );
      Texto->Add( "$)#+=*#&+++=&@$)@!#         FAB:0000004889\x1B\x4A\x1 BR\x1B\x4A\x2 \x0A\x0A" );
      /*
      if( StringReplace( *this->ValorTotal, ".", "", TReplaceFlags( ) << rfReplaceAll << rfIgnoreCase ).ToDouble( ) < 100 ) {
        Texto->Add( "................................................\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
      }
      else {
      */
        Texto->Add( "................................................\x0A" );
        Texto->Add( "    Visite Nosso Salao de Exposicao Consigo!   \x0A" );
        Texto->Add( "\x0A" );
        if( ( Cliente->IsEmpty( ) ) || ( Telefone->IsEmpty( ) ) ) {
          Texto->Add( "Nome: _______________________________________\x0A" );
          Texto->Add( "\x0A" );
          Texto->Add( "Tel: ________________________________________\x0A" );
        }
        else {
          Texto->Add( "Nome: " + *Cliente + "\x0A" );
          Texto->Add( "\x0A" );
          Texto->Add( "Tel: " + *Telefone + "\x0A" );
        }
        Texto->Add( "Cupom Numero: " + *this->NumeroCupom + "\x0A" );
        Texto->Add( "................................................\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( "\x0A" );
      //}

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
  	    ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::AbrirCupomVinculado( String* &Retorno ) {

  int CodRetorno;
  String *Total;
  TStringList *Texto;

  try {
    *Retorno = "";
    Total = new AnsiString( );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      Texto->Add( "   CONSIGO COMERCIO DE CINE FOTO E SOM LTDA.\x0A" );
	    Texto->Add( "\x1B\x57\x1   CONSIGO SOM IMAGEM\x1B\x57\x2\x0A" );
 	    Texto->Add( "RUA CONSELHEIRO CRISPINIANO, 105 - 1 AND.SALA 13\x0A" );
     	Texto->Add( "    CENTRO - SAO PAULO - SP - CEP: 01037-001\x0A\x0A" );
      Texto->Add( "................................................\x0A" );
 		  Texto->Add( "CNPJ:59201327/0001-74        IE:  112061543114\x0A" );
  	  DateSeparator = '/';
      TimeSeparator = ':';
      // Implementar depois contador CVe
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "                COO:" + *this->NumeroCupom + "\x0A" );
      Texto->Add( "          COMPROVANTE NAO FISCAL - vinculado\x0A" );
      *Total = *this->ValorTotal;
      while( Total->Length( ) < 18 ) {
        *Total = " " + *Total;
      }
      Texto->Add( "Valor Cupom No:" + *this->NumeroCupom + " =" + *Total + "\x0A" );
      Texto->Add( "         NAO E DOCUMENTO FISCAL\x0A\x0A" );
      Texto->Add( "              Consigo Som Imagem\x0A" );
      Texto->Add( "       Rua Cons. Crispiniano,105 1and\x0A" );
      Texto->Add( "          CNPJ: 59.201.327/0001-74\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
  	    ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete Total;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::FecharCupomVinculado( String* &Retorno ) {

  TStringList *Texto;
  int CodRetorno;

  try {
    *Retorno = "";
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "      GNF:0037  ECF:000001\x0A" );
      Texto->Add( "PROCOMP   - ECF2011             Ver.:FCP-500\x0A" );
      Texto->Add( "$)#+=*#&+++=&@$)@!#         FAB:0000004889\x1B\x4A\x1 BR\x1B\x4A\x2 \x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "................................................\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
  	    ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::ImprimirTextoTEF( TStringList* Texto, String* &Retorno ) {

  int CodRetorno, i;
  String *Observacao;

  try {
    *Retorno = "";
    Observacao = new AnsiString( "   NAO E DOCUMENTO FISCAL\x0A" );

    try {
      i = 0;
      Texto->Add( "\x0A" );
      while( ( i < Texto->Count ) && ( Retorno->IsEmpty( ) ) ) {
        if( fmod( i + 1, 10 ) == 0 ) {
          CodRetorno = CPImprimeTexto( Observacao->c_str( ), Observacao->Length( ) );
          Sleep( 400 );
          ObterRetornoComando( CodRetorno, Retorno );
        }
        Texto->Strings[i] =  Texto->Strings[i] + "\x0A";
        CodRetorno = CPImprimeTexto( Texto->Strings[i].c_str( ), Texto->Strings[i].Length( ) );
        Sleep( 400 );
        ObterRetornoComando( CodRetorno, Retorno );
        i++;
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Observacao;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::AbrirOrcamentoConserto( String* &NumeroOrcamento, String* &Retorno ) {

  int CodRetorno;
  TStringList *Texto;

  try {

    try {
      *Retorno = "";
      while( NumeroOrcamento->Length( ) != 6 ) {
        *NumeroOrcamento = "0" + *NumeroOrcamento;
      }
      Texto = new TStringList( );
      Texto->Sorted = false;
      Texto->Add( "   CONSIGO COMERCIO DE CINE FOTO E SOM LTDA.\x0A" );
	    Texto->Add( "\x1B\x57\x1   CONSIGO SOM IMAGEM\x1B\x57\x2\x0A" );
 	    Texto->Add( "RUA CONSELHEIRO CRISPINIANO, 105 - 1 AND.SALA 13\x0A" );
     	Texto->Add( "    CENTRO - SAO PAULO - SP - CEP: 01037-001\x0A\x0A" );
      Texto->Add( "................................................\x0A" );
 		  Texto->Add( "CNPJ:59201327/0001-74        IE:  112061543114\x0A" );
  	  DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "                 COO:" + *NumeroOrcamento + "\x0A" );
      Texto->Add( "\x1B\x57\x1  ORCAMENTO / CONSERTO\x1B\x57\x2\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
    	  ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::LancarItemOrcamento( String* PrecoUnit, String* Codigo,
      String* Descricao, String* NumeroSerie, String* Defeito, String* &Retorno ) {

  String *Item;
  TStringList *Texto;
  int CodRetorno;

  try {
    *Retorno = "";
    Item = new AnsiString( );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      DecimalSeparator = ',';
      ThousandSeparator = '.';
      *PrecoUnit = StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll );
      if( Descricao->Length( ) > 114 ) {
        *Descricao = Descricao->Delete( 115, Descricao->Length( ) - 114 );
      }
      *this->Itens = *this->Itens + 1;
      *Item = *this->Itens;
      while( Item->Length( ) <= 2 ) {
        *Item = "0" + *Item;
      }
      if( *this->ValorTotal == "" ) {
        *this->ValorTotal = *PrecoUnit;
      }
      else {
        *this->ValorTotal = FormatFloat( "0.00", ( this->ValorTotal->ToDouble( ) + StringReplace( *PrecoUnit, ".", "", TReplaceFlags( ) << rfReplaceAll ).ToDouble( ) ) );
      }
      while( PrecoUnit->Length( ) <= 41 ) {
        *PrecoUnit = " " + *PrecoUnit;
      }

      Texto->Add( *Item + ")" + *Codigo  + "\x0A" );
      if( Descricao->Length( ) <= 38 ) {
        while( Descricao->Length( ) <= 38 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( "[  " + *Descricao + "  ]\x0A" );
      }
      else if( ( Descricao->Length( ) > 38 ) && ( Descricao->Length( ) <= 76 ) ) {
        while( Descricao->Length( ) <= 76 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( "[  " + Descricao->SubString( 1, 38 ) + "  ]\x0A" );
        Texto->Add( "[  " + Descricao->SubString( 39, 38 ) + "  ]\x0A" );
      }
      else if( Descricao->Length( ) > 76 ) {
        while( Descricao->Length( ) <= 114 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( "[  " + Descricao->SubString( 1, 38 ) + "  ]\x0A" );
        Texto->Add( "[  " + Descricao->SubString( 39, 38 ) + "  ]\x0A" );
        Texto->Add( "[  " + Descricao->SubString( 77, 38 ) + "  ]\x0A" );
      }
      Texto->Add( *PrecoUnit + "\x0A" );
      Texto->Add( "Numero Serie: " + *NumeroSerie + "\x0A" );
      Texto->Add( "Defeito/Obs:\x0A");
      *Defeito = StringReplace( *Defeito, "||", "\x0A", TReplaceFlags( ) << rfReplaceAll );
      do {
        if( Defeito->Length( ) > 42 ) {
          Texto->Add( " " + Defeito->SubString( 1, 42 ) + "\x0A" );
          Defeito->Delete( 1, 42 );
        }
        else {
          Texto->Add( " " + Defeito->SubString( 1, Defeito->Length( ) ) + "\x0A" );
        }
      } while( Defeito->Length( ) > 42 );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
  	    ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Item;
    delete Texto;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::TotalizarOrcamento( String* &Retorno ) {

  TStringList *Texto;
  String *Total, *Item;
  int CodRetorno;

  try {
    *Retorno = "";
    Texto = new TStringList( );
    Texto->Sorted = false;
    Total = new AnsiString( );
    Item = new AnsiString( );

    try {
      if( this->ValorTotal == NULL ) {
        *Retorno = "É Preciso Lançar um Item antes de Totalizar Cupom !";
      }
      else {
        DecimalSeparator = ',';
        ThousandSeparator = '.';
        *Total = FormatFloat( "0.00", this->ValorTotal->ToDouble( ) );
        while( Total->Length( ) != 20 ) {
          *Total = " " + *Total;
        }
        *Item = *this->Itens;
        while( Item->Length( ) != 3 ) {
          *Item = "0" + *Item;
        }

        Texto->Add( "                    ---------------------\x0A" );
        Texto->Add( "\x1B\x57\x1     TOTAL\x1B\x57\x2" + *Total + "\x0A" );
        Texto->Add( "ITEM(S): " + *Item + "\x0A" );

        while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
          CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
          Sleep( 400 );
      	  ObterRetornoComando( CodRetorno, Retorno );
          Texto->Delete( 0 );
        }
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete Total;
    delete Item;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::FecharOrcamento( String* Vendedor, String* Cliente, String* Telefone,
  String* &Retorno ) {

  TStringList *Texto;
  int CodRetorno;

  try {
    *Retorno = "";
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      Texto->Add( "Vendedor: " + *Vendedor + "\x0A" );
      Texto->Add( "Nome: " + *Cliente + "\x0A" );
      Texto->Add( "Tel: " + *Telefone + "\x0A\x0A" );
      Texto->Add( "        Concorra a um Colete Profissional!      \x0A" );
      Texto->Add( "      CONSIGO - A CERTEZA DE UM BOM NEGOCIO    \x0A" );
      Texto->Add( "      TEL: (11)3214-2660  FAX: (11)3214-5896    \x0A\x0A" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "      GNF:0037    ECF:000001\x0A" );
      Texto->Add( "PROCOMP   - ECF2011             Ver.:FCP-500\x0A" );
      Texto->Add( "$)#+=*#&+++=&@$)@!#         FAB:0000004889\x1B\x4A\x1 BR\x1B\x4A\x2 \x0A\x0A" );
      Texto->Add( "................................................\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
  	    ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::AbrirRecibo( String* &Retorno ) {

  int CodRetorno;
  TStringList *Texto;

  try {

    try {
      *Retorno = "";
      Texto = new TStringList( );
      Texto->Sorted = false;
      Texto->Add( "   CONSIGO COMERCIO DE CINE FOTO E SOM LTDA.\x0A" );
	    Texto->Add( "\x1B\x57\x1   CONSIGO SOM IMAGEM\x1B\x57\x2\x0A" );
 	    Texto->Add( "RUA CONSELHEIRO CRISPINIANO, 105 - 1 AND.SALA 13\x0A" );
     	Texto->Add( "    CENTRO - SAO PAULO - SP - CEP: 01037-001\x0A\x0A" );
      Texto->Add( "................................................\x0A" );
 		  Texto->Add( "CNPJ:59201327/0001-74        IE:  112061543114\x0A" );
  	  DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "\x0A" );
      Texto->Add( "\x1B\x57\x1          RECIBO\x1B\x57\x2\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
    	  ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::ImprimirRecibo( String* Vendedor, String* Cliente, String* Valor, String* Referente,
  String* &Retorno ) {

  int CodRetorno;
  TStringList *Texto;
  String *PrecoExtenso;

  try {

    try {
      *Retorno = "";
      Texto = new TStringList( );
      Texto->Sorted = false;
      PrecoExtenso = new AnsiString( );

      this->ValorExtenso( Valor, PrecoExtenso );
      Texto->Add( "          Recebemos de(a) " + UpperCase( *Cliente ) + " a quantia de R$ " + *Valor +
                  " ( " + *PrecoExtenso + " ), Referente a(o) " + *Referente + "\x0A\x0A\x0A" );
 	    Texto->Add( "               Sem mais,\x0A\x0A" );
     	Texto->Add( "               Atenciosamente\x0A\x0A" );
      Texto->Add( "               " + *Vendedor + "\x0A\x0A\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
    	  ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete PrecoExtenso;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::FecharRecibo( String* &Retorno ) {

  TStringList *Texto;
  int CodRetorno;

  try {
    *Retorno = "";
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      Texto->Add( "      CONSIGO - A CERTEZA DE UM BOM NEGOCIO    \x0A" );
      Texto->Add( "      TEL: (11)3214-2660  FAX: (11)3214-5896    \x0A\x0A" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "      GNF:0037   ECF:000001\x0A" );
      Texto->Add( "PROCOMP   - ECF2011             Ver.:FCP-500\x0A" );
      Texto->Add( "$)#+=*#&+++=&@$)@!#         FAB:0000004889\x1B\x4A\x1 BR\x1B\x4A\x2 \x0A\x0A" );
      Texto->Add( "................................................\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        CodRetorno = CPImprimeTexto( Texto->Strings[0].c_str( ), Texto->Strings[0].Length( ) );
        Sleep( 400 );
  	    ObterRetornoComando( CodRetorno, Retorno );
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::ObterStatus( String* &Retorno ) {

  int CodRetorno;

  try {
    *Retorno = "";
    CodRetorno = CPStatusImpressora( );
    Sleep( 500 );
    if( CodRetorno != 1 ) {
  	  if( CodRetorno == 0 ) {
    	  *Retorno = "A Impressora Pode estar Desligada, com o Cabo de Comunicação Desconectado ou com Alguns dos Sinais da Interface Inoperante.";
      }
    	else if( CodRetorno == 2 ) {
      	*Retorno = "A Impressora Ocupada ou Buffer de Recepção Está Cheio!";
      }
    	else if( CodRetorno == 3 ) {
      	*Retorno = "A Impressora Está sem Papel!\r\rColoque uma Nova Bobina e Refaça a Operação.";
      }
    	else if( CodRetorno == 4 ) {
      	*Retorno = "Ocorreu um Erro no Funcionamento da Impressora!";
      }
      else {
        *Retorno = "Erro Desconhecido !";
      }
	  	if( iHandleDllMecaf != 0 ) {
  	  	FreeLibrary( iHandleDllMecaf );
    	}
    }
  }
  catch( String &Error ) {
    *Retorno = Error;
  }
}
//------------------------------------------------------------------------------
void TImpressoraMecaf::ObterRetornoComando( int CodRetorno, String* &Retorno ) {

  *Retorno = "";
  if( CodRetorno != 0 ) {
  	if( CodRetorno == 1 ) {
    	*Retorno = "Função da Impressora Ainda em Execução!";
    }
    else if( CodRetorno == 2 ) {
    	*Retorno = "Uma Outra Função da Impressora está sendo Executada!";
    }
    else if( CodRetorno == 3 ) {
    	*Retorno = "A Função da Impressora foi Cancelada!";
    }
    else if( CodRetorno == 4 ) {
    	*Retorno = "A Impressora não está Pronta para Uso!";
    }
    else if( CodRetorno == 5 ) {
    	*Retorno = "A Impressora Não foi Iniciada!";
    }
    else if( CodRetorno == 6 ) {
    	*Retorno = "Não há Comando em Execução!";
    }
    else if( CodRetorno == 7 ) {
    	*Retorno = "A Função da Impressora Não foi Iniciada!";
    }
    else if( CodRetorno == 8 ) {
    	*Retorno = "A Impressora Não foi Encontrada!";
    }
    else if( CodRetorno == 9 ) {
    	*Retorno = "Time Out de Validação de Documento!";
    }
    else if( CodRetorno == 10 ) {
    	*Retorno = "Impressora sem Papel!\r\rColoque uma Nova Bobina e Refaça a Operação.";
    }
    else if( CodRetorno == 50 ) {
    	*Retorno = "Ocorreu um Erro na Execução da Função!";
    }
    else if( CodRetorno == 51 ) {
    	*Retorno = "Ocorreu um Erro na Alocação de Recurso do Windows!";
    }
    else if( CodRetorno == 52 ) {
    	*Retorno = "Parâmetro da Função da Impressora Inválido!";
    }
    else if( CodRetorno == 53 ) {
    	*Retorno = "Erro no Arquivo de Configuração: MECAF.INI!";
    }
    else if( CodRetorno == 54 ) {
    	*Retorno = "Time Out de Execução da Função!";
    }
    else if( CodRetorno == 55 ) {
    	*Retorno = "Erro de Comunicação com a Impressora!";
    }
    else {
      *Retorno = "Erro Desconhecido !";
    }
		if( iHandleDllMecaf != 0 ) {
  		FreeLibrary( iHandleDllMecaf );
	  }
  }
}
//-----------------------------------------------------------------------------
void TImpressoraMecaf::ValorExtenso( String* Preco, String* ValorExtenso ) {

  TDinheiroTexto *ConversorDinheiroTexto;

  try {
    ConversorDinheiroTexto = new TDinheiroTexto( );

    ConversorDinheiroTexto->ConverterDinheiroTexto( Preco, ValorExtenso );
  }
  __finally {
    delete ConversorDinheiroTexto;
  }

}
//-----------------------------------------------------------------------------

