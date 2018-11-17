/**
 * @file circular_buffer.h
 * @author Rock Deng
 * @brief 
 * @version 0.1
 * @date 2018-11-15
 * 
 * @copyright Copyright (c) 2018
 * 
 */


#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include "stdint.h"

/**
 * @brief buffer structure
 * 
 */
typedef struct{
    uint8_t *buf; ///< block of memory
    uint8_t size; ///< must be a power of two
    uint8_t read; ///< holds current read position: 0 to (size-1)
    uint8_t write; ///< holds current write position: 0 to (size-1)
}circularBuffer_t;

/**
 * @brief error flag 
 * 
 */
typedef enum{
    no_error,
    error_buffer_full,
    error_buffer_empty,

}circular_buf_error_t;

/**
 * @brief Initialize a circular buffer structer
 * 
 * @param cb - pointer of the circular buffer structer
 * @param buf - pointer of the buffer
 * @return uint8_t - 1 means error, 0 means success
 */
uint8_t InitCircularBuf(circularBuffer_t *cb, uint8_t buf[], uint8_t buf_size);

/**
 * @brief Get the Length Of Circular Buf object
 * 
 * @param cb - pointer of the circular buffer
 * @return uint8_t - 1 means error, 0 means success
 */
uint8_t GetLengthOfCircularBuf(circularBuffer_t *cb);

/**
 * @brief get a item for the circular buffer
 * 
 * @param cb - pointer of the circular buff
 * @param data - the data return from the buffer
 * @return circular_buf_error_t - state of the processing
 */
circular_buf_error_t ReadCircularBuf(circularBuffer_t *cb, uint8_t *data);

/**
 * @brief write a data into the buffer
 * 
 * @param cb - pointer of the buffer structure
 * @param data - the data to be write
 * @return circular_buf_error_t - state of the processing
 */
circular_buf_error_t WriteCircularBuf(circularBuffer_t *cb, uint8_t data);

#endif

