


#include "adc_led.h"
#include "bsp.h"
#include "circular_buffer.h"


extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

//__io uint16_t adcLedBuf[4];

#define ADC_BUFFER_SIZE 64

uint8_t channel0_buffer[ADC_BUFFER_SIZE];
uint8_t channel1_buffer[ADC_BUFFER_SIZE];
uint8_t temp_sensor_buffer[ADC_BUFFER_SIZE];
uint8_t vrefint_buffer[ADC_BUFFER_SIZE];
circularBuffer_t channel1_cb;
circularBuffer_t channel0_cb;
circularBuffer_t temp_sersor_cb;
circularBuffer_t vrefint_cb;

void InitAdcLed(void){
   InitCircularBuf(&channel0_cb, channel0_buffer, ADC_BUFFER_SIZE);
   InitCircularBuf(&channel1_cb, channel1_buffer, ADC_BUFFER_SIZE);
   InitCircularBuf(&temp_sersor_cb, temp_sensor_buffer, ADC_BUFFER_SIZE);
   InitCircularBuf(&vrefint_cb, vrefint_buffer, ADC_BUFFER_SIZE);
    /// 
    ActRelay(2);
    ActRelay(8);
}

uint8_t WriteAdcData(void){
    uint32_t adc_array[4] = {0, 0, 0, 0};

    HAL_ADC_Start_DMA(&hadc1, adc_array, 4);
    // HAL_ADC_Start_IT();

    return 0;
}
