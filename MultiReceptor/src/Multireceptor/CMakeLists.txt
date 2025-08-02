set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MultiReceptor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/MultiReceptor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibMultireceptor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibMultireceptor" PUBLIC ${LIBRARY_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibMultireceptor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibMultireceptor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibMultireceptor")
endif()
