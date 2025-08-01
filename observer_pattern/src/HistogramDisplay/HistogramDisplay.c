//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "HistogramDisplay.h"
#include "TMDQueue.h"

/**
 * Observer Pattern: OBSERVER Implementation
 * 
 * This file implements an observer in the Observer pattern.
 * It receives notifications from the subject when data changes.
 */

static void cleanUpRelations(HistogramDisplay* const self);

/**
 * Observer Pattern: UPDATE method
 * 
 * This is the callback method that gets called by the subject
 * when new data is available. This is the key method that allows
 * the observer to react to changes in the subject.
 */
void HistogramDisplay_update(void* instance, const struct TimeMarkedData tmd) {
    HistogramDisplay* me = (HistogramDisplay*)instance;
    printf("Observer (HistogramDisplay) received update: TimeInterval: %ld DataValue: %d\n", 
           tmd.timeInterval, tmd.dataValue);
    
    // If we want to use the observer instance in the future, we have it available
    (void)me; // Suppress unused variable warning
    
    // In a real implementation, this would update a histogram display
}

/**
 * Initialize the observer
 */
void HistogramDisplay_Init(HistogramDisplay* const self) {
    self->itsTMDQueue = NULL;
    self->index = 0;  // Initialize index
}

/**
 * Clean up the observer and unsubscribe from the subject
 */
void HistogramDisplay_Cleanup(HistogramDisplay* const me) {
    /* Observer Pattern: Unsubscribe from the subject */
    if (me->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(me->itsTMDQueue, (UpdateFuncPtr)HistogramDisplay_update);
    }
    cleanUpRelations(me);
}

/**
 * Access data from the subject's queue
 */
void HistogramDisplay_getValue(HistogramDisplay* const self) {
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("HistogramDisplay manually checked data: TimeInterval: %ld DataValue:%d\n", 
           tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

/**
 * Internal method to update histogram (placeholder)
 */
void HistogramDisplay_updateHistogram(HistogramDisplay* const me) {
    // This would contain logic to update the histogram visualization
    (void)me; // Suppress unused parameter warning
}

/**
 * Get reference to the subject
 */
struct TMDQueue* HistogramDisplay_getItsTMDQueue(const HistogramDisplay* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

/**
 * Observer Pattern: Connect observer to subject
 * 
 * This key method:
 * 1. Sets a reference to the subject
 * 2. Subscribes to notifications from the subject
 */
void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const me, struct TMDQueue* p_TMDQueue) {
    // First unsubscribe from previous queue if exists
    if (me->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(me->itsTMDQueue, (UpdateFuncPtr)HistogramDisplay_update);
    }
    
    me->itsTMDQueue = p_TMDQueue;
    if (p_TMDQueue != NULL) {
        printf("HistogramDisplay: Subscribing to TMDQueue\n");
        TMDQueue_subscribe(p_TMDQueue, me, (UpdateFuncPtr)HistogramDisplay_update);
    }
}

HistogramDisplay * HistogramDisplay_Create(void) {
    HistogramDisplay* me = (HistogramDisplay *) malloc(sizeof(HistogramDisplay));
    if(me!=NULL)
    {
        HistogramDisplay_Init(me);
    }
    return me;
}

void HistogramDisplay_Destroy(HistogramDisplay* const me) {
    if(me!=NULL)
    {
        HistogramDisplay_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(HistogramDisplay* const me) {
    if(me->itsTMDQueue != NULL)
    {
        me->itsTMDQueue = NULL;
    }
}
