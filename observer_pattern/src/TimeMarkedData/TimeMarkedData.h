//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_TIMEMARKEDDATA_H
#define CLIENT_SERVER_PATTERN_TIMEMARKEDDATA_H

#include "ECGPkg.h"
#include <string.h>

/**
 * Observer Pattern: Subject State
 *
 * TimeMarkedData represents the state data that is tracked by the Subject
 * and shared with Observer objects when state changes occur.
 * This is a key component in the Observer pattern - it's the data being observed.
 */

// Forward declarations
typedef struct TimeMarkedData TimeMarkedData;

/**
 * Data structure for time-marked ECG data
 */
struct TimeMarkedData {
    long timeInterval;           // Timestamp for the data
    int dataValue;               // The ECG value
    struct TMDQueue* itsTMDQueue; // Back-reference to the queue
};

void TimeMarkedData_Init (TimeMarkedData* const self);
void TimeMarkedData_Cleanup (TimeMarkedData* const self);
void TimeMarkedData_setItsTMDQueue(TimeMarkedData* const self, struct TMDQueue* p_TMDQueue);


#endif //CLIENT_SERVER_PATTERN_TIMEMARKEDDATA_H
