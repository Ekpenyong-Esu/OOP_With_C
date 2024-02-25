//
// Created by mahon on 12/31/2023.
//

#ifndef OBSERVER_PATTERN_TESTBUILDER_H
#define OBSERVER_PATTERN_TESTBUILDER_H

#include <stdio.h>
#include "ECGPkg.h"
//#include "ArrhythmiaDetector.h"
#include "ECG_Module.h"
#include "HistogramDisplay.h"
//#include "QRSDetector.h"
#include "TMDQueue.h"
//#include "WaveformDisplay.h"

/* class TestBuilder */
typedef struct TestBuilder TestBuilder;

struct TestBuilder {
    // struct ArrhythmiaDetector itsArrhythmiaDetector;
    struct ECG_Module itsECG_Module;
    struct HistogramDisplay itsHistogramDisplay;
    // struct QRSDetector itsQRSDetector;
    struct TMDQueue itsTMDQueue;
    // struct WaveformDisplay itsWaveformDisplay;
};

/* Constructors and destructors:*/
void TestBuilder_Init(TestBuilder* const me);
void TestBuilder_Cleanup(TestBuilder* const me);

// struct ArrhythmiaDetector* TestBuilder_getItsArrhythmiaDetector(const TestBuilder* const me);
struct ECG_Module* TestBuilder_getItsECG_Module(const TestBuilder* const me);
struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(const TestBuilder* const me);
// struct QRSDetector* TestBuilder_getItsQRSDetector(const TestBuilder* const me);
struct TMDQueue* TestBuilder_getItsTMDQueue(const TestBuilder* const me);
// struct WaveformDisplay* TestBuilder_getItsWaveformDisplay(const TestBuilder* const me);

TestBuilder * TestBuilder_Create(void);
void TestBuilder_Destroy(TestBuilder* const me);


#endif //OBSERVER_PATTERN_TESTBUILDER_H
