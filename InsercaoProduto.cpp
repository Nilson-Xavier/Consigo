//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "InsercaoProduto.h"
#include "ImpressaoDescontoCheque.h"
#include "Main.h"
#include "Dmod1.h"
#include "Dmod2.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormInsercaoProduto *FormInsercaoProduto;
//---------------------------------------------------------------------------
__fastcall TFormInsercaoProduto::TFormInsercaoProduto( TComponent* Owner )
  : TForm( Owner ) {

}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Inserao1Click( TObject *Sender ) {

  PageControl1->ActivePage = TabSheet1;
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Fotos1Click( TObject *Sender ) {

  PageControl1->ActivePage = TabSheet2;
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::MenuItemSair1Click( TObject *Sender ) {

  FormInsercaoProduto->Close( );
  FormInsercaoProduto = NULL;
  delete FormInsercaoProduto;
  FormPrincipal->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::BitBtn1Click( TObject *Sender ) {

  TCursor SaveCursor;
  String Preco;

  if( ( Edit1->Text == "" ) || ( Edit2->Text == "" ) || ( Edit3->Text == "" ) ) {
     Application->MessageBox( "O Produto a ser inserido DEVE ter CODIGO, MARCA e NOME!",
     													"Inserção de Produtos", MB_OK | MB_ICONWARNING );
  }
  else {
  	try {
			SaveCursor = Screen->Cursor;
			Screen->Cursor = crHourGlass;
      this->Enabled = false;

	  	try {
		    DataModuleQuery->Produtos->Close( );
  		  DataModuleQuery->Produtos->Prepare( );
    		DataModuleQuery->Produtos->ParamByName( "Codigo" )->AsString = Trim( Edit1->Text );
		    DataModuleQuery->Produtos->ParamByName( "Marca" )->AsString = "%";
  		  DataModuleQuery->Produtos->ParamByName( "Nome" )->AsString = "%";
    		DataModuleQuery->Produtos->Open( );
	  		if( !DataModuleQuery->Produtos->IsEmpty( ) ) {
  	  		 MessageDlg( "O Codigo: " + Trim( Edit1->Text ) + " já existe!!!\r\rO Produto não será inserido!",
    	  		           mtWarning, TMsgDlgButtons( ) << mbOK, 0 );
	    		Edit1->SetFocus( );
		  	}
  			else if ( MessageBox( Handle, "Você digitou todos os campos CORRETAMENTE?",
    			                    "Inserção de Produtos", MB_YESNO | MB_ICONQUESTION ) == ID_YES ) {

	      	DataModuleQuery->consigo_BD->StartTransaction( );
		  	  DataModuleQuery2->InsereProduto->Prepare( );
  			  DataModuleQuery2->InsereProduto->ParamByName( "Codigo" )->AsString = Trim( Edit1->Text );
  			  DataModuleQuery2->InsereProduto->ParamByName( "Marca" )->AsString = Trim( Edit2->Text );
      		DataModuleQuery2->InsereProduto->ParamByName( "Nome" )->AsString = Trim( Edit3->Text );
		      DataModuleQuery2->InsereProduto->ParamByName( "Quantidade" )->AsInteger = Trim( Edit4->Text ).ToInt( );
  			  DataModuleQuery2->InsereProduto->ParamByName( "Quantidade_" )->AsInteger = Trim( Edit5->Text ).ToInt( );
          Preco = Trim( Edit6->Text );
          Preco = StringReplace( Preco, ".", "", TReplaceFlags( ) << rfReplaceAll );
          Preco = StringReplace( Preco, ",", ".", TReplaceFlags( ) << rfReplaceAll );
          ThousandSeparator = ',';
          DecimalSeparator = '.';
  			  DataModuleQuery2->InsereProduto->ParamByName( "Custo_Anterior" )->AsFloat = StrToFloat( Preco );
          Preco = Trim( Edit7->Text );
          Preco = StringReplace( Preco, ".", "", TReplaceFlags( ) << rfReplaceAll );
          Preco = StringReplace( Preco, ",", ".", TReplaceFlags( ) << rfReplaceAll );
          ThousandSeparator = ',';
          DecimalSeparator = '.';
  	  		DataModuleQuery2->InsereProduto->ParamByName( "Custo_Atual" )->AsFloat = StrToFloat( Preco );
          Preco = Trim( Edit8->Text );
          Preco = StringReplace( Preco, ".", "", TReplaceFlags( ) << rfReplaceAll );
          Preco = StringReplace( Preco, ",", ".", TReplaceFlags( ) << rfReplaceAll );
          ThousandSeparator = ',';
          DecimalSeparator = '.';
	  	  	DataModuleQuery2->InsereProduto->ParamByName( "Preco" )->AsFloat = StrToFloat( Preco );
	  		  DataModuleQuery2->InsereProduto->ParamByName( "Garantia" )->AsString = Trim( Edit9->Text );
          Preco = Trim( Edit10->Text );
          Preco = StringReplace( Preco, ".", "", TReplaceFlags( ) << rfReplaceAll );
          Preco = StringReplace( Preco, ",", ".", TReplaceFlags( ) << rfReplaceAll );
          ThousandSeparator = ',';
          DecimalSeparator = '.';
  			  DataModuleQuery2->InsereProduto->ParamByName( "Dolar" )->AsFloat = StrToFloat( Preco );;
    	  	DataModuleQuery2->InsereProduto->ParamByName( "Path" )->AsString = Trim( Edit11->Text );
	  		  DataModuleQuery2->InsereProduto->ParamByName( "Arquivo" )->AsString = Trim( Edit12->Text );
  	    	DataModuleQuery2->InsereProduto->ExecSQL( );
	    	  DataModuleQuery->consigo_BD->Commit( );

			  	Edit1->Text = "";
  				Edit2->Text = "";
			  	Edit3->Text = "";
  				Edit4->Text = "";
		  		Edit5->Text = "";
	  			Edit6->Text = "";
			  	Edit7->Text = "";
  				Edit8->Text = "";
		  		Edit9->Text = "";
  				Edit12->Text = "";
  	    }
    	  DataModuleQuery->Produtos->Close( );
	    }
  	  catch( Exception &e ) {
    		DataModuleQuery->Produtos->Close( );
      	if( DataModuleQuery->consigo_BD->InTransaction ) {
        	DataModuleQuery->consigo_BD->Rollback( );
	      }
  	    Application->MessageBox( e.Message.c_str( ), "Inserção de Produtos", MB_OK | MB_ICONERROR );
    	}
    }
    __finally {
    	Screen->Cursor = SaveCursor;
      this->Enabled = true;
      Edit1->SetFocus( );
    }
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit1KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit2->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit2KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit3->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit3KeyPress( TObject *Sender, char &Key ) {

  if ( Key == 13 ){
    Edit4->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit4KeyPress( TObject *Sender, char &Key ) {

  if ( Key == 13 ){
    Edit5->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit5KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit6->SetFocus( );
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit6KeyPress(TObject *Sender, char &Key)
{
   if ( Key == 13 ) {
      Edit7->SetFocus();
   }

}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit7KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit8->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit8KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit9->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit9KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit10->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit10KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit11->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit11KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    Edit12->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::Edit12KeyPress( TObject *Sender, char &Key ) {

  if( Key == 13 ){
    BitBtn1->SetFocus( );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::FormCreate( TObject *Sender ) {

  JpegImage2 = new TJPEGImage( );

  StringGridCheque->ColCount = 6;
  StringGridCheque->FixedRows = 1;
  StringGridCheque->RowCount = 2;
  StringGridCheque->Cells[0][0] = "Banco";
  StringGridCheque->ColWidths[0] = 80;
  StringGridCheque->Cells[1][0] = "Agência";
  StringGridCheque->ColWidths[1] = 110;
  StringGridCheque->Cells[2][0] = "Conta";
  StringGridCheque->ColWidths[2] = 120;
  StringGridCheque->Cells[3][0] = "Nº Cheque";
  StringGridCheque->ColWidths[3] = 120;
  StringGridCheque->Cells[4][0] = "Valor R$";
  StringGridCheque->ColWidths[4] = 90;
  StringGridCheque->Cells[5][0] = "Data p/ Depósito";
  StringGridCheque->ColWidths[5] = 140;

}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::FileListBox1KeyPress(TObject *Sender,
  char &Key ) {

  if( ( Key == 13 ) || ( Key == ' ' ) ) {
		JpegImage2->LoadFromFile( FileListBox1->FileName );
		Image3->Picture->Assign( JpegImage2 );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::FileListBox1MouseDown(
	TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
  int Y) {

  if( Button == mbLeft ) {
		JpegImage2->LoadFromFile( FileListBox1->FileName );
		Image3->Picture->Assign( JpegImage2 );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::DriveComboBox1KeyPress( TObject *Sender, char &Key ) {

	if( ( Key == ' ' ) || ( Key == VK_DOWN	) || ( Key == VK_UP ) ){
  	DriveComboBox1->DroppedDown = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::DescontodeCheques1Click( TObject *Sender )  {

  PageControl1->ActivePage = TabSheetCheque;
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::StringGridChequeKeyDown( TObject *Sender,
  WORD &Key, TShiftState Shift ) {

  if( ( Key == 40 ) && ( StringGridCheque->Row == StringGridCheque->RowCount - 1 ) &&
      ( ( StringGridCheque->Rows[StringGridCheque->Row]->Text ).Length( ) > 12 ) ) {
    StringGridCheque->RowCount++;
    StringGridCheque->Row = StringGridCheque->RowCount - 1;
    StringGridCheque->Col = 0;
  }
  if( ( Key == 38 ) && ( StringGridCheque->Row == StringGridCheque->RowCount - 1 ) &&
      ( ( StringGridCheque->Rows[StringGridCheque->Row]->Text ).Length( ) <= 12 ) &&
      ( StringGridCheque->RowCount > 2 ) ) {
    StringGridCheque->RowCount--;
    StringGridCheque->Row = StringGridCheque->RowCount - 1;
    StringGridCheque->Col = 0;
  }
  if( ( Key == 13 ) && ( StringGridCheque->Col != 5 ) ) {
    StringGridCheque->Col = StringGridCheque->Col + 1;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInsercaoProduto::BitBtnImprimirChequeClick( TObject *Sender ) {

  TCursor SaveCursor;
  TDateTime *Data;
  String Contador, TotalPorData;
  int i;
  float Total, TotalData;

  try {
  	SaveCursor = Screen->Cursor;
		Screen->Cursor = crHourGlass;
    this->Enabled = false;
    FormImpressaoCheque = new TFormImpressaoCheque( FormPrincipal );
    Data = new TDateTime( );

    if( ( Trim( EditContato->Text ) == "" ) || ( Trim( EditTelefone->Text ) == "" ) ||
        ( Trim( EditBanco->Text ) == "" ) || ( Trim( EditAgencia->Text ) == "" ) ||
        ( Trim( EditConta->Text ) == "" ) || ( Trim( MaskEditDV->Text ) == "" ) ||
        ( StringGridCheque->RowCount == 1 ) ) {
      Application->MessageBox( "Faltam Dados para a Impressão do Protocolo !!!",
        "Desconto de Cheques", MB_OK | MB_ICONERROR );
    }
    else {
      try {
        FormImpressaoCheque->QRMemoContato->Lines->Append( Trim( EditContato->Text ) );
        FormImpressaoCheque->QRMemoTelefone->Lines->Append( Trim( EditTelefone->Text ) );
        FormImpressaoCheque->QRMemoCodBanco->Lines->Append( Trim( EditBanco->Text ) );
        FormImpressaoCheque->QRMemoCodAgencia->Lines->Append( Trim( EditAgencia->Text ) );
        FormImpressaoCheque->QRMemoCodConta->Lines->Append( Trim( EditConta->Text ) );
        FormImpressaoCheque->QRMemoDV->Lines->Append( Trim( MaskEditDV->Text ) );

        Total = 0;
        TotalData = 0;
        *Data = StrToDate( StringGridCheque->Cells[5][1] );

        for( i = 1; i < StringGridCheque->RowCount; i++ ) {
          ThousandSeparator = '.';
          DecimalSeparator = ',';
          Total = Total + StrToFloat( StringReplace( StringGridCheque->Cells[4][i], ".", "", TReplaceFlags( ) << rfReplaceAll ) );

          StringGridCheque->Cells[4][i] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( StringGridCheque->Cells[4][i], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
          StringGridCheque->Cells[5][i] = FormatDateTime( "dd/mm/yyyy",StrToDate( StringGridCheque->Cells[5][i] ) );

          Contador = IntToStr( i );
          while( Contador.Length( ) < 4 ) {
            Contador = Contador + " ";
          }
          while( ( StringGridCheque->Cells[0][i] ).Length( ) < 4 ) {
            StringGridCheque->Cells[0][i] = StringGridCheque->Cells[0][i] + " ";
          }
          while( ( StringGridCheque->Cells[1][i] ).Length( ) < 5 ) {
            StringGridCheque->Cells[1][i] = StringGridCheque->Cells[1][i] + " ";
          }
          while( ( StringGridCheque->Cells[2][i] ).Length( ) < 13 ) {
            StringGridCheque->Cells[2][i] = StringGridCheque->Cells[2][i] + " ";
          }
          while( ( StringGridCheque->Cells[3][i] ).Length( ) < 9 ) {
            StringGridCheque->Cells[3][i] = StringGridCheque->Cells[3][i] + " ";
          }
          while( ( StringGridCheque->Cells[4][i] ).Length( ) < 10 ) {
            StringGridCheque->Cells[4][i] = StringGridCheque->Cells[4][i] + " ";
          }
          while( ( StringGridCheque->Cells[5][i] ).Length( ) < 11 ) {
            StringGridCheque->Cells[5][i] = StringGridCheque->Cells[5][i] + " ";
          }
          if( *Data != StrToDate( StringGridCheque->Cells[5][i] ) ) {
            *Data = StrToDate( StringGridCheque->Cells[5][i] );
            TotalData = 0;
          }
          TotalData = TotalData + StrToFloat( StringReplace( StringGridCheque->Cells[4][i], ".", "", TReplaceFlags( ) << rfReplaceAll ) );
          if( i == StringGridCheque->RowCount - 1 ) {
            TotalPorData = FormatFloat( "#,##0.00", StrToFloat( StringReplace( TotalData, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
            while( TotalPorData.Length( ) < 9 ) {
              TotalPorData = TotalPorData + " ";
            }
          }
          else {
            if( *Data != StrToDate( StringGridCheque->Cells[5][i+1] ) ) {
              TotalPorData = FormatFloat( "#,##0.00", StrToFloat( StringReplace( TotalData, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
              while( TotalPorData.Length( ) < 9 ) {
                    TotalPorData = TotalPorData + " ";
              }
            }
            else {
              TotalPorData = "          ";
            }
          }

          FormImpressaoCheque->QRStringsBand1->Items->Append( Contador + StringGridCheque->Cells[0][i] +
            StringGridCheque->Cells[1][i] + StringGridCheque->Cells[2][i] + StringGridCheque->Cells[3][i] +
            StringGridCheque->Cells[4][i] + StringGridCheque->Cells[5][i] + TotalPorData );
        }

        FormImpressaoCheque->QRMemoQuantidade->Lines->Append( IntToStr( StringGridCheque->RowCount - 1 ) );
        FormImpressaoCheque->QRMemoTotal->Lines->Append( "R$ " + FormatFloat( "#,##0.00", Total ) );
        FormImpressaoCheque->QRLabelTotal2->Caption = "R$ " + FormatFloat( "#,##0.00", Total );
        FormImpressaoCheque->QRLabelData3->Caption = FormatDateTime( "dd/mm/yyyy", Data->CurrentDate( ) );

        //FormImpressaoCheque->QuickRepCheque->PrinterSetup( );
        FormImpressaoCheque->QuickRepCheque->Preview( );

        if( Application->MessageBox( "A Impressão do Protocolo está Correta ?", "Desconto de Cheques", MB_YESNO | MB_ICONQUESTION ) == 6 ) {
          EditContato->Clear( );
          EditTelefone->Clear( );
          EditBanco->Clear( );
          EditAgencia->Clear( );
          EditConta->Clear( );
          MaskEditDV->Clear( );
          for( i = 1; i < StringGridCheque->RowCount; i++ ) {
            StringGridCheque->Rows[i]->Clear( );
          }
        }
      }
      catch( Exception &e ) {
        Application->MessageBox( e.Message.c_str( ), "Desconto de Cheques", MB_OK | MB_ICONERROR );
      }
    }
  }
  __finally {
    delete Data;
    delete FormImpressaoCheque;
   	Screen->Cursor = SaveCursor;
    this->Enabled = true;
  }
}
//---------------------------------------------------------------------------

