


#include "xfinitty.h"
#include "cmsis_os.h"
#include "bsp.h"
#include "main.h"


extern osTimerId LedFlashingHandle;
extern osTimerId S1DelayHandle;


led_t led_board_1;
void TurnOnBoard1Led(void);


void InitLeds(void){
    led_board_1.color = orange;
    led_board_1.state = on;
    TurnOnBoard1Led();
}

void TurnOnBoard1Led(void){
    switch (led_board_1.color){
        case orange:
            TurnOnLed(BOARD_1_LED_R);
            TurnOnLed(BORAD_1_LED_B);
        break;
        case red:
            TurnOnLed(BOARD_1_LED_R);
        break;
        case green:
            TurnOnLed(BORAD_1_LED_B);
        break;

        default:
        break;
    }

}

void TurnOffBoard1Led(void){
    
    TurnOffLed(BOARD_1_LED_R);
    TurnOffLed(BORAD_1_LED_B);
}

void StartFlashing(led_t *led){
    osTimerStart(LedFlashingHandle, 100);
}

void StopFlashing(led_t *led){
    osTimerStop(LedFlashingHandle);
}

void CallbackForLedFlashing(void){
    uint8_t i = 0;
    if((i++ & 0x01) == 0){
        TurnOnBoard1Led();
    }
    else {
        TurnOffBoard1Led();
    }
}

uint8_t SetLedColor(led_t *led, led_color_t color){
    if (led->state == off)
        return 0;

    led->color = color;
    if (led->state == on)
        TurnOnBoard1Led();
    return 0;
}

uint8_t SetLedState(led_t *led, led_state_t state){
    if (state != led->state){
        if (led->state == on){
            if (state == off){
                TurnOffBoard1Led();
            }
            else if (state == flash){
                StartFlashing(&led_board_1);
            }
            else{
                return 1;
            }
        }
        else if (led->state == off){
            if (state == on){
                TurnOnBoard1Led();
            }
            else if (state == flash){
                StartFlashing(&led_board_1);
            }
            else {
                return 1;
            }
        }
        else if (led->state == flash){
            if (state == on){
                StopFlashing(&led_board_1);
                TurnOnBoard1Led();
            }
            else if (state == off){
                StopFlashing(&led_board_1);
                TurnOffBoard1Led();
            }
            else {
                return 1;
            }
        }
        else {
            return 1;
        }
    }

    return 0;
}


led_t *GetBoard1Led(void){
    return &led_board_1;
}

void TestLeds(void){
    
    SetLedState(&led_board_1, flash);
    SetLedColor(&led_board_1, red);
    osDelay(1000);
    SetLedColor(&led_board_1, green);
    osDelay(1000);
    SetLedColor(&led_board_1, orange);
    osDelay(1000);
    SetLedState(&led_board_1, off);
    osDelay(1000);
    SetLedState(&led_board_1, on);
    osDelay(1000);
    SetLedColor(&led_board_1, green);
    osDelay(1000);
    SetLedColor(&led_board_1, red);
}

uint8_t PressS1(void){
    ActRelay(2);
    if (osTimerStart(S1DelayHandle, 1200) == osOK)
        return 0;

    return 1;
    /// if s1 is not pressed, then pressd
}












uint8_t StepOnePowerOff(void){
    /// wait for powering off the pcba and set a timeout, and use led indicate the board is not power off

        /// led 1 and led 2 should be off

    /// if timeout return error

	return 0;
}

uint8_t StepTwoPowerOn(void){
    /// power and resistan check


    /// wait for powering on the pcab and set a timeout, and use led indicate the board is not power on

        /// press S1

        /// then, led1 should be tunrd on

        /// and current should < 0.575A

    /// if timeout return error


	return 0;
}

uint8_t StepThreeHignTemp(void){
    /// power and resistan check


    /// switch the resistance to 2.7K

    /// press S1 > 1S

    /// then, led1 flash 6 tiems and then turned off


    /// switch the resistance to 10k
    return 0;
}

uint8_t StepFourStandbyCurrent(void){
    /// power and resistan check




    /// hold for > 2s

    /// get standby current, is should be < 4uA


	return 0;
}

uint8_t StepFiveLowBattery(void){
    /// power and resistan check




    /// switch power to 3.3v

    /// press S1

    /// led1 should flash 3 times and then off


    /// switch powr to 4.1v

	return 0;
}

uint8_t StepSixCharging(void){
    /// power and resistan check




    /// switch power to 3.06(charging) and wait for > 2s


    /// led1 flashes in the breathing state and the current should be 88-279mA.



	return 0;
}

uint8_t StepSevenChargingHighTemp(void){
    /// powr an dresistance check.    3.06v and 10k



    /// switch the resistance to 3.8k for > 2s 

    /// led1 flashing rapidy( 6 times per second)



	return 0;
}

uint8_t SetpEightEnd(void){
    /// reset and show the result



	return 0;
}



void TestSequence(void){
    ChangeResistance(resistance_10k);
    ChangePower(power_4v1);

    /// step 1: s3 == off
    PressS1();
    osDelay(3000);

    /// step 2: s3 == on --> led1 on; led2 on
    PressS1();
    osDelay(3000);

    /// step 3: res == 2.7k --> led 2 from on to off; led 1 flash 6times and off
    ChangeResistance(resistance_2k7);
    PressS1();
    osDelay(5000);
    ChangeResistance(resistance_10k);

    /// step 4: stanby current test
    ChangeMeter(ua_meter);
    osDelay(3000);

    /// step 5: bow battery --> led1 flash 3 tiems then off.
    ChangePower(power_3v3);
    PressS1();
    osDelay(3000);

    /// step 6: charging --> led1 breathing state
    ChangeMeter(power_3v06);
    osDelay(5000);

    /// step 7: high temp with charging --> led flahes rapidly 6times/s
    ChangeResistance(resistance_3k85);

    /// step 8: done

}