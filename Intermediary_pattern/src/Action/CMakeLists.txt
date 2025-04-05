set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Action.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Action.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibAction" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibAction" PUBLIC ${LIBRARY_INCLUDES})

#target_link_libraries("LibAction" PUBLIC "LibHWProxyExamplePkg")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibAction"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibAction"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibAction")
endif()
