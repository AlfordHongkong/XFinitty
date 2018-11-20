


#ifndef __ADC_LED_H
#define __ADC_LED_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"


void InitAdcLed(void);

/**
 * @brief start converting adc
 * 
 * @return uint8_t 
 */
uint8_t WriteAdcData(void);

uint8_t ReadAdcData(uint8_t which_channel, uint8_t *data);

#endif


