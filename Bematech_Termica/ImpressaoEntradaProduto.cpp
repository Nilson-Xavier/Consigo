//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "ImpressaoEntradaProduto.h"
#include "ImpressaoEntradaProduto2.h"
#include "Dmod1.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormImpressaoEntradaProduto *FormImpressaoEntradaProduto;
//---------------------------------------------------------------------------
__fastcall TFormImpressaoEntradaProduto::TFormImpressaoEntradaProduto(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressaoEntradaProduto::QRCompositeReportEntradaProdutoAddReports(
  TObject *Sender ) {

  QRCompositeReportEntradaProduto->Reports->Add( this->QuickRepEntradaProduto );
  QRCompositeReportEntradaProduto->Reports->Add( FormImpressaoEntradaProduto2->QuickRepEntradaProduto );
}
//---------------------------------------------------------------------------


