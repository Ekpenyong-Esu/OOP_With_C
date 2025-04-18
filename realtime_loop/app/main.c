/**
 * @file main.c
 * @brief Main entry point for the Gas Control System
 */

 #include <unistd.h>  // Header for usleep() function
 #include "GasControlEpochTime.h"
 #include "GasActuatorThread.h"
 #include "GasDisplayThread.h"
 #include "GasSensorThread.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <stdbool.h>

 
 /**
  * @brief Initialize all subsystems
  * 
  * @return int 0 on success, non-zero on failure
  */
 int initializeSystem(void) {
     int status = 0;
     
     printf("Gas Control System: Starting initialization\n");
     
     status = GasSensorThread_init();
     if (status != 0) {
         fprintf(stderr, "Failed to initialize sensor subsystem (error %d)\n", status);
         return status;
     }
     
     status = GasActuatorThread_init();
     if (status != 0) {
         fprintf(stderr, "Failed to initialize actuator subsystem (error %d)\n", status);
         return status;
     }
     
     status = GasDisplayThread_init();
     if (status != 0) {
         fprintf(stderr, "Failed to initialize display subsystem (error %d)\n", status);
         return status;
     }
     
     printf("Gas Control System: Initialization complete\n");
     return 0;
 }
 
 /**
  * @brief Shutdown all subsystems
  */
 void shutdownSystem(void) {
     printf("Gas Control System: Starting shutdown sequence\n");
     
     // Shutdown subsystems in reverse order of initialization
     GasDisplayThread_shutdown();
     GasActuatorThread_shutdown();
     GasSensorThread_shutdown();
     GasDisplayThread_shutdown();
     
     
     printf("Gas Control System: Shutdown complete\n");
 }


  // Flag to indicate if the system should continue running
  volatile sig_atomic_t running = true;
 
  /**
   * @brief Signal handler for graceful shutdown
   * 
   * @param sig Signal number
   */
  void signalHandler(int sig) {
      printf("\nReceived signal %d. Shutting down...\n", sig);
      shutdownSystem();
      running = false;
  }
 
 /**
  * @brief Modified control loop that can be interrupted
  */
 void runControlLoop(void) {
     // Set initial status message
     GasDisplayThread_setStatusMessage("System running normally");
     
     printf("Gas Control System: Starting control loop\n");
     
     // Main control loop
     while (running) {
         startEpochTimer();
         
         // Run all threads in sequence
         GasSensorThread_run();
         GasActuatorThread_run();
         GasDisplayThread_run();
         
         // Wait for epoch to complete or until interrupted
         while (!epochTimerHasElapsed() && running) {
             // Short sleep to prevent CPU spinning
             sleep(10);  // 1ms sleep
         }
     }
 }
 
 int main(int argc, char *argv[]) {
     (void)argc;  // Suppress unused parameter warning
     (void)argv;  // Suppress unused parameter warning
     
     // Register signal handlers for graceful termination
     signal(SIGINT, signalHandler);   // Ctrl+C
     signal(SIGTERM, signalHandler);  // kill command
     
     // Initialize the system
     int status = initializeSystem();
     if (status != 0) {
         fprintf(stderr, "System initialization failed with status %d\n", status);
         shutdownSystem();
         return EXIT_FAILURE;
     }
     
     // Run the main control loop
     runControlLoop();
     
     // Clean shutdown
     shutdownSystem();
     
     return EXIT_SUCCESS;
 }
