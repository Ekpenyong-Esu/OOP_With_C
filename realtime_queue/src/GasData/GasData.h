//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_GASDATA_H
#define REALTIME_QUEUE_GASDATA_H

#include <stdio.h>
#include <stdlib.h>

// Gas type definitions
typedef enum {
    UNKNOWN_GAS = 0,
    O2_GAS = 1,    // Oxygen
    N2_GAS = 2,    // Nitrogen
    HE_GAS = 3     // Helium
} GAS_TYPE;

// Gas data structure
typedef struct GasData {
    GAS_TYPE gType;           // Type of gas
    double conc;              // Concentration of gas
    unsigned int flowInCCPerMin;  // Flow rate in CC/min
} GasData;

/* Constructors and destructors */
void GasData_Init(GasData* const me);
void GasData_Cleanup(GasData* const me);
GasData* GasData_Create(void);
void GasData_Destroy(GasData* const me);

/* Operations */
void GasData_print(const GasData* data);

#endif //REALTIME_QUEUE_GASDATA_H
