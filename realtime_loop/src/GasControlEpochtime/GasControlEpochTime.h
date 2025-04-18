#ifndef GAS_CONTROL_EPOCH_TIMER_H
#define GAS_CONTROL_EPOCH_TIMER_H

/**
 * @file GasControlEpochTimer.h
 * @brief Provides timing functionality for the gas control system execution loop
 */

/**
 * @brief Starts the epoch timer for a new cycle
 * 
 * This function initializes a new timing epoch for the control loop.
 * It should be called at the beginning of each control cycle.
 */
void startEpochTimer(void);

/**
 * @brief Checks if the current epoch has elapsed
 * 
 * @return int Non-zero if the epoch time has elapsed, 0 otherwise
 */
int epochTimerHasElapsed(void);

#endif /* GAS_CONTROL_EPOCH_TIMER_H */