#include <gtest/gtest.h>

#include <cg/operations/orientation.h>
#include "random_utils.h"

#include <vector>

TEST(DISABLED_orientation, uniform_line)
{
   boost::random::mt19937 gen;
   boost::random::uniform_real_distribution<> distr(-(1LL << 53), (1LL << 53));

   std::vector<cg::point_2> pts = uniform_points(1000);
   for (size_t l = 0, ln = 1; ln < pts.size(); l = ln++)
   {
      cg::point_2 a = pts[l];
      cg::point_2 b = pts[ln];

      for (size_t k = 0; k != 1000; ++k)
      {
         double t = distr(gen);
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
}


