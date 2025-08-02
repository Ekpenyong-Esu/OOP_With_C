//
// Created by mahon on 8/2/2025.
//

#include "Context.h"
#include "../State/State.h"
#include "../mutex/Mutex.h"
#include <stdio.h>
#include <stdlib.h>

// Context implementation
Context* Context_Create(void) {
    Context* context = malloc(sizeof(Context));
    if (context == NULL) {
        return NULL;
    }
    
    context->currentState = NoNumberState;
    context->result = 0.0;
    context->fractionalDigits = 0;
    context->mutex = NULL;
    
    printf("Context created, starting in %s state\n", context->currentState->name);
    return context;
}

void Context_Destroy(Context* context) {
    if (context != NULL) {
        printf("Context destroyed\n");
        free(context);
    }
}

// State management
void Context_setState(Context* context, struct State* newState) {
    if (context == NULL || newState == NULL) return;
    
    printf("State transition: %s -> %s\n", 
           context->currentState->name, newState->name);
    context->currentState = newState;
}

struct State* Context_getState(Context* context) {
    return (context != NULL) ? context->currentState : NULL;
}

// Result management
void Context_setResult(Context* context, double result) {
    if (context != NULL) {
        context->result = result;
    }
}

double Context_getResult(Context* context) {
    return (context != NULL) ? context->result : 0.0;
}

// Fractional digits management
void Context_setFractionalDigits(Context* context, int digits) {
    if (context != NULL) {
        context->fractionalDigits = digits;
    }
}

int Context_getFractionalDigits(Context* context) {
    return (context != NULL) ? context->fractionalDigits : 0;
}

// Mutex management
void Context_setMutex(Context* context, struct Mutex* mutex) {
    if (context != NULL) {
        context->mutex = mutex;
    }
}

// Event processing - delegate to current state
void Context_processDigit(Context* context, char digit) {
    if (context == NULL || context->currentState == NULL) return;
    
    if (context->mutex != NULL) {
        Mutex_lock(context->mutex);
    }
    
    context->currentState->onDigit(context, digit);
    
    if (context->mutex != NULL) {
        Mutex_release(context->mutex);
    }
}

void Context_processDot(Context* context) {
    if (context == NULL || context->currentState == NULL) return;
    
    if (context->mutex != NULL) {
        Mutex_lock(context->mutex);
    }
    
    context->currentState->onDot(context);
    
    if (context->mutex != NULL) {
        Mutex_release(context->mutex);
    }
}

void Context_processWhiteSpace(Context* context) {
    if (context == NULL || context->currentState == NULL) return;
    
    if (context->mutex != NULL) {
        Mutex_lock(context->mutex);
    }
    
    context->currentState->onWhiteSpace(context);
    
    if (context->mutex != NULL) {
        Mutex_release(context->mutex);
    }
}

void Context_processEndOfString(Context* context) {
    if (context == NULL || context->currentState == NULL) return;
    
    if (context->mutex != NULL) {
        Mutex_lock(context->mutex);
    }
    
    context->currentState->onEndOfString(context);
    
    if (context->mutex != NULL) {
        Mutex_release(context->mutex);
    }
}

// Convenience function to process a string
void Context_processString(Context* context, const char* str) {
    if (context == NULL || str == NULL) return;
    
    printf("Processing string: \"%s\"\n", str);
    
    for (const char* ptr = str; *ptr != '\0'; ptr++) {
        char ch = *ptr;
        
        if (ch >= '0' && ch <= '9') {
            Context_processDigit(context, ch);
        } else if (ch == '.') {
            Context_processDot(context);
        } else if (ch == ' ' || ch == '\t' || ch == '\n') {
            Context_processWhiteSpace(context);
        } else {
            // Treat other characters as whitespace
            Context_processWhiteSpace(context);
        }
    }
    
    // Process end of string
    Context_processEndOfString(context);
    printf("String processing complete\n\n");
}
