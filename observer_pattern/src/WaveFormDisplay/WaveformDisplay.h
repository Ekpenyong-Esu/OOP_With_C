//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_WAVEFORMDISPLAY_H
#define CLIENT_SERVER_PATTERN_WAVEFORMDISPLAY_H

#include "ECGPkg.h"
#include "TMDQueue.h"

/**
 * Observer Pattern: OBSERVER class
 *
 * WaveformDisplay is another observer in the Observer pattern.
 * It displays time-series data as a waveform visualization.
 * This observer receives updates from TMDQueue (the Subject).
 */
typedef struct WaveformDisplay WaveformDisplay;
struct WaveformDisplay
{
    int index;                   // Current position in the queue
    struct TMDQueue* itsTMDQueue; // Reference to the subject
};

/**
 * Initialize the observer
 */
void WaveformDisplay_Init(WaveformDisplay* const self);

/**
 * Clean up the observer
 */
void WaveformDisplay_Cleanup(WaveformDisplay* const self);

/**
 * Observer Pattern: UPDATE method
 * 
 * Called by the subject when there is new data
 */
void WaveformDisplay_update(void* instance, const struct TimeMarkedData tmd);

/**
 * Get a scalar value from the subject's data queue
 */
void WaveformDisplay_getScalarValue(WaveformDisplay* const self);

/**
 * Observer Pattern: Connect observer to subject
 * 
 * This method:
 * 1. Sets a reference to the subject (TMDQueue)
 * 2. Subscribes to notifications from the subject
 */
void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const self, struct TMDQueue* p_TMDQueue);

/**
 * Create a new WaveformDisplay observer
 */
WaveformDisplay* WaveformDisplay_Create(void);

/**
 * Destroy the WaveformDisplay observer
 */
WaveformDisplay* WaveformDisplay_Destroy(WaveformDisplay* const self);

#endif //CLIENT_SERVER_PATTERN_WAVEFORMDISPLAY_H
