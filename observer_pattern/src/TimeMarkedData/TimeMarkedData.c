//
// Created by mahon on 12/27/2023.
//

#include "TimeMarkedData.h"
#include <stdlib.h>
/**
 * Observer Pattern: Subject State Implementation
 *
 * TimeMarkedData represents the state that is shared by the Subject
 * with all registered Observers when state changes occur.
 */

/**
 * Initialize the data object
 */
void TimeMarkedData_Init(TimeMarkedData* const self){
    self->timeInterval = 0;
    self->dataValue = 0;
    self->itsTMDQueue = NULL;
}

/**
 * Clean up the data object
 */
void TimeMarkedData_Cleanup(TimeMarkedData* const self){
    // Nothing to clean up for this simple data structure
    (void)self;
}

/**
 * Set the reference to the containing queue
 */
void TimeMarkedData_setItsTMDQueue(TimeMarkedData* const self, struct TMDQueue* p_TMDQueue){
    self->itsTMDQueue = p_TMDQueue;
}
