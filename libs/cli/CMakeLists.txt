add_library(warehouse_cli_internal STATIC)

target_sources(warehouse_cli_internal
    PRIVATE
        src/input_processor.c
)

target_include_directories(warehouse_cli_internal
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(warehouse_cli_internal
    PRIVATE
        warehouse_core
        warehouse_config
)

add_executable(warehouse_cli)

set_target_properties(warehouse_cli PROPERTIES 
    OUTPUT_NAME "warehouse"
)

target_sources(warehouse_cli
    PRIVATE
        src/controller.c
        src/input_handler.c
        src/main.c
)

target_include_directories(warehouse_cli
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(warehouse_cli
    PRIVATE
        warehouse_cli_internal
        warehouse_core
        warehouse_validation
        warehouse_config
)

if(BUILD_TESTING)
    add_executable(warehouse_cli_internal_unit_tests)

    target_sources(warehouse_cli_internal_unit_tests
        PRIVATE
            src/input_processor.test.cpp
    )

    target_link_libraries(warehouse_cli_internal_unit_tests
        PRIVATE
            warehouse_cli_internal
            warehouse_config
            warehouse_unit_test_runner
    )

    include(GoogleTest)
    gtest_discover_tests(warehouse_cli_internal_unit_tests
        TEST_PREFIX "CliInternal."
    )
endif()