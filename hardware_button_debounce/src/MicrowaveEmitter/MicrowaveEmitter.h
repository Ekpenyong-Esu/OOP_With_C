//
// Created by mahon on 1/8/2024.
//

#ifndef BUTTON_DEBOUNCE_MICROWAVEEMITTER_H
#define BUTTON_DEBOUNCE_MICROWAVEEMITTER_H

/**
 * @brief Device states for the microwave emitter
 */
#define EMITTER_OFF  0
#define EMITTER_ON   1

/**
 * @brief MicrowaveEmitter structure for controlling emission functionality
 */
typedef struct MicrowaveEmitter MicrowaveEmitter;
struct MicrowaveEmitter
{
    int deviceState;  // Current state of the emitter (EMITTER_OFF or EMITTER_ON)
};

/**
 * @brief Initialize a MicrowaveEmitter instance
 * @param me Pointer to the MicrowaveEmitter instance
 */
void MicrowaveEmitter_Init(MicrowaveEmitter* const me);

/**
 * @brief Clean up MicrowaveEmitter resources
 * @param me Pointer to the MicrowaveEmitter instance
 */
void MicrowaveEmitter_Cleanup(MicrowaveEmitter* const me);

/**
 * @brief Create a new MicrowaveEmitter instance
 * @return Pointer to the created MicrowaveEmitter, NULL if creation failed
 */
MicrowaveEmitter* MicrowaveEmitter_Create(void);

/**
 * @brief Destroy a MicrowaveEmitter instance and free its memory
 * @param me Pointer to the MicrowaveEmitter instance
 */
void MicrowaveEmitter_Destroy(MicrowaveEmitter* const me);

/**
 * @brief Start emitting microwaves
 * @param me Pointer to the MicrowaveEmitter instance
 */
void MicrowaveEmitter_startEmitting(MicrowaveEmitter* const me);

/**
 * @brief Stop emitting microwaves
 * @param me Pointer to the MicrowaveEmitter instance
 */
void MicrowaveEmitter_stopEmitting(MicrowaveEmitter* const me);

#endif //BUTTON_DEBOUNCE_MICROWAVEEMITTER_H
