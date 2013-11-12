project(clientserver)

set(SDL_BUILDING_LIBRARY On)

find_package(X11)
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_library(SDL_OPENGL_LIB SDL_opengl)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)

IF(SDL_FOUND)
	MESSAGE("SDL Found")
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
ELSE(SDL_FOUND)
	MESSAGE("SDL not found")
ENDIF(SDL_FOUND)

IF(OPENGL_FOUND)
	MESSAGE("OPENGL Found")
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIRS})
ELSE(OPENGL_FOUND)
	MESSAGE("OPENGL not found")
ENDIF(OPENGL_FOUND)

if(NOT X11_FOUND)
    message(FATAL_ERROR "Failed to find X11 which is required to build client")
endif(NOT X11_FOUND)

set(LIBS ${LIBS} ${X11_LIBRARIES})

include_directories(SDL_opengl)
include_directories(SDL_mixer)

add_subdirectory(includes)
#add_subdirectory(levels)

add_executable(server server.c)
add_executable(client client.c)
add_executable(testCase testCases.c)

target_link_libraries(server SDL pthread udp_protocol structure timer calc controller cbuffer)
target_link_libraries(client SDL ${OPENGL_LIBRARY} ${LIBS} jukebox pthread graphics draw timer udp_protocol structure cbuffer)
target_link_libraries(testCase cbuffer calc structure)