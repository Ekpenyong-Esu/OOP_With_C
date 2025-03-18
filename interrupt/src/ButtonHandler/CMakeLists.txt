set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ButtonHandler.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/ButtonHandler.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibButtonHandler" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibButtonHandler" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibButtonHandler" PUBLIC LibLED LibRobotInterruptVectorTable)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibButtonHandler"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibButtonHandler"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibButtonHandler")
endif()
