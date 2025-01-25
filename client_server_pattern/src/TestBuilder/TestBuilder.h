//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_TESTBUILDER_H
#define CLIENT_SERVER_PATTERN_TESTBUILDER_H

#include "ECGPkg.h"
#include "ECG_Module.h"
#include "HistogramDisplay.h"
#include "QRSDetector.h"
#include "TMDQueue.h"
#include "WaveformDisplay.h"
#include "ArrhythmiaDetector.h"



/* class TestBuilder */
typedef struct TestBuilder TestBuilder;
struct TestBuilder {
    struct ArrhythmiaDetector* itsArrythmiaDetector;
    struct ECG_Module* itsECG_Module;
    struct HistogramDisplay* itsHistogramDisplay;
    struct TMDQueue* itsTMDQueue;
    struct QRSDetector* itsQRSDetector;
    struct WaveformDisplay* itsWaveformDisplay;
};

/* Constructors and destructors:*/
void TestBuilder_Init(TestBuilder* const self);
void TestBuilder_Cleanup(TestBuilder* const self);

struct ArrythmiaDetector* TestBuilder_getItsArrythmiaDetector(const TestBuilder* const self);
struct QRSDetector* TestBuilder_getItsQRSDetector(const TestBuilder* const self);
struct ECG_Module* TestBuilder_getItsECG_Module(const TestBuilder* const self);
struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(const TestBuilder* const self);
struct TMDQueue* TestBuilder_getItsTMDQueue(const TestBuilder* const self);
struct WaveformDisplay* TestBuilder_getItsWaveformDisplay(const TestBuilder* const self);

TestBuilder * TestBuilder_Create(void);
void TestBuilder_Destroy(TestBuilder* const self);

#endif //CLIENT_SERVER_PATTERN_TESTBUILDER_H
