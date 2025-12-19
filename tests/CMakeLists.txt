
add_executable(test_warehouse)

target_sources(test_warehouse
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hello_test.cpp
)

target_link_libraries(
    test_warehouse GTest::gtest_main
)

set_property(TARGET test_warehouse PROPERTY CXX_STANDARD 17)
set_property(TARGET test_warehouse PROPERTY CXX_STANDARD_REQUIRED ON)

include(GoogleTest)
gtest_discover_tests(
    test_warehouse
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)