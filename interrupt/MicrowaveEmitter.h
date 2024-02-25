//
// Created by mahon on 1/8/2024.
//

#ifndef BUTTON_DEBOUNCE_MICROWAVEEMITTER_H
#define BUTTON_DEBOUNCE_MICROWAVEEMITTER_H


#include <stdio.h>
#include <stdlib.h>

typedef struct MicrowaveEmitter MicrowaveEmitter;
struct MicrowaveEmitter
{
    int deviceState;
};

void MicrowaveEmitter_Init(MicrowaveEmitter* const me);
void MicrowaveEmitter_Cleanup(MicrowaveEmitter* const me);

MicrowaveEmitter* MicrowaveEmitter_Create();
void MicrowaveEmitter_Destroy(MicrowaveEmitter* const me);

void MicrowaveEmitter_startEmitting(MicrowaveEmitter* const me);
void MicrowaveEmitter_stopEmitting(MicrowaveEmitter* const me);

#endif //BUTTON_DEBOUNCE_MICROWAVEEMITTER_H
