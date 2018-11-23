


#include "xfinitty.h"
#include "cmsis_os.h"
#include "bsp.h"
#include "adc_led.h"
#include "indicator.h"
#include "main.h"
#include "tsl2561.h"
#include "line_analyze.h"


extern osTimerId S1DelayHandle;

uint8_t flag_enable_fetching_light;

void InitXFinitty(void){
    flag_enable_fetching_light = 0;

}

uint8_t PressS1(void){
    ActRelay(1);
    osDelay(100); ///< for relay delay
    if (osTimerStart(S1DelayHandle, 1200) == osOK)
        return 0;

    return 1;
    /// if s1 is not pressed, then pressd
}

uint8_t isEnableFetchingLight(void){
    return flag_enable_fetching_light;
}
 
uint8_t EnableFetchingLight(void){

    flag_enable_fetching_light = 1;
    
    ClearAllLightData(); /// clean all historical data

    return 0;
}

uint8_t DisableFetchingLight(void){
    flag_enable_fetching_light = 0;

    return 0;
}



uint8_t StepOnePowerDown(void){
    uint8_t value_led_plus = 0;
    uint8_t value_led_minus = 0;
    uint8_t value_light = 0;
    uint8_t read_adc_state = 0;
    light_signal_t light_signal;
    printf("Step 1: \n");
    /// wait for powering off the pcba and set a timeout, and use led indicate the board is not power off
    EnableLedPlusTest();
    EnableAdcFetching();
    printf(">>enable fetching adc value.\n");
    SetLedColor(led_1, led_orange);
    SetLedState(led_1, led_flash);
    printf(">>wait power-off...\n");
    printf(">>>>value_led_plus: ");
    read_adc_state = ReadAdcData(1, &value_led_plus);
    while ( (read_adc_state != 0) || value_led_plus >= LED_PLUS_shreshold){
        if (read_adc_state == 0){ ///< read success
        // printf("  %d", value_led_plus);
        } 
            
        read_adc_state = ReadAdcData(1, &value_led_plus);
    }
    printf("\n>>>>qualified value_led_plus: %d\n", value_led_plus);
    SetLedState(led_1, led_on);
    printf(">>power off.\n");
    DisableAdcFetching();
    DisableLedPlusTest();
    printf(">>disable fetching adc value.\n");


    /// led 1 and led 2 should be off
    PressS1();
    printf(">>Press S1\n");
    EnableLedMinusTest();
    EnableAdcFetching();
    EnableFetchingLight();
    osDelay(5000);   ///< delay 5s for light data fetching
    DisableLedMinusTest();
    DisableAdcFetching();
    DisableFetchingLight();
    printf(">>>>led_minus: ");
    while(ReadCircularBuf(GetLedMinusCB(), &value_led_minus) == 0){
        printf("  %d", value_led_minus);
    }
    

    AnalyzeLightData(GetLightCB(), &light_signal);
    
    printf("\n\n\n");
	return 0;
}

uint8_t StepTwoPowerUp(void){
    uint8_t value_led_plus = 0;
    uint8_t value_led_minus = 0;
    uint8_t value_light = 0;
    uint8_t read_adc_state = 0;
    light_signal_t light_signal;
    printf("Step 2: led1 on-->off; led2 on-->off; current<0.575A\n");
    /// wait for powering off the pcba and set a timeout, and use led indicate the board is not power off
    EnableLedPlusTest();
    EnableAdcFetching();
    printf(">>enable fetching adc value.\n");
    SetLedColor(led_1, led_orange);
    SetLedState(led_1, led_flash);
    printf(">>wait power-on...\n");
    printf(">>>>value_led_plus: ");
    read_adc_state = ReadAdcData(1, &value_led_plus);
    while ( (read_adc_state != 0) || value_led_plus < LED_PLUS_shreshold){
        if (read_adc_state == 0) { ///< read success
            // printf("  %d", value_led_plus);
        }   
        read_adc_state = ReadAdcData(1, &value_led_plus);
    }
    printf("\n>>>>qualified value_led_plus: %d\n", value_led_plus);
    SetLedState(led_1, led_on);
    printf(">>power on.\n");
    DisableAdcFetching();
    DisableLedPlusTest();
    printf(">>disable fetching adc value.\n");

    /// power and resistan check



        /// press S1. led1 should be tunrd on
        /// and current should < 0.575A    
    PressS1();
    printf(">>Press S1\n");
    EnableLedMinusTest();
    EnableAdcFetching();
    EnableFetchingLight();
    osDelay(5000);   ///< delay 5s for data fetching
    DisableLedMinusTest();
    DisableAdcFetching();
    DisableFetchingLight();
    printf(">>>>led_minus: ");
    while(ReadCircularBuf(GetLedMinusCB(), &value_led_minus) == 0){
        printf("  %d", value_led_minus);
    }
    
    AnalyzeLightData(GetLightCB(), &light_signal);
    
        /// then, press s1 again. led1 and led2 should be off
    PressS1();
    printf("\n>>Press S1 again\n");
    EnableLedMinusTest();
    EnableAdcFetching();
    EnableFetchingLight();
    osDelay(5000);   ///< delay 5s for data fetching
    DisableLedMinusTest();
    DisableAdcFetching();
    DisableFetchingLight();
    printf(">>>>led_minus: ");
    while(ReadCircularBuf(GetLedMinusCB(), &value_led_minus) == 0){
        printf("  %d", value_led_minus);
    }

    AnalyzeLightData(GetLightCB(), &light_signal);

    printf("\n\n\n");

	return 0;
}

uint8_t StepThreeHignTemp(void){
//    uint8_t value_led_plus = 0;
    uint8_t value_led_minus = 0;
    uint8_t value_light = 0;
//    uint8_t read_adc_state = 0;
    light_signal_t light_signal;
    /// power and resistan check

    printf(">>Step 3: led1 flash 6tiems; led2 on-->off\n");
    /// switch the resistance to 2.7K
    ChangeResistance(resistance_2k7);
    osDelay(100); ///< relay delay
    printf(">>Change resistance to 2.7k.\n");
    /// press S1 > 1S
    PressS1();
    printf(">>Press s1\n");
    EnableLedMinusTest();
    EnableAdcFetching();
    EnableFetchingLight();
    /// then, led1 flash 6 tiems and then turned off
    osDelay(5000); ///< delay for data fetching
    DisableLedMinusTest();
    DisableAdcFetching();
    DisableFetchingLight();
    printf(">>>>led_minus: ");
    while(ReadCircularBuf(GetLedMinusCB(), &value_led_minus) == 0){
        printf("  %d", value_led_minus);
    }
    
    AnalyzeLightData(GetLightCB(), &light_signal);

    printf("\n\n\n");
    /// switch the resistance to 10k
    Reset();
    return 0;
}

uint8_t StepFourStandbyCurrent(void){
    /// power and resistan check

    printf(">>Step 4: standby current < 4uA\n");


    /// hold for > 2s
    ChangeMeter(ua_meter);
    osDelay(3000); ///< delay for system stable
    /// get standby current, is should be < 4uA

    

    printf("\n\n\n");
    Reset();

	return 0;
}

uint8_t StepFiveLowBattery(void){
//	uint8_t value_led_plus = 0;
//	uint8_t value_led_minus = 0;
	uint8_t value_light = 0;
//	uint8_t read_adc_state = 0;
    light_signal_t light_signal;
    /// power and resistan check


    printf(">>Step 5: low battery  led1 bink 3timrs-->off\n");

    /// switch power to 3.3v
    ChangePower(power_3v3);
    osDelay(100); ///< delay for relay 
    printf(">>Chagne power to 3.3v.\n");
    /// press S1
    PressS1();
    printf(">>Press s1\n");
    /// led1 should flash 3 times and then off
    EnableFetchingLight();
    /// then, led1 flash 6 tiems and then turned off
    osDelay(5000); ///< delay for data fetching
    DisableFetchingLight();
    
    AnalyzeLightData(GetLightCB(), &light_signal);

    /// switch powr to 4.1v
    Reset();
    printf("\n\n\n");

	return 0;
}

uint8_t StepSixCharging(void){
//	uint8_t value_led_plus = 0;
//	uint8_t value_led_minus = 0;
	uint8_t value_light = 0;
//	uint8_t read_adc_state = 0;
    light_signal_t light_signal;

    /// power and resistan check

    printf(">>Step 6: charging :  led1 breathing; current 88~279mA\n");


    /// switch power to 3.06(charging) and wait for > 2s
    ChangePower(power_3v06);
    printf(">>Change powr to 3.06v\n");
    osDelay(3000); ///< delay for system statle
    /// led1 flashes in the breathing state and the current should be 88-279mA.
    EnableFetchingLight();
    osDelay(5000); ///< delay for data fetching
    DisableFetchingLight();
    
    AnalyzeLightData(GetLightCB(), &light_signal);

    Reset();
    printf("\n\n\n");


	return 0;
}


uint8_t StepSevenChargingHighTemp(void){
//	uint8_t value_led_plus = 0;
//	uint8_t value_led_minus = 0;
	uint8_t value_light = 0;
//	uint8_t read_adc_state = 0;
    light_signal_t light_signal;

    /// powr an dresistance check.    3.06v and 10k

    printf(">>Step 7: charging while high temp:  led1 blink rapidly.\n");

    /// switch the resistance to 3.8k for > 2s 
    ChangePower(power_3v06);
    ChangeResistance(resistance_3k85);
    printf(">>Change powr to 3.06v and resistance to 3.85k\n");
    osDelay(3000); ///< delay for system statle

    /// led1 flashing rapidy( 6 times per second)

    EnableFetchingLight();
    osDelay(5000); ///< delay for data fetching
    DisableFetchingLight();
    
    AnalyzeLightData(GetLightCB(), &light_signal);
    
    Reset();
    printf("\n\n\n");

	return 0;
}

uint8_t StepEightEnd(void){
    /// reset and show the result
	
    printf(">>Step 8: end\n\n\n\n\n");

	return 0;
}

void Reset(void){
    ChangeResistance(resistance_10k);
    ChangePower(power_4v1);
    ChangeMeter(ma_meter);
    osDelay(100);
}





void TestSequence(void){
    
    // /// step 1: led1 and led2 should be off
    //     /// wait for pcba powering off

    // PressS1();
    //     /// start fetch light data
    // osDelay(4000);
    //     /// stop fetch light data and analyze this 3 scconds data, should be 000...000
    //     /// led2 should be off
    StepOnePowerDown();


    // /// step 2: s3 == on --> led1 on; led2 on
    // PressS1();
    //     /// start fetch light data
    // osDelay(3000);
    //     /// stop fetch light data and analyze this 3 scconds data, should be 00..000 24,24 24 24 ...24
    //     /// led2 should be on
    // PressS1();
    //     /// star fetch light data 
    // osDelay(3000);
    //     /// stop fetch light data and analyze this 3 scconds data, should be 24 24 24 ...24 24 000...000
    //     /// led2 should be off
    StepTwoPowerUp();


    // /// step 3: HIGH TEMP TEST  res == 2.7k --> led 2 from on to off; led 1 flash 6times and off
    // ChangeResistance(resistance_2k7);
    // osDelay(100); ///< RELAY DELAY
    // PressS1();
    //     /// start fetch light data and led2 data
    // osDelay(4000);
    //     /// stop fetch data and start to analyze. led2 light on and then light off, led3 flash 6times and then off
    // Reset();
    // osDelay(1000); /// simulate human manipulation.
    StepThreeHignTemp();


    // /// step 4: stanby current test
    // ChangeMeter(ua_meter);
    // osDelay(100); /// for relay delay
    //     /// start to fetch data
    // osDelay(5000);
    //     /// stop fetching and start analyzing
    // Reset();
    // osDelay(1000); /// simulate human manipulation.
    StepFourStandbyCurrent();


    // /// step 5: bow battery --> led1 flash 3 tiems then off.
    // ChangePower(power_3v3);
    // osDelay(100); /// for relay delay
    // PressS1();
    //     /// start fecth light data
    // osDelay(4000);
    //     /// stop fetch and start analyze. led1 fhash 3 times and then off.
    // Reset();
    // osDelay(1000); /// simulate human manipulation.
    StepFiveLowBattery();


    // /// step 6: charging --> led1 breathing state
    // ChangePower(power_3v06);
    // osDelay(100);   /// for relay delay
    //     /// start fetch data
    // osDelay(4000);
    //     /// stop fetch and analyze breathing signal
    // Reset();
    // osDelay(1000); /// simulate human manipulation.
    StepSixCharging();


    // /// step 7: high temp with charging --> led flahes rapidly 6times/s
    // ChangePower(power_3v06);
    // osDelay(100); /// for relay delay
    // osDelay(1000); /// simulate human manipulation
    // ChangeResistance(resistance_3k85);
    // osDelay(100); /// for relay delay
    //     /// start fetch data
    // osDelay(4000);  
    //     /// stop fetch and start analyze
    // Reset();
    // osDelay(1000); /// simulate human manipulation.
    StepSevenChargingHighTemp();


    // /// step 8: done
    //     /// wait for pcba power off
    StepEightEnd();
}
