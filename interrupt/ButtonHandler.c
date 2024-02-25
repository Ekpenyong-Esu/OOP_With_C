//
// Created by mahon on 1/13/2024.
//

#include "ButtonHandler.h"
#include "LED.h"
#include "RobotInterruptVectorTable.h"

ButtonVectorPtr oldVectors[10];

static struct LED* itsLED;

void deinstall(void) {
    ISRAddress[0] = oldVectors[0];
    ISRAddress[1] = oldVectors[1];
}

void handleButtonPushInterrupt(void) {
    LED_LightOn(itsLED);
}

void handleButtonReleaseInterrupt(void) {
    LED_LightOff(itsLED);
}

void install(void) {
    oldVectors[0] = ISRAddress[0];
    oldVectors[1] = ISRAddress[1];
    ISRAddress[0] = handleButtonPushInterrupt;
    ISRAddress[1] = handleButtonReleaseInterrupt;
}

struct LED* ButtonHandler_getItsLED(void) {
    return (struct LED*)itsLED;
}

void ButtonHandler_setItsLED(struct LED* p_LED) {
    itsLED = p_LED;
}