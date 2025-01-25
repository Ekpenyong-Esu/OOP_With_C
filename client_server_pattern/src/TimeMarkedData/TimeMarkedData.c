//
// Created by mahon on 12/27/2023.
//

#include "TimeMarkedData.h"

void TimeMarkedData_Init(TimeMarkedData* const me){

}


void TimeMarkedData_Cleanup(TimeMarkedData* const me){

}

void TimeMarkedData_setItsTMDQueue(TimeMarkedData* const me, struct TMDQueue* p_TMDQueue){
    me->itsTMDQueue = p_TMDQueue;
}
