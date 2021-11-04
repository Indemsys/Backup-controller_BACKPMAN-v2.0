#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "frm_Sector_dump.h"


#pragma package(smart_init)
#pragma resource "*.dfm"

Tfrm_Main *frm_Main;

extern "C"
void Write_to_mem(const char *name, unsigned int line_num, char *str);

extern uint32_t  sim_erase_count[];

static uint32_t stfs_inited = 0;

/*-----------------------------------------------------------------------------------------------------


  \param str
-----------------------------------------------------------------------------------------------------*/
void Write_to_mem(const char *name, unsigned int line_num, char *str)
{
  frm_Main->Log_memo->Lines->Add(str);
}

/*-----------------------------------------------------------------------------------------------------


-----------------------------------------------------------------------------------------------------*/
__fastcall Tfrm_Main::Tfrm_Main(TComponent *Owner)
  : TForm(Owner)
{
  CreateSimulationView();
  ViewPanel->Repaint();
}


/*-----------------------------------------------------------------------------------------------------


  \param Sender
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::Segment_Paint(TObject *Sender)
{
  uint32_t       sector;
  uint32_t       sectors_count;
  uint32_t       position;

  uint32_t       width;
  uint32_t       height;
  TRect          rec;
  TPaintBox      *p_pbox =  (TPaintBox *)Sender;

  sectors_count  = STfs_get_sec_num();
  sector         = p_pbox->Tag;

  rec            = ViewPanel->ClientRect;
  height         = rec.Height();
  width          = rec.Width() / sectors_count;

  p_pbox->Height = 1024; //height - 30;
  p_pbox->Width  = 128;  //width  - 10;
  p_pbox->Top    = 15;
  p_pbox->Left   =(sector * rec.Width()) / sectors_count + 5;

  position = 0;
  Graphics::TBitmap *pBitmap = new Graphics::TBitmap;
  pBitmap->PixelFormat       = pf24bit;
  pBitmap->Height            = 1024;
  pBitmap->Width             = 128;
  for (int y = pBitmap->Height -1; y >= 0; y--)
  {
    TRGBTriple *ptr = (TRGBTriple *)(pBitmap->ScanLine[y]);

    for (int x = 0; x < pBitmap->Width; x++)
    {
      uint32_t color = Get_STfs_mark(sector, position);
      switch (color)
      {
      case EMPTY_DESCRIPTOR_COLOR:
        ptr[x].rgbtBlue  = 128;
        ptr[x].rgbtGreen = 128;
        ptr[x].rgbtRed   = 128;
        break;
      case VALID_DESCRIPTOR_COLOR:
        ptr[x].rgbtBlue  = 0;
        ptr[x].rgbtGreen = 255;
        ptr[x].rgbtRed   = 255;
        break;
      case INVALID_DESCRIPTOR_COLOR:
        ptr[x].rgbtBlue  = 0;
        ptr[x].rgbtGreen = 0;
        ptr[x].rgbtRed   = 64;
        break;
      case EMPTY_DATA_CHUNK_COLOR:
        ptr[x].rgbtBlue  = 64;
        ptr[x].rgbtGreen = 64;
        ptr[x].rgbtRed   = 64;
        break;
      case VALID_DATA_CHUNK_COLOR:
        ptr[x].rgbtBlue  = 0;
        ptr[x].rgbtGreen = 255;
        ptr[x].rgbtRed   = 0;
        break;
      case INVALID_DATA_CHUNK_COLOR:
        ptr[x].rgbtBlue  = 0;
        ptr[x].rgbtGreen = 0;
        ptr[x].rgbtRed   = 128;
        break;
      case 0:
        ptr[x].rgbtBlue  = 64;
        ptr[x].rgbtGreen = 64;
        ptr[x].rgbtRed   = 64;
        break;
      }
      position++;
    }
  }

  p_pbox->Canvas->Draw(0,0,pBitmap);

  pBitmap->Free();
}


/*-----------------------------------------------------------------------------------------------------


  \param void
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::CreateSimulationView(void)
{
  uint32_t  sec_num;
  sec_num = STfs_get_sec_num();

  for (uint32_t i=0; i < sec_num; i++)
  {
    TPaintBox *p_pbox = new TPaintBox(ViewPanel);
    p_pboxes[i] = p_pbox;
    p_pbox->OnPaint = Segment_Paint;
    p_pbox->Tag = i;
    ViewPanel->InsertControl(p_pbox);
  }
}

/*-----------------------------------------------------------------------------------------------------


  \param void
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::Stop_simulation(void)
{
  UnicodeString  str;
  uint32_t       sec_num;

  sec_num = STfs_get_sec_num();


  btn_Start_Simulation->Caption = "Start";

  CmdsPanel->Visible = true;
  Timer->Enabled = false;
  Log_memo->Lines->Add(" ");
  Log_memo->Lines->Add("Stop simulation");
  str = "Count = " + Sysutils::Format("%d",ARRAYOFCONST((iterations_number)))+ "  Fails = " + Sysutils::Format("%d",ARRAYOFCONST((fails_cnt)));
  Log_memo->Lines->Add(str);
  Log_memo->Lines->Add(".......................................................");

  for (uint32_t i=0; i < sec_num; i++)
  {
    UnicodeString str = Sysutils::Format("Sector %d erased %d times",ARRAYOFCONST((i,STfs_get_sector_erase_num(i))));
    Log_memo->Lines->Add(str);
  }


}

/*-----------------------------------------------------------------------------------------------------


  \param Sender
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::btn_Start_SimulationClick(TObject *Sender)
{
  if (Timer->Enabled == true)
  {
    Stop_simulation();
  }
  else
  {
    Log_memo->Lines->Add(" ");
    Log_memo->Lines->Add("------------------------------------------------------");
    Log_memo->Lines->Add("Start simulation");
    Log_memo->Lines->Add("------------------------------------------------------");

    if (stfs_inited == 0)
    {
      if (STfs_init(INT_FLASH_BANK2, &stfs_info) != STFS_OK)
      {
        Log_memo->Lines->Add("SFFS Initialization error!");
        return;
      }
      Log_memo->Lines->Add("SFFS Initialization done!");
      stfs_inited = 1;
    }

    test_cbl.min_file_size  = 512   ;
    test_cbl.max_file_size  = 48000 ;
    test_cbl.min_file_chunk = 8     ;
    test_cbl.max_file_chunk = 512   ;
    test_cbl.max_num_chunks = 150   ;

    //test_cbl.min_file_size  = 10000   ;
    //test_cbl.max_file_size  = 10000   ;
    //test_cbl.min_file_chunk = 100     ;
    //test_cbl.max_file_chunk = 100     ;
    //test_cbl.max_num_chunks = 110 ;
    STfs_init_test(&test_cbl);


    iterations_number = ed_Iterations_number->Text.ToInt();
    current_iteration = 0;
    fails_cnt         = 0;
    Timer->Enabled    = true;
    btn_Start_Simulation->Caption = "Stop";
    CmdsPanel->Visible = false;

    //Save_panel_to_file();
  }
}


/*-----------------------------------------------------------------------------------------------------


  \param Sender
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::btn_InitSTFSClick(TObject *Sender)
{
  uint32_t       res;
  UnicodeString  str;

  if (stfs_inited == 0)
  {
    res = STfs_init(INT_FLASH_BANK2, &stfs_info);
    if (res != STFS_OK)
    {
      str = "SFFS Initialization error " + Sysutils::Format("%d",ARRAYOFCONST((res)));
      return;
    }
    Log_memo->Lines->Add("SFFS Initialization done!");
    stfs_inited = 1;
  }

  res = STfs_format(INT_FLASH_BANK2);
  if (res != STFS_OK)
  {
    str = "SFFS formating error " + Sysutils::Format("%d",ARRAYOFCONST((res)));
    Log_memo->Lines->Add(str);
    return;
  }
  else
  {
    Log_memo->Lines->Add("SFFS formating successsful.");
  }

  Log_memo->Lines->Add("SFFS Initialization done!");

  STfs_test_check(INT_FLASH_BANK2);

  for (uint32_t i=0; i < STfs_get_sec_num(); i++)
  {
    p_pboxes[i]->Repaint();
    Application->ProcessMessages();
  }

  Log_memo->Clear();
}

/*-----------------------------------------------------------------------------------------------------


  \param Sender
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::TimerTimer(TObject *Sender)
{


  Log_memo->Lines->Add(".......................................................");
  Log_memo->Lines->Add("Iteration " + Sysutils::Format("%d",ARRAYOFCONST((current_iteration))));
  Log_memo->Lines->Add(".......................................................");

  if (current_iteration < iterations_number)
  {
    uint8_t enable_deleting;
    if (current_iteration % 10)
    {
      enable_deleting = 1;
    }
    else
    {
      enable_deleting = 0;
    }

    //Save_panel_to_file();
    uint8_t fragm_flag = 0;
    if (cb_Fragmented->Checked)
    {
      fragm_flag = 1;
    }

    if (STfs_test_write_read_delete(INT_FLASH_BANK2, current_iteration, rand(), enable_deleting, fragm_flag) != STFS_OK)
    {
      fails_cnt++;
      Stop_simulation();
      Sbar->Panels->Items[0]->Text = "An error has occurred";
      PageControl->TabIndex = 0;
    }
    current_iteration++;
  }
  else
  {
    Stop_simulation();
    Sbar->Panels->Items[0]->Text = "Test completed successfully";
  }

  for (uint32_t i=0; i < STfs_get_sec_num(); i++)
  {
    p_pboxes[i]->Repaint();
  }
  //Save_panel_to_file();
  //Application->ProcessMessages();

}


/*-----------------------------------------------------------------------------------------------------


  \param void
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::Save_panel_to_file(void)
{
  UnicodeString str;

  Graphics::TBitmap *p_bmp = new Graphics::TBitmap;
  Graphics::TBitmap *p_bmp2 = new Graphics::TBitmap;

  p_bmp->Width = ViewPanel->Width;
  p_bmp->Height = ViewPanel->Height;
  p_bmp2->Width  = ViewPanel->Width/4;
  p_bmp2->Height = ViewPanel->Height/4;

  ViewPanel->PaintTo(p_bmp->Canvas->Handle,0,0);
  p_bmp2->Canvas->StretchDraw(TRect(0,0,p_bmp->Width/4,p_bmp->Height/4 ),p_bmp);


  str = Sysutils::Format("ScreenShot%d.bmp",ARRAYOFCONST((current_iteration)));
  p_bmp2->SaveToFile(str);
  p_bmp->Free();
  p_bmp2->Free();
}

/*-----------------------------------------------------------------------------------------------------


  \param Sender
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::btn_CheckSTfsClick(TObject *Sender)
{
  if (stfs_inited == 0)
  {
    if (STfs_init(INT_FLASH_BANK2, &stfs_info) != STFS_OK)
    {
      Log_memo->Lines->Add("SFFS Initialization error!");
      return;
    }
    Log_memo->Lines->Add("SFFS Initialization done!");
    stfs_inited = 1;
  }

  STfs_test_check(INT_FLASH_BANK2);
  for (uint32_t i=0; i < STfs_get_sec_num(); i++)
  {
    p_pboxes[i]->Repaint();
    Application->ProcessMessages();
  }
}

/*-----------------------------------------------------------------------------------------------------


  \param Sender
-----------------------------------------------------------------------------------------------------*/
void __fastcall Tfrm_Main::btn_SectorDumpClick(TObject *Sender)
{
  uint32_t        sector;
  uint8_t         *sec_ptr;
  uint32_t        sec_size;
  uint32_t        offs;
  uint8_t         *ptr;
  UnicodeString   str;
  TfrmSectorDump *frm;


  if (stfs_inited == 0)
  {
    ShowMessage("STfs not initialised yet!");
    return;
  }

  sector = cb_Sector->ItemIndex;

  sec_ptr = STfs_get_sector(sector);
  sec_size = STfs_get_sector_size(sector);

  frm = new TfrmSectorDump(this);

  frm->Caption =  Sysutils::Format("Sector %d",ARRAYOFCONST((sector)));

  // Выводим в memo формы дамп содержимого сектора

  offs = 0;
  ptr = sec_ptr;
  do
  {
    str = Sysutils::Format("%08.8X %08.8X   ",ARRAYOFCONST(((uint32_t)ptr, offs)));
    for (uint32_t i=0;i<32;i++)
    {
      uint8_t b = *ptr;
      str = str + Sysutils::Format("%02.2X ",ARRAYOFCONST((b)));
      ptr++;
      offs++;
      if (offs >= sec_size) break;
    }
    frm->Memo->Lines->Add(str);

  }while (offs < sec_size);

  frm->Show();
}

