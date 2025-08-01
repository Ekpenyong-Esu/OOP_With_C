#ifndef NotificationHandle_H
#define NotificationHandle_H

#include "ECGPkg.h"

/**
 * Observer Pattern: Observer Reference Management
 * 
 * This structure manages observers in the Observer pattern.
 * It holds a function pointer to the observer's update method
 * and forms a linked list of observers.
 */
typedef struct NotificationHandle NotificationHandle;

/* Forward declaration of function pointer type for observer's update method */
typedef void (*UpdateFuncPtr)(void* observer, const struct TimeMarkedData tmd);

struct NotificationHandle {
    UpdateFuncPtr updateAddr;                     // Function pointer to observer's update method
    void* observerInstance;                       // Pointer to the observer object
    struct NotificationHandle* itsNotificationHandle; // Next observer in the list
};

/* Constructors and destructors */
void NotificationHandle_Init(NotificationHandle* const me);
void NotificationHandle_Cleanup(NotificationHandle* const me);

/* Linked list operations */
struct NotificationHandle* NotificationHandle_getItsNotificationHandle(const NotificationHandle* const me);
void NotificationHandle_setItsNotificationHandle(NotificationHandle* const me, struct NotificationHandle* p_NotificationHandle);

/* Creation and destruction */
NotificationHandle* NotificationHandle_Create(void);
void NotificationHandle_Destroy(NotificationHandle* const me);

#endif
