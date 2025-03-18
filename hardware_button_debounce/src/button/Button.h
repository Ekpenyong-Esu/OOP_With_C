//
// Created by mahon on 1/8/2024.
//

#ifndef BUTTON_DEBOUNCE_BUTTON_H
#define BUTTON_DEBOUNCE_BUTTON_H

// Forward declaration
struct ButtonDriver;

/**
 * @brief Button states
 */
#define BUTTON_STATE_RELEASED  0
#define BUTTON_STATE_PRESSED   1

/**
 * @brief Button structure for hardware button interface
 */
typedef struct Button Button;
struct Button
{
    int deviceState;  // Current physical state (PRESSED/RELEASED)
    int backlight;    // Backlight state (ON/OFF)
    struct ButtonDriver* buttonDriver;  // Associated driver
};

/**
 * @brief Initialize a Button instance
 * @param me Pointer to the Button instance
 */
void Button_Init(Button* const me);

/**
 * @brief Clean up Button resources
 * @param me Pointer to the Button instance
 */
void Button_Cleanup(Button* const me);

/**
 * @brief Create a new Button instance
 * @return Pointer to the created Button, NULL if creation failed
 */
Button* Button_Create(void);

/**
 * @brief Destroy a Button instance and free its memory
 * @param me Pointer to the Button instance
 */
void Button_Destroy(Button* const me);

/**
 * @brief Control button backlight
 * @param me Pointer to the Button instance
 * @param light Backlight state (1=ON, 0=OFF)
 */
void Button_backlight(Button* const me, int light);

/**
 * @brief Get current button state
 * @param me Pointer to the Button instance
 * @return Current button state (1=PRESSED, 0=RELEASED)
 */
int Button_getState(Button* const me);

/**
 * @brief Set the associated ButtonDriver
 * @param me Pointer to the Button instance
 * @param buttonDriver Pointer to the ButtonDriver to associate
 */
void Button_setItsButtonDriver(Button* const me, struct ButtonDriver* const buttonDriver);

/**
 * @brief Get the associated ButtonDriver
 * @param me Pointer to the Button instance
 * @return Pointer to the associated ButtonDriver
 */
struct ButtonDriver* Button_getItsButtonDriver(Button* const me);

#endif //BUTTON_DEBOUNCE_BUTTON_H
