cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(operations-example)

add_executable(v_tr_con_pnt triangle_contains_point.cpp)
target_link_libraries(v_tr_con_pnt visualization ${GMP_LIBRARIES})

add_executable(v_seg_cont_pnt segment_contains_point.cpp)
target_link_libraries(v_seg_cont_pnt visualization ${GMP_LIBRARIES})

add_executable(v_rect_cont_pnt rectangle_contains_point.cpp)
target_link_libraries(v_rect_cont_pnt visualization ${GMP_LIBRARIES})


add_executable(v_ccw_conv_cont_pnt ccw_convex_contour_contains_point.cpp)
target_link_libraries(v_ccw_conv_cont_pnt visualization ${GMP_LIBRARIES})


