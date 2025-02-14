set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/WaveformDisplay.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/WaveformDisplay.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibWaveFormDisplay" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibWaveFormDisplay" PUBLIC ${LIBRARY_INCLUDES})

# link the LibECGPkg library to the LibSensor library
target_link_libraries("LibWaveFormDisplay" PUBLIC LibECGPkg LibTMDQueue LibTimeMarkedData)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibWaveFormDisplay"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibWaveFormDisplay"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibWaveFormDisplay")
endif()
