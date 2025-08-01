set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GasController.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GasController.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGasController" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGasController" PUBLIC ${LIBRARY_INCLUDES})

# Link required libraries
target_link_libraries("LibGasController" PUBLIC 
    LibGasData
    LibGasDataQueue
    LibGasDisplay)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGasController"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGasController"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGasController")
endif()
