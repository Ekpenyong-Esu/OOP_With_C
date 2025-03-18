//
// Created by mahon on 1/8/2024.
//

#ifndef BUTTON_DEBOUNCE_BUTTONDRIVER_H
#define BUTTON_DEBOUNCE_BUTTONDRIVER_H

/**
 * @brief Constants for button driver operations
 */
#define LOOPS_PER_MS     (1000)
#define DEBOUNCE_TIME    (40)    // Debounce time in milliseconds
#define BUTTON_OFF       (0)
#define BUTTON_ON        (1)

// Forward declarations
struct Button;
struct MicrowaveEmitter;
struct Timer;

/**
 * @brief ButtonDriver structure for handling button interactions
 */
typedef struct ButtonDriver ButtonDriver;
struct ButtonDriver {
    unsigned char oldState;   // Previous button state
    unsigned char toggleOn;   // Toggle state (ON/OFF)
    struct Button* itsButton; // Associated button
    struct MicrowaveEmitter* itsMicrowaveEmitter; // Controlled emitter
    struct Timer* itsTimer;   // Timer for debouncing
};

/**
 * @brief Initialize a ButtonDriver instance
 * @param me Pointer to the ButtonDriver instance
 */
void ButtonDriver_Init(ButtonDriver* const me);

/**
 * @brief Clean up ButtonDriver resources
 * @param me Pointer to the ButtonDriver instance
 */
void ButtonDriver_Cleanup(ButtonDriver* const me);

/**
 * @brief Process button events and handle device control
 * @param me Pointer to the ButtonDriver instance
 */
void ButtonDriver_eventReceive(ButtonDriver* const me);

/**
 * @brief Get the associated Button
 * @param me Pointer to the ButtonDriver instance
 * @return Pointer to the associated Button
 */
struct Button* ButtonDriver_getItsButton(const ButtonDriver* const me);

/**
 * @brief Set the associated Button with two-way relationship
 * @param me Pointer to the ButtonDriver instance
 * @param p_Button Pointer to the Button to associate
 */
void ButtonDriver_setItsButton(ButtonDriver* const me, struct Button* p_Button);

/**
 * @brief Get the associated MicrowaveEmitter
 * @param me Pointer to the ButtonDriver instance
 * @return Pointer to the associated MicrowaveEmitter
 */
struct MicrowaveEmitter* ButtonDriver_getItsMicrowaveEmitter(const ButtonDriver* const me);

/**
 * @brief Set the associated MicrowaveEmitter
 * @param me Pointer to the ButtonDriver instance
 * @param p_MicrowaveEmitter Pointer to the MicrowaveEmitter to associate
 */
void ButtonDriver_setItsMicrowaveEmitter(ButtonDriver* const me, struct MicrowaveEmitter* p_MicrowaveEmitter);

/**
 * @brief Get the associated Timer
 * @param me Pointer to the ButtonDriver instance
 * @return Pointer to the associated Timer
 */
struct Timer* ButtonDriver_getItsTimer(const ButtonDriver* const me);

/**
 * @brief Set the associated Timer
 * @param me Pointer to the ButtonDriver instance
 * @param p_Timer Pointer to the Timer to associate
 */
void ButtonDriver_setItsTimer(ButtonDriver* const me, struct Timer* p_Timer);

/**
 * @brief Create a new ButtonDriver instance
 * @return Pointer to the created ButtonDriver, NULL if creation failed
 */
ButtonDriver* ButtonDriver_Create(void);

/**
 * @brief Destroy a ButtonDriver instance and free its memory
 * @param me Pointer to the ButtonDriver instance
 */
void ButtonDriver_Destroy(ButtonDriver* const me);

/**
 * @brief Set the associated Button (internal method)
 * @param me Pointer to the ButtonDriver instance
 * @param p_Button Pointer to the Button to associate
 */
void ButtonDriver_setItsButton2(ButtonDriver* const me, struct Button* p_Button);

/**
 * @brief Set the associated Button with cleanup (internal method)
 * @param me Pointer to the ButtonDriver instance
 * @param p_Button Pointer to the Button to associate
 */
void ButtonDriver_setItsButton1(ButtonDriver* const me, struct Button* p_Button);

/**
 * @brief Clear the associated Button
 * @param me Pointer to the ButtonDriver instance
 */
void ButtonDriver_clearItsButton(ButtonDriver* const me);

#endif //BUTTON_DEBOUNCE_BUTTONDRIVER_H
