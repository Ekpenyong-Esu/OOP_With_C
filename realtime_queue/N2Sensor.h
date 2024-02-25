//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_N2SENSOR_H
#define REALTIME_QUEUE_N2SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "QueuingExample.h"

typedef struct N2Sensor N2Sensor;
struct N2Sensor {
    double conc;
    unsigned int flow;
};

/* Constructors and destructors:*/
void N2Sensor_Init(N2Sensor* const me);
void N2Sensor_Cleanup(N2Sensor* const me);

/* Operations */

void N2Sensor_getN2Data(N2Sensor* const me);
N2Sensor * N2Sensor_Create(void);
void N2Sensor_Destroy(N2Sensor* const me);

#endif //REALTIME_QUEUE_N2SENSOR_H
