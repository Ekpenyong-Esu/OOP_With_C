//
// TokenizerMultiReceptor Implementation
// Created by mahon on 1/27/2024.
//
// This file implements a finite state machine-based tokenizer that parses
// numeric values from input strings. The tokenizer can handle both integer
// and floating-point numbers, using mutex for thread-safe operation.
//

#include "MultiReceptor.h"
#include "../mutex/Mutex.h"
#include <stdlib.h>

// Forward declaration for internal cleanup function
static void cleanUpRelations(TokenizerMultiReceptor* const me);

/**
 * @brief Converts a character digit to its numeric value
 * @param c Character representing a digit ('0'-'9')
 * @return Integer value of the digit (0-9)
 * @note Assumes input is a valid digit character
 */
int digit(char c) {
    return c - '0';
}

/**
 * @brief Cleanup function for TokenizerMultiReceptor object
 * @param me Pointer to the TokenizerMultiReceptor instance
 * @note This function handles cleanup of relationships and resources
 */
void TokenizerMultiReceptor_Cleanup(TokenizerMultiReceptor* const me) {
    cleanUpRelations(me);
}

/**
 * @brief Processes a digit character event in the state machine
 * @param me Pointer to the TokenizerMultiReceptor instance
 * @param c The digit character to process ('0'-'9')
 * 
 * This function implements the state machine logic for processing digit characters.
 * It handles transitions between different states and updates the numeric result
 * accordingly. The function is thread-safe through mutex locking.
 * 
 * State transitions:
 * - NONUMBER_STATE -> GOTNUMBER_STATE (ProcessingWholePart substate)
 * - GOTNUMBER_STATE remains, but may switch between substates
 */
void TokenizerMultiReceptor_evDigit(TokenizerMultiReceptor* const me, char c) {
    // Acquire mutex lock for thread safety
    Mutex_lock(me->itsMutex);
    
    switch (me->stateID) {
        case NONUMBER_STATE:
            /* Transition from no number to processing a number */
            TokenizerMultiReceptor_exit_NoNumber(me);
            me->ch = c;  // Store the current character
            TokenizerMultiReceptor_enter_GotNumber(me);
            me->stateID = GOTNUMBER_STATE;
            TokenizerMultiReceptor_enter_ProcessingWholePart(me);
            me->subStateID = PROCESSINGWHOLEPART_SSTATE;
            printf("Current value of result: %g\n", me->result);
            break;
            
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    /* Continue processing whole number part */
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    me->ch = c;
                    TokenizerMultiReceptor_enter_ProcessingWholePart(me);
                    printf("Current value of result: %g\n", me->result);
                    break;
                    
                case PROCESSINGFRACTIONALPART_SSTATE:
                    /* Process fractional digits after decimal point */
                    TokenizerMultiReceptor_exit_ProcessingFractionalPart(me);
                    me->ch = c;
                    // Add fractional digit to result using current decimal place
                    me->result += digit(me->ch) / me->tensPlace;
                    me->tensPlace *= 10.0;  // Move to next decimal place
                    TokenizerMultiReceptor_enter_ProcessingFractionalPart(me);
                    printf("Current value of result: %g\n", me->result);
                    break;
                    
                case NULL_SSTATE:
                default:
                    /* Invalid substate - ignore the digit */
                    break;
            };
            break;
            
        case NULL_STATE:
        default:
            /* Invalid state - ignore the digit */
            break;
    };
    
    // Release mutex lock
    Mutex_release(me->itsMutex);
}

/**
 * @brief Processes a decimal point character event in the state machine
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * This function handles the decimal point ('.') character, which transitions
 * the parser to fractional number processing mode. It's thread-safe through
 * mutex locking.
 * 
 * State transitions:
 * - NONUMBER_STATE -> GOTNUMBER_STATE (ProcessingFractionalPart substate)
 * - GOTNUMBER_STATE: ProcessingWholePart -> ProcessingFractionalPart substate
 */
void TokenizerMultiReceptor_evDot(TokenizerMultiReceptor* const me) {
    // Acquire mutex lock for thread safety
    Mutex_lock(me->itsMutex);
    me->ch = '.';  // Store the decimal point character
    
    switch (me->stateID) {
        case NONUMBER_STATE:
            /* Start processing a fractional number (e.g., ".5") */
            TokenizerMultiReceptor_exit_NoNumber(me);
            TokenizerMultiReceptor_enter_GotNumber(me);
            me->stateID = GOTNUMBER_STATE;
            TokenizerMultiReceptor_enter_ProcessingFractionalPart(me);
            me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
            break;
            
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    /* Transition from whole part to fractional part */
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    TokenizerMultiReceptor_enter_ProcessingFractionalPart(me);
                    me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
                    break;
                    
                case PROCESSINGFRACTIONALPART_SSTATE:
                case NULL_SSTATE:
                default:
                    /* Already processing fractional part or invalid state - ignore */
                    break;
            };
            break;
            
        case NULL_STATE:
        default:
            /* Invalid state - ignore the decimal point */
            break;
    };
    
    // Release mutex lock
    Mutex_release(me->itsMutex);
}

/**
 * @brief Processes end-of-string event to finalize number parsing
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * This function is called when the end of input string is reached.
 * It finalizes the current number being processed and outputs the result.
 * Thread-safe through mutex locking.
 * 
 * State transitions:
 * - GOTNUMBER_STATE -> NONUMBER_STATE (resets for next number)
 */
void TokenizerMultiReceptor_evEndOfString(TokenizerMultiReceptor* const me) {
    // Acquire mutex lock for thread safety
    Mutex_lock(me->itsMutex);
    
    switch (me->stateID) {
        case GOTNUMBER_STATE:
            /* Finalize the current number being processed */
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    /* Exit from whole part processing */
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    break;
                    
                case PROCESSINGFRACTIONALPART_SSTATE:
                    /* Exit from fractional part processing */
                    TokenizerMultiReceptor_exit_ProcessingFractionalPart(me);
                    break;
                    
                case NULL_SSTATE:
                default:
                    /* Invalid substate - ignore */
                    break;
            };
            
            /* Complete number processing and output result */
            TokenizerMultiReceptor_exit_GotNumber(me);
            printf("Number: %g\n", me->result);
            TokenizerMultiReceptor_enter_NoNumber(me);
            me->stateID = NONUMBER_STATE;
            break;
            
        case NONUMBER_STATE:
        case NULL_STATE:
        default:
            /* No number being processed or invalid state - nothing to do */
            break;
    };
    
    // Release mutex lock
    Mutex_release(me->itsMutex);
}

/**
 * @brief Processes whitespace character event to separate numbers
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * This function handles whitespace characters (space, tab, newline) which
 * act as number separators in the input stream. When whitespace is encountered
 * during number processing, it finalizes the current number and prepares
 * for the next one. Thread-safe through mutex locking.
 * 
 * State transitions:
 * - GOTNUMBER_STATE -> NONUMBER_STATE (completes current number)
 */
void TokenizerMultiReceptor_evWhiteSpace(TokenizerMultiReceptor* const me) {
    // Acquire mutex lock for thread safety
    Mutex_lock(me->itsMutex);
    
    switch (me->stateID) {
        case GOTNUMBER_STATE:
            /* Complete the current number when whitespace is encountered */
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    /* Exit from whole part processing */
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    break;
                    
                case PROCESSINGFRACTIONALPART_SSTATE:
                    /* Exit from fractional part processing */
                    TokenizerMultiReceptor_exit_ProcessingFractionalPart(me);
                    break;
                    
                case NULL_SSTATE:
                default:
                    /* Invalid substate - ignore */
                    break;
            };
            
            /* Complete number processing and output result */
            TokenizerMultiReceptor_exit_GotNumber(me);
            printf("Number: %g\n", me->result);
            TokenizerMultiReceptor_enter_NoNumber(me);
            me->stateID = NONUMBER_STATE;
            break;
            
        case NONUMBER_STATE:
        case NULL_STATE:
        default:
            /* No number being processed or invalid state - whitespace is ignored */
            break;
    };
    
    // Release mutex lock
    Mutex_release(me->itsMutex);
}

/*
 * ============================================================================
 * STATE ENTRY AND EXIT ACTION FUNCTIONS
 * ============================================================================
 * These functions define the actions performed when entering or exiting
 * specific states and substates in the finite state machine.
 */

/**
 * @brief Entry action for GotNumber state
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Initializes decimal place tracking for fractional number processing.
 * This ensures proper decimal place calculation when processing digits
 * after a decimal point.
 */
void TokenizerMultiReceptor_enter_GotNumber(TokenizerMultiReceptor* const me) {
    me->tensPlace = 10.0;  // Initialize decimal place multiplier
}

/**
 * @brief Entry action for NoNumber state
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Resets the numeric result to zero, preparing for processing
 * a new number sequence.
 */
void TokenizerMultiReceptor_enter_NoNumber(TokenizerMultiReceptor* const me) {
    me->result = 0.0;  // Reset accumulated result
}

/**
 * @brief Entry action for ProcessingFractionalPart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Currently no specific action needed when entering fractional
 * part processing. Decimal place tracking is handled in GotNumber entry.
 */
void TokenizerMultiReceptor_enter_ProcessingFractionalPart(TokenizerMultiReceptor* const me) {
    // No specific action required for entering fractional part processing
    // The tensPlace is already initialized in enter_GotNumber
}

/**
 * @brief Entry action for ProcessingWholePart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Processes the current digit character and updates the numeric result
 * by shifting existing digits left and adding the new digit.
 * Formula: result = result * 10 + new_digit
 */
void TokenizerMultiReceptor_enter_ProcessingWholePart(TokenizerMultiReceptor* const me) {
    // Shift existing digits left and add new digit
    me->result = me->result * 10 + digit(me->ch);
}

/**
 * @brief Exit action for GotNumber state
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Resets the substate to NULL when exiting the number processing state.
 * This ensures clean state transitions.
 */
void TokenizerMultiReceptor_exit_GotNumber(TokenizerMultiReceptor* const me) {
    me->subStateID = NULL_SSTATE;  // Reset substate
}

/**
 * @brief Exit action for NoNumber state
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Currently no specific action needed when exiting the no-number state.
 */
void TokenizerMultiReceptor_exit_NoNumber(TokenizerMultiReceptor* const me) {
    // No specific action required for exiting no-number state
}

/**
 * @brief Exit action for ProcessingFractionalPart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Currently no specific action needed when exiting fractional
 * part processing substate.
 */
void TokenizerMultiReceptor_exit_ProcessingFractionalPart(TokenizerMultiReceptor* const me) {
    // No specific action required for exiting fractional part processing
}

/**
 * @brief Exit action for ProcessingWholePart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * Currently no specific action needed when exiting whole
 * part processing substate.
 */
void TokenizerMultiReceptor_exit_ProcessingWholePart(TokenizerMultiReceptor* const me) {
    // No specific action required for exiting whole part processing
}

/*
 * ============================================================================
 * OBJECT LIFECYCLE MANAGEMENT FUNCTIONS
 * ============================================================================
 * These functions handle creation, initialization, and destruction of
 * TokenizerMultiReceptor objects following object-oriented patterns in C.
 */

/**
 * @brief Factory function to create a new TokenizerMultiReceptor instance
 * @return Pointer to newly created and initialized TokenizerMultiReceptor, 
 *         or NULL if allocation fails
 * 
 * This function allocates memory for a new TokenizerMultiReceptor object
 * and initializes it with default values. It follows the factory pattern
 * commonly used in object-oriented C programming.
 */
TokenizerMultiReceptor * TokenizerMultiReceptor_Create(void) {
    // Allocate memory for the new instance
    TokenizerMultiReceptor* me = (TokenizerMultiReceptor *) malloc(sizeof(TokenizerMultiReceptor));
    
    // Initialize the object if allocation succeeded
    if(me != NULL)
        TokenizerMultiReceptor_Init(me);
        
    return me;
}

/**
 * @brief Destructor function to clean up and deallocate TokenizerMultiReceptor
 * @param me Pointer to the TokenizerMultiReceptor instance to destroy
 * 
 * This function performs cleanup operations and deallocates the memory
 * used by the TokenizerMultiReceptor object. It's safe to call with NULL.
 */
void TokenizerMultiReceptor_Destroy(TokenizerMultiReceptor* const me) {
    if(me != NULL) {
        TokenizerMultiReceptor_Cleanup(me);  // Clean up resources
    }
    free(me);  // Deallocate memory (free() handles NULL safely)
}

/**
 * @brief Initialize a TokenizerMultiReceptor instance with default values
 * @param me Pointer to the TokenizerMultiReceptor instance to initialize
 * 
 * This function sets up the initial state of a TokenizerMultiReceptor object.
 * It can be used with both heap-allocated (via Create) and stack-allocated
 * instances.
 */
void TokenizerMultiReceptor_Init(TokenizerMultiReceptor* const me) {
    // Initialize character storage
    me->ch = 'x';  // Default placeholder character
    
    // Initialize numeric processing variables
    me->result = 0.0;       // Start with zero result
    me->tensPlace = 10.0;   // Decimal place multiplier
    
    // Initialize mutex pointer (will be set later via setter)
    me->itsMutex = NULL;

    // Initialize finite state machine variables
    me->stateID = NONUMBER_STATE;     // Start in no-number state
    me->subStateID = NULL_SSTATE;     // No substate initially
}

/*
 * ============================================================================
 * MUTEX ACCESSOR FUNCTIONS
 * ============================================================================
 * These functions provide safe access to the mutex member variable,
 * following encapsulation principles of object-oriented programming.
 */

/**
 * @brief Getter function for the mutex member
 * @param me Pointer to the TokenizerMultiReceptor instance
 * @return Pointer to the associated Mutex object, or NULL if none set
 * 
 * This function provides read-only access to the mutex object associated
 * with the TokenizerMultiReceptor. The return type is cast to maintain
 * proper type safety.
 */
struct Mutex* TokenizerMultiReceptor_getItsMutex(const TokenizerMultiReceptor* const me) {
    return (struct Mutex*)me->itsMutex;
}

/**
 * @brief Setter function for the mutex member
 * @param me Pointer to the TokenizerMultiReceptor instance
 * @param p_Mutex Pointer to the Mutex object to associate
 * 
 * This function sets the mutex object that will be used for thread
 * synchronization during state machine operations. The mutex should
 * be properly initialized before being set.
 */
void TokenizerMultiReceptor_setItsMutex(TokenizerMultiReceptor* const me, struct Mutex* p_Mutex) {
    me->itsMutex = p_Mutex;
}

/*
 * ============================================================================
 * INTERNAL HELPER FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Internal function to clean up object relationships
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * This static function handles cleanup of any relationships this object
 * has with other objects. Currently, it safely nullifies the mutex pointer
 * without destroying the mutex itself (as it may be shared or managed
 * externally).
 */
static void cleanUpRelations(TokenizerMultiReceptor* const me) {
    if(me->itsMutex != NULL) {
        me->itsMutex = NULL;  // Remove reference without destroying the mutex
    }
}