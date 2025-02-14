//
// Created by mahon on 12/27/2023.
//

#include "TimeMarkedData.h"

void TimeMarkedData_Init(TimeMarkedData* const self){
    (void)self;
}


void TimeMarkedData_Cleanup(TimeMarkedData* const self){
    (void)self;
}

void TimeMarkedData_setItsTMDQueue(TimeMarkedData* const self, struct TMDQueue* p_TMDQueue){
    self->itsTMDQueue = p_TMDQueue;
}
