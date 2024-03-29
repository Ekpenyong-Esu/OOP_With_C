//
// Created by mahon on 2/3/2024.
//

#ifndef STATEPATTERN_STATEACTIONSET_H
#define STATEPATTERN_STATEACTIONSET_H


#include "StatePattern.h"


typedef struct StateActionSet StateActionSet;
struct StateActionSet {
    ActionPtr0 entryAction;
    ActionPtr1 evDigitHandler;
    ActionPtr0 evDotHandler;
    ActionPtr0 evEOSHandler;
    ActionPtr0 evWSHandler;
    ActionPtr0 exitAction;
};

/* Constructors and destructors:*/
void StateActionSet_Init(StateActionSet* const me);
void StateActionSet_Cleanup(StateActionSet* const me);

StateActionSet * StateActionSet_Create(void);
void StateActionSet_Destroy(StateActionSet* const me);


#endif //STATEPATTERN_STATEACTIONSET_H
