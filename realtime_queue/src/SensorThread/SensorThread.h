//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_SENSORTHREAD_H
#define REALTIME_QUEUE_SENSORTHREAD_H

#include <stdio.h>
#include <stdlib.h>
#include "../O2Sensor/O2Sensor.h"
#include "../N2Sensor/N2Sensor.h"
#include "../HeSensor/HeSensor.h"
#include "../GasDataQueue/GasDataQueue.h"

typedef struct SensorThread SensorThread;
struct SensorThread {
    struct GasDataQueue* itsGasDataQueue;
    struct HeSensor itsHeSensor;
    struct N2Sensor itsN2Sensor;
    struct O2Sensor itsO2Sensor;
};

/* Constructors and destructors */
void SensorThread_Init(SensorThread* const me);
void SensorThread_Cleanup(SensorThread* const me);
SensorThread* SensorThread_Create(void);
void SensorThread_Destroy(SensorThread* const me);

/* Operations */
void SensorThread_updateData(SensorThread* const me);
void SensorThread_setItsGasDataQueue(SensorThread* const me, struct GasDataQueue* p_GasDataQueue);

#endif //REALTIME_QUEUE_SENSORTHREAD_H
