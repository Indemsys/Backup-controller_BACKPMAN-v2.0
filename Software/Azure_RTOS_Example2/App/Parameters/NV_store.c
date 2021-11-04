// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 2018.09.03
// 23:06:41
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include   "App.h"



uint8_t    nv_store_ok;

/*-------------------------------------------------------------------------------------------
  Восстановление параметров по умолчанию, после сбоев системы или смены версии
---------------------------------------------------------------------------------------------*/
void Return_def_params(void)
{
  uint16_t  i;

  // Загрузить параметры значениями по умолчанию
  for (i = 0; i < DWVAR_SIZE; i++)
  {
    if ((dwvar[i].attr & VAL_NOINIT) == 0)
    {
      switch (dwvar[i].vartype)
      {
        // tint8u, tint16u, tuint32_t, tfloat, tarrofdouble, tarrofbyte
      case tint8u:
        *(uint8_t *)dwvar[i].val = (uint8_t)dwvar[i].defval;
        break;
      case tint16u:
        *(uint16_t *)dwvar[i].val = (uint16_t)dwvar[i].defval;
        break;
      case tint32u:
        *(uint32_t *)dwvar[i].val = (uint32_t)dwvar[i].defval;
        break;
      case tint32s:
        *(int32_t *)dwvar[i].val = (int32_t)dwvar[i].defval;
        break;
      case tfloat:
        *(float *)dwvar[i].val = (float)dwvar[i].defval;
        break;
      case tstring:
        {
          uint8_t *st;

          strncpy((char *)dwvar[i].val, (const char *)dwvar[i].pdefval, dwvar[i].varlen - 1);
          st = (uint8_t *)dwvar[i].val;
          st[dwvar[i].varlen - 1] = 0;
        }
        break;
      case tarrofbyte:
        memcpy(dwvar[i].val, dwvar[i].pdefval, dwvar[i].varlen);
        break;
      case tarrofdouble:
        break;
      }
    }
  }
}


/*-------------------------------------------------------------------------------------------
  Загрузка параметров из файла, после старта системы
---------------------------------------------------------------------------------------------*/
int32_t Restore_NV_parameters(void)
{
  int32_t status;

  nv_store_ok = true;

  Return_def_params(); // Сначала запишем в параметры значения по умолчанию
  status = Restore_from_NV_store();
  if (status != RES_OK)
  {
    nv_store_ok = false;
    Return_def_params();
    Save_Params_to_NV_store();
    LOGs(__FUNCTION__, __LINE__, SEVERITY_DEFAULT,"NV parameters restoring error. Returned to defaults");
  }
  else
  {
    LOGs(__FUNCTION__, __LINE__, SEVERITY_DEFAULT,"NV parameters restored successfully");
  }
  snprintf((char *)wvar.ver, sizeof(wvar.ver), "%s %s", __DATE__, __TIME__);
  LOGs(__FUNCTION__, __LINE__, SEVERITY_DEFAULT,"Compilation date time: %s %s", __DATE__, __TIME__);
  return (RES_OK);
}

/*-------------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------*/
int32_t Restore_from_NV_store(void)
{
//  uint16_t crc;
//  if (eeprom_ok==false) return RES_ERROR;
//  if (sizeof(WVAR_TYPE) > MAX_WVAR_SIZE) return RES_ERROR;
//  if (FLASH_read_from_EEPROM(WVAR_OFFSET_IN_EEPROM, sizeof(WVAR_TYPE), (uint8_t *)&wvar) != 0)  return RES_ERROR;
//  if (FLASH_read_from_EEPROM(WVAR_CRC_OFFSET_IN_EEPROM, sizeof(crc), (uint8_t *)&crc) != 0)  return RES_ERROR;
//  if (Get_CRC_of_block((void *)(&wvar),sizeof(WVAR_TYPE), 0xFFFF) != crc) return RES_ERROR;
  return RES_OK;
}

/*-------------------------------------------------------------------------------------------
   Процедура сохранения в ini-файл параметров
---------------------------------------------------------------------------------------------*/
int32_t Save_Params_to_NV_store(void)
{
//  uint16_t crc;
//
//  if (eeprom_ok==false) return RES_ERROR;
//  if (sizeof(WVAR_TYPE) > MAX_WVAR_SIZE) return RES_ERROR;
//  crc = Get_CRC_of_block((uint8_t *)&wvar,sizeof(WVAR_TYPE), 0xFFFF);
//  if (FLASH_write_to_EEPROM(WVAR_OFFSET_IN_EEPROM, sizeof(WVAR_TYPE),(uint8_t *)&wvar) != 0) return RES_ERROR;
//  if (FLASH_write_to_EEPROM(WVAR_CRC_OFFSET_IN_EEPROM, sizeof(crc),(uint8_t *)&crc) != 0) return RES_ERROR;
//  if (FLASH_read_from_EEPROM(WVAR_CRC_OFFSET_IN_EEPROM, sizeof(crc), (uint8_t *)&crc) != 0) return RES_ERROR;
//  if (Get_CRC_of_block((void *)(EEPROM_ADDR + WVAR_OFFSET_IN_EEPROM),sizeof(WVAR_TYPE), 0xFFFF) != crc) return RES_ERROR;

  return RES_OK;
}

