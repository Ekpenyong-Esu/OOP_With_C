//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_GASDISPLAY_H
#define REALTIME_QUEUE_GASDISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "QueuingExample.h"
#include "GasData.h"

typedef struct GasDisplay GasDisplay;
struct GasDisplay {
    int screenWidth;
};

/* Constructors and destructors:*/
void GasDisplay_Init(GasDisplay* const me);
void GasDisplay_Cleanup(GasDisplay* const me);

/* Operations */
void GasDisplay_printGasData(GasDisplay* const me, const GAS_TYPE gasType, double gas_conc, unsigned int gas_flow);

GasDisplay * GasDisplay_Create(void);

void GasDisplay_Destroy(GasDisplay* const me);


#endif //REALTIME_QUEUE_GASDISPLAY_H
