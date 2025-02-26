#ifndef SAFETY_MONITOR_CLIENT_H
#define SAFETY_MONITOR_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include "GasSensor.h"
#include "GasData.h"

typedef struct SafetyMonitorClient SafetyMonitorClient;
struct SafetyMonitorClient {
    struct GasData* itsGasData;
    struct GasSensor* itsGasSensor;
};

void SafetyMonitorClient_Init(SafetyMonitorClient* const me);
void SafetyMonitorClient_Cleanup(SafetyMonitorClient* const me);
void SafetyMonitorClient_accept(SafetyMonitorClient* const me, struct GasData* g);
void SafetyMonitorClient_register(SafetyMonitorClient* const me);
void SafetyMonitorClient_checkSafety(SafetyMonitorClient* const me);
SafetyMonitorClient* SafetyMonitorClient_Create(void);
void SafetyMonitorClient_Destroy(SafetyMonitorClient* const me);

#endif
