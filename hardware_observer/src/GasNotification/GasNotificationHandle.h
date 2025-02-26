//
// Created by mahon on 1/8/2024.
//

#ifndef UNTITLED_GASNOTIFICATIONHANDLE_H
#define UNTITLED_GASNOTIFICATIONHANDLE_H


#include "GasData.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct GasNotificationHandle GasNotificationHandle;
struct GasNotificationHandle
{
    void (*acceptorPtr)(void *, struct GasData*);
    void* instancePtr;
};

void GasNotificationHandle_Init(GasNotificationHandle* const me);
void GasNotificationHandle_Cleanup(GasNotificationHandle* const me);

GasNotificationHandle * GasNotificationHandle_Create(void);
void GasNotificationHandle_Destroy(GasNotificationHandle* const me);

#endif //UNTITLED_GASNOTIFICATIONHANDLE_H
