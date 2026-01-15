add_library(libwarehouse STATIC)

target_sources(libwarehouse
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/controller.c
        ${CMAKE_CURRENT_SOURCE_DIR}/guards.c
        ${CMAKE_CURRENT_SOURCE_DIR}/input_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/input_processor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/product.c
        ${CMAKE_CURRENT_SOURCE_DIR}/product_stock.c
        ${CMAKE_CURRENT_SOURCE_DIR}/render.c
        ${CMAKE_CURRENT_SOURCE_DIR}/validator.c
        ${CMAKE_CURRENT_SOURCE_DIR}/warehouse_section.c
        ${CMAKE_CURRENT_SOURCE_DIR}/warehouse.c
)

target_include_directories(libwarehouse
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(warehouse)

target_sources(warehouse
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/app.c
)

set_property(TARGET warehouse PROPERTY C_STANDARD 11)
set_property(TARGET warehouse PROPERTY C_STANDARD_REQUIRED ON)

if(
  (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
  (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
)
  target_compile_options(warehouse PRIVATE /W4)
elseif(
  (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
  (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)
  target_compile_options(warehouse PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(warehouse PRIVATE libwarehouse)