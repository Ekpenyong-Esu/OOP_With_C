//
// Timer Component - Demonstrates time-based AND pattern aspect
// This adds a timing dimension to demonstrate how time can be 
// another orthogonal aspect in the AND pattern
//

#ifndef ANDSTATE_TIMER_H
#define ANDSTATE_TIMER_H

#include <stdbool.h>
#include <time.h>

typedef enum TimerState {
    TIMER_STOPPED,
    TIMER_RUNNING,
    TIMER_PAUSED,
    TIMER_EXPIRED
} TimerState;

typedef enum TimerMode {
    ONESHOT,    // Timer runs once and stops
    REPEATING,  // Timer restarts automatically
    COUNTDOWN   // Timer counts down to zero
} TimerMode;

typedef struct Timer Timer;
struct Timer {
    // AND Pattern: Timer has multiple independent aspects
    TimerState state;       // Current timer state
    TimerMode mode;         // How the timer behaves
    
    // Timing data
    unsigned int duration_ms;    // Timer duration in milliseconds
    unsigned int elapsed_ms;     // Time elapsed
    clock_t start_time;          // When timer was started
    
    // Configuration
    bool auto_reset;        // Reset automatically when expired
    unsigned int repeat_count;   // How many times to repeat (0 = infinite)
    unsigned int current_repeats; // Current repeat count
};

// Constructor/Destructor
void Timer_Init(Timer* const me, unsigned int duration_ms, TimerMode mode);
void Timer_Cleanup(Timer* const me);
Timer* Timer_Create(unsigned int duration_ms, TimerMode mode);
void Timer_Destroy(Timer* const me);

// Basic timer operations
void Timer_start(Timer* const me);
void Timer_stop(Timer* const me);
void Timer_pause(Timer* const me);
void Timer_resume(Timer* const me);
void Timer_reset(Timer* const me);

// AND Pattern operations - independent aspects
void Timer_setMode(Timer* const me, TimerMode mode);
void Timer_setDuration(Timer* const me, unsigned int duration_ms);
void Timer_setAutoReset(Timer* const me, bool auto_reset);
void Timer_setRepeatCount(Timer* const me, unsigned int count);

// Status and utility functions
void Timer_update(Timer* const me);  // Call this regularly to update timer
bool Timer_isExpired(Timer* const me);
bool Timer_isRunning(Timer* const me);
unsigned int Timer_getRemainingTime(Timer* const me);
unsigned int Timer_getElapsedTime(Timer* const me);
float Timer_getProgress(Timer* const me);  // Returns 0.0 to 1.0

// Display and debugging
void Timer_displayStatus(Timer* const me);
const char* Timer_getStateString(Timer* const me);
const char* Timer_getModeString(Timer* const me);

#endif //ANDSTATE_TIMER_H
