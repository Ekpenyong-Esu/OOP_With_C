//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_ECGPKG_H
#define CLIENT_SERVER_PATTERN_ECGPKG_H

/**
 * Observer Pattern: Common Definitions
 *
 * This file provides common definitions and forward declarations for
 * the Observer pattern implementation in the ECG system.
 */

/* Forward declarations for Observer pattern components */
struct ArrhythmiaDetector;  // Observer
struct ECG_Module;          // Data provider
struct HistogramDisplay;    // Observer
struct QRSDetector;         // Observer
struct TMDQueue;            // Subject
struct TestBuilder;         // Test framework
struct TimeMarkedData;      // Subject state
struct WaveformDisplay;     // Observer

/* Common type definitions */
typedef unsigned char boolean;

/* Configuration for Subject data storage */
#define QUEUE_SIZE (20000)   // Size of circular buffer in Subject

#endif //CLIENT_SERVER_PATTERN_ECGPKG_H
