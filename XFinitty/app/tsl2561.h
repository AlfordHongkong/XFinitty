

#ifndef __TSL2561_H__
#define __TSL2561_H__


#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "circular_buffer.h"



/**
 * @brief Initialize the tsl2561 module
 * 
 */
void InitTSL2561(void);

/**
 * @brief power up tsl2561 and it's adc start convert
 * 
 * @return uint8_t - 0 means return success
 */
uint8_t PowerUpTSL2561(void);

/**
 * @brief power down the tsl2561 and it's adc stop convert
 * 
 * @return uint8_t - 0 means success
 */
uint8_t PowerDownTSL2561(void);


/**
 * @brief Set the Integrate Time 4 T S L 2 5 6 1 object
 * 
 * @param integ - 0x00 for 13.7ms; 0x10(default) for 402ms
 * @return uint8_t - 0 means return success
 */
uint8_t SetIntegrateTime4TSL2561(uint8_t integ);

/**
 * @brief Get the High Byte Light object
 *        This data is the data0 high in tsl2561.
 * 
 * @return uint8_t 
 */
uint8_t GetHighByteLight(void);

/**
 * @brief for this driver testing
 * 
 */
void TestTSL2561(void);


/**
 * @brief get a light data and write it to buffer
 * 
 * @return uint8_t - 0 means return success
 */
uint8_t WriteLight(void);

/**
 * @brief read a light data from buffer.
 * 
 * @param light - the data pass to light
 * @return uint8_t - 0 means return success
 */
uint8_t ReadLight(uint8_t *light);

/**
 * @brief clear all light data in the buffer
 * 
 * @return uint8_t - 0 means return success
 */
uint8_t ClearAllLightData(void);

circularBuffer_t *GetLightCB(void);

#endif

