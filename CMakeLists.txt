cmake_minimum_required(VERSION 3.21.0)

project(jfrog VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CURSES_USE_NCURSES TRUE)
add_compile_definitions(NCURSES_STATIC)

find_package(Curses REQUIRED)

add_executable(jfrog)

target_include_directories(jfrog PUBLIC ${CURSES_INCLUDE_DIR})
target_link_libraries(jfrog PUBLIC ${CURSES_LIBRARIES})

add_subdirectory(src)

if(MSVC)
  target_compile_options(jfrog PRIVATE /W4 /WX)
else()
  target_compile_options(jfrog PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()