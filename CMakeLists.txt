cmake_minimum_required(VERSION 3.25)
project(raytracing_in_C C)

set(CMAKE_C_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(munit ${CMAKE_CURRENT_SOURCE_DIR}/deps/munit/munit.c)
add_library(cstring ${CMAKE_CURRENT_SOURCE_DIR}/deps/cstring/cstring.c)


add_executable(raytracing_in_C main.c tuple.h float.h color.h canvas.h deps/cstring/cstring.h)
add_executable(test test/tests.c deps/munit/munit.h deps/cstring/cstring.h test/tests.h float.h color.h test/color_test.h canvas.h test/canvas_test.h test/tuple_test.h)
target_link_libraries(test munit cstring)
target_link_libraries(raytracing_in_C cstring)