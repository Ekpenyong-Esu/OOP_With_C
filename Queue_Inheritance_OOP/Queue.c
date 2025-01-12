//
// Created by mahon on 12/10/2023.
//
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void Queue_Init(Queue* const me,
                int (*isFullFunc)(const Queue* const me),
                int (*isEmptyFunc)(const Queue* const me),
                int (*getSizeFunc)(const Queue* const me),
                void (*insertFunc)(Queue* const me, int k),
                int (*removeFunc)(Queue* const me)) {
                    
    assert(me != NULL);
    // initialize attributes
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    // initialize member function pointers
    me->isFull = isFullFunc;
    me->isEmpty = isEmptyFunc;
    me->getSize = getSizeFunc;
    me->insert = insertFunc;
    me->remove = removeFunc;
}

// operation cleanup
void Queue_Cleanup(const Queue* const me) {
    assert(me != NULL);
    printf("call Queue_Cleanup\n");
    printf("nothing to clean.\n");
}

// operation isFull
int Queue_isFull(const Queue* const me) {
    assert(me != NULL);
    return me->size == QUEUE_SIZE;
}

// operation isEmpty
int Queue_isEmpty(const Queue* const me) {
    assert(me != NULL);
    return me->size == 0;
}

// operation getSize
int Queue_getSize(const Queue* const me) {
    assert(me != NULL);
    return me->size;
}

// operation insert
void Queue_insert(Queue* const me, int k) {
    assert(me != NULL);
    if (!me->isFull(me)) {
        me->buffer[me->head] = k;
        me->head = (me->head + 1) % QUEUE_SIZE;  // incrase the head by 1 and modulus it by QUEUE_SIZE
        ++me->size;
    }
}

// operation remove
int Queue_remove(Queue* const me) {
    assert(me != NULL);
    int value = 0;
    if (!me->isEmpty(me)) {
        value = me->buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_SIZE;
        --me->size;
    }
    return value;
}

// operation create
Queue* Queue_Create(void) {
    Queue* me = (Queue*)malloc(sizeof(Queue));
    if (me != NULL) {
        Queue_Init(me, Queue_isFull, Queue_isEmpty, Queue_getSize, Queue_insert, Queue_remove);
    }
    return me;
}

// operation destroy
void Queue_Destroy(Queue* const me) {
    if (me != NULL) {
        Queue_Cleanup(me);
    }
    free(me);
}
