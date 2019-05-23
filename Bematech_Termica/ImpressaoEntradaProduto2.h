//---------------------------------------------------------------------------

#ifndef ImpressaoEntradaProduto2H
#define ImpressaoEntradaProduto2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TFormImpressaoEntradaProduto2 : public TForm
{
__published:	// IDE-managed Components
  TQuickRep *QuickRepEntradaProduto;
  TQRBand *QRBand1;
  TQRLabel *QRLabelSlogan;
  TQRImage *QRImageLogo;
  TQRLabel *QRLabel2;
  TQRLabel *QRLabelDataInicial;
  TQRLabel *QRLabel4;
  TQRLabel *QRLabelDataFinal;
  TQRBand *QRBand4;
  TQRLabel *QRLabelFornecedor;
  TQRExpr *QRExprFornecedor;
  TQRLabel *QRLabelNotaFiscal;
  TQRExpr *QRExprNotaFiscal;
  TQRLabel *QRLabelData;
  TQRExpr *QRExprData;
  TQRSubDetail *QRSubDetail1;
  TQRExpr *QRExprPrecoUnit;
  TQRExpr *QRExprMarca;
  TQRExpr *QRExprNome;
  TQRExpr *QRExprQuantidade;
  TQRExpr *QRExprPreco;
  TQRBand *QRBand2;
  TQRLabel *QRLabelTotal;
  TQRExpr *QRExprTotal;
  TQRBand *QRBand5;
  TQRLabel *QRLabelTotal2;
  TQRExpr *QRExprTotal2;
  TQRBand *QRBand3;
  TQRSysData *QRSysData1;
  TQRLabel *QRLabel16;
  TQRSysData *QRSysData2;
  TQuery *QueryEntradaFornecedores;
  TStringField *StringField1;
  TIntegerField *IntegerField1;
  TStringField *QueryEntradaFornecedoresNome;
  TIntegerField *QueryEntradaFornecedoresDia;
  TIntegerField *QueryEntradaFornecedoresMes;
  TIntegerField *QueryEntradaFornecedoresAno;
  TQuery *QueryEntradaItens;
  TFloatField *QueryEntradaItensPreco;
  TStringField *QueryEntradaItensNome;
  TStringField *QueryEntradaItensMarca;
  TIntegerField *QueryEntradaItensQuantidade;
  TDataSource *DataSourceEntradaFornecedores;
private:	// User declarations
public:		// User declarations
  __fastcall TFormImpressaoEntradaProduto2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImpressaoEntradaProduto2 *FormImpressaoEntradaProduto2;
//---------------------------------------------------------------------------
#endif
