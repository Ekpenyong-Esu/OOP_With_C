#include "GasSensorBase.h"
#include <stdlib.h>
#include <time.h>

// Initialize random seed using static variable
static int rngInitialized = 0;

void GasSensorBase_Init(GasSensorBase* const me) {
    if (!rngInitialized) {
        srand((unsigned int)time(NULL));
        rngInitialized = 1;
    }
    
    me->concentration = 0.0;
    me->flowRate = 0.0;
    me->health = 100;
    me->isInitialized = 1;
}

void GasSensorBase_Cleanup(GasSensorBase* const me) {
    me->isInitialized = 0;
}

// Default sensor update behavior with some simulated noise
void GasSensorBase_Update(GasSensorBase* const me) {
    if (!me->isInitialized) return;
    
    // Add random noise to readings
    double noise = ((double)(rand() % 21) - 10.0) / 10.0; // ±1.0 noise
    me->concentration += noise;
    
    noise = ((double)(rand() % 21) - 10.0) / 10.0;
    me->flowRate += noise;
    
    // Keep values in reasonable ranges
    if (me->concentration < 0.0) me->concentration = 0.0;
    if (me->flowRate < 0.0) me->flowRate = 0.0;
}

int GasSensorBase_CheckHealth(GasSensorBase* const me) {
    if (!me->isInitialized) return 0;
    
    // Simple health check - ensure values are in reasonable ranges
    if (me->concentration < 0.0 || me->concentration > 100.0 ||
        me->flowRate < 0.0 || me->flowRate > 1000.0) {
        me->health -= 5;
        if (me->health < 0) me->health = 0;
    } else {
        if (me->health < 100) me->health += 1;
    }
    
    return me->health;
}

void GasSensorBase_Calibrate(GasSensorBase* const me) {
    if (!me->isInitialized) return;
    
    // In a real system, this would perform actual calibration
    // For simulation, we just reset to nominal values
    me->concentration = 20.0;  // Start at 20% nominal
    me->flowRate = 100.0;     // Start at 100 CC/min nominal
    me->health = 100;        // Reset health after calibration
}
