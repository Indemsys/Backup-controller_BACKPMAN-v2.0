/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx_device.c
  * @author  MCD Application Team
  * @brief   USBX Device applicative file
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
#include "app_usbx_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usb_otg.h"
#include "ux_api.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_device_stack.h"
#include "ux_dcd_stm32.h"
#include "ux_device_descriptors.h"
#include "ux_device_class_storage.h"

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

#define DEFAULT_THREAD_PRIO                   10

#define DEFAULT_PREEMPTION_THRESHOLD          DEFAULT_THREAD_PRIO
#define USBX_APP_STACK_SIZE                   (2  * 1024)
#define USBX_MEMORY_SIZE                      (48 * 1024)


TX_THREAD                           ux_app_thread;
TX_EVENT_FLAGS_GROUP                EventFlag;
UX_SLAVE_CLASS_STORAGE_PARAMETER    storage_parameter;

BSP_SD_CardInfo                     USBD_SD_CardInfo;

VOID  usbx_app_thread_entry(ULONG arg);


/*-----------------------------------------------------------------------------------------------------


  \param memory_ptr

  \return UINT
-----------------------------------------------------------------------------------------------------*/
UINT App_USBX_Device_Init(VOID *memory_ptr)
{
  UINT               ret = UX_SUCCESS;
  TX_BYTE_POOL      *byte_pool = (TX_BYTE_POOL *)memory_ptr;
  CHAR              *pointer;
  SD_HandleTypeDef  *p_hsd1;

  ULONG device_framework_hs_length;
  ULONG device_framework_fs_length;
  ULONG string_framework_length;
  ULONG languge_id_framework_length;
  UCHAR *device_framework_high_speed;
  UCHAR *device_framework_full_speed;
  UCHAR *string_framework;
  UCHAR *language_id_framework;


  tx_byte_allocate(byte_pool, (VOID **)&pointer, USBX_MEMORY_SIZE, TX_NO_WAIT);                                /* Allocate the USBX_MEMORY_SIZE. */
  ux_system_initialize(pointer, USBX_MEMORY_SIZE, UX_NULL, 0);                                                 /* Initialize USBX Memory */
  device_framework_high_speed = USBD_Get_Device_Framework_Speed(USBD_HIGH_SPEED, &device_framework_hs_length); /* Get_Device_Framework_High_Speed and get the length */
  device_framework_full_speed = USBD_Get_Device_Framework_Speed(USBD_FULL_SPEED, &device_framework_fs_length); /* Get_Device_Framework_Full_Speed and get the length */
  string_framework            = USBD_Get_String_Framework(&string_framework_length);                           /* Get_String_Framework and get the length */
  language_id_framework       = USBD_Get_Language_Id_Framework(&languge_id_framework_length);                  /* Get_Language_Id_Framework and get the length */

  ret =  _ux_device_stack_initialize(device_framework_high_speed,
       device_framework_hs_length,
       device_framework_full_speed,
       device_framework_fs_length,
       string_framework,
       string_framework_length,
       language_id_framework,
       languge_id_framework_length, UX_NULL);

//  ret =  _ux_device_stack_initialize(NULL,
//       0,
//       device_framework_full_speed,
//       device_framework_fs_length,
//       string_framework,
//       string_framework_length,
//       language_id_framework,
//       languge_id_framework_length, UX_NULL);

  if (ret != UX_SUCCESS)
  {
    return ret;
  }

  p_hsd1 = &hsd_sdmmc[SD_INSTANCE];

  storage_parameter.ux_slave_class_storage_parameter_number_lun = 1;                                                                              /* Store the number of LUN in this device storage instance. */
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_last_lba       = (ULONG)(p_hsd1->SdCard.BlockNbr - 1); /* Initialize the storage class parameters for reading/writing to the Flash Disk. */
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_block_length   = p_hsd1->SdCard.BlockSize;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_type           = 0;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_removable_flag = 0x80;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_read           = STORAGE_Read;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_write          = STORAGE_Write;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_status         = STORAGE_Status;

  ret =  _ux_device_stack_class_register(_ux_system_slave_class_storage_name, _ux_device_class_storage_entry, 1, 0, (VOID *)&storage_parameter);  /* Initialize the device storage class. The class is connected with interface 0 on configuration 1. */

  if (ret != UX_SUCCESS)
  {
    return ret;
  }

  tx_byte_allocate(byte_pool, (VOID **)&pointer, USBX_APP_STACK_SIZE, TX_NO_WAIT);

  ret = tx_thread_create(&ux_app_thread, "main_usbx_app_thread_entry",
       usbx_app_thread_entry, 0,
       pointer, USBX_APP_STACK_SIZE,
       DEFAULT_THREAD_PRIO, DEFAULT_PREEMPTION_THRESHOLD,
       TX_NO_TIME_SLICE, TX_AUTO_START);

  if (tx_event_flags_create(&EventFlag, "Event Flag") != TX_SUCCESS)
  {
    ret = TX_GROUP_ERROR;
  }



  return ret;
}

/*-----------------------------------------------------------------------------------------------------


  \param arg
-----------------------------------------------------------------------------------------------------*/
void usbx_app_thread_entry(ULONG arg)
{

  tx_thread_sleep(0.1 * TX_TIMER_TICKS_PER_SECOND); /* Sleep for 100 ms */

  MX_USB_Device_Init();
}


/*-----------------------------------------------------------------------------------------------------
   Initialization of USB device.
   Init USB device Library, add supported class and start the library

  \param void
-----------------------------------------------------------------------------------------------------*/
void MX_USB_Device_Init(void)
{
  //HAL_PWREx_EnableUSBVoltageDetector();

  MX_USB_OTG_FS_PCD_Init();                                             // initialize the device controller HAL driver
  HAL_PCDEx_SetRxFiFo(&hpcd_USB_OTG_FS, 0x200);
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 0, 0x40);
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 1, 0x100);

  _ux_dcd_stm32_initialize((ULONG)USB_OTG_FS, (ULONG)&hpcd_USB_OTG_FS); // initialize and link controller HAL driver to USBx

  HAL_PCD_Start(&hpcd_USB_OTG_FS);                                      // Start USB device by connecting the DP pullup

}

