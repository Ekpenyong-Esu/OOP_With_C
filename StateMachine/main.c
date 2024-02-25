/*Creating a state machine in C involves defining states, events, transitions, and actions.
 * Below is a simple example of a state machine in C using function pointers and a state
 * transition table. This example represents a simple light switch state machine with two states:
 * OFF and ON.
 */


#include <stdio.h>
#include <stdlib.h>

// Enumeration for states
typedef enum {
    OFF,
    ON
} State;

// Enumeration for events
typedef enum {
    TURN_ON,
    TURN_OFF
} Event;

// Function pointer type for state actions
typedef void (*StateAction)(void);

// Structure representing a state machine
typedef struct {
    State currentState;
    StateAction* stateActions;
} StateMachine;

// Function prototypes for state actions
void enterOffState(void);
void enterOnState(void);

// Function to initialize the state machine
void initStateMachine(StateMachine* machine);

// Function to transition to a new state
void transitionState(StateMachine* machine, Event event);

int main() {
    StateMachine lightSwitch;
    initStateMachine(&lightSwitch);

    // Initial state
    printf("Initial state: ");
    lightSwitch.stateActions[lightSwitch.currentState]();

    // Event: Turn On
    printf("Turning on...\n");
    transitionState(&lightSwitch, TURN_ON);
    lightSwitch.stateActions[lightSwitch.currentState]();

    // Event: Turn Off
    printf("Turning off...\n");
    transitionState(&lightSwitch, TURN_OFF);
    lightSwitch.stateActions[lightSwitch.currentState]();

    return 0;
}

// State actions
void enterOffState(void) {
    printf("Light is OFF.\n");
}

void enterOnState(void) {
    printf("Light is ON.\n");
}

// Initialize the state machine
void initStateMachine(StateMachine* machine) {
    machine->currentState = OFF;

    // Allocate memory for state actions
    machine->stateActions = (StateAction*)malloc(sizeof(StateAction) * (ON + 1));

    // Set state actions
    machine->stateActions[OFF] = enterOffState;
    machine->stateActions[ON] = enterOnState;
}

// Transition to a new state based on the event
void transitionState(StateMachine* machine, Event event) {
    switch (event) {
        case TURN_ON:
            machine->currentState = ON;
            break;
        case TURN_OFF:
            machine->currentState = OFF;
            break;
            // Handle other events as needed
    }
}
