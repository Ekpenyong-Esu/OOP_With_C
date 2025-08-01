//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_GUARD_ATTTUDECONTROLLER_H
#define REALTIME_GUARD_ATTTUDECONTROLLER_H

#include "GuardedCallExample.h"
#include "Attitude.h"
struct KinematicData;

typedef struct AttitudeController AttitudeController;
struct AttitudeController {
    struct Attitude ownShipAttitude;
    struct KinematicData* itsKinematicData;
};


/* Constructors and destructors:*/

void AttitudeController_Init(AttitudeController* const me);
void AttitudeController_Cleanup(AttitudeController* const me);


/* Operations */

void AttitudeController_manageAttitude(AttitudeController* const me);

struct KinematicData* AttitudeController_getItsKinematicData(const AttitudeController* const me);

void AttitudeController_setItsKinematicData(AttitudeController* const me, struct KinematicData* p_KinematicData);

AttitudeController * AttitudeController_Create(void);

void AttitudeController_Destroy(AttitudeController* const me);

#endif //REALTIME_GUARD_ATTTUDECONTROLLER_H
