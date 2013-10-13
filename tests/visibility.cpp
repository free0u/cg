#include <gtest/gtest.h>
#include <cg/primitives/contour.h>
#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>
#include <cg/io/segment.h>
#include <cg/visibility/visibility_slow.h>
#include <vector>
#include <iostream>
#include <boost/assign/list_of.hpp>

using namespace std;
using cg::point_2;
using cg::contour_2;
using cg::segment_2;

size_t calc_size(vector<vector<point_2> > const& a) {
   size_t ret = 0;
   for (size_t i = 0; i < a.size(); ++i) {
      ret += a[i].size();
   }
   return ret;
}

TEST(visibility, sample)
{
   point_2 start(0, 0), finish(4, 4);
   vector<contour_2> poly;
   std::vector<point_2> pts = boost::assign::list_of(point_2(1, 1))
   (point_2(2, 1))
   (point_2(2, 2))
   (point_2(1, 2));

   poly.push_back(pts);
   vector<vector<point_2> > ans = cg::build_graph(poly, start, finish);

//   for (segment_2 s : ans) {
//      std::cout << s << std::endl;
//   }

   EXPECT_EQ(calc_size(ans), 20);
}

TEST(visibility, unbelievable)
{

   point_2 start(0, 0), finish(4, 5);
   vector<contour_2> poly;
   std::vector<point_2> first = boost::assign::list_of(point_2(1, 1))
   (point_2(1, -2))
   (point_2(2, 0))
   (point_2(3, -2))
   (point_2(3, 1));

   poly.push_back(first);

   vector<vector<point_2> > ans = cg::build_graph(poly, start, finish);
   EXPECT_EQ(calc_size(ans), 20);
}

TEST(visibility, gangsta)
{
   point_2 start(0, 0), finish(4, 5);
   vector<contour_2> poly;

   vector<vector<point_2> > ans = cg::build_graph(poly, start, finish);
   EXPECT_EQ(calc_size(ans), 2);
}
