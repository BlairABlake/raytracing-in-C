cmake_minimum_required(VERSION 3.25)
project(raytracing_in_C C)

set(CMAKE_C_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test)

add_library(munit ${CMAKE_CURRENT_SOURCE_DIR}/deps/munit/munit.c)
add_library(algorithms ${CMAKE_CURRENT_SOURCE_DIR}/deps/algorithms/htable.c ${CMAKE_CURRENT_SOURCE_DIR}/deps/algorithms/list.c)
add_library(raytracing tuple.c matrix.c util.h util.c ray.c sphere.c canvas.c 3Dobject.c)
target_link_libraries(raytracing algorithms)

add_executable(test test/tests.c)
target_link_libraries(test munit algorithms raytracing)

add_executable(sphere_image sphere_image.c)
target_link_libraries(sphere_image raytracing)