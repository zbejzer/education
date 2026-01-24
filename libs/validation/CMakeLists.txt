add_library(warehouse_validation SHARED)

target_sources(warehouse_validation
    PRIVATE
        src/validator.c
)

target_include_directories(warehouse_validation
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(warehouse_validation
    PRIVATE
        warehouse_config
)

if(BUILD_TESTING)
    add_executable(warehouse_validation_unit_tests)

    target_sources(warehouse_validation_unit_tests
        PRIVATE
            src/validator.test.cpp
    )

    target_link_libraries(warehouse_validation_unit_tests
        PRIVATE
            warehouse_validation
            warehouse_unit_test_runner
    )

    include(GoogleTest)
    gtest_discover_tests(warehouse_validation_unit_tests
        TEST_PREFIX "Validation."
    )
endif()