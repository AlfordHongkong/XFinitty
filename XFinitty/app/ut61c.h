

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



/**
 * @brief UT61C test
 * 
 */
void TestUT61(void);

#endif


