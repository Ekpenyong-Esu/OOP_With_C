/**
 * @file StateTablePattern.h
 * @brief Simple State Table Pattern for Learning
 * 
 * This is a SIMPLIFIED version of the state table pattern designed for learners.
 * We use direct function pointers instead of complex action wrappers to make
 * the code easier to understand and follow.
 */

#ifndef STATE_TABLE_STATETABLEPATTERN_H
#define STATE_TABLE_STATETABLEPATTERN_H

#include <stdio.h>
#include <stdlib.h>

// Boolean constants for clarity
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/**
 * @brief States in our number tokenizer
 * 
 * Think of these as different "modes" the tokenizer can be in:
 * - WAITING: Ready to start processing a new number
 * - WHOLE: Processing the integer part (e.g., "123" in "123.45")
 * - DECIMAL: Processing the fractional part (e.g., "45" in "123.45")
 */
typedef enum {
    STATE_WAITING,      // Waiting for input, no number being processed
    STATE_WHOLE,        // Processing whole number part (before decimal point)
    STATE_DECIMAL       // Processing decimal part (after decimal point)
} State;

/**
 * @brief Events that can happen while processing input
 * 
 * These represent the different types of characters we might encounter:
 */
typedef enum {
    EVENT_DIGIT,        // A number (0-9)
    EVENT_DOT,          // A decimal point (.)
    EVENT_SPACE,        // Whitespace (space, tab, etc.)
    EVENT_END           // End of input string
} Event;

// Forward declaration - we'll define this structure in TokenizerStateTable.h
struct NumberTokenizer;

/**
 * @brief Function pointer types for state actions
 * 
 * These are simpler than the original - just direct function pointers
 * that take the tokenizer and the current character as parameters.
 */
typedef void (*ActionFunction)(struct NumberTokenizer* tokenizer, char ch);

/**
 * @brief A single entry in our state transition table
 * 
 * This is much simpler than the original - just the new state and one action.
 * When an event happens in a state:
 * 1. Execute the action (if not NULL)
 * 2. Change to the new state
 */
typedef struct {
    State nextState;           // Which state to go to next
    ActionFunction action;     // What to do during this transition (can be NULL)
} StateTableEntry;

/**
 * @brief Helper function to convert character to digit
 * @param c Character to convert ('0' through '9')
 * @return Integer value (0 through 9), or -1 if not a digit
 * 
 * Example: digit('5') returns 5, digit('a') returns -1
 */
int char_to_digit(char c);

#endif // STATE_TABLE_STATETABLEPATTERN_H
