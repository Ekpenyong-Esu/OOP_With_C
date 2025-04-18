#ifndef GAS_SENSOR_THREAD_H
#define GAS_SENSOR_THREAD_H

/**
 * @file GasSensorThread.h
 * @brief Manages the gas sensing subsystem and provides readings to other components
 */

/**
 * @brief Run the gas sensor operations for one cycle
 * 
 * Reads the latest data from gas sensors and processes it.
 * This function should be called once per control cycle.
 */
void GasSensorThread_run(void);

/**
 * @brief Get the current gas level reading
 * 
 * @return int The current gas level measurement (0-100)
 */
int GasSensorThread_getGasLevel(void);

/**
 * @brief Get the current gas temperature reading
 * 
 * @return float The current gas temperature in degrees Celsius
 */
float GasSensorThread_getTemperature(void);

/**
 * @brief Get the current gas pressure reading
 * 
 * @return float The current gas pressure in kPa
 */
float GasSensorThread_getPressure(void);

/**
 * @brief Initialize the gas sensor subsystem
 * 
 * This function should be called once at system startup to
 * set up the sensor hardware and data structures.
 * 
 * @return int 0 on success, non-zero error code otherwise
 */
int GasSensorThread_init(void);

/**
 * @brief Shutdown the gas sensor subsystem
 * 
 * This function should be called during system shutdown to
 * properly close sensor connections and free resources.
 */
void GasSensorThread_shutdown(void);

#endif /* GAS_SENSOR_THREAD_H */