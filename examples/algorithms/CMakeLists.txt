cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(algorithms-example)

add_executable(v_douglas v_douglas.cpp)
target_link_libraries(v_douglas visualization ${GMP_LIBRARIES})

add_executable(v_vis_graph1 v_vis_graph1.cpp)
target_link_libraries(v_vis_graph1 visualization ${GMP_LIBRARIES})
