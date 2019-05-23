//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <vcl/dialogs.hpp>
#pragma hdrstop

#include "ImpressaoFechamentoVendedor.h"
#include "ImpressaoFechamentoVendedor2.h"
#include "Dmod1.h"
#include "Dmod2.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormImpressaoFechamentoVendedor *FormImpressaoFechamentoVendedor;
//---------------------------------------------------------------------------
__fastcall TFormImpressaoFechamentoVendedor::TFormImpressaoFechamentoVendedor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressaoFechamentoVendedor::QRCompositeReportFechamentoVendedorAddReports(
  TObject *Sender ) {

  QRCompositeReportFechamentoVendedor->Reports->Add( this->QuickRepFechamentoVendedor );
  QRCompositeReportFechamentoVendedor->Reports->Add( FormImpressaoFechamentoVendedor2->QuickRepFechamentoVendedor );
}
//---------------------------------------------------------------------------

