//
// Created by mahon on 2/8/2024.
//

#ifndef CCHANNELMODE_CONVERTTOFREQUENCY_H
#define CCHANNELMODE_CONVERTTOFREQUENCY_H

typedef struct ConvertToFrequency ConvertToFrequency;
struct ConvertToFrequency
{

};

/* Constructors and destructors:*/
void ConvertToFrequency_Init(ConvertToFrequency* const me);
void ConvertToFrequency_Cleanup(ConvertToFrequency* const me);

/* Operations */

ConvertToFrequency * ConvertToFrequency_Create(void);
void ConvertToFrequency_Destroy(ConvertToFrequency* const me);

void ConvertToFrequency_setItsMovingAverageFilter(ConvertToFrequency* const me, MovingAverageFilter* const p_MovingAverageFilter);

#endif //CCHANNELMODE_CONVERTTOFREQUENCY_H
