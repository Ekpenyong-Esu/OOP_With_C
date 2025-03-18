//
// Created by mahon on 1/8/2024.
//

#include "Timer.h"
#include <stdio.h>
#include <stdlib.h>

void Timer_Init(Timer* const me) {
    if (me != NULL) {
        me->time = 0;
    }
}

void Timer_Cleanup(Timer* const me) {
    // Currently no resources to clean up
}

Timer* Timer_Create(void) {
    Timer* me = (Timer*)malloc(sizeof(Timer));
    if (me != NULL) {
        Timer_Init(me);
    }
    return me;
}

void Timer_Destroy(Timer* const me) {
    if (me != NULL) {
        Timer_Cleanup(me);
        free(me);
    }
}

void Timer_delay(Timer* const me, int time) {
    // In a real implementation, this would use platform-specific delay mechanisms
    // For demonstration purposes, we'll just store the time value
    if (me != NULL) {
        me->time = time;
        printf("Timer: Delaying for %d ms\n", time);
    }
}
