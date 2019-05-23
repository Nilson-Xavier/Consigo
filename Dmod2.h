//---------------------------------------------------------------------------
#ifndef Dmod2H
#define Dmod2H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\DBTables.hpp>
#include <vcl\DB.hpp>
#include <Db.hpp>
//---------------------------------------------------------------------------
class TDataModuleQuery2 : public TDataModule
{
__published:	// IDE-managed Components
  TQuery *InsereProduto;

private:	// User declarations
public:		// User declarations
	__fastcall TDataModuleQuery2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TDataModuleQuery2 *DataModuleQuery2;
//---------------------------------------------------------------------------
#endif
