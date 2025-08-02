/**
 * @file TokenizerStateTable.c
 * @brief SIMPLIFIED Implementation of State Table Pattern for Number Tokenization
 * 
 * This implementation is designed for learning - it's much simpler than the
 * original version but demonstrates the core concepts clearly.
 * 
 * KEY LEARNING POINTS:
 * 1. The state table is just a 2D array of structs
 * 2. Each entry tells us: next state + what action to take
 * 3. Processing input is just: look up table entry, call action, change state
 * 4. No complex memory management or function pointer gymnastics
 */

#include "TokenizerStateTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === HELPER FUNCTIONS ===

/**
 * @brief Convert a character to an event type
 * @param ch The character to classify
 * @return The corresponding event type
 */
static Event char_to_event(char ch) {
    if (ch >= '0' && ch <= '9') {
        return EVENT_DIGIT;
    } else if (ch == '.') {
        return EVENT_DOT;
    } else if (ch == ' ' || ch == '\t' || ch == '\n') {
        return EVENT_SPACE;
    } else if (ch == '\0') {
        return EVENT_END;
    } else {
        return EVENT_SPACE; // Treat unknown chars as whitespace
    }
}

/**
 * @brief Initialize the state transition table
 * @param tokenizer The tokenizer whose table to initialize
 * 
 * This is where we define the "rules" of our state machine.
 * Reading this table should tell you exactly how the tokenizer behaves.
 */
static void setup_state_table(NumberTokenizer* tokenizer) {
    StateTableEntry* table = &tokenizer->stateTable[0][0];
    
    // Clear the entire table first
    memset(table, 0, sizeof(tokenizer->stateTable));
    
    // === STATE_WAITING transitions ===
    
    // WAITING + DIGIT → start a new number
    tokenizer->stateTable[STATE_WAITING][EVENT_DIGIT].nextState = STATE_WHOLE;
    tokenizer->stateTable[STATE_WAITING][EVENT_DIGIT].action = action_start_number;
    
    // WAITING + DOT → start a decimal number (like ".5")
    tokenizer->stateTable[STATE_WAITING][EVENT_DOT].nextState = STATE_DECIMAL;
    tokenizer->stateTable[STATE_WAITING][EVENT_DOT].action = action_start_decimal;
    
    // WAITING + SPACE → stay waiting (ignore whitespace)
    tokenizer->stateTable[STATE_WAITING][EVENT_SPACE].nextState = STATE_WAITING;
    tokenizer->stateTable[STATE_WAITING][EVENT_SPACE].action = NULL; // No action needed
    
    // WAITING + END → stay waiting (nothing to do)
    tokenizer->stateTable[STATE_WAITING][EVENT_END].nextState = STATE_WAITING;
    tokenizer->stateTable[STATE_WAITING][EVENT_END].action = NULL;
    
    // === STATE_WHOLE transitions ===
    
    // WHOLE + DIGIT → add another digit to whole part
    tokenizer->stateTable[STATE_WHOLE][EVENT_DIGIT].nextState = STATE_WHOLE;
    tokenizer->stateTable[STATE_WHOLE][EVENT_DIGIT].action = action_add_digit;
    
    // WHOLE + DOT → start decimal part
    tokenizer->stateTable[STATE_WHOLE][EVENT_DOT].nextState = STATE_DECIMAL;
    tokenizer->stateTable[STATE_WHOLE][EVENT_DOT].action = action_start_decimal;
    
    // WHOLE + SPACE → finish number, go back to waiting
    tokenizer->stateTable[STATE_WHOLE][EVENT_SPACE].nextState = STATE_WAITING;
    tokenizer->stateTable[STATE_WHOLE][EVENT_SPACE].action = action_finish_number;
    
    // WHOLE + END → finish number, go back to waiting
    tokenizer->stateTable[STATE_WHOLE][EVENT_END].nextState = STATE_WAITING;
    tokenizer->stateTable[STATE_WHOLE][EVENT_END].action = action_finish_number;
    
    // === STATE_DECIMAL transitions ===
    
    // DECIMAL + DIGIT → add digit to decimal part
    tokenizer->stateTable[STATE_DECIMAL][EVENT_DIGIT].nextState = STATE_DECIMAL;
    tokenizer->stateTable[STATE_DECIMAL][EVENT_DIGIT].action = action_add_decimal_digit;
    
    // DECIMAL + DOT → error! Can't have two dots (treat as space)
    tokenizer->stateTable[STATE_DECIMAL][EVENT_DOT].nextState = STATE_WAITING;
    tokenizer->stateTable[STATE_DECIMAL][EVENT_DOT].action = action_finish_number;
    
    // DECIMAL + SPACE → finish number, go back to waiting
    tokenizer->stateTable[STATE_DECIMAL][EVENT_SPACE].nextState = STATE_WAITING;
    tokenizer->stateTable[STATE_DECIMAL][EVENT_SPACE].action = action_finish_number;
    
    // DECIMAL + END → finish number, go back to waiting
    tokenizer->stateTable[STATE_DECIMAL][EVENT_END].nextState = STATE_WAITING;
    tokenizer->stateTable[STATE_DECIMAL][EVENT_END].action = action_finish_number;
}

// === CONSTRUCTION AND DESTRUCTION ===

NumberTokenizer* create_tokenizer(void) {
    NumberTokenizer* tokenizer = malloc(sizeof(NumberTokenizer));
    if (tokenizer == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Initialize the tokenizer state
    tokenizer->currentState = STATE_WAITING;
    tokenizer->result = 0.0;
    tokenizer->decimalPlace = 10.0;
    
    // Set up the state transition table
    setup_state_table(tokenizer);
    
    return tokenizer;
}

void destroy_tokenizer(NumberTokenizer* tokenizer) {
    if (tokenizer != NULL) {
        free(tokenizer);
    }
}

// === MAIN PROCESSING FUNCTIONS ===

void process_character(NumberTokenizer* tokenizer, char ch) {
    if (tokenizer == NULL) {
        return;
    }
    
    // Convert character to event
    Event event = char_to_event(ch);
    
    // Look up what to do in the state table
    StateTableEntry* entry = &tokenizer->stateTable[tokenizer->currentState][event];
    
    // Debug output (can be removed for production)
    printf("State: %s, Event: %s ('%c') -> ", 
           state_to_string(tokenizer->currentState), 
           event_to_string(event), 
           ch == '\0' ? '0' : ch);
    
    // Execute the action if there is one
    if (entry->action != NULL) {
        entry->action(tokenizer, ch);
    }
    
    // Change to the new state
    tokenizer->currentState = entry->nextState;
    
    // Debug output continued
    printf("Next State: %s\n", state_to_string(tokenizer->currentState));
}

void process_string(NumberTokenizer* tokenizer, const char* input) {
    if (tokenizer == NULL || input == NULL) {
        return;
    }
    
    printf("Processing string: \"%s\"\n", input);
    
    // Process each character
    for (const char* ptr = input; *ptr != '\0'; ptr++) {
        process_character(tokenizer, *ptr);
    }
    
    // Send end-of-string event
    process_character(tokenizer, '\0');
    
    printf("String processing complete.\n\n");
}

// === ACTION FUNCTIONS ===
// These are the functions that actually DO things when state transitions happen.
// They're much simpler than the original version.

void action_start_number(NumberTokenizer* tokenizer, char ch) {
    int digit = char_to_digit(ch);
    if (digit >= 0) {
        tokenizer->result = (double)digit;
        tokenizer->decimalPlace = 10.0; // Reset for potential decimal part
        printf("Started new number: %g", tokenizer->result);
    }
}

void action_add_digit(NumberTokenizer* tokenizer, char ch) {
    int digit = char_to_digit(ch);
    if (digit >= 0) {
        tokenizer->result = tokenizer->result * 10.0 + digit;
        printf("Added digit, number now: %g", tokenizer->result);
    }
}

void action_start_decimal(NumberTokenizer* tokenizer, char ch) {
    (void)ch; // Suppress unused parameter warning
    tokenizer->decimalPlace = 10.0; // Start decimal part
    printf("Started decimal part");
}

void action_add_decimal_digit(NumberTokenizer* tokenizer, char ch) {
    int digit = char_to_digit(ch);
    if (digit >= 0) {
        tokenizer->result += digit / tokenizer->decimalPlace;
        tokenizer->decimalPlace *= 10.0;
        printf("Added decimal digit, number now: %g", tokenizer->result);
    }
}

void action_finish_number(NumberTokenizer* tokenizer, char ch) {
    (void)ch; // Suppress unused parameter warning
    printf("FINISHED NUMBER: %g", tokenizer->result);
    // Reset for next number
    tokenizer->result = 0.0;
    tokenizer->decimalPlace = 10.0;
}

void action_reset(NumberTokenizer* tokenizer, char ch) {
    (void)ch; // Suppress unused parameter warning
    tokenizer->result = 0.0;
    tokenizer->decimalPlace = 10.0;
    printf("Reset tokenizer");
}

// === UTILITY FUNCTIONS ===

const char* state_to_string(State state) {
    switch (state) {
        case STATE_WAITING: return "WAITING";
        case STATE_WHOLE:   return "WHOLE";
        case STATE_DECIMAL: return "DECIMAL";
        default:            return "UNKNOWN";
    }
}

const char* event_to_string(Event event) {
    switch (event) {
        case EVENT_DIGIT: return "DIGIT";
        case EVENT_DOT:   return "DOT";
        case EVENT_SPACE: return "SPACE";
        case EVENT_END:   return "END";
        default:          return "UNKNOWN";
    }
}

void print_tokenizer_state(NumberTokenizer* tokenizer) {
    if (tokenizer == NULL) {
        printf("Tokenizer is NULL\n");
        return;
    }
    
    printf("=== TOKENIZER STATE ===\n");
    printf("Current State: %s\n", state_to_string(tokenizer->currentState));
    printf("Current Result: %g\n", tokenizer->result);
    printf("Decimal Place: %g\n", tokenizer->decimalPlace);
    printf("=====================\n");
}
