#include <gtest/gtest.h>

#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/contains/rectangle_point.h>

TEST(contains, triangle_point0)
{
   using cg::point_2;

   cg::triangle_2 t(point_2(0, 0), point_2(1, 1), point_2(2, 0));

   for (size_t l = 0; l != 3; ++l)
      EXPECT_TRUE(cg::contains(t, t[l]));

   EXPECT_TRUE(cg::contains(t, point_2(1, 0.5)));

   EXPECT_TRUE(cg::contains(t, point_2(1, 0)));
   EXPECT_TRUE(cg::contains(t, point_2(0.5, 0.5)));
   EXPECT_TRUE(cg::contains(t, point_2(1.5, 0.5)));

   EXPECT_FALSE(cg::contains(t, point_2(0, 1)));
   EXPECT_FALSE(cg::contains(t, point_2(2, 1)));
   EXPECT_FALSE(cg::contains(t, point_2(1, -1)));
}

TEST(contains, triangle_point1)
{
   using cg::point_2;
   cg::triangle_2 t(point_2(0, 0), point_2(3, 0), point_2(0, 3));

   EXPECT_TRUE(cg::contains(t, point_2(1, 1)));
   EXPECT_TRUE(cg::contains(t, point_2(1, 0)));
   EXPECT_TRUE(cg::contains(t, point_2(0, 1)));
   EXPECT_FALSE(cg::contains(t, point_2(10, 10)));
}

TEST(contains, segment_point)
{
   using cg::point_2;

   cg::segment_2 s(point_2(0, 0), point_2(2, 2));
   for (size_t l = 0; l != 2; ++l)
      EXPECT_TRUE(cg::contains(s, s[l]));

   EXPECT_TRUE(cg::contains(s, point_2(1, 1)));

   EXPECT_FALSE(cg::contains(s, point_2(-1, -1)));
   EXPECT_FALSE(cg::contains(s, point_2(4, 4)));

   EXPECT_FALSE(cg::contains(s, point_2(1, 0)));
   EXPECT_FALSE(cg::contains(s, point_2(0, 1)));
}

TEST(contains, rectangle_point)
{
   using cg::point_2;
   cg::rectangle_2 rec(cg::range_t<double>(1, 4), cg::range_t<double>(1, 3));

   for (size_t i = 0; i != 2; ++i)
   {
      for (size_t j = 0; j != 2; ++j)
      {
         EXPECT_TRUE(cg::contains(rec, rec.corner(i, j)));
      }
   }

   EXPECT_TRUE(cg::contains(rec, point_2(2, 2)));
   EXPECT_FALSE(cg::contains(rec, point_2(-1, 0)));
}
