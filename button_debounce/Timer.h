//
// Created by mahon on 1/8/2024.
//

#ifndef BUTTON_DEBOUNCE_TIMER_H
#define BUTTON_DEBOUNCE_TIMER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Timer Timer;
struct Timer
{
    int time;
};

void Timer_Init(Timer* const me);
void Timer_Cleanup(Timer* const me);

Timer* Timer_Create();
void Timer_Destroy(Timer* const me);

void Timer_delay(Timer* const me, int time);


#endif //BUTTON_DEBOUNCE_TIMER_H
