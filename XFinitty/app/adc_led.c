


#include "adc_led.h"
#include "bsp.h"
#include "circular_buffer.h"


extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

//__io uint16_t adcLedBuf[4];


#define ADC_BUFFER_SIZE 64
#define CHANNEL_NUM 4

__IO uint16_t adcConvertedValues[CHANNEL_NUM];

uint8_t channel0_buffer[ADC_BUFFER_SIZE];
uint8_t channel1_buffer[ADC_BUFFER_SIZE];
uint8_t temp_sensor_buffer[ADC_BUFFER_SIZE];
uint8_t vrefint_buffer[ADC_BUFFER_SIZE];
circularBuffer_t channel1_cb;
circularBuffer_t channel0_cb;
circularBuffer_t temp_sersor_cb;
circularBuffer_t vrefint_cb;

void ResetAdcConvertedValues(void){
    for (int i=0; i<4; i++){
        adcConvertedValues[i] = 0;
    }
}

void InitAdcLed(void){
   
   ResetAdcConvertedValues();
   InitCircularBuf(&channel0_cb, channel0_buffer, ADC_BUFFER_SIZE);
   InitCircularBuf(&channel1_cb, channel1_buffer, ADC_BUFFER_SIZE);
   InitCircularBuf(&temp_sersor_cb, temp_sensor_buffer, ADC_BUFFER_SIZE);
   InitCircularBuf(&vrefint_cb, vrefint_buffer, ADC_BUFFER_SIZE);
    /// 
    ActRelay(2);
    ActRelay(8);
    HAL_Delay(100);  ///< for relay delay

    /// adc calibration
    if (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK){
        Error_Handler();
    }
    /// start adc conversion on regular group with transfer by DMA
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcConvertedValues, CHANNEL_NUM) != HAL_OK){
        Error_Handler();
    }
}

uint8_t WriteAdcData(void){

    /// 
    // HAL_ADC_Start_IT(&hadc1);
    // __HAL_ADC_ENABLE_IT(&hadc1, ADC_IT_EOC);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcConvertedValues, 4);
    // HAL_ADC_Start_IT(&hadc1);

    

    return 0;
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    // static uint8_t sequence = 0;
    // uint32_t value_adc = 0;
    // uint8_t value_adc8 = 0;
    // if (hadc == &hadc1){
    //     value_adc = HAL_ADC_GetValue(&hadc1);
    //     value_adc8 = (uint8_t)(value_adc >> 4);
    //     if (sequence++ >= 4){
    //         sequence = 0;
    //     }

    //     switch (sequence) {
    //         case 0:
    //         WriteCircularBuf(&channel0_cb, value_adc8);
    //         break;

    //         case 1:
    //         WriteCircularBuf(&channel1_cb, value_adc8);
    //         break;

    //         case 2:
    //         WriteCircularBuf(&temp_sersor_cb, value_adc8);
    //         break;

    //         case 3:
    //         WriteCircularBuf(&vrefint_cb, value_adc8);
    //         break;

    //         default:
    //         break;
    //     }
    // }

    WriteCircularBuf(&channel0_cb, (uint8_t)(adcConvertedValues[0] >> 4));
    WriteCircularBuf(&channel1_cb, (uint8_t)(adcConvertedValues[1] >> 4));
    WriteCircularBuf(&temp_sersor_cb, (uint8_t)(adcConvertedValues[2] >> 4));
    WriteCircularBuf(&vrefint_cb, (uint8_t)(adcConvertedValues[3] >> 4));

    ResetAdcConvertedValues();
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc){
    while(1);
}

uint8_t ReadAdcData(uint8_t which_channel, uint8_t *value_adc){

    circular_buf_error_t error = no_error;
    switch (which_channel){
        case 0:
        error = ReadCircularBuf(&channel0_cb, value_adc);
        break;

        case 1:
        error = ReadCircularBuf(&channel1_cb, value_adc);
        break;

        case 2:
        error = ReadCircularBuf(&temp_sersor_cb, value_adc);
        break;

        case 3:
        error = ReadCircularBuf(&vrefint_cb, value_adc);
        break;

        default:
        break;
    }

    if (error == error_buffer_empty){
        return 1;
    }

    return 0;
}
