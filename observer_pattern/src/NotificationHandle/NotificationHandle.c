#include <stdlib.h>
#include "NotificationHandle.h"

static void cleanUpRelations(NotificationHandle* const self);

void NotificationHandle_Init(NotificationHandle* const self) {
    self->itsNotificationHandle = NULL;
}

void NotificationHandle_Cleanup(NotificationHandle* const self) {
    cleanUpRelations(self);
}

struct NotificationHandle* NotificationHandle_getItsNotificationHandle(const NotificationHandle* const self) {
    return (struct NotificationHandle*)self->itsNotificationHandle;
}

void NotificationHandle_setItsNotificationHandle(NotificationHandle* const self, struct NotificationHandle* p_NotificationHandle) {
    self->itsNotificationHandle = p_NotificationHandle;
}

NotificationHandle * NotificationHandle_Create(void) {
    NotificationHandle* self = (NotificationHandle *) malloc(sizeof(NotificationHandle));
    if(self!=NULL)
    {
        NotificationHandle_Init(self);
    }
    return self;
}

void NotificationHandle_Destroy(NotificationHandle* const self) {
    if(self!=NULL)
    {
        NotificationHandle_Cleanup(self);
    }
    free(self);
}

static void cleanUpRelations(NotificationHandle* const self) {
    if(self->itsNotificationHandle != NULL)
    {
        self->itsNotificationHandle = NULL;
    }
}
