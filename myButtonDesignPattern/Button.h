//
// Created by mahon on 1/13/2024.
//

#ifndef MYBUTTONDESIGNPATTERN_BUTTON_H
#define MYBUTTONDESIGNPATTERN_BUTTON_H

#include <stdint.h>

// Button states
#define BUTTON_PRESSED 1
#define BUTTON_RELEASED 0

// Function to initialize the button
void initButton(void);

// Function to get the debounced state of the button
uint8_t getDebouncedButtonState(void);

#endif //MYBUTTONDESIGNPATTERN_BUTTON_H
