add_library(warehouse_config INTERFACE)

target_include_directories(warehouse_config
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)