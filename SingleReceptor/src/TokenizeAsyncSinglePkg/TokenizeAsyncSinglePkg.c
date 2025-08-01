#include "TokenizeAsyncSinglePkg.h"

// Helper function: returns the digit value of a character ('0'-'9')
int digit(char character) {
    return character - '0';
}

// Signal that an event has been posted (stub implementation for educational purposes)
void postSignal(void) {
    // In a real implementation, this would signal a waiting thread
    // For educational purposes, this is a no-op
}

// Wait for a signal that an event is available (stub implementation for educational purposes)
void waitOnSignal(void) {
    // In a real implementation, this would block until an event is available
    // For educational purposes, this is a no-op
}
