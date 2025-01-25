//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_TIMEMARKEDDATA_H
#define CLIENT_SERVER_PATTERN_TIMEMARKEDDATA_H


#include "ECGPkg.h"



// Forward declarations

typedef struct TimeMarkedData TimeMarkedData;

struct TimeMarkedData {
    long timeInterval;
    int dataValue;
    struct TMDQueue* itsTMDQueue;
};

void TimeMarkedData_Init (TimeMarkedData* const me);
void TimeMarkedData_Cleanup (TimeMarkedData* const me);
void TimeMarkedData_setItsTMDQueue(TimeMarkedData* const me, struct TMDQueue* p_TMDQueue);


#endif //CLIENT_SERVER_PATTERN_TIMEMARKEDDATA_H
