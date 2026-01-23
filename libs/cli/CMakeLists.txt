add_executable(warehouse_cli)

set_target_properties(warehouse_cli PROPERTIES 
    OUTPUT_NAME "warehouse"
    C_STANDARD  11
    C_STANDARD_REQUIRED ON
)

target_sources(warehouse_cli
    PRIVATE
        src/controller.c
        src/input_handler.c
        src/input_processor.c
        src/main.c
)

target_include_directories(warehouse_cli
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(MSVC)
    target_compile_options(warehouse_cli PRIVATE /W4)
else()
    target_compile_options(warehouse_cli PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(warehouse_cli
    PRIVATE
        warehouse_core
        warehouse_validation
        warehouse_config
)