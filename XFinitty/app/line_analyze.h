/**
 * @file line_analyze.h
 * @author RocK Deng (dengyongpeng110@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-24
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef __LINE_ANALYZE_H__
#define __LINE_ANALYZE_H__


#include "circular_buffer.h"


/**
 * @brief on-board led1 signal types
 * 
 */
typedef enum{
    light_off,
    light_off_then_on,
    light_on_then_off,
    blink_3times_then_off,
    blink_6times_then_off,
    breathing,
    blink_rapidly,
    light_unknow,
}light_signal_t;

/**
 * @brief for recording type of line
 *         treat light data as a line
 * 
 */
typedef struct{
    uint8_t up_count;   ///< 线条上升的段数
    uint8_t down_count; ///< 线条下降的段数
    uint8_t zero_count; ///< 线条下降拐点为0的次数
}line_type_t;

/**
 * @brief analyze line(light data)
 * 
 * @param buff - light data to be analyze
 * @param light_signal - the result of this function
 * @return uint8_t - 0 means return success
 */
uint8_t AnalyzeLightData(circularBuffer_t *buff, light_signal_t *light_signal);

#endif

