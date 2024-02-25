//
// Created by mahon on 2/3/2024.
//

#ifndef ANDSTATE_STATEACTIONSET_H
#define ANDSTATE_STATEACTIONSET_H

#include "LightPkg.h"

typedef struct StateActionSet StateActionSet;
struct StateActionSet {
    ActionPtr0 entryAction;
    ActionPtr0 evAbortHandler;
    ActionPtr0 evDisableHandler;
    ActionPtr0 evEnableHandler;
    ActionPtr0 evErrorHandler;
    ActionPtr0 evOkHandler;
    ActionPtr0 evRunHandler;
    ActionPtr0 evShutDownHandler;
    ActionPtr0 evWarningHandler;
    ActionPtr0 exitAction;
    ActionPtr1 is_inHandler;
};


void StateActionSet_Init(StateActionSet* const me);
void StateActionSet_Cleanup(StateActionSet* const me);
StateActionSet * StateActionSet_Create(void);
void StateActionSet_Destroy(StateActionSet* const me);


#endif //ANDSTATE_STATEACTIONSET_H
