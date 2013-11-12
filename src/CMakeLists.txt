project(clientserver)

set(SDL_BUILDING_LIBRARY On)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_library(SDL_OPENGL_LIB SDL_opengl)
find_package(SDL_image REQUIRED)

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

include_directories(SDL_opengl)

add_subdirectory(includes)
add_subdirectory(levels)

add_executable(server server.c)
add_executable(client client.c)
add_executable(testCase testCases.c)

target_link_libraries(server SDL pthread udp_protocol structure libcalc controller linkedlist)
target_link_libraries(client SDL ${OPENGL_LIBRARY} graphics pthread world timer udp_protocol structure eventque linkedlist)
target_link_libraries(testCase linkedlist libcalc)