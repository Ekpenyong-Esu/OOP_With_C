// Refactored for readability and maintainability

#include "GasActuatorThread.h"
#include "GasSensorThread.h"  // To access sensor readings

/**
 * Private state variables for the actuator system
 */
typedef struct {
    int valvePosition;   // Current position of the gas valve (0-100%)
    int targetPosition;  // Target position for the gas valve
    int isActive;        // Whether the actuator system is active
} ActuatorState;

static ActuatorState state = {
    .valvePosition = 0,
    .targetPosition = 0,
    .isActive = 0
};

/**
 * @brief Set the gas valve position
 * 
 * @param position The desired valve position (0-100%)
 */
static void setValvePosition(int position) {
    // Clamp position to valid range
    if (position < 0) position = 0;
    if (position > 100) position = 100;

    // In a real system, this would control hardware
    // For simulation, we just update our internal state
    state.valvePosition = position;
}

/**
 * @brief Calculate new actuator settings based on sensor data
 */
static void processControlLogic(void) {
    // Example control logic - in a real system this would be more sophisticated
    // Get current gas measurement from the sensor module
    int gasLevel = GasSensorThread_getGasLevel();

    // Simplified proportional control example
    const int setPoint = 50;  // Desired gas level
    const float Kp = 0.5f;    // Proportional gain

    int error = setPoint - gasLevel;
    state.targetPosition = state.valvePosition + (int)(Kp * error);

    // Implement the new valve position
    setValvePosition(state.targetPosition);
}

/**
 * @brief Run the actuator control logic for one cycle
 */
void GasActuatorThread_run(void) {
    if (!state.isActive) return;

    // Process control logic to determine new actuator settings
    processControlLogic();
}

/**
 * @brief Initialize the gas actuator subsystem
 * 
 * @return int 0 on success, non-zero error code otherwise
 */
int GasActuatorThread_init(void) {
    // Initialize hardware - would include actual code for your specific hardware
    // For simulation, we just initialize our internal state

    state.valvePosition = 0;
    state.targetPosition = 0;
    state.isActive = 1;

    // Set actuators to safe initial positions
    setValvePosition(0);

    return 0;  // Success
}

/**
 * @brief Shutdown the gas actuator subsystem safely
 */
void GasActuatorThread_shutdown(void) {
    // Put actuators in a safe state when shutting down
    setValvePosition(0);
    state.isActive = 0;
}