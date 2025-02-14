//
// Created by mahon on 12/31/2023.
//

#ifndef OBSERVER_PATTERN_HISTOGRAMDISPLAY_H
#define OBSERVER_PATTERN_HISTOGRAMDISPLAY_H


#include "ECGPkg.h"

struct TMDQueue;

/* class HistogramDisplay */
typedef struct HistogramDisplay HistogramDisplay;
struct HistogramDisplay {
    int index;
    struct TMDQueue* itsTMDQueue;
};

/* Constructors and destructors:*/
void HistogramDisplay_Init(HistogramDisplay* const me);
void HistogramDisplay_Cleanup(HistogramDisplay* const me);

/* Operations */
void HistogramDisplay_getValue(HistogramDisplay* const me);
void HistogramDisplay_updateHistogram(HistogramDisplay* const me);
struct TMDQueue* HistogramDisplay_getItsTMDQueue(const HistogramDisplay* const me);
void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const me, struct TMDQueue* p_TMDQueue);

HistogramDisplay * HistogramDisplay_Create(void);
void HistogramDisplay_Destroy(HistogramDisplay* const me);

#endif //OBSERVER_PATTERN_HISTOGRAMDISPLAY_H
