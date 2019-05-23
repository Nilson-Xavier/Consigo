//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TefVisanetRedecardAmex.h"
#include "ImpressoraFiscal.h"
#include "Main.h"
#include "Gerencia.h"
#include "Dmod1.h"
#include "Processos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TTefVisaNetRedeCardAmex::TTefVisaNetRedeCardAmex( ) {

  Identificacao = new AnsiString( );
  Transacao = new AnsiString( );
  Finalizacao = new AnsiString( );
  Cartao = new AnsiString( );
  Valor = new AnsiString( );
}
//---------------------------------------------------------------------------
__fastcall TTefVisaNetRedeCardAmex::~TTefVisaNetRedeCardAmex( ) {

  delete Identificacao;
  delete Transacao;
  delete Finalizacao;
  delete Cartao;
  delete Valor;
}
//---------------------------------------------------------------------------
// Verifica se o Gerenciador Padrão está ATIVO !!!
void TTefVisaNetRedeCardAmex::Atv( String* &Retorno ) {

  *Retorno = "";
  if( !FileExists( "C:\\tef_dial\\resp\\ativo.001" ) ) {
    *Retorno = "O Gerenciador TEF Padrão Não Está Ativo !\r\rPor Favor Fechar o Aplicativo e Ative o Gerenciador Padrão.";
  }
}
//---------------------------------------------------------------------------
bool TTefVisaNetRedeCardAmex::Adm( String* &Retorno, TStringList* &Cupom ) {

  TStringList *Texto;
  int i;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;
    Texto->Duplicates = dupError;
    *Retorno = "";
    *this->Identificacao = IntToStr( random( 21 ) );
    Texto->Add( "000-000 = ADM" );
    Texto->Add( "001-000 = " + *Identificacao );
    Texto->Add( "999-999 = 0" );
    if( !this->CriarArquivo( Texto ) ) {
      *Retorno = "Não Foi Possível Criar o Arquivo de Solicitação !";
    }
    else {
      Texto->Clear( );
      this->LerArquivoStatus( Texto );
      if( Texto->Values["001-000"] != *Identificacao ) {
        *Retorno = "Não Houve Resposta do Gerenciador TEF Padrão !";
      }
      else {
        do {
          this->LerArquivoResposta( Texto );
        } while( Texto->Values["001-000"] != *Identificacao );
        if( !Texto->Values["012-000"].IsEmpty( ) ) {
          *this->Transacao = Texto->Values["012-000"];
        }
        if( !Texto->Values["027-000"].IsEmpty( ) ) {
          *this->Finalizacao = Texto->Values["027-000"];
        }
        *this->Cartao = Texto->Values["010-000"];
        // Fazer Mensagem do Campo 30
        if( !Texto->Values["028-000"].IsEmpty( ) ) {
          if( Texto->Values["028-000"].ToInt( ) > 0 ) {
            Cupom->Sorted = false;
            Cupom->Duplicates = dupError;
            for( i = 0; i < Texto->Values["028-000"].ToInt( ); i++ ) {
              if( i < 9 ) {
                if( !Texto->Values["029-00" + IntToStr( i + 1 )].IsEmpty( ) ) {
                  Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Delete( 9, 1 );
                  Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Delete( Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Length( ), 1 );
                  Cupom->Append( "     " + Texto->Values["029-00" + IntToStr( i + 1 )] );
                }
                else {
                  Cupom->Append( "   " );
                }
              }
              else {
                if( !Texto->Values["029-0" + IntToStr( i + 1 )].IsEmpty( ) ) {
                  Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Delete( 9, 1 );
                  Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Delete( Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Length( ), 1 );
                  Cupom->Append( "     " + Texto->Values["029-0" + IntToStr( i + 1 )] );
                }
                else {
                  Cupom->Append( "   " );
                }
              }
            }
          }
        }
       *Retorno = Texto->Values["030-000"];
        if( Texto->Values["009-000"] != "0" ) {
          return( false );
        }
        else {
          return( true );
        }
      }
    }
  }
  __finally {
    delete Texto;
  }
}
//---------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::Chq( String* Total, String* &Retorno, TStringList* &Cupom ) {

  TStringList *Texto;
  int i;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;
    Texto->Duplicates = dupError;
    *Retorno = "";
    *Identificacao = IntToStr( random( 21 ) );
    Texto->Add( "000-000 = CHQ" );
    Texto->Add( "001-000 = " + *Identificacao );
    Total->Delete( Total->Pos( "." ), 1 );
    Total->Delete( Total->Pos( "," ), 1 );
    Texto->Add( "003-000 = " + *Total );
    Texto->Add( "999-999 = 0" );
    if( !this->CriarArquivo( Texto ) ) {
      *Retorno = "Não Foi Possível Criar o Arquivo de Solicitação !";
    }
    else {
      Texto->Clear( );
      this->LerArquivoStatus( Texto );
      if( Texto->Values["001-000"] != *Identificacao ) {
        *Retorno = "Não Houve Resposta do Gerenciador TEF Padrão !";
      }
      else {
        do {
          this->LerArquivoResposta( Texto );
        } while( Texto->Values["001-000"] != *Identificacao );
        if( Texto->Values["009-000"] != "0" ) {
          *Retorno = Texto->Values["030-000"];
        }
        if( ( Texto->Values["028-000"].IsEmpty( ) ) &&
            ( !Texto->Values["030-000"].IsEmpty( ) ) ) {
            SetForegroundWindow( Application->Handle );
            Application->MessageBox( ( Texto->Values["030-000"] ).c_str( ), "TEF Discado",
                                     MB_OK | MB_ICONINFORMATION );
        }
        else if( !Texto->Values["028-000"].IsEmpty( ) ) {
          if( Texto->Values["028-000"].ToInt( ) > 0 ) {
            Cupom->Sorted = false;
            Cupom->Duplicates = dupError;
            for( i = 0; i < Texto->Values["028-000"].ToInt( ); i++ ) {
              if( i < 9 ) {
                Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Delete( 9, 1 );
                Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Delete( Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Length( ), 1 );
                Cupom->Append( Texto->Values["029-00" + IntToStr( i + 1 )] );
              }
              else {
                Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Delete( 9, 1 );
                Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Delete( Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Length( ), 1 );
                Cupom->Append( Texto->Values["029-0" + IntToStr( i + 1 )] );
              }
            }
            if( !Texto->Values["030-000"].IsEmpty( ) ) {
              *Retorno = "Impressora=" + Texto->Values["030-000"];
            }
          }
        }
      }
    }
  }
  __finally {
    delete Texto;
  }
}
//---------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::Crt( String* Total, String* &Retorno, TStringList* &Cupom ) {

  TStringList *Texto;
  int i;
  bool ok;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;
    Texto->Duplicates = dupError;
    *Retorno = "";
    *Identificacao = IntToStr( random( 21 ) );
    Texto->Add( "000-000 = CRT" );
    Texto->Add( "001-000 = " + *Identificacao );
    // Formatar Valor R$
    Total->Delete( Total->Pos( "." ), 1 );
    Total->Delete( Total->Pos( "," ), 1 );
    Texto->Add( "003-000 = " + *Total );
    Texto->Add( "999-999 = 0" );
    if( !this->CriarArquivo( Texto ) ) {
      *Retorno = "Não Foi Possível Criar o Arquivo de Solicitação !";
    }
    else {
      Texto->Clear( );
      this->LerArquivoStatus( Texto );
      if( Texto->Values["001-000"] != *Identificacao ) {
        *Retorno = "Não Houve Resposta do Gerenciador TEF Padrão !";
      }
      else {
        Sleep( 2000 );
        //SetForegroundWindow( GetMainWindowHandle( "tef_dial.exe" ) );
        //SetFocus( GetMainWindowHandle( "tef_dial.exe" ) );
        this->LerArquivoResposta( Texto );
        if( Texto->Values["001-000"] != *Identificacao ) {
          *Retorno = "Não Houve Resposta do Gerenciador TEF Padrão !";
        }
        else {
          // Se o Campo 028-000 for > 0, Imprimir Cupom TEF
          *Transacao = Texto->Values["012-000"];
          *Finalizacao = Texto->Values["027-000"];
          *Cartao = Texto->Values["010-000"];
          *Valor = Texto->Values["003-000"];
          if( Valor->Length( ) == 1 ) {
            *Valor = "0,0" + *Valor;
          }
          else if( Valor->Length( ) == 2 ) {
            *Valor = "0," + *Valor;
          }
          else {
            Valor->Insert( ",", Valor->Length( ) -1 );
          }
          *Total = *Valor;
          if( !Texto->Values["028-000"].IsEmpty( ) ) {
            if( Texto->Values["028-000"].ToInt( ) > 0 ) {
              Cupom->Sorted = false;
              //Cupom->Duplicates = dupError;
              for( i = 0; i < Texto->Values["028-000"].ToInt( ); i++ ) {
                if( i < 9 ) {
                  Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Delete( 9, 1 );
                  Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Delete( Texto->Strings[ Texto->IndexOfName( "029-00" + IntToStr( i + 1 ) )].Length( ), 1 );
                  Cupom->Append( "     " + Texto->Values["029-00" + IntToStr( i + 1 )] );
                }
                else {
                  Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Delete( 9, 1 );
                  Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )] = Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Delete( Texto->Strings[ Texto->IndexOfName( "029-0" + IntToStr( i + 1 ) )].Length( ), 1 );
                  Cupom->Append( "     " + Texto->Values["029-0" + IntToStr( i + 1 )] );
                }
              }
            }
          }
          *Retorno = Texto->Values["030-000"];
        }
      }
    }
  }
  __finally {
    delete Texto;
  }
}
//---------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::Cnc( String* &Retorno, TStringList* &Cupom ) {

  this->Adm( Retorno, Cupom );
}
//---------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::Cnf( String* &Retorno ) {

  TStringList *Texto;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;
    Texto->Duplicates = dupError;
    DeleteFile( "C:\\tef_dial\\resp\\IntPos.001" );
    *Retorno = "";
    *this->Identificacao = IntToStr( random( 21 ) );
    Texto->Add( "000-000 = CNF" );
    Texto->Add( "001-000 = " + *this->Identificacao );
    Texto->Add( "010-000 = " + *this->Cartao );
    Texto->Add( "012-000 = " + *this->Transacao );
    Texto->Add( "027-000 = " + *this->Finalizacao );
    Texto->Add( "999-999 = 0" );
    if( !this->CriarArquivo( Texto ) ) {
      *Retorno = "Não Foi Possível Criar o Arquivo de Solicitação !";
    }
    else {
      Texto->Clear( );
      this->LerArquivoStatus( Texto );
      if( Texto->Values["001-000"] != *Identificacao ) {
        *Retorno = "Não Houve Resposta do Gerenciador TEF Padrão !";
      }
    }
  }
  __finally {
    delete Texto;
  }
}
//---------------------------------------------------------------------------
bool TTefVisaNetRedeCardAmex::Ncn( String* &Retorno ) {

  TStringList *Texto;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;
    Texto->Duplicates = dupError;
    DeleteFile( "C:\\tef_dial\\resp\\IntPos.001" );
    *Retorno = "";
    *this->Identificacao = IntToStr( random( 21 ) );
    Texto->Add( "000-000 = NCN" );
    Texto->Add( "001-000 = " + *this->Identificacao );
    Texto->Add( "010-000 = " + *this->Cartao );
    Texto->Add( "012-000 = " + *this->Transacao );
    Texto->Add( "027-000 = " + *this->Finalizacao );
    Texto->Add( "999-999 = 0" );
    if( !this->CriarArquivo( Texto ) ) {
      *Retorno = "Não Foi Possível Criar o Arquivo de Solicitação !";
      return( false );
    }
    else {
      Texto->Clear( );
      this->LerArquivoStatus( Texto );
      if( Texto->Values["001-000"] != *Identificacao ) {
        *Retorno = "Não Houve Resposta do Gerenciador TEF Padrão !";
        return( false );
      }
      else {
        if( !this->Valor->IsEmpty( ) ) {
          *Retorno =  "Cancelada a Transação: \rDoc No: " + *this->Transacao + "\r" +
                     "Rede: " + *this->Cartao + "\r" + "Valor: " + *this->Valor;
        }
        else {
          *Retorno = "Cancelada a Transação: \rDoc No: " + *this->Transacao + "\r" +
                    "Rede: " + *this->Cartao;
        }
        return( true );
      }
    }
  }
  __finally {
    delete Texto;
  }
}
//---------------------------------------------------------------------------
bool TTefVisaNetRedeCardAmex::CriarArquivo( TStringList *Texto ) {

  Texto->SaveToFile( "C:\\tef_dial\\req\\IntPos.tmp" );
  if( !RenameFile( "C:\\tef_dial\\req\\IntPos.tmp", StringReplace( "C:\\tef_dial\\req\\IntPos.tmp", ".tmp", ".001", TReplaceFlags( ) << rfReplaceAll ) ) ) {
    return( false );
  }

  return( true );
}
//---------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::LerArquivoStatus( TStringList* &Texto ) {

  int i;
  bool Ok = false;

  for( i = 0; i < 8; i++ ) {
    Sleep( 1000 );
    Ok = FileExists( "C:\\tef_dial\\resp\\IntPos.sts" );
    if( Ok ) {
      break;
    }
  }
  if( Ok ) {
    Texto->Clear( );
    Texto->LoadFromFile( "C:\\tef_dial\\resp\\IntPos.sts" );
    for( i = 0; i < Texto->Count; i++ ) {
      Texto->Strings[i] = Texto->Strings[i].Delete( 8, 1);
      Texto->Strings[i] = Texto->Strings[i].Delete( 9, 1 );
    }
    DeleteFile( "C:\\tef_dial\\resp\\IntPos.sts" );
  }
}
//---------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::LerArquivoResposta( TStringList* &Texto ) {

  bool Ok = false;
  int i;

  while( !Ok ) {
    Ok = FileExists( "C:\\tef_dial\\resp\\IntPos.001" );
    Sleep( 2000 );
  }
  Texto->Clear( );
  Texto->LoadFromFile( "C:\\tef_dial\\resp\\IntPos.001" );
  for( i = 0; i < Texto->Count; i++ ) {
    Texto->Strings[i] = Texto->Strings[i].Delete( 8, 1);
    Texto->Strings[i] = Texto->Strings[i].Delete( 9, 1 );
  }
  if( Texto->Values["029-001"].IsEmpty( ) ) {
    DeleteFile( "C:\\tef_dial\\resp\\IntPos.001" );
  }
}
//---------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::ChecarErro( String* &Retorno ) {

  TStringList *Texto;
  int i;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;

    *Retorno = "";
    if( FileExists( "C:\\tef_dial\\req\\IntPos.001" ) ) {
      DeleteFile( "C:\\tef_dial\\req\\IntPos.001" );
    }
    if( FileExists( "C:\\tef_dial\\resp\\IntPos.001" ) ) {
      Texto->LoadFromFile( "C:\\tef_dial\\resp\\IntPos.001" );
      for( i = 0; i < Texto->Count; i++ ) {
        Texto->Strings[i] = Texto->Strings[i].Delete( 8, 1);
        Texto->Strings[i] = Texto->Strings[i].Delete( 9, 1 );
      }
      *this->Identificacao = Texto->Values["001-000"];
      *this->Cartao = Texto->Values["010-000"];
      *this->Transacao = Texto->Values["012-000"];
      *this->Finalizacao = Texto->Values["027-000"];
      *this->Valor = Texto->Values["003-000"];
      if( !this->Valor->IsEmpty( ) ) {
        if( Valor->Length( ) == 1 ) {
          Valor->Insert( "00,", 1 );
        }
        else if( Valor->Length( ) == 2 ) {
          Valor->Insert( "0,", 1 );
        }
        else {
          Valor->Insert( ",", Valor->Length( ) -1 );
        }
      }
      if( this->Ncn( Retorno ) ) {
        Application->MessageBox( Retorno->c_str( ), "TEF Discado", MB_OK | MB_ICONWARNING );
        *Retorno = "";
      }
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------
void TTefVisaNetRedeCardAmex::ChecarErroTemp( String* &Retorno ) {

  TStringList *Texto;
  int i, j;

  try {
    Texto = new TStringList( );
    Texto->Sorted = false;

    try {
      *Retorno = "";
      i = 1;
      while( FileExists( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) ) ) {
        Texto->LoadFromFile( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) );
        for( j = 0; j < Texto->Count; j++ ) {
          Texto->Strings[j] = Texto->Strings[j].Delete( 8, 1);
          Texto->Strings[j] = Texto->Strings[j].Delete( 9, 1 );
        }
        if( Texto->Values["010-000"] != "TECBAN" ) {
          *this->Identificacao = Texto->Values["001-000"];
          *this->Cartao = Texto->Values["010-000"];
          *this->Transacao = Texto->Values["012-000"];
          *this->Finalizacao = Texto->Values["027-000"];
          *this->Valor = Texto->Values["003-000"];
          if( !this->Valor->IsEmpty( ) ) {
            if( Valor->Length( ) == 1 ) {
              Valor->Insert( "00,", 1 );
            }
            else if( Valor->Length( ) == 2 ) {
              Valor->Insert( "0,", 1 );
            }
            else {
              Valor->Insert( ",", Valor->Length( ) -1 );
            }
          }
          if( this->Ncn( Retorno ) ) {
            if( FileExists( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) ) ) {
              DeleteFile( "C:\\tef_temp\\IntPos.00" + IntToStr( i ) );
            }
            *Retorno = "";
            Application->MessageBox( Retorno->c_str( ), "TEF Discado", MB_OK | MB_ICONWARNING );
          }
          else {
            throw( *Retorno );
          }
        }
        Texto->Clear( );
        i++;
      }
    }
    catch( String &Erro ) {
      *Retorno = Erro;
    }
  }
  __finally {
    delete Texto;
  }
}
//------------------------------------------------------------------------

