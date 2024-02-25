//
// Created by mahon on 12/17/2023.
//

#include "Queue.h"
#include <stdio.h>

int main()
{
    int j;
    int k;
    int h;
    int t;

    // test normal queue
    Queue* myQ;
    myQ = Queue_Create();
    k = 1000;

    for (j = 0; j <=QUEUE_SIZE; ++j)
    {
        h = myQ->head;
        myQ->insert(myQ, k);
        printf("inserting %d at position %d, size=%d\n", k, h, myQ->getSize(myQ));
        k--;
    }

    printf("inserted %d element\n", myQ->getSize(myQ));

    for (j = 0; j < QUEUE_SIZE; ++j)
    {
        t = myQ->tail;
        k = myQ->remove(myQ);
        printf("removing %d at position %d, size=%d\n", k, t, myQ->getSize(myQ));
    }
    printf("last item removed %d\n", k);
    printf("current Queue size %d\n", myQ->getSize(myQ));

    return 0;
}