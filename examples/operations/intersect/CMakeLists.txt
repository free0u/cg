cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(operations-example)

add_executable(v_seg_inter_seg segment_intersect_segment.cpp)
target_link_libraries(v_seg_inter_seg visualization ${GMP_LIBRARIES})

add_executable(v_seg_inter_tr segment_intersect_triangle.cpp)
target_link_libraries(v_seg_inter_tr visualization ${GMP_LIBRARIES})

add_executable(v_seg_intert_rect segment_intersect_rectangle.cpp)
target_link_libraries(v_seg_intert_rect visualization ${GMP_LIBRARIES})


