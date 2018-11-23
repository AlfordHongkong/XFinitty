/**
 * @file line_analyze.c
 * @author RocK Deng (dengyongpeng110@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-24
 * 
 * @copyright Copyright (c) 2018
 * 
 */


#include "line_analyze.h"
#include "stdint.h"
#include "stdio.h"


/**
 * @brief line direction
 * 
 */
typedef enum{
    up, 
    down,
}line_direction_t;


/**
 * @brief printf a light signla
 * 
 * @param light_signal - 
 * @return uint8_t -
 */
static uint8_t PrintLightSignal(light_signal_t light_signal);


/**
 * @brief 将数据看一条曲线，从第一个不为零的数开始计算，分析曲线的上次次数up_count下降次数down_count，以及为零的峰峰值数量
 * 
 * @param buff - data to be analyze
 * @param light_signal - return the type of light signale
 * @return uint8_t - 0 means sucess
 */
uint8_t AnalyzeLightData(circularBuffer_t *buff, light_signal_t *light_signal){
    line_type_t line_type;
    *light_signal = light_unknow;
    uint8_t new_data = 0;
    uint8_t last_data = 0;
    // uint8_t data_count = 0;
    // uint8_t line_length = 0;
    // uint8_t all_count = 0;
    // line_t lines[20];
    line_type.up_count = 0;
    line_type.down_count = 0;
    line_type.zero_count = 0;
    uint8_t sum_count = 0;
    line_direction_t direction = up;
    
    printf("\n>>>>light:  ");
    while (ReadCircularBuf(buff, &new_data) == no_error){
        if (direction == up){
            if (new_data < last_data){
                direction = down;
                line_type.down_count++; 
            }
        }
        else {
            if (new_data > last_data){
                direction = up;
                line_type.up_count++;
                if (last_data == 0){
                    line_type.zero_count++;
                }
            }
        }
        
        last_data = new_data;
        printf("  %d", new_data);  ///< output every data
    }
    sum_count = line_type.zero_count + \
                line_type.up_count + \
                line_type.down_count;
    if (sum_count > 60){
        *light_signal = blink_rapidly;
    }
    else if (sum_count > 15){
        *light_signal = blink_6times_then_off;
    }
    else if (sum_count > 7){
        *light_signal = breathing;
    }
    else if (sum_count > 5){
        *light_signal = blink_3times_then_off;
    }
    else if (sum_count > 0){
        if (new_data == 0){
            *light_signal = light_on_then_off;
        }
        else {
            *light_signal = light_off_then_on;
        }
    }
    else {
        *light_signal = light_off;
    }

    /// output line type
    printf("\n>>>>up count: %d \n>>>>down count: %d \n>>>>zero count: %d \n", 
            line_type.up_count, line_type.down_count, line_type.zero_count);
    /// output light signal type
    PrintLightSignal(*light_signal);

    return 0;

}


static uint8_t PrintLightSignal(light_signal_t light_signal){
    printf("**** led1: ");
    switch (light_signal){
        case light_off:
        printf("off\n");
        break;
        case light_off_then_on:
        printf("off on\n");
        break;
        case light_on_then_off:
        printf("on off\n");
        break;
        case blink_3times_then_off:
        printf("blink 3times\n");
        break;
        case blink_6times_then_off:
        printf("blnk 6times\n");
        break;
        case breathing:
        printf("breathing\n");
        break;
        case blink_rapidly:
        printf("blink rapidly\n");
        break;
        default: 
        printf("unknow\n");
        break;
    }

    return 0;
}
