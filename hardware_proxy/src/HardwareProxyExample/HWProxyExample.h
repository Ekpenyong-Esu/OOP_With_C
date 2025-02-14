//
// Created by mahon on 1/4/2024.
//

#ifndef HARDWARE_PROXY_HWPROXYEXAMPLE_H
#define HARDWARE_PROXY_HWPROXYEXAMPLE_H

// Motor direction enumeration
typedef enum DirectionType {
    NO_DIRECTION,    // Motor is stopped
    FORWARD,         // Motor moving forward
    REVERSE         // Motor moving backward
} DirectionType;

// Hardware components
struct MotorController;  // Controls motor operations
struct MotorData;        // Stores motor state and parameters
struct MotorDisplay;     // Handles motor information display
struct MotorProxy;       // Provides interface to motor hardware

#endif //HARDWARE_PROXY_HWPROXYEXAMPLE_H
