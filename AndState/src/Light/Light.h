//
// Created by mahon on 2/3/2024.
//
// Simple Light implementation demonstrating the AND Pattern
// The Light has TWO concurrent (AND) aspects:
// 1. Color state (RED, YELLOW, GREEN)  
// 2. Flash mode (STEADY, SLOWLY, QUICKLY)
// These run independently and simultaneously

#ifndef ANDSTATE_LIGHT_H
#define ANDSTATE_LIGHT_H

#include "LightPkg.h"
#include <stdbool.h>

typedef struct Light Light;
struct Light
{
    // Basic light state
    bool isOn;          // Is the light turned on?
    
    // AND Pattern: Two concurrent aspects that operate independently
    ColorType color;    // Current color (RED, YELLOW, GREEN)
    FlashType mode;     // Current flash mode (STEADY, SLOWLY, QUICKLY)
};

// Constructor/Destructor pattern
void Light_Init(Light* const me);
void Light_Cleanup(Light* const me);
Light* Light_Create(void);
void Light_Destroy(Light* const me);

// Basic operations
void Light_turnOn(Light* const me);
void Light_turnOff(Light* const me);

// AND Pattern operations - these can be set independently
void Light_setColor(Light* const me, ColorType color);
void Light_setMode(Light* const me, FlashType mode);

// Utility functions for demonstration
void Light_displayStatus(Light* const me);
bool Light_isOn(Light* const me);
ColorType Light_getColor(Light* const me);
FlashType Light_getMode(Light* const me);

#endif //ANDSTATE_LIGHT_H
