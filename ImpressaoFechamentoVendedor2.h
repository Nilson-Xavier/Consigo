//---------------------------------------------------------------------------

#ifndef ImpressaoFechamentoVendedor2H
#define ImpressaoFechamentoVendedor2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TFormImpressaoFechamentoVendedor2 : public TForm
{
__published:	// IDE-managed Components
  TQuery *QueryFechamentoVendedor2;
  TStringField *QueryFechamentoVendedor2Marca;
  TStringField *QueryFechamentoVendedor2Nome;
  TIntegerField *QueryFechamentoVendedor2Quantidade;
  TFloatField *QueryFechamentoVendedor2Preco;
  TStringField *QueryFechamentoVendedor2Tipo;
  TDateTimeField *QueryFechamentoVendedor2Data;
  TIntegerField *QueryFechamentoVendedor2Numero_nota;
  TStringField *QueryFechamentoVendedor2Vendedor;
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
private:	// User declarations
public:		// User declarations
  __fastcall TFormImpressaoFechamentoVendedor2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImpressaoFechamentoVendedor2 *FormImpressaoFechamentoVendedor2;
//---------------------------------------------------------------------------
#endif
