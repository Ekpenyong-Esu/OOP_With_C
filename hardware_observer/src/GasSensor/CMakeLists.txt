set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GasSensor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GasSensor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGasSensor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGasSensor" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibGasSensor" PUBLIC LibGasData LibGasNotificationHandle)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGasSensor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGasSensor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGasSensor")
endif()
