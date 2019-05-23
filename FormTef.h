//---------------------------------------------------------------------------

#ifndef FormTefH
#define FormTefH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormMensagemTef : public TForm {

  __published:	// IDE-managed Components

    TLabel *LabelMensagemTEF;
  private:	// User declarations

  public:		// User declarations

    __fastcall TFormMensagemTef( TComponent* Owner );
    __fastcall ~TFormMensagemTef( void );
};
//---------------------------------------------------------------------------
#endif
