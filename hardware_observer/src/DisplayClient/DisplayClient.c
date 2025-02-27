//
// Created by mahon on 1/8/2024.
//

#include "DisplayClient.h"
#include "GasSensor.h"
#include "GasData.h"

static void cleanUpRelations(DisplayClient* const me);

void DisplayClient_Init(DisplayClient* const me) {
    me->itsGasData = NULL;
    me->itsGasSensor = NULL;
}

void DisplayClient_Cleanup(DisplayClient* const me) {
    cleanUpRelations(me);
}

/**
 * Observer Pattern: Update method implementation
 * This is the callback that gets executed when the subject (GasSensor)
 * notifies this observer of a state change.
 * 
 * @param me The observer (DisplayClient instance)
 * @param g Updated gas data from the subject
 */
void DisplayClient_accept(DisplayClient* const me, struct GasData* g) {
    if (!me->itsGasData)
        me->itsGasData = GasData_Create();

    if (me->itsGasData) {
        // Update the local copy of the data
        me->itsGasData->flowRate = g->flowRate;
        me->itsGasData->N2Conc = g->N2Conc;
        me->itsGasData->O2Conc = g->O2Conc;
        
        // React to the update by displaying the new data
        DisplayClient_show(me);
    }
}

void DisplayClient_alarm(DisplayClient* const me, char* alarmMsg) {
    printf("ALERT! ");
    printf("%s\n",alarmMsg);
    printf("\n\n");  // Fixed newline characters
}

/**
 * Observer Pattern: Registration method implementation
 * Registers this observer with its subject to receive notifications
 * 
 * @param me The observer (DisplayClient instance)
 */
void DisplayClient_register(DisplayClient* const me) {
    if (me->itsGasSensor)
        // Register with the subject using our callback function
        GasSensor_subscribe(me->itsGasSensor, me, (gasDataAcceptorPtr) DisplayClient_accept);
}

void DisplayClient_show(DisplayClient* const me) {
    if (me->itsGasData) {
        printf("Gas Flow Rate = %5d\n", me->itsGasData->flowRate);  // Fixed newline characters
        printf("O2 Concentration = %2d\n", me->itsGasData->O2Conc); // Fixed display of O2 concentration
        printf("N2 Concentration = %2d\n\n", me->itsGasData->N2Conc); // Fixed newline characters
    }
    else
        printf("No data available\n\n"); // Fixed newline characters
}

struct GasData* DisplayClient_getItsGasData(const DisplayClient* const me) {
    return (struct GasData*)me->itsGasData;
}

void DisplayClient_setItsGasData(DisplayClient* const me, struct GasData* p_GasData) {
    me->itsGasData = p_GasData;
}

struct GasSensor* DisplayClient_getItsGasSensor(const DisplayClient* const me) {
    return (struct GasSensor*)me->itsGasSensor;
}

void DisplayClient_setItsGasSensor(DisplayClient* const me, struct GasSensor* p_GasSensor) {
    me->itsGasSensor = p_GasSensor;
}

DisplayClient * DisplayClient_Create(void) {
    DisplayClient* me = (DisplayClient *) malloc(sizeof(DisplayClient));
    if(me!=NULL) {
        DisplayClient_Init(me);
    }
    return me;
}

void DisplayClient_Destroy(DisplayClient* const me) {
    if(me!=NULL) {
        DisplayClient_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(DisplayClient* const me) {
    if(me->itsGasData != NULL) {
        me->itsGasData = NULL;
    }
    if(me->itsGasSensor != NULL) {
        me->itsGasSensor = NULL;
    }
}
