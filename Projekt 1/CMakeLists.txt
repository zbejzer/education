cmake_minimum_required(VERSION 3.10.0)
project(AL2 VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(AL2 AL2.c)

target_link_libraries(AL2 PRIVATE m)
target_link_libraries(AL2 PRIVATE rt)
