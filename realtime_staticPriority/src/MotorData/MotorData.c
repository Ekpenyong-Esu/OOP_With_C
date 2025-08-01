// Simplified implementation using FreeRTOS API for static priority
#include "MotorData.h"

// Static variables for motor data

// Getter for commanded position
int getCmdPos(void) {
    return commandedPosition;
}

// Getter for measured position
int getMeasPos(void) {
    return measuredPosition;
}

// Setter for commanded position
void setCmdPos(int x) {
    commandedPosition = x;
}

// Setter for measured position
void setMeasPos(int x) {
    measuredPosition = x;
}
