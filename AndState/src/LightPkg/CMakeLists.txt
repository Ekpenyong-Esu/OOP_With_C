# Light Package - Essential types for AND pattern demonstration
# Contains basic enums for Color and Flash modes

set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/LightPkg.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibLightPkg" INTERFACE)
target_include_directories("LibLightPkg" INTERFACE ${LIBRARY_INCLUDES})

# This is an interface-only library (header-only with type definitions)
# All components depend on this for common types and constants
