


#ifndef __BSP_H__
#define __BSP_H__


#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "main.h"


#define ActRelay(relay_x) HAL_GPIO_WritePin(relay_x##_GPIO_Port, relay_x##_Pin, GPIO_PIN_RESET)
#define ReleaseRelay(relay_x) HAL_GPIO_WritePin(relay_x##_GPIO_Port, relay_x##_Pin, GPIO_PIN_SET)

#define TurnOnLed(led_x) HAL_GPIO_WritePin(led_x##_GPIO_Port, led_x##_Pin, GPIO_PIN_RESET)
#define TurnOffLed(led_x) HAL_GPIO_WritePin(led_x##_GPIO_Port, led_x##_Pin, GPIO_PIN_SET)



#endif

