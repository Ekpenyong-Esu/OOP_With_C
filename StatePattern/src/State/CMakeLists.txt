set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/State.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/State.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibState" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibState" PUBLIC ${LIBRARY_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibState"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibState"
        ENABLE
        ${ENABLE_LTO})
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibState")
endif()
