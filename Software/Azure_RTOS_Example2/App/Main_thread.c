#include "App.h"

/*-----------------------------------------------------------------------------------------------------


  \param initial_input
-----------------------------------------------------------------------------------------------------*/
void Thread_main(ULONG initial_input)
{
  // Выполняем контрольный замер времени одновременно эта задержка служит для обеспечения установления референсных напряжений в чипе
  ref_time = Measure_reference_time_interval(REF_TIME_INTERVAL);

  AppLogg_init();
  APPLOG("Main thread started");

  Thread_idle_create();
  Restore_NV_parameters();

  App_USBX_Device_Init();

//  if (wvar.vcom_mode == 0)
//  {
//    Task_VT100_create(Mnsdrv_get_usbfs_vcom0_driver(),0);
//  }
//  else
//  {
    FreeMaster_task_create((ULONG)Mnsdrv_get_usbfs_vcom0_driver());
//  }


  Init_Net();
  RNDIS_init_network_stack();

  for (;;)
  {
    RNDIS_interface_controller();
    HAL_GPIO_WritePin(LED_GR_GPIO_Port, LED_GR_Pin, GPIO_PIN_RESET);
    tx_thread_sleep(500);
    HAL_GPIO_WritePin(LED_GR_GPIO_Port, LED_GR_Pin, GPIO_PIN_SET);
    tx_thread_sleep(500);
  }
}


