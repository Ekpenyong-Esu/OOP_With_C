//
// Created by mahon on 1/25/2024.
//

#include "N2Sensor.h"
#include <stdlib.h>
#include <stdio.h>

void N2Sensor_Init(N2Sensor* const me) {
    GasSensorBase_Init(&me->base);
    me->purityLevel = 99.9;  // Default N2 purity level
    
    // Set initial N2-specific values
    me->base.concentration = 78.0;  // Start at 78% N2 (typical air composition)
    me->base.flowRate = 100.0;     // Start at 100 CC/min
}

void N2Sensor_Cleanup(N2Sensor* const me) {
    GasSensorBase_Cleanup(&me->base);
}

void N2Sensor_Update(N2Sensor* const me) {
    if (!me->base.isInitialized) return;
    
    // Update base readings
    GasSensorBase_Update(&me->base);
    
    // N2-specific adjustments: purity affects concentration
    me->base.concentration *= (me->purityLevel / 100.0);
}

void N2Sensor_UpdatePurity(N2Sensor* const me, double purity) {
    if (purity >= 0.0 && purity <= 100.0) {
        me->purityLevel = purity;
    }
}

N2Sensor* N2Sensor_Create(void) {
    N2Sensor* me = (N2Sensor*) malloc(sizeof(N2Sensor));
    if (me != NULL) {
        N2Sensor_Init(me);
    }
    return me;
}

void N2Sensor_Destroy(N2Sensor* const me) {
    if (me != NULL) {
        N2Sensor_Cleanup(me);
    }
    free(me);
}