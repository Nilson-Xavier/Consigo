//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Dmod1.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDataModuleQuery *DataModuleQuery;
//---------------------------------------------------------------------------
__fastcall TDataModuleQuery::TDataModuleQuery( TComponent* Owner ) : TDataModule( Owner ) {

}
//---------------------------------------------------------------------------
void __fastcall TDataModuleQuery::Query15BeforeEdit( TDataSet *DataSet ) {

  DataModuleQuery->consigo_BD->StartTransaction( );
}
//---------------------------------------------------------------------------
void __fastcall TDataModuleQuery::Query15AfterPost( TDataSet *DataSet ) {

  DataModuleQuery->consigo_BD->Commit( );
}
//---------------------------------------------------------------------------
void __fastcall TDataModuleQuery::Query15PostError(TDataSet *DataSet,
	EDatabaseError *E, TDataAction &Action ) {

  DataModuleQuery->consigo_BD->Rollback( );
}
//---------------------------------------------------------------------------
void __fastcall TDataModuleQuery::DataModuleCreate( TObject *Sender ) {

	try {
		DataModuleQuery->consigo_BD->Open( );
  }
  catch( Exception &e ) {
    Application->MessageBox( e.Message.c_str( ), "CONSIGO Client DataBase Manager v1.0",
    												 MB_OK | MB_ICONERROR );
    Application->Terminate( );
  }
}
//---------------------------------------------------------------------------
__fastcall TConsigoQuery::TConsigoQuery( String* DatabaseName, TComponent* AOwner ): TQuery( AOwner ) {

  this->DatabaseName = *DatabaseName;
}
//---------------------------------------------------------------------------

