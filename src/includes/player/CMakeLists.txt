project(player)
find_library(libcalc REQUIRED)
add_library(controller SHARED controller.c)
target_link_libraries(controller calc)