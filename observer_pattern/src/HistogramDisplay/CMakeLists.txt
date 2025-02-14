set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/HistogramDisplay.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/HistogramDisplay.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibHistogramDisplay" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibHistogramDisplay" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibHistogramDisplay library
target_link_libraries("LibHistogramDisplay" PUBLIC LibECGPkg LibTimeMarkedData LibTMDQueue)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibHistogramDisplay"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibHistogramDisplay"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibHistogramDisplay")
endif()
