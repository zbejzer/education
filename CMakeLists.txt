cmake_minimum_required(VERSION 3.21.0)
project(warehouse VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/extern/googletest extern/googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(warehouse
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.c
)

set_property(TARGET warehouse PROPERTY C_STANDARD 11)
set_property(TARGET warehouse PROPERTY C_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(warehouse PRIVATE /W4)
else()
    target_compile_options(warehouse PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_library(libwarehouse STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/warehouse.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/validator.c
)

target_include_directories(libwarehouse
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(warehouse PRIVATE libwarehouse)

add_subdirectory(tests)