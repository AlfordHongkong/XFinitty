


#ifndef __BSP_H__
#define __BSP_H__


#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "main.h"

/**
 * @brief for switching 3 different resistances
 * 
 */
typedef enum{
    resistance_10k,
    resistance_2k7,
    resistance_3k85,

}which_resistance_t;


/**
 * @brief for switching 3 different power
 * 
 */
typedef enum{
    power_4v1,
    power_3v3,
    power_3v06,
}which_power_t;


/**
 * @brief for switch 2 different multi-meter
 * 
 */
typedef enum{
    ua_meter,
    ma_meter,
}which_meter_t;



#define ActRelay(relay_x) HAL_GPIO_WritePin(RELAY_##relay_x##_GPIO_Port, RELAY_##relay_x##_Pin, GPIO_PIN_SET)
#define ReleaseRelay(relay_x) HAL_GPIO_WritePin(RELAY_##relay_x##_GPIO_Port, RELAY_##relay_x##_Pin, GPIO_PIN_RESET)

#define TurnOnLed(led_x) HAL_GPIO_WritePin(led_x##_GPIO_Port, led_x##_Pin, GPIO_PIN_RESET)
#define TurnOffLed(led_x) HAL_GPIO_WritePin(led_x##_GPIO_Port, led_x##_Pin, GPIO_PIN_SET)


uint8_t ChangeResistance(which_resistance_t which_resistance);

uint8_t ChangePower(which_power_t which_powre);

uint8_t ChangeMeter(which_meter_t meter);

 void TestRelay(void);

#endif

