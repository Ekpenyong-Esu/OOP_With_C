#ifndef GASSENSOR_H
#define GASSENSOR_H

#include "GasData.h"

#define MAX_OBSERVERS 10

/**
 * Observer Pattern: Callback function type for observers
 * This function pointer allows the subject to notify observers
 * without knowing the concrete observer types
 */
typedef void (*gasDataAcceptorPtr)(void* observer, GasData* gasData);

/**
 * Observer Pattern: SUBJECT class
 * GasSensor acts as the Subject (Observable) in the Observer pattern.
 * It maintains a list of observers and notifies them of state changes.
 */
typedef struct GasSensor {
    GasData* itsGasData;                      // The state that observers are monitoring
    void* observers[MAX_OBSERVERS];           // Array of observer objects
    gasDataAcceptorPtr callbacks[MAX_OBSERVERS]; // Callback functions for each observer
    int numObservers;                         // Number of registered observers
} GasSensor;

// Initialization and cleanup
void GasSensor_Init(GasSensor* const me);
void GasSensor_Cleanup(GasSensor* const me);

// Creation and destruction
GasSensor* GasSensor_Create(void);
void GasSensor_Destroy(GasSensor* const me);

/**
 * Observer Pattern: Subject registration methods
 * These methods allow observers to register and unregister for notifications
 */
void GasSensor_subscribe(GasSensor* const me, void* observer, gasDataAcceptorPtr callback);
void GasSensor_unsubscribe(GasSensor* const me, void* observer);

/**
 * Observer Pattern: Notification method
 * This method notifies all registered observers when state changes
 */
void GasSensor_notify(GasSensor* const me);

/**
 * Updates the sensor data and notifies observers of the change
 */
void GasSensor_readSensor(GasSensor* const me);

// Getters and setters
GasData* GasSensor_getItsGasData(const GasSensor* const me);
void GasSensor_setItsGasData(GasSensor* const me, GasData* p_GasData);

#endif /* GASSENSOR_H */
