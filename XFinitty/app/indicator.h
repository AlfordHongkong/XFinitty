/**
 * @file indicator.h
 * @author Rock Deng(dengyongpeng110@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-21
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef __INDICATOR_H__
#define __INDICATOR_H__


/**
 * @brief led color
 * 
 */
typedef enum{
    led_orange,
    led_red,
    led_green,
}led_color_t;


/**
 * @brief led states
 * 
 */
typedef enum{
    led_off,
    led_on,
    led_flash,
}led_state_t;


/**
 * @brief led struct
 * 
 */
typedef struct{
    led_color_t led_color;
    led_state_t led_state;
}led_t;

/**
 * @brief for recgnising the leds on the board
 * 
 */
typedef enum {
    led_1,
    led_2,
}which_led_t;


/**
 * @brief error types
 * 
 */
typedef enum{
    no_led_error,
    error_which_led,
    error_cant_set_color,
    error_led_color,
    error_led_state,
}led_error_t;


/**
 * @brief init led module
 * 
 */
void InitLeds(void);

/**
 * @brief callback function for led1 flahing
 * 
 */
void CallbackForLed1Flashing(void);


/**
 * @brief Set the Led Color object
 * 
 * @param led 
 * @param color 
 * @return led_error_t 
 */
led_error_t SetLedColor(which_led_t led, led_color_t color);

/**
 * @brief Set the Led State object
 * 
 * @param led 
 * @param state 
 * @return led_error_t 
 */
led_error_t SetLedState(which_led_t led, led_state_t state);


/**
 * @brief for led module testing
 * 
 */
void TestLeds(void);

#endif

