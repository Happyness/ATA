project(includes)

add_subdirectory(player)
add_subdirectory(network)
#add_subdirectory(world)
add_subdirectory(graphics)

add_library(libcalc SHARED libcalc.c)
add_library(eventque SHARED eventQue.c)
add_library(linkedlist SHARED linkedList.c)
add_library(graphics SHARED graphics.c)

target_link_libraries(eventque linkedlist)
target_link_libraries(graphics SDL SDL_image menu timer editor level world load_image)