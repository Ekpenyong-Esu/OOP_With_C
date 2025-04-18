#ifndef GAS_DISPLAY_THREAD_H
#define GAS_DISPLAY_THREAD_H

/**
 * @file GasDisplayThread.h
 * @brief Manages the display of gas system data and status information
 */

/**
 * @brief Display modes for different visualization preferences
 */
typedef enum {
    DISPLAY_MODE_DETAILED = 0,    /**< Detailed status with all parameters */
    DISPLAY_MODE_BASIC = 1,       /**< Basic status with essential info */
    DISPLAY_MODE_GRAPH = 2,       /**< Graphical representation of trends */
    DISPLAY_MODE_DEBUG = 3        /**< Debug information for diagnostics */
} DisplayMode;

/**
 * @brief Run the display operations for one cycle
 * 
 * Updates the display with current system information.
 * This function should be called once per control cycle.
 */
void GasDisplayThread_run(void);

/**
 * @brief Initialize the display subsystem
 * 
 * This function should be called once at system startup to
 * set up the display and initialize the UI.
 * 
 * @return int 0 on success, non-zero error code otherwise
 */
int GasDisplayThread_init(void);

/**
 * @brief Shutdown the display subsystem
 * 
 * This function should be called during system shutdown to
 * close the display gracefully.
 */
void GasDisplayThread_shutdown(void);

/**
 * @brief Set the display mode
 * 
 * @param mode The display mode to use
 */
void GasDisplayThread_setDisplayMode(DisplayMode mode);

/**
 * @brief Set the status message to display
 * 
 * @param message The status message to show
 */
void GasDisplayThread_setStatusMessage(const char* message);

#endif /* GAS_DISPLAY_THREAD_H */