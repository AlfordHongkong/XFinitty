/**
 * @file adc_led.h
 * @author Rock Deng (dengyongpeng110@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-20
 * 
 * @copyright Copyright (c) 2018
 * 
 */


#ifndef __ADC_LED_H
#define __ADC_LED_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "adc_led.h"
#include "circular_buffer.h"


#define LED_PLUS_shreshold 200

#define EnableLedPlusTest() ActRelay(2); \
                                HAL_Delay(100)
#define DisableLedPlusTest() ReleaseRelay(2); \
                                HAL_Delay(100)
#define EnableLedMinusTest() ActRelay(8); \
                                HAL_Delay(100)
#define DisableLedMinusTest() ReleaseRelay(8); \
                                HAL_Delay(100)

                                
void EnableAdcFetching(void);

void DisableAdcFetching(void);

/**
 * @brief Init adc software for led detection
 * 
 */
void InitAdcLed(void);

/**
 * @brief start converting adc
 * 
 * @return uint8_t 
 */
uint8_t WriteAdcData(void);


/**
 * @brief Read Adc data from buffer
 * 
 * @param which_channel - indicate channel, it could be 0, 1, 2, 3.
 * @param data - the data read out of buffer
 * @return uint8_t - 0 means return success.
 */
uint8_t ReadAdcData(uint8_t which_channel, uint8_t *data);

/**
 * @brief clean all four channels' buffer.
 * 
 */
void CleanAllAdcBuffer(void);

circularBuffer_t *GetLedMinusCB(void);
circularBuffer_t *GetLedPlusCB(void);

uint8_t AnalyzeLed2(void);

#endif


