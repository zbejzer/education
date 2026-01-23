add_library(warehouse_validation SHARED)

target_sources(warehouse_validation
    PRIVATE
        src/validator.c
)

target_include_directories(warehouse_validation
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(warehouse_validation
    PRIVATE
        warehouse_config
)