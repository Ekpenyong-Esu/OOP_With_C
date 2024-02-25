
/*In a state machine, an "AND" state refers to a situation where the system
 * is in multiple states simultaneously. This concept is often implemented using
 * parallel or concurrent states. However, in many traditional state machine implementations,
 * including simple ones in C, the concept of parallel states might not be directly supported.
 *One way to simulate the behavior of an "AND" state in a traditional state machine is to represent
 * the combined state as a composite state. In other words, you can have a single state that encapsulates
 * the behavior of multiple independent states. Each of these independent states can have its own set of
 * transitions, actions, and conditions.
 *
 */


#include <stdio.h>

// Enumeration for states
typedef enum {
    OFF,
    ON,
    ALARM
} State;

// Enumeration for events
typedef enum {
    TURN_ON,
    TURN_OFF,
    TRIGGER_ALARM,
    RESET_ALARM
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
void enterAlarmState(void);

// Function to initialize the state machine
void initStateMachine(StateMachine* machine);

// Function to transition to a new state
void transitionState(StateMachine* machine, Event event);

int main() {
    StateMachine alarmSystem;
    initStateMachine(&alarmSystem);

    // Initial state
    printf("Initial state: ");
    alarmSystem.stateActions[alarmSystem.currentState]();

    // Event: Turn On
    printf("Turning on...\n");
    transitionState(&alarmSystem, TURN_ON);
    alarmSystem.stateActions[alarmSystem.currentState]();

    // Event: Trigger Alarm
    printf("Triggering alarm...\n");
    transitionState(&alarmSystem, TRIGGER_ALARM);
    alarmSystem.stateActions[alarmSystem.currentState]();

    // Event: Reset Alarm
    printf("Resetting alarm...\n");
    transitionState(&alarmSystem, RESET_ALARM);
    alarmSystem.stateActions[alarmSystem.currentState]();

    return 0;
}

// State actions
void enterOffState(void) {
    printf("System is OFF.\n");
}

void enterOnState(void) {
    printf("System is ON.\n");
}

void enterAlarmState(void) {
    printf("System is in ALARM state.\n");
}

// Initialize the state machine
void initStateMachine(StateMachine* machine) {
    machine->currentState = OFF;

    // Allocate memory for state actions
    machine->stateActions = (StateAction*)malloc(sizeof(StateAction) * (ALARM + 1));

    // Set state actions
    machine->stateActions[OFF] = enterOffState;
    machine->stateActions[ON] = enterOnState;
    machine->stateActions[ALARM] = enterAlarmState;
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
        case TRIGGER_ALARM:
            machine->currentState = ALARM;
            break;
        case RESET_ALARM:
            machine->currentState = ON; // Resetting alarm brings the system back to the ON state
            break;
            // Handle other events as needed
    }
}
