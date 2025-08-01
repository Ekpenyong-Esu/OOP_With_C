//
// Created by mahon on 12/27/2023.
//

#include "WaveformDisplay.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Observer Pattern: OBSERVER Implementation
 * 
 * WaveformDisplay implements an observer in the Observer pattern.
 * It receives notifications from the subject when data changes.
 */

/**
 * Initialize the WaveformDisplay observer
 */
void WaveformDisplay_Init(WaveformDisplay* const self){
    self->itsTMDQueue = NULL;
    self->index = 0;
}

/**
 * Clean up the WaveformDisplay observer and unsubscribe
 */
void WaveformDisplay_Cleanup(WaveformDisplay* const self){
    if (self->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(self->itsTMDQueue, (UpdateFuncPtr)WaveformDisplay_update);
    }
}

/**
 * Observer Pattern: UPDATE method implementation
 * 
 * Called by the subject when there is new data
 */
void WaveformDisplay_update(void* instance, const struct TimeMarkedData tmd) {
    WaveformDisplay* self = (WaveformDisplay*)instance;
    printf("Observer (WaveformDisplay) received update: TimeInterval: %ld DataValue: %d\n", 
           tmd.timeInterval, tmd.dataValue);
    
    // If we want to use the observer instance in the future, we have it available
    (void)self; // Suppress unused variable warning
    
    // In a real implementation, this would update the waveform visualization
}

/**
 * Get a scalar value from the subject's data queue
 */
void WaveformDisplay_getScalarValue(WaveformDisplay* const self){
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("WaveformDisplay manually checked data: TimeInterval: %ld DataValue: %d\n", 
           tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

/**
 * Observer Pattern: Connect observer to subject
 * 
 * This method sets a reference to the subject and subscribes for notifications
 */
void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const self, struct TMDQueue* p_TMDQueue){
    // First unsubscribe from previous queue if exists
    if (self->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(self->itsTMDQueue, (UpdateFuncPtr)WaveformDisplay_update);
    }
    
    self->itsTMDQueue = p_TMDQueue;
    if (p_TMDQueue != NULL) {
        printf("WaveformDisplay: Subscribing to TMDQueue\n");
        TMDQueue_subscribe(p_TMDQueue, self, (UpdateFuncPtr)WaveformDisplay_update);
    }
}

/**
 * Create a new WaveformDisplay observer
 */
WaveformDisplay* WaveformDisplay_Create(void){
    WaveformDisplay* self = (WaveformDisplay*)malloc(sizeof(WaveformDisplay));
    if (self != NULL) {
        WaveformDisplay_Init(self);
    }
    return self;
}

/**
 * Destroy the WaveformDisplay observer
 */
WaveformDisplay* WaveformDisplay_Destroy(WaveformDisplay* const self){
    if (self != NULL) {
        WaveformDisplay_Cleanup(self);
        free((void*)self);
    }
    return NULL;
}
