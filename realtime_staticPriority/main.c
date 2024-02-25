#include <stdio.h>
#include "MotorPositionSensor.h"
#include "MotorDisplay.h"
#include "MotorController.h"
#include "MotorData.h"

int main(void) {
    /* initialize the links and start the tasks */
    MotorPositionSensor_initRelations();
    MotorDisplay_initRelations();
    MotorController_initRelations();

    /* now let the tasks do their thing */
    while (TRUE) {
        task();
    }
}