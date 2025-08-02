//
// Created by mahon on 8/2/2025.
//

#include "State.h"
#include <stdio.h>

// Forward declaration for Context functions
struct Context;
void Context_setResult(struct Context* context, double result);
double Context_getResult(struct Context* context);
void Context_setState(struct Context* context, struct State* newState);
void Context_setFractionalDigits(struct Context* context, int digits);
int Context_getFractionalDigits(struct Context* context);

// Utility function implementation
int digit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;  // Invalid digit
}

// =============================================================================
// NoNumber State Implementation
// =============================================================================
static void noNumber_onDigit(struct Context* context, char digitChar) {
    printf("NoNumber: Starting new number with digit %c\n", digitChar);
    Context_setResult(context, (double)digit(digitChar));
    Context_setState(context, ProcessingWholeState);
}

static void noNumber_onDot(struct Context* context) {
    (void)context;  // Suppress unused parameter warning
    printf("NoNumber: Ignoring dot (no number started)\n");
    // Stay in NoNumber state - dots without preceding digits are ignored
}

static void noNumber_onWhiteSpace(struct Context* context) {
    (void)context;  // Suppress unused parameter warning
    printf("NoNumber: Ignoring whitespace\n");
    // Stay in NoNumber state
}

static void noNumber_onEndOfString(struct Context* context) {
    (void)context;  // Suppress unused parameter warning
    printf("NoNumber: End of string\n");
    // Stay in NoNumber state
}

static State noNumberState = {
    .onDigit = noNumber_onDigit,
    .onDot = noNumber_onDot,
    .onWhiteSpace = noNumber_onWhiteSpace,
    .onEndOfString = noNumber_onEndOfString,
    .name = "NoNumber"
};

// =============================================================================
// ProcessingWhole State Implementation  
// =============================================================================
static void processingWhole_onDigit(struct Context* context, char digitChar) {
    printf("ProcessingWhole: Adding digit %c\n", digitChar);
    double currentResult = Context_getResult(context);
    double newResult = currentResult * 10.0 + digit(digitChar);
    Context_setResult(context, newResult);
    // Stay in ProcessingWhole state
}

static void processingWhole_onDot(struct Context* context) {
    printf("ProcessingWhole: Starting fractional part\n");
    Context_setFractionalDigits(context, 0);
    Context_setState(context, ProcessingFractionState);
}

static void processingWhole_onWhiteSpace(struct Context* context) {
    printf("ProcessingWhole: Number complete (%.2f), resetting\n", Context_getResult(context));
    Context_setResult(context, 0.0);
    Context_setState(context, NoNumberState);
}

static void processingWhole_onEndOfString(struct Context* context) {
    printf("ProcessingWhole: End of string, number complete (%.2f)\n", Context_getResult(context));
    Context_setResult(context, 0.0);
    Context_setState(context, NoNumberState);
}

static State processingWholeState = {
    .onDigit = processingWhole_onDigit,
    .onDot = processingWhole_onDot,
    .onWhiteSpace = processingWhole_onWhiteSpace,
    .onEndOfString = processingWhole_onEndOfString,
    .name = "ProcessingWhole"
};

// =============================================================================
// ProcessingFraction State Implementation
// =============================================================================
static void processingFraction_onDigit(struct Context* context, char digitChar) {
    printf("ProcessingFraction: Adding fractional digit %c\n", digitChar);
    double currentResult = Context_getResult(context);
    int fractionalDigits = Context_getFractionalDigits(context);
    
    // Add fractional digit: result = result + digit / 10^(fractionalDigits+1)
    double fractionalValue = digit(digitChar);
    for (int i = 0; i <= fractionalDigits; i++) {
        fractionalValue /= 10.0;
    }
    
    Context_setResult(context, currentResult + fractionalValue);
    Context_setFractionalDigits(context, fractionalDigits + 1);
    // Stay in ProcessingFraction state
}

static void processingFraction_onDot(struct Context* context) {
    (void)context;  // Suppress unused parameter warning
    printf("ProcessingFraction: Ignoring extra dot\n");
    // Stay in ProcessingFraction state - ignore extra dots
}

static void processingFraction_onWhiteSpace(struct Context* context) {
    printf("ProcessingFraction: Number complete (%.6f), resetting\n", Context_getResult(context));
    Context_setResult(context, 0.0);
    Context_setState(context, NoNumberState);
}

static void processingFraction_onEndOfString(struct Context* context) {
    printf("ProcessingFraction: End of string, number complete (%.6f)\n", Context_getResult(context));
    Context_setResult(context, 0.0);
    Context_setState(context, NoNumberState);
}

static State processingFractionState = {
    .onDigit = processingFraction_onDigit,
    .onDot = processingFraction_onDot,
    .onWhiteSpace = processingFraction_onWhiteSpace,
    .onEndOfString = processingFraction_onEndOfString,
    .name = "ProcessingFraction"
};

// =============================================================================
// Public State Pointers
// =============================================================================
State* NoNumberState = &noNumberState;
State* ProcessingWholeState = &processingWholeState;
State* ProcessingFractionState = &processingFractionState;

// Initialize function (for future extensibility)
void States_Init(void) {
    printf("States initialized\n");
}
