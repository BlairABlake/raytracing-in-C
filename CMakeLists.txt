cmake_minimum_required(VERSION 3.25)
project(raytracing_in_C C)

set(CMAKE_C_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(munit ${CMAKE_CURRENT_SOURCE_DIR}/deps/munit/munit.c)
add_library(cstring ${CMAKE_CURRENT_SOURCE_DIR}/deps/cstring/cstring.c)


add_executable(projectile projectile.c tuple.h color.h canvas.h deps/cstring/cstring.h util.h)
add_executable(clock_image clock_image.c tuple.h color.h canvas.h deps/cstring/cstring.h util.h matrix.h)
add_executable(sphere_image sphere_image.c tuple.h color.h canvas.h deps/cstring/cstring.h util.h matrix.h sphere.h ray.h)
add_executable(raytracing_in_C main.c tuple.h color.h canvas.h deps/cstring/cstring.h util.h matrix.h ray.h sphere.h transform.h)
add_executable(test test/tests.c deps/munit/munit.h deps/cstring/cstring.h test/tests.h color.h test/color_test.h canvas.h test/canvas_test.h test/tuple_test.h util.h matrix.h test/matrix_test.h ray.h test/ray_test.h sphere.h test/sphere_test.h transform.h test/transform_test.h)
target_link_libraries(test munit cstring)
target_link_libraries(raytracing_in_C cstring)
target_link_libraries(projectile cstring)
target_link_libraries(clock_image cstring)
target_link_libraries(sphere_image cstring)