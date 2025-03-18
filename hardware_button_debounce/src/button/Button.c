//
// Created by mahon on 1/8/2024.
//

#include "Button.h"
#include "ButtonDriver.h"
#include <stdlib.h>
#include <stdio.h>

void Button_Init(Button* const me) {
    if (me != NULL) {
        me->deviceState = BUTTON_STATE_RELEASED;
        me->backlight = 0;
        me->buttonDriver = NULL;
    }
}

void Button_Cleanup(Button* const me) {
    if (me != NULL) {
        // We don't destroy the buttonDriver here as it might be shared
        // Just disconnect the relationship
        me->buttonDriver = NULL;
    }
}

Button* Button_Create(void) {
    Button* me = (Button*)malloc(sizeof(Button));
    if (me != NULL) {
        Button_Init(me);
    }
    return me;
}

void Button_Destroy(Button* const me) {
    if (me != NULL) {
        Button_Cleanup(me);
        free(me);
    }
}

void Button_backlight(Button* const me, int light) {
    if (me != NULL) {
        me->backlight = light;
        printf("Button: Backlight %s\n", light ? "ON" : "OFF");
    }
}

int Button_getState(Button* const me) {
    if (me != NULL) {
        return me->deviceState;
    }
    return BUTTON_STATE_RELEASED; // Default safe state
}

void Button_setItsButtonDriver(Button* const me, struct ButtonDriver* const buttonDriver) {
    if (me != NULL) {
        me->buttonDriver = buttonDriver;
    }
}

ButtonDriver* Button_getItsButtonDriver(Button* const me) {
    if (me != NULL) {
        return me->buttonDriver;
    }
    return NULL;
}
