// main.c - Demonstrates Single Receptor Pattern with Tokenizer
//
// Single Receptor Pattern:
// - Only one receptor instance processes events
// - Events are processed sequentially (one at a time)
// - State is maintained between event processing
// - Thread-safe through mutex synchronization
//
#include <stdio.h>
#include "../src/mutex/Mutex.h"
#include "../src/TSREventQueue/TSREventQueue.h"
#include "../src/TSRSyncSingleReceptor/TSRSyncSingleReceptor.h"
#include "../src/TokenizeAsyncSinglePkg/TokenizeAsyncSinglePkg.h"

void demonstrate_single_receptor_pattern(const char* input_string) {
    printf("=== Single Receptor Pattern Demo ===\n");
    printf("Processing string: \"%s\"\n\n", input_string);

    // Create and initialize mutex for single receptor access
    Mutex mutex;

    // Create and initialize event queue
    TSREventQueue eventQueue;
    TSREventQueue_Init(&eventQueue);
    TSREventQueue_setItsMutex(&eventQueue, &mutex);

    // Create and initialize the SINGLE receptor (this is the key pattern)
    TokenizerSyncSingleReceptor* receptor = TokenizerSyncSingleReceptor_Create();
    TokenizerSyncSingleReceptor_setItsMutex(receptor, &mutex);

    printf("Step 1: Converting input to events and posting to queue\n");
    // Convert input string to events and post to queue
    for (const char* ptr = input_string; *ptr; ++ptr) {
        Event event;
        if (*ptr >= '0' && *ptr <= '9') {
            event.eType = EVDIGIT;
            event.ed.c = *ptr;
            printf("  Posted DIGIT event: '%c'\n", *ptr);
        } else if (*ptr == '.') {
            event.eType = EVDOT;
            event.ed.c = *ptr;
            printf("  Posted DOT event: '%c'\n", *ptr);
        } else if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') {
            event.eType = EVWHITESPACE;
            event.ed.c = *ptr;
            printf("  Posted WHITESPACE event\n");
        } else {
            event.eType = EVENDOFSTRING;
            event.ed.c = *ptr;
            printf("  Posted END_OF_STRING event\n");
        }
        TSREventQueue_post(&eventQueue, event);
    }

    // Add final end of string event
    Event end_event = {EVENDOFSTRING, {'\0'}};
    TSREventQueue_post(&eventQueue, end_event);
    printf("  Posted final END_OF_STRING event\n\n");

    printf("Step 2: Single receptor processing events sequentially\n");
    // Process events from the queue using the SINGLE receptor
    while (!TSREventQueue_isEmpty(&eventQueue)) {
        Event event = TSREventQueue_pull(&eventQueue);
        printf("  Processing event type: %d\n", event.eType);
        TokenizerSyncSingleReceptor_eventDispatch(receptor, event);
    }

    // Clean up
    TokenizerSyncSingleReceptor_Destroy(receptor);
    printf("\nSingle Receptor Pattern demonstration complete.\n");
    printf("===========================================\n\n");
}

int main() {
    printf("Single Receptor Pattern Educational Demo\n");
    printf("TSR = Tokenizer Sync Receptor\n\n");

    // Demonstrate with multiple test cases
    demonstrate_single_receptor_pattern("123.45");
    demonstrate_single_receptor_pattern("0.75");
    demonstrate_single_receptor_pattern("42");

    printf("All demonstrations complete.\n");
    return 0;
}
