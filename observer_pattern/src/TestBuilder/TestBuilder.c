//
// Created by mahon on 12/27/2023.
//
#include <stdlib.h>
#include "TestBuilder.h"

static void initRelations(TestBuilder* const self);
static void cleanUpRelations(TestBuilder* const self);

void TestBuilder_Init(TestBuilder* const self) {
    initRelations(self);
}

void TestBuilder_Cleanup(TestBuilder* const self) {
    cleanUpRelations(self);
}

struct ArrhythmiaDetector* TestBuilder_getItsArrythmiaDetector(const TestBuilder* const self){
return (struct ArrhythmiaDetector*)(self->itsArrhythmiaDetector);
}

struct ECG_Module* TestBuilder_getItsECG_Module(const TestBuilder* const self) {
    return (struct ECG_Module*)(self->itsECG_Module);
}

struct WaveformDisplay* TestBuilder_getItsWaveformDisplay(const TestBuilder* const self) {
    return (struct WaveformDisplay*)(self->itsWaveformDisplay);
}
struct QRSDetector* TestBuilder_getItsQRSDetector(const TestBuilder* const self) {
return (struct QRSDetector*)&(self->itsQRSDetector);
}

struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(const TestBuilder* const self) {
    return (struct HistogramDisplay*)(self->itsHistogramDisplay);
}

struct TMDQueue* TestBuilder_getItsTMDQueue(const TestBuilder* const self) {
    return (struct TMDQueue*)(self->itsTMDQueue);
}

TestBuilder * TestBuilder_Create(void) {
    TestBuilder* self = (TestBuilder *) malloc(sizeof(TestBuilder));
    if (self != NULL) {
        TestBuilder_Init(self);
    }
    return self;
}

void TestBuilder_Destroy(TestBuilder* const self) {
    if (self != NULL){
        TestBuilder_Cleanup(self);
    }
    free(self);
}

static void initRelations(TestBuilder* const self) {
    // Allocate memory for each component
    self->itsArrhythmiaDetector = (struct ArrhythmiaDetector*)malloc(sizeof(struct ArrhythmiaDetector));
    self->itsECG_Module = (struct ECG_Module*)malloc(sizeof(struct ECG_Module));
    self->itsHistogramDisplay = (struct HistogramDisplay*)malloc(sizeof(struct HistogramDisplay));
    self->itsQRSDetector = (struct QRSDetector*)malloc(sizeof(struct QRSDetector));
    self->itsTMDQueue = (struct TMDQueue*)malloc(sizeof(struct TMDQueue));
    self->itsWaveformDisplay = (struct WaveformDisplay*)malloc(sizeof(struct WaveformDisplay));

    // Check if any allocation failed
    if (!self->itsArrhythmiaDetector || !self->itsECG_Module || !self->itsHistogramDisplay ||
        !self->itsQRSDetector || !self->itsTMDQueue || !self->itsWaveformDisplay) {
        // Handle allocation failure
        cleanUpRelations(self);
        return;
    }

    // Initialize components
    ArrhythmiaDetector_Init(self->itsArrhythmiaDetector);
    ECG_Module_Init(self->itsECG_Module);
    HistogramDisplay_Init(self->itsHistogramDisplay);
    QRSDetector_Init(self->itsQRSDetector);
    TMDQueue_Init(self->itsTMDQueue);
    WaveformDisplay_Init(self->itsWaveformDisplay);

    // Set up relationships
    ECG_Module_setItsTMDQueue(self->itsECG_Module, self->itsTMDQueue);
    HistogramDisplay_setItsTMDQueue(self->itsHistogramDisplay, self->itsTMDQueue);
    QRSDetector_setItsTMDQueue(self->itsQRSDetector, self->itsTMDQueue);
    WaveformDisplay_setItsTMDQueue(self->itsWaveformDisplay, self->itsTMDQueue);
    ArrhythmiaDetector_setItsTMDQueue(self->itsArrhythmiaDetector, self->itsTMDQueue);
}

static void cleanUpRelations(TestBuilder* const self) {
    // First unsubscribe all observers from TMDQueue to avoid issues during cleanup
    if (self->itsTMDQueue) {
        if (self->itsHistogramDisplay) {
            TMDQueue_unsubscribe(self->itsTMDQueue, HistogramDisplay_update);
        }
        if (self->itsQRSDetector) {
            TMDQueue_unsubscribe(self->itsTMDQueue, QRSDetector_update);
        }
        if (self->itsWaveformDisplay) {
            TMDQueue_unsubscribe(self->itsTMDQueue, WaveformDisplay_update);
        }
        if (self->itsArrhythmiaDetector) {
            TMDQueue_unsubscribe(self->itsTMDQueue, ArrhythmiaDetector_update);
        }
    }
    
    // Clean up and free observers first
    if (self->itsArrhythmiaDetector) {
        ArrhythmiaDetector_Cleanup(self->itsArrhythmiaDetector);
        free(self->itsArrhythmiaDetector);
        self->itsArrhythmiaDetector = NULL;
    }
    if (self->itsQRSDetector) {
        QRSDetector_Cleanup(self->itsQRSDetector);
        free(self->itsQRSDetector);
        self->itsQRSDetector = NULL;
    }
    if (self->itsWaveformDisplay) {
        WaveformDisplay_Cleanup(self->itsWaveformDisplay);
        free(self->itsWaveformDisplay);
        self->itsWaveformDisplay = NULL;
    }
    if (self->itsHistogramDisplay) {
        HistogramDisplay_Cleanup(self->itsHistogramDisplay);
        free(self->itsHistogramDisplay);
        self->itsHistogramDisplay = NULL;
    }
    
    // Clean up ECG Module (data source)
    if (self->itsECG_Module) {
        ECG_Module_Cleanup(self->itsECG_Module);
        free(self->itsECG_Module);
        self->itsECG_Module = NULL;
    }
    
    // Finally clean up the TMDQueue (subject)
    if (self->itsTMDQueue) {
        TMDQueue_Cleanup(self->itsTMDQueue);
        free(self->itsTMDQueue);
        self->itsTMDQueue = NULL;
    }
}
