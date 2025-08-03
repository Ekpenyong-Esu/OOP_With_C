# Light Library - Simple AND Pattern Demonstration
# This component demonstrates the AND Pattern with a Light that has
# two independent aspects: Color (RED, YELLOW, GREEN) and Mode (STEADY, SLOWLY, QUICKLY)

set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Light.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Light.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# Create a static library with the implementation
add_library("LibLight" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibLight" PUBLIC ${LIBRARY_INCLUDES})

# Link with LightPkg for type definitions
target_link_libraries("LibLight" PUBLIC "LibLightPkg")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibLight"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibLight"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibLight")
endif()