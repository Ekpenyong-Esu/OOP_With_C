set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TimeMarkedData.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TimeMarkedData.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTimeMarkedData" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTimeMarkedData" PUBLIC ${LIBRARY_INCLUDES})

# link the LibECGPkg library to the LibTimeMarkedData library
target_link_libraries("LibTimeMarkedData" PUBLIC LibTMDQueue LibECGPkg)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTimeMarkedData"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTimeMarkedData"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTimeMarkedData")
endif()
