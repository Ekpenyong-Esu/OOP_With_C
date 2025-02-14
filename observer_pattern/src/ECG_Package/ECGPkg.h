//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_ECGPKG_H
#define CLIENT_SERVER_PATTERN_ECGPKG_H


/* forward declarations */

struct ArrhythmiaDetector;
struct ECG_Module;
struct HistogramDisplay;
struct QRSDetector;
struct TMDQueue;
struct TestBuilder;
struct TimeMarkedData;
struct WaveformDisplay;

typedef unsigned char boolean;
#define QUEUE_SIZE (20000)

#endif //CLIENT_SERVER_PATTERN_ECGPKG_H
