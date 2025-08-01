set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TokenizeAsyncSinglePkg.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TokenizeAsyncSinglePkg.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTokenizeAsyncSinglePkg" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTokenizeAsyncSinglePkg" PUBLIC ${LIBRARY_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTokenizeAsyncSinglePkg"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTokenizeAsyncSinglePkg"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTokenizeAsyncSinglePkg")
endif()
