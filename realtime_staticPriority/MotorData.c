//
// Created by mahon on 1/25/2024.
//

#include "MotorData.h"


int commandedPosition = 0;
int measuredPosition = 0;

int getCmdPos(void) {
    return commandedPosition;
}

int getMeasPos(void) {
    return measuredPosition;
}

void setCmdPos(int x) {
    commandedPosition = x;
}

void setMeasPos(int x) {
    measuredPosition = x;
}