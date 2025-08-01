//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "ECG_Module.h"

/**
 * ECG_Module Implementation
 * 
 * This module generates ECG data and sends it to the TMDQueue subject,
 * which then notifies all observers.
 */

static void cleanUpRelations(ECG_Module* const self);

/**
 * Initialize the ECG module
 */
void ECG_Module_Init(ECG_Module* const self) {
    self->dataNum = 0;
    self->itsTMDQueue = NULL;
}

/**
 * Clean up the ECG module
 */
void ECG_Module_Cleanup(ECG_Module* const self) {
    cleanUpRelations(self);
}

/**
 * Observer Pattern: Generate new data and notify observers
 * 
 * This method simulates acquiring a new ECG value and sends it
 * to the TMDQueue subject, which notifies all observers.
 */
void ECG_Module_acquireValue(ECG_Module* const self) {
    // Simulate acquiring a new ECG value
    TimeMarkedData tmd;
    tmd.dataValue = rand();
    tmd.timeInterval = ++self->dataNum;
    
    // Send data to the subject (TMDQueue), which notifies observers
    printf("\nECG_Module: Acquired new data value %d (sample #%ld)\n", 
           tmd.dataValue, tmd.timeInterval);
    TMDQueue_insert(self->itsTMDQueue, tmd);
}

/* operation setLeadPair(int,int) */
void ECG_Module_setLeadPair(ECG_Module* const self, int lead1, int lead2) {
    self->lead1 = lead1;
    self->lead2 = lead2;
}

struct TMDQueue* ECG_Module_getItsTMDQueue(const ECG_Module* const self) {
    return self->itsTMDQueue;
}

void ECG_Module_setItsTMDQueue(ECG_Module* const self, struct TMDQueue* p_TMDQueue) {
    self->itsTMDQueue = p_TMDQueue;
}

ECG_Module * ECG_Module_Create(void) {
    ECG_Module* self = (ECG_Module *) malloc(sizeof(ECG_Module));
    if (self != NULL) {
        ECG_Module_Init(self);
    }
    return self;
}

void ECG_Module_Destroy(ECG_Module* const self) {
    if (self != NULL) {
        ECG_Module_Cleanup(self);
    }
    free(self);
}

static void cleanUpRelations(ECG_Module* const self) {
    if (self->itsTMDQueue != NULL) {
        self->itsTMDQueue = NULL;
    }
}
