

#ifndef __UT61C_H__
#define __UT61C_H__


#include "circular_buffer.h"

/**
 * @brief initilize two circular buffer for uA meter and mA meter
 * 
 */
void InitUT61C(void);


/**
 * @brief get the uA cb
 * 
 * @return circularBuffer_t* 
 */
circularBuffer_t *GetuACircularBuffer(void);

/**
 * @brief get the mA cb
 * 
 * @return circularBuffer_t* 
 */
circularBuffer_t *GetmACircularBuffer(void);


uint8_t EnableFetchingUA(void);

uint8_t DisableFetchingUA(void);

uint8_t EnableFetchingMA(void);

uint8_t DisableFetchingMA(void);



uint8_t AnalyzeUAData(void);


uint8_t AnalyzeMAData(void);

/**
 * @brief UT61C test
 * 
 */
void TestUT61(void);

#endif


