project(udp_protocol)
add_library(${PROJECT_NAME} SHARED udp_protocol.c)

target_link_libraries(udp_protocol SDL_net)

