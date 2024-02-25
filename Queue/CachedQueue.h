//
// Created by mahon on 12/17/2023.
// Polymorphism in C
//

#ifndef QUEUE_CACHEDQUEUE_H
#define QUEUE_CACHEDQUEUE_H


#include "Queue.h"

typedef struct CachedQueue CachedQueue;
struct CachedQueue
{
    Queue* queue; //base class

    char filename[80];

    int numberElementsOnDisk;
    Queue* outputQueue;

    // inherited vitual functions
    int (*isFull)(const CachedQueue* const me);
    int (*isEmpty)(const CachedQueue* const me);
    int (*getSize)(const CachedQueue* const me);
    void (*insert)(CachedQueue* const me, int k);
    int (*remove)(CachedQueue* const me);
    //new virtual functions
    void (*flush)(CachedQueue* const me);
    void (*load)(CachedQueue* const me);
};

// constructions and destructions
void CachedQueue_Init(CachedQueue* const me,
                      char* fName,
                      int (*isFullFunc)(const CachedQueue* const me),
                      int (*isEmptyFunc)(const CachedQueue* const me),
                      int (*getSizeFunc)(const CachedQueue* const me),
                      void (*insertFunc)(CachedQueue* const me, int k),
                      int (*removeFunc)(CachedQueue* const me),
                      void (*flushFunc)(CachedQueue* const me),
                      void (*loadFunc)(CachedQueue* const me) );

void CachedQueue_Cleanup(const CachedQueue* const me);

// operations
int CachedQueue_isFull(const CachedQueue* const me);
int CachedQueue_isEmpty(const CachedQueue* const me);
int CachedQueue_getSize(const CachedQueue* const me);
void CachedQueue_insert(CachedQueue* const me, int k);
int CachedQueue_remove(CachedQueue* const me);
void CachedQueue_flush(CachedQueue* const me);
void CachedQueue_load(CachedQueue* const me);

CachedQueue* CachedQueue_Create(void);
void CachedQueue_Destroy(CachedQueue* const me);

#endif //QUEUE_CACHEDQUEUE_H
