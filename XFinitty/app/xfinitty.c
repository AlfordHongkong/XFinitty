


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
            TurnOffLed(BORAD_1_LED_B);
        break;
        case green:
            TurnOnLed(BORAD_1_LED_B);
            TurnOffLed(BOARD_1_LED_R);
        break;

        default:
        break;
    }
    led_board_1.state = on;
}

void TurnOffBoard1Led(void){
    
    TurnOffLed(BOARD_1_LED_R);
    TurnOffLed(BORAD_1_LED_B);

    led_board_1.state = off;
}

void FlashToOff(led_t *led){
    if (led == &led_board_1){
        TurnOffLed(BOARD_1_LED_R);
        TurnOffLed(BORAD_1_LED_B);
    }
}

void FlashToOn(led_t *led){
    if (led == &led_board_1){
        switch (led_board_1.color){
            case orange:
                TurnOnLed(BOARD_1_LED_R);
                TurnOnLed(BORAD_1_LED_B);
            break;
            case red:
                TurnOnLed(BOARD_1_LED_R);
                TurnOffLed(BORAD_1_LED_B);
            break;
            case green:
                TurnOnLed(BORAD_1_LED_B);
                TurnOffLed(BOARD_1_LED_R);
            break;

            default:
            break;
        }
    }
}

void StartFlashing(led_t *led){
    osTimerStart(LedFlashingHandle, 100);
}

void StopFlashing(led_t *led){
    osTimerStop(LedFlashingHandle);
}

void CallbackForLedFlashing(void){
    static uint8_t i = 0;
    if((i++ & 0x01) == 0){
        FlashToOn(&led_board_1);
    }
    else {
        FlashToOff(&led_board_1);
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
                led->state = off;
            }
            else if (state == flash){
                StartFlashing(&led_board_1);
                led->state = flash;
            }
            else{
                return 1;
            }
        }
        else if (led->state == off){
            if (state == on){
                TurnOnBoard1Led();
                led->state = on;
            }
            else if (state == flash){
                StartFlashing(&led_board_1);
                led->state = flash;
            }
            else {
                return 1;
            }
        }
        else if (led->state == flash){
            if (state == on){
                StopFlashing(&led_board_1);
                TurnOnBoard1Led();
                led->state = on;
            }
            else if (state == off){
                StopFlashing(&led_board_1);
                TurnOffBoard1Led();
                led->state = off;
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
    
    SetLedState(&led_board_1, on);
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
    SetLedState(&led_board_1, flash);
    osDelay(5000);
    SetLedColor(&led_board_1, red);
    osDelay(5000);
    SetLedColor(&led_board_1, green);
    osDelay(5000);

}

uint8_t PressS1(void){
    ActRelay(1);
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

void ResumeRelays(void){

}

uint8_t StepSevenChargingHighTemp(void){
    /// powr an dresistance check.    3.06v and 10k



    /// switch the resistance to 3.8k for > 2s 

    /// led1 flashing rapidy( 6 times per second)



	return 0;
}

uint8_t SetpEightEnd(void){
    /// reset and show the result
	ChangeResistance(resistance_10k);
	ChangePower(power_4v1);
	ChangeMeter(ma_meter);

	return 0;
}

void Reset(void){
    ChangeResistance(resistance_10k);
    ChangePower(power_4v1);
    ChangeMeter(ma_meter);
    osDelay(100);
}


void TestSequence(void){
    
    /// step 1: led1 and led2 should be off
        /// wait for pcba powering off

    PressS1();
        /// start fetch light data
    osDelay(4000);
        /// stop fetch light data and analyze this 3 scconds data, should be 000...000
        /// led2 should be off
    /// step 2: s3 == on --> led1 on; led2 on
    PressS1();
        /// start fetch light data
    osDelay(3000);
        /// stop fetch light data and analyze this 3 scconds data, should be 00..000 24,24 24 24 ...24
        /// led2 should be on
    PressS1();
        /// star fetch light data 
    osDelay(3000);
        /// stop fetch light data and analyze this 3 scconds data, should be 24 24 24 ...24 24 000...000
        /// led2 should be off

    /// step 3: HIGH TEMP TEST  res == 2.7k --> led 2 from on to off; led 1 flash 6times and off
    ChangeResistance(resistance_2k7);
    osDelay(100); ///< RELAY DELAY
    PressS1();
        /// start fetch light data and led2 data
    osDelay(4000);
        /// stop fetch data and start to analyze. led2 light on and then light off, led3 flash 6times and then off
    Reset();
    osDelay(1000); /// simulate human manipulation.

    /// step 4: stanby current test
    ChangeMeter(ua_meter);
    osDelay(100); /// for relay delay
        /// start to fetch data
    osDelay(5000);
        /// stop fetching and start analyzing
    Reset();
    osDelay(1000); /// simulate human manipulation.

    /// step 5: bow battery --> led1 flash 3 tiems then off.
    ChangePower(power_3v3);
    osDelay(100); /// for relay delay
    PressS1();
        /// start fecth light data
    osDelay(4000);
        /// stop fetch and start analyze. led1 fhash 3 times and then off.
    Reset();
    osDelay(1000); /// simulate human manipulation.

    /// step 6: charging --> led1 breathing state
    ChangePower(power_3v06);
    osDelay(100);   /// for relay delay
        /// start fetch data
    osDelay(4000);
        /// stop fetch and analyze breathing signal
    Reset();
    osDelay(1000); /// simulate human manipulation.

    /// step 7: high temp with charging --> led flahes rapidly 6times/s
    ChangePower(power_3v06);
    osDelay(100); /// for relay delay
    osDelay(1000); /// simulate human manipulation
    ChangeResistance(resistance_3k85);
    osDelay(100); /// for relay delay
        /// start fetch data
    osDelay(4000);  
        /// stop fetch and start analyze
    Reset();
    osDelay(1000); /// simulate human manipulation.

    /// step 8: done
        /// wait for pcba power off

}
