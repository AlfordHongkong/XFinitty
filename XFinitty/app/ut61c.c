


#include "ut61c.h"
#include "circular_buffer.h"
#include "stm32f1xx_hal.h"

#define UA_UART USART2
#define MA_UART USART3

#define SIZE_OF_METER_CB 64
circularBuffer_t uAmeter_cb;
circularBuffer_t mAmeter_cb;
uint8_t uAbuf[SIZE_OF_METER_CB];
uint8_t mAbuf[SIZE_OF_METER_CB];


void InitUT61C(void){
    InitCircularBuf(&uAmeter_cb, uAbuf, SIZE_OF_METER_CB);
    InitCircularBuf(&mAmeter_cb, mAbuf, SIZE_OF_METER_CB);
}

circularBuffer_t *GetuACircularBuffer(void){
    return &uAmeter_cb;
}


circularBuffer_t *GetmACircularBuffer(void){
    return &mAmeter_cb;
}


 
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t temp2, temp3;
   if (huart->Instance == UA_UART){
       HAL_UART_Receive_IT(&huart2, &temp2, 1);
       WriteCircularBuf(&uAmeter_cb, temp2);
   
   }
   else if (huart->Instance == MA_UART){
       HAL_UART_Receive_IT(&huart3, &temp3, 1);
       WriteCircularBuf(&mAmeter_cb, temp3);
   }
   else{

   }
}
// HAL_UART_RxCpltCallback



