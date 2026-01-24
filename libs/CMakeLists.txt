if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(cli)
add_subdirectory(core)
add_subdirectory(validation)
add_subdirectory(config)

if(BUILD_TESTING)
    add_subdirectory(unit_test_runner)
endif()
