#include <stdio.h>
#include <stdlib.h>
#include "TestBuilder.h"
#include "ECG_Module.h"
#include "TMDQueue.h"
#include "HistogramDisplay.h"
#include "QRSDetector.h"
#include "ArrhythmiaDetector.h"

/**
 * Observer Pattern Demonstration Using TestBuilder
 *
 * This example shows the Observer pattern implementation with TestBuilder:
 * 1. TestBuilder creates and configures all components
 * 2. A subject (TMDQueue) maintains a list of observers
 * 3. Multiple observers register with the subject
 * 4. When data changes, the subject notifies all observers
 * 5. Each observer responds to the notification independently
 */
int main(int argc, char* argv[]) {
    printf("Observer Pattern Demonstration with TestBuilder\n");
    printf("==========================================\n\n");

    // Create all components using the TestBuilder
    printf("Creating components with TestBuilder...\n");
    TestBuilder* testBuilder = TestBuilder_Create();
    
    // Get references to all components
    TMDQueue* tmdQueue = TestBuilder_getItsTMDQueue(testBuilder);
    ECG_Module* ecgModule = TestBuilder_getItsECG_Module(testBuilder);
    HistogramDisplay* histogramDisplay = TestBuilder_getItsHistogramDisplay(testBuilder);
    WaveformDisplay* waveformDisplay = TestBuilder_getItsWaveformDisplay(testBuilder);
    QRSDetector* qrsDetector = TestBuilder_getItsQRSDetector(testBuilder);
    ArrhythmiaDetector* arrhythmiaDetector = TestBuilder_getItsArrythmiaDetector(testBuilder);
    
    printf("All components created and relationships established.\n");
    printf("\nThe following observers are currently subscribed to the subject:\n");
    printf("1. HistogramDisplay\n");
    printf("2. WaveFormDisplay\n");
    printf("3. QRSDetector\n");
    printf("4. ArrhythmiaDetector\n");
    
    // Generate data which will notify observers
    printf("\nGenerating data which will trigger notifications to all observers:\n");
    printf("--------------------------------------------------------\n");
    ECG_Module_acquireValue(ecgModule);
    
    printf("\nGenerating more data:\n");
    printf("-------------------\n");
    ECG_Module_acquireValue(ecgModule);
    
    // Unsubscribe two observers
    printf("\nUnsubscribing HistogramDisplay and QRSDetector...\n");
    TMDQueue_unsubscribe(tmdQueue, (UpdateFuncPtr)HistogramDisplay_update);
    TMDQueue_unsubscribe(tmdQueue, (UpdateFuncPtr)QRSDetector_update);
    
    // Generate more data (only the remaining observers will be notified)
    printf("\nGenerating more data (only WaveFormDisplay and ArrhythmiaDetector should be notified):\n");
    printf("------------------------------------------------------------------\n");
    ECG_Module_acquireValue(ecgModule);
    
    // Clean up all resources
    printf("\nCleaning up resources...\n");
    TestBuilder_Destroy(testBuilder);
    
    printf("\nObserver pattern demonstration complete.\n");
    return 0;
}
