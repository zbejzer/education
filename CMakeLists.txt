cmake_minimum_required(VERSION 3.21.0)
project(
    warehouse
    VERSION 0.1.0
    LANGUAGES C CXX
)

include(CTest)

if(BUILD_TESTING)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(
        "${PROJECT_SOURCE_DIR}/external/googletest"
        "external/googletest"
    )
endif()

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

get_property(
    WAREHOUSE_BUILD_DIR
    TARGET
        warehouse
    PROPERTY
        BINARY_DIR
)

configure_file(
    "${PROJECT_SOURCE_DIR}/tools/run_scenario.sh"
    "${WAREHOUSE_BUILD_DIR}/run_scenario.sh"
    FILE_PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)