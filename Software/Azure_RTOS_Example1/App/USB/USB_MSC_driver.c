#include "App.h"


#define SD_READ_FLAG                         0x01
#define SD_WRITE_FLAG                        0x02
#define SD_TIMEOUT                           100   // Время ожидания готовности в миллисекундах

SD_HandleTypeDef hsd_sdmmc[1];

static int32_t check_sd_status(uint32_t instance);

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

UX_SLAVE_CLASS_STORAGE_PARAMETER    storage_parameter;


static uint8_t sd_is_detected = 1;
/*-----------------------------------------------------------------------------------------------------


  \param void
-----------------------------------------------------------------------------------------------------*/
UINT Register_USB_MSC_class(void)
{
  SD_HandleTypeDef  *p_hsd1;
  UINT               ret = UX_SUCCESS;

  p_hsd1 =&hsd_sdmmc[SD_INSTANCE];
  storage_parameter.ux_slave_class_storage_parameter_number_lun = 1;                                                                            /* Store the number of LUN in this device storage instance. */
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_last_lba       = (ULONG)(p_hsd1->SdCard.BlockNbr - 1); /* Initialize the storage class parameters for reading/writing to the Flash Disk. */
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_block_length   = p_hsd1->SdCard.BlockSize;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_type           = 0;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_removable_flag = 0x80;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_read           = STORAGE_Read;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_write          = STORAGE_Write;
  storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_status         = STORAGE_Status;

  ret =  _ux_device_stack_class_register(_ux_system_slave_class_storage_name, _ux_device_class_storage_entry, 1, USBD_MSC_INTERFACE_INDEX, (VOID *)&storage_parameter);
  return ret;
}


/*-----------------------------------------------------------------------------------------------------


  \param storage
  \param lun
  \param media_id
  \param media_status

  \return UINT
-----------------------------------------------------------------------------------------------------*/
UINT STORAGE_Status(VOID *storage, ULONG lun, ULONG media_id, ULONG *media_status)
{
  /* The ATA drive never fails. This is just for app_usb_device only !!!! */
  return (UX_SUCCESS);
}

/*-----------------------------------------------------------------------------------------------------


  \param storage
  \param lun
  \param data_pointer
  \param number_blocks
  \param lba
  \param media_status

  \return UINT
-----------------------------------------------------------------------------------------------------*/
UINT STORAGE_Read(VOID *storage, ULONG lun, UCHAR *data_pointer, ULONG number_blocks, ULONG lba, ULONG *media_status)
{
  HAL_StatusTypeDef  res;
  UINT status = UX_ERROR;
  ULONG ReadFlags = 0U;

  if (sd_is_detected == 0) return UX_ERROR;

  if (check_sd_status(SD_INSTANCE) == RES_OK)
  {
    res = HAL_SD_ReadBlocks_DMA(&hsd_sdmmc[SD_INSTANCE], (uint8_t *)data_pointer, lba, number_blocks);
    if (res != HAL_OK ) status = UX_ERROR;
    else status = UX_SUCCESS;
    if (tx_event_flags_get(&usb_msc_flag_grp, SD_READ_FLAG, TX_OR_CLEAR,&ReadFlags, 100) != TX_SUCCESS)
    {
      return UX_ERROR;
    }
  }
  return (status);
}

/*-----------------------------------------------------------------------------------------------------


  \param storage
  \param lun
  \param data_pointer
  \param number_blocks
  \param lba
  \param media_status

  \return UINT
-----------------------------------------------------------------------------------------------------*/
UINT STORAGE_Write(VOID *storage, ULONG lun, UCHAR *data_pointer, ULONG number_blocks, ULONG lba, ULONG *media_status)
{
  HAL_StatusTypeDef  res;
  UINT status = UX_ERROR;
  ULONG WriteFlags = 0U;

  if (sd_is_detected == 0) return UX_ERROR;

  if (check_sd_status(SD_INSTANCE) == RES_OK)
  {
    res = HAL_SD_WriteBlocks_DMA(&hsd_sdmmc[SD_INSTANCE], (uint8_t *)data_pointer, lba, number_blocks);
    if (res != HAL_OK ) status = UX_ERROR;
    else status = UX_SUCCESS;
    if (tx_event_flags_get(&usb_msc_flag_grp, SD_WRITE_FLAG, TX_OR_CLEAR,&WriteFlags, 100) != TX_SUCCESS)
    {
      return UX_ERROR;
    }
  }
  return (status);
}

/*-----------------------------------------------------------------------------------------------------


  \param Instance
-----------------------------------------------------------------------------------------------------*/
void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
  if (tx_event_flags_set(&usb_msc_flag_grp, SD_WRITE_FLAG, TX_OR) != TX_SUCCESS)
  {
    Error_Handler();
  }
}


/*-----------------------------------------------------------------------------------------------------


  \param Instance
-----------------------------------------------------------------------------------------------------*/
void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
  if (tx_event_flags_set(&usb_msc_flag_grp, SD_READ_FLAG, TX_OR) != TX_SUCCESS)
  {
    Error_Handler();
  }
}

/*-----------------------------------------------------------------------------------------------------


  \param Instance

  \return int32_t
-----------------------------------------------------------------------------------------------------*/
static int32_t _GetCardState(uint32_t Instance)
{
  HAL_SD_CardStateTypeDef res;

  res = HAL_SD_GetCardState(&hsd_sdmmc[Instance]);
  if (res == HAL_SD_CARD_TRANSFER)
  {
    return RES_OK;
  }
  else
  {
    return RES_ERROR;
  }
}

/*-----------------------------------------------------------------------------------------------------


  \param Instance

  \return int32_t
-----------------------------------------------------------------------------------------------------*/
static int32_t check_sd_status(uint32_t Instance)
{
  uint32_t start_t;
  uint32_t curr_t;

  Get_system_ticks(&start_t);
  do
  {
    Get_system_ticks(&curr_t);
    if ((curr_t - start_t) > MS_TO_TICKS(SD_TIMEOUT)) return RES_ERROR;
    if (_GetCardState(Instance) == RES_OK) return RES_OK;
    tx_thread_sleep(1);

  }while (1);
}

