//---------------------------------------------------------------------------
#ifndef ImpressaoCotacaoPrecoH
#define ImpressaoCotacaoPrecoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <QuickRpt.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Qrctrls.hpp>
//---------------------------------------------------------------------------
class TFormCotacaoPreco : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *QuickRepCotacao;
  TQRBand *QRBand2;
  TQRImage *QRImage2;
  TQRLabel *QRLabel38;
	TQRBand *QRBand3;
	TQRLabel *QRLabel15;
	TQRLabel *QRLabelTotal;
	TQRLabel *QRLabel16;
	TQRLabel *QRLabelValidade;
	TQRLabel *QRLabel18;
	TQRLabel *QRLabelPrazoEntrega;
	TQRLabel *QRLabel20;
	TQRLabel *QRLabel21;
	TQRLabel *QRLabelFrete;
	TQRLabel *QRLabel22;
	TQRLabel *QRLabelVendedor;
	TQRLabel *QRLabel23;
	TQRLabel *QRLabel24;
	TQRLabel *QRLabelAssinatura;
	TQRLabel *QRLabel26;
	TQRLabel *QRLabel27;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel28;
	TQRLabel *QRLabel29;
	TQRBand *QRBand5;
	TQRSysData *QRSysData1;
	TQRLabel *QRLabelPagina;
	TQRExpr *QRExpr1;
	TQRRichText *QRRichTextPagamento;
	TQRLabel *QRLabelData;
	TQRLabel *QRLabel3;
	TQRLabel *QRLabelEmpresa;
	TQRLabel *QRLabel8;
	TQRLabel *QRLabelCNPJ;
	TQRLabel *QRLabel17;
	TQRLabel *QRLabelInscricaoEstadual;
	TQRLabel *QRLabel4;
	TQRLabel *QRLabelNome;
	TQRLabel *QRLabel7;
	TQRLabel *QRLabelFax;
	TQRLabel *QRLabel6;
	TQRLabel *QRLabelTel;
	TQRLabel *QRLabelEndereco;
	TQRLabel *QRLabelCidade;
	TQRLabel *QRLabel2;
	TQRLabel *QRLabelCep;
	TQRLabel *QRLabelEstado;
	TQRLabel *QRLabel9;
	TQRStringsBand *QRStringsBand1;
	TQRLabel *QRLabel10;
	TQRLabel *QRLabel11;
	TQRLabel *QRLabel12;
	TQRLabel *QRLabel13;
	TQRLabel *QRLabel5;
	TQRLabel *QRLabel14;
	TQRMemo *QRMemoMarca;
	TQRMemo *QRMemoNome;
	TQRMemo *QRMemoGarantia;
	TQRMemo *QRMemoQuantidade;
	TQRMemo *QRMemoPrecoUnit;
	TQRMemo *QRMemoPreco;
private:	// User declarations
public:		// User declarations
	__fastcall TFormCotacaoPreco(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormCotacaoPreco *FormCotacaoPreco;
//---------------------------------------------------------------------------
#endif
