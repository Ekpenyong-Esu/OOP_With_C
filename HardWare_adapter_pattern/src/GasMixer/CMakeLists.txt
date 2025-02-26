set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GasMixer.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GasMixer.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGasMixer" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGasMixer" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibGasMixer" PUBLIC Libi02Sensor LibUltimate02Adapter LibUltimateO2SensorProxy LibAcme02Adapter)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGasMixer"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGasMixer"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGasMixer")
endif()
