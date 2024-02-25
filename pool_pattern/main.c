#include <stdio.h>
#include <stdlib.h>

// Object structure (can be any type of object)
typedef struct {
    int id;
    // Additional fields specific to your object
} Object;

// Pool structure
typedef struct {
    Object** objects;
    int size;
    int capacity;
} ObjectPool;

// Function to initialize the object pool
void initObjectPool(ObjectPool* pool, int capacity) {
    pool->objects = (Object**)malloc(sizeof(Object*) * capacity);
    pool->size = 0;
    pool->capacity = capacity;

    // Create and add objects to the pool
    for (int i = 0; i < capacity; ++i) {
        Object* newObj = (Object*)malloc(sizeof(Object));
        newObj->id = i;
        pool->objects[i] = newObj;
        pool->size++;
    }
}

// Function to acquire an object from the pool
Object* acquireObject(ObjectPool* pool) {
    if (pool->size > 0) {
        Object* obj = pool->objects[--pool->size];
        printf("Acquired object with id %d\n", obj->id);
        return obj;
    } else {
        printf("Pool is empty. No object acquired.\n");
        return NULL;
    }
}

// Function to release an object back to the pool
void releaseObject(ObjectPool* pool, Object* obj) {
    if (pool->size < pool->capacity) {
        pool->objects[pool->size++] = obj;
        printf("Released object with id %d\n", obj->id);
    } else {
        printf("Pool is full. Cannot release more objects.\n");
    }
}

// Function to clean up the object pool
void cleanupObjectPool(ObjectPool* pool) {
    for (int i = 0; i < pool->size; ++i) {
        free(pool->objects[i]);
    }
    free(pool->objects);
    pool->size = 0;
    pool->capacity = 0;
}

int main() {
    // Create an object pool with a capacity of 5
    ObjectPool myPool;
    initObjectPool(&myPool, 5);

    // Acquire and release objects
    Object* obj1 = acquireObject(&myPool);
    Object* obj2 = acquireObject(&myPool);

    // Do some work with acquired objects...

    releaseObject(&myPool, obj1);
    releaseObject(&myPool, obj2);

    // Cleanup the object pool
    cleanupObjectPool(&myPool);

    return 0;
}
