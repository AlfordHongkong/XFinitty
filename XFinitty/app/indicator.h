



#ifndef __INDICATOR_H__
#define __INDICATOR_H__



typedef enum{
    led_orange,
    led_red,
    led_green,
}led_color_t;

typedef enum{
    led_off,
    led_on,
    led_flash,
}led_state_t;

typedef struct{
    led_color_t led_color;
    led_state_t led_state;
}led_t;

typedef enum {
    led_1,
    led_2,
}which_led_t;

typedef enum{
    no_led_error,
    error_which_led,
    error_cant_set_color,
    error_led_color,
    error_led_state,
}led_error_t;

void InitLeds(void);
void CallbackForLed1Flashing(void);

led_error_t SetLedColor(which_led_t led, led_color_t color);

led_error_t SetLedState(which_led_t led, led_state_t state);

// led_t *GetBoard1Led(void);

void TestLeds(void);

#endif

