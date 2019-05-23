//---------------------------------------------------------------------------
#ifndef ImpressaoEntradaProdutoH
#define ImpressaoEntradaProdutoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <Graphics.hpp>
#include <Qrctrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TFormImpressaoEntradaProduto : public TForm
{
__published:	// IDE-managed Components
  TQuickRep *QuickRepEntradaProduto;
  TQRBand *QRBand1;
  TQRLabel *QRLabel1;
  TQRSubDetail *QRSubDetail1;
  TQRBand *QRBand2;
  TQRLabel *QRLabelTotal;
  TQRBand *QRBand3;
  TQRSysData *QRSysData1;
  TQRSysData *QRSysData2;
  TQRImage *QRImageLogo;
  TQRLabel *QRLabel2;
  TQRLabel *QRLabelDataInicial;
  TQRLabel *QRLabel4;
  TQRLabel *QRLabelDataFinal;
  TQRBand *QRBand5;
  TQRLabel *QRLabelTotalOk;
  TQRBand *QRBand4;
  TQRLabel *QRLabelFornecedor;
  TQRExpr *QRExprFornecedor;
  TQRLabel *QRLabelNotaFiscal;
  TQRExpr *QRExprNotaFiscal;
  TQRLabel *QRLabelData;
  TQRExpr *QRExprData;
  TQRExpr *QRExprPrecoUnit;
  TQRExpr *QRExprTotal;
  TQRExpr *QRExprMarca;
  TQRExpr *QRExprNome;
  TQRExpr *QRExprQuantidade;
  TQRExpr *QRExprPreco;
  TQRExpr *QRExprTotalOk;
  TQRCompositeReport *QRCompositeReportEntradaProduto;
  TQuery *QueryEntradaFornecedores;
  TStringField *QueryEntradaFornecedoresCGC;
  TIntegerField *QueryEntradaFornecedoresNumero_nota;
  TStringField *QueryEntradaFornecedoresNome;
  TIntegerField *QueryEntradaFornecedoresDia;
  TIntegerField *QueryEntradaFornecedoresMes;
  TIntegerField *QueryEntradaFornecedoresAno;
  TQuery *QueryEntradaItens;
  TFloatField *QueryEntradaItensPreco_Custo;
  TStringField *QueryEntradaItensNome;
  TStringField *QueryEntradaItensMarca;
  TIntegerField *QueryEntradaItensQuantidade;
  TDataSource *DataSourceEntradaFornecedores;
  void __fastcall QRCompositeReportEntradaProdutoAddReports(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormImpressaoEntradaProduto(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormImpressaoEntradaProduto *FormImpressaoEntradaProduto;
//---------------------------------------------------------------------------
#endif
