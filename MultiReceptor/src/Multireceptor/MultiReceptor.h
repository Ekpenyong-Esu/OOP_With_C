//
// TokenizerMultiReceptor Header File
// Created by mahon on 1/27/2024.
//
// This header defines a finite state machine-based tokenizer for parsing
// numeric values from input strings. The tokenizer supports both integer
// and floating-point numbers and provides thread-safe operation through
// mutex synchronization.
//
// Design Pattern: State Machine with Object-Oriented C
// Thread Safety: Provided through POSIX mutex integration
//

#ifndef MULTIRECEPTOR_MULTIRECEPTOR_H
#define MULTIRECEPTOR_MULTIRECEPTOR_H

#include <stdio.h>

// Forward declaration for Mutex structure (defined in Mutex.h)
struct Mutex;

/*
 * ============================================================================
 * STATE MACHINE ENUMERATIONS
 * ============================================================================
 */

/**
 * @brief Main state enumeration for the tokenizer state machine
 * 
 * This enumeration defines the primary states of the number parsing
 * finite state machine:
 * - NULL_STATE: Invalid/uninitialized state
 * - NONUMBER_STATE: Not currently processing any number
 * - GOTNUMBER_STATE: Currently processing a number (has substates)
 */
typedef enum TSTATETYPE {
    NULL_STATE,        // Invalid or uninitialized state
    NONUMBER_STATE,    // Ready to receive first digit of a new number
    GOTNUMBER_STATE    // Currently processing a number (with substates)
} TSTATETYPE;

/**
 * @brief Substate enumeration for number processing details
 * 
 * This enumeration defines the substates used within GOTNUMBER_STATE
 * to track whether we're processing the whole or fractional part:
 * - NULL_SSTATE: Invalid/no substate
 * - PROCESSINGWHOLEPART_SSTATE: Processing digits before decimal point
 * - PROCESSINGFRACTIONALPART_SSTATE: Processing digits after decimal point
 */
typedef enum TSUBSTATETYPE {
    NULL_SSTATE,                    // Invalid or no substate
    PROCESSINGWHOLEPART_SSTATE,     // Processing integer part of number
    PROCESSINGFRACTIONALPART_SSTATE // Processing fractional part of number
} TSUBSTATETYPE;

/*
 * ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Converts a character digit to its numeric value
 * @param c Character representing a digit ('0'-'9')
 * @return Integer value of the digit (0-9)
 * @note This function assumes the input is a valid digit character
 */
int digit(char c);

/*
 * ============================================================================
 * MAIN STRUCTURE DEFINITION
 * ============================================================================
 */

// Forward declaration of the main structure
typedef struct TokenizerMultiReceptor TokenizerMultiReceptor;

/**
 * @brief Main tokenizer structure implementing the state machine
 * 
 * This structure contains all the data needed for the tokenizer state machine:
 * - Character processing: Current character being processed
 * - Numeric accumulation: Current result and decimal place tracking
 * - State management: Current state and substate of the finite state machine
 * - Thread safety: Mutex for synchronized access in multi-threaded environments
 */
struct TokenizerMultiReceptor {
    char ch;                    // Current character being processed
    double result;              // Accumulated numeric result
    TSTATETYPE stateID;         // Current main state of the state machine
    TSUBSTATETYPE subStateID;   // Current substate (when in GOTNUMBER_STATE)
    double tensPlace;           // Decimal place multiplier for fractional processing
    struct Mutex* itsMutex;     // Mutex for thread-safe operation
};

/*
 * ============================================================================
 * OBJECT LIFECYCLE FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Factory function to create and initialize a new TokenizerMultiReceptor
 * @return Pointer to newly created TokenizerMultiReceptor, or NULL if allocation fails
 */
TokenizerMultiReceptor * TokenizerMultiReceptor_Create(void);

/**
 * @brief Destructor function to clean up and deallocate a TokenizerMultiReceptor
 * @param me Pointer to the TokenizerMultiReceptor instance to destroy
 */
void TokenizerMultiReceptor_Destroy(TokenizerMultiReceptor* const me);

/**
 * @brief Initialize a TokenizerMultiReceptor instance with default values
 * @param me Pointer to the TokenizerMultiReceptor instance to initialize
 */
void TokenizerMultiReceptor_Init(TokenizerMultiReceptor* const me);

/**
 * @brief Cleanup function for TokenizerMultiReceptor resources
 * @param me Pointer to the TokenizerMultiReceptor instance to clean up
 */
void TokenizerMultiReceptor_Cleanup(TokenizerMultiReceptor* const me);

/*
 * ============================================================================
 * EVENT PROCESSING FUNCTIONS (STATE MACHINE OPERATIONS)
 * ============================================================================
 */

/**
 * @brief Process a digit character event
 * @param me Pointer to the TokenizerMultiReceptor instance
 * @param c The digit character to process ('0'-'9')
 * 
 * This function processes digit characters and updates the numeric result
 * according to the current state of the finite state machine.
 */
void TokenizerMultiReceptor_evDigit(TokenizerMultiReceptor* const me, char c);

/**
 * @brief Process a decimal point character event
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * This function handles decimal point characters, transitioning the state
 * machine to fractional number processing mode.
 */
void TokenizerMultiReceptor_evDot(TokenizerMultiReceptor* const me);

/**
 * @brief Process end-of-string event
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * This function finalizes processing of the current number when the end
 * of the input string is reached.
 */
void TokenizerMultiReceptor_evEndOfString(TokenizerMultiReceptor* const me);

/**
 * @brief Process whitespace character event
 * @param me Pointer to the TokenizerMultiReceptor instance
 * 
 * This function handles whitespace characters which act as number separators,
 * finalizing the current number and preparing for the next one.
 */
void TokenizerMultiReceptor_evWhiteSpace(TokenizerMultiReceptor* const me);

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
 */
void TokenizerMultiReceptor_enter_GotNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Entry action for NoNumber state
 * @param me Pointer to the TokenizerMultiReceptor instance
 */
void TokenizerMultiReceptor_enter_NoNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Entry action for ProcessingFractionalPart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 */
void TokenizerMultiReceptor_enter_ProcessingFractionalPart(TokenizerMultiReceptor* const me);

/**
 * @brief Entry action for ProcessingWholePart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 */
void TokenizerMultiReceptor_enter_ProcessingWholePart(TokenizerMultiReceptor* const me);

/**
 * @brief Exit action for GotNumber state
 * @param me Pointer to the TokenizerMultiReceptor instance
 */
void TokenizerMultiReceptor_exit_GotNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Exit action for NoNumber state
 * @param me Pointer to the TokenizerMultiReceptor instance
 */
void TokenizerMultiReceptor_exit_NoNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Exit action for ProcessingFractionalPart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 */
void TokenizerMultiReceptor_exit_ProcessingFractionalPart(TokenizerMultiReceptor* const me);

/**
 * @brief Exit action for ProcessingWholePart substate
 * @param me Pointer to the TokenizerMultiReceptor instance
 */
void TokenizerMultiReceptor_exit_ProcessingWholePart(TokenizerMultiReceptor* const me);

/*
 * ============================================================================
 * ACCESSOR FUNCTIONS (GETTERS AND SETTERS)
 * ============================================================================
 */

/**
 * @brief Getter function for the mutex member
 * @param me Pointer to the TokenizerMultiReceptor instance
 * @return Pointer to the associated Mutex object, or NULL if none set
 */
struct Mutex* TokenizerMultiReceptor_getItsMutex(const TokenizerMultiReceptor* const me);

/**
 * @brief Setter function for the mutex member
 * @param me Pointer to the TokenizerMultiReceptor instance
 * @param p_Mutex Pointer to the Mutex object to associate
 */
void TokenizerMultiReceptor_setItsMutex(TokenizerMultiReceptor* const me, struct Mutex* p_Mutex);

#endif //MULTIRECEPTOR_MULTIRECEPTOR_H
