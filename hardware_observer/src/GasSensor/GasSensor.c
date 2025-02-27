//
// Created by mahon on 1/8/2024.
//

#include "GasSensor.h"
#include <stdlib.h>

static void cleanUpRelations(GasSensor* const me);

void GasSensor_Init(GasSensor* const me) {
    me->itsGasData = NULL;
    me->numObservers = 0;
    
    // Initialize observer arrays
    for (int i = 0; i < MAX_OBSERVERS; i++) {
        me->observers[i] = NULL;
        me->callbacks[i] = NULL;
    }
}

void GasSensor_Cleanup(GasSensor* const me) {
    cleanUpRelations(me);
}

GasSensor* GasSensor_Create(void) {
    GasSensor* me = (GasSensor*) malloc(sizeof(GasSensor));
    if (me != NULL) {
        GasSensor_Init(me);
        me->itsGasData = GasData_Create();
    }
    return me;
}

void GasSensor_Destroy(GasSensor* const me) {
    if (me != NULL) {
        GasSensor_Cleanup(me);
    }
    free(me);
}

/**
 * Observer Pattern: Subscribe method implementation
 * Registers an observer to receive notifications when the subject's state changes
 * 
 * @param me The subject (GasSensor instance)
 * @param observer Pointer to the observer object
 * @param callback The function to call in the observer when state changes
 */
void GasSensor_subscribe(GasSensor* const me, void* observer, gasDataAcceptorPtr callback) {
    if (me->numObservers < MAX_OBSERVERS) {
        me->observers[me->numObservers] = observer;
        me->callbacks[me->numObservers] = callback;
        me->numObservers++;
    }
}

/**
 * Observer Pattern: Unsubscribe method implementation
 * Removes an observer from the notification list
 * 
 * @param me The subject (GasSensor instance)
 * @param observer The observer to remove
 */
void GasSensor_unsubscribe(GasSensor* const me, void* observer) {
    for (int i = 0; i < me->numObservers; i++) {
        if (me->observers[i] == observer) {
            // Shift the remaining observers to fill the gap
            for (int j = i; j < me->numObservers - 1; j++) {
                me->observers[j] = me->observers[j + 1];
                me->callbacks[j] = me->callbacks[j + 1];
            }
            me->numObservers--;
            break;
        }
    }
}

/**
 * Observer Pattern: Notify method implementation
 * Notifies all registered observers about state changes by calling their callbacks
 * 
 * @param me The subject (GasSensor instance)
 */
void GasSensor_notify(GasSensor* const me) {
    for (int i = 0; i < me->numObservers; i++) {
        if (me->observers[i] != NULL && me->callbacks[i] != NULL) {
            // Call each observer's callback with the updated data
            me->callbacks[i](me->observers[i], me->itsGasData);
        }
    }
}

/**
 * Simulates reading from a hardware sensor and updates the internal state
 * Then notifies all observers of the state change (Observer Pattern notification)
 * 
 * @param me The subject (GasSensor instance)
 */
void GasSensor_readSensor(GasSensor* const me) {
    // Simulate reading from a physical sensor
    // In a real application, this would interact with hardware
    if (me->itsGasData != NULL) {
        // For demo: generate some changing values
        me->itsGasData->flowRate += 1;
        if (me->itsGasData->flowRate > 100) me->itsGasData->flowRate = 0;
        
        me->itsGasData->O2Conc = 20 + (me->itsGasData->flowRate % 5);
        me->itsGasData->N2Conc = 70 + (me->itsGasData->flowRate % 10);
        
        // Observer Pattern: Notify observers about the new data
        GasSensor_notify(me);
    }
}

GasData* GasSensor_getItsGasData(const GasSensor* const me) {
    return me->itsGasData;
}

void GasSensor_setItsGasData(GasSensor* const me, GasData* p_GasData) {
    me->itsGasData = p_GasData;
}

static void cleanUpRelations(GasSensor* const me) {
    if (me->itsGasData != NULL) {
        GasData_Destroy(me->itsGasData);
        me->itsGasData = NULL;
    }
}
