//
// Created by mahon on 1/25/2024.
//
#include "GasControlExecutive.h"
#include "GasActuatorThread.h"
#include "GasControlEpochTime.h"
#include "GasDisplayThread.h"
#include "GasSensorThread.h"
#include <stdbool.h>


void controlLoop(void) {
    while (true) {
        startEpochTimer();
        GasSensorThread_run();
        GasActuatorThread_run();
        GasDisplayThread_run();
        while(!epochTimerHasElapsed()) ;
    };
}
