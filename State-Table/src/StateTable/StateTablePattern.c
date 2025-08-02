/**
 * @file StateTablePattern.c
 * @brief Simple implementations for State Table Pattern utilities
 */

#include "StateTablePattern.h"

/**
 * @brief Convert a character to its numeric digit value
 * @param c Character to convert ('0' through '9')
 * @return Integer value (0 through 9), or -1 if not a digit
 * 
 * This is a simple utility function that's easy to understand.
 * Examples:
 *   char_to_digit('0') returns 0
 *   char_to_digit('5') returns 5 
 *   char_to_digit('9') returns 9
 *   char_to_digit('a') returns -1 (not a digit)
 */
int char_to_digit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';  // ASCII arithmetic: '5' - '0' = 5
    }
    return -1;  // Invalid character - not a digit
}
