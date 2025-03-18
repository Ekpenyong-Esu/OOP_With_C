//
// Created by mahon on 1/13/2024.
//

#include "Led.h"
#include <stdlib.h>

void LED_Init(LED* const me){
    me->LEDStatus = LED_OFF;
}
void LED_Cleanup(LED* const me){
    me->LEDStatus = LED_OFF;
}

LED* LED_Create(void){
    LED* me = (LED*)malloc(sizeof(LED));
    if (me != NULL)
    {
        LED_Init(me);
    }
    return me;
}

void LED_Destroy(LED* const me){
    if (me != NULL)
    {
        LED_Cleanup(me);
    }
    free(me);
}

void LED_LightOn(LED* const me){
    me->LEDStatus = LED_ON;
}

void LED_LightOff(LED* const me){
    me->LEDStatus = LED_OFF;
}
