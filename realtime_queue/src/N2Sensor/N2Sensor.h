//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_N2SENSOR_H
#define REALTIME_QUEUE_N2SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "../GasSensorBase/GasSensorBase.h"

typedef struct N2Sensor N2Sensor;
struct N2Sensor {
    GasSensorBase base;  // Inherit from base sensor
    double purityLevel;  // N2-specific: Nitrogen purity level
};

/* Constructors and destructors */
void N2Sensor_Init(N2Sensor* const me);
void N2Sensor_Cleanup(N2Sensor* const me);
N2Sensor* N2Sensor_Create(void);
void N2Sensor_Destroy(N2Sensor* const me);

/* Operations */
void N2Sensor_Update(N2Sensor* const me);  // Read new N2 data
void N2Sensor_UpdatePurity(N2Sensor* const me, double purity);

#endif //REALTIME_QUEUE_N2SENSOR_H
