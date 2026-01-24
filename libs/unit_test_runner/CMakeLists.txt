add_library(warehouse_unit_test_runner STATIC)

target_sources(warehouse_unit_test_runner
    PRIVATE
        src/main.cpp
)

set_property(TARGET warehouse_unit_test_runner PROPERTY CXX_STANDARD 17)
set_property(TARGET warehouse_unit_test_runner PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(warehouse_unit_test_runner 
    PUBLIC
        warehouse_core
        GTest::gtest
)