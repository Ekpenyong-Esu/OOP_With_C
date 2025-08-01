
#include "../TokenizeAsyncSinglePkg/TokenizeAsyncSinglePkg.h"
#include <stdio.h>
#include "../mutex/Mutex.h"

/**
 * Single Receptor Pattern Implementation:
 * This module implements a single receptor that processes events sequentially.
 * The receptor maintains state and processes one event at a time, ensuring
 * thread-safe operation through mutex synchronization.
 *
 * The "Single Receptor" pattern means:
 * - Only one instance processes events at a time
 * - Events are processed in order (FIFO)
 * - State is maintained between event processing
 * - Thread-safe through mutex protection
 */

// State machine for tokenizing numbers (whole and fractional parts)
typedef struct TokenizerSyncSingleReceptor {
    char ch;                // Current character being processed
    double result;          // Current result of tokenization
    TSTATETYPE stateID;     // Current state
    TSUBSTATETYPE subStateID;// Current substate
    double tensPlace;       // Place value for fractional part
    struct Mutex* itsMutex; // Mutex for thread safety (single receptor access)
} TokenizerSyncSingleReceptor;

// State transition and event handling functions
void TokenizerSyncSingleReceptor_enter_GotNumber(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_enter_NoNumber(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_enter_ProcessingWholePart(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_exit_GotNumber(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_exit_NoNumber(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_exit_ProcessingWholePart(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_Init(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_Cleanup(TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_eventDispatch(TokenizerSyncSingleReceptor* const receptor, Event event);
Mutex* TokenizerSyncSingleReceptor_getItsMutex(const TokenizerSyncSingleReceptor* const receptor);
void TokenizerSyncSingleReceptor_setItsMutex(TokenizerSyncSingleReceptor* const receptor, Mutex* mutex);
TokenizerSyncSingleReceptor* TokenizerSyncSingleReceptor_Create(void);
void TokenizerSyncSingleReceptor_Destroy(TokenizerSyncSingleReceptor* const receptor);
