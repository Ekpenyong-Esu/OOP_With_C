#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SecuritySupervisor.h"

// Event handler
void handleEvent(DoorMachineState* door, char key) {
    door->params = (Param*)malloc(sizeof(Param));
    if (door->params == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    door->params->key = (char)key;
    door->id = keypress_SecuritySupervisor_Event_id;
    dispatchEvent(door);
    free(door->params);
    door->params = NULL;
}

void processState(DoorMachineState* door) {
    while (door->activeState == SecuritySupervisor_CheckingLength || door->activeState == SecuritySupervisor_ValidatingPIN) {
        door->id = Null_id;
        dispatchEvent(door);
    }
}

int main(void) {
    // Initialize door state machine
    DoorMachineState door;
    memset(&door, 0, sizeof(DoorMachineState));
    door.activeState = SecuritySupervisor_Idle;

    // Simulate the state machine
    printf("Door Security System\n");
    printf("Press ESC to cancel, ENTER to submit, R to reset, or digits to enter the PIN.\n");

    char input = 0;
    while (1) {
        printf("Enter a key: ");
        input = (char)getchar();

        // Consume the newline left in the buffer
        while (getchar() != '\n');

        // Simulate cancellation
        if (input == ESC_KEY) {
            handleEvent(&door, ESC_KEY);
            printf("Operation cancelled.\n");
        }
        // Simulate PIN entry
        else if (input >= '0' && input <= '9') {
            handleEvent(&door, input);
            printf("Digit entered: %d\n", input - '0');
        }
        // Simulate submitting the PIN
        else if (input == ENTER_KEY) {
            handleEvent(&door, ENTER_KEY);
            printf("PIN submitted.\n");
        }
        // Simulate resetting
        else if (input == RESET_KEY) {
            handleEvent(&door, RESET_KEY);
            printf("System reset.\n");
        }
        // Handle exit condition
        else if (input == 'Q' || input == 'q') {
            printf("Exiting the program.\n");
            break;
        }
        // Handle unknown input
        else {
            printf("Unknown input. Please try again.\n");
        }

        // Process state transitions
        processState(&door);

        // Print current state as a string

    }

    return 0;
}
