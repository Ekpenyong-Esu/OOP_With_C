//
// Created by mahon on 1/25/2024.
//

#include "HeSensor.h"
#include <stdlib.h>
#include <stdio.h>

void HeSensor_Init(HeSensor* const me) {
    GasSensorBase_Init(&me->base);
    me->pressureComp = 1.0;  // Default pressure compensation
    
    // Set initial He-specific values
    me->base.concentration = 0.0;   // Start at 0% He (trace in air)
    me->base.flowRate = 50.0;      // Start at 50 CC/min
}

void HeSensor_Cleanup(HeSensor* const me) {
    GasSensorBase_Cleanup(&me->base);
}

void HeSensor_Update(HeSensor* const me) {
    if (!me->base.isInitialized) return;
    
    // Update base readings
    GasSensorBase_Update(&me->base);
    
    // He-specific adjustments: pressure affects readings
    me->base.concentration *= me->pressureComp;
    me->base.flowRate *= me->pressureComp;
}

void HeSensor_SetPressureComp(HeSensor* const me, double comp) {
    if (comp > 0.0 && comp <= 2.0) {  // Reasonable range for pressure compensation
        me->pressureComp = comp;
    }
}

HeSensor* HeSensor_Create(void) {
    HeSensor* me = (HeSensor*) malloc(sizeof(HeSensor));
    if (me != NULL) {
        HeSensor_Init(me);
    }
    return me;
}

void HeSensor_Destroy(HeSensor* const me) {
    if (me != NULL) {
        HeSensor_Cleanup(me);
    }
    free(me);
}