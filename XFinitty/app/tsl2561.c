



#include "tsl2561.h"


extern I2C_HandleTypeDef hi2c1;


#define ADDR_TSL2561 (0x72)
#define NORMAL_COMMAND (0x80)  ///< last 3 bits is the rigister address which to be read or write
#define CONTROL_REGISTER_POWRE_ON (0x03)  ///< control register addr == 0x00
#define CONTROL_REGISTER_POWRE_OFF (0X00)


#define LIGHT_BUFFER_SIZE 128
circularBuffer_t light_cb;
uint8_t light_cb_array[LIGHT_BUFFER_SIZE];


circularBuffer_t *GetLightCB(void){
    return &light_cb;
}

void InitTSL2561(void){
    PowerUpTSL2561();
    SetIntegrateTime4TSL2561(0);

    InitCircularBuf(&light_cb, light_cb_array, LIGHT_BUFFER_SIZE);
}

uint8_t PowerUpTSL2561(void){
    uint8_t sendingData[2];
    sendingData[0] = 0x80;  ///< this byte is the command for tsl2561
    sendingData[1] = 0x03;  ///< this byte is setting at control register of tsl2561 and it will powre on it.
    if (HAL_I2C_Master_Transmit_IT(&hi2c1, ADDR_TSL2561, sendingData, 2) != HAL_OK)
        return 1;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}

    return 0;
}

uint8_t PowerDownTSL2561(void){
    uint8_t sendingData[2];
    sendingData[0] = 0x80;  ///< this byte is the command for tsl2561
    sendingData[1] = 0x00;  ///< this byte is setting at control register of tsl2561 and it will powre off it.
    if (HAL_I2C_Master_Transmit_IT(&hi2c1, ADDR_TSL2561, sendingData, 2) != HAL_OK)
        return 1;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}

    return 0;
}

/**
 * @brief Set the Integrate Time 4 T S L 2 5 6 1 object
 * 
 * @param integ - 0x00 for 13.7ms; 0x10(default) for 402ms
 * @return uint8_t 
 */
uint8_t SetIntegrateTime4TSL2561(uint8_t integ){
    uint8_t sendingData[2];
    sendingData[0] = 0x81;  ///< this byte is the command for tsl2561, the timing register address is 1h
    sendingData[1] = integ;  ///< set INTEG bits to 0 can modify integrate time to 13.7ms
    if (HAL_I2C_Master_Transmit_IT(&hi2c1, ADDR_TSL2561, sendingData, 2) != HAL_OK)
        return 1;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}

    return 0;
}

uint8_t GetHighByteLight(void){
    uint8_t command = 0x8D; 
    uint8_t highByteLight = 0;
    if (HAL_I2C_Master_Transmit_IT(&hi2c1, ADDR_TSL2561, &command, 1) != HAL_OK)
        return 0;
    /// waite a acknowledge
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
    /// receive data
    if (HAL_I2C_Master_Receive_IT(&hi2c1, ADDR_TSL2561, &highByteLight, 1) != HAL_OK)
        return 0;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}

    printf("TSL2561: %d\n", highByteLight);

    return 0;
}

uint8_t GetLightBytes(uint16_t *light){
    uint8_t command = 0x8C; ///< the addresses of DATA0LOW and DATA0HIGH are Ch & Dh
    uint8_t lightBytes[2] = {0, 0};
    if (HAL_I2C_Master_Transmit_IT(&hi2c1, ADDR_TSL2561, &command, 1) != HAL_OK)
        return 0;
    /// waite a acknowledge
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
    /// receive data
    if (HAL_I2C_Master_Receive_IT(&hi2c1, ADDR_TSL2561, lightBytes, 2) != HAL_OK)
        return 0;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
    *light = lightBytes[1] * 256 + lightBytes[0];

    return 0;
}

uint8_t WriteLight(void){
    uint16_t light = 0;
    uint8_t light8 = 0;
    GetLightBytes(&light);
    light /= 3;
    if (light > 255) {
        light8 = 255;
    }
    else {
        light8 = (uint8_t)(light);
    }
    
    if( WriteCircularBuf(&light_cb, light8) == error_buffer_full)
        return 1;

    return 0;
}

uint8_t ReadLight(uint8_t *light){
    if (ReadCircularBuf(&light_cb, light) == error_buffer_empty)
        return 1;

    return 0;
}

uint8_t ClearAllLightData(void){
    uint8_t light = 0;
    while(ReadCircularBuf(&light_cb, &light) != error_buffer_empty){}

    return 0;
}

uint8_t GetAllRegisterOfTSL2561(uint8_t *array, uint8_t array_size){
    if (array_size < 16) {
        return 1;
    }
    if (array == NULL){
        return 1;
    }
    uint8_t command = 0x80;
    /// send write command
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
    HAL_I2C_Master_Transmit_IT(&hi2c1, ADDR_TSL2561, &command, 1);
    /// waite a acknowledge
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
    /// receive data
    HAL_I2C_Master_Receive_IT(&hi2c1, ADDR_TSL2561, array, 16);
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}

    return 0;
}






extern UART_HandleTypeDef huart1;

void TestTSL2561(void){

    uint8_t readingDate[16] = { 0, 0, 0, 0, \
                                0, 0, 0, 0, \
                                0, 0, 0, 0, \
                                0, 0, 0, 0};
    // PowerUpTSL2561();
    // SetIntegrateTime4TSL2561(0);
    GetAllRegisterOfTSL2561(readingDate, 16);
    // PowerDownTSL2561();
    // SetIntegrateTime4TSL2561(0x02);
    GetAllRegisterOfTSL2561(readingDate, 16);

    // uint16_t light = 0;
    // GetLightBytes(&light);

    //printf("%d\n", light);
    
}



void ScanSensorData(void){

}
