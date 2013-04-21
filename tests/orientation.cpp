#include <gtest/gtest.h>

#include <cg/operations/orientation.h>
#include <cg/operations/convex.h>
#include <misc/random_utils.h>

#include "random_utils.h"

#include <vector>

TEST(DISABLED_orientation, uniform_line)
{
   util::uniform_random_real<double, std::mt19937> distr(-(1LL << 53), (1LL << 53));

   std::vector<cg::point_2> pts = uniform_points(1000);
   for (size_t l = 0, ln = 1; ln < pts.size(); l = ln++)
   {
      cg::point_2 a = pts[l];
      cg::point_2 b = pts[ln];

      for (size_t k = 0; k != 1000; ++k)
      {
         double t = distr();
         cg::point_2 c = a + t * (b - a);
         EXPECT_EQ(cg::orientation(a, b, c), *cg::orientation_r()(a, b, c));
      }
   }
}


TEST(orientation, counterclockwise)
{
   using cg::point_2;
   std::vector<point_2> a;

   a.push_back(point_2(0, 0));
   a.push_back(point_2(1, 0));
   a.push_back(point_2(1, 1));
   a.push_back(point_2(0, 1));

   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(a)));


   a.clear();
   a.push_back(point_2(0, 0));
   a.push_back(point_2(0, 1));
   a.push_back(point_2(1, 1));
   a.push_back(point_2(1, 0));

   EXPECT_FALSE(cg::counterclockwise(cg::contour_2(a)));

   a.clear();
   a.push_back(point_2(0, 0));
   a.push_back(point_2(2, 0));
   a.push_back(point_2(1, 2));
   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(a)));

   a.clear();
   a.push_back(point_2(1, 0));
   a.push_back(point_2(3, 0));
   a.push_back(point_2(0, 2));
   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(a)));
}

TEST(orientation, convex0)
{
   using cg::point_2;
   std::vector<point_2> a;

   a.push_back(point_2(0, 0));
   a.push_back(point_2(1, -1));
   a.push_back(point_2(2, 0));
   a.push_back(point_2(1, 3));
   EXPECT_TRUE(cg::convex(cg::contour_2(a)));

   a.clear();
   a.push_back(point_2(0, 0));
   a.push_back(point_2(1, 0));
   a.push_back(point_2(2, 0));
   a.push_back(point_2(1, 3));
   EXPECT_TRUE(cg::convex(cg::contour_2(a)));

   a.clear();
   a.push_back(point_2(0, 0));
   a.push_back(point_2(1, 1));
   a.push_back(point_2(2, 0));
   a.push_back(point_2(1, 3));
   EXPECT_FALSE(cg::convex(cg::contour_2(a)));

   a.clear();
   a.push_back(point_2(0, 0));
   a.push_back(point_2(2, 2));
   a.push_back(point_2(0, 1));
   a.push_back(point_2(-2, 2));
   EXPECT_FALSE(cg::convex(cg::contour_2(a)));


}
