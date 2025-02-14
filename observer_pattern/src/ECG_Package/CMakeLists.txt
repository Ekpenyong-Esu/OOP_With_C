#set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Sensor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/ECGkpg.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibECGPkg" INTERFACE)
target_include_directories("LibECGPkg" INTERFACE ${LIBRARY_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibECGPkg"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibECGPkg"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibECGPkg")
endif()
