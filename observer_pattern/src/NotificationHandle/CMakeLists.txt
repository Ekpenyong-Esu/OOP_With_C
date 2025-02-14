set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/NotificationHandle.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/NotificationHandle.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibNotificationHandle" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibNotificationHandle" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibNotificationHandle library
target_link_libraries("LibNotificationHandle" PUBLIC LibECGPkg LibHistogramDisplay)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibNotificationHandle"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibNotificationHandle"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibNotificationHandle")
endif()
