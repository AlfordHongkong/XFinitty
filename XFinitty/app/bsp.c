




#include "bsp.h"
#include <stdlib.h>


typedef enum{
    resistance_10k,
    resistance_2k7,
    resistance_3k85,

}which_resistance_t;

typedef enum{
    power_4v1,
    power_3v3,
    power_5v,
}which_power_t;


uint8_t ChangeResistance(which_resistance_t which_resistance) {

    switch (which_resistance) {
        case resistance_10k:
        break;
        case resistance_2k7:
        break;
        case resistance_3k85:
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

        break;
        case power_3v3:

        break;
        case power_5v:

        break;

        default:
        return 1;
        break;
    }


    return 0;
}