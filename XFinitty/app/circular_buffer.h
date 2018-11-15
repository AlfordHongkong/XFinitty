


#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include "stdint.h"

typedef struct{
    uint8_t *buf;
    uint8_t size;
    uint8_t read;
    uint8_t write;
}circularBuffer_t;


uint8_t InitCircularBuffer();
uint8_t GetLengthOfCircularBuf();
uint8_t ReadCircularBuf();
uint8_t WriteCircularBuf();


#endif

