#include <stdio.h>
#include "ECG_Module.h"
#include "TMDQueue.h"
#include "HistogramDisplay.h"
#include "WaveformDisplay.h"
#include "TestBuilder.h"

/**
 * Observer Pattern Demonstration
 *
 * This example shows the basic structure of the Observer pattern:
 * 1. A subject (TMDQueue) maintains a list of observers
 * 2. Observers (HistogramDisplay and WaveFormDisplay) register with the subject
 * 3. When data changes, the subject notifies all observers
 * 4. Each observer responds to the notification independently
 * 
 * Note: This file demonstrates two approaches:
 * - Manual setup (by creating and connecting objects directly)
 * - Using TestBuilder (which encapsulates creation and connection)
 */
// We will demonstrate two approaches to setting up the Observer pattern
void manual_setup_demo(void);
void testbuilder_demo(void);

int main(int argc, char* argv[]) {
    (void)argc;  // Avoid unused parameter warning
    (void)argv;  // Avoid unused parameter warning

    printf("===============================================\n");
    printf("     OBSERVER PATTERN DEMONSTRATION            \n");
    printf("===============================================\n\n");

    // First demonstrate manual setup
    printf("APPROACH 1: Manual Setup\n");
    printf("======================\n");
    manual_setup_demo();

    printf("\n\n");
    printf("===============================================\n");
    printf("\nAPPROACH 2: Using TestBuilder\n");
    printf("==========================\n");
    testbuilder_demo();

    return 0;
}

// Manual setup of the Observer pattern components
void manual_setup_demo(void) {
    printf("Manually creating and connecting components...\n\n");

    // Create the subject
    printf("Creating Subject (TMDQueue)...\n");
    TMDQueue* tmdQueue = TMDQueue_Create();
    
    // Create the data source
    printf("Creating ECG Module (data source)...\n");
    ECG_Module* ecgModule = ECG_Module_Create();
    
    // Connect data source to subject
    ECG_Module_setItsTMDQueue(ecgModule, tmdQueue);
    
    // Create observers
    printf("\nCreating Observer 1 (HistogramDisplay)...\n");
    HistogramDisplay* histogramDisplay = HistogramDisplay_Create();
    
    printf("Creating Observer 2 (WaveFormDisplay)...\n");
    WaveformDisplay* waveformDisplay = WaveformDisplay_Create();
    
    // Register observers with the subject
    printf("\nRegistering Observers with Subject...\n");
    HistogramDisplay_setItsTMDQueue(histogramDisplay, tmdQueue);
    WaveformDisplay_setItsTMDQueue(waveformDisplay, tmdQueue);
    
    // Generate data which will notify observers
    printf("\nGenerating data which will trigger notifications:\n");
    printf("------------------------------------------------\n");
    ECG_Module_acquireValue(ecgModule);
    
    printf("\nGenerating more data:\n");
    printf("-------------------\n");
    ECG_Module_acquireValue(ecgModule);
    
    // Unsubscribe one observer
    printf("\nUnsubscribing Observer 1 (HistogramDisplay)...\n");
    TMDQueue_unsubscribe(tmdQueue, (UpdateFuncPtr)HistogramDisplay_update);
    
    // Generate more data (only WaveFormDisplay will be notified)
    printf("\nGenerating more data (only Observer 2 should be notified):\n");
    printf("------------------------------------------------------\n");
    ECG_Module_acquireValue(ecgModule);
    
    // Clean up
    printf("\nCleaning up resources...\n");
    HistogramDisplay_Destroy(histogramDisplay);
    WaveformDisplay_Destroy(waveformDisplay);
    ECG_Module_Destroy(ecgModule);
    TMDQueue_Destroy(tmdQueue);
    
    printf("\nManual setup demonstration complete.\n");
}

// Using TestBuilder to set up the Observer pattern components
void testbuilder_demo(void) {
    printf("Creating components with TestBuilder...\n\n");
    
    // Create all components using the TestBuilder
    TestBuilder* testBuilder = TestBuilder_Create();
    
    // Get references to components
    ECG_Module* ecgModule = TestBuilder_getItsECG_Module(testBuilder);
    
    printf("All components created and relationships established.\n");
    printf("The following observers are subscribed to the subject:\n");
    printf("1. HistogramDisplay\n");
    printf("2. WaveFormDisplay\n");
    printf("3. QRSDetector\n");
    printf("4. ArrhythmiaDetector\n\n");
    
    // Generate data which will notify all observers
    printf("Generating data which will trigger notifications to all observers:\n");
    printf("--------------------------------------------------------\n");
    ECG_Module_acquireValue(ecgModule);
    
    // Clean up
    printf("\nCleaning up all resources...\n");
    TestBuilder_Destroy(testBuilder);
    
    printf("\nTestBuilder demonstration complete.\n");
}
