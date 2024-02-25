//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_GASDATA_H
#define REALTIME_QUEUE_GASDATA_H

#include <stdio.h>
#include <stdlib.h>
#include "QueuingExample.h"

typedef struct GasData GasData;

struct GasData {
    double conc;
    unsigned int flowInCCPerMin;
    GAS_TYPE gType;
};

/* Constructors and destructors:*/

void GasData_Init(GasData* const me);
void GasData_Cleanup(GasData* const me);
GasData * GasData_Create(void);
void GasData_Destroy(GasData* const me);

#endif //REALTIME_QUEUE_GASDATA_H
