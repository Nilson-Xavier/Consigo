//---------------------------------------------------------------------------

#ifndef ImpressoraFiscalH
#define ImpressoraFiscalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TFormImpressora : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControlImpressora;
	TTabSheet *TabSheetEmissaoCupom;
	TMainMenu *MainMenuImpressora;
	TMenuItem *MenuItemFuncoes;
	TMenuItem *MenuItemSair;
	TMenuItem *EmissodeCupom1;
	TTabSheet *TabSheetFuncaoImpressora;
	TMenuItem *MenuItemFuncaoImpressora;
	TLabel *LabelNomeVendedor;
	TComboBox *ComboBoxNomeVendedor;
	TLabel *LabelCodigoProduto;
	TEdit *EditCodigoProduto;
	TLabel *LabelQuantidade;
	TLabel *LabelIcms;
	TComboBox *ComboBoxIcms;
	TBitBtn *BitBtnConfirmaProduto;
	TBitBtn *BitBtnCancelaProduto;
	TImage *ImageConsigo;
	TLabel *LabelSlogan;
	TStringGrid *StringGridProdutos;
	TBitBtn *BitBtnImprimeCupom;
	TLabel *LabelTotal;
	TEdit *EditTotal;
	TDatabase *DatabaseConsigo;
	TQuery *QueryProdutos;
	TLabel *LabelPreco;
	TEdit *EditPreco;
	TEdit *EditQuantidade;
	void __fastcall MenuItemSairClick(TObject *Sender);
	void __fastcall EmissodeCupom1Click(TObject *Sender);
	void __fastcall MenuItemFuncaoImpressoraClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BitBtnConfirmaProdutoClick(TObject *Sender);
	void __fastcall BitBtnCancelaProdutoClick(TObject *Sender);
	void __fastcall BitBtnImprimeCupomClick(TObject *Sender);
	void __fastcall ComboBoxNomeVendedorKeyPress(TObject *Sender, char &Key);
	void __fastcall ComboBoxIcmsKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TFormImpressora(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImpressora *FormImpressora;
//---------------------------------------------------------------------------
#endif
