//
// Created by mahon on 2/3/2024.
//

#ifndef ANDSTATE_ANDSTATELIST_H
#define ANDSTATE_ANDSTATELIST_H

#include "LightPkg.h"

struct ErrorStateClass;

typedef struct AndStateList AndStateList;
struct AndStateList {
    struct ErrorStateClass* andStates[MAX_ANDSTATES];
    int nAndStates;
};

void AndStateList_Init(AndStateList* const me);
void AndStateList_Cleanup(AndStateList* const me);
AndStateList * AndStateList_Create(void);
void AndStateList_Destroy(AndStateList* const me);

#endif //ANDSTATE_ANDSTATELIST_H
