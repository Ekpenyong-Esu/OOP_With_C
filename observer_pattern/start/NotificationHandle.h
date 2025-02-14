//
// Created by mahon on 12/31/2023.
//

#ifndef OBSERVER_PATTERN_NOTIFICATIONHANDLE_H
#define OBSERVER_PATTERN_NOTIFICATIONHANDLE_H


#include <stdio.h>
#include "ECGPkg.h"
#include "TMDQueue.h"

typedef struct NotificationHandle NotificationHandle;

struct NotificationHandle {
    UpdateFuncPtr updateAddr;
    struct NotificationHandle* itsNotificationHandle;
};

/* Constructors and destructors:*/
void NotificationHandle_Init(NotificationHandle* const me);
void NotificationHandle_Cleanup(NotificationHandle* const me);

struct NotificationHandle* NotificationHandle_getItsNotificationHandle(const NotificationHandle* const me);
void NotificationHandle_setItsNotificationHandle(NotificationHandle* const me, struct NotificationHandle* p_NotificationHandle);

NotificationHandle * NotificationHandle_Create(void);
void NotificationHandle_Destroy(NotificationHandle* const me);

#endif //OBSERVER_PATTERN_NOTIFICATIONHANDLE_H
