
#include <stddef.h>
#include <stdlib.h>
#include "TSRSyncSingleReceptor.h"

// Enter GotNumber state: initialize tens place for fractional part
void TokenizerSyncSingleReceptor_enter_GotNumber(TokenizerSyncSingleReceptor* const receptor) {
    receptor->tensPlace = TENS_PLACE_INITIAL;
}

// Enter NoNumber state: reset result
void TokenizerSyncSingleReceptor_enter_NoNumber(TokenizerSyncSingleReceptor* const receptor) {
    receptor->result = 0.0;
}

// Enter ProcessingFractionalPart substate (no-op)
void TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const receptor) {
    // No specific action needed
}

// Enter ProcessingWholePart substate: update result with digit
void TokenizerSyncSingleReceptor_enter_ProcessingWholePart(TokenizerSyncSingleReceptor* const receptor) {
    receptor->result = receptor->result * DIGIT_BASE + digit(receptor->ch);
}

// Exit GotNumber state: reset substate
void TokenizerSyncSingleReceptor_exit_GotNumber(TokenizerSyncSingleReceptor* const receptor) {
    receptor->subStateID = NULL_SSTATE;
}

// Exit NoNumber state (no-op)
void TokenizerSyncSingleReceptor_exit_NoNumber(TokenizerSyncSingleReceptor* const receptor) {
    // No specific action needed
}

// Exit ProcessingFractionalPart substate (no-op)
void TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const receptor) {
    // No specific action needed
}

// Exit ProcessingWholePart substate (no-op)
void TokenizerSyncSingleReceptor_exit_ProcessingWholePart(TokenizerSyncSingleReceptor* const receptor) {
    // No specific action needed
}

// Initialize the state machine
void TokenizerSyncSingleReceptor_Init(TokenizerSyncSingleReceptor* const receptor) {
    if (receptor == NULL) {
        return; // Fail gracefully if receptor is null
    }
    receptor->ch = '\0';  // Initialize to null character instead of 'x'
    receptor->result = 0.0;
    receptor->tensPlace = TENS_PLACE_INITIAL;
    receptor->itsMutex = NULL;
    receptor->stateID = NONUMBER_STATE;
    receptor->subStateID = NULL_SSTATE;
}

// Dispatch an event to the state machine
// Handles digit, dot, whitespace, and end-of-string events
void TokenizerSyncSingleReceptor_eventDispatch(TokenizerSyncSingleReceptor* const receptor, Event event) {
    if (receptor == NULL) {
        return; // Fail gracefully if receptor is null
    }

    Mutex_lock(receptor->itsMutex);
    switch (event.eType) {
        case EVDIGIT:
            // Handle digit input
            switch (receptor->stateID) {
                case NONUMBER_STATE:
                    // No number yet, start new number
                    TokenizerSyncSingleReceptor_exit_NoNumber(receptor);
                    receptor->ch = event.ed.c;
                    TokenizerSyncSingleReceptor_enter_GotNumber(receptor);
                    receptor->stateID = GOTNUMBER_STATE;
                    TokenizerSyncSingleReceptor_enter_ProcessingWholePart(receptor);
                    receptor->subStateID = PROCESSINGWHOLEPART_SSTATE;
                    printf("Current value of result: %g\n", receptor->result);
                    break;
                case GOTNUMBER_STATE:
                    // Already processing a number
                    switch (receptor->subStateID) {
                        case PROCESSINGWHOLEPART_SSTATE:
                            // Add digit to whole part
                            TokenizerSyncSingleReceptor_exit_ProcessingWholePart(receptor);
                            receptor->ch = event.ed.c;
                            TokenizerSyncSingleReceptor_enter_ProcessingWholePart(receptor);
                            printf("Current value of result: %g\n", receptor->result);
                            break;
                        case PROCESSINGFRACTIONALPART_SSTATE:
                            // Add digit to fractional part
                            TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(receptor);
                            receptor->ch = event.ed.c;
                            receptor->result += digit(receptor->ch) / receptor->tensPlace;
                            receptor->tensPlace *= TENS_PLACE_INITIAL;
                            TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(receptor);
                            printf("Current value of result: %g\n", receptor->result);
                            break;
                        case NULL_SSTATE:
                            // No substate, ignore
                            break;
                    }
                    break;
                case NULL_STATE:
                    // Handle NULL_STATE if needed
                    break;
            }
            break;
        case EVDOT:
            // Handle dot input (start fractional part)
            receptor->ch = '.';
            switch (receptor->stateID) {
                case NONUMBER_STATE:
                    // No number yet, start new number as fractional
                    TokenizerSyncSingleReceptor_exit_NoNumber(receptor);
                    TokenizerSyncSingleReceptor_enter_GotNumber(receptor);
                    receptor->stateID = GOTNUMBER_STATE;
                    TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(receptor);
                    receptor->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
                    break;
                case GOTNUMBER_STATE:
                    // Already processing a number
                    switch (receptor->subStateID) {
                        case PROCESSINGWHOLEPART_SSTATE:
                            // Transition to fractional part
                            TokenizerSyncSingleReceptor_exit_ProcessingWholePart(receptor);
                            TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(receptor);
                            receptor->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
                            break;
                        case NULL_SSTATE:
                            // No substate, ignore
                            break;
                        case PROCESSINGFRACTIONALPART_SSTATE:
                            // Already processing fractional part, ignore dot
                            break;
                    }
                    break;
                case NULL_STATE:
                    // Handle NULL_STATE if needed
                    break;
            }
            break;
        case EVWHITESPACE:
        case EVENDOFSTRING:
            // Handle whitespace or end of string (finalize number)
            switch (receptor->stateID) {
                case GOTNUMBER_STATE:
                    switch (receptor->subStateID) {
                        case PROCESSINGWHOLEPART_SSTATE:
                            TokenizerSyncSingleReceptor_exit_ProcessingWholePart(receptor);
                            break;
                        case PROCESSINGFRACTIONALPART_SSTATE:
                            TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(receptor);
                            break;
                        case NULL_SSTATE:
                            // No substate, ignore
                            break;
                    }
                    TokenizerSyncSingleReceptor_exit_GotNumber(receptor);
                    printf("Number: %g\n", receptor->result);
                    TokenizerSyncSingleReceptor_enter_NoNumber(receptor);
                    receptor->stateID = NONUMBER_STATE;
                    break;
                case NONUMBER_STATE:
                    // No action needed
                    break;
                case NULL_STATE:
                    // Handle NULL_STATE if needed
                    break;
            }
            break;
    }
    Mutex_release(receptor->itsMutex);
}

// Get the mutex associated with the state machine
struct Mutex* TokenizerSyncSingleReceptor_getItsMutex(const TokenizerSyncSingleReceptor* const receptor) {
    return receptor->itsMutex;
}

// Set the mutex for the state machine
void TokenizerSyncSingleReceptor_setItsMutex(TokenizerSyncSingleReceptor* const receptor, struct Mutex* mutex) {
    receptor->itsMutex = mutex;
}

// Create a new state machine instance
TokenizerSyncSingleReceptor* TokenizerSyncSingleReceptor_Create(void) {
    TokenizerSyncSingleReceptor* receptor = (TokenizerSyncSingleReceptor*) malloc(sizeof(TokenizerSyncSingleReceptor));
    if (receptor != NULL) {
        TokenizerSyncSingleReceptor_Init(receptor);
    }
    return receptor;
}

// Destroy a state machine instance
void TokenizerSyncSingleReceptor_Destroy(TokenizerSyncSingleReceptor* const receptor) {
    if (receptor != NULL) {
        TokenizerSyncSingleReceptor_Cleanup(receptor);
        free(receptor);
    }
}

// Internal helper to clean up relations (mutex pointer)
static void cleanUpRelations(TokenizerSyncSingleReceptor* const receptor) {
    if (receptor->itsMutex != NULL) {
        receptor->itsMutex = NULL;
    }
}

// Cleanup the state machine
void TokenizerSyncSingleReceptor_Cleanup(TokenizerSyncSingleReceptor* const receptor) {
    cleanUpRelations(receptor);
}
