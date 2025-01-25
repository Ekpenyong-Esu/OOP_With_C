set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TMDQueue.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TMDQueue.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTMDQueue" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTMDQueue" PUBLIC ${LIBRARY_INCLUDES})

# link the LibECGPkg library to the LibTMDQueue library
target_link_libraries("LibTMDQueue" PUBLIC LibECGPkg LibTimeMarkedData)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTMDQueue"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTMDQueue"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTMDQueue")
endif()
