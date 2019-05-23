//---------------------------------------------------------------------------

#ifndef ImpressaoListaPrecoH
#define ImpressaoListaPrecoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TFormImpressaoListaPreco : public TForm
{
__published:	// IDE-managed Components
  TQuickRep *QuickRepListaPreco;
  TQRBand *QRBand1;
  TQRLabel *QRLabel1;
  TQRLabel *QRLabel2;
  TQRImage *QRImageLogo;
  TQRGroup *QRGroup1;
  TQRExpr *QRExprMarca;
  TQRBand *QRBand3;
  TQRSysData *QRSysData1;
  TQRLabel *QRLabel11;
  TQRSysData *QRSysData2;
  TQRBand *QRBand2;
  TQRExpr *QRExprNome;
  TQRExpr *QRExprPreco;
private:	// User declarations
public:		// User declarations
  __fastcall TFormImpressaoListaPreco(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImpressaoListaPreco *FormImpressaoListaPreco;
//---------------------------------------------------------------------------
#endif
