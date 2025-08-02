/**
 * @file main.c
 * @brief SIMPLIFIED Demo of State Table Pattern for Learning
 * 
 * This demo shows how the state table pattern works in its simplest form.
 * Perfect for understanding the core concepts without getting lost in complexity.
 * 
 * KEY LEARNING CONCEPTS:
 * 1. State Table = 2D array where table[state][event] = what_to_do
 * 2. Processing = look up table entry, call action, change state
 * 3. Actions = simple functions that update the tokenizer
 * 4. Clean separation between "what to do" and "when to do it"
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/StateTable/StateTablePattern.h"
#include "../src/TokenizerStateTable/TokenizerStateTable.h"

/**
 * @brief Simple demonstration of the state table pattern
 * @param input_string The string to process
 */
void demonstrate_simple_parsing(const char* input_string) {
    printf("=====================================\n");
    printf("SIMPLE STATE TABLE PATTERN DEMO\n");
    printf("=====================================\n");
    printf("Input: \"%s\"\n", input_string);
    printf("-------------------------------------\n");
    
    // Create a tokenizer
    NumberTokenizer* tokenizer = create_tokenizer();
    if (tokenizer == NULL) {
        printf("Error: Could not create tokenizer\n");
        return;
    }
    
    // Show initial state
    printf("Initial state: %s\n", state_to_string(tokenizer->currentState));
    printf("-------------------------------------\n");
    
    // Process the string
    process_string(tokenizer, input_string);
    
    // Show final state
    printf("-------------------------------------\n");
    printf("Final state: %s\n", state_to_string(tokenizer->currentState));
    printf("=====================================\n\n");
    
    // Cleanup
    destroy_tokenizer(tokenizer);
}

/**
 * @brief Show how the state table works step by step
 */
void show_state_table_structure(void) {
    printf("==========================================\n");
    printf("HOW THE STATE TABLE WORKS\n");
    printf("==========================================\n");
    printf("The state table is a 2D array:\n");
    printf("  table[current_state][input_event] = {next_state, action}\n\n");
    
    printf("States in our tokenizer:\n");
    printf("  WAITING: Ready for input\n");
    printf("  WHOLE:   Processing integer part\n");
    printf("  DECIMAL: Processing fractional part\n\n");
    
    printf("Events (input types):\n");
    printf("  DIGIT: Numbers 0-9\n");
    printf("  DOT:   Decimal point (.)\n");
    printf("  SPACE: Whitespace\n");
    printf("  END:   End of input\n\n");
    
    printf("Example transitions:\n");
    printf("  WAITING + DIGIT → WHOLE (start new number)\n");
    printf("  WHOLE + DIGIT → WHOLE (add to number)\n");
    printf("  WHOLE + DOT → DECIMAL (start decimal part)\n");
    printf("  DECIMAL + DIGIT → DECIMAL (add decimal digit)\n");
    printf("  WHOLE + SPACE → WAITING (finish number)\n");
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
        demonstrate_simple_parsing(test_cases[i]);
    }
}

/**
 * @brief Interactive demo - let user type input
 */
void interactive_demo(void) {
    char input[100];
    
    printf("==========================================\n");
    printf("INTERACTIVE STATE TABLE DEMO\n");
    printf("==========================================\n");
    printf("Type numbers to see the state machine work!\n");
    printf("Try: integers, decimals, multiple numbers\n");
    printf("Type 'quit' to exit\n");
    printf("------------------------------------------\n");
    
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
        
        demonstrate_simple_parsing(input);
    }
    
    printf("Thanks for trying the state table demo!\n");
}

/**
 * @brief Show the advantages of using a state table
 */
void explain_advantages(void) {
    printf("==========================================\n");
    printf("WHY USE STATE TABLE PATTERN?\n");
    printf("==========================================\n");
    printf("ADVANTAGES:\n");
    printf("1. VISUAL: You can SEE all transitions in the table\n");
    printf("2. SIMPLE: Just look up table[state][event]\n");
    printf("3. MAINTAINABLE: Easy to add new states/events\n");
    printf("4. DEBUGGABLE: Can print current state anytime\n");
    printf("5. FAST: Direct table lookup, no nested if/switch\n");
    printf("6. SCALABLE: Table grows linearly with complexity\n\n");
    
    printf("COMPARE TO ALTERNATIVES:\n");
    printf("- Nested if/else: Gets messy with many states\n");
    printf("- Switch statements: Hard to see all transitions\n");
    printf("- Function pointers everywhere: Confusing\n\n");
    
    printf("STATE TABLE PATTERN IS:\n");
    printf("- Data-driven (table defines behavior)\n");
    printf("- Easy to understand and modify\n");
    printf("- Perfect for parsers, protocols, user interfaces\n");
    printf("==========================================\n\n");
}

/**
 * @brief Main function - run all demos
 */
int main(void) {
    printf("STATE TABLE PATTERN - LEARNING DEMO\n");
    printf("===================================\n\n");
    
    // Show how the pattern works
    explain_advantages();
    show_state_table_structure();
    
    // Run automated tests
    run_test_cases();
    
    // Interactive demo
    interactive_demo();
    
    printf("Demo completed! You now understand state table patterns.\n");
    return 0;
}
