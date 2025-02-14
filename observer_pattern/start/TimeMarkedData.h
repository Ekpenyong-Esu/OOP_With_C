//
// Created by mahon on 12/31/2023.
//

#ifndef OBSERVER_PATTERN_TIMEMARKEDDATA_H
#define OBSERVER_PATTERN_TIMEMARKEDDATA_H

#include "ECGPkg.h"

typedef struct TimeMarkedData TimeMarkedData;
struct TimeMarkedData
{
    int timeInterval;
    int dataValue;
    struct TMDQueue* itsTMDQueue;
};

void TimeMarkedData_Init(TimeMarkedData* const me);
void TimeMarkedData_Cleanup(TimeMarkedData* const me);

void TimeMarkedData_setItsTMDQueue(TimeMarkedData* const me, struct TMDQueue* p_TMDQueue);

#endif //OBSERVER_PATTERN_TIMEMARKEDDATA_H
