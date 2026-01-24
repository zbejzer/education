add_library(warehouse_core STATIC)

target_sources(warehouse_core
    PRIVATE
        src/guards.c
        src/product_stock.c
        src/product.c
        src/render.c
        src/state_save.c
        src/warehouse_section.c
        src/warehouse.c
)

target_include_directories(warehouse_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(warehouse_core
    PUBLIC
        warehouse_config
)

if(BUILD_TESTING)
    add_executable(warehouse_core_unit_tests)

    target_sources(warehouse_core_unit_tests
        PRIVATE
            src/guards.test.cpp
            src/product_stock.test.cpp
            src/product.test.cpp
            src/warehouse_section.test.cpp
            src/warehouse.test.cpp
    )

    target_link_libraries(warehouse_core_unit_tests
        PRIVATE
            warehouse_core
            warehouse_unit_test_runner
    )

    include(GoogleTest)
    gtest_discover_tests(warehouse_core_unit_tests
        TEST_PREFIX "Core."
    )
endif()