# Observer Pattern Implementation in C

This directory contains a complete implementation of the Observer pattern in C, demonstrated through an ECG (Electrocardiogram) data processing system. The implementation follows clean, maintainable design principles and showcases how to implement object-oriented patterns in C.

## 📋 Table of Contents

- [Architecture Overview](#architecture-overview)
- [Component Structure](#component-structure)
- [Observer Pattern Implementation](#observer-pattern-implementation)
- [Data Flow](#data-flow)
- [Component Relationships](#component-relationships)
- [Usage Examples](#usage-examples)
- [Building and Running](#building-and-running)
- [Testing](#testing)

## 🏗️ Architecture Overview

The system implements the classic Observer pattern with the following roles:

- **Subject**: `TMDQueue` - Maintains a list of observers and notifies them of data changes
- **Observers**: `WaveformDisplay`, `HistogramDisplay`, `QRSDetector`, `ArrhythmiaDetector`
- **Data Source**: `ECG_Module` - Generates ECG data and sends it to the subject
- **Observer Management**: `NotificationHandle` - Manages the observer list as a linked list
- **Data Container**: `TimeMarkedData` - Encapsulates timestamped ECG data
- **Factory**: `TestBuilder` - Creates and wires all components together

```
┌─────────────┐    generates    ┌─────────────┐    notifies     ┌─────────────────┐
│ ECG_Module  │ ───────────────► │  TMDQueue   │ ──────────────► │    Observers    │
│             │                 │  (Subject)  │                 │                 │
└─────────────┘                 └─────────────┘                 │ • WaveformDisplay│
                                       │                        │ • HistogramDisplay│
                                       │                        │ • QRSDetector    │
                                       │                        │ • ArrhythmiaDetector│
                                       ▼                        └─────────────────┘
                              ┌─────────────────┐
                              │NotificationHandle│
                              │  (Observer List) │
                              └─────────────────┘
```

## 📁 Component Structure

### Core Observer Pattern Components

#### 1. **TMDQueue** (`TMDQueue/`)
**Role**: Subject in the Observer pattern
- Maintains a circular buffer of ECG data
- Manages a linked list of observers via `NotificationHandle`
- Notifies all observers when new data arrives
- Provides subscription/unsubscription methods

```c
struct TMDQueue {
    int head;                                   // Current position in circular buffer
    int nSubscribers;                           // Number of observers
    int size;                                   // Current size of data in buffer
    struct TimeMarkedData buffer[QUEUE_SIZE];   // Circular buffer of data
    struct NotificationHandle* itsNotificationHandle; // Linked list of observers
};
```

**Key Methods**:
- `TMDQueue_subscribe()` - Register an observer
- `TMDQueue_unsubscribe()` - Remove an observer
- `TMDQueue_notify()` - Notify all observers
- `TMDQueue_insert()` - Add data and trigger notifications

#### 2. **NotificationHandle** (`NotificationHandle/`)
**Role**: Observer list management
- Manages observers as a linked list
- Stores function pointers to observer update methods
- Stores references to observer instances

```c
struct NotificationHandle {
    UpdateFuncPtr updateAddr;                     // Function pointer to observer's update method
    void* observerInstance;                       // Pointer to the observer object
    struct NotificationHandle* itsNotificationHandle; // Next observer in the list
};
```

#### 3. **TimeMarkedData** (`TimeMarkedData/`)
**Role**: Data container
- Encapsulates ECG data with timestamps
- Provides data structure for observer notifications

```c
struct TimeMarkedData {
    long timeInterval;  // Timestamp
    int dataValue;      // ECG data value
    // Additional fields for complete ECG data
};
```

### Observer Implementations

#### 4. **WaveformDisplay** (`WaveFormDisplay/`)
**Role**: Concrete Observer
- Displays ECG waveform data
- Updates display when notified by subject

#### 5. **HistogramDisplay** (`HistogramDisplay/`)
**Role**: Concrete Observer
- Creates histogram analysis of ECG data
- Maintains statistical data about ECG signals

#### 6. **QRSDetector** (`QRSDetector/`)
**Role**: Concrete Observer
- Detects QRS complexes in ECG data
- Performs real-time cardiac rhythm analysis

#### 7. **ArrhythmiaDetector** (`ArrhythmiaDetector/`)
**Role**: Concrete Observer
- Detects cardiac arrhythmias
- Provides alerts for abnormal heart rhythms

### Supporting Components

#### 8. **ECG_Module** (`ECG_Module/`)
**Role**: Data Source
- Generates simulated ECG data
- Sends data to the TMDQueue subject
- Controls data generation timing

#### 9. **TestBuilder** (`TestBuilder/`)
**Role**: Factory Pattern
- Creates and initializes all system components
- Wires components together
- Provides clean system setup and teardown

#### 10. **ECG_Package** (`ECG_Package/`)
**Role**: Common definitions
- Contains shared constants and type definitions
- Provides system-wide configuration

## 🔄 Observer Pattern Implementation

### Observer Interface

All observers implement a consistent update interface:

```c
typedef void (*UpdateFuncPtr)(void* observer, const struct TimeMarkedData tmd);
```

### Subscription Process

1. **Observer Registration**:
   ```c
   TMDQueue_subscribe(subject, observerInstance, observerUpdateFunction);
   ```

2. **Notification Handle Creation**:
   - `TMDQueue` creates a `NotificationHandle` for each observer
   - Stores both the update function pointer and observer instance
   - Links into the observer list

3. **Notification Process**:
   ```c
   void TMDQueue_notify(TMDQueue* const me, const struct TimeMarkedData tmd) {
       struct NotificationHandle *current = me->itsNotificationHandle;
       while (current != NULL) {
           current->updateAddr(current->observerInstance, tmd);
           current = current->itsNotificationHandle;
       }
   }
   ```

### Observer Update Methods

Each observer implements its update method with the standard signature:

```c
// WaveformDisplay
void WaveformDisplay_update(void* instance, const struct TimeMarkedData tmd);

// HistogramDisplay  
void HistogramDisplay_update(void* instance, const struct TimeMarkedData tmd);

// QRSDetector
void QRSDetector_update(void* instance, const struct TimeMarkedData tmd);

// ArrhythmiaDetector
void ArrhythmiaDetector_update(void* instance, const struct TimeMarkedData tmd);
```

## 🔄 Data Flow

### Complete Data Processing Pipeline

```
1. ECG_Module generates data
   ↓
2. ECG_Module calls TMDQueue_insert()
   ↓
3. TMDQueue stores data in circular buffer
   ↓
4. TMDQueue calls TMDQueue_notify()
   ↓
5. TMDQueue iterates through NotificationHandle list
   ↓
6. Each observer's update method is called
   ↓
7. Observers process data independently:
   • WaveformDisplay updates visual display
   • HistogramDisplay updates statistical analysis
   • QRSDetector analyzes for QRS complexes
   • ArrhythmiaDetector checks for abnormalities
```

### Detailed Flow Example

```c
// 1. ECG Module generates data
TimeMarkedData ecgData = {
    .timeInterval = getCurrentTime(),
    .dataValue = generateECGSample()
};

// 2. Data sent to subject
TMDQueue_insert(tmdQueue, ecgData);

// 3. Inside TMDQueue_insert():
//    - Data stored in circular buffer
//    - TMDQueue_notify() called

// 4. Inside TMDQueue_notify():
//    - Iterate through observer list
//    - Call each observer's update method

// 5. Each observer processes independently:
WaveformDisplay_update(waveformInstance, ecgData);   // Updates display
HistogramDisplay_update(histogramInstance, ecgData); // Updates statistics
QRSDetector_update(qrsInstance, ecgData);           // Detects QRS complexes
ArrhythmiaDetector_update(arrhythmiaInstance, ecgData); // Checks for arrhythmias
```

## 🔗 Component Relationships

### Dependency Graph

```
ECG_Module
    ├── depends on: TMDQueue, TimeMarkedData
    └── creates: ECG data

TMDQueue (Subject)
    ├── depends on: NotificationHandle, TimeMarkedData
    ├── manages: Observer list
    └── notifies: All registered observers

NotificationHandle
    ├── depends on: Observer instances
    └── manages: Observer references and function pointers

Observers (WaveformDisplay, HistogramDisplay, QRSDetector, ArrhythmiaDetector)
    ├── depend on: TimeMarkedData
    ├── register with: TMDQueue
    └── receive: Data notifications

TestBuilder
    ├── creates: All system components
    ├── wires: Component relationships
    └── manages: System lifecycle
```

### Memory Management

```
TestBuilder_Create()
    ├── Creates ECG_Module
    ├── Creates TMDQueue
    ├── Creates all Observers
    └── Registers observers with TMDQueue

TestBuilder_Destroy()
    ├── Unregisters all observers
    ├── Destroys all observers
    ├── Destroys TMDQueue
    └── Destroys ECG_Module
```

## 💡 Usage Examples

### Manual System Setup

```c
#include "TMDQueue.h"
#include "ECG_Module.h"
#include "WaveformDisplay.h"
#include "HistogramDisplay.h"
#include "QRSDetector.h"
#include "ArrhythmiaDetector.h"

int main() {
    // Create the subject
    TMDQueue* tmdQueue = TMDQueue_Create();
    
    // Create observers
    WaveformDisplay* waveform = WaveformDisplay_Create();
    HistogramDisplay* histogram = HistogramDisplay_Create();
    QRSDetector* qrsDetector = QRSDetector_Create();
    ArrhythmiaDetector* arrhythmiaDetector = ArrhythmiaDetector_Create();
    
    // Register observers with subject
    TMDQueue_subscribe(tmdQueue, waveform, WaveformDisplay_update);
    TMDQueue_subscribe(tmdQueue, histogram, HistogramDisplay_update);
    TMDQueue_subscribe(tmdQueue, qrsDetector, QRSDetector_update);
    TMDQueue_subscribe(tmdQueue, arrhythmiaDetector, ArrhythmiaDetector_update);
    
    // Create and configure data source
    ECG_Module* ecgModule = ECG_Module_Create();
    ECG_Module_setItsTMDQueue(ecgModule, tmdQueue);
    
    // Generate some data
    for (int i = 0; i < 10; i++) {
        ECG_Module_acquireValue(ecgModule);
    }
    
    // Cleanup
    ECG_Module_Destroy(ecgModule);
    ArrhythmiaDetector_Destroy(arrhythmiaDetector);
    QRSDetector_Destroy(qrsDetector);
    HistogramDisplay_Destroy(histogram);
    WaveformDisplay_Destroy(waveform);
    TMDQueue_Destroy(tmdQueue);
    
    return 0;
}
```

### Using TestBuilder (Recommended)

```c
#include "TestBuilder.h"

int main() {
    // Create entire system with one call
    TestBuilder* builder = TestBuilder_Create();
    
    // Generate data and demonstrate Observer pattern
    for (int i = 0; i < 10; i++) {
        TestBuilder_generateData(builder);
    }
    
    // Clean up everything
    TestBuilder_Destroy(builder);
    
    return 0;
}
```

## 🔧 Building and Running

### Prerequisites

- CMake 3.15 or higher
- C compiler (GCC, Clang, etc.)
- Make or Ninja build system

### Build Process

1. **Create build directory**:
   ```bash
   mkdir -p build
   cd build
   ```

2. **Configure with CMake**:
   ```bash
   cmake ..
   ```

3. **Build the project**:
   ```bash
   make
   ```

4. **Run the application**:
   ```bash
   ./app/main
   ```

### Running Examples

The main application provides two demonstration modes:

1. **Manual Setup Demo**: Shows step-by-step Observer pattern construction
2. **TestBuilder Demo**: Shows factory pattern usage for system creation

## 🧪 Testing

### Unit Tests

Run the test suite to verify Observer pattern implementation:

```bash
cd build
make test
```

### Test Coverage

The tests verify:
- Observer registration and deregistration
- Notification delivery to all observers
- Data integrity through the pipeline
- Memory management and cleanup
- Component lifecycle management

## 🎯 Key Design Principles

### 1. **Separation of Concerns**
- Each component has a single, well-defined responsibility
- Observers are independent and can be added/removed without affecting others
- Subject doesn't know about specific observer implementations

### 2. **Loose Coupling**
- Observers only depend on the common update interface
- Subject communicates through function pointers, not direct references
- Components can be easily swapped or extended

### 3. **Extensibility**
- New observers can be added by implementing the UpdateFuncPtr interface
- System supports dynamic observer registration/deregistration
- TestBuilder pattern makes it easy to configure different system setups

### 4. **Memory Safety**
- Proper initialization and cleanup for all components
- Clear ownership and lifecycle management
- No memory leaks in normal operation

### 5. **C Best Practices**
- Consistent naming conventions
- Proper header organization
- Clear function signatures
- Comprehensive documentation

## 🔍 Advanced Features

### Dynamic Observer Management
- Observers can be added and removed at runtime
- System handles observer list management automatically
- No limit on number of observers (within memory constraints)

### Circular Buffer Implementation
- Efficient storage of ECG data stream
- Automatic overwrite of old data
- Multiple observers can read the same data

### Type Safety
- Function pointer types ensure correct observer interfaces
- Compile-time checking of observer method signatures
- Clear separation between observer instances and update methods

---

This Observer pattern implementation demonstrates how to create maintainable, extensible object-oriented designs in C while following best practices for memory management and component organization.
