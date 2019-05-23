//---------------------------------------------------------------------------
#ifndef CadastroClienteH
#define CadastroClienteH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Mask.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormInsercaoCliente : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TMainMenu *MainMenu2;
  TMenuItem *MenuItemSair;
  TLabel *LabelCadastroCliente;
  TImage *ImageConsigo;
  TLabel *LabelACertezaDeUmBomNegocio;
  TLabel *LabelNome;
  TEdit *EditNome;
  TLabel *LabelEndereco;
  TEdit *EditEndereco;
  TLabel *LabelBairro;
  TEdit *EditBairro;
  TLabel *LabelCidade;
  TEdit *EditCidade;
  TLabel *LabelEstado;
  TLabel *LabelCep;
  TLabel *LabelTelefone;
  TLabel *LabelTelefoneComercial;
  TLabel *LabelFax;
	TLabel *Label12;
  TEdit *EditRgCnpj;
  TLabel *LabelCpf;
  TEdit *EditCpf;
  TBitBtn *BitBtnInserirCliente;
  TBitBtn *BitBtnVoltar;
  TLabel *LabelInscricaoEstadual;
  TEdit *EditInscricaoEstadual;
	TMenuItem *Atalhos1;
  TMenuItem *MenuItemInserirCliente;
	TLabel *Label15;
	TLabel *LabelEmail;
	TEdit *EditEmail;
  TLabel *LabelObservacao;
	TMemo *MemoObservacaoCliente;
  TComboBox *ComboBoxEstado;
  TEdit *EditCep;
  TEdit *EditTelefone;
  TEdit *EditTelefoneComercial;
  TEdit *EditTelefoneFax;
  TComboBox *ComboBoxEERG;

	void __fastcall BitBtnVoltarClick(TObject *Sender);
	void __fastcall BitBtnInserirClienteClick(TObject *Sender);
	void __fastcall EditEnderecoKeyPress(TObject *Sender, char &Key);
	void __fastcall EditBairroKeyPress(TObject *Sender, char &Key);
	void __fastcall EditCidadeKeyPress(TObject *Sender, char &Key);
	void __fastcall EditRgCnpjKeyPress(TObject *Sender, char &Key);
	void __fastcall EditCpfKeyPress(TObject *Sender, char &Key);
	void __fastcall EditInscricaoEstadualKeyPress(TObject *Sender, char &Key);
	void __fastcall MenuItemSairClick(TObject *Sender);
	void __fastcall EditEmailKeyPress(TObject *Sender, char &Key);
  void __fastcall EditNomeKeyPress(TObject *Sender, char &Key);
  void __fastcall ComboBoxEstadoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall EditCepKeyPress(TObject *Sender, char &Key);
  void __fastcall EditTelefoneKeyPress(TObject *Sender, char &Key);
  void __fastcall EditTelefoneComercialKeyPress(TObject *Sender,
          char &Key);
  void __fastcall EditTelefoneFaxKeyPress(TObject *Sender, char &Key);
  void __fastcall ComboBoxEERGKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall MemoObservacaoClienteKeyPress(TObject *Sender,
          char &Key);
	
	
private:	// User declarations
public:		// User declarations
	__fastcall TFormInsercaoCliente(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormInsercaoCliente *FormInsercaoCliente;
//---------------------------------------------------------------------------
#endif
