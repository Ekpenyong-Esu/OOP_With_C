#include <stdio.h>
#include "button.h"
#include "Led.h"
#include "ButtonHandler.h"


int main()
{

    LED* itsLED;

    itsLED = LED_Create();

    for (int j=0;j<9;j++) {
        ISRAddress[j] = NULL;
        oldVectors[j] = NULL;
    }
    ButtonHandler_setItsLED(itsLED);
    install(); /* install interrupt vectors */
    /* normal system execution stuff */

    return 0;
}