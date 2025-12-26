add_executable(warehouse_tests)

target_sources(warehouse_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test_runner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/validator_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/warehouse_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/line_parser_tests.cpp
)

set_property(TARGET warehouse_tests PROPERTY CXX_STANDARD 17)
set_property(TARGET warehouse_tests PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(warehouse_tests 
    PRIVATE
        libwarehouse
        GTest::gtest
)

target_include_directories(warehouse_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(
    warehouse_tests
)