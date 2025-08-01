//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_O2SENSOR_H
#define REALTIME_QUEUE_O2SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "../GasSensorBase/GasSensorBase.h"

typedef struct O2Sensor O2Sensor;
struct O2Sensor {
    GasSensorBase base;  // Inherit from base sensor
    double targetConcentration;  // O2-specific: Target O2 concentration
};

/* Constructors and destructors */
void O2Sensor_Init(O2Sensor* const me);
void O2Sensor_Cleanup(O2Sensor* const me);
O2Sensor* O2Sensor_Create(void);
void O2Sensor_Destroy(O2Sensor* const me);

/* Operations */
void O2Sensor_Update(O2Sensor* const me);  // Read new O2 data
void O2Sensor_SetTarget(O2Sensor* const me, double target);

#endif //REALTIME_QUEUE_O2SENSOR_H
