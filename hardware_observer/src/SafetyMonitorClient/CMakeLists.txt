set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/SafetyMonitorClient.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/SafetyMonitorClient.")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibSafetyMonitorClient" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibSafetyMonitorClient" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibSafetyMonitorClient" PUBLIC LibGasData LibGasSensor)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibSafetyMonitorClient"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibSafetyMonitorClient"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibSafetyMonitorClient")
endif()
