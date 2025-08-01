//
// Created by mahon on 1/25/2024.
//

#include "SensorThread.h"
#include <stdlib.h>
#include <time.h>

// Initialize random number generator once
static int rngInitialized = 0;

void SensorThread_Init(SensorThread* const me) {
    me->itsGasDataQueue = NULL;
    
    // Initialize all sensors
    O2Sensor_Init(&(me->itsO2Sensor));
    N2Sensor_Init(&(me->itsN2Sensor));
    HeSensor_Init(&(me->itsHeSensor));
}

void SensorThread_Cleanup(SensorThread* const me) {
    // Cleanup all sensors
    O2Sensor_Cleanup(&(me->itsO2Sensor));
    N2Sensor_Cleanup(&(me->itsN2Sensor));
    HeSensor_Cleanup(&(me->itsHeSensor));
    // Queue is cleaned up by its owner
}

SensorThread* SensorThread_Create(void) {
    SensorThread* me = (SensorThread*) malloc(sizeof(SensorThread));
    if (me != NULL) {
        SensorThread_Init(me);
    }
    return me;
}

void SensorThread_Destroy(SensorThread* const me) {
    if (me != NULL) {
        SensorThread_Cleanup(me);
    }
    free(me);
}

void SensorThread_setItsGasDataQueue(SensorThread* const me, struct GasDataQueue* p_GasDataQueue) {
    me->itsGasDataQueue = p_GasDataQueue;
}

/*
    updateData runs every period of the sensor thread
    and updates each sensor, then randomly decides
    which sensor data to publish to the GasDataQueue.
*/
void SensorThread_updateData(SensorThread* const me) {
    if (!me->itsGasDataQueue) return;  // Need a queue to store data
    
    if (!rngInitialized) {
        srand((unsigned int)time(NULL));
        rngInitialized = 1;
    }

    unsigned char success;
    GasData g;
    GasData_Init(&g);

    // Update all sensors
    O2Sensor_Update(&(me->itsO2Sensor));
    N2Sensor_Update(&(me->itsN2Sensor));
    HeSensor_Update(&(me->itsHeSensor));

    // Randomly select which sensor data to publish
    if (rand() > RAND_MAX / 3) {
        g.gType = HE_GAS;
        g.conc = me->itsHeSensor.base.concentration;
        g.flowInCCPerMin = (unsigned int)me->itsHeSensor.base.flowRate;
        success = GasDataQueue_insert(me->itsGasDataQueue, g);
        if (!success)
            printf("Helium Gas Data queue insertion failed!\n");
    }

    if (rand() > RAND_MAX / 3) {
        g.gType = N2_GAS;
        g.conc = me->itsN2Sensor.base.concentration;
        g.flowInCCPerMin = (unsigned int)me->itsN2Sensor.base.flowRate;
        success = GasDataQueue_insert(me->itsGasDataQueue, g);
        if (!success)
            printf("Nitrogen Gas Data queue insertion failed!\n");
    }

    if (rand() > RAND_MAX / 3) {
        g.gType = O2_GAS;
        g.conc = me->itsO2Sensor.base.concentration;
        g.flowInCCPerMin = (unsigned int)me->itsO2Sensor.base.flowRate;
        success = GasDataQueue_insert(me->itsGasDataQueue, g);
        if (!success)
            printf("Oxygen Gas Data queue insertion failed!\n");
    }
}