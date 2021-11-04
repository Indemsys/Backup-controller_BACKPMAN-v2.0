//---------------------------------------------------------------------------

#ifndef frm_Sector_dumpH
#define frm_Sector_dumpH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TfrmSectorDump : public TForm
{
__published:	// IDE-managed Components
  TMemo *Memo;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
  __fastcall TfrmSectorDump(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSectorDump *frmSectorDump;
//---------------------------------------------------------------------------
#endif
