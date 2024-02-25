//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_GUARD_FLIGHTDATADISPLAY_H
#define REALTIME_GUARD_FLIGHTDATADISPLAY_H

#include "GuardedCallExample.h"

struct KinematicData;

typedef struct FlightDataDisplay FlightDataDisplay;
struct FlightDataDisplay {
    struct KinematicData* itsKinematicData;
};

/* Constructors and destructors:*/
void FlightDataDisplay_Init(FlightDataDisplay* const me);
void FlightDataDisplay_Cleanup(FlightDataDisplay* const me);

/* Operations */

void FlightDataDisplay_showFlightData(FlightDataDisplay* const me);

struct KinematicData* FlightDataDisplay_getItsKinematicData(const FlightDataDisplay* const me);

void FlightDataDisplay_setItsKinematicData(FlightDataDisplay* const me, struct KinematicData* p_KinematicData);

FlightDataDisplay * FlightDataDisplay_Create(void);

void FlightDataDisplay_Destroy(FlightDataDisplay* const me);


#endif //REALTIME_GUARD_FLIGHTDATADISPLAY_H
