//
// Created by mahon on 2/8/2024.
//

#ifndef CCHANNELMODE_MOVINGAVERAGEFILTER_H
#define CCHANNELMODE_MOVINGAVERAGEFILTER_H

typedef struct MovingAverageFilter MovingAverageFilter;
struct MovingAverageFilter
{
    int computedFreq;
};

/* Constructors and destructors:*/
void MovingAverageFilter_Init(MovingAverageFilter* const me);
void MovingAverageFilter_Cleanup(MovingAverageFilter* const me);

/* Operations */

MovingAverageFilter * MovingAverageFilter_Create(void);
void MovingAverageFilter_Destroy(MovingAverageFilter* const me);

void MovingAverageFilter_setItsCalculateColor(MovingAverageFilter* const me, CalculateColor* const p_CalculateColor);

#endif //CCHANNELMODE_MOVINGAVERAGEFILTER_H
