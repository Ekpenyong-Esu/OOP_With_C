//
// Created by mahon on 12/27/2023.
//

#include <stdlib.h>
#include "ECG_Module.h"

static void cleanUpRelations(ECG_Module* const self);

void ECG_Module_Init(ECG_Module* const self) {
    self->dataNum = 0;
    self->itsTMDQueue = NULL;
}
void ECG_Module_Cleanup(ECG_Module* const self) {
    cleanUpRelations(self);
}
/* operation acquireValue() */
void ECG_Module_acquireValue(ECG_Module* const self) {
// in actual implementation, this would return the
// measured voltage across the lead pair
    TimeMarkedData tmd;
    tmd.dataValue = rand();
    tmd.timeInterval = ++self->dataNum;
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
