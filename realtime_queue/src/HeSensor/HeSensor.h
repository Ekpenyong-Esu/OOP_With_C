//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_HESENSOR_H
#define REALTIME_QUEUE_HESENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "../GasSensorBase/GasSensorBase.h"

typedef struct HeSensor HeSensor;
struct HeSensor {
    GasSensorBase base;  // Inherit from base sensor
    double pressureComp;  // He-specific: Pressure compensation factor
};

/* Constructors and destructors */
void HeSensor_Init(HeSensor* const me);
void HeSensor_Cleanup(HeSensor* const me);
HeSensor* HeSensor_Create(void);
void HeSensor_Destroy(HeSensor* const me);

/* Operations */
void HeSensor_Update(HeSensor* const me);  // Read new He data
void HeSensor_SetPressureComp(HeSensor* const me, double comp);

#endif //REALTIME_QUEUE_HESENSOR_H
