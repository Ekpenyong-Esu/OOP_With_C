
/*
 * A state table is a structured way to define the transitions and actions in a
 * state machine. It typically consists of rows, each representing a possible state,
 * and columns for events or triggers, containing the resulting state and
 * associated actions. Here's an example of a simple state table for a
 * light switch in C:
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

// Structure representing a state table entry
typedef struct {
    State nextState;
    StateAction action;
} StateTableEntry;

// Structure representing a state machine
typedef struct {
    State currentState;
    StateTableEntry** stateTable;
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
    lightSwitch.stateTable[lightSwitch.currentState][0].action();

    // Event: Turn On
    printf("Turning on...\n");
    transitionState(&lightSwitch, TURN_ON);
    lightSwitch.stateTable[lightSwitch.currentState][0].action();

    // Event: Turn Off
    printf("Turning off...\n");
    transitionState(&lightSwitch, TURN_OFF);
    lightSwitch.stateTable[lightSwitch.currentState][0].action();

    // Free memory
    free(lightSwitch.stateTable[OFF]);
    free(lightSwitch.stateTable[ON]);
    free(lightSwitch.stateTable);

    return 0;
}

// State actions
void enterOffState(void) {
    printf("Light is OFF.\n");
}

void enterOnState(void) {
    printf("Light is ON.\n");
}

// Initialize the state machine and state table
void initStateMachine(StateMachine* machine) {
    machine->currentState = OFF;

    // Allocate memory for state table
    machine->stateTable = (StateTableEntry**)malloc(sizeof(StateTableEntry*) * (ON + 1));

    // Allocate memory for state entries
    machine->stateTable[OFF] = (StateTableEntry*)malloc(sizeof(StateTableEntry) * 1);
    machine->stateTable[ON] = (StateTableEntry*)malloc(sizeof(StateTableEntry) * 1);

    // Set state table entries
    machine->stateTable[OFF][0].nextState = ON;
    machine->stateTable[OFF][0].action = enterOnState;

    machine->stateTable[ON][0].nextState = OFF;
    machine->stateTable[ON][0].action = enterOffState;
}

// Transition to a new state based on the event
void transitionState(StateMachine* machine, Event event) {
    switch (event) {
        case TURN_ON:
            machine->currentState = machine->stateTable[machine->currentState][0].nextState;
            break;
        case TURN_OFF:
            machine->currentState = machine->stateTable[machine->currentState][0].nextState;
            break;
            // Handle other events as needed
    }
}
