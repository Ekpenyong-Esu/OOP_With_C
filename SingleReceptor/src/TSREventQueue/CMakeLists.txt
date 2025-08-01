set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TSREventQueue.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TSREventQueue.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTSREventQueue" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTSREventQueue" PUBLIC ${LIBRARY_INCLUDES})

# link the LibTokenizeAsyncSinglePkg library to the LibTSREventQueue library
target_link_libraries("LibTSREventQueue" PUBLIC LibTokenizeAsyncSinglePkg LibMutex)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTSREventQueue"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTSREventQueue"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTSREventQueue")
endif()
