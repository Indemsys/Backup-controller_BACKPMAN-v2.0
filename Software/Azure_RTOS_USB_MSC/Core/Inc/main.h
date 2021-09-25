/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

#define  SD_INSTANCE 0
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OLED_RES_Pin GPIO_PIN_13
#define OLED_RES_GPIO_Port GPIOC
#define OLED_CLK_Pin GPIO_PIN_2
#define OLED_CLK_GPIO_Port GPIOE
#define SPI1_CS_Pin GPIO_PIN_9
#define SPI1_CS_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB
#define SPI0_MISO_Pin GPIO_PIN_4
#define SPI0_MISO_GPIO_Port GPIOB
#define LED_GR_Pin GPIO_PIN_15
#define LED_GR_GPIO_Port GPIOA
#define OLED_DC_Pin GPIO_PIN_3
#define OLED_DC_GPIO_Port GPIOE
#define CAN0_RX_Pin GPIO_PIN_8
#define CAN0_RX_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define OLEDP_Pin GPIO_PIN_5
#define OLEDP_GPIO_Port GPIOD
#define OLED_CS_Pin GPIO_PIN_4
#define OLED_CS_GPIO_Port GPIOE
#define UART1_TX_Pin GPIO_PIN_1
#define UART1_TX_GPIO_Port GPIOE
#define SPI0_MOSI_Pin GPIO_PIN_5
#define SPI0_MOSI_GPIO_Port GPIOB
#define OLEDV_Pin GPIO_PIN_6
#define OLEDV_GPIO_Port GPIOD
#define SPI1_SCK_Pin GPIO_PIN_3
#define SPI1_SCK_GPIO_Port GPIOD
#define UART1_RX_Pin GPIO_PIN_0
#define UART1_RX_GPIO_Port GPIOE
#define ENC_A_Pin GPIO_PIN_8
#define ENC_A_GPIO_Port GPIOA
#define VREF_1_65V_Pin GPIO_PIN_2
#define VREF_1_65V_GPIO_Port GPIOC
#define OLED_DIN_Pin GPIO_PIN_6
#define OLED_DIN_GPIO_Port GPIOE
#define CAN0_TX_Pin GPIO_PIN_1
#define CAN0_TX_GPIO_Port GPIOD
#define OUT1_Pin GPIO_PIN_7
#define OUT1_GPIO_Port GPIOC
#define ACCUM_V_Pin GPIO_PIN_0
#define ACCUM_V_GPIO_Port GPIOC
#define INVERT_V_Pin GPIO_PIN_1
#define INVERT_V_GPIO_Port GPIOC
#define SPI1_MOSI_Pin GPIO_PIN_3
#define SPI1_MOSI_GPIO_Port GPIOC
#define OUT2_Pin GPIO_PIN_6
#define OUT2_GPIO_Port GPIOC
#define PSRC_I_Pin GPIO_PIN_4
#define PSRC_I_GPIO_Port GPIOC
#define UART1_RTS_Pin GPIO_PIN_15
#define UART1_RTS_GPIO_Port GPIOD
#define LEDCAN0_Pin GPIO_PIN_11
#define LEDCAN0_GPIO_Port GPIOD
#define CANCTRL_Pin GPIO_PIN_15
#define CANCTRL_GPIO_Port GPIOB
#define SPI0_SCK_Pin GPIO_PIN_5
#define SPI0_SCK_GPIO_Port GPIOA
#define MAINS_PATH_STATE_Pin GPIO_PIN_5
#define MAINS_PATH_STATE_GPIO_Port GPIOC
#define INVSW_FAULT_Pin GPIO_PIN_7
#define INVSW_FAULT_GPIO_Port GPIOE
#define ENC_B_Pin GPIO_PIN_11
#define ENC_B_GPIO_Port GPIOE
#define SW_MAINS_PATH_Pin GPIO_PIN_10
#define SW_MAINS_PATH_GPIO_Port GPIOD
#define SPI1_MISO_Pin GPIO_PIN_14
#define SPI1_MISO_GPIO_Port GPIOB
#define PWR24_V_Pin GPIO_PIN_2
#define PWR24_V_GPIO_Port GPIOA
#define ACCUM_ID_I_Pin GPIO_PIN_6
#define ACCUM_ID_I_GPIO_Port GPIOA
#define INV_PATH_STATE_Pin GPIO_PIN_0
#define INV_PATH_STATE_GPIO_Port GPIOB
#define INVSW_ON_Pin GPIO_PIN_8
#define INVSW_ON_GPIO_Port GPIOE
#define DCDC_PGOOD_Pin GPIO_PIN_12
#define DCDC_PGOOD_GPIO_Port GPIOE
#define LED_RD_Pin GPIO_PIN_10
#define LED_RD_GPIO_Port GPIOB
#define AIDS_SHDN_Pin GPIO_PIN_13
#define AIDS_SHDN_GPIO_Port GPIOB
#define SW_INV_PATH_Pin GPIO_PIN_9
#define SW_INV_PATH_GPIO_Port GPIOD
#define ENC_SW_Pin GPIO_PIN_13
#define ENC_SW_GPIO_Port GPIOD
#define PSRC_V_Pin GPIO_PIN_3
#define PSRC_V_GPIO_Port GPIOA
#define ACCUM_I_Pin GPIO_PIN_7
#define ACCUM_I_GPIO_Port GPIOA
#define INVERT_I_Pin GPIO_PIN_1
#define INVERT_I_GPIO_Port GPIOB
#define EN_CHARGER_Pin GPIO_PIN_9
#define EN_CHARGER_GPIO_Port GPIOE
#define DCDC_MODE_Pin GPIO_PIN_13
#define DCDC_MODE_GPIO_Port GPIOE
#define AIDS_FAUL_Pin GPIO_PIN_11
#define AIDS_FAUL_GPIO_Port GPIOB
#define AIDS_FBC_Pin GPIO_PIN_12
#define AIDS_FBC_GPIO_Port GPIOB
#define PIDS_SHDN_Pin GPIO_PIN_8
#define PIDS_SHDN_GPIO_Port GPIOD
#define PIDS_FAULT_Pin GPIO_PIN_12
#define PIDS_FAULT_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
