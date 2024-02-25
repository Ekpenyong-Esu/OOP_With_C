//
// Created by mahon on 2/3/2024.
//

#ifndef ANDSTATE_LIGHT_H
#define ANDSTATE_LIGHT_H

#include "LightPkg.h"

typedef struct Light Light;
struct Light
{

};

void Light_Init(Light* const me);
void Light_Cleanup(Light* const me);
Light * Light_Create(void);
void Light_Destroy(Light* const me);


void Light_turnOn(Light* const me);
void Light_turnOff(Light* const me);
void Light_setColor(Light* const me, ColorType color);
void Light_setMode(Light* const me, FlashType mode);

#endif //ANDSTATE_LIGHT_H
