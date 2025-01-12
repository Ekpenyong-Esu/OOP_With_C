#include "SecuritySupervisor.h"
#include <string.h>
#include <stdio.h>

#define PIN_SIZE 4

int pinLength = 0;
static char pin[PIN_SIZE + 1] = {0};  // Add one extra space for null-terminator

void displayMsg(const char* msg){
    printf("%s\n", msg);
}

int isCancel(char key){
    return key == ESC_KEY;
}

int isDigit(char key){
    return ((key) >= '0' && (key) <= '9');
}

int isEnter(char key){
    return key == ENTER_KEY;
}

int isReset(char key){
    return key == RESET_KEY;
}

void addKey(char key){
    if (pinLength < PIN_SIZE) {
        pin[pinLength] = key;
        pinLength++;
        pin[pinLength] = '\0';  // Ensure null-termination
    }
}

int isValid(char* inputPin){
    return strcmp(inputPin, "1234");
}

void unlockDoor(void){
    displayMsg("Door unlocked");
}

void lockDoor(void){
    displayMsg("Door locked");
}

void resetPin(void) {
    memset(pin, 0, PIN_SIZE + 1);  // Reset the pin array
    pinLength = 0;  // Reset the pin length
}

const char* getActiveStateString(ActiveState state) {
    switch (state) {
        case SecuritySupervisor_Idle:
            return "Idle";
        case SecuritySupervisor_Accepting:
            return "Accepting";
        case SecuritySupervisor_CheckingLength:
            return "CheckingLength";
        case SecuritySupervisor_ValidatingPIN:
            return "ValidatingPIN";
        case SecuritySupervisor_SecurityOpen:
            return "SecurityOpen";
        case SecuritySupervisor_ErrorState:
            return "ErrorState";
        default:
            return "Unknown";
    }
}

/**
 * @brief This function is responsible for managing the state machine of a door security system.
 *        It processes events and transitions between different states based on the current state and the event received.
 *
 * @param door A pointer to the DoorMachineState structure representing the current state of the door security system.
 *
 * @return EventStatus - An enum representing the status of the event consumption.
 *         - EventConsumed: The event was successfully consumed and processed.
 *         - EventNotConsumed: The event was not consumed and should be processed by other parts of the system.
 *
 * @note The function uses a switch-case statement to handle different states and events.
 *       It calls various helper functions to perform actions and update the state of the door security system.
 *
 * @note The function assumes that the DoorMachineState structure has the following members:
 *       - activeState: An enum representing the current state of the door security system.
 *       - params: A pointer to a Param structure containing event parameters.
 *       - id: A char representing the event ID.
 *       - retries: An integer representing the number of retries made by the user.
 *
 * @note The function also assumes the existence of the following helper functions:
 *       - displayMsg(const char* msg): A function to display a message to the user.
 *       - isCancel(char key): A function to check if a key represents the cancel action.
 *       - isDigit(char key): A function to check if a key represents a digit.
 *       - isEnter(char key): A function to check if a key represents the enter action.
 *       - isReset(char key): A function to check if a key represents the reset action.
 *       - addKey(char key): A function to add a key to the PIN.
 *       - isValid(char* inputPin): A function to check if the entered PIN is valid.
 *       - unlockDoor(): A function to unlock the door.
 *       - lockDoor(): A function to lock the door.
 */
 EventStatus dispatchEvent(DoorMachineState* door){
    Param* params = door->params;
    char id = door->id;
    EventStatus res = EventNotConsumed;



    switch(door->activeState){
        case SecuritySupervisor_Idle:
            {
                if (id == Null_id)  //not trigger event
                {
                    door->activeState = SecuritySupervisor_ErrorState;
                    displayMsg("ERROR: max retries exceeded");
                    res = EventConsumed;
                }
                else
                {
                    ++door->retries;
                    door->activeState = SecuritySupervisor_Accepting;
                    addKey((char)params->key);
                    res = EventConsumed;
                }
            }
            break;
        case SecuritySupervisor_Accepting:
            {
                if (id == keypress_SecuritySupervisor_Event_id)
                {
                    if (isCancel((char)params->key))
                    {
                        door->retries = 0;
                        displayMsg("Canceled");
                        door->activeState = SecuritySupervisor_Idle;
                        resetPin();
                    }
                    else
                    {
                        if(isDigit((char)params->key)){
                            addKey((char)params->key);
                            door->activeState = SecuritySupervisor_Accepting;
                            res = EventConsumed;
                        }
                        else
                        {
                            if (isEnter((char)params->key))
                            {
                                door->activeState = SecuritySupervisor_CheckingLength;
                                res = EventConsumed;
                            }
                        }
                    }
                }
            }
            break;
        case SecuritySupervisor_CheckingLength:
            if (id == Null_id)
            {
                if (pinLength == PIN_SIZE)
                {
                    door->activeState = SecuritySupervisor_ValidatingPIN;
                    displayMsg("Correct pin length");
                    res = EventConsumed;
                }
                else
                {
                    displayMsg("ERROR: wrong PIN length");
                    door->activeState = SecuritySupervisor_Idle;
                    resetPin();
                    res = EventConsumed;
                }
            }
            break;
        case SecuritySupervisor_ValidatingPIN:
            if (id == Null_id)
            {
                if (isValid(pin) == 0)  // Assuming isValid returns 0 for valid PIN
                {
                    unlockDoor();
                    door->activeState = SecuritySupervisor_SecurityOpen;
                    resetPin();
                    res = EventConsumed;
                }
                else
                {
                    displayMsg("ERROR: invalid PIN");
                    door->activeState = SecuritySupervisor_Idle;
                    resetPin();
                    res = EventConsumed;
                }
            }
            break;
        case SecuritySupervisor_SecurityOpen:
            if (id == keypress_SecuritySupervisor_Event_id)
            {
                if (isReset((char)params->key))
                {
                    lockDoor();
                    displayMsg("Door locked");
                    door->activeState = SecuritySupervisor_Idle;
                    resetPin();
                    res = EventConsumed;
                }
            }
            break;
        default:
            break;
    }

    printf("Current state: %s\n\n", getActiveStateString(door->activeState));
    return res;
}
