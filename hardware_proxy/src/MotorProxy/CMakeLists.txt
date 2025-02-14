set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MotorProxy.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/MotorProxy.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibMotorProxy" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibMotorProxy" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibMotorProxy" PUBLIC LibHWProxyExamplePkg LibMotorDataPkg)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibMotorProxy"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibMotorProxy"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibMotorProxy")
endif()
