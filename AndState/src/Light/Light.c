//
// Created by mahon on 2/3/2024.
//
// Simple Light implementation demonstrating the AND Pattern
// This shows how two aspects (color and flash mode) can operate independently

#include "Light.h"
#include <stdlib.h>
#include <stdio.h>

// Helper function to convert enum to string for display
static const char* colorToString(ColorType color) {
    switch(color) {
        case RED: return "RED";
        case YELLOW: return "YELLOW";
        case GREEN: return "GREEN";
        default: return "UNKNOWN";
    }
}

static const char* modeToString(FlashType mode) {
    switch(mode) {
        case STEADY: return "STEADY";
        case SLOWLY: return "SLOWLY";
        case QUICKLY: return "QUICKLY";
        default: return "UNKNOWN";
    }
}

// Constructor/Destructor pattern implementation
void Light_Init(Light* const me) {
    if (me == NULL) return;
    
    // Initialize to safe defaults
    me->isOn = false;
    me->color = RED;        // Default color
    me->mode = STEADY;      // Default mode
    
    printf("Light initialized: OFF, RED, STEADY\n");
}

void Light_Cleanup(Light* const me) {
    if (me == NULL) return;
    
    // Turn off light during cleanup
    me->isOn = false;
    printf("Light cleaned up\n");
}

Light* Light_Create(void) {
    Light* me = (Light*)malloc(sizeof(Light));
    if (me != NULL) {
        Light_Init(me);
    }
    return me;
}

void Light_Destroy(Light* const me) {
    if (me != NULL) {
        Light_Cleanup(me);
        free(me);
    }
}

// Basic operations
void Light_turnOn(Light* const me) {
    if (me == NULL) return;
    
    me->isOn = true;
    printf("Light turned ON - Color: %s, Mode: %s\n", 
           colorToString(me->color), modeToString(me->mode));
}

void Light_turnOff(Light* const me) {
    if (me == NULL) return;
    
    me->isOn = false;
    printf("Light turned OFF\n");
}

// AND Pattern operations - these can be changed independently!
// This demonstrates the key concept: Color and Mode are orthogonal (independent)
void Light_setColor(Light* const me, ColorType color) {
    if (me == NULL) return;
    
    me->color = color;
    printf("Light color changed to: %s", colorToString(color));
    
    if (me->isOn) {
        printf(" (Mode: %s)\n", modeToString(me->mode));
    } else {
        printf(" (Light is OFF)\n");
    }
}

void Light_setMode(Light* const me, FlashType mode) {
    if (me == NULL) return;
    
    me->mode = mode;
    printf("Light mode changed to: %s", modeToString(mode));
    
    if (me->isOn) {
        printf(" (Color: %s)\n", colorToString(me->color));
    } else {
        printf(" (Light is OFF)\n");
    }
}

// Utility functions
void Light_displayStatus(Light* const me) {
    if (me == NULL) {
        printf("Light: NULL pointer\n");
        return;
    }
    
    printf("Light Status: %s", me->isOn ? "ON" : "OFF");
    if (me->isOn) {
        printf(" | Color: %s | Mode: %s\n", 
               colorToString(me->color), modeToString(me->mode));
    } else {
        printf(" | (Color: %s, Mode: %s - when turned on)\n", 
               colorToString(me->color), modeToString(me->mode));
    }
}

bool Light_isOn(Light* const me) {
    return (me != NULL) ? me->isOn : false;
}

ColorType Light_getColor(Light* const me) {
    return (me != NULL) ? me->color : RED;
}

FlashType Light_getMode(Light* const me) {
    return (me != NULL) ? me->mode : STEADY;
}
