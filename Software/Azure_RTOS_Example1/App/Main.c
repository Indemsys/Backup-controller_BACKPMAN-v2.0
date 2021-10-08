#include "App.h"

WVAR_TYPE    wvar;

#pragma data_alignment=8
uint8_t                 thread_main_stack[THREAD_MAIN_STACK_SIZE];
TX_THREAD               main_thread;


void SystemClock_Config(void);
void PeriphCommonClock_Config(void);

/*-----------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------*/
int main(void)
{
  SCB_EnableICache();
  //SCB_EnableDCache();

  HAL_Init();
  SystemClock_Config();
  PeriphCommonClock_Config();

  MX_GPIO_Init();
  MX_RTC_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_FDCAN1_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_SDMMC1_SD_Init();
  MX_SPI2_Init();
  MX_SPI4_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_UART8_Init();
  tx_kernel_enter();
  while (1)
  {
  }

}

/*-----------------------------------------------------------------------------------------------------


  \param first_unused_memory
-----------------------------------------------------------------------------------------------------*/
VOID tx_application_define(VOID *first_unused_memory)
{
  App_create_pool_memry(first_unused_memory);

  tx_thread_create(&main_thread, "Main", Thread_main,
    0,
    (void *)thread_main_stack, // stack_start
    THREAD_MAIN_STACK_SIZE,    // stack_size

    THREAD_MAIN_PRIORITY,     // priority.
                              // Numerical priority of thread.
                              // Legal values range from 0 through (TX_MAX_PRIORITIES-1), where a value of 0 represents the highest priority.

    THREAD_MAIN_PRIORITY,     // preempt_threshold.
                              // Highest priority level (0 through (TX_MAX_PRIORITIES-1)) of disabled preemption.
                              // Only priorities higher than this level are allowed to preempt this thread.
                              // This value must be less than or equal to the specified priority.
                              // A value equal to the thread priority disables preemption-threshold.
    TX_NO_TIME_SLICE,
    TX_AUTO_START);
}

/*-----------------------------------------------------------------------------------------------------


-----------------------------------------------------------------------------------------------------*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // Supply configuration update enable
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  // Configure the main internal regulator output voltage
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
  {
  }

  // Configure LSE Drive Capability
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  // Macro to configure the PLL clock source
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  // Initializes the RCC Oscillators according to the specified parameters  in the RCC_OscInitTypeDef structure.
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState      = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState      = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState  = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM      = 1;
  RCC_OscInitStruct.PLL.PLLN      = 60;
  RCC_OscInitStruct.PLL.PLLP      = 2;
  RCC_OscInitStruct.PLL.PLLQ      = 8; // 120 MHz
  RCC_OscInitStruct.PLL.PLLR      = 2;
  RCC_OscInitStruct.PLL.PLLRGE    = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN  = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/*-----------------------------------------------------------------------------------------------------
   Peripherals Common Clock Configuration

-----------------------------------------------------------------------------------------------------*/
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_SPI2 | RCC_PERIPHCLK_SPI1 | RCC_PERIPHCLK_FDCAN;
  PeriphClkInitStruct.PLL2.PLL2M           = 1;
  PeriphClkInitStruct.PLL2.PLL2N           = 12;
  PeriphClkInitStruct.PLL2.PLL2P           = 3;
  PeriphClkInitStruct.PLL2.PLL2Q           = 2;
  PeriphClkInitStruct.PLL2.PLL2R           = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE         = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL      = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN       = 0;

  PeriphClkInitStruct.PLL3.PLL3M           = 1;
  PeriphClkInitStruct.PLL3.PLL3N           = 12;
  PeriphClkInitStruct.PLL3.PLL3P           = 2;
  PeriphClkInitStruct.PLL3.PLL3Q           = 4;
  PeriphClkInitStruct.PLL3.PLL3R           = 2;
  PeriphClkInitStruct.PLL3.PLL3RGE         = RCC_PLL3VCIRANGE_3;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL      = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3FRACN       = 0;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL3;
  PeriphClkInitStruct.FdcanClockSelection  = RCC_FDCANCLKSOURCE_PLL2;
  PeriphClkInitStruct.UsbClockSelection    = RCC_USBCLKSOURCE_PLL3;
  PeriphClkInitStruct.AdcClockSelection    = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/*-----------------------------------------------------------------------------------------------------
  Period elapsed callback in non-blocking mode.
  This function is called  when TIM3 interrupt took place, inside HAL_TIM_IRQHandler().
  It makes a direct call to HAL_IncTick() to increment a global variable "uwTick" used as application time base

  \param htim
-----------------------------------------------------------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM3)
  {
    HAL_IncTick();
  }
}

/*-----------------------------------------------------------------------------------------------------
  This function is executed in case of error occurrence.

  \param void
-----------------------------------------------------------------------------------------------------*/
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

