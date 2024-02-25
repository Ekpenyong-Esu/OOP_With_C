#include "Button.h"

int main() {
    // Initialize the button
    initButton();

    while (1) {
        // Read the state of the debounced button
        uint8_t buttonState = getDebouncedButtonState();

        // Your application logic based on the button state
        if (buttonState == BUTTON_PRESSED) {
            // Do something when the button is pressed
        } else {
            // Do something when the button is released
        }
    }

    return 0;
}
