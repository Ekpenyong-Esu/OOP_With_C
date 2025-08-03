//
// Created by mahon on 2/3/2024.
//
// Simple Light Package - Essential types for AND Pattern demonstration
// This defines the basic types used by the Light component

#ifndef ANDSTATE_LIGHTPKG_H
#define ANDSTATE_LIGHTPKG_H

// Forward declarations (not used in simple demo but kept for compatibility)
struct Light;

// Color states - first aspect of the AND pattern
typedef enum ColorType {
    RED,
    YELLOW,
    GREEN
} ColorType;

// Flash modes - second aspect of the AND pattern
typedef enum FlashType {
    STEADY,
    SLOWLY,
    QUICKLY
} FlashType;

#endif //ANDSTATE_LIGHTPKG_H
