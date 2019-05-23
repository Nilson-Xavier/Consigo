//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Main.h"
#include "ImpressoraFiscal.h"
#include "ThreadLeituraX.h"
#include "ThreadReducaoZ.h"
#include "ThreadLeituraMemoriaFiscal.h"
#include "ThreadLeituraReducaoFiscal.h"
#include "ThreadCancelamentoCupom.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::ImpressoraClick( TObject *Sender ) {

	PageControl1->ActivePage = TabSheetImpressora;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnCancelarCupomClick( TObject *Sender ) {

  TCancelamentoCupomThread *CancelamentoCupomThread;

  try {
    CancelamentoCupomThread = new TCancelamentoCupomThread( true );
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BtnLeituraXClick( TObject *Sender ) {

  TLeituraXThread *LeituraXThread;

  try {
    LeituraXThread = new TLeituraXThread( true );
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BtnReducaoZClick( TObject *Sender ) {

  TReducaoZThread *ReducaoZThread;

  try {
    ReducaoZThread = new TReducaoZThread( true );
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BtnMensagemPromocionalClick( TObject *Sender ) {

  // Implementar PROGLINHAADICIONAL!!!
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnLeituraMemoriaFiscalDataClick( TObject *Sender) {

  TLeituraMemoriaFiscalThread *LeituraMemoriaFiscalThread;

  try {
    if( ( this->MaskEditDataInicial->Text.Length( ) == 8 ) &&
        ( this->MaskEditDataFinal->Text.Length( ) == 8 ) ) {
      LeituraMemoriaFiscalThread = new TLeituraMemoriaFiscalThread( &( this->MaskEditDataInicial->Text ), &( this->MaskEditDataFinal->Text ), true );
    }
    else {
      Application->MessageBox( "Formato de Data Inválido !", "Gerência - Impressora", MB_OK | MB_ICONERROR );
    }
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnLeituraMemoriaFiscalReducaoClick( TObject *Sender) {

  TLeituraReducaoFiscalThread *LeituraReducaoFiscalThread;

  try {
    if( ( this->MaskEditReducaoInicial->Text.Length( ) >= 1 ) &&
        ( this->MaskEditReducaoFinal->Text.Length( ) >= 1 ) ) {
      LeituraReducaoFiscalThread = new TLeituraReducaoFiscalThread( &( this->MaskEditReducaoInicial->Text ), &( this->MaskEditReducaoFinal->Text ), true );
    }
    else {
      Application->MessageBox( "Faltam Dados para a Leitura da Memória Fiscal por Redução !", "Gerência - Impressora", MB_OK | MB_ICONERROR );
    }
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
