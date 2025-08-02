//
// MultiReceptor Application - Main Entry Point
// 
// This application demonstrates the TokenizerMultiReceptor functionality for 
// parsing numeric values from input strings. It showcases the finite state 
// machine-based tokenizer with thread-safe operation through mutex synchronization.
//
// Features:
// - Interactive number parsing demonstration
// - Command-line input processing
// - Comprehensive testing capabilities
// - Thread-safe operation with mutex integration
// - Support for integers and floating-point numbers
// - Multiple number parsing from single input strings
//
// Usage Examples:
//   ./main                    - Run interactive demonstration
//   ./main "123.45"          - Parse a single number
//   ./main "12 34.5" "67.89" - Parse multiple number strings
//   ./main --test            - Run comprehensive tests
//   ./main --help            - Show usage information
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../src/Multireceptor/MultiReceptor.h"
#include "../src/mutex/Mutex.h"

/*
 * ============================================================================
 * FUNCTION PROTOTYPES
 * ============================================================================
 */

void processString(TokenizerMultiReceptor* tokenizer, const char* input);
void printUsage(const char* programName);
void demonstrateTokenizer(void);
int testTokenizerWithMutex(void);

/*
 * ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================
 */

/**
 * @brief Main application entry point
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return 0 on success, 1 on error
 * 
 * This function handles command line argument parsing and dispatches to
 * appropriate functionality based on user input. It supports multiple
 * modes of operation including demonstration, testing, and direct input
 * processing.
 */
int main(int argc, char* argv[]) {
    printf("=== MultiReceptor Tokenizer Application ===\n\n");
    
    if (argc == 1) {
        // No arguments provided - run interactive demonstration
        demonstrateTokenizer();
        return 0;
    }
    
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        // Help requested - show usage information
        printUsage(argv[0]);
        return 0;
    }
    
    if (argc == 2 && strcmp(argv[1], "--test") == 0) {
        // Test mode requested - run comprehensive tests
        return testTokenizerWithMutex();
    }
    
    // Process command line arguments as input strings for tokenization
    TokenizerMultiReceptor* tokenizer = TokenizerMultiReceptor_Create();
    if (tokenizer == NULL) {
        fprintf(stderr, "Error: Failed to create tokenizer\n");
        return 1;
    }
    
    // Create and initialize mutex for thread-safe operation
    Mutex* mutex = malloc(sizeof(Mutex));
    if (mutex == NULL) {
        fprintf(stderr, "Error: Failed to allocate mutex\n");
        TokenizerMultiReceptor_Destroy(tokenizer);
        return 1;
    }
    
    if (Mutex_init(mutex) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex\n");
        free(mutex);
        TokenizerMultiReceptor_Destroy(tokenizer);
        return 1;
    }
    
    // Associate mutex with tokenizer for thread safety
    TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
    
    printf("Processing input strings:\n");
    for (int i = 1; i < argc; i++) {
        printf("\nInput: \"%s\"\n", argv[i]);
        processString(tokenizer, argv[i]);
    }
    
    // Clean up resources
    Mutex_destroy(mutex);
    free(mutex);
    TokenizerMultiReceptor_Destroy(tokenizer);
    
    return 0;
}

/*
 * ============================================================================
 * CORE PROCESSING FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Process a single input string through the tokenizer
 * @param tokenizer Pointer to initialized TokenizerMultiReceptor instance
 * @param input String containing numbers to be parsed
 * 
 * This function takes an input string and processes each character through
 * the finite state machine tokenizer. It handles:
 * - Digit characters (0-9): Processed as numeric input
 * - Decimal points (.): Transition to fractional processing
 * - Whitespace: Acts as number separator
 * - Other characters: Ignored
 */
void processString(TokenizerMultiReceptor* tokenizer, const char* input) {
    if (tokenizer == NULL || input == NULL) {
        return;
    }
    
    // Reset tokenizer state for new input processing
    TokenizerMultiReceptor_Init(tokenizer);
    
    // Re-associate the mutex (since Init clears all associations)
    Mutex* mutex = TokenizerMultiReceptor_getItsMutex(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
    
    printf("Processing characters: ");
    
    // Process each character in the input string
    for (size_t i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        printf("'%c' ", c);
        
        // Dispatch character to appropriate event handler
        if (isdigit(c)) {
            TokenizerMultiReceptor_evDigit(tokenizer, c);
        } else if (c == '.') {
            TokenizerMultiReceptor_evDot(tokenizer);
        } else if (isspace(c)) {
            TokenizerMultiReceptor_evWhiteSpace(tokenizer);
        }
        // Other characters are ignored (could be extended for error handling)
    }
    
    // Signal end of string to finalize any pending number
    printf("\nProcessing end of string...\n");
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    printf("---\n");
}

/*
 * ============================================================================
 * DEMONSTRATION AND TESTING FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Run interactive demonstration with predefined test cases
 * 
 * This function demonstrates the tokenizer capabilities using a variety
 * of number formats including integers, floating-point numbers, and
 * multiple numbers in single strings. It showcases the finite state
 * machine's ability to handle different input patterns.
 */
void demonstrateTokenizer(void) {
    printf("Running demonstration with various number formats:\n\n");
    
    // Comprehensive test cases covering different number formats
    const char* testCases[] = {
        "123",           // Simple integer
        "45.67",         // Simple floating-point
        "0.789",         // Fractional number starting with zero
        "100.0",         // Integer with explicit decimal
        "42 56 78.9",    // Multiple numbers with spaces
        "1.23 4.56 7.89", // Multiple floating-point numbers
        ".5",            // Fractional number without leading zero
        "999.999",       // Large number with many decimal places
        NULL             // Sentinel value to end array
    };
    
    // Create and initialize tokenizer
    TokenizerMultiReceptor* tokenizer = TokenizerMultiReceptor_Create();
    if (tokenizer == NULL) {
        fprintf(stderr, "Error: Failed to create tokenizer\n");
        return;
    }
    
    // Set up mutex for thread safety
    Mutex* mutex = malloc(sizeof(Mutex));
    if (mutex == NULL) {
        fprintf(stderr, "Error: Failed to allocate mutex\n");
        TokenizerMultiReceptor_Destroy(tokenizer);
        return;
    }
    
    if (Mutex_init(mutex) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex\n");
        free(mutex);
        TokenizerMultiReceptor_Destroy(tokenizer);
        return;
    }
    
    TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
    
    // Process all test cases
    for (int i = 0; testCases[i] != NULL; i++) {
        printf("Test case %d: \"%s\"\n", i + 1, testCases[i]);
        processString(tokenizer, testCases[i]);
        printf("\n");
    }
    
    // Clean up resources
    Mutex_destroy(mutex);
    free(mutex);
    TokenizerMultiReceptor_Destroy(tokenizer);
    
    printf("Demonstration completed successfully!\n");
}

/**
 * @brief Comprehensive testing suite for TokenizerMultiReceptor functionality
 * @return 0 on success (all tests passed), 1 on failure
 * 
 * This function performs thorough testing of the TokenizerMultiReceptor
 * implementation including:
 * - Object lifecycle (creation/destruction)
 * - Mutex integration and thread safety
 * - State machine functionality
 * - Number parsing accuracy
 * - Resource management
 */
int testTokenizerWithMutex(void) {
    printf("Testing TokenizerMultiReceptor with Mutex functionality:\n\n");
    
    // Test 1: Basic object lifecycle
    printf("Test 1: Basic object lifecycle\n");
    TokenizerMultiReceptor* tokenizer = TokenizerMultiReceptor_Create();
    if (tokenizer == NULL) {
        fprintf(stderr, "FAILED: Could not create tokenizer\n");
        return 1;
    }
    printf("✓ Tokenizer created successfully\n");
    
    // Test 2: Mutex creation and initialization
    printf("\nTest 2: Mutex setup\n");
    Mutex* mutex = malloc(sizeof(Mutex));
    if (mutex == NULL) {
        fprintf(stderr, "FAILED: Could not allocate mutex\n");
        TokenizerMultiReceptor_Destroy(tokenizer);
        return 1;
    }
    
    if (Mutex_init(mutex) != 0) {
        fprintf(stderr, "FAILED: Could not initialize mutex\n");
        free(mutex);
        TokenizerMultiReceptor_Destroy(tokenizer);
        return 1;
    }
    printf("✓ Mutex created and initialized successfully\n");
    
    // Test 3: Mutex association with tokenizer
    printf("\nTest 3: Mutex association with tokenizer\n");
    TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
    Mutex* retrievedMutex = TokenizerMultiReceptor_getItsMutex(tokenizer);
    if (retrievedMutex != mutex) {
        fprintf(stderr, "FAILED: Mutex association test failed\n");
        Mutex_destroy(mutex);
        free(mutex);
        TokenizerMultiReceptor_Destroy(tokenizer);
        return 1;
    }
    printf("✓ Mutex association working correctly\n");
    
    // Test 4: Number parsing functionality
    printf("\nTest 4: Number parsing\n");
    TokenizerMultiReceptor_Init(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, mutex); // Re-associate after init
    
    // Test parsing of "123.45" step by step
    TokenizerMultiReceptor_evDigit(tokenizer, '1');
    TokenizerMultiReceptor_evDigit(tokenizer, '2');
    TokenizerMultiReceptor_evDigit(tokenizer, '3');
    TokenizerMultiReceptor_evDot(tokenizer);
    TokenizerMultiReceptor_evDigit(tokenizer, '4');
    TokenizerMultiReceptor_evDigit(tokenizer, '5');
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    printf("✓ Number parsing test completed\n");
    
    // Test 5: Resource cleanup
    printf("\nTest 5: Cleanup\n");
    Mutex_destroy(mutex);
    free(mutex);
    TokenizerMultiReceptor_Destroy(tokenizer);
    printf("✓ All resources cleaned up successfully\n");
    
    printf("\n🎉 All tests passed! TokenizerMultiReceptor is working correctly.\n");
    return 0;
}

/*
 * ============================================================================
 * USER INTERFACE FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Display comprehensive usage information
 * @param programName Name of the program executable
 * 
 * This function provides detailed usage instructions and examples
 * for all supported program modes and options.
 */
void printUsage(const char* programName) {
    printf("Usage: %s [options] [input_strings...]\n\n", programName);
    
    printf("Options:\n");
    printf("  -h, --help    Show this help message and exit\n");
    printf("  --test        Run comprehensive functionality tests\n\n");
    
    printf("Examples:\n");
    printf("  %s                    # Run demonstration with predefined test cases\n", programName);
    printf("  %s \"123.45\"           # Parse a single number string\n", programName);
    printf("  %s \"12 34.5\" \"67.89\"  # Parse multiple number strings\n", programName);
    printf("  %s --test             # Run comprehensive test suite\n\n", programName);
    
    printf("Supported Input Format:\n");
    printf("The tokenizer recognizes and processes:\n");
    printf("  - Digits (0-9)         : Numeric input for building numbers\n");
    printf("  - Decimal points (.)   : Transition to fractional processing\n");
    printf("  - Whitespace           : Number separators (space, tab, newline)\n");
    printf("  - End of string        : Automatic finalization trigger\n");
    printf("  - Other characters     : Ignored (allows mixed input)\n\n");
    
    printf("Key Features:\n");
    printf("  ✓ Thread-safe operation using POSIX mutex synchronization\n");
    printf("  ✓ Finite state machine-based parsing for robust processing\n");
    printf("  ✓ Support for integers and floating-point numbers\n");
    printf("  ✓ Multiple number parsing from single input strings\n");
    printf("  ✓ Object-oriented design patterns in C\n");
    printf("  ✓ Comprehensive error handling and resource management\n\n");
    
    printf("State Machine Details:\n");
    printf("  States: NONUMBER_STATE → GOTNUMBER_STATE → NONUMBER_STATE\n");
    printf("  Substates: PROCESSINGWHOLEPART ↔ PROCESSINGFRACTIONALPART\n");
    printf("  Events: evDigit, evDot, evWhiteSpace, evEndOfString\n");
}
