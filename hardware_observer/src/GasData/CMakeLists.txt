set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GasData.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GasData.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGasData" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGasData" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector librarya
# target_link_libraries("LibGasData" PUBLIC )


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGasData"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGasData"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGasData")
endif()
