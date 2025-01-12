//
// Created by mahon on 12/10/2023.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#define QUEUE_SIZE 10

typedef struct Queue Queue; // forward declaration of the Queue struct
struct Queue
{
    int buffer[QUEUE_SIZE];     // where the data things are
    int head;                 // index to the oldest item
    int size;              // how many items in the queue
    int tail;
    int (*isFull)(const Queue* const me);     // function pointer to isFull function
    int (*isEmpty)(const Queue* const me);        // function pointer to isEmpty function
    int (*getSize)(const Queue* const me);    // function pointer to getSize function
    void (*insert)(Queue* const me, int k);  // function pointer to insert function
    int (*remove)(Queue* const me);     // function pointer to remove function
};

// constructions and destructor
void Queue_Init(Queue* const me,
                int (*isFullFunc)(const Queue* const me),
                int (*isEmptyFunc)(const Queue* const me),
                int (*getSizeFunc)(const Queue* const me),
                void (*insertFunc)(Queue* const me, int k),
                int (*removeFunc)(Queue* const me));


void Queue_Cleanup(const Queue* const me);

//  operations
int Queue_isFull(const Queue* const me);
int Queue_isEmpty(const Queue* const me);
int Queue_getSize(const Queue* const me);
void Queue_insert(Queue* const me, int k);
int Queue_remove(Queue* const me);

Queue* Queue_Create(void);
void Queue_Destroy(Queue* const me);

#endif //QUEUE_QUEUE_H
