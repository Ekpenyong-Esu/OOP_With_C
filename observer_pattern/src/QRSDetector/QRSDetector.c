//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "QRSDetector.h"

/**
 * Observer Pattern: OBSERVER Implementation
 * 
 * QRSDetector implements an observer in the Observer pattern.
 * It receives notifications from the subject when ECG data changes.
 */

static void cleanUpRelations(QRSDetector* const self);

/**
 * Initialize the QRSDetector observer
 */
void QRSDetector_Init(QRSDetector* const self){
    self->heartRate = 0;
    self->index = 0;
    self->itsTMDQueue = NULL;
}

/**
 * Clean up the QRSDetector observer
 */
void QRSDetector_Cleanup(QRSDetector* const self){
    if (self->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(self->itsTMDQueue, (UpdateFuncPtr)QRSDetector_update);
    }
    cleanUpRelations(self);
}

/**
 * Observer Pattern: UPDATE method implementation
 * 
 * Called by the subject when there is new data
 */
void QRSDetector_update(void* instance, const struct TimeMarkedData tmd) {
    QRSDetector* self = (QRSDetector*)instance;
    printf("Observer (QRSDetector) received update: TimeInterval: %ld DataValue: %d\n", 
           tmd.timeInterval, tmd.dataValue);
    // In a real implementation, this would analyze the ECG waveform for QRS complexes
    QRSDetector_computeHR(self);
}

/**
 * Compute heart rate based on QRS detection
 */
void QRSDetector_computeHR(QRSDetector* const self){
    self->heartRate = self->heartRate + 10;
    printf("QRSDetector: Heart rate computed: %d BPM\n", self->heartRate);
}

/**
 * Get a data sample from the subject's queue
 */
void QRSDetector_getDataSample(QRSDetector* const self){
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("QRSDetector manually checked data: TimeInterval: %ld DataValue: %d\n", 
           tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

/**
 * Observer Pattern: Connect observer to subject
 * 
 * This method sets a reference to the subject and subscribes for notifications
 */
void QRSDetector_setItsTMDQueue(QRSDetector* const self, struct TMDQueue* p_TMDQueue){
    self->itsTMDQueue = p_TMDQueue;
    if (p_TMDQueue != NULL) {
        printf("QRSDetector: Subscribing to TMDQueue\n");
        TMDQueue_subscribe(p_TMDQueue, self, (UpdateFuncPtr)QRSDetector_update);
    }
}

/**
 * Get reference to the subject
 */
struct TMDQueue* QRSDetector_getItsTMDQueue(const QRSDetector* const self){
    return self->itsTMDQueue;
}

/**
 * Create a new QRSDetector observer
 */
QRSDetector* QRSDetector_Create(void){
    QRSDetector* self = (QRSDetector*)malloc(sizeof(QRSDetector));
    if (self != NULL) {
        QRSDetector_Init(self);
    }
    return self;
}

/**
 * Destroy the QRSDetector observer
 */
QRSDetector* QRSDetector_Destroy(QRSDetector* const self){
    if (self != NULL) {
        QRSDetector_Cleanup(self);
        free(self);
    }
    return NULL;
}

/**
 * Clean up related objects
 */
static void cleanUpRelations(QRSDetector* const self) {
    if (self->itsTMDQueue != NULL) {
        self->itsTMDQueue = NULL;
    }
}
