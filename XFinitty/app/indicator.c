/**
 * @file indicator.c
 * @author Rock Deng(dengyongpeng110@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-21
 * 
 * @copyright Copyright (c) 2018
 * 
 */



#include "indicator.h"
#include "bsp.h"
#include "cmsis_os.h"


extern osTimerId LedFlashingHandle;



led_t led_board_1;
//let_t led_board_2;
void TurnOnBoard1Led(void);


void InitLeds(void){
    led_board_1.led_color = led_orange;
    led_board_1.led_state = led_on;
    TurnOnLed(BOARD_1_LED_R);
    TurnOnLed(BORAD_1_LED_B);

    
//    led_board_2.led_color = led_orange;
//    led_board_2.led_state = led_on;
    
}



void FlashToOff(which_led_t led){
    if (led == led_1){
        TurnOffLed(BOARD_1_LED_R);
        TurnOffLed(BORAD_1_LED_B);
    }
}

void FlashToOn(which_led_t led){
    if (led == led_1){
        switch (led_board_1.led_color){
            case led_orange:
                TurnOnLed(BOARD_1_LED_R);
                TurnOnLed(BORAD_1_LED_B);
            break;
            case led_red:
                TurnOnLed(BOARD_1_LED_R);
                TurnOffLed(BORAD_1_LED_B);
            break;
            case led_green:
                TurnOnLed(BORAD_1_LED_B);
                TurnOffLed(BOARD_1_LED_R);
            break;

            default:
            break;
        }
    }
}

void StartFlashingLed1(void){
    osTimerStart(LedFlashingHandle, 100);
}

void StopFlashingLed1(void){
    osTimerStop(LedFlashingHandle);
}

void CallbackForLed1Flashing(void){
    static uint8_t i = 0;
    if((i++ & 0x01) == 0){
        FlashToOn(led_1);
    }
    else {
        FlashToOff(led_1);
    }
}

led_error_t SetLedColor(which_led_t led, led_color_t color){
    // if (led->state == off)
    //     return 0;

    // led->color = color;
    // if (led->state == on)
    //     TurnOnBoard1Led();
    // return 0;

    if (led == led_1){
        if (led_board_1.led_state == led_flash){
            led_board_1.led_color = color;
        }
        else if (led_board_1.led_state == led_on){
            if (color == led_orange){
                TurnOnLed(BOARD_1_LED_R);
                TurnOnLed(BORAD_1_LED_B);
            }
            else if (color == led_red){
                TurnOnLed(BOARD_1_LED_R);
                TurnOffLed(BORAD_1_LED_B);
            }
            else if (color == led_green){
                TurnOffLed(BOARD_1_LED_R);
                TurnOnLed(BORAD_1_LED_B);
            }
            else {
                return error_led_color;
            }

            led_board_1.led_color = color;


        }
        else if (led_board_1.led_state == led_off){
            return error_cant_set_color;
        }
        else {
            return error_led_state;
        }
    }

    else if (led == led_2){
        
    }
    else {
        return error_which_led;
    }


    return no_led_error;
}

led_error_t SetLedState(which_led_t led, led_state_t state){
    if (led == led_1){
        /// first stop flash
        StopFlashingLed1();
        /// then, switch to next state
        switch (state){
            case led_on:
            SetLedColor(led_1, led_board_1.led_color);
            break;
            case led_off:
            TurnOffLed(BOARD_1_LED_R);
            TurnOffLed(BORAD_1_LED_B);
            break;
            case led_flash:
            StartFlashingLed1();
            break;
            default:
            break;
        }
        led_board_1.led_state = state;
    }
    else if (led == led_2){

    }

    return no_led_error;
}


void TestLeds(void){
    
    // SetLedState(led_1, led_on);
    // SetLedColor(led_1, led_red);
    // osDelay(1000);
    // SetLedColor(led_1, led_green);
    // osDelay(1000);
    // SetLedColor(led_1, led_orange);
    // osDelay(1000);
    // SetLedState(led_1, led_off);
    // osDelay(1000);
    // SetLedState(led_1, led_on);
    // osDelay(1000);
    // SetLedState(led_1, led_flash);
    // osDelay(5000);
    // SetLedColor(led_1, led_red);
    // osDelay(5000);
    // SetLedColor(led_1, led_green);
    // osDelay(5000);

    SetLedState(led_1, led_on);
    osDelay(3000);
    SetLedState(led_1, led_flash);
    osDelay(3000);

}
