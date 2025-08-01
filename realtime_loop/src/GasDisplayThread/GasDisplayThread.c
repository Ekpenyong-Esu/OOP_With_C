//
// Created by mahon on 1/25/2024.
//

#define _POSIX_C_SOURCE 199309L  // Ensure POSIX compliance for clock_gettime
#include "GasDisplayThread.h"
#include "GasSensorThread.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

// Grouped constants for better organization
#define DISPLAY_REFRESH_INTERVAL_MS 500
#define MAX_LINE_LENGTH 80
#define HISTORY_LENGTH 10
#define BAR_WIDTH 40

// Display state structure
typedef struct {
    int isInitialized;
    int errorCount;
    unsigned long lastUpdateTime;
    int updateCount;
    DisplayMode displayMode;
    char statusMessage[MAX_LINE_LENGTH];
} DisplayState;

// History buffer structure
typedef struct {
    int gasFlow[HISTORY_LENGTH];
    float temperature[HISTORY_LENGTH];
    float pressure[HISTORY_LENGTH];
    int currentIndex;
} DataHistory;

// Static variables for display state and data history
static DisplayState displayState = {
    .isInitialized = 0,
    .errorCount = 0,
    .lastUpdateTime = 0,
    .updateCount = 0,
    .displayMode = DISPLAY_MODE_DETAILED,
    .statusMessage = "System initialized"
};

static DataHistory dataHistory = {
    .currentIndex = 0
};

/**
 * @brief Clear the console screen (platform dependent)
 */
static void clearScreen(void) {
    printf("\033[2J\033[H");  // ANSI escape sequence to clear screen and move cursor to home
}

/**
 * @brief Get the current timestamp in milliseconds
 * 
 * @return unsigned long Current time in milliseconds
 */
static unsigned long getCurrentTimeMs(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

/**
 * @brief Update the data history with current readings
 */
static void updateDataHistory(void) {
    dataHistory.currentIndex = (dataHistory.currentIndex + 1) % HISTORY_LENGTH;
    dataHistory.gasFlow[dataHistory.currentIndex] = GasSensorThread_getGasLevel();
    dataHistory.temperature[dataHistory.currentIndex] = GasSensorThread_getTemperature();
    dataHistory.pressure[dataHistory.currentIndex] = GasSensorThread_getPressure();
}

/**
 * @brief Display a simple ASCII bar graph for the given value
 * 
 * @param value The value to display (0-100)
 * @param width The maximum width of the bar
 */
static void displayBar(int value, int width) {
    int barLength = (value * width) / 100;
    printf("[");
    for (int i = 0; i < width; i++) {
        printf(i < barLength ? "█" : " ");
    }
    printf("] %3d%%", value);
}

/**
 * @brief Display detailed system status with all relevant values and bars
 */
static void displayDetailedStatus(void) {
    int gasFlow = GasSensorThread_getGasLevel();
    float temperature = GasSensorThread_getTemperature();
    float pressure = GasSensorThread_getPressure();

    clearScreen();

    time_t now = time(NULL);
    char timeBuffer[30];
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║ Gas Control System Status         %27s ║\n", timeBuffer);
    printf("╠══════════════════════════════════════════════════════════════╣\n");

    printf("║ Measured Gas Flow: ");
    displayBar(gasFlow, BAR_WIDTH);
    printf(" ║\n");

    printf("║ Temperature: %6.2f °C                                     ║\n", temperature);
    printf("║ Pressure:    %6.2f kPa                                    ║\n", pressure);

    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ Status: %-52s ║\n", displayState.statusMessage);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

/**
 * @brief Display basic system status with minimal information
 */
static void displayBasicStatus(void) {
    clearScreen();
    printf("Gas Control System - Basic Display\n");
    printf("----------------------------------\n");
    printf("Gas Flow: %d%%\n", GasSensorThread_getGasLevel());
    printf("Status: %s\n", displayState.statusMessage);
}

/**
 * @brief Display a simple ASCII graph of historical values
 */
static void displayGraphView(void) {
    clearScreen();
    printf("Gas Flow History (newest to oldest):\n");
    
    // Display a simple ASCII graph of the last HISTORY_LENGTH readings
    for (int i = 0; i < HISTORY_LENGTH; i++) {
        int idx = (dataHistory.currentIndex - i + HISTORY_LENGTH) % HISTORY_LENGTH;
        printf("%2d: ", i);
        displayBar(dataHistory.gasFlow[idx], BAR_WIDTH);
        printf("\n");
    }
    
    printf("\nTemperature: %.2f°C  Pressure: %.2fkPa\n", 
           GasSensorThread_getTemperature(), 
           GasSensorThread_getPressure());
}

/**
 * @brief Display debug information for diagnostics
 */
static void displayDebugView(void) {
    clearScreen();
    printf("Gas Control System - Debug View\n");
    printf("------------------------------\n");
    printf("Display updates: %d\n", displayState.updateCount);
    printf("Error count: %d\n", displayState.errorCount);
    printf("Last update time: %lu ms\n", displayState.lastUpdateTime);
    
    printf("\nRaw Sensor Data:\n");
    printf("Gas Flow: %d\n", GasSensorThread_getGasLevel());
    printf("Temperature: %.2f\n", GasSensorThread_getTemperature());
    printf("Pressure: %.2f\n", GasSensorThread_getPressure());
    
    printf("\nHistory Buffer (idx=%d):\n", dataHistory.currentIndex);
    for (int i = 0; i < HISTORY_LENGTH; i++) {
        printf("Slot %2d: Flow=%3d, Temp=%.2f, Press=%.2f\n", 
               i, 
               dataHistory.gasFlow[i], 
               dataHistory.temperature[i], 
               dataHistory.pressure[i]);
    }
}

/**
 * @brief Update the display based on the current mode
 */
static void updateDisplay(void) {
    switch (displayState.displayMode) {
        case DISPLAY_MODE_DETAILED:
            displayDetailedStatus();
            break;
        case DISPLAY_MODE_BASIC:
            displayBasicStatus();
            break;
        case DISPLAY_MODE_GRAPH:
            displayGraphView();
            break;
        case DISPLAY_MODE_DEBUG:
            displayDebugView();
            break;
        default:
            displayDetailedStatus();
            break;
    }
}

/**
 * @brief Initialize the display thread
 * 
 * @return int 0 on success, non-zero error code otherwise
 */
int GasDisplayThread_init(void) {
    displayState.isInitialized = 1;
    displayState.updateCount = 0;
    displayState.lastUpdateTime = getCurrentTimeMs();
    displayState.displayMode = DISPLAY_MODE_DETAILED;
    strcpy(displayState.statusMessage, "System initialized");
    
    // Initialize history buffer
    memset(dataHistory.gasFlow, 0, sizeof(dataHistory.gasFlow));
    memset(dataHistory.temperature, 0, sizeof(dataHistory.temperature));
    memset(dataHistory.pressure, 0, sizeof(dataHistory.pressure));
    dataHistory.currentIndex = 0;
    
    clearScreen();
    printf("Gas Control System Display Initialized\n");
    
    return 0;
}

/**
 * @brief Run the display operations for one cycle
 */
void GasDisplayThread_run(void) {
    // Initialize if not already done
    if (!displayState.isInitialized) {
        if (GasDisplayThread_init() != 0) {
            fprintf(stderr, "Failed to initialize display thread\n");
            return;
        }
    }
    
    // Throttle display updates to reduce flicker and CPU usage
    unsigned long currentTime = getCurrentTimeMs();
    
    if (currentTime - displayState.lastUpdateTime >= DISPLAY_REFRESH_INTERVAL_MS) {
        displayState.lastUpdateTime = currentTime;
        displayState.updateCount++;
        
        // Update history data
        updateDataHistory();
        
        // Display the current status
        updateDisplay();
    }
}

/**
 * @brief Set the display mode
 * 
 * @param mode The display mode to use
 */
void GasDisplayThread_setDisplayMode(DisplayMode mode) {
    if (mode >= DISPLAY_MODE_DETAILED && mode <= DISPLAY_MODE_DEBUG) {
        displayState.displayMode = mode;
    }
}

/**
 * @brief Set the status message to display
 * 
 * @param message The status message to show
 */
void GasDisplayThread_setStatusMessage(const char* message) {
    if (message != NULL) {
        strncpy(displayState.statusMessage, message, MAX_LINE_LENGTH - 1);
        displayState.statusMessage[MAX_LINE_LENGTH - 1] = '\0';
    }
}

/**
 * @brief Shutdown the display subsystem
 */
void GasDisplayThread_shutdown(void) {
    if (displayState.isInitialized) {
        clearScreen();
        printf("Gas Control System Display Shutdown\n");
        displayState.isInitialized = 0;
    }
}
