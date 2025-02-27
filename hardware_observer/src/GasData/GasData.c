#include "GasData.h"
#include <stdlib.h>

void GasData_Init(GasData* const me) {
}

void GasData_Cleanup(GasData* const me) {
}

GasData* GasData_Create(void) {
    GasData* me = (GasData*) malloc(sizeof(GasData));
    if (me != NULL) {
        me->flowRate = 0;
        me->O2Conc = 0;
        me->N2Conc = 0;
    }
    return me;
}

void GasData_Destroy(GasData* const me) {
    free(me);
}
