/**
 * Main application for button debounce demonstration
 *
 * This example shows how to use a ButtonDriver to manage a hardware button
 * with debounce functionality and control a MicrowaveEmitter.
 */
#include "ButtonDriver.h"
#include "Button.h"
#include "MicrowaveEmitter.h"
#include "Timer.h"
#include <stdio.h>

/**
 * Test scenario: Toggle OFF to ON
 */
void runToggleOnTest(ButtonDriver* p_ButtonDriver, Button* p_Button) {
    printf("\n=== Running Toggle ON Test ===\n");
    p_ButtonDriver->toggleOn = 0;  // Initially OFF
    p_ButtonDriver->oldState = 1;  // Previously pressed
    p_Button->deviceState = 0;     // Now released

    ButtonDriver_eventReceive(p_ButtonDriver);
}

/**
 * Test scenario: Toggle ON to OFF
 */
void runToggleOffTest(ButtonDriver* p_ButtonDriver, Button* p_Button) {
    printf("\n=== Running Toggle OFF Test ===\n");
    p_ButtonDriver->toggleOn = 1;  // Initially ON
    p_ButtonDriver->oldState = 1;  // Previously pressed
    p_Button->deviceState = 0;     // Now released

    ButtonDriver_eventReceive(p_ButtonDriver);
}

int main(int argc, char const *argv[]) {
    printf("Button Debounce Application\n");

    // Create component instances
    ButtonDriver* p_ButtonDriver = ButtonDriver_Create();
    Button* p_Button = Button_Create();
    MicrowaveEmitter* p_MicrowaveEmitter = MicrowaveEmitter_Create();
    Timer* p_Timer = Timer_Create();

    if (!p_ButtonDriver || !p_Button || !p_MicrowaveEmitter || !p_Timer) {
        printf("Error: Failed to create component instances\n");
        return -1;
    }

    // Set up relationships
    ButtonDriver_setItsButton(p_ButtonDriver, p_Button);
    ButtonDriver_setItsMicrowaveEmitter(p_ButtonDriver, p_MicrowaveEmitter);
    ButtonDriver_setItsTimer(p_ButtonDriver, p_Timer);

    // Run test scenarios
    runToggleOnTest(p_ButtonDriver, p_Button);
    runToggleOffTest(p_ButtonDriver, p_Button);

    // Clean up resources
    ButtonDriver_Destroy(p_ButtonDriver);
    Button_Destroy(p_Button);
    MicrowaveEmitter_Destroy(p_MicrowaveEmitter);
    Timer_Destroy(p_Timer);

    printf("\nApplication completed successfully\n");
    return 0;
}
