set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ECG_Module.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/ECG_Module.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibECG_Module" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibECG_Module" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibECG_Module library
target_link_libraries("LibECG_Module" PUBLIC LibECGPkg LibTMDQueue LibTimeMarkedData)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibECG_Module"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibECG_Module"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibECG_Module")
endif()
