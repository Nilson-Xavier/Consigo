//---------------------------------------------------------------------------
#pragma hdrstop

#include "ImpressoraBematech.h"
#include <math.h>
#include <math.hpp>
#include <vcl\StrUtils.hpp>
#include <vcl\SysUtils.hpp>
//------------------------------------------------------------------------------
#pragma package(smart_init)
//------------------------------------------------------------------------------
__fastcall TImpressoraBematech::TImpressoraBematech( ) {

  this->ValorTotal = new AnsiString( );
  this->Itens = new int( );
  this->FilmeRebobinado = new bool( false );
  this->NumeroCupom = new AnsiString( );
}
//------------------------------------------------------------------------------
__fastcall TImpressoraBematech::~TImpressoraBematech( ) {

  delete this->ValorTotal;
  delete this->Itens;
  delete this->FilmeRebobinado;
  delete this->NumeroCupom;
}
//------------------------------------------------------------------------------
void TImpressoraBematech::Iniciar( String* Retorno ) {

  String *Porta;

  try {
    Porta = new AnsiString( "LPT1" );

    try {
      FechaPorta( );
      if( ConfiguraModeloImpressora( 0 ) != 1 ) {
        throw( "" );
      }
//    ConfiguraTaxaSerial( 115200 );
      if( IniciaPorta( Porta->c_str( ) ) != 1 ) {
        throw( "" );
      }
      if( HabilitaEsperaImpressao( 1 ) != 1 ) {
        throw( "" );
      }
      if( AjustaLarguraPapel ( 80 ) != 1 ) {
        throw( "" );
      }

      /*
      if( SelecionaQualidadeImpressao( 2 ) != 1 ) {
        throw( "" );
      }
      if( HabilitaExtratoLongo( 1 ) != 1 ) {
        throw( "" );
      }
      if( ConfiguraTamanhoExtrato( 90 ) != 1 ) {
        throw( "" );
      }
      if( HabilitaPresenterRetratil( 1 ) != 1 ) {
        throw( "" );
      }
      if( VerificaPapelPresenter( ) != 1 ) {
        throw( "" );
      }
      */
    }
    catch( ... ) {
      *Retorno = "Erro na Impressora !!!";
    }
  }
  __finally {
    delete Porta;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::Finalizar( ) {

  FechaPorta( );

}
//------------------------------------------------------------------------------
void TImpressoraBematech::AbrirCupom( String* Cupom, String *CpfCnpj, String* Retorno ) {

  int i;
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

      Texto->Add( "      CONSIGO COM. DE CINE FOTO E SOM LTDA" );
      if( !FormataTX( Texto->Text.c_str( ), 3, 0, 0, 0, 1 ) ) {
        throw( "" );
      }
      Sleep( 700 );

      Texto->Clear( );

      Texto->Add( "    Rua Conselheiro Crispiniano, 105 1 andar" );
      Texto->Add( "  CEP:01037001 Tel:(11)3214-2660 São Paulo - SP" );
      Texto->Add( " CNPJ:59.201.327/0001-74" );
      Texto->Add( " IE:112.061.543.114" );
      Texto->Add( " IM:9.532.153-5" );
      Texto->Add( " -------------------------------------------------" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( " " + Date( ).FormatString( "dd/mm/yyyy" ) + " " + Time( ).FormatString( "hh:mm:ss" ) + "   CCF:" + *this->NumeroCupom + "       " + "COO:" + *this->NumeroCupom );
      if( !CpfCnpj->IsEmpty( ) ) {
        for( i = 1; i <= CpfCnpj->Length( ); i++ ) {
          if( ( ( AnsiCompareStr( CpfCnpj->SubString( i, 1 ), "0" ) >= 0 ) && ( AnsiCompareStr( CpfCnpj->SubString( i, 1 ), "9" ) <= 0 ) ) ) {
            *CpfCnpjFmt = *CpfCnpjFmt + CpfCnpj->SubString( i, 1 );
          }
        }
        *CpfCnpjFmt = LeftStr( *CpfCnpjFmt, 14 );
        Texto->Add( " CNPJ/CPF consumidor:" + LeftStr( *CpfCnpjFmt, 28 ) );
      }
      if( !FormataTX( Texto->Text.c_str( ), 3, 0, 0, 0, 0 ) ) {
        throw( "" );
      }
      Sleep( 700 );
      
      Texto->Clear( );

      Texto->Add( "       CUPOM FISCAL" );
      if( !FormataTX( Texto->Text.c_str( ), 3, 0, 0, 1, 1 ) ) {
        throw( "" );
      }
      Sleep( 700 );
      
      Texto->Clear( );

      Texto->Add( " ITEM   CÓDIGO             DESCRIÇÃO" );
      Texto->Add( " QTD UN. VL UNIT( R$)      ST         VL ITEM( R$)" );
      Texto->Add( " -------------------------------------------------" );
      if( !FormataTX( Texto->Text.c_str( ), 3, 0, 0, 0, 0 ) ) {
        throw( "" );
      }
      Sleep( 700 );
    }
    catch( ... ) {
      *Retorno = "Erro na Impressora !!!";
    }
  }
  __finally {
    delete Texto;
    delete CpfCnpjFmt;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::LancarItem( String* Qtd, String* PrecoUnit, String* Codigo,
      String* Descricao, String* Retorno ) {

  String *Item, *PrecoTot;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;
  TStringList *Texto;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
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

      if( Descricao->Length( ) > 127 ) {
        *Descricao = Descricao->SubString( 1, 127 );
        //*Descricao = Descricao->Delete( 115, Descricao->Length( ) - 114 );
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

      while( Qtd->Length( ) <= 8 ) {
        *Qtd = " " + *Qtd;
      }

      while( PrecoUnit->Length( ) <= 10 ) {
        *PrecoUnit = *PrecoUnit + " ";
      }
      while( PrecoTot->Length( ) <= 13 ) {
        *PrecoTot = " " + *PrecoTot;
      }

      if( Descricao->Pos( "Rebobinado" ) != 0 ) {
        *FilmeRebobinado = true;
      }

      if( Descricao->Length( ) <= 29 ) {
        while( Descricao->Length( ) <= 29 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( " " + *Item + " " + *Codigo + *Descricao + "\x0A" );
      }
      else if( ( Descricao->Length( ) > 29 ) && ( Descricao->Length( ) <= 79 ) ) {
        while( Descricao->Length( ) <= 79 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( " " + *Item + " " + *Codigo + Descricao->SubString( 1, 29 ) + "\x0A" );
        Texto->Add( " " + Descricao->SubString( 30, 79 ) + "\x0A" );
      }
      else if( Descricao->Length( ) > 80 ) {
        while( Descricao->Length( ) <= 128 ) {
          *Descricao = *Descricao + " ";
        }
        Texto->Add( " " + *Item + " " + *Codigo + Descricao->SubString( 1, 29 ) + "\x0A" );
        Texto->Add( " " + Descricao->SubString( 30, 79 ) + "\x0A" );
        Texto->Add( " " + Descricao->SubString( 80, 128 ) + "\x0A" );
      }

      // texto c/ icms 2,15% - simples paulista
      // Texto->Add( *Qtd + ",000 x" + *PrecoUnit + *PrecoTot + "\xBET 2,15\x0A" );

      // texto isento icms - simples nacional

      Texto->Add( *Qtd + "UN X "  + *PrecoUnit + "01T18,00%" + *PrecoTot + "\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
    	    *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
    	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
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
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::TotalizarCupom( String* Retorno ) {

  TStringList *Texto;
  String *Total;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
    Texto = new TStringList( );
    Texto->Sorted = false;
    Total = new AnsiString( );

    try {
      if( this->ValorTotal == NULL ) {
        *Retorno = "É Preciso Lançar um Item antes de Totalizar Cupom !";
      }
      else {
        DecimalSeparator = ',';
        ThousandSeparator = '.';

        *Total = FormatFloat( "0.00", this->ValorTotal->ToDouble( ) );
        while( Total->Length( ) != 38 ) {
          *Total = " " + *Total;
        }

        Texto->Add( "                              -------------------\x0A" );
        Texto->Add( " TOTAL  R$" + *Total + "\x0A" );

        while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
          if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
      	    *Retorno = "Erro na Impressora !!!";
          }
*/
          if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
          }
          Sleep( 700 );
          
          Texto->Delete( 0 );

        }
        *this->Total = "";
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete Total;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::Pagamento( String* FormaPagamento, String* Entrada,
  String* QtdParcela, String* Parcela, String* Retorno ) {

  TStringList *Texto;
  String *ValorTotal;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
    ValorTotal = new AnsiString( *this->ValorTotal );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      //Texto->Add( "PAGO EM:\x0A" );
      while( FormaPagamento->Length( ) <= 24 ) {
        *FormaPagamento = *FormaPagamento + " ";
      }
      while( ValorTotal->Length( ) <= 21 ) {
        *ValorTotal = " " + *ValorTotal;
      }

      Texto->Add( " " + *FormaPagamento + *ValorTotal + "\x0A" );
      if( Entrada != NULL || Parcela != NULL ) {
        Texto->Add( " ENTRADA: R$" + *Entrada + " " + *QtdParcela + "X PARCELA DE: R$" + *Parcela + "\x0A" );
      }
      Texto->Add( " T1=01T18,00%\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
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
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::FecharCupom( String* Vendedor, String* Cliente, String* Telefone,
  String* Retorno ) {

  TStringList *Texto;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito, *CodigoAleatorio;
  int i;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
    CodigoAleatorio = new AnsiString( );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      Texto->Add( " Vendedor: " + *Vendedor + "\x0A\x0A" );
      if( *FilmeRebobinado ) {
        Texto->Add( "\x0A OBS: A Garantia dos Filmes Rebobinados NAO cobre qualquer DANO MORAL ou MATERIAL. Implica apenas na troca do mesmo.\x0A\x0A" );
      }
      Texto->Add( "  A Consigo Agradece a sua Visita e Boas Fotos! \x0A" );
      Texto->Add( "     Visite Nosso Salao de Exposicao Consigo! \x0A" );
      Texto->Add( "      CONSIGO - A CERTEZA DE UM BOM NEGOCIO    \x0A" );
      Texto->Add( "      TEL: (11)3214-2660  FAX: (11)3214-5896    \x0A\x0A" );
      Texto->Add( " -------------------------------------------------\x0A" );

      for( i =1 ; i <= 45; i++ ) {
        //*CodigoAleatorio = *CodigoAleatorio + IntToStr( RandomRange( 33, 126 ) );
        *CodigoAleatorio = *CodigoAleatorio + (char) RandomRange( 33, 126 );
      }
      *CodigoAleatorio = CodigoAleatorio->UpperCase( );

      Texto->Add( " " + CodigoAleatorio->SubString( 1, 8 ) + " " + CodigoAleatorio->SubString( 9, 8 ) + " " + CodigoAleatorio->SubString( 17, 8 ) + " " + CodigoAleatorio->SubString( 25, 8 ) + " " + CodigoAleatorio->SubString( 33, 12 ) +  "\x0A" );

      Texto->Add( " BEMATECH MP-4000 TH FI ECF-IF\x0A" );
      Texto->Add( " VERSAO:01.00.01 ECF:002 LJ:0001\x0A" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( " QQQQQQQQQWREOQQURO " + DateToStr( Date( ) ) + " " + Time( ).FormatString( "hh:mm:ss" ) + "\x0A" );

       while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
        Texto->Delete( 0 );
      }

      Texto->Add( " FAB:BE090810100010100067                       BR" );
      if( !FormataTX( Texto->Text.c_str( ), 3, 0, 0, 0, 1 ) ) {
        throw( "" );
      }
      Sleep( 700 );
      
      Texto->Clear( );

      Texto->Add( " -------------------------------------------------\x0A\x0A" );
      if( ( Cliente->IsEmpty( ) ) || ( Telefone->IsEmpty( ) ) ) {
        Texto->Add( " Nome: _________________________________________\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( " Tel:  _________________________________________\x0A" );
      }
      else {
        Texto->Add( " Nome: " + *Cliente + "\x0A" );
        Texto->Add( "\x0A" );
        Texto->Add( " Tel: " + *Telefone + "\x0A" );
      }
      Texto->Add( " Cupom Numero: " + *this->NumeroCupom + "\x0A" );
      Texto->Add( " -------------------------------------------------\x0A" );
      Texto->Add( "\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
        Texto->Delete( 0 );
      }

      // para impressao da 2 via do cf devemos zerar o contador de itens
      *this->Itens = 0;

      if( !AcionaGuilhotina( 1 ) ) {
        *Retorno = "Erro na Impressora !!!";
      }
      Sleep( 700 );
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
    delete CodigoAleatorio;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::AbrirCupomVinculado( String* Retorno ) {

  String *Total;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;
  TStringList *Texto;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
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
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
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
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::ImprimirTextoTEF( TStringList* Texto, String* Retorno ) {

  int i;
  String *Observacao;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
    Observacao = new AnsiString( "   NAO E DOCUMENTO FISCAL\x0A" );

    try {
      i = 0;
      Texto->Add( "\x0A" );
      while( ( i < Texto->Count ) && ( Retorno->IsEmpty( ) ) ) {
        if( fmod( i + 1, 10 ) == 0 ) {
/*
          if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
            *Retorno = "Erro na Impressora !!!";
          }
*/
          if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
          }
          Sleep( 700 );
        }
        Texto->Strings[i] =  Texto->Strings[i] + "\x0A";
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
        i++;
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Observacao;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::FecharCupomVinculado( String* Retorno ) {

  TStringList *Texto;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
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
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/

        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::AbrirOrcamentoConserto( String* &NumeroOrcamento, String* Retorno ) {

  TStringList *Texto;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {

    try {
      *Retorno = "";
      TipoLetra = new AnsiString( "0" );
      Italico = new AnsiString( "0" );
      Sublinhado = new AnsiString( "0" );
      Expandido = new AnsiString( "0" );
      Negrito = new AnsiString( "0" );

      while( NumeroOrcamento->Length( ) != 6 ) {
        *NumeroOrcamento = "0" + *NumeroOrcamento;
      }
      Texto = new TStringList( );
      Texto->Sorted = false;

      Texto->Add( "      CONSIGO COM. DE CINE FOTO E SOM LTDA" );
      if( !FormataTX( Texto->Text.c_str( ), 3, 0, 0, 0, 1 ) ) {
        throw( "" );
      }
      Sleep( 700 );
      
      Texto->Clear( );

      Texto->Add( "    Rua Conselheiro Crispiniano, 105 1 andar\x0A" );
      Texto->Add( "  CEP:01037001 Tel:(11)3214-2660 São Paulo - SP\x0A" );
      Texto->Add( " CNPJ:59.201.327/0001-74\x0A" );
      Texto->Add( " IE:112.061.543.114\x0A" );
      Texto->Add( " IM:9.532.153-5\x0A" );
      Texto->Add( " -------------------------------------------------\x0A" );

      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( DateToStr( Date( ) ) + "   " + Time( ).FormatString( "hh:mm:ss" ) + "                 COO:" + *NumeroOrcamento + "\x0A" );
      Texto->Add( "\x1B\x57\x1  ORCAMENTO / CONSERTO\x1B\x57\x2\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/

        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );

        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::LancarItemOrcamento( String* PrecoUnit, String* Codigo,
      String* Descricao, String* NumeroSerie, String* Defeito, String* Retorno ) {

  String *Item;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;
  TStringList *Texto;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
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
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/

        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 1000 );
        
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
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::TotalizarOrcamento( String* Retorno ) {

  TStringList *Texto;
  String *Total, *Item;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
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
/*
          if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
            *Retorno = "Erro na Impressora !!!";
          }
*/
          if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
          }
          Sleep( 700 );
          
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
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::FecharOrcamento( String* Vendedor, String* Cliente, String* Telefone,
  String* Retorno ) {

  TStringList *Texto;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito, *CodigoAleatorio;
  int i;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
    CodigoAleatorio = new AnsiString( );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      Texto->Add( "Vendedor: " + *Vendedor + "\x0A" );
      Texto->Add( "Nome: " + *Cliente + "\x0A" );
      Texto->Add( "Tel: " + *Telefone + "\x0A\x0A" );

      Texto->Add( "  A Consigo Agradece a sua Visita e Boas Fotos! \x0A" );
      Texto->Add( "     Visite Nosso Salao de Exposicao Consigo! \x0A" );
      Texto->Add( "      CONSIGO - A CERTEZA DE UM BOM NEGOCIO    \x0A" );
      Texto->Add( "      TEL: (11)3214-2660  FAX: (11)3214-5896    \x0A\x0A" );
      Texto->Add( " -------------------------------------------------\x0A" );

      for( i =1 ; i <= 45; i++ ) {
        //*CodigoAleatorio = *CodigoAleatorio + IntToStr( RandomRange( 33, 126 ) );
        *CodigoAleatorio = *CodigoAleatorio + (char) RandomRange( 33, 126 );
      }
      *CodigoAleatorio = CodigoAleatorio->UpperCase( );

      Texto->Add( " " + CodigoAleatorio->SubString( 1, 8 ) + " " + CodigoAleatorio->SubString( 9, 8 ) + " " + CodigoAleatorio->SubString( 17, 8 ) + " " + CodigoAleatorio->SubString( 25, 8 ) + " " + CodigoAleatorio->SubString( 33, 12 ) +  "\x0A" );

      Texto->Add( " BEMATECH MP-4000 TH FI ECF-IF\x0A" );
      Texto->Add( " VERSAO:01.00.01 ECF:002 LJ:0001\x0A" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( " QQQQQQQQQWREOQQURO " + DateToStr( Date( ) ) + " " + Time( ).FormatString( "hh:mm:ss" ) + "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );
      Texto->Add( "\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
        Texto->Delete( 0 );
      }

      // para impressao da 2 via do cf devemos zerar o contador de itens
      *this->Itens = 0;

      if( !AcionaGuilhotina( 1 ) ) {
        *Retorno = "Erro na Impressora !!!";
      }
      Sleep( 700 );
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
    delete CodigoAleatorio;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::AbrirRecibo( String* Retorno ) {

  TStringList *Texto;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {

    try {
      *Retorno = "";
      TipoLetra = new AnsiString( "0" );
      Italico = new AnsiString( "0" );
      Sublinhado = new AnsiString( "0" );
      Expandido = new AnsiString( "0" );
      Negrito = new AnsiString( "0" );
      Texto = new TStringList( );
      Texto->Sorted = false;

      Texto->Add( "      CONSIGO COM. DE CINE FOTO E SOM LTDA" );
      if( !FormataTX( Texto->Text.c_str( ), 3, 0, 0, 0, 1 ) ) {
        throw( "" );
      }
      Sleep( 700 );
      
      Texto->Clear( );

      Texto->Add( "    Rua Conselheiro Crispiniano, 105 1 andar\x0A" );
      Texto->Add( "  CEP:01037001 Tel:(11)3214-2660 São Paulo - SP\x0A" );
      Texto->Add( " CNPJ:59.201.327/0001-74\x0A" );
      Texto->Add( " IE:112.061.543.114\x0A" );
      Texto->Add( " IM:9.532.153-5\x0A" );
      Texto->Add( " -------------------------------------------------\x0A" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( " " + Date( ).FormatString( "dd/mm/yyyy" ) + " " + Time( ).FormatString( "hh:mm:ss" ) + "\x0A" );
      Texto->Add( "\x1B\x57\x1          RECIBO\x1B\x57\x2\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
        Texto->Delete( 0 );
      }
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::ImprimirRecibo( String* Vendedor, String* Cliente, String* Valor, String* Referente,
  String* Retorno ) {

  TStringList *Texto;
  String *PrecoExtenso;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito;

  try {

    try {
      *Retorno = "";
      TipoLetra = new AnsiString( "0" );
      Italico = new AnsiString( "0" );
      Sublinhado = new AnsiString( "0" );
      Expandido = new AnsiString( "0" );
      Negrito = new AnsiString( "0" );
      Texto = new TStringList( );
      Texto->Sorted = false;
      PrecoExtenso = new AnsiString( );

//      this->ValorExtenso( Valor, PrecoExtenso );
/*
      Texto->Add( "          Recebemos de(a) " + UpperCase( *Cliente ) + " a quantia de R$ " + *Valor +
                  " ( " + *PrecoExtenso + " ), Referente a(o) " + *Referente + "\x0A\x0A\x0A" );
      Texto->Add( "               Sem mais,\x0A\x0A" );
      Texto->Add( "               Atenciosamente\x0A\x0A" );
      Texto->Add( "               " + *Vendedor + "\x0A\x0A\x0A\x0A" );
*/
      Texto->Add( "          Recebemos de(a) " + UpperCase( *Cliente ) + " a quantia de R$ " + *Valor +
                  ", Referente a(o) " + *Referente + "\x0A\x0A\x0A" );
      Texto->Add( "               Sem mais,\x0A\x0A" );
      Texto->Add( "               Atenciosamente\x0A\x0A" );
      Texto->Add( "               " + *Vendedor + "\x0A\x0A\x0A\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 1000 );
        
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
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
  }
}
//------------------------------------------------------------------------------
void TImpressoraBematech::FecharRecibo( String* Retorno ) {

  TStringList *Texto;
  String *TipoLetra, *Italico, *Sublinhado, *Expandido, *Negrito, *CodigoAleatorio;
  int i;

  try {
    *Retorno = "";
    TipoLetra = new AnsiString( "0" );
    Italico = new AnsiString( "0" );
    Sublinhado = new AnsiString( "0" );
    Expandido = new AnsiString( "0" );
    Negrito = new AnsiString( "0" );
    CodigoAleatorio = new AnsiString( );
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      Texto->Add( "  A Consigo Agradece a sua Visita e Boas Fotos! \x0A" );
      Texto->Add( "     Visite Nosso Salao de Exposicao Consigo! \x0A" );
      Texto->Add( "      CONSIGO - A CERTEZA DE UM BOM NEGOCIO    \x0A" );
      Texto->Add( "      TEL: (11)3214-2660  FAX: (11)3214-5896    \x0A\x0A" );
      Texto->Add( " -------------------------------------------------\x0A" );

      for( i =1 ; i <= 45; i++ ) {
        //*CodigoAleatorio = *CodigoAleatorio + IntToStr( RandomRange( 33, 126 ) );
        *CodigoAleatorio = *CodigoAleatorio + (char) RandomRange( 33, 126 );
      }
      *CodigoAleatorio = CodigoAleatorio->UpperCase( );

      Texto->Add( " " + CodigoAleatorio->SubString( 1, 8 ) + " " + CodigoAleatorio->SubString( 9, 8 ) + " " + CodigoAleatorio->SubString( 17, 8 ) + " " + CodigoAleatorio->SubString( 25, 8 ) + " " + CodigoAleatorio->SubString( 33, 12 ) +  "\x0A" );

      Texto->Add( " BEMATECH MP-4000 TH FI ECF-IF\x0A" );
      Texto->Add( " VERSAO:01.00.01 ECF:002 LJ:0001\x0A" );
      DateSeparator = '/';
      TimeSeparator = ':';
      Texto->Add( " QQQQQQQQQWREOQQURO " + DateToStr( Date( ) ) + " " + Time( ).FormatString( "hh:mm:ss" ) + "\x0A" );
      Texto->Add( "\x0A" );

      while( ( Texto->Count > 0 ) && ( Retorno->IsEmpty( ) ) ) {
/*
        if( !FormataTX( Texto->Strings[0].c_str( ), TipoLetra->c_str( ), Italico->c_str( ), Sublinhado->c_str( ), Expandido->c_str( ), Negrito->c_str( ) ) ) {
          *Retorno = "Erro na Impressora !!!";
        }
*/
        if( !FormataTX( Texto->Strings[0].c_str( ), 3, 0, 0, 0, 0 ) ) {
      	    *Retorno = "Erro na Impressora !!!";
        }
        Sleep( 700 );
        
        Texto->Delete( 0 );
      }

      if( !AcionaGuilhotina( 1 ) ) {
        *Retorno = "Erro na Impressora !!!";
      }
      Sleep( 700 );     
    }
    catch( String &Error ) {
      *Retorno = Error;
    }
  }
  __finally {
    delete Texto;
    delete TipoLetra;
    delete Italico;
    delete Sublinhado;
    delete Expandido;
    delete Negrito;
    delete CodigoAleatorio;
  }
}
//------------------------------------------------------------------------------
