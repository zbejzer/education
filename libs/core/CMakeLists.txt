add_library(warehouse_core STATIC)

target_sources(warehouse_core
    PRIVATE
        src/guards.c
        src/product.c
        src/product_stock.c
        src/render.c
        src/state_save.c
        src/warehouse_section.c
        src/warehouse.c
)

target_include_directories(warehouse_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(warehouse_core
    PUBLIC
        warehouse_config
)