add_executable(unit_tests)

target_sources(unit_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/guards_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/input_processor_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/product_stock_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/product_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_runner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/validator_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/warehouse_section_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/warehouse_tests.cpp
)

set_property(TARGET unit_tests PROPERTY CXX_STANDARD 17)
set_property(TARGET unit_tests PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(unit_tests 
    PRIVATE
        libwarehouse
        GTest::gtest
)

target_include_directories(unit_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(
    unit_tests
)