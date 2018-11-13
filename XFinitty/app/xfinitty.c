




#include "xfinitty.h"



uint8_t PressS1(void){

    /// if s1 is not pressed, then pressd
}


uint8_t StepOnePowerOff(void){
    /// wait for powering off the pcba and set a timeout, and use led indicate the board is not power off

        /// led 1 and led 2 should be off

    /// if timeout return error
}

uint8_t StepTwoPowerOn(void){
    /// power and resistan check


    /// wait for powering on the pcab and set a timeout, and use led indicate the board is not power on

        /// press S1

        /// then, led1 should be tunrd on

        /// and current should < 0.575A

    /// if timeout return error

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

}

uint8_t StepFiveLowBattery(void){
    /// power and resistan check




    /// switch power to 3.3v

    /// press S1

    /// led1 should flash 3 times and then off


    /// switch powr to 4.1v
}

uint8_t StepSixCharging(void){
    /// power and resistan check




    /// switch power to 3.06(charging) and wait for > 2s


    /// led1 flashes in the breathing state and the current should be 88-279mA.
}

uint8_t StepSevenChargingHighTemp(void){
    /// powr an dresistance check.    3.06v and 10k



    /// switch the resistance to 3.8k for > 2s 

    /// led1 flashing rapidy( 6 times per second)
}

uint8_t SetpEightEnd(void){
    /// reset and show the result


}
