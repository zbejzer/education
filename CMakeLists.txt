cmake_minimum_required(VERSION 3.21.0)
project(warehouse VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/googletest external/googletest)

add_subdirectory(src)
add_subdirectory(tests)