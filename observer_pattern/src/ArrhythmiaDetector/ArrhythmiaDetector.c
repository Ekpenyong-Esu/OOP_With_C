#include "ArrhythmiaDetector.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Observer Pattern: OBSERVER Implementation
 * 
 * ArrhythmiaDetector implements an observer in the Observer pattern.
 * It receives notifications from the subject when ECG data changes.
 */

/**
 * Initialize the ArrhythmiaDetector observer
 */
void ArrhythmiaDetector_Init(ArrhythmiaDetector* const self){
    self->index = 0;
    self->pcvCount = 0;
    self->STSegmentHeight = 0;
    self->firstDegreeHeatBlock = 0;
    self->Two_one_heartBlock = 0;
    self->prematureAtrialContraction = 0;
    self->flbrillation = 0;
    self->itsTMDQueue = NULL;
}

/**
 * Clean up the ArrhythmiaDetector observer
 */
void ArrhythmiaDetector_Cleanup(ArrhythmiaDetector* const self){
    if (self->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(self->itsTMDQueue, (UpdateFuncPtr)ArrhythmiaDetector_update);
    }
}

/**
 * Observer Pattern: UPDATE method implementation
 * 
 * Called by the subject when there is new data
 */
void ArrhythmiaDetector_update(void* instance, const struct TimeMarkedData tmd) {
    ArrhythmiaDetector* self = (ArrhythmiaDetector*)instance;
    printf("Observer (ArrhythmiaDetector) received update: TimeInterval: %ld DataValue: %d\n", 
           tmd.timeInterval, tmd.dataValue);
    // In a real implementation, this would analyze the ECG for arrhythmias
    ArrhythmiaDetector_indentifyArrhythmia(self);
}

/**
 * Analyze ECG data to detect arrhythmias
 */
void ArrhythmiaDetector_indentifyArrhythmia(ArrhythmiaDetector* const self){
    // This would contain logic to detect various arrhythmias
    printf("ArrhythmiaDetector: Analyzing ECG for arrhythmias\n");
}

/**
 * Get a data sample from the subject's queue
 */
void ArrhythmiaDetector_getDataSample(ArrhythmiaDetector* const self){
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("ArrhythmiaDetector manually checked data: TimeInterval: %ld DataValue: %d\n", 
           tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

/**
 * Observer Pattern: Connect observer to subject
 * 
 * This method sets a reference to the subject and subscribes for notifications
 */
void ArrhythmiaDetector_setItsTMDQueue(ArrhythmiaDetector* const self, struct TMDQueue* p_TMDQueue){
    self->itsTMDQueue = p_TMDQueue;
    if (p_TMDQueue != NULL) {
        printf("ArrhythmiaDetector: Subscribing to TMDQueue\n");
        TMDQueue_subscribe(p_TMDQueue, self, (UpdateFuncPtr)ArrhythmiaDetector_update);
    }
}

/**
 * Create a new ArrhythmiaDetector observer
 */
ArrhythmiaDetector* ArrhythmiaDetector_Create(void){
    ArrhythmiaDetector* self = (ArrhythmiaDetector*)malloc(sizeof(ArrhythmiaDetector));
    if (self != NULL) {
        ArrhythmiaDetector_Init(self);
    }
    return self;
}

/**
 * Destroy the ArrhythmiaDetector observer
 */
ArrhythmiaDetector* ArrhythmiaDetector_Destroy(ArrhythmiaDetector* const self){
    if (self != NULL) {
        ArrhythmiaDetector_Cleanup(self);
        free(self);
    }
    return NULL;
}
