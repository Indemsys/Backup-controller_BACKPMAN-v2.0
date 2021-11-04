#ifndef MainH
  #define MainH

  #include <System.Classes.hpp>
  #include <Vcl.Controls.hpp>
  #include <Vcl.StdCtrls.hpp>
  #include <Vcl.Forms.hpp>
  #include <Vcl.ComCtrls.hpp>
  #include <Vcl.ExtCtrls.hpp>

  #include "App.h"
  #include "STfs_int.h"
  #include "STfs_api.h"
  #include "STfs_tests.h"
  #include "Flash_media_driver.h"
  #include <Vcl.Mask.hpp>

class Tfrm_Main : public TForm
{
    __published:      // IDE-managed Components
    TButton *btn_Start_Simulation;
    TMemo *Log_memo;
  TPageControl *PageControl;
    TTabSheet *tsLog;
    TTabSheet *tsView;
    TPanel *ViewPanel;
    TTimer *Timer;
    TMaskEdit *ed_Iterations_number;
    TLabel *Label1;
  TPanel *CmdsPanel;
  TButton *btn_SectorDump;
  TComboBox *cb_Sector;
  TButton *btn_CheckSTfs;
  TButton *btn_InitSTFS;
  TStatusBar *Sbar;
  TCheckBox *cb_Fragmented;
    void __fastcall  btn_Start_SimulationClick(TObject *Sender);
    void __fastcall  Segment_Paint(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall btn_InitSTFSClick(TObject *Sender);
  void __fastcall btn_CheckSTfsClick(TObject *Sender);
  void __fastcall btn_SectorDumpClick(TObject *Sender);

  private:
    uint32_t          iterations_number;
    uint32_t          current_iteration;
    uint32_t          fails_cnt;
    T_stfs_info       stfs_info;
    TPaintBox        *p_pboxes[100];
    T_stfs_test_cbl   test_cbl;

    void __fastcall   CreateSimulationView(void);
    void __fastcall   Stop_simulation(void);
    void __fastcall   Save_panel_to_file(void);

  public:   // User declarations

    __fastcall        Tfrm_Main(TComponent *Owner);
};


extern PACKAGE Tfrm_Main *frm_Main;
#endif
