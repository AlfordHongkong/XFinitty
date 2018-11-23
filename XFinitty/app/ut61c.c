/**
 * @file ut61c.c
 * @author Rock Deng(dengyongpeng110@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-22
 * 
 * @copyright Copyright (c) 2018
 * 
 */


#include "ut61c.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"


#define UA_UART USART2
#define MA_UART USART3
#define UT61C_PROTOCOL_SIZE 14
#define UT61C_FETCHING_SEZE (UT61C_PROTOCOL_SIZE * 4)

#define SIZE_OF_METER_CB 128
circularBuffer_t uAmeter_cb;
circularBuffer_t mAmeter_cb;
uint8_t uAbuf[SIZE_OF_METER_CB];
uint8_t mAbuf[SIZE_OF_METER_CB];
uint8_t temp_ua_current_data[100];
uint8_t temp_ma_current_data[100];


static void ResetTempUA_array(void){
    for(int i=0; i<100; i++){
        temp_ua_current_data[i] = '*';
    }
}

static void ResetTempMA_array(void){
    for(int i=0; i<100; i++){
        temp_ma_current_data[i] = '*';
    }
}

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


uint8_t EnableFetchingMA(void){
    ResetTempMA_array();
    if (HAL_UART_Receive_DMA(&huart3, temp_ma_current_data, UT61C_FETCHING_SEZE) != HAL_OK){
        //Error_Handler();
        return 1;
    }

    return 0;
}

uint8_t DisableFetchingUA(void){
    return 0;
}

uint8_t EnableFetchingUA(void){
    ResetTempUA_array();
    if (HAL_UART_Receive_DMA(&huart2, temp_ua_current_data, UT61C_FETCHING_SEZE) != HAL_OK){
        //Error_Handler();
        return 1;
    }

    return 0;
}

uint8_t DisableFetchingMA(void){
    return 0;
}




static uint8_t NumberCheck(uint8_t _char){
    if ((_char >= '0') && (_char <= '9')){
        return 0;
    }

    return 1;
}


#define USEFUL_DATA_SIZE 10

typedef enum{
	no_measure_error,
    no_original_data,
    data_byte_error,

}multimeter_measure_error_t;

typedef struct {
    uint8_t write;
    uint8_t size;
    uint8_t flag_full;
    uint8_t *buf;
}overwrite_ring_buffer_t;

static uint8_t InitOverwriteRingbuffer(overwrite_ring_buffer_t *ow_ring_buf, uint8_t *buff_array){
    ow_ring_buf->write = 0;
    ow_ring_buf->size = USEFUL_DATA_SIZE;
    ow_ring_buf->flag_full = 0;
    ow_ring_buf->buf = buff_array;

    return 0;
}

static uint8_t WriteOWRingbuf(overwrite_ring_buffer_t *ow_ring_buf, uint8_t data){
    if (ow_ring_buf->flag_full == 0){
        *(ow_ring_buf->buf + ow_ring_buf->write) = data;
        ow_ring_buf->write++;
        if (ow_ring_buf->write >= ow_ring_buf->size){
            ow_ring_buf->flag_full = 1;
        }
        
    }
    else {
        for (int i=0; i<USEFUL_DATA_SIZE-1; i++){
            ow_ring_buf->buf[i] = ow_ring_buf->buf[i+1];
        }
        ow_ring_buf->buf[USEFUL_DATA_SIZE -1] = data;
    }
    

    return 0;
}
uint8_t AnalyzeUAData(void){
    uint8_t data = 0;
    uint8_t count = 0;
    overwrite_ring_buffer_t ow_ring_buf;
    uint8_t data_array[USEFUL_DATA_SIZE];
    float current = 0;
    InitOverwriteRingbuffer(&ow_ring_buf, data_array);
    /// write data to circular buffer
    for (int i=0; i<UT61C_FETCHING_SEZE; i++){
        WriteCircularBuf(&uAmeter_cb, temp_ua_current_data[i]);
    }
    printf(">>>>uA origin data: \n");
    while (ReadCircularBuf(&uAmeter_cb, &data) == no_error){
        count++;
        WriteOWRingbuf(&ow_ring_buf, data);
        if (ow_ring_buf.flag_full != 0){  ///< the buff is full
            if ((NumberCheck(ow_ring_buf.buf[0]) == 0)
                && (NumberCheck(ow_ring_buf.buf[1]) == 0)
                && (NumberCheck(ow_ring_buf.buf[2]) == 0)
                && (NumberCheck(ow_ring_buf.buf[3]) == 0)
                && (ow_ring_buf.buf[4] = ' ')
                && (ow_ring_buf.buf[8] = 0x80)
                && (ow_ring_buf.buf[9] = 0x40)){
                
                current = ow_ring_buf.buf[0] * 1000 \
                          + ow_ring_buf.buf[1] * 100 \
                          + ow_ring_buf.buf[2] * 10 \
                          + ow_ring_buf.buf[3];                 
                
            }
                
            
        }
        // if (ow_ring_buf.buff_array[0])

        printf("%c", data);
    }

    printf("    The real current is %f\n", current);

    return 0;
}




/**
 * @brief 
 * 
 * @note - 2B    30 30 30 30 20 34 31 00 80 40    80 0D 0A
 * @return uint8_t 
 */
multimeter_measure_error_t AnalyzeMAData(void){
	uint8_t data = 0;
    uint8_t count = 0;
    overwrite_ring_buffer_t ow_ring_buf;
    uint8_t data_array[USEFUL_DATA_SIZE];
    float current = 0;
    InitOverwriteRingbuffer(&ow_ring_buf, data_array);
    /// write data to circular buffer
    for (int i=0; i<UT61C_FETCHING_SEZE; i++){
        WriteCircularBuf(&mAmeter_cb, temp_ma_current_data[i]);
    }
    printf(">>>>mA origin data: \n");
    while (ReadCircularBuf(&mAmeter_cb, &data) == no_error){
        count++;
        WriteOWRingbuf(&ow_ring_buf, data);
        if (ow_ring_buf.flag_full != 0){  ///< the buff is full
            if ((NumberCheck(ow_ring_buf.buf[0]) == 0)
                && (NumberCheck(ow_ring_buf.buf[1]) == 0)
                && (NumberCheck(ow_ring_buf.buf[2]) == 0)
                && (NumberCheck(ow_ring_buf.buf[3]) == 0)
                && (ow_ring_buf.buf[4] = ' ')
                && (ow_ring_buf.buf[8] = 0x80)
                && (ow_ring_buf.buf[9] = 0x40)){
                
                current = ow_ring_buf.buf[0] * 1000 \
                          + ow_ring_buf.buf[1] * 100 \
                          + ow_ring_buf.buf[2] * 10 \
                          + ow_ring_buf.buf[3];
                
            }
                
            
        }
        // if (ow_ring_buf.buff_array[0])
        

        printf("%c", data);
    }
    if (count == 0){
        return no_original_data;
    }

    printf("    The real current is %f\n", current);
    return no_measure_error;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//    uint8_t temp2, temp3;
   if (huart->Instance == UA_UART){
    //    HAL_UART_Receive_IT(&huart2, &temp2, 1);
    //    WriteCircularBuf(&uAmeter_cb, temp2);
    //    HAL_UART_Transmit_IT(&huart2, &temp2, 1);
   
   }
   else if (huart->Instance == MA_UART){
    //    HAL_UART_Receive_IT(&huart3, &temp3, 1);
    //    WriteCircularBuf(&mAmeter_cb, temp3);
    //    HAL_UART_Transmit_IT(&huart3, &temp3, 1);
   }
   else{

   }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(huart); 
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_ErrorCallback could be implemented in the user file
   */ 
}

void TestUT61(void){
    // uint8_t data;
    // CleanCircularBuffer(&uAmeter_cb);
    // CleanCircularBuffer(&mAmeter_cb);
    // osDelay(2000);
    // printf(">>uA data: \n");
    // while (ReadCircularBuf(&uAmeter_cb, &data) == no_error){
    //     printf("%c", data);
    // }
    // printf("\n\n");
    // printf(">>mA data: \n");
    // while (ReadCircularBuf(&mAmeter_cb, &data) == no_error){
    //     printf("%c", data);
    // }
    // printf("\n\n");
    EnableFetchingUA();
    EnableFetchingMA();
    osDelay(3000);
    AnalyzeUAData();
    AnalyzeMAData();

}





