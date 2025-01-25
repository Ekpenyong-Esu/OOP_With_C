//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_WAVEFORMDISPLAY_H
#define CLIENT_SERVER_PATTERN_WAVEFORMDISPLAY_H


#include "ECGPkg.h"
#include "TMDQueue.h"
#include "TimeMarkedData.h"


typedef struct WaveformDisplay WaveformDisplay;
struct WaveformDisplay
{
    int index;
    struct TMDQueue* itsTMDQueue;
};

void WaveformDisplay_Init(WaveformDisplay* const me);
void WaveformDisplay_Cleanup(WaveformDisplay* const me);

void WaveformDisplay_getScalarValue(WaveformDisplay* const me);
void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const me, struct TMDQueue* p_TMDQueue);

WaveformDisplay* WaveformDisplay_Create(void);
WaveformDisplay* WaveformDisplay_Destroy(WaveformDisplay* const me);

#endif //CLIENT_SERVER_PATTERN_WAVEFORMDISPLAY_H
