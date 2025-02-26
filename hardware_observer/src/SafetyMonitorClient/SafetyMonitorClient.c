//
// Created by mahon on 1/8/2024.
//

#include "SafetyMonitorClient.h"

#define MAX_O2_CONCENTRATION 25
#define MIN_O2_CONCENTRATION 19
#define MAX_N2_CONCENTRATION 82
#define MIN_N2_CONCENTRATION 78

static void cleanUpRelations(SafetyMonitorClient* const me);

void SafetyMonitorClient_Init(SafetyMonitorClient* const me) {
    me->itsGasData = NULL;
    me->itsGasSensor = NULL;
}

void SafetyMonitorClient_Cleanup(SafetyMonitorClient* const me) {
    cleanUpRelations(me);
}

void SafetyMonitorClient_accept(SafetyMonitorClient* const me, struct GasData* g) {
    if (!me->itsGasData)
        me->itsGasData = GasData_Create();
    
    if (me->itsGasData) {
        me->itsGasData->flowRate = g->flowRate;
        me->itsGasData->N2Conc = g->N2Conc;
        me->itsGasData->O2Conc = g->O2Conc;
        SafetyMonitorClient_checkSafety(me);
    }
}

void SafetyMonitorClient_register(SafetyMonitorClient* const me) {
    if (me->itsGasSensor)
        GasSensor_subscribe(me->itsGasSensor, me, (gasDataAcceptorPtr)SafetyMonitorClient_accept);
}

void SafetyMonitorClient_checkSafety(SafetyMonitorClient* const me) {
    if (!me->itsGasData) return;
    
    if (me->itsGasData->O2Conc > MAX_O2_CONCENTRATION)
        printf("DANGER: O2 concentration too high: %d%%\n", me->itsGasData->O2Conc);
    else if (me->itsGasData->O2Conc < MIN_O2_CONCENTRATION)
        printf("DANGER: O2 concentration too low: %d%%\n", me->itsGasData->O2Conc);
        
    if (me->itsGasData->N2Conc > MAX_N2_CONCENTRATION)
        printf("DANGER: N2 concentration too high: %d%%\n", me->itsGasData->N2Conc);
    else if (me->itsGasData->N2Conc < MIN_N2_CONCENTRATION)
        printf("DANGER: N2 concentration too low: %d%%\n", me->itsGasData->N2Conc);
}

SafetyMonitorClient* SafetyMonitorClient_Create(void) {
    SafetyMonitorClient* me = (SafetyMonitorClient*)malloc(sizeof(SafetyMonitorClient));
    if (me != NULL) {
        SafetyMonitorClient_Init(me);
    }
    return me;
}

void SafetyMonitorClient_Destroy(SafetyMonitorClient* const me) {
    if (me != NULL) {
        SafetyMonitorClient_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(SafetyMonitorClient* const me) {
    if (me->itsGasData != NULL) {
        me->itsGasData = NULL;
    }
    if (me->itsGasSensor != NULL) {
        me->itsGasSensor = NULL;
    }
}
