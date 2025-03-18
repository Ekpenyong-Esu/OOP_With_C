//
// Created by mahon on 1/8/2024.
// Timer component for managing time-based operations
//

#ifndef BUTTON_DEBOUNCE_TIMER_H
#define BUTTON_DEBOUNCE_TIMER_H

/**
 * @brief Timer structure for delay operations
 */
typedef struct Timer Timer;
struct Timer
{
    int time;  // Current time value in milliseconds
};

/**
 * @brief Initialize a Timer instance
 * @param me Pointer to the Timer instance
 */
void Timer_Init(Timer* const me);

/**
 * @brief Clean up Timer resources
 * @param me Pointer to the Timer instance
 */
void Timer_Cleanup(Timer* const me);

/**
 * @brief Create a new Timer instance
 * @return Pointer to the created Timer, NULL if creation failed
 */
Timer* Timer_Create(void);

/**
 * @brief Destroy a Timer instance and free its memory
 * @param me Pointer to the Timer instance
 */
void Timer_Destroy(Timer* const me);

/**
 * @brief Delay execution for specified time
 * @param me Pointer to the Timer instance
 * @param time Delay time in milliseconds
 */
void Timer_delay(Timer* const me, int time);

#endif //BUTTON_DEBOUNCE_TIMER_H
