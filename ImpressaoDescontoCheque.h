//---------------------------------------------------------------------------

#ifndef ImpressaoDescontoChequeH
#define ImpressaoDescontoChequeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <Qrctrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormImpressaoCheque : public TForm
{
__published:	// IDE-managed Components
  TQuickRep *QuickRepCheque;
  TQRBand *QRBand1;
  TQRShape *QRShapeLinha;
  TQRLabel *QRLabelProtocolo;
  TQRShape *QRShapeLinha2;
  TQRMemo *QRMemoInstrucao;
  TQRShape *QRShape1;
  TQRShape *QRShape2;
  TQRLabel *QRLabelTelefone;
  TQRLabel *QRLabelBanco;
  TQRLabel *QRLabelAgencia;
  TQRLabel *QRLabelConta;
  TQRLabel *QRLabelDV;
  TQRLabel *QRLabelPCB;
  TQRLabel *QRLabelQtdCheque;
  TQRLabel *QRLabelTotalCheque;
  TQRLabel *QRLabelTotalData;
  TQRShape *QRShapeLinhaVert1;
  TQRShape *QRShapeLinhaVert2;
  TQRShape *QRShapeLinha3;
  TQRShape *QRShapeLinhaVert3;
  TQRShape *QRShape3;
  TQRShape *QRShape4;
  TQRShape *QRShape5;
  TQRShape *QRShape6;
  TQRLabel *QRLabelCheques;
  TQRShape *QRShape7;
  TQRLabel *QRLabelCodBanco;
  TQRLabel *QRLabelCodAgencia;
  TQRLabel *QRLabelConta2;
  TQRLabel *QRLabelCheque;
  TQRLabel *QRLabelTotal;
  TQRLabel *QRLabelData;
  TQRLabel *QRLabelTotalData2;
  TQRShape *QRShape9;
  TQRShape *QRShape10;
  TQRShape *QRShape11;
  TQRShape *QRShape12;
  TQRShape *QRShape13;
  TQRShape *QRShape14;
  TQRShape *QRShape15;
  TQRStringsBand *QRStringsBand1;
  TQRShape *QRShape16;
  TQRShape *QRShape8;
  TQRShape *QRShape17;
  TQRShape *QRShape18;
  TQRShape *QRShape19;
  TQRShape *QRShape20;
  TQRShape *QRShape21;
  TQRShape *QRShape22;
  TQRBand *QRBand3;
  TQRShape *QRShape23;
  TQRLabel *QRLabelTotalGeral;
  TQRLabel *QRLabelData2;
  TQRLabel *QRLabelAssinatura;
  TQRShape *QRShape24;
  TQRShape *QRShapeLinhaVert4;
  TQRShape *QRShape26;
  TQRShape *QRShape25;
  TQRShape *QRShape27;
  TQRShape *QRShape28;
  TQRShape *QRShape29;
  TQRMemo *QRMemoContato;
  TQRMemo *QRMemoTelefone;
  TQRMemo *QRMemoCodBanco;
  TQRMemo *QRMemoCodAgencia;
  TQRMemo *QRMemoCodConta;
  TQRMemo *QRMemoDV;
  TQRMemo *QRMemoQuantidade;
  TQRMemo *QRMemoTotal;
  TQRLabel *QRLabel3;
  TQRLabel *QRLabelTotal2;
  TQRLabel *QRLabelData3;
  TQRExpr *QRExprTetxo;
  TQRExpr *QRExpr1;
  TQRExpr *QRExpr2;
  TQRExpr *QRExpr3;
  TQRExpr *QRExpr4;
  TQRExpr *QRExpr5;
  TQRExpr *QRExpr6;
  TQRExpr *QRExpr7;
  TQRImage *QRImageConsigo;
  TQRLabel *QRLabelCliente;
  TQRLabel *QRLabelContato;
  TQRLabel *QRLabelConsigo;
private:	// User declarations
public:		// User declarations
  __fastcall TFormImpressaoCheque(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImpressaoCheque *FormImpressaoCheque;
//---------------------------------------------------------------------------
#endif
