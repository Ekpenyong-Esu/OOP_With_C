#ifndef CRDISPLAY_H
#define CRDISPLAY_H

#include <stdbool.h>
#include <stdint.h>

// Forward declarations
typedef struct CRDisplay CRDisplay;

// Simple display structure
struct CRDisplay {
    bool isInitialized;
    uint32_t messageCount;
};

// Core display functions
CRDisplay* CRDisplay_Create(void);
void CRDisplay_Destroy(CRDisplay* me);

bool CRDisplay_printMsg(CRDisplay* me, const char* message);
bool CRDisplay_clear(CRDisplay* me);

#endif // CRDISPLAY_H