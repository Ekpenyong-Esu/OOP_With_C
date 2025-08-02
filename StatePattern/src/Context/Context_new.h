//
// Created by mahon on 8/2/2025.
//

#ifndef STATEPATTERN_CONTEXT_H
#define STATEPATTERN_CONTEXT_H

// Forward declarations
struct State;
struct Mutex;

// Context - the main controller of the state machine
typedef struct Context {
    struct State* currentState;
    double result;
    int fractionalDigits;    // Count of digits after decimal point
    struct Mutex* mutex;     // For thread safety (optional)
} Context;

// Context lifecycle
Context* Context_Create(void);
void Context_Destroy(Context* context);

// Context operations
void Context_setState(Context* context, struct State* newState);
struct State* Context_getState(Context* context);

void Context_setResult(Context* context, double result);
double Context_getResult(Context* context);

void Context_setFractionalDigits(Context* context, int digits);
int Context_getFractionalDigits(Context* context);

void Context_setMutex(Context* context, struct Mutex* mutex);

// Event processing
void Context_processDigit(Context* context, char digit);
void Context_processDot(Context* context);
void Context_processWhiteSpace(Context* context);
void Context_processEndOfString(Context* context);

// Convenience function to process a string
void Context_processString(Context* context, const char* str);

#endif //STATEPATTERN_CONTEXT_H
