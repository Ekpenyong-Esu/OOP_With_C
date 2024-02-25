//
// Created by mahon on 1/13/2024.
//

#include "Button.h"


// Debounce structure
typedef struct {
    uint8_t state;       // Current state of the button (pressed or released)
    uint8_t stableState; // Stable state after debouncing
    uint16_t debounceTime; // Debounce time in milliseconds
    uint16_t counter;     // Counter for debounce time
} DebounceButton;

// Global instance of the debounce button
DebounceButton myButton;

// Function to update the debounced button state
void updateDebouncedButtonState(uint8_t rawState) {
    if (rawState != myButton.state) {
        // Reset counter if there's a change in button state
        myButton.counter = 0;
    } else {
        // Increment counter if the state is stable
        myButton.counter++;
        if (myButton.counter >= myButton.debounceTime) {
            // Update stable state after debounce time
            myButton.stableState = rawState;
        }
    }

    // Update button state
    myButton.state = rawState;
}

// Function to initialize the button
void initButton(void) {
    // Initialize the debounce button parameters
    myButton.state = BUTTON_RELEASED;
    myButton.stableState = BUTTON_RELEASED;
    myButton.debounceTime = 20; // Debounce time in milliseconds
    myButton.counter = 0;
}

// Function to get the debounced state of the button
uint8_t getDebouncedButtonState(void) {
    // Simulate reading the raw state of the button (0 for released, 1 for pressed)
    uint8_t rawButtonState = 0; /* Read the actual state from your hardware */

    // Update the debounced button state
    updateDebouncedButtonState(rawButtonState);

    // Return the stable state of the debounced button
    return myButton.stableState;
}
