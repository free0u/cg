cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(operation-example)

add_executable(v_contour_ccw orientation_contour_ccw.cpp)
target_link_libraries(v_contour_ccw visualization ${GMP_LIBRARIES})


add_executable(v_cont_ccw_convex ccw_contour_convex.cpp)
target_link_libraries(v_cont_ccw_convex visualization ${GMP_LIBRARIES})


