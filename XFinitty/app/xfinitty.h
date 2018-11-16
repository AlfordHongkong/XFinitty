


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


typedef enum{
    orange,
    red,
    green,
}led_color_t;

typedef enum{
    off,
    on,
    flash,
}led_state_t;

typedef struct{
    led_color_t color;
    led_state_t state;
}led_t;

void InitLeds(void);
void CallbackForLedFlashing(void);

uint8_t SetLedColor(led_t *led, led_color_t color);

uint8_t SetLedState(led_t *led, led_state_t state);

led_t *GetBoard1Led(void);

void TestLeds(void);

uint8_t PressS1(void);
#define S1DelayCallback4User() ReleaseRelay(2)

void TestSequence(void);

#endif


