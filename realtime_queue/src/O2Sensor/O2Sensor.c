//
// Created by mahon on 1/25/2024.
//

#include "O2Sensor.h"
#include <stdlib.h>
#include <stdio.h>

void O2Sensor_Init(O2Sensor* const me) {
    GasSensorBase_Init(&me->base);
    me->targetConcentration = 20.0;  // Default target O2 concentration
    
    // Set initial O2-specific values
    me->base.concentration = 20.0;  // Start at 20% O2
    me->base.flowRate = 100.0;     // Start at 100 CC/min
}

void O2Sensor_Cleanup(O2Sensor* const me) {
    GasSensorBase_Cleanup(&me->base);
}

void O2Sensor_Update(O2Sensor* const me) {
    if (!me->base.isInitialized) return;
    
    // Update base readings
    GasSensorBase_Update(&me->base);
    
    // O2-specific adjustments: try to maintain concentration near target
    double error = me->targetConcentration - me->base.concentration;
    me->base.flowRate += error * 0.1;  // Simple proportional control
}

void O2Sensor_SetTarget(O2Sensor* const me, double target) {
    if (target >= 0.0 && target <= 100.0) {
        me->targetConcentration = target;
    }
}

O2Sensor* O2Sensor_Create(void) {
    O2Sensor* me = (O2Sensor*) malloc(sizeof(O2Sensor));
    if (me != NULL) {
        O2Sensor_Init(me);
    }
    return me;
}

void O2Sensor_Destroy(O2Sensor* const me) {
    if (me != NULL) {
        O2Sensor_Cleanup(me);
    }
    free(me);
}