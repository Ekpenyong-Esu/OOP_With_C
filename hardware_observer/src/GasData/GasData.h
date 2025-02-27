#ifndef GASDATA_H
#define GASDATA_H

/**
 * Observer Pattern: State data
 * GasData represents the state that is being observed in the Observer pattern.
 * Changes to this data will trigger notifications to all observers.
 */
typedef struct GasData {
    int flowRate;  // Gas flow rate
    int O2Conc;    // Oxygen concentration
    int N2Conc;    // Nitrogen concentration
} GasData;

// Initialization and cleanup
void GasData_Init(GasData* const me);
void GasData_Cleanup(GasData* const me);

// Creation and destruction
GasData* GasData_Create(void);
void GasData_Destroy(GasData* const me);

#endif /* GASDATA_H */
