//---------------------------------------------------------------------------
#ifndef CadastroFornecedorH
#define CadastroFornecedorH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Mask.hpp>
#include <vcl\Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormInserirFornecedor : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *SairESC1;
	TPanel *Panel1;
	TLabel *Label1;
  TLabel *LabelNome;
  TEdit *EditNome;
  TLabel *LabelCnpj;
  TEdit *EditCnpj;
  TLabel *LabelInscricaoEtadual;
  TEdit *EditInscricaoEstadual;
  TLabel *LabelEndereco;
  TEdit *EditEndereco;
  TLabel *LabelBairro;
  TEdit *EditBairro;
  TLabel *LabelCidade;
  TEdit *EditCidade;
  TLabel *LabelEstado;
  TLabel *LabelCep;
  TLabel *LabelTelefone;
  TLabel *LabelFax;
  TBitBtn *BitBtnInserirFornecedor;
  TBitBtn *BitBtnVoltar;
	TImage *Image1;
	TLabel *Label12;
  TLabel *LabelObservacao;
	TMemo *MemoObservacao;
  TComboBox *ComboBoxEstado;
  TEdit *EditCep;
  TEdit *EditTelefone;
  TEdit *EditFax;
	void __fastcall SairESC1Click(TObject *Sender);
	
	
	
	void __fastcall BitBtnInserirFornecedorClick(TObject *Sender);
	void __fastcall BitBtnVoltarClick(TObject *Sender);
	void __fastcall EditNomeKeyPress(TObject *Sender, char &Key);
	void __fastcall EditCnpjKeyPress(TObject *Sender, char &Key);
	void __fastcall EditInscricaoEstadualKeyPress(TObject *Sender, char &Key);
	void __fastcall EditEnderecoKeyPress(TObject *Sender, char &Key);
	void __fastcall EditBairroKeyPress(TObject *Sender, char &Key);
	void __fastcall EditCidadeKeyPress(TObject *Sender, char &Key);
  void __fastcall ComboBoxEstadoKeyPress(TObject *Sender, char &Key);
  void __fastcall EditCepKeyPress(TObject *Sender, char &Key);
  void __fastcall EditTelefoneKeyPress(TObject *Sender, char &Key);
  void __fastcall EditFaxKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TFormInserirFornecedor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormInserirFornecedor *FormInserirFornecedor;
//---------------------------------------------------------------------------
#endif
