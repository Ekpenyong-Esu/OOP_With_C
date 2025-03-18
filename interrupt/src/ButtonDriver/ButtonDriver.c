//
// Created by mahon on 1/8/2024.
//

#include "ButtonDriver.h"
#include "button.h"
#include "MicrowaveEmitter.h"
#include "Timer.h"
#include <stdlib.h>
#include <stdio.h>

static void cleanUpRelations(ButtonDriver* const me);

void ButtonDriver_Init(ButtonDriver* const me) {
    me->oldState = 0;
    me->toggleOn = 0;
    me->itsButton = NULL;
    me->itsMicrowaveEmitter = NULL;
    me->itsTimer = NULL;
}

void ButtonDriver_Cleanup(ButtonDriver* const me) {
    cleanUpRelations(me);
}

void ButtonDriver_eventReceive(ButtonDriver* const me) {
    /* Ensure all required components are available */
    if (me == NULL || me->itsTimer == NULL || me->itsButton == NULL || me->itsMicrowaveEmitter == NULL) {
        printf("ButtonDriver: Missing required components\n");
        return;
    }
    Timer_delay(me->itsTimer, DEBOUNCE_TIME);

    /* Check if button state has changed */
    int currentState = Button_getState(me->itsButton);
    if (currentState != me->oldState) {

        /* must be a valid button event */
        me->oldState = currentState;

        printf("ButtonDriver: Button state changed to %s\n",
               currentState ? "PRESSED" : "RELEASED");

        if (!me->oldState) {  // if the old state is 0
            /* must be a button release, so update toggle value */
            if (me->toggleOn) {
                me->toggleOn = 0; /* toggle it off */
                Button_backlight(me->itsButton, 0);
                MicrowaveEmitter_stopEmitting(me->itsMicrowaveEmitter);
            }
            else {
                me->toggleOn = 1; /* toggle it on */
                Button_backlight(me->itsButton, 1);
                MicrowaveEmitter_startEmitting(me->itsMicrowaveEmitter);
            }
        }
        /* if it's not a button release, then it must
           be a button push, which we ignore.
        */
    }

}

struct Button* ButtonDriver_getItsButton(const ButtonDriver* const me) {
    return me->itsButton;
}

void ButtonDriver_setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    if(p_Button != NULL)
    {
        Button_setItsButtonDriver(p_Button, me);
    }
    ButtonDriver_setItsButton1(me, p_Button);
}

struct MicrowaveEmitter* ButtonDriver_getItsMicrowaveEmitter(const ButtonDriver* const me) {
    return me->itsMicrowaveEmitter;
}

void ButtonDriver_setItsMicrowaveEmitter(ButtonDriver* const me, struct MicrowaveEmitter* p_MicrowaveEmitter) {
    me->itsMicrowaveEmitter = p_MicrowaveEmitter;
}

struct Timer* ButtonDriver_getItsTimer(const ButtonDriver* const me) {
    return me->itsTimer;
}

void ButtonDriver_setItsTimer(ButtonDriver* const me, struct Timer* p_Timer) {
    me->itsTimer = p_Timer;
}

ButtonDriver * ButtonDriver_Create(void) {
    ButtonDriver* me = (ButtonDriver *) malloc(sizeof(ButtonDriver));
    if(me!=NULL)
    {
        ButtonDriver_Init(me);
    }
    return me;
}

void ButtonDriver_Destroy(ButtonDriver* const me) {
    if(me!=NULL)
    {
        ButtonDriver_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(ButtonDriver* const me) {
    if(me->itsButton != NULL)
    {
        struct ButtonDriver* p_ButtonDriver = Button_getItsButtonDriver(me->itsButton);
        if(p_ButtonDriver != NULL)
        {
            Button_setItsButtonDriver(me->itsButton, NULL);
        }
        me->itsButton = NULL;
    }
    if(me->itsMicrowaveEmitter != NULL)
    {
        me->itsMicrowaveEmitter = NULL;
    }
    if(me->itsTimer != NULL)
    {
        me->itsTimer = NULL;
    }
}

void ButtonDriver_setItsButton2(ButtonDriver* const me, struct Button* p_Button) {
    me->itsButton = p_Button;
}

void ButtonDriver_setItsButton1(ButtonDriver* const me, struct Button* p_Button) {
    if(me->itsButton != NULL)
    {
        Button_setItsButtonDriver(me->itsButton, NULL);
    }
    ButtonDriver_setItsButton2(me, p_Button);
}

void ButtonDriver_clearItsButton(ButtonDriver* const me) {
    me->itsButton = NULL;
}
