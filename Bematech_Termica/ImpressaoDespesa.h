//---------------------------------------------------------------------------
#ifndef ImpressaoDespesaH
#define ImpressaoDespesaH
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
class TFormImpressaoDespesa : public TForm {

  __published:	// IDE-managed Components

	  TQuickRep *QuickRepDespesa;
      TQRBand *QRBand1;
      TQRLabel *QRLabel1;
      TQRBand *QRBand2;
	  TQRLabel *QRLabelTotal;
      TQRBand *QRBand3;
      TQRSysData *QRSysData1;
      TQRLabel *QRLabel11;
      TQRSysData *QRSysData2;
  	TQRLabel *QRLabel2;
	  TQRLabel *QRLabelDataInicial;
  	TQRLabel *QRLabel4;
	  TQRLabel *QRLabelDataFinal;
  	TQRLabel *QRLabelVencimento;
	  TQRLabel *QRLabel7;
  	TQRLabel *QRLabel8;
	  TQRImage *QRImageLogo;
  	TQRBand *QRBand4;
	  TQRDBText *QRDBVencimento;
  	TQRDBText *QRDBNome;
    TQRExpr *QRExprTotal;
    TQRExpr *QRExpr1;
  TQuery *QueryDespesa;
  TDateTimeField *QueryDespesaVencimento;
  TStringField *QueryDespesaNome;
  TFloatField *QueryDespesaValor;
  TDateTimeField *QueryDespesaData;

  private:	// User declarations

  public:		// User declarations

	__fastcall TFormImpressaoDespesa( TComponent* Owner );
};
//---------------------------------------------------------------------------
extern TFormImpressaoDespesa *FormImpressaoDespesa;
//---------------------------------------------------------------------------
#endif
