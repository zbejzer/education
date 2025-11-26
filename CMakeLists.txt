cmake_minimum_required(VERSION 3.21.0)
project(warehouse VERSION 0.1.0 LANGUAGES C)

add_executable(warehouse)

target_sources(warehouse
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/warehouse.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/product.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/command_parser.c
)

target_include_directories(warehouse
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_property(TARGET warehouse PROPERTY C_STANDARD 11)

if(MSVC)
    target_compile_options(warehouse PRIVATE /W4)
else()
    target_compile_options(warehouse PRIVATE -Wall -Wextra -Wpedantic)
endif()