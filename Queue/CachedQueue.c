//
// Created by mahon on 12/17/2023.
//
#include "CachedQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void CachedQueue_Init(CachedQueue* const me,
                      char* fName,
                      int (*isFullFunc)(const CachedQueue* const me),
                      int (*isEmptyFunc)(const CachedQueue* const me),
                      int (*getSizeFunc)(const CachedQueue* const me),
                      void (*insertFunc)(CachedQueue* const me, int k),
                      int (*removeFunc)(CachedQueue* const me),
                      void (*flushFunc)(CachedQueue* const me),
                      void (*loadFunc)(CachedQueue* const me) ) {
    // initialize base class
    me->queue = Queue_Create();     // queue member must use its original functions

    // initialize subclass attributes
    me->numberElementsOnDisk = 0;

    strcpy(me->filename, fName);

    // initialize aggregates
    me->outputQueue = Queue_Create();

    // initialize subclass virtual operations ptrs
    me->isFull = isFullFunc;
    me->isEmpty = isEmptyFunc;
    me->getSize = getSizeFunc;
    me->insert = insertFunc;
    me->remove = removeFunc;
    me->flush = flushFunc;
    me->load = loadFunc;
}

// operation cleanup
void CachedQueue_Cleanup(const CachedQueue* const me) {
    Queue_Cleanup(me->queue);
    Queue_Cleanup(me->outputQueue);
}

// operation isFull
int CachedQueue_isFull(const CachedQueue* const me) {
    return me->queue->isFull(me->queue) && me->outputQueue->isFull(me->outputQueue);
}

// operation isEmpty
int CachedQueue_isEmpty(const CachedQueue* const me) {
    return me->queue->isEmpty(me->queue) && me->outputQueue->isEmpty(me->outputQueue) && me->numberElementsOnDisk == 0;
}

// operation getSize
int CachedQueue_getSize(const CachedQueue* const me) {
    return me->queue->getSize(me->queue) + me->outputQueue->getSize(me->outputQueue) + me->numberElementsOnDisk;
}

// operation insert
void CachedQueue_insert(CachedQueue* const me, int k){
    if (me->queue->isFull(me->queue))
    {
        me->flush(me);
    }
    me->queue->insert(me->queue, k);
}


// operation remove
int CachedQueue_remove(CachedQueue* const me){
    if (!me->outputQueue->isEmpty(me->outputQueue))
    {
        return me->outputQueue->remove(me->outputQueue);
    }
    else if (me->numberElementsOnDisk > 0)
    {
        me->load(me);
        return me->queue->remove(me->queue);
    }
    else
    {
        return me->queue->remove(me->queue);
    }
}
// operation flush
void CachedQueue_flush(CachedQueue* const me) {
    printf("flush data to disk\n");
    int value1 = 0;
    int value2 = 0;

    while((!me->queue->isEmpty(me->queue)) && (!me->outputQueue->isFull(me->outputQueue))) {
        value1 = me->queue->remove(me->queue);
        me->outputQueue->insert(me->outputQueue, value1);

        if (me->outputQueue->isFull(me->outputQueue)) {
            FILE* fp = fopen("test.dat", "w+");
            while(!me->outputQueue->isEmpty(me->queue)) {
                value2 = me->queue->remove(me->queue);
                fwrite(&value2, sizeof(int), 1, fp);
            }
            fclose(fp);
        }
    }
}

// operation load
void CachedQueue_load(CachedQueue* const me) {
    printf("load data to queue\n");
    FILE* fp = fopen("test.dat", "r");  // Changed "w+" to "r" for reading
    int value = 0;

    while(!me->queue->isFull(me->queue)) {
        fread(&value, sizeof(int), 1, fp);
        me->queue->insert(me->queue, value);
    }
    fclose(fp);
}

// operation create
CachedQueue* CachedQueue_Create(void) {
    CachedQueue* me = (CachedQueue*)malloc(sizeof(CachedQueue));
    if (me != NULL) {
        CachedQueue_Init(me, "/home/yang/test.txt",
                         CachedQueue_isFull, CachedQueue_isEmpty,
                         CachedQueue_getSize, CachedQueue_insert,
                         CachedQueue_remove, CachedQueue_flush,
                         CachedQueue_load);
    }
    return me;
}

// operation destroy
void CachedQueue_Destroy(CachedQueue* const me) {
    if (me != NULL) {
        CachedQueue_Cleanup(me);
    }
    free(me);
}
