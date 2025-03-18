//
// Created by mahon on 1/8/2024.
//

#include "ButtonDriver.h"
#include "Button.h"
#include "MicrowaveEmitter.h"
#include "Timer.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Helper function to clean up relationships
 * @param me Pointer to the ButtonDriver instance
 */
static void cleanUpRelations(ButtonDriver* const me);

void ButtonDriver_Init(ButtonDriver* const me) {
    if (me != NULL) {
        me->oldState = 0;
        me->toggleOn = 0;
        me->itsButton = NULL;
        me->itsMicrowaveEmitter = NULL;
        me->itsTimer = NULL;
    }
}

void ButtonDriver_Cleanup(ButtonDriver* const me) {
    if (me != NULL) {
        cleanUpRelations(me);
    }
}

/**
 * @brief Processes button events and controls the microwave emitter accordingly
 * @param me Pointer to the ButtonDriver instance
 */
void ButtonDriver_eventReceive(ButtonDriver* const me) {
    /* Ensure all required components are available */
    if (me == NULL || me->itsTimer == NULL || me->itsButton == NULL || me->itsMicrowaveEmitter == NULL) {
        printf("ButtonDriver: Missing required components\n");
        return;
    }

    /* Apply debounce delay */
    printf("ButtonDriver: Applying debounce delay of %d ms\n", DEBOUNCE_TIME);
    Timer_delay(me->itsTimer, DEBOUNCE_TIME);

    /* Check if button state has changed */
    int currentState = Button_getState(me->itsButton);
    if (currentState != me->oldState) {
        /* Update stored state with the new button state */
        me->oldState = currentState;
        printf("ButtonDriver: Button state changed to %s\n",
               currentState ? "PRESSED" : "RELEASED");

        /* Process button release events (when state is 0) */
        if (currentState == BUTTON_STATE_RELEASED) {
            /* Toggle the state and update related components */
            if (me->toggleOn) {
                /* Turn off */
                printf("ButtonDriver: Toggling OFF\n");
                me->toggleOn = BUTTON_OFF;
                Button_backlight(me->itsButton, BUTTON_OFF);
                MicrowaveEmitter_stopEmitting(me->itsMicrowaveEmitter);
            } else {
                /* Turn on */
                printf("ButtonDriver: Toggling ON\n");
                me->toggleOn = BUTTON_ON;
                Button_backlight(me->itsButton, BUTTON_ON);
                MicrowaveEmitter_startEmitting(me->itsMicrowaveEmitter);
            }
        }
    } else {
        printf("ButtonDriver: No change in button state\n");
    }
}

struct Button* ButtonDriver_getItsButton(const ButtonDriver* const me) {
    return (me != NULL) ? me->itsButton : NULL;
}

void ButtonDriver_setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    if (me != NULL) {
        if (p_Button != NULL) {
            Button_setItsButtonDriver(p_Button, me);
        }
        ButtonDriver_setItsButton1(me, p_Button);
    }
}

struct MicrowaveEmitter* ButtonDriver_getItsMicrowaveEmitter(const ButtonDriver* const me) {
    return (me != NULL) ? me->itsMicrowaveEmitter : NULL;
}

void ButtonDriver_setItsMicrowaveEmitter(ButtonDriver* const me, struct MicrowaveEmitter* p_MicrowaveEmitter) {
    if (me != NULL) {
        me->itsMicrowaveEmitter = p_MicrowaveEmitter;
    }
}

struct Timer* ButtonDriver_getItsTimer(const ButtonDriver* const me) {
    return (me != NULL) ? me->itsTimer : NULL;
}

void ButtonDriver_setItsTimer(ButtonDriver* const me, struct Timer* p_Timer) {
    if (me != NULL) {
        me->itsTimer = p_Timer;
    }
}

ButtonDriver* ButtonDriver_Create(void) {
    ButtonDriver* me = (ButtonDriver*)malloc(sizeof(ButtonDriver));
    if (me != NULL) {
        ButtonDriver_Init(me);
    }
    return me;
}

void ButtonDriver_Destroy(ButtonDriver* const me) {
    if (me != NULL) {
        ButtonDriver_Cleanup(me);
        free(me);
    }
}

static void cleanUpRelations(ButtonDriver* const me) {
    if (me == NULL) {
        return;
    }

    if (me->itsButton != NULL) {
        struct ButtonDriver* p_ButtonDriver = Button_getItsButtonDriver(me->itsButton);
        if (p_ButtonDriver == me) {
            Button_setItsButtonDriver(me->itsButton, NULL);
        }
        me->itsButton = NULL;
    }

    me->itsMicrowaveEmitter = NULL;
    me->itsTimer = NULL;
}

void ButtonDriver_setItsButton2(ButtonDriver* const me, struct Button* p_Button) {
    if (me != NULL) {
        me->itsButton = p_Button;
    }
}

void ButtonDriver_setItsButton1(ButtonDriver* const me, struct Button* p_Button) {
    if (me != NULL) {
        if (me->itsButton != NULL) {
            Button_setItsButtonDriver(me->itsButton, NULL);
        }
        ButtonDriver_setItsButton2(me, p_Button);
    }
}

void ButtonDriver_clearItsButton(ButtonDriver* const me) {
    if (me != NULL) {
        me->itsButton = NULL;
    }
}
