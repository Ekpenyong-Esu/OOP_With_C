set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TSRSyncSingleReceptor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TSRSyncSingleReceptor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTSRSyncSingleReceptor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTSRSyncSingleReceptor" PUBLIC ${LIBRARY_INCLUDES})

# link the LibECGPkg library to the LibTSRSyncSingleReceptor library
target_link_libraries("LibTSRSyncSingleReceptor" PUBLIC LibTokenizeAsyncSinglePkg LibTSREventQueue LibMutex)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTSRSyncSingleReceptor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTSRSyncSingleReceptor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTSRSyncSingleReceptor")
endif()
