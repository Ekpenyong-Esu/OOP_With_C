//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_HESENSOR_H
#define REALTIME_QUEUE_HESENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "QueuingExample.h"

typedef struct HeSensor HeSensor;
struct HeSensor {
    double conc;
    unsigned int flow;
};

/* Constructors and destructors:*/
void HeSensor_Init(HeSensor* const me);
void HeSensor_Cleanup(HeSensor* const me);

/* Operations */

void HeSensor_getHeData(HeSensor* const me);
HeSensor * HeSensor_Create(void);
void HeSensor_Destroy(HeSensor* const me);


#endif //REALTIME_QUEUE_HESENSOR_H
