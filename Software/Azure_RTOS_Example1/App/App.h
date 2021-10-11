#ifndef APP_HEADER_H
  #define APP_HEADER_H

#include   <stdio.h>
#include   <time.h>
#include   <math.h>
#include   <stdint.h>
#include   <stdarg.h>
#include   <ctype.h>
#include   <stdbool.h>
#include   <arm_itm.h>
#include   "App_config.h"
#include   "tx_api.h"
#include   "ux_api.h"
#include   "Main.h"
#include   "adc.h"
#include   "fdcan.h"
#include   "i2c.h"
#include   "rtc.h"
#include   "sdmmc.h"
#include   "spi.h"
#include   "tim.h"
#include   "usart.h"
#include   "gpio.h"
#include   <core_cm7.h>

#include   "Serial_driver.h"

//#include   "stm32h735g_discovery_sd.h"
#include   "ux_dcd_stm32.h"
#include   "ux_device_class_storage.h"
#include   "ux_device_class_cdc_acm.h"
#include   "ux_device_class_rndis.h"
#include   "USB_descriptors_builder.h"
#include   "USB_periph_init.h"
#include   "USB_device_init.h"
#include   "USB_msc_driver.h"
#include   "USB_CDC_driver.h"
#include   "USB_RNDIS_driver.h"

#include   "BKMAN2_1_Params.h"
#include   "BKMAN2_1_Params_dyn_tables.h"
#include   "MonitorVT100.h"
#include   "Params_editor.h"
#include   "Main_thread.h"
#include   "App_ISRs.h"
#include   "Time_utils.h"
#include   "Mem_man.h"
#include   "App_utils.h"
#include   "logger.h"
#include   "Net_common.h"
#include   "Net_utils.h"
#include   "NV_store.h"
#include   "FreeMaster_thread.h"
#include   "FreeMaster_vars_map.h"
#include   "IDLE_task.h"

#define        AXI_SRAM_END          0x2407FFFF


#define        RES_OK                0
#define        RES_ERROR             1

#define        OS_PRIORITY_LEVEL     14
#define        DISABLE_OS_PRI_LEV    (OS_PRIORITY_LEVEL << (8 - __NVIC_PRIO_BITS))  // Маска приоритета в регистре BASEPRI запрещающая прерывания PendSV и  SysTick
#define        ENABLE_OS_PRI_LEV     0   // Маска приоритета в регистре BASEPRI разрешающая прерывания с любыми приоритетами

#define        DISABLE_OS_INTERRUPTS __set_BASEPRI(DISABLE_OS_PRI_LEV)
#define        ENABLE_OS_INTERRUPTS  __set_BASEPRI(ENABLE_OS_PRI_LEV)

#define        BIT(n) (1u << n)
#define        LSHIFT(v,n) (((unsigned int)(v) << n))

extern void    Delay_m7(int cnt); // Задержка на (cnt+1)*7 тактов . Передача нуля недопускается

#define        DELAY_1us    Delay_m7(64)           // 0.992     мкс при частоте 480 МГц
#define        DELAY_4us    Delay_m7(272)          // 4.025     мкс при частоте 480 МГц
#define        DELAY_8us    Delay_m7(544)          // 7.992     мкс при частоте 480 МГц
#define        DELAY_32us   Delay_m7(2192)         // 32.025    мкс при частоте 480 МГц
#define        DELAY_ms(x)  Delay_m7(68572*(x)-1)    // 999.95*N  мкс при частоте 480 МГц

#define        REF_TIME_INTERVAL                  100    // Задержка в мс для замера калибровочного интервала времени


#define        THREAD_MAIN_STACK_SIZE             1024
#define        VT100_TASK_STACK_SIZE              4096
#define        THREAD_FREEMASTER_STACK_SIZE       2048
#define        THREAD_IDLE_STACK_SIZE             512

#define        THREAD_MAIN_PRIORITY               3
#define        VT100_TASK_PRIO                    10
#define        THREAD_FREEMASTER_PRIORITY         4
#define        THREAD_IDLE_PRIORITY               30

extern         WVAR_TYPE       wvar;
extern const   T_work_params   dwvar[];
extern uint64_t                ref_time;             // Калибровочная константа предназначенная для измерения нагрузки микропроцессора
extern volatile uint32_t       g_cpu_usage;
extern volatile float          g_cpu_usage_fp;

#endif



