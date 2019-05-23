//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Gerencia.h"
#include "ThreadTefAdmVisanet.h"
#include "ThreadTefAdmTecban.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::MenuItemTefClick( TObject *Sender ) {

  this->PageControl1->ActivePage = this->TabSheetTef;
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnAdministracaoTefVisanetClick( TObject *Sender ) {

  TTefAdmVisanetThread *TefAdmVisanetThread;

  try {
    TefAdmVisanetThread = new TTefAdmVisanetThread( true );
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnAdministracaoTefTecBanClick( TObject *Sender ) {

  TTefAdmTecBanThread *TefAdmTecBanThread;

  try {
    TefAdmTecBanThread = new TTefAdmTecBanThread( true );
  }
  __finally {

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGerencia::BitBtnConsultarChequeClick( TObject *Sender ) {

}
//---------------------------------------------------------------------------

