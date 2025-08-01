#include <stdlib.h>
#include "NotificationHandle.h"

/**
 * Observer Pattern: Observer Node Implementation
 * 
 * This file implements a node in the linked list of observers.
 * Each node contains a function pointer to an observer's update method.
 */

static void cleanUpRelations(NotificationHandle* const self);

/**
 * Initialize a notification handle
 */
void NotificationHandle_Init(NotificationHandle* const self) {
    self->itsNotificationHandle = NULL;
    self->updateAddr = NULL;
    self->observerInstance = NULL;
}

/**
 * Clean up a notification handle
 */
void NotificationHandle_Cleanup(NotificationHandle* const self) {
    cleanUpRelations(self);
}

/**
 * Get the next notification handle in the list
 */
struct NotificationHandle* NotificationHandle_getItsNotificationHandle(const NotificationHandle* const self) {
    return (struct NotificationHandle*)self->itsNotificationHandle;
}

/**
 * Set the next notification handle in the list
 */
void NotificationHandle_setItsNotificationHandle(NotificationHandle* const self, struct NotificationHandle* p_NotificationHandle) {
    self->itsNotificationHandle = p_NotificationHandle;
}

/**
 * Create a new notification handle
 */
NotificationHandle* NotificationHandle_Create(void) {
    NotificationHandle* self = (NotificationHandle*)malloc(sizeof(NotificationHandle));
    if (self != NULL) {
        NotificationHandle_Init(self);
    }
    return self;
}

/**
 * Destroy a notification handle
 */
void NotificationHandle_Destroy(NotificationHandle* const self) {
    if (self != NULL) {
        NotificationHandle_Cleanup(self);
        free(self);
    }
}

/**
 * Clean up related objects
 */
static void cleanUpRelations(NotificationHandle* const self) {
    if (self->itsNotificationHandle != NULL) {
        self->itsNotificationHandle = NULL;
    }
}
