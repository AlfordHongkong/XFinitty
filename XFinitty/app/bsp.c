




#include "bsp.h"
//#include <stdlib.h>


#define RELAY_2K7 3
#define RELAY_3K85 4
#define RELAY_3V3 6
#define RELAY_3V06 5
#define RELAY_4V1 5
#define RELAY_5V 5
#define RELAY_TP7 5
#define RELAY_MA 5
#define RELAY_UA 6


uint8_t ChangeResistance(which_resistance_t which_resistance) {

    switch (which_resistance) {
        case resistance_10k:
            ReleaseRelay(3);
            ReleaseRelay(4);
         break;
         case resistance_2k7:
            ReleaseRelay(4);
            ActRelay(3);
         break;
         case resistance_3k85:
            ReleaseRelay(3);
            ActRelay(4);
         break;

         default:
         return 1;
         break;
     }

    return 0;
}



 uint8_t ChangePower(which_power_t which_powre){

     switch (which_powre){
         case power_4v1:
            //  _ReleaseRelay(RELAY_5V);
            //  _ReleaseRelay(RELAY_3V06);
            //  _ReleaseRelay(RELAY_TP7);
            //  _ReleaseRelay(RELAY_MA);
            //  _ReleaseRelay(RELAY_3V3);
            //  _ActRelay(RELAY_4V1);
            ReleaseRelay(5);
            // ReleaseRelay(6);
            ReleaseRelay(7);
         break;
         case power_3v3:
            //  _ReleaseRelay(RELAY_5V);
            //  _ReleaseRelay(RELAY_3V06);
            //  _ReleaseRelay(RELAY_TP7);
            //  _ReleaseRelay(RELAY_MA);
            //  _ActRelay(RELAY_3V3);
            //  _ReleaseRelay(RELAY_4V1);
            ReleaseRelay(5);
            // ReleaseRelay(6);
            ActRelay(7);
         break;
         case power_3v06:
            //  _ActRelay(RELAY_5V);
            //  _ActRelay(RELAY_3V06);
            //  _ActRelay(RELAY_TP7);
            //  _ActRelay(RELAY_MA);
            //  _ReleaseRelay(RELAY_3V3);
            //  _ReleaseRelay(RELAY_4V1);
            ActRelay(5);
            // ReleaseRelay(6);
            ReleaseRelay(7);

         break;

         default:
         return 1;
         break;
     }

     return 0;
 }

uint8_t ChangeMeter(which_meter_t meter){

    switch (meter){
        case ua_meter:
        ActRelay(6);

        break;
        case ma_meter:
        ReleaseRelay(6);
        break;

        default:
        return 1;
    }

    return 0;
}

 void TestRelay(void){

 }




