//---------------------------------------------------------------------------
#ifndef ImpressoraMecafH
#define ImpressoraMecafH
//---------------------------------------------------------------------------
#include <vcl\Windows.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Sysutils.hpp>
//---------------------------------------------------------------------------
// Funções da Impressora MECAF

// Obtém Status da Impressora
typedef int ( WINAPI *CPByteStatus ) ( void );
// Obtém o Estado da Impressora
typedef int ( WINAPI *CPStatusImp ) ( void );
// Inicia a Impressora
typedef int ( WINAPI *CPReset ) ( void );
// Inicia a Impressora pela Interface Paralela
typedef int ( WINAPI *CPInit ) ( void );
// Imprime
typedef int ( WINAPI *CPImprime ) ( char far *, int );
// Modo Documento da Impressora
typedef int ( WINAPI *CPModoDoc ) ( void );
// Modo Normal da Impressora
typedef int ( WINAPI *CPModoPE ) ( void );
// Validação ou Autenticação de Documentos
typedef int ( WINAPI *CPValidaDoc ) ( char far *, int );
// Validação de Documentos e Bobina
typedef int ( WINAPI *CPValidaDupla ) ( char far *, int );
// Cancela a Validação de Documentos e Bobina
typedef int ( WINAPI *CPCancelCmd ) ( void );

class TImpressoraMecaf : public TObject {
  private:
    CPByteStatus CPByteStatusImpressora;
    CPStatusImp CPStatusImpressora;
    CPReset CPResetImpressora;
    CPInit CPInitImpressora;
    CPImprime CPImprimeTexto;
		CPModoDoc CPModoDocImpressora;
    CPModoPE CPModoPEImpressora;
    CPValidaDoc CPValidaDocImpressora;
    CPValidaDupla CPValidaDuplaImpressora;
    CPCancelCmd CPCancelCmdImpressora;
  public:
    String ObterRetornoComando( int ret, bool local );
    String ObterStatus( bool local );
    String CarregarDll( bool local );
    String Iniciar( bool local );
    String Imprimir( String Texto, bool local );
    void Finalizar( );
};
//---------------------------------------------------------------------------
#endif
