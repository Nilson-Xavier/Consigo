//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("Main.cpp", FormPrincipal);
USEFORM("Dmod2.cpp", DataModuleQuery2); /* TDataModule: File Type */
USEFORM("ImpressaoDespesa.cpp", FormImpressaoDespesa);
USEFORM("ImpressaoCotacaoPreco.cpp", FormCotacaoPreco);
USEFORM("InsercaoProduto.cpp", FormInsercaoProduto);
USEFORM("CadastroCliente.cpp", FormInsercaoCliente);
USEFORM("InformacaoAdicionalCliente.cpp", FormInformacaoAdicionalCliente);
USEFORM("Gerencia.cpp", FormGerencia);
USEFORM("CadastroFornecedor.cpp", FormInserirFornecedor);
USEFORM("ImpressaoFechamentoVendedor.cpp", FormImpressaoFechamentoVendedor);
USEFORM("ImpressaoEntradaProduto.cpp", FormImpressaoEntradaProduto);
USEFORM("ImpressaoEntradaProduto2.cpp", FormImpressaoEntradaProduto2);
USEFORM("Dmod1.cpp", DataModuleQuery); /* TDataModule: File Type */
USEFORM("ImpressaoFechamentoVendedor2.cpp", FormImpressaoFechamentoVendedor2);
USEFORM("ImpressaoListaPreco.cpp", FormImpressaoListaPreco);
USEFORM("ImpressaoDescontoCheque.cpp", FormImpressaoCheque);
USEFORM("DescontoProduto.cpp", FormDescontoProduto);
USEFORM("Senha.cpp", FormPassword);
USEFORM("FormTef.cpp", FormMensagemTef);
USEFORM("ValorCartao.cpp", FormValorCartao);
USEFORM("FormaPagamento.cpp", FormFormaPagamento);
USEFORM("OrdemDeServico.cpp", FormOrdemDeServico);
//---------------------------------------------------------------------------
WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {

  try {
    Application->Initialize( );
     Application->CreateForm(__classid(TDataModuleQuery), &DataModuleQuery);
     Application->CreateForm(__classid(TDataModuleQuery2), &DataModuleQuery2);
     Application->CreateForm(__classid(TFormPrincipal), &FormPrincipal);
     Application->CreateForm(__classid(TFormGerencia), &FormGerencia);
     Application->Run( );
  }
  catch( Exception &exception ) {
    Application->ShowException( &exception );
  }
  return 0;
}
//---------------------------------------------------------------------------


