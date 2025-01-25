#include "ArrhythmiaDetector.h"
#include <stdio.h>
#include <stdlib.h>


void ArrhythmiaDetector_Init(ArrhythmiaDetector* const self){
    (void)self;

}

void ArrhythmiaDetector_Cleanup(ArrhythmiaDetector* const self){
 (void)self;
}

void ArrhythmiaDetector_indentifyArrhythmia(ArrhythmiaDetector* const self){
    (void)self;

}

void ArrhythmiaDetector_getDataSample(ArrhythmiaDetector* const self){
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("ArrhythmiaDetector index: %d TimeInterval: %d  DataValue: %ld\n", self->index,
                   tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

void ArrhythmiaDetector_setItsTMDQueue(ArrhythmiaDetector* const self, struct TMDQueue* p_TMDQueue){
    self->itsTMDQueue = p_TMDQueue;
}

ArrhythmiaDetector * ArrhythmiaDetector_Create(void){
    ArrhythmiaDetector* self = (ArrhythmiaDetector*)malloc(sizeof(ArrhythmiaDetector));
    if (self != NULL)
    {
        ArrhythmiaDetector_Init(self);
    }
    return self;
}

ArrhythmiaDetector * ArrhythmiaDetector_Destroy(ArrhythmiaDetector* const self){
    if (self != NULL)
    {
        ArrhythmiaDetector_Cleanup(self);
    }
    free(self);
}
