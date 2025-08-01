//
// Created by mahon on 1/25/2024.
//

#include "GasData.h"
#include <stdio.h>
#include <stdlib.h>

void GasData_Init(GasData* const me) {
    me->gType = UNKNOWN_GAS;
    me->conc = 0.0;
    me->flowInCCPerMin = 0;
}

void GasData_Cleanup(GasData* const me) {
    // Nothing to clean up for now
}

GasData* GasData_Create(void) {
    GasData* me = (GasData*) malloc(sizeof(GasData));
    if (me != NULL) {
        GasData_Init(me);
    }
    return me;
}

void GasData_Destroy(GasData* const me) {
    if (me != NULL) {
        GasData_Cleanup(me);
    }
    free(me);
}

void GasData_print(const GasData* data) {
    if (!data) return;
    
    const char* type_str = "Unknown";
    switch (data->gType) {
        case O2_GAS: type_str = "Oxygen"; break;
        case N2_GAS: type_str = "Nitrogen"; break;
        case HE_GAS: type_str = "Helium"; break;
        default: break;
    }
    
    printf("Gas: %s, Concentration: %.2f%%, Flow Rate: %u CC/min\n", 
           type_str, data->conc, data->flowInCCPerMin);
}