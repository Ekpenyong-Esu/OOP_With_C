
#define DIGIT_BASE 10.0 // Base for digit conversion (decimal)
#define TENS_PLACE_INITIAL 10.0 // Initial value for tens place in fractional part
#ifndef TokenizeAsyncSingle_H
#define TokenizeAsyncSingle_H

// Size of the event queue
#define QSIZE 100

// Event types for the tokenizer state machine
typedef enum EventType {
    EVDIGIT,        // Digit character event
    EVDOT,          // Dot ('.') event
    EVWHITESPACE,   // Whitespace event
    EVENDOFSTRING   // End of string event
} EventType;

// Event structure holding type and associated data
typedef struct {
    EventType eType; // Type of event
    union eventData {
        char c;      // Character data for the event
    } ed;
} Event;

// State types for the tokenizer
typedef enum TSTATETYPE {
    NULL_STATE,      // No state
    NONUMBER_STATE,  // Not currently parsing a number
    GOTNUMBER_STATE  // Currently parsing a number
} TSTATETYPE;

// Substate types for the tokenizer
typedef enum TSUBSTATETYPE {
    NULL_SSTATE,                 // No substate
    PROCESSINGWHOLEPART_SSTATE,  // Processing whole part of number
    PROCESSINGFRACTIONALPART_SSTATE // Processing fractional part of number
} TSUBSTATETYPE;

// Helper function: returns the digit value of a character ('0'-'9')
int digit(char character);

// OS signal and wait functions for task synchronization (to be implemented)
void postSignal(void);
void waitOnSignal(void);

#endif
