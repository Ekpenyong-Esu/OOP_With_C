#define _POSIX_C_SOURCE 199309L
#include "GasControlEpochTime.h"
#include <time.h>

/**
 * The fixed duration of each control cycle in milliseconds
 */
#define EPOCH_DURATION_MS 100

/**
 * Variable to store the start time of the current epoch
 */
static struct timespec epochStartTime;

/**
 * @brief Starts the epoch timer for a new cycle
 */
void startEpochTimer(void) {
    clock_gettime(CLOCK_MONOTONIC, &epochStartTime);
}

/**
 * @brief Checks if the current epoch has elapsed
 * 
 * @return int Non-zero if the epoch time has elapsed, 0 otherwise
 */
int epochTimerHasElapsed(void) {
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    
    // Calculate elapsed time in milliseconds
    long elapsedMs = (currentTime.tv_sec - epochStartTime.tv_sec) * 1000 + 
                     (currentTime.tv_nsec - epochStartTime.tv_nsec) / 1000000;
    
    // Return non-zero (true) if the epoch duration has elapsed
    return elapsedMs >= EPOCH_DURATION_MS;
}
