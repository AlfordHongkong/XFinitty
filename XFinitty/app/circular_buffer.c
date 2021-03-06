/**
 * @file circular_buffer.c
 * @author Rock Deng
 * @brief 
 * @version 0.1
 * @date 2018-11-15
 * 
 * @copyright Copyright (c) 2018
 * 
 */


#include "circular_buffer.h"
#include "string.h"


uint8_t InitCircularBuf(circularBuffer_t *cb, uint8_t buf[], uint8_t buf_size){
    /// assert two arguments
    if ( (!buf_size || (buf_size & (buf_size - 1))) != 0) { return 1;} ///< size is not a power of tow

    cb->buf = buf;
    cb->size = buf_size;
    cb->read = 0;
    cb->write = 0;

    for (int i=0; i<buf_size; i++){
        buf[i] = 0;
    }

    return 0;
}

uint8_t GetLengthOfCircularBuf(circularBuffer_t *cb){
    return ((cb->write - cb->read) & (cb->size -1));
}

circular_buf_error_t WriteCircularBuf(circularBuffer_t *cb, uint8_t data){
    if (GetLengthOfCircularBuf(cb) == (cb->size-1)) { return error_buffer_full;}
    cb->buf[cb->write] = data;
    cb->write = (cb->write + 1) & (cb->size -1); // must be atomic

    return no_error;
}
circular_buf_error_t ReadCircularBuf(circularBuffer_t *cb, uint8_t *data){
    if (GetLengthOfCircularBuf(cb) == 0) { return error_buffer_empty;}
    *data = cb->buf[cb->read];
    cb->read = (cb->read +1) & (cb->size - 1);

    return no_error;
}

uint8_t CleanCircularBuffer(circularBuffer_t *cb){
    uint8_t data;
    while (ReadCircularBuf(cb, &data) == no_error){

    }

    return 0;
}


