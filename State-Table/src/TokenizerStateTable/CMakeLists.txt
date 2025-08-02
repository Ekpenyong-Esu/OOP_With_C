set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TokenizerStateTable.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TokenizerStateTable.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTokenizerStateTable" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTokenizerStateTable" PUBLIC ${LIBRARY_INCLUDES})

# link the LibStateTable library to the LibTokenizerStateTable library
target_link_libraries("LibTokenizerStateTable" PUBLIC LibMutex LibStateTable)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTokenizerStateTable"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTokenizerStateTable"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTokenizerStateTable")
endif()
