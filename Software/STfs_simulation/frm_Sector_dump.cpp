//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frm_Sector_dump.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSectorDump *frmSectorDump;
//---------------------------------------------------------------------------
__fastcall TfrmSectorDump::TfrmSectorDump(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSectorDump::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
