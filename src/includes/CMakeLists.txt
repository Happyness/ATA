project(includes)

add_subdirectory(player)
add_subdirectory(network)
add_subdirectory(graphics)

add_library(calc SHARED calc.c)
add_library(cbuffer SHARED cbuffer.c)
add_library(graphics SHARED graphics.c)
add_library(jukebox SHARED jukebox.c)

target_link_libraries(graphics SDL SDL_image menu timer editor draw)
target_link_libraries(jukebox SDL SDL_mixer)