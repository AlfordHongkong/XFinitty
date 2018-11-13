


#ifndef __XFINITTY_H__
#define __XFINITTY_H__


#include "stdint.h"

typedef enum{
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
    processint_step_t processing_step;
    step_result_t step_one;
    step_result_t step_two;
    step_result_t step_three;
    step_result_t step_four;
    step_result_t step_five;
    step_result_t step_six;
    step_result_t step_seven;
    step_result_t step_eight;
}xfinitty_t;











#endif


