cmake_minimum_required(VERSION 3.30.0)

project(jumping-frog VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CURSES_USE_NCURSES TRUE)
add_compile_definitions(NCURSES_STATIC)

find_package(Curses REQUIRED)

add_executable(jumping-frog)

target_include_directories(jumping-frog PUBLIC ${CURSES_INCLUDE_DIR})
target_link_libraries(jumping-frog PUBLIC ${CURSES_LIBRARIES})

target_sources(jumping-frog
  PRIVATE
    main.cpp
    app.cpp
    app.hpp
    game.cpp
    game.hpp
    entity.cpp
    entity.hpp
    config.cpp
    config.hpp
)

if(MSVC)
  target_compile_options(jumping-frog PRIVATE /W4 /WX)
else()
  target_compile_options(jumping-frog PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()