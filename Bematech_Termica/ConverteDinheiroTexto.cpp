//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ConverteDinheiroTexto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

String TValorUnidade::ConverterUnidadeTexto( String* Unidade ) {

  int Opcao = Unidade->ToInt( );

  switch( Opcao ) {
    case 1: return( "Um" );
    case 2: return( "Dois" );
    case 3: return( "Tres" );
    case 4: return( "Quatro" );
    case 5: return( "Cinco" );
    case 6: return( "Seis" );
    case 7: return( "Sete" );
    case 8: return( "Oito" );
    case 9: return( "Nove" );
  }
}
//---------------------------------------------------------------------------
String TValorDezena::ConverterDezenaTexto( String* Dezena ) {

  int Opcao = Dezena->ToInt( );

  switch( Opcao ) {
    case 10: return( "Dez" );
    case 11: return( "Onze" );
    case 12: return( "Doze" );
    case 13: return( "Treze" );
    case 14: return( "Quatorze" );
    case 15: return( "Quinze" );
    case 16: return( "Dezesseis" );
    case 17: return( "Dezessete" );
    case 18: return( "Dezoito" );
    case 19: return( "Dezenove" );
    case 2: return( "Vinte" );
    case 3: return( "Trinta" );
    case 4: return( "Quarenta" );
    case 5: return( "Cinquenta" );
    case 6: return( "Sessenta" );
    case 7: return( "Setenta" );
    case 8: return( "Oitenta" );
    case 9: return( "Noventa" );
  }
}
//---------------------------------------------------------------------------
String TValorCentena::ConverterCentenaTexto( String* Centena ) {

  int Opcao = Centena->ToInt( );

  switch( Opcao ) {
    case 1: return( "Cento" );
    case 100: return( "Cem" );
    case 2: return( "Duzentos" );
    case 3: return( "Trezentos" );
    case 4: return( "Quatrocentos" );
    case 5: return( "Quinhentos" );
    case 6: return( "Seiscentos" );
    case 7: return( "Setecentos" );
    case 8: return( "Oitocentos" );
    case 9: return( "Novecentos" );
  }
}
//---------------------------------------------------------------------------
__fastcall TDinheiroTexto::TDinheiroTexto( void ) {

  Unidade = new TValorUnidade( );
  Dezena = new TValorDezena( );
  Centena = new TValorCentena( );
}
//---------------------------------------------------------------------------
__fastcall TDinheiroTexto::~TDinheiroTexto( void ) {

  delete Unidade;
  delete Dezena;
  delete Centena;
}
//---------------------------------------------------------------------------
void TDinheiroTexto::ConverterDinheiroTexto( String* Valor, String* ValorExtenso ) {

  int i;

    try {
      if( ( Valor->Length( ) < 4 ) || ( Valor->Length( ) > 11 ) ) {
        throw( "Valor Inválido para Conversão !!!" );
      }
      Valor->Delete( Valor->Pos( "." ), 1 );
      Valor->Delete( Valor->Pos( "," ), 1 );
      i = 1;
      for( i; i <= Valor->Length( ); i++ ) {
        switch( i ) {
          case 1:
            if( ( Valor->SubString( Valor->Length( ) - 1, 1 ) != "1" ) && ( Valor->SubString( Valor->Length( ), 1 ) != "0" ) ) {
              *ValorExtenso = Unidade->ConverterUnidadeTexto( &(Valor->SubString( Valor->Length( ), 1 )) ) + " Centavo(s)";
            }
            break;
          case 2:
            if( Valor->SubString( Valor->Length( ) - 1, 1 ) == "1" ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 1, 2 )) ) + " Centavo(s)";
            }
            else if( ( Valor->SubString( Valor->Length( ) - 1, 1 ) != "0" ) && ( Valor->SubString( Valor->Length( ), 1 ) == "0" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 1, 1 )) ) + " Centavo(s)";
            }
            else if( Valor->SubString( Valor->Length( ) - 1, 1 ) != "0" ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 1, 1 )) ) + " e " + *ValorExtenso;
            }
            break;
          case 3:
            if( Valor->SubString( Valor->Length( ) - 3, 1 ) == "1" ) {
              break;
            }
            else {
              if( ( Valor->SubString( Valor->Length( ) - 2, 1 ) != "0" ) && ( Valor->SubString( Valor->Length( ) - 1, 1 ) == "0" ) && ( Valor->SubString( Valor->Length( ), 1 ) == "0" ) ) {
                *ValorExtenso = Unidade->ConverterUnidadeTexto( &(Valor->SubString( Valor->Length( ) - 2, 1 )) ) + " Real(is)";
              }
              else if( ( Valor->SubString( Valor->Length( ) - 2, 1 ) != "0" ) && ( ( Valor->SubString( Valor->Length( ) - 1, 1 ) != "0" ) || ( Valor->SubString( Valor->Length( ), 1 ) != "0" ) ) ) {
                *ValorExtenso = Unidade->ConverterUnidadeTexto( &(Valor->SubString( Valor->Length( ) - 2, 1 )) ) + " Real(is) e " + *ValorExtenso;
              }
            }
            break;
          case 4:
            if( ( Valor->SubString( Valor->Length( ) - 3, 1 ) == "1" ) && ( Valor->SubString( Valor->Length( ) - 1, 1 ) == "0" ) && ( Valor->SubString( Valor->Length( ), 1 ) == "0" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 3, 2 )) ) + " Real(is)";
            }
            else if( ( Valor->SubString( Valor->Length( ) - 3, 1 ) != "0" ) && ( Valor->SubString( Valor->Length( ) - 2, 1 ) == "0" ) && ( Valor->SubString( Valor->Length( ) - 1, 1 ) == "0" ) && ( Valor->SubString( Valor->Length( ), 1 ) == "0" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 3, 1 )) ) + " Real(is)";
            }
            else if( Valor->SubString( Valor->Length( ) - 3, 1 ) == "1" ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 3, 2 )) ) + " Real(is) e " + *ValorExtenso;
            }
            else if( ( Valor->SubString( Valor->Length( ) - 3, 1 ) != "0" ) && ( Valor->SubString( Valor->Length( ) - 2, 1 ) == "0" ) && ( Valor->SubString( Valor->Length( ) - 1, 2 ) != "00" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 3, 1 )) ) + " Real(is) e " + *ValorExtenso;
            }
            else if( ( Valor->SubString( Valor->Length( ) - 3, 1 ) != "0" ) && ( ( Valor->SubString( Valor->Length( ) - 2, 1 ) != "0" ) || ( Valor->SubString( Valor->Length( ) - 1, 1 ) != "0" ) || ( Valor->SubString( Valor->Length( ), 2 ) != "0" ) ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 3, 1 )) ) + " e " + *ValorExtenso;
            }
            break;
          case 5:
            if( ( Valor->SubString( Valor->Length( ) - 4, 1 ) == "1" ) && ( Valor->SubString( Valor->Length( ) - 3, 4 ) == "0000" ) ) {
              *ValorExtenso = Centena->ConverterCentenaTexto( &(Valor->SubString( Valor->Length( ) - 4, 3 )) ) + " Reais ";
            }
            else if( ( Valor->SubString( Valor->Length( ) - 4, 1 ) == "1" ) && ( Valor->SubString( Valor->Length( ) - 3, 2 ) == "00" ) && ( ( Valor->SubString( Valor->Length( ) - 1, 1 ) != "0" ) || ( Valor->SubString( Valor->Length( ), 1 ) != "0" ) ) ) {
              *ValorExtenso = Centena->ConverterCentenaTexto( &(Valor->SubString( Valor->Length( ) - 4, 3 )) ) + " Reais e " + *ValorExtenso;
            }
            else {
              if( ( Valor->SubString( Valor->Length( ) - 4, 1 ) != "0" ) && ( Valor->SubString( Valor->Length( ) - 3, 4 ) == "0000" ) ) {
                *ValorExtenso = Centena->ConverterCentenaTexto( &(Valor->SubString( Valor->Length( ) - 4, 1 )) ) + " Reais" + *ValorExtenso;
              }
              else if( ( Valor->SubString( Valor->Length( ) - 4, 1 ) != "0" ) && ( Valor->SubString( Valor->Length( ) - 3, 2 ) == "00" ) && ( ( Valor->SubString( Valor->Length( ) - 1, 1 ) != "0" ) || ( Valor->SubString( Valor->Length( ), 1 ) != "0" ) ) ) {
                *ValorExtenso = Centena->ConverterCentenaTexto( &(Valor->SubString( Valor->Length( ) - 4, 1 )) ) + " Reais e " + *ValorExtenso;
              }
              else if( Valor->SubString( Valor->Length( ) - 4, 1 ) != "0" ) {
                *ValorExtenso = Centena->ConverterCentenaTexto( &(Valor->SubString( Valor->Length( ) - 4, 1 )) ) + " e " + *ValorExtenso;
              }
            }
            break;
          case 6:
            if( ( Valor->SubString( Valor->Length( ) - 5, 1 ) != "0" ) && ( Valor->SubString( Valor->Length( ) - 4, 5 ) == "00000" ) ) {
              *ValorExtenso = Unidade->ConverterUnidadeTexto( &(Valor->SubString( Valor->Length( ) - 5, 1 )) ) + " Mil Reais" + *ValorExtenso;
            }
            else if( ( Valor->SubString( Valor->Length( ) - 4, 3 ) == "000" ) && ( Valor->Length( ) <= 6 ) ) {
              *ValorExtenso = Unidade->ConverterUnidadeTexto( &(Valor->SubString( Valor->Length( ) - 5, 1 )) ) + " Mil Reais e " + *ValorExtenso;
            }
            else if( ( ( Valor->SubString( Valor->Length( ) - 3, 2 ) == "00") || ( Valor->SubString( Valor->Length( ) - 4, 1 ) == "0" ) ) && ( Valor->SubString( Valor->Length( ) - 6, 1 ) != "1" ) && ( Valor->SubString( Valor->Length( ) - 5, 1 ) != "0" ) ) {
              *ValorExtenso = Unidade->ConverterUnidadeTexto( &(Valor->SubString( Valor->Length( ) - 5, 1 )) ) + " Mil e " + *ValorExtenso;
            }
            else if( ( Valor->SubString( Valor->Length( ) - 6, 1 ) != "1" ) && ( Valor->SubString( Valor->Length( ) - 5, 1 ) != "0" ) ) {
              *ValorExtenso = Unidade->ConverterUnidadeTexto( &(Valor->SubString( Valor->Length( ) - 5, 1 )) ) + " Mil " + *ValorExtenso;
            }
            break;
          case 7:
            if( ( Valor->SubString( Valor->Length( ) - 6, 1 ) == "1" ) && ( Valor->SubString( Valor->Length( ) - 4, 5 ) == "00000" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 2 )) ) + " Mil Reais";
            }
            else if( ( Valor->SubString( Valor->Length( ) - 6, 1 ) == "1" ) && ( Valor->SubString( Valor->Length( ) - 4, 3 ) == "000" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 2 )) ) + " Mil Reais e " + *ValorExtenso;
            }
            else if( ( Valor->SubString( Valor->Length( ) - 6, 1 ) == "1" ) && ( ( Valor->SubString( Valor->Length( ) - 3, 2 ) == "00" ) || ( Valor->SubString( Valor->Length( ) - 4, 1 ) == "0" ) ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 2 )) ) + " Mil e " + *ValorExtenso;
            }
            else if( Valor->SubString( Valor->Length( ) - 6, 1 ) == "1" ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 2 )) ) + " Mil " + *ValorExtenso;
            }
            else if( ( Valor->SubString( Valor->Length( ) - 4, 5 ) == "00000" ) && ( Valor->SubString( Valor->Length( ) - 5, 1 ) == "0" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 1 )) ) + " Mil Reais";
            }
            else if( Valor->SubString( Valor->Length( ) - 5, 1 ) != "0" ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 1 )) ) + " e " + *ValorExtenso;
            }
            else if( Valor->SubString( Valor->Length( ) - 4, 3 ) == "000" ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 1 )) ) + " Mil Reais e " + *ValorExtenso;
            }
            else if( ( Valor->SubString( Valor->Length( ) - 3, 2 ) == "00" ) || ( Valor->SubString( Valor->Length( ) - 4, 1 ) == "0" ) ) {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 1 )) ) + " Mil e " + *ValorExtenso;
            }
            else {
              *ValorExtenso = Dezena->ConverterDezenaTexto( &(Valor->SubString( Valor->Length( ) - 6, 1 )) ) + " Mil " + *ValorExtenso;
            }
            break;
        }
      }
      *Valor = Valor->Insert( ",", Valor->Length( ) - 1 );
    }
    catch( String &Message ) {
      Application->MessageBox( Message.c_str( ), "Conversor de Dinheiro para Texto", MB_ICONERROR||MB_OK );
    }
}
//---------------------------------------------------------------------------

