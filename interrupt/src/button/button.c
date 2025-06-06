//
// Created by mahon on 1/8/2024.
//

#include "button.h"
#include <stdlib.h>

void Button_Init(Button* const me){
    me->deviceState = 0;
    me->backlight = 0;
    me->buttonDriver = NULL;
}
void Button_Cleanup(Button* const me){
/**
 * 1. free the memory allocated for the buttonDriver
 * 2. set the pointer to NULL
 */
    if (me->buttonDriver != NULL)
    {
        ButtonDriver_Destroy(me->buttonDriver);
    }
    me->buttonDriver = NULL;
}

Button* Button_Create(void){
    Button* me = (Button*)malloc(sizeof(Button));
    if (me != NULL)
    {
        Button_Init(me);
    }
    return me;
}

void Button_Destroy(Button* const me){
    if (me != NULL)
    {
        Button_Cleanup(me);
    }
    free(me);
}

void Button_backlight(Button* const me, int backlight){
    me->backlight = backlight;
}

int Button_getState(Button* const me){
    return me->deviceState;
}

void Button_setItsButtonDriver(Button* const me, ButtonDriver* const buttonDriver){
    me->buttonDriver = buttonDriver;
}

ButtonDriver* Button_getItsButtonDriver(Button* const me){
    return me->buttonDriver;
}
