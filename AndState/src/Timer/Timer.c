//
// Timer Component Implementation
// Demonstrates time-based AND pattern aspects
//

#include "Timer.h"
#include <stdlib.h>
#include <stdio.h>

// Helper functions
static const char* stateToString(TimerState state) {
    switch(state) {
        case TIMER_STOPPED: return "STOPPED";
        case TIMER_RUNNING: return "RUNNING";
        case TIMER_PAUSED: return "PAUSED";
        case TIMER_EXPIRED: return "EXPIRED";
        default: return "UNKNOWN";
    }
}

static const char* modeToString(TimerMode mode) {
    switch(mode) {
        case ONESHOT: return "ONESHOT";
        case REPEATING: return "REPEATING";
        case COUNTDOWN: return "COUNTDOWN";
        default: return "UNKNOWN";
    }
}

// Constructor/Destructor
void Timer_Init(Timer* const me, unsigned int duration_ms, TimerMode mode) {
    if (me == NULL) return;
    
    me->state = TIMER_STOPPED;
    me->mode = mode;
    me->duration_ms = duration_ms;
    me->elapsed_ms = 0;
    me->start_time = 0;
    me->auto_reset = false;
    me->repeat_count = 0;  // Infinite by default
    me->current_repeats = 0;
    
    printf("Timer initialized: %d ms, %s mode\n", duration_ms, modeToString(mode));
}

void Timer_Cleanup(Timer* const me) {
    if (me == NULL) return;
    
    me->state = TIMER_STOPPED;
    printf("Timer cleaned up\n");
}

Timer* Timer_Create(unsigned int duration_ms, TimerMode mode) {
    Timer* me = (Timer*)malloc(sizeof(Timer));
    if (me != NULL) {
        Timer_Init(me, duration_ms, mode);
    }
    return me;
}

void Timer_Destroy(Timer* const me) {
    if (me != NULL) {
        Timer_Cleanup(me);
        free(me);
    }
}

// Basic timer operations
void Timer_start(Timer* const me) {
    if (me == NULL) return;
    
    me->state = TIMER_RUNNING;
    me->start_time = clock();
    me->elapsed_ms = 0;
    
    printf("Timer started (%s mode)\n", modeToString(me->mode));
}

void Timer_stop(Timer* const me) {
    if (me == NULL) return;
    
    me->state = TIMER_STOPPED;
    me->elapsed_ms = 0;
    me->current_repeats = 0;
    
    printf("Timer stopped\n");
}

void Timer_pause(Timer* const me) {
    if (me == NULL || me->state != TIMER_RUNNING) return;
    
    Timer_update(me);  // Update elapsed time before pausing
    me->state = TIMER_PAUSED;
    
    printf("Timer paused at %d ms\n", me->elapsed_ms);
}

void Timer_resume(Timer* const me) {
    if (me == NULL || me->state != TIMER_PAUSED) return;
    
    me->state = TIMER_RUNNING;
    me->start_time = clock() - (me->elapsed_ms * CLOCKS_PER_SEC / 1000);
    
    printf("Timer resumed from %d ms\n", me->elapsed_ms);
}

void Timer_reset(Timer* const me) {
    if (me == NULL) return;
    
    me->elapsed_ms = 0;
    me->current_repeats = 0;
    if (me->state == TIMER_RUNNING) {
        me->start_time = clock();
    }
    
    printf("Timer reset\n");
}

// AND Pattern operations - these can be changed independently
void Timer_setMode(Timer* const me, TimerMode mode) {
    if (me == NULL) return;
    
    me->mode = mode;
    printf("Timer mode changed to: %s\n", modeToString(mode));
}

void Timer_setDuration(Timer* const me, unsigned int duration_ms) {
    if (me == NULL) return;
    
    me->duration_ms = duration_ms;
    printf("Timer duration changed to: %d ms\n", duration_ms);
}

void Timer_setAutoReset(Timer* const me, bool auto_reset) {
    if (me == NULL) return;
    
    me->auto_reset = auto_reset;
    printf("Timer auto-reset: %s\n", auto_reset ? "ON" : "OFF");
}

void Timer_setRepeatCount(Timer* const me, unsigned int count) {
    if (me == NULL) return;
    
    me->repeat_count = count;
    printf("Timer repeat count set to: %d (0 = infinite)\n", count);
}

// Core update function
void Timer_update(Timer* const me) {
    if (me == NULL || me->state != TIMER_RUNNING) return;
    
    clock_t current_time = clock();
    me->elapsed_ms = (unsigned int)((current_time - me->start_time) * 1000 / CLOCKS_PER_SEC);
    
    // Check if timer expired
    if (me->elapsed_ms >= me->duration_ms) {
        me->state = TIMER_EXPIRED;
        printf("Timer expired! ");
        
        // Handle different modes
        switch (me->mode) {
            case ONESHOT:
                printf("(One-shot complete)\n");
                break;
                
            case REPEATING:
                me->current_repeats++;
                if (me->repeat_count == 0 || me->current_repeats < me->repeat_count) {
                    printf("(Repeating - cycle %d)\n", me->current_repeats);
                    Timer_start(me);  // Restart automatically
                } else {
                    printf("(Repeat limit reached)\n");
                }
                break;
                
            case COUNTDOWN:
                printf("(Countdown finished)\n");
                if (me->auto_reset) {
                    Timer_start(me);
                }
                break;
        }
    }
}

// Status functions
bool Timer_isExpired(Timer* const me) {
    if (me == NULL) return false;
    Timer_update(me);
    return me->state == TIMER_EXPIRED;
}

bool Timer_isRunning(Timer* const me) {
    return (me != NULL) && (me->state == TIMER_RUNNING);
}

unsigned int Timer_getRemainingTime(Timer* const me) {
    if (me == NULL) return 0;
    Timer_update(me);
    
    if (me->elapsed_ms >= me->duration_ms) {
        return 0;
    }
    return me->duration_ms - me->elapsed_ms;
}

unsigned int Timer_getElapsedTime(Timer* const me) {
    if (me == NULL) return 0;
    Timer_update(me);
    return me->elapsed_ms;
}

float Timer_getProgress(Timer* const me) {
    if (me == NULL || me->duration_ms == 0) return 0.0f;
    Timer_update(me);
    
    float progress = (float)me->elapsed_ms / (float)me->duration_ms;
    return (progress > 1.0f) ? 1.0f : progress;
}

// Display functions
void Timer_displayStatus(Timer* const me) {
    if (me == NULL) {
        printf("Timer: NULL pointer\n");
        return;
    }
    
    Timer_update(me);
    
    printf("Timer Status: %s | Mode: %s | %d/%d ms (%.1f%%)",
           stateToString(me->state),
           modeToString(me->mode),
           me->elapsed_ms,
           me->duration_ms,
           Timer_getProgress(me) * 100.0f);
    
    if (me->mode == REPEATING && me->repeat_count > 0) {
        printf(" | Cycle: %d/%d", me->current_repeats, me->repeat_count);
    }
    
    printf("\n");
}

const char* Timer_getStateString(Timer* const me) {
    return (me != NULL) ? stateToString(me->state) : "NULL";
}

const char* Timer_getModeString(Timer* const me) {
    return (me != NULL) ? modeToString(me->mode) : "NULL";
}
