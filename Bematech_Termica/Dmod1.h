//---------------------------------------------------------------------------
#ifndef Dmod1H
#define Dmod1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\DB.hpp>
#include <vcl\DBTables.hpp>
#include <Db.hpp>
//---------------------------------------------------------------------------
class TDataModuleQuery : public TDataModule
{
__published:	// IDE-managed Components
  TQuery *Produtos;
	TDataSource *DataSource15;
	TQuery *Query15;
	TDatabase *consigo_BD;
  TStringField *ProdutosCodigo;
  TStringField *ProdutosMarca;
  TStringField *ProdutosNome;
  TIntegerField *ProdutosQuantidade;
  TIntegerField *ProdutosQuantidade_;
  TFloatField *ProdutosCusto_Anterior;
  TFloatField *ProdutosCusto_Atual;
  TStringField *ProdutosGarantia;
  TFloatField *ProdutosDolar;
  TFloatField *ProdutosPreco;
  TStringField *ProdutosPath;
  TStringField *ProdutosArquivo;
  TFloatField *ProdutosPreco2;
	void __fastcall Query15BeforeEdit(TDataSet *DataSet);
	void __fastcall Query15AfterPost(TDataSet *DataSet);
	void __fastcall Query15PostError(TDataSet *DataSet, EDatabaseError *E,
	TDataAction &Action);
	void __fastcall DataModuleCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDataModuleQuery(TComponent* Owner);
};
//---------------------------------------------------------------------------
class TConsigoQuery : public TQuery {
  private:

  public:
    __fastcall TConsigoQuery( String* DataBaseName, TComponent* AOwner );
};
//---------------------------------------------------------------------------
extern TDataModuleQuery *DataModuleQuery;
//---------------------------------------------------------------------------
#endif

 