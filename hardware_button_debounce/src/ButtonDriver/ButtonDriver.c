//
// Created by mahon on 1/8/2024.
//

#include "ButtonDriver.h"
#include "Button.h"
#include "MicrowaveEmitter.h"
#include "Timer.h"
#include <stdlib.h>
#include <stdint.h>

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

/**
 * @brief Processes button events and controls the microwave emitter accordingly
 * @param me Pointer to the ButtonDriver instance
 */
void ButtonDriver_eventReceive(ButtonDriver* const me) {
    /* Ensure all required components are available */
    if (me == NULL || me->itsTimer == NULL || me->itsButton == NULL || me->itsMicrowaveEmitter == NULL) {
        return;
    }

    /* Apply debounce delay */
    Timer_delay(me->itsTimer, DEBOUNCE_TIME);

    /* Check if button state has changed */
    int currentState = Button_getState(me->itsButton);
    if (currentState != me->oldState) {
        /* Update stored state with the new button state */
        me->oldState = me->itsButton->deviceState;

        /* Process button release events (when state is 0) */
        if (!me->oldState) {
            /* Toggle the state and update related components */
            if (me->toggleOn) {
                /* Turn off */
                me->toggleOn = 0;
                Button_backlight(me->itsButton, 0);
                MicrowaveEmitter_stopEmitting(me->itsMicrowaveEmitter);
            } else {
                /* Turn on */
                me->toggleOn = 1;
                Button_backlight(me->itsButton, 1);
                MicrowaveEmitter_startEmitting(me->itsMicrowaveEmitter);
            }
        }
        /* Button press events (when state is not 0) are intentionally ignored */
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
