//
// Created by mahon on 1/8/2024.
//

#include "Timer.h"
#include <stdlib.h>

void Timer_Init(Timer* const me){
    // me->
}
void Timer_Cleanup(Timer* const me){

}

Timer* Timer_Create(void){
    Timer* me = (Timer*)malloc(sizeof(Timer));
    if (me != NULL)
    {
        Timer_Init(me);
    }
    return me;
}

void Timer_Destroy(Timer* const me){
    if (me != NULL)
    {
        Timer_Cleanup(me);
    }
    free(me);
}

void Timer_delay(Timer* const me, int time){
}
