#ifndef GAS_ACTUATOR_THREAD_H
#define GAS_ACTUATOR_THREAD_H

/**
 * @file GasActuatorThread.h
 * @brief Controls the gas system actuators based on sensor readings and control logic
 */

/**
 * @brief Run the actuator control logic for one cycle
 * 
 * This function processes the latest sensor data and adjusts 
 * gas actuators according to the control algorithm.
 * It should be called once per control cycle.
 */
void GasActuatorThread_run(void);

/**
 * @brief Initialize the gas actuator subsystem
 * 
 * This function should be called once at system startup to
 * set up the actuator hardware and initialize control parameters.
 * 
 * @return int 0 on success, non-zero error code otherwise
 */
int GasActuatorThread_init(void);

/**
 * @brief Shutdown the gas actuator subsystem safely
 * 
 * This function should be called during system shutdown to
 * ensure actuators are placed in a safe state.
 */
void GasActuatorThread_shutdown(void);

#endif /* GAS_ACTUATOR_THREAD_H */