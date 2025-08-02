//
// Created by mahon on 8/2/2025.
//

#ifndef STATEPATTERN_STATE_H
#define STATEPATTERN_STATE_H

// Forward declarations
struct Context;

// State interface - all states implement these functions
typedef struct State {
    void (*onDigit)(struct Context* context, char digit);
    void (*onDot)(struct Context* context);
    void (*onWhiteSpace)(struct Context* context);
    void (*onEndOfString)(struct Context* context);
    const char* name;  // For debugging
} State;

// Utility function
int digit(char c);  // converts '0'-'9' to 0-9

// State instances (singletons)
extern State* NoNumberState;
extern State* ProcessingWholeState;
extern State* ProcessingFractionState;

// Initialize all states
void States_Init(void);

#endif //STATEPATTERN_STATE_H
