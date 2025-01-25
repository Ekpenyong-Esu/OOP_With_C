//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_HISTOGRAMDISPLAY_H
#define CLIENT_SERVER_PATTERN_HISTOGRAMDISPLAY_H

#include "ECGPkg.h"
#include "TMDQueue.h"


/* class HistogramDisplay */
typedef struct HistogramDisplay HistogramDisplay;

struct HistogramDisplay {
    int index;
    struct TMDQueue* itsTMDQueue;
};

/* Constructors and destructors:*/

void HistogramDisplay_Init(HistogramDisplay* const self);
void HistogramDisplay_Cleanup(HistogramDisplay* const self);

/* Operations */

void HistogramDisplay_getValue(HistogramDisplay* const self);
void HistogramDisplay_updateHistogram(HistogramDisplay* const self);
struct TMDQueue* HistogramDisplay_getItsTMDQueue(const HistogramDisplay* const self);
void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const self, struct TMDQueue* p_TMDQueue);


HistogramDisplay * HistogramDisplay_Create(void);
void HistogramDisplay_Destroy(HistogramDisplay* const self);


#endif //CLIENT_SERVER_PATTERN_HISTOGRAMDISPLAY_H
