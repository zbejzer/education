cmake_minimum_required(VERSION 3.21.0)
project(
    warehouse
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

if(BUILD_TESTING)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(
        "${PROJECT_SOURCE_DIR}/external/googletest"
        "external/googletest"
    )
endif()

add_subdirectory(libs)

get_property(
    WAREHOUSE_BUILD_DIR
    TARGET
        warehouse_cli
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