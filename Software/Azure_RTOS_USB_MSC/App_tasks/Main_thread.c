// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 2021-09-21
// 18:00:39 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "App.h"



/*-----------------------------------------------------------------------------------------------------


  \param initial_input
-----------------------------------------------------------------------------------------------------*/
void Thread_main(ULONG initial_input)
{


  for (;;)
  {
    HAL_GPIO_WritePin(LED_GR_GPIO_Port, LED_GR_Pin, GPIO_PIN_RESET);
    tx_thread_sleep(500);
    HAL_GPIO_WritePin(LED_GR_GPIO_Port, LED_GR_Pin, GPIO_PIN_SET);
    tx_thread_sleep(500);
  }
}


