/**
 * @file TokenizerStateTable.h
 * @brief SIMPLIFIED Number Tokenizer using State Table Pattern
 * 
 * This is a learning-focused implementation that demonstrates the state table
 * pattern in its simplest form. The tokenizer can parse numbers like:
 * - "123" (integer)
 * - "123.45" (decimal)
 * - "0.75" (decimal starting with zero)
 * 
 * KEY LEARNING CONCEPTS:
 * 1. State Table: 2D array where table[current_state][event] = what_to_do
 * 2. States: Different "modes" the parser can be in
 * 3. Events: Different types of input characters
 * 4. Actions: What to do when transitioning between states
 */

#ifndef STATE_TABLE_TOKENIZERSTATETABLE_H
#define STATE_TABLE_TOKENIZERSTATETABLE_H

#include "StateTablePattern.h"

/**
 * @brief The main structure for our number tokenizer
 * 
 * This is much simpler than the original version - we store just the
 * essential data needed to parse numbers.
 */
typedef struct NumberTokenizer {
    // Current state of the tokenizer
    State currentState;
    
    // The number we're building up as we parse
    double result;
    
    // For decimal numbers: tracks which decimal place we're at
    // (10.0 for first decimal place, 100.0 for second, etc.)
    double decimalPlace;
    
    // The 2D state transition table
    // Usage: stateTable[currentState][event] tells us what to do
    StateTableEntry stateTable[3][4];  // 3 states × 4 events
} NumberTokenizer;

// === CONSTRUCTION AND DESTRUCTION ===
/**
 * @brief Create and initialize a new tokenizer
 * @return Pointer to new tokenizer, or NULL if creation failed
 */
NumberTokenizer* create_tokenizer(void);

/**
 * @brief Clean up and destroy a tokenizer
 * @param tokenizer The tokenizer to destroy (can be NULL)
 */
void destroy_tokenizer(NumberTokenizer* tokenizer);

// === MAIN PROCESSING FUNCTION ===
/**
 * @brief Process a single character through the state machine
 * @param tokenizer The tokenizer to use
 * @param ch The character to process
 * 
 * This is the heart of the state table pattern - it looks up what to do
 * based on the current state and the input character.
 */
void process_character(NumberTokenizer* tokenizer, char ch);

/**
 * @brief Process an entire string of characters
 * @param tokenizer The tokenizer to use
 * @param input The string to process
 * 
 * This is a convenience function that calls process_character for each
 * character in the string, plus sends an "end of string" event.
 */
void process_string(NumberTokenizer* tokenizer, const char* input);

// === SIMPLE ACTION FUNCTIONS ===
// These are the functions that get called when state transitions happen.
// They're much simpler than the original version - just regular functions
// that take a tokenizer and a character.

/**
 * @brief Start processing a new number (first digit)
 */
void action_start_number(NumberTokenizer* tokenizer, char ch);

/**
 * @brief Add another digit to the whole number part
 */
void action_add_digit(NumberTokenizer* tokenizer, char ch);

/**
 * @brief Start processing the decimal part
 */
void action_start_decimal(NumberTokenizer* tokenizer, char ch);

/**
 * @brief Add a digit to the decimal part
 */
void action_add_decimal_digit(NumberTokenizer* tokenizer, char ch);

/**
 * @brief Finish processing current number and print it
 */
void action_finish_number(NumberTokenizer* tokenizer, char ch);

/**
 * @brief Reset to start processing a new number
 */
void action_reset(NumberTokenizer* tokenizer, char ch);

// === UTILITY FUNCTIONS ===
/**
 * @brief Get a string representation of the current state
 * @param state The state to convert
 * @return Human-readable string
 */
const char* state_to_string(State state);

/**
 * @brief Get a string representation of an event
 * @param event The event to convert  
 * @return Human-readable string
 */
const char* event_to_string(Event event);

/**
 * @brief Print the current state of the tokenizer (for debugging)
 * @param tokenizer The tokenizer to examine
 */
void print_tokenizer_state(NumberTokenizer* tokenizer);

#endif // STATE_TABLE_TOKENIZERSTATETABLE_H
