set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GasNotificationHandle.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GasNotificationHandle.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGasNotificationHandle" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGasNotificationHandle" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibGasNotificationHandle" PUBLIC LibGasData)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGasNotificationHandle"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGasNotificationHandle"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGasNotificationHandle")
endif()
