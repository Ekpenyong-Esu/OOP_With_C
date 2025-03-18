set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/BCPeriodicPoller.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/BCPeriodicPoller.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibBCPeriodicPoller" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibBCPeriodicPoller" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibBCPeriodicPoller" PUBLIC LibBCTimer LibBreathingCircuitSensor LibMedicalDisplay)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibBCPeriodicPoller"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibBCPeriodicPoller"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibBCPeriodicPoller")
endif()
