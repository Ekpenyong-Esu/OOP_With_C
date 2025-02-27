#ifndef DISPLAYCLIENT_H
#define DISPLAYCLIENT_H

#include <stdio.h>
#include <stdlib.h>

// Forward declarations
struct GasSensor;
struct GasData;

/**
 * Observer Pattern: OBSERVER class
 * DisplayClient acts as the Observer in the Observer pattern.
 * It receives updates from the GasSensor (Subject) when gas data changes.
 */
typedef struct DisplayClient {
    struct GasData* itsGasData;     // Local copy of observed data
    struct GasSensor* itsGasSensor; // Reference to the subject being observed
} DisplayClient;

// Initialization and cleanup
void DisplayClient_Init(DisplayClient* const me);
void DisplayClient_Cleanup(DisplayClient* const me);

// Creation and destruction
DisplayClient* DisplayClient_Create(void);
void DisplayClient_Destroy(DisplayClient* const me);

/**
 * Observer Pattern: Update method
 * Called by the subject (GasSensor) when data changes
 */
void DisplayClient_accept(DisplayClient* const me, struct GasData* g);

/**
 * Observer Pattern: Registration method
 * Registers this observer with its subject
 */
void DisplayClient_register(DisplayClient* const me);

// Display functionality
void DisplayClient_show(DisplayClient* const me);
void DisplayClient_alarm(DisplayClient* const me, char* alarmMsg);

// Getters and setters
struct GasData* DisplayClient_getItsGasData(const DisplayClient* const me);
void DisplayClient_setItsGasData(DisplayClient* const me, struct GasData* p_GasData);
struct GasSensor* DisplayClient_getItsGasSensor(const DisplayClient* const me);
void DisplayClient_setItsGasSensor(DisplayClient* const me, struct GasSensor* p_GasSensor);

#endif /* DISPLAYCLIENT_H */
