//---------------------------------------------------------------------------
#ifndef ImpressaoFechamentoVendedorH
#define ImpressaoFechamentoVendedorH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <QuickRpt.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Qrctrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TFormImpressaoFechamentoVendedor : public TForm
{
__published:	// IDE-managed Components
  TQuickRep *QuickRepFechamentoVendedor;
  TQRBand *QRBand1;
  TQRLabel *QRLabel1;
  TQRImage *QRImage1;
  TQRLabel *QRLabel2;
  TQRLabel *QRLabelDataInicial;
  TQRLabel *QRLabel4;
  TQRLabel *QRLabelDataFinal;
  TQRBand *QRBand3;
  TQRSysData *QRSysData1;
  TQRLabel *QRLabel17;
  TQRSysData *QRSysData2;
  TQRBand *QRBand4;
  TQRLabel *QRLabelTotal;
  TQRExpr *QRExprTotal;
  TQRLabel *QRLabelComissao;
  TQRExpr *QRExprComissao;
  TQRBand *QRBand5;
  TQRLabel *QRLabelTotalGeral;
  TQRExpr *QRExprTotalGeral;
  TQuery *QueryFechamentoVendedor;
  TQRGroup *QRGroup1;
  TQRLabel *QRLabelVendedor;
  TQRExpr *QRExprVendedor;
  TQRBand *QRBand2;
  TQRExpr *QRExprData;
  TQRExpr *QRExprMarca;
  TQRExpr *QRExprNome;
  TQRExpr *QRExprQuantidade;
  TQRExpr *QRExprPrecoUnit;
  TQRExpr *QRExprPreco;
  TQRExpr *QRExprTipo;
  TStringField *QueryFechamentoVendedorMarca;
  TStringField *QueryFechamentoVendedorNome;
  TIntegerField *QueryFechamentoVendedorQuantidade;
  TFloatField *QueryFechamentoVendedorPreco;
  TStringField *QueryFechamentoVendedorTipo;
  TDateTimeField *QueryFechamentoVendedorData;
  TIntegerField *QueryFechamentoVendedorNumero_nota;
  TStringField *QueryFechamentoVendedorVendedor;
  TQRCompositeReport *QRCompositeReportFechamentoVendedor;
  void __fastcall QRCompositeReportFechamentoVendedorAddReports(
          TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormImpressaoFechamentoVendedor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormImpressaoFechamentoVendedor *FormImpressaoFechamentoVendedor;
//---------------------------------------------------------------------------
#endif
