//
// Created by mahon on 12/27/2023.
//

#include "WaveformDisplay.h"
#include <stdio.h>


void WaveformDisplay_Init(WaveformDisplay* const self){

}

void WaveformDisplay_Cleanup(WaveformDisplay* const self){

}

void WaveformDisplay_getScalarValue(WaveformDisplay* const self){
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("WaveformDisplay index: %d TimeInterval: %ld  DataValue: %d\n", self->index, tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const self, struct TMDQueue* p_TMDQueue){
    self->itsTMDQueue = p_TMDQueue;
}

WaveformDisplay* WaveformDisplay_Create(void){

}

WaveformDisplay* WaveformDisplay_Destroy(WaveformDisplay* const self){

}
