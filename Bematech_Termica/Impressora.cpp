//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "Main.h"
#include "ThreadLeituraX.h"
#include "ThreadReducaoZ.h"
#include "ThreadLeituraMemoriaFiscal.h"
#include "ThreadLeituraReducaoFiscal.h"
#include "ThreadCancelamentoCupom.h"
#include "ThreadGerarArquivoRfd.h"
#include "ThreadValidarArquivoRfd.h"
#include <FileCtrl.hpp>
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
    if( Application->MessageBox( "Esse processo finalizara o dia fiscal do ECF.\r\rTem certeza de que deseja realizar a Reducao Z ?", "Funcoes da impressora Fiscal", MB_YESNO | MB_ICONWARNING ) == IDYES ) {
      ReducaoZThread = new TReducaoZThread( true );
    }
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
void __fastcall TFormGerencia::BitBtnOpenFolderDialogClick( TObject *Sender) {

  String *Folder;

  try {
    Folder = new AnsiString( );
    if( SelectDirectory( *Folder, TSelectDirOpts( ), 1000 ) ) {
      EditPastaRfd->Text = *Folder;
    }
    else {
      EditPastaRfd->Clear( );
    }
  }
  __finally {
    delete Folder;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnGerarArquivoRfdClick( TObject *Sender) {

  TThreadGerarArquivoRfd *GerarArquivoRfdThread;

  try {
    GerarArquivoRfdThread = new TThreadGerarArquivoRfd( &(this->MaskEditDataRfd->Text),
        &(this->EditPastaRfd->Text), true );
  }
  __finally {
    
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnOpenFileDialogClick( TObject *Sender) {

  if( OpenDialogArquivoRfd->Execute( ) ) {
    EditPastaRfd->Text = OpenDialogArquivoRfd->FileName;
  }
  else {
    EditArquivoRfd->Clear( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnValidarArquivoRfdClick( TObject *Sender) {

  TThreadValidarArquivoRfd *ValidarArquivoRfdThread;

  try {
    if( !this->EditArquivoRfd->Text.IsEmpty( ) ) {
      ValidarArquivoRfdThread = new TThreadValidarArquivoRfd( &(this->EditArquivoRfd->Text), true );
    }
    else {
      Application->MessageBox( "Falta o Caminho do Arquivo para a Validacao do Arquivo RFD !", "Gerência - Impressora", MB_OK | MB_ICONERROR );
    }
  }
  __finally {
    
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::DesabilitarButoesFuncoesImpressora( void ) {

  FormGerencia->BitBtnCancelarCupom->Enabled = false;
  FormGerencia->BtnLeituraX->Enabled = false;
  FormGerencia->BtnReducaoZ->Enabled = false;
  FormGerencia->MaskEditDataFinal->Enabled = false;
  FormGerencia->MaskEditDataInicial->Enabled = false;
  FormGerencia->BitBtnLeituraMemoriaFiscalData->Enabled = false;
  FormGerencia->MaskEditReducaoInicial->Enabled = false;
  FormGerencia->MaskEditReducaoFinal->Enabled = false;
  FormGerencia->BitBtnLeituraMemoriaFiscalReducao->Enabled = false;
  FormGerencia->BitBtnOpenFolderDialog->Enabled = false;
  FormGerencia->EditPastaRfd->Enabled = false;
  FormGerencia->MaskEditDataRfd->Enabled = false;
  FormGerencia->BitBtnGerarArquivoRfd->Enabled = false;
  FormGerencia->BitBtnOpenFileDialog->Enabled = false;
  FormGerencia->EditArquivoRfd->Enabled = false;
  FormGerencia->BitBtnValidarArquivoRfd->Enabled = false;

}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::AbilitarButoesFuncoesImpressora( void ) {

  FormGerencia->BitBtnCancelarCupom->Enabled = true;
  FormGerencia->BtnLeituraX->Enabled = true;
  FormGerencia->BtnReducaoZ->Enabled = true;
  FormGerencia->MaskEditDataFinal->Enabled = true;
  FormGerencia->MaskEditDataInicial->Enabled = true;
  FormGerencia->BitBtnLeituraMemoriaFiscalData->Enabled = true;
  FormGerencia->MaskEditReducaoInicial->Enabled = true;
  FormGerencia->MaskEditReducaoFinal->Enabled = true;
  FormGerencia->BitBtnLeituraMemoriaFiscalReducao->Enabled = true;
  FormGerencia->BitBtnOpenFolderDialog->Enabled = true;
  FormGerencia->EditPastaRfd->Enabled = true;
  FormGerencia->MaskEditDataRfd->Enabled = true;
  FormGerencia->BitBtnGerarArquivoRfd->Enabled = true;
  FormGerencia->BitBtnOpenFileDialog->Enabled = true;
  FormGerencia->EditArquivoRfd->Enabled = true;
  FormGerencia->BitBtnValidarArquivoRfd->Enabled = true;
}
//---------------------------------------------------------------------------
