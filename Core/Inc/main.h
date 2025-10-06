/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_CURRENT_1_Pin GPIO_PIN_0
#define ADC_CURRENT_1_GPIO_Port GPIOC
#define ADC_CURRENT_2_Pin GPIO_PIN_1
#define ADC_CURRENT_2_GPIO_Port GPIOC
#define ADC_CURRENT_3_Pin GPIO_PIN_2
#define ADC_CURRENT_3_GPIO_Port GPIOC
#define ADC_1_Pin GPIO_PIN_3
#define ADC_1_GPIO_Port GPIOC
#define VOLTAGE_1_Pin GPIO_PIN_0
#define VOLTAGE_1_GPIO_Port GPIOA
#define VOLTAGE_2_Pin GPIO_PIN_1
#define VOLTAGE_2_GPIO_Port GPIOA
#define VOLTAGE_3_Pin GPIO_PIN_2
#define VOLTAGE_3_GPIO_Port GPIOA
#define ADC_TEMP_Pin GPIO_PIN_3
#define ADC_TEMP_GPIO_Port GPIOA
#define ADC_TEMPMOTOR_Pin GPIO_PIN_4
#define ADC_TEMPMOTOR_GPIO_Port GPIOC
#define GPIO_LED_1_Pin GPIO_PIN_0
#define GPIO_LED_1_GPIO_Port GPIOB
#define GPIO_LED_2_Pin GPIO_PIN_1
#define GPIO_LED_2_GPIO_Port GPIOB
#define GATE_L1_Pin GPIO_PIN_13
#define GATE_L1_GPIO_Port GPIOB
#define GATE_L2_Pin GPIO_PIN_14
#define GATE_L2_GPIO_Port GPIOB
#define GATE_L3_Pin GPIO_PIN_15
#define GATE_L3_GPIO_Port GPIOB
#define ANALOG_HAL1_Pin GPIO_PIN_6
#define ANALOG_HAL1_GPIO_Port GPIOC
#define ANALOG_HAL2_Pin GPIO_PIN_7
#define ANALOG_HAL2_GPIO_Port GPIOC
#define ANALOG_HAL3_Pin GPIO_PIN_8
#define ANALOG_HAL3_GPIO_Port GPIOC
#define GATE_H1_Pin GPIO_PIN_8
#define GATE_H1_GPIO_Port GPIOA
#define GATE_H2_Pin GPIO_PIN_9
#define GATE_H2_GPIO_Port GPIOA
#define GATE_H3_Pin GPIO_PIN_10
#define GATE_H3_GPIO_Port GPIOA
#define SPI3_EN_ENGATE_Pin GPIO_PIN_5
#define SPI3_EN_ENGATE_GPIO_Port GPIOB
#define GPIO_FAULT_Pin GPIO_PIN_7
#define GPIO_FAULT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
