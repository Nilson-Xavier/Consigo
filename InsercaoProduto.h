//---------------------------------------------------------------------------
#ifndef InsercaoProdutoH
#define InsercaoProdutoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Mask.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\DBGrids.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\FileCtrl.hpp>
#include <vcl\DBCtrls.hpp>
#include <vcl\DB.hpp>
#include <vcl\DBTables.hpp>
#include "jpeg.hpp"
//---------------------------------------------------------------------------
class TFormInsercaoProduto : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TMainMenu *MainMenu1;
	TMenuItem *Atalhos10;
  TMenuItem *MenuItemSair1;
	TMenuItem *Inserao1;
	TTabSheet *TabSheet2;
	TMenuItem *Fotos1;
	TPanel *Panel2;
	TDriveComboBox *DriveComboBox1;
	TDirectoryListBox *DirectoryListBox1;
	TFileListBox *FileListBox1;
	TPanel *Panel3;
	TImage *Image3;
	TLabel *Label10;
	TTabSheet *TabSheet1;
	TPanel *Panel4;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label1;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TEdit *Edit7;
	TEdit *Edit8;
	TEdit *Edit9;
	TLabel *Label2;
	TEdit *Edit10;
	TLabel *Label3;
	TEdit *Edit11;
	TLabel *Label4;
	TEdit *Edit12;
	TBitBtn *BitBtn1;
  TTabSheet *TabSheetCheque;
  TMenuItem *DescontodeCheques1;
  TGroupBox *GroupBoxCheque;
  TEdit *EditContato;
  TLabel *LabelContato;
  TLabel *LabelTelefone;
  TEdit *EditTelefone;
  TLabel *LabelBanco;
  TEdit *EditBanco;
  TLabel *LabelAgencia;
  TEdit *EditAgencia;
  TLabel *LabelConta;
  TEdit *EditConta;
  TLabel *LabelDV;
  TMaskEdit *MaskEditDV;
  TBitBtn *BitBtnImprimirCheque;
  TStringGrid *StringGridCheque;
	void __fastcall Inserao1Click(TObject *Sender);
	void __fastcall Fotos1Click(TObject *Sender);
	void __fastcall MenuItemSair1Click(TObject *Sender);
	
	
	


	
	
	
	
	
	
	
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit3KeyPress(TObject *Sender, char &Key);
	
	void __fastcall Edit4KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit5KeyPress(TObject *Sender, char &Key);
	
	void __fastcall Edit6KeyPress(TObject *Sender, char &Key);
	
	void __fastcall Edit7KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit8KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit9KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit10KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit11KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit12KeyPress(TObject *Sender, char &Key);
  void __fastcall FormCreate(TObject *Sender);
	void __fastcall FileListBox1KeyPress(TObject *Sender, char &Key);
	void __fastcall FileListBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall DriveComboBox1KeyPress(TObject *Sender, char &Key);
  void __fastcall DescontodeCheques1Click(TObject *Sender);
  void __fastcall StringGridChequeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall BitBtnImprimirChequeClick(TObject *Sender);
	
	
private:	// User declarations
  TJPEGImage *JpegImage2;
public:		// User declarations
	__fastcall TFormInsercaoProduto(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormInsercaoProduto *FormInsercaoProduto;
//---------------------------------------------------------------------------
#endif
