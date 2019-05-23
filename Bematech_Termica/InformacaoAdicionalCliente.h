//---------------------------------------------------------------------------
#ifndef InformacaoAdicionalClienteH
#define InformacaoAdicionalClienteH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\DBGrids.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\Mask.hpp>
//---------------------------------------------------------------------------
class TFormInformacaoAdicionalCliente : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TMainMenu *MainMenu1;
	TMenuItem *SairESC1;
	TLabel *Label1;
	TLabel *Label3;
	TBitBtn *BitBtnVoltar;
	TMemo *MemoObesrvacaoCliente;
	TStringGrid *StringGridClienteInfo;
	TLabel *LabelObservacao;
  TComboBox *ComboBoxNomeCliente;
	void __fastcall SairESC1Click(TObject *Sender);
	void __fastcall BitBtnVoltarClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
  void __fastcall ComboBoxNomeClienteKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TFormInformacaoAdicionalCliente(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormInformacaoAdicionalCliente *FormInformacaoAdicionalCliente;
//---------------------------------------------------------------------------
#endif
