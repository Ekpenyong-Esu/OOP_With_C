//
// Created by mahon on 1/8/2024.
//

#include "MicrowaveEmitter.h"
#include <stdio.h>
#include <stdlib.h>

void MicrowaveEmitter_Init(MicrowaveEmitter* const me){
    // me->
}
void MicrowaveEmitter_Cleanup(MicrowaveEmitter* const me){

}

MicrowaveEmitter* MicrowaveEmitter_Create(void){
    MicrowaveEmitter* me = (MicrowaveEmitter*)malloc(sizeof(MicrowaveEmitter));
    if (me != NULL)
    {
        MicrowaveEmitter_Init(me);
    }
    return me;
}

void MicrowaveEmitter_Destroy(MicrowaveEmitter* const me){
    if (me != NULL)
    {
        MicrowaveEmitter_Cleanup(me);
    }
    free(me);
}

void MicrowaveEmitter_startEmitting(MicrowaveEmitter* const me){
    printf("call MicrowaveEmitter_startEmitting\n");
}
void MicrowaveEmitter_stopEmitting(MicrowaveEmitter* const me){
    printf("call MicrowaveEmitter_stopEmitting\n");
}