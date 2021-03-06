#ifndef __FREEMASTER_LOOP
  #define __FREEMASTER_LOOP


  #define FMCMD_RESET_DEVICE       0x01
  #define FMCMD_SET_DCDC_DAC       0x04
  #define FMCMD_ENABLE_DCDC        0x05
  #define FMCMD_DISABLE_DCDC       0x06
  #define FMCMD_CHECK_LOG_PIPE     0x07
  #define FMCMD_SAVE_WVARS         0x08
  #define FMCMD_START_STFS_TEST    0x09
  #define FMCMD_STOP_STFS_TEST     0x0A
  #define FMCMD_DUMP_SECTOR        0x0B

uint32_t FreeMaster_task_create(ULONG initial_data);
void     Task_FreeMaster(uint32_t initial_data);

#endif

