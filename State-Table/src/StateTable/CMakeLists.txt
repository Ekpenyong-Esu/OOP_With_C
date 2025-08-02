#set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TokenizeAsyncSinglePkg.c")
set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/StateTablePattern.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/StateTablePattern.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibStateTable" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibStateTable" PUBLIC ${LIBRARY_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibStateTable"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibStateTable"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibStateTable")
endif()
