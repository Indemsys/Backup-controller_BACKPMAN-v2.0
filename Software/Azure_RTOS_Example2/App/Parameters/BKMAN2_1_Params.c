#include "App.h"
#include "freemaster_cfg.h"
#include "freemaster.h"
#include "freemaster_tsa.h"

const T_parmenu parmenu[3]=
{
  {BKMAN2_1_0,BKMAN2_1_main,"Parameters and settings","PARAMETERS", -1},//  Основная категория
  {BKMAN2_1_main,BKMAN2_1_General,"General settings","GENERAL SETTINGS", -1},//  
  {BKMAN2_1_main,BKMAN2_1_Network,"Network settings","NETWORK SETTINGS", -1},//  
};


const T_work_params dwvar[4]=
{
  {
    "name",
    "Product  name",
    "-",
    (void*)&wvar.name,
    tstring,
    0,
    0,
    0,
    0,
    BKMAN2_1_General,
    "BACKPMAN10",
    "%s",
    0,
    sizeof(wvar.name),
    1,
    0,
  },
  {
    "ver",
    "Firmware version",
    "-",
    (void*)&wvar.ver,
    tstring,
    0,
    0,
    0,
    0,
    BKMAN2_1_General,
    "1.0",
    "%s",
    0,
    sizeof(wvar.ver),
    2,
    0,
  },
  {
    "vcom_mode",
    "Select VCOM mode (0 - VT100 terminal, 1 - FreeMaster) ",
    "-",
    (void*)&wvar.vcom_mode,
    tint8u,
    1,
    0,
    1,
    0,
    BKMAN2_1_General,
    "",
    "%d",
    0,
    sizeof(wvar.vcom_mode),
    3,
    1,
  },
  {
    "rndis_config",
    "RNDIS interface configuration (0-Win home net, 1 - DHCP server)",
    "-",
    (void*)&wvar.rndis_config,
    tint8u,
    1,
    0,
    1,
    0,
    BKMAN2_1_Network,
    "",
    "%в",
    0,
    sizeof(wvar.rndis_config),
    0,
    2,
  },
};
 
 
// Selector description:  Выбор между Yes и No
static const T_selector_items selector_1[2] = 
{
  {0, "No", 0},
  {1, "Yes", 1},
};
 
// Selector description:  Confuguration of RNDIS interface
static const T_selector_items selector_2[2] = 
{
  {0, "Windows home network ", -1},
  {1, "Preconfigured DHCP server", -1},
};
 
const T_selectors_list selectors_list[3] = 
{
  {"string"            , 0    , 0             },
  {"binary"            , 2    , selector_1    },
  {"rndis_config"      , 2    , selector_2    },
};
 
