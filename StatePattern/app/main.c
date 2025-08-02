/**
 * @file main.c
 * @brief Demo of State Pattern Design Pattern for Learning
 * 
 * This demo shows how the state pattern works using the classic GoF approach.
 * Perfect for understanding the core concepts of object-oriented state machines in C.
 * 
 * KEY LEARNING CONCEPTS:
 * 1. State Pattern = Each state is a separate object/class
 * 2. Context = Holds current state and delegates to it
 * 3. State Interface = Common interface for all states
 * 4. Transitions = States change themselves via the context
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/Context/Context.h"
#include "../src/State/State.h"
#include "../src/mutex/Mutex.h"

/**
 * @brief Simple demonstration of the state pattern
 * @param input_string The string to process
 */
void demonstrate_state_pattern(const char* input_string) {
    printf("=====================================\n");
    printf("STATE PATTERN DESIGN PATTERN DEMO\n");
    printf("=====================================\n");
    printf("Input: \"%s\"\n", input_string);
    printf("-------------------------------------\n");
    
    // Initialize states first
    States_Init();
    
    // Create a context (the main state machine)
    Context* context = Context_Create();
    if (context == NULL) {
        printf("Error: Could not create context\n");
        return;
    }
    
    // Create and set a mutex for thread safety
    Mutex mutex;
    if (Mutex_init(&mutex) != 0) {
        printf("Error: Could not initialize mutex\n");
        Context_Destroy(context);
        return;
    }
    Context_setMutex(context, &mutex);
    
    // Show initial state
    printf("Initial state: %s\n", Context_getState(context)->name);
    printf("-------------------------------------\n");
    
    // Process the string character by character
    for (const char* ptr = input_string; *ptr != '\0'; ptr++) {
        char ch = *ptr;
        printf("Processing '%c': ", ch);
        
        if (ch >= '0' && ch <= '9') {
            printf("digit -> ");
            Context_processDigit(context, ch);
        } else if (ch == '.') {
            printf("dot -> ");
            Context_processDot(context);
        } else if (ch == ' ' || ch == '\t') {
            printf("whitespace -> ");
            Context_processWhiteSpace(context);
        } else {
            printf("other -> ");
            Context_processWhiteSpace(context);  // Treat as whitespace
        }
        
        printf("State: %s, Result: %.6f\n", 
               Context_getState(context)->name, 
               Context_getResult(context));
    }
    
    // Process end of string
    printf("Processing end of string -> ");
    Context_processEndOfString(context);
    printf("State: %s, Result: %.6f\n", 
           Context_getState(context)->name, 
           Context_getResult(context));
    
    // Show final state
    printf("-------------------------------------\n");
    printf("Final state: %s\n", Context_getState(context)->name);
    printf("Final result: %.6f\n", Context_getResult(context));
    printf("=====================================\n\n");
    
    // Cleanup
    Context_Destroy(context);
    Mutex_destroy(&mutex);
}

/**
 * @brief Show how the state pattern works step by step
 */
void show_state_pattern_structure(void) {
    printf("==========================================\n");
    printf("HOW THE STATE PATTERN WORKS\n");
    printf("==========================================\n");
    printf("The state pattern uses separate objects for each state:\n");
    printf("  Context holds current state and delegates to it\n\n");
    
    printf("States in our number parser:\n");
    printf("  NoNumberState: Ready for input\n");
    printf("  ProcessingWholeState: Processing integer part\n");
    printf("  ProcessingFractionState: Processing decimal part\n\n");
    
    printf("Events (input types):\n");
    printf("  processDigit: Numbers 0-9\n");
    printf("  processDot:   Decimal point (.)\n");
    printf("  processWhiteSpace: Whitespace\n");
    printf("  processEndOfString: End of input\n\n");
    
    printf("How it works:\n");
    printf("  1. Context receives event\n");
    printf("  2. Context delegates to current state object\n");
    printf("  3. State object handles event and may change context state\n");
    printf("  4. Each state knows what to do for each event\n");
    printf("==========================================\n\n");
}

/**
 * @brief Test multiple input cases to show different transitions
 */
void run_test_cases(void) {
    printf("==========================================\n");
    printf("TESTING DIFFERENT INPUT CASES\n");
    printf("==========================================\n");
    
    const char* test_cases[] = {
        "123",         // Simple integer
        "45.67",       // Simple decimal
        "0.5",         // Decimal starting with 0
        ".75",         // Decimal starting with dot
        "12 34",       // Two numbers
        "1.2 3.4",     // Two decimals
        "100.001",     // Number with many decimal places
        NULL           // End marker
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("Test %d: ", i + 1);
        demonstrate_state_pattern(test_cases[i]);
    }
}

/**
 * @brief Interactive demo - let user type input
 */
void interactive_demo(void) {
    char input[100];
    
    printf("==========================================\n");
    printf("INTERACTIVE STATE PATTERN DEMO\n");
    printf("==========================================\n");
    printf("Type numbers to see the state machine work!\n");
    printf("Try: integers, decimals, multiple numbers\n");
    printf("Type 'quit' to exit\n");
    printf("------------------------------------------\n");
    
    // Initialize states
    States_Init();
    
    // Create a persistent context for the interactive session
    Context* context = Context_Create();
    if (context == NULL) {
        printf("Error: Could not create context\n");
        return;
    }
    
    Mutex mutex;
    if (Mutex_init(&mutex) == 0) {
        Context_setMutex(context, &mutex);
    }
    
    while (1) {
        printf("Enter input: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = '\0';
        
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        printf("Processing: \"%s\"\n", input);
        Context_processString(context, input);
        printf("Current state: %s\n", Context_getState(context)->name);
        printf("------------------------------------------\n");
    }
    
    // Cleanup
    Context_Destroy(context);
    Mutex_destroy(&mutex);
    printf("Thanks for trying the state pattern demo!\n");
}

/**
 * @brief Show the advantages of using the state pattern
 */
void explain_advantages(void) {
    printf("==========================================\n");
    printf("WHY USE STATE PATTERN?\n");
    printf("==========================================\n");
    printf("ADVANTAGES:\n");
    printf("1. CLEAN: Each state is a separate, focused object\n");
    printf("2. EXTENSIBLE: Easy to add new states without changing existing ones\n");
    printf("3. MAINTAINABLE: State-specific behavior is encapsulated\n");
    printf("4. DEBUGGABLE: Can easily see which state is active\n");
    printf("5. FLEXIBLE: States can maintain their own data\n");
    printf("6. REUSABLE: State objects can be reused across contexts\n\n");
    
    printf("COMPARE TO ALTERNATIVES:\n");
    printf("- Nested if/else: Gets messy with many states\n");
    printf("- Switch statements: Hard to extend, violates open/closed principle\n");
    printf("- State flags: Logic scattered, hard to maintain\n\n");
    
    printf("STATE PATTERN IS:\n");
    printf("- Object-oriented (each state is an object)\n");
    printf("- Easy to understand and modify\n");
    printf("- Perfect for parsers, protocols, user interfaces\n");
    printf("==========================================\n\n");
}

/**
 * @brief Main function - run all demos
 */
int main(void) {
    printf("STATE PATTERN DESIGN PATTERN - LEARNING DEMO\n");
    printf("============================================\n\n");
    
    // Initialize the state pattern implementation
    States_Init();
    
    // Show how the pattern works
    explain_advantages();
    show_state_pattern_structure();
    
    // Run automated tests
    run_test_cases();
    
    // Interactive demo
    interactive_demo();
    
    printf("Demo completed! You now understand the state pattern.\n");
    return 0;
}
