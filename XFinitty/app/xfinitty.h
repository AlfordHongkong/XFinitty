


#ifndef __XFINITTY_H__
#define __XFINITTY_H__


#include "stdint.h"

typedef enum{
    test_wait,
    test_started,
    test_end,
}test_state_t;

typedef enum{
    one = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
}processing_step_t;

typedef enum{
    step_failure,
    step_succeed,
}step_result_t;

typedef struct{
    test_state_t test_state;
    processing_step_t processing_step;
    step_result_t step_one;
    step_result_t step_two;
    step_result_t step_three;
    step_result_t step_four;
    step_result_t step_five;
    step_result_t step_six;
    step_result_t step_seven;
    step_result_t step_eight;
}xfinitty_t;


/**
 * @brief press s1 button
 * 
 * @return uint8_t 
 */
uint8_t PressS1(void);

/**
 * @brief callback for releasing s1 button
 * 
 */
#define S1DelayCallback4User() ReleaseRelay(1)

/**
 * @brief test sequence
 * 
 */
void TestSequence(void);

/**
 * @brief check out if fetching enabled
 * 
 * @return uint8_t 
 */
uint8_t isEnableFetchingLight(void);


uint8_t EnableFetchingLight(void);

uint8_t DisableFetchingLight(void);


/**
 * @brief xfinitty initialization
 * 
 */
void InitXFinitty(void);

void Reset(void);

#endif


