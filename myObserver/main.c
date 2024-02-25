#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the observer structure
struct Observer;

// Function pointer type for the update function
typedef void (*UpdateFunc)(struct Observer*);

// Subject structure
struct Subject {
    int state;
    struct Observer** observers;
    size_t numObservers;
};

// Observer structure
struct Observer {
    UpdateFunc update;
};

// Function to create a new observer
struct Observer* createObserver(UpdateFunc update) {
    struct Observer* observer = (struct Observer*)malloc(sizeof(struct Observer));
    observer->update = update;
    return observer;
}

// Function to create a new subject
struct Subject* createSubject(int initialState) {
    struct Subject* subject = (struct Subject*)malloc(sizeof(struct Subject));
    subject->state = initialState;
    subject->observers = NULL;
    subject->numObservers = 0;
    return subject;   // return the address of the newly created subject
}

// Function to attach an observer to a subject
void attachObserver(struct Subject* subject, struct Observer* observer) {
    subject->observers = realloc(subject->observers, (subject->numObservers + 1) * sizeof(struct Observer*));
    subject->observers[subject->numObservers++] = observer;
}

// Function to notify all observers about a state change
void notifyObservers(struct Subject* subject) {
    for (size_t i = 0; i < subject->numObservers; ++i) {
        subject->observers[i]->update(subject->observers[i]);
    }
}

// Function to update the state of the subject
void setState(struct Subject* subject, int newState) {
    subject->state = newState;
    notifyObservers(subject);
}

// Sample update function for an observer
void sampleUpdate(struct Observer* observer) {
    printf("Observer updated!\n");
}

int main() {
    // Create a subject and observers
    struct Subject* subject = createSubject(0);
    struct Observer* observer1 = createObserver(sampleUpdate);
    struct Observer* observer2 = createObserver(sampleUpdate);

    // Attach observers to the subject
    attachObserver(subject, observer1);
    attachObserver(subject, observer2);

    // Update the state of the subject, which will notify the observers
    setState(subject, 42);

    // Clean up
    free(observer1);
    free(observer2);
    free(subject->observers);
    free(subject);

    return 0;
}
