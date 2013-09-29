cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(v_douglas-example)

add_executable(v_douglas v_douglas.cpp)
target_link_libraries(v_douglas visualization ${GMP_LIBRARIES})
