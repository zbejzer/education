add_executable(jfrog)

set_target_properties(jfrog PROPERTIES 
    OUTPUT_NAME "jumping_frog"
)

target_sources(jfrog
  PRIVATE
    app.c
    config.c
    entity.c
    game.c
    input.c
    main.c
    render.c
)