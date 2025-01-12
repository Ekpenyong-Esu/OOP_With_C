#include <stdio.h>
#include "CachedQueue.h"

int main() {
    // Create a CachedQueue
    CachedQueue* myQueue = CachedQueue_Create();
    if (myQueue == NULL) {
        printf("Failed to create CachedQueue\n");
        return -1;
    }

    // Insert elements into the CachedQueue
    for (int i = 0; i < 100; ++i) {
        myQueue->insert(myQueue, i);
    }

    // Flush the queue to disk
    myQueue->flush(myQueue);

    // Load the queue from disk
    myQueue->load(myQueue);

    // Remove elements from the CachedQueue
    while (!myQueue->isEmpty(myQueue)) {
        int value = myQueue->remove(myQueue);
        printf("Removed value: %d\n", value);
    }

    // Destroy the CachedQueue
    CachedQueue_Destroy(myQueue);

    return 0;
}