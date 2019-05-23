//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ImpressoraFiscal.h"
#include "ImpressoraFiscalEcf.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormImpressora *FormImpressora;

//---------------------------------------------------------------------------
__fastcall TFormImpressora::TFormImpressora( TComponent* Owner )
	: TForm( Owner ) {
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::MenuItemSairClick( TObject *Sender ) {
	Application->Terminate( );
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::EmissodeCupom1Click( TObject *Sender ) {
	PageControlImpressora->ActivePage = TabSheetEmissaoCupom;
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::MenuItemFuncaoImpressoraClick(
      TObject *Sender ) {
	PageControlImpressora->ActivePage = TabSheetFuncaoImpressora;
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::FormCreate( TObject *Sender ) {
  try {
	  DatabaseConsigo->Open( );
  }
  catch( Exception &e ) {
  	MessageDlg( e.Message, mtError, TMsgDlgButtons( ) << mbOK, 0 );
    Application->Terminate( );
  }

  StringGridProdutos->RowCount = 1;
  StringGridProdutos->ColCount = 7;
  StringGridProdutos->Cells[0][0] = "Marca";
  StringGridProdutos->ColWidths[0] = 170;
  StringGridProdutos->Cells[1][0] = "Nome";
  StringGridProdutos->ColWidths[1] = 430;
  StringGridProdutos->Cells[2][0] = "Qtd";
  StringGridProdutos->ColWidths[2] = 52;
  StringGridProdutos->Cells[3][0] = "Preço Unit. R$";
  StringGridProdutos->ColWidths[3] = 120;
  StringGridProdutos->Cells[4][0] = "Preço R$";
  StringGridProdutos->ColWidths[4] = 110;
  StringGridProdutos->Cells[5][0] = "Código";
  StringGridProdutos->ColWidths[5] = 180;
  StringGridProdutos->Cells[6][0] = "Garantia";
  StringGridProdutos->ColWidths[6] = 180;
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::BitBtnConfirmaProdutoClick( TObject *Sender ) {

	if( ( Trim( EditCodigoProduto->Text ) == "" ) || ( Trim( EditQuantidade->Text ) == "" ) ) {
  	Application->MessageBox( "O campo Código ou Quantidade está Vazio!",
    												 "Emissão de Cupom", MB_OK | MB_ICONERROR );
  }
  else {
  	try {
    	QueryProdutos->Prepare( );
      QueryProdutos->ParamByName( "Codigo" )->AsString = Trim( EditCodigoProduto->Text );
      QueryProdutos->Open( );
      if( QueryProdutos->IsEmpty( ) ) {
      	throw Exception( "Produto Inexistente!!!" );
      }
      else {
        QueryProdutos->First( );
      	while( !QueryProdutos->Eof ) {
	      	StringGridProdutos->RowCount++;
  	      StringGridProdutos->Cells[0][StringGridProdutos->RowCount - 1] = QueryProdutos->FieldByName( "Marca" )->AsString;
    	    StringGridProdutos->Cells[1][StringGridProdutos->RowCount - 1] = QueryProdutos->FieldByName( "Nome" )->AsString;
          while( Trim( EditQuantidade->Text ).SubString( 1, 1 ) == '0' ) {
          	Trim( EditQuantidade->Text ).Delete( 1, 1 );
          }
        	StringGridProdutos->Cells[2][StringGridProdutos->RowCount - 1] = Trim( EditQuantidade->Text );
	        ThousandSeparator = '.';
  	      DecimalSeparator = ',';
          if( Trim( EditPreco->Text ) == "" ) {
          	StringGridProdutos->Cells[3][StringGridProdutos->RowCount - 1] = FormatFloat( "#,##0.00", ( QueryProdutos->FieldByName( "Preco" )->AsFloat * QueryProdutos->FieldByName( "Dolar" )->AsFloat ) );
          }
          else {
	          StringGridProdutos->Cells[3][StringGridProdutos->RowCount - 1] = FormatFloat( "#,##0.00", StrToFloat( StringReplace( Trim( EditPreco->Text ), ".", "", TReplaceFlags( ) << rfReplaceAll ) ) );
          }
	        ThousandSeparator = '.';
  	      DecimalSeparator = ',';
    	    StringGridProdutos->Cells[4][StringGridProdutos->RowCount - 1] = FormatFloat( "#,##0.00", ( StrToFloat( StringGridProdutos->Cells[2][StringGridProdutos->RowCount - 1] ) * StrToFloat( StringReplace( StringGridProdutos->Cells[3][StringGridProdutos->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
      	  StringGridProdutos->Cells[5][StringGridProdutos->RowCount - 1] = QueryProdutos->FieldByName( "Codigo" )->AsString;
        	StringGridProdutos->Cells[6][StringGridProdutos->RowCount - 1] = QueryProdutos->FieldByName( "Garantia" )->AsString;
          ThousandSeparator = '.';
 	        DecimalSeparator = ',';
					if( ( Trim( EditTotal->Text ) == "" ) || ( StringGridProdutos->RowCount == 2 ) ) {
            EditTotal->Text = StringGridProdutos->Cells[4][StringGridProdutos->RowCount - 1];
          }
          else {
          	EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( StringGridProdutos->Cells[4][StringGridProdutos->RowCount - 1], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) + StrToFloat( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
          }
          QueryProdutos->Next( );
      	}
        QueryProdutos->Close( );
        EditPreco->Clear( );
        EditQuantidade->Clear( );
        EditCodigoProduto->Clear( );
        EditCodigoProduto->SetFocus( );
      }
    }
    catch( Exception &e ) {
    	QueryProdutos->Close( );
    	Application->MessageBox( e.Message.c_str( ), "Emissão de Cupom", MB_OKCANCEL | MB_ICONERROR );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::BitBtnCancelaProdutoClick( TObject *Sender ) {

	int i, j, k;
  Boolean Ok;

	if( EditCodigoProduto->Text == "" ) {
		Application->MessageBox( "O Campo Código está Vazio!!!", "Emissão de Cupom", MB_OKCANCEL | MB_ICONERROR );
  }
  else if( StringGridProdutos->RowCount == 1 ) {
		Application->MessageBox( "Não há Produto para ser Cancelado!!!", "Emissão de Cupom", MB_OKCANCEL | MB_ICONERROR );
  }
  else {
    for( i = 1; i < StringGridProdutos->RowCount; i++ ) {
      if( StringGridProdutos->Cells[5][i] == Trim( EditCodigoProduto->Text ) ) {
      	if( StringGridProdutos->RowCount == 2 ) {
        	EditTotal->Text = "";
        }
        else {
          ThousandSeparator = '.';
          DecimalSeparator = ',';
    	    EditTotal->Text = FormatFloat( "#,##0.00", ( StrToFloat( StringReplace( EditTotal->Text, ".", "", TReplaceFlags( ) << rfReplaceAll ) ) - StrToFloat( StringReplace( StringGridProdutos->Cells[4][i], ".", "", TReplaceFlags( ) << rfReplaceAll ) ) ) );
        }
      	Ok = true;
        break;
      }
      else {
      	Ok = false;
      }
    }
    if( Ok ) {
      for( j = i + 1; j < StringGridProdutos->RowCount; j++ ) {
      	for( k = 0; k < StringGridProdutos->ColCount; k++ ) {
	      	StringGridProdutos->Cells[k][j-1] = StringGridProdutos->Cells[k][j];
        }
      }
      StringGridProdutos->RowCount--;
      EditQuantidade->Text = "";
      EditCodigoProduto->Text = "";
      EditCodigoProduto->SetFocus( );
    }
    else {
    	Application->MessageBox( "O Código Digitado não está na Venda!!!",
      												 "Emissão de Cupom", MB_OK | MB_ICONERROR );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::BitBtnImprimeCupomClick( TObject *Sender ) {

	TCursor SaveCursor;
	TImpressoraFiscal *impressora;
  String Qtd, Qtde, Preco, CodFiscal, Unidade, Codigo, Descricao, Descricao2; // Lança Item
  String Atrib;
  String Reg, VPgto, Subtr; // Pagamento
  String TamMensagem, Mensagem; // Fechamento do Cupom
  String itens[15][7];
  int i, j, s;

  if( ( ComboBoxNomeVendedor->Text == "" ) ||
  		( ComboBoxIcms->Text == "" ) ) {
  	Application->MessageBox( "Os campos: Nome do Vendedor e ICMS, não estão Preenchidos!!!",
    												 "Emissão de Cupom", MB_OK | MB_ICONERROR );
  }
  else if( StringGridProdutos->RowCount == 1 ) {
    Application->MessageBox( "Não Há Produtos para a Venda!!!", "Emissão de Cupom", MB_OK | MB_ICONERROR );
  }
  else {
    try {
    	SaveCursor = Screen->Cursor;
			Screen->Cursor = crHourGlass;
    	impressora = new TImpressoraFiscal( );
		  try {
	  		impressora->CarregaDll( true );
	  		impressora->ObterStatus( true );

  	  	for( i = 1; i < StringGridProdutos->RowCount; i++ ) {
  	  	  Qtd = StringGridProdutos->Cells[2][i];
    	  	Qtde = Qtd + "000";
	      	s = Qtde.Length( );
		      s = 6 - s;
  		    for( j = 0; j < s; j++ ) {
    		  	Qtde = "0" + Qtde;
      		}
          itens[i-1][0] = Qtde;
		      DecimalSeparator = ',';
  		    ThousandSeparator = '.';
    		  Preco = StringGridProdutos->Cells[3][i];
          Preco = StringReplace( Preco, ".", "", TReplaceFlags( ) << rfReplaceAll );
  		    Preco = FormatFloat( "0.00", Preco.ToDouble( ) );
          Preco = StringReplace( Preco, ",", "", TReplaceFlags( ) << rfReplaceAll );
		      s = Preco.Length( );
  		    s = 11 - s;
    		  for( j = 0; j < s ; j++ ) {
      		 Preco = "0" + Preco;
      		}
		      itens[i-1][1] = Preco;
  	      if( ComboBoxIcms->Text == "5,00%" ) {
    	    	CodFiscal = "T00";
      	  }
        	else if( ComboBoxIcms->Text == "2,15%" ) {
        		CodFiscal = "T01";
	        }
  	      else if( ComboBoxIcms->Text == "3,10%" ) {
    	    	CodFiscal = "T02";
      	  }
        	else if( ComboBoxIcms->Text == "7,00%" ) {
        		CodFiscal = "T04";
	        }
  	      else if( ComboBoxIcms->Text == "12,00%" ) {
    	    	CodFiscal = "T05";
      	  }
        	else if( ComboBoxIcms->Text == "18,00%" ) {
        		CodFiscal = "T03";
	        }
          itens[i-1][2] = CodFiscal;
  	  	  itens[i-1][3] = "&";
    	  	itens[i-1][4] = "000000000000000";
  	    	Codigo = StringGridProdutos->Cells[5][i];
	    	  if( Codigo.Length( ) > 13 ) {
  	    		Codigo = Codigo.Delete( 14, Codigo.Length( ) - 13 );
	  	    }
  	  	  else if( Codigo.Length( ) < 13 ) {
    	  		s = 13 - Codigo.Length( );
      	  	for( j = 0; j < s; j++ ) {
        			Codigo = Codigo + " ";
		        }
  		    }
          itens[i-1][5] = Codigo;
      		if( StringGridProdutos->Cells[6][i] == "" ) {
      			Descricao = StringGridProdutos->Cells[0][i] + " " +
        								StringGridProdutos->Cells[1][i];
		      }
  		    else {
    		  	Descricao = StringGridProdutos->Cells[0][i] + " " +
      		  						StringGridProdutos->Cells[1][i] + " Garantia: " +
        		            StringGridProdutos->Cells[6][i];
		      }
  		    if( Descricao.Length( ) < 114 ) {
    		  	s = 114 - Descricao.Length( );
      		  for( j = 0; j < s; j++ ) {
        			Descricao = Descricao + " ";
	        	}
	  	    }
  	  	  else if( Descricao.Length( ) > 114 ) {
    	  		Descricao = Descricao.Delete( 115, Descricao.Length( ) - 114 );
	    	  }
          itens[i-1][6] = Descricao;
	  	  }
	    	Reg = "00"; // Dinheiro!
		    Preco = EditTotal->Text;
        Preco = StringReplace( Preco, ".", "", TReplaceFlags( ) << rfReplaceAll );
        Preco = StringReplace( Preco, ",", "", TReplaceFlags( ) << rfReplaceAll );
      	s = Preco.Length( );
  	    s = 15 - s;
 	  	  for( j = 0; j < s ; j++ ) {
   	  		Preco = "0" + Preco;
    	  }
 	    	VPgto = Preco;
    	  Subtr = "0";
      	Mensagem = "Vendedor: " + Trim( ComboBoxNomeVendedor->Text );
	      for( j = 0; j < ( 76 - Mensagem.Length( ) ); j++ ) {
 		    	Mensagem = Mensagem + " ";
   		  }
     		Mensagem = Mensagem + "           Concorra a um Colete Profissional!   ";
	      Mensagem = Mensagem + "         CONSIGO - A CERTEZA DE UM BOM NEGOCIO  ";
 		    if( Mensagem.Length( ) >= 100 ) {
   		  	TamMensagem = "S" + String( Mensagem.Length( ) );
     		}
      	else {
 	    		TamMensagem = "S0" + String( Mensagem.Length( ) );
    	  }

        impressora->AbreCupom( true );
        for( i = 0; i < 15; i++ ) {
         	if( itens[i][0].IsEmpty( ) ) {
 	        	break;
          }
          else {
	          impressora->LancaItem( itens[i][0], itens[i][1], itens[i][2], itens[i][3],
             											 itens[i][4], itens[i][5], itens[i][6], true );
          }
        }
        impressora->TotalizaCupom( true );
        impressora->Pagamento( Reg, VPgto, Subtr, true );
        VPgto = "000000000000000";
        impressora->Pagamento( Reg, VPgto, Subtr, true );
        impressora->FechaCupom( TamMensagem, Mensagem, true );
        impressora->FechaSerial( );

  	  	for( i = 1; i < StringGridProdutos->RowCount; i++ ) {
          StringGridProdutos->Rows[i]->Clear( );
 		    }
   		  StringGridProdutos->RowCount = 1;

      	EditCodigoProduto->Text = "";
  	    EditQuantidade->Text = "";
 	  	  EditTotal->Text = "";
	  	}
  		catch( Exception &e ) {
	    	Application->MessageBox( e.Message.c_str( ), "Emissão de Cupom", MB_OK | MB_ICONERROR );
		  }
    }
    __finally {
    	Screen->Cursor = SaveCursor;
    	delete impressora;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::ComboBoxNomeVendedorKeyPress( TObject *Sender,
	char &Key ) {

   if ( Key == ' ' ) {
   	ComboBoxNomeVendedor->DroppedDown = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormImpressora::ComboBoxIcmsKeyPress(TObject *Sender,
  char &Key) {

   if ( Key == ' ' ) {
   	ComboBoxIcms->DroppedDown = true;
   }
}
//---------------------------------------------------------------------------

