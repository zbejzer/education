cmake_minimum_required(VERSION 3.21.0)

project(jfrog VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_subdirectory(src)

target_include_directories(jfrog
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)