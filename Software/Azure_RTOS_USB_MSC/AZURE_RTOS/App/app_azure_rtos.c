/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_azure_rtos.c
  * @author  MCD Application Team
  * @brief   azure_rtos application implementation file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "app_azure_rtos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "main.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define THREAD_MAIN_STACK_SIZE 1024
#define THREAD_MAIN_PRIORITY               3

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

#pragma data_alignment=8
uint8_t                 thread_main_stack[THREAD_MAIN_STACK_SIZE];
TX_THREAD               main_thread;
extern  void            Thread_main(ULONG initial_input);
/* USER CODE END PV */
#if (USE_MEMORY_POOL_ALLOCATION == 1)

/* USER CODE BEGIN FX_Pool_Buffer */
/* USER CODE END FX_Pool_Buffer */
static UCHAR  fx_byte_pool_buffer[FX_APP_MEM_POOL_SIZE];
static TX_BYTE_POOL fx_app_byte_pool;

/* USER CODE BEGIN NX_Pool_Buffer */
/* USER CODE END NX_Pool_Buffer */
static UCHAR  nx_byte_pool_buffer[NX_APP_MEM_POOL_SIZE];
static TX_BYTE_POOL nx_app_byte_pool;

/* USER CODE BEGIN UX_Device_Pool_Buffer */
/* USER CODE END UX_Device_Pool_Buffer */
static UCHAR  ux_device_byte_pool_buffer[UX_DEVICE_APP_MEM_POOL_SIZE];
static TX_BYTE_POOL ux_device_app_byte_pool;

#endif

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Define the initial system.
  * @param  first_unused_memory : Pointer to the first unused memory
  * @retval None
  */
VOID tx_application_define(VOID *first_unused_memory)
{
    /* USER CODE BEGIN  tx_application_define_1*/
  tx_thread_create(&main_thread, "Main", Thread_main,
    0,
    (void *)thread_main_stack, // stack_start
    THREAD_MAIN_STACK_SIZE,    // stack_size

    THREAD_MAIN_PRIORITY,     // priority.
                              // Numerical priority of thread.
                              // Legal values range from 0 through (TX_MAX_PRIORITES-1), where a value of 0 represents the highest priority.

    THREAD_MAIN_PRIORITY,     // preempt_threshold.
                              // Highest priority level (0 through (TX_MAX_PRIORITIES-1)) of disabled preemption.
                              // Only priorities higher than this level are allowed to preempt this thread.
                              // This value must be less than or equal to the specified priority.
                              // A value equal to the thread priority disables preemption-threshold.
    TX_NO_TIME_SLICE,
    TX_AUTO_START);


    /* USER CODE END  tx_application_define_1 */
#if (USE_MEMORY_POOL_ALLOCATION == 1)
  VOID *memory_ptr;

  if (tx_byte_pool_create(&fx_app_byte_pool, "Fx App memory pool", fx_byte_pool_buffer, FX_APP_MEM_POOL_SIZE) != TX_SUCCESS)
  {
    /* USER CODE BEGIN FX_Byte_Pool_Error */

    /* USER CODE END FX_Byte_Pool_Error */
  }
  else
  {
    /* USER CODE BEGIN FX_Byte_Pool_Success */

    /* USER CODE END FX_Byte_Pool_Success */

    memory_ptr = (VOID *)&fx_app_byte_pool;

    if (App_FileX_Init(memory_ptr) != FX_SUCCESS)
    {
      /* USER CODE BEGIN  App_FileX_Init_Error */

      /* USER CODE END  App_FileX_Init_Error */
    }
    /* USER CODE BEGIN  App_FileX_Init_Success */

    /* USER CODE END  App_FileX_Init_Success */
  }

  if (tx_byte_pool_create(&nx_app_byte_pool, "Nx App memory pool", nx_byte_pool_buffer, NX_APP_MEM_POOL_SIZE) != TX_SUCCESS)
  {
    /* USER CODE BEGIN NX_Byte_Pool_Error */

    /* USER CODE END NX_Byte_Pool_Error */
  }
  else
  {
    /* USER CODE BEGIN TX_Byte_Pool_Success */

    /* USER CODE END TX_Byte_Pool_Success */

    memory_ptr = (VOID *)&nx_app_byte_pool;

    if (App_NetXDuo_Init(memory_ptr) != NX_SUCCESS)
    {
      /* USER CODE BEGIN  App_NetXDuo_Init_Error */

      /* USER CODE END  App_NetXDuo_Init_Error */
    }
    /* USER CODE BEGIN  App_NetXDuo_Init_Success */

    /* USER CODE END App_NetXDuo_Init_Success */

  }

  if (tx_byte_pool_create(&ux_device_app_byte_pool, "Ux App memory pool", ux_device_byte_pool_buffer, UX_DEVICE_APP_MEM_POOL_SIZE) != TX_SUCCESS)
  {
    /* USER CODE BEGIN UX_Device_Byte_Pool_Error */

    /* USER CODE END UX_Device_Byte_Pool_Error */
  }
  else
  {
    /* USER CODE BEGIN UX_Device_Byte_Pool_Success */

    /* USER CODE END UX_Device_Byte_Pool_Success */

    memory_ptr = (VOID *)&ux_device_app_byte_pool;

    if (App_USBX_Device_Init(memory_ptr) != UX_SUCCESS)
    {
      /* USER CODE BEGIN  App_USBX_Device_Init_Error */

      /* USER CODE END  App_USBX_Device_Init_Error */
    }
    /* USER CODE BEGIN  App_USBX_Device_Init_Success */

    /* USER CODE END  App_USBX_Device_Init_Success */
  }
#else
/*
 * Using dynamic memory allocation requires to apply some changes to the linker file.
 * ThreadX needs to pass a pointer to the first free memory location in RAM to the tx_application_define() function,
 * using the "first_unused_memory" argument.
 * This require changes in the linker files to expose this memory location.
 * For EWARM add the following section into the .icf file:
     place in RAM_region    { last section FREE_MEM };
 * For MDK-ARM
     - either define the RW_IRAM1 region in the ".sct" file
     - or modify the line below in "tx_low_level_initilize.s to match the memory region being used
        LDR r1, =|Image$$RW_IRAM1$$ZI$$Limit|

 * For STM32CubeIDE add the following section into the .ld file:
     ._threadx_heap :
       {
          . = ALIGN(8);
          __RAM_segment_used_end__ = .;
          . = . + 64K;
          . = ALIGN(8);
        } >RAM_D1 AT> RAM_D1
    * The simplest way to provide memory for ThreadX is to define a new section, see ._threadx_heap above.
    * In the example above the ThreadX heap size is set to 64KBytes.
    * The ._threadx_heap must be located between the .bss and the ._user_heap_stack sections in the linker script.
    * Caution: Make sure that ThreadX does not need more than the provided heap memory (64KBytes in this example).
    * Read more in STM32CubeIDE User Guide, chapter: "Linker script".

 * The "tx_initialize_low_level.s" should be also modified to enable the "USE_DYNAMIC_MEMORY_ALLOCATION" flag.
 */

  /* USER CODE BEGIN DYNAMIC_MEM_ALLOC */
  (void)first_unused_memory;
  /* USER CODE END DYNAMIC_MEM_ALLOC */
#endif

}

/**
  * @brief  MX_AZURE_RTOS_Init
  * @param  None
  * @retval None
  */
void MX_AZURE_RTOS_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/**
  * @brief  MX_AZURE_RTOS_Process
  * @param  None
  * @retval None
  */
void MX_AZURE_RTOS_Process(void)
{
  /* USER CODE BEGIN  1 */

  /* USER CODE END  1 */

}

/* USER CODE BEGIN  2 */

/* USER CODE END  2 */
