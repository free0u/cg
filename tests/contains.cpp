#include <gtest/gtest.h>

#include "random_utils.h"

#include <boost/assign/list_of.hpp>

#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/contains/rectangle_point.h>
#include <cg/operations/contains/contour_point.h>
#include <cg/convex_hull/graham.h>

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


namespace details
{
   bool point_in_ccw_contour(cg::contour_2 const & c, cg::point_2 const & q)
   {
      size_t cnt_vertices = c.size();
      if (cnt_vertices == 0)
         return false;

      if (std::find(c.begin(), c.end(), q) != c.end())
         return true;


      if (cnt_vertices == 1)
      {
         return c[0] == q;
      }

      if (cnt_vertices == 2)
      {
         return cg::contains(cg::segment_2(c[0], c[1]), q);
      }

      cg::contour_2::circulator_t t2 = c.circulator();
      cg::contour_2::circulator_t t1 = t2++;

      for (size_t i = 0; i < cnt_vertices; ++i)
      {
         if (cg::orientation(*t1, *t2, q) == cg::CG_RIGHT)
         {
            return false;
         }
         ++t1;
         ++t2;
      }

      return true;
   }
}

TEST(contains, convex_ccw_point1)
{
   using cg::point_2;
   using cg::contour_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(1, 1));

   contour_2 cont(pts);
   for (size_t i = 0; i < pts.size(); i++)
   {
      EXPECT_TRUE(cg::convex_contains(cont, pts[i]));
   }

   EXPECT_TRUE(cg::convex_contains(cont, point_2(1, 1)));

   EXPECT_FALSE(cg::convex_contains(cont, point_2(0, 0)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(2, 2)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(0, 1)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(1, 0)));
}

TEST(contains, convex_ccw_point2)
{
   using cg::point_2;
   using cg::contour_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(1, 1))
                                                    (point_2(3, 3));

   contour_2 cont(pts);
   for (size_t i = 0; i < pts.size(); i++)
   {
      EXPECT_TRUE(cg::convex_contains(cont, pts[i]));
   }

   EXPECT_TRUE(cg::convex_contains(cont, point_2(2, 2)));

   EXPECT_FALSE(cg::convex_contains(cont, point_2(0, 0)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(4, 4)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(0, 1)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(1, 0)));
}

TEST(contains, convex_ccw_point3)
{
   using cg::point_2;
   using cg::contour_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 1))
                                                    (point_2(0, 0))
                                                    (point_2(1, -1));

   contour_2 cont(pts);
   for (size_t i = 0; i < pts.size(); i++)
   {
      EXPECT_TRUE(cg::convex_contains(cont, pts[i]));
   }

   for (size_t i = 0; i < pts.size(); i++)
   {
      EXPECT_TRUE(cg::convex_contains(cont, pts[i]));
   }
}

TEST(contains, convex_ccw_point4)
{
   using cg::point_2;
   using cg::contour_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(2, 4))
                                                    (point_2(0, 4))
                                                    (point_2(-2, 4));

   contour_2 cont(pts);
   for (size_t i = 0; i < pts.size(); i++)
   {
      EXPECT_TRUE(cg::convex_contains(cont, pts[i]));
   }

   EXPECT_TRUE(cg::convex_contains(cont, point_2(1, 2)));
   EXPECT_TRUE(cg::convex_contains(cont, point_2(1, 3)));
   EXPECT_TRUE(cg::convex_contains(cont, point_2(0, 2)));
   EXPECT_TRUE(cg::convex_contains(cont, point_2(-1, 2)));
   EXPECT_TRUE(cg::convex_contains(cont, point_2(-1, 3)));


   EXPECT_FALSE(cg::convex_contains(cont, point_2(1, 1)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(-1, 1)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(1, 5)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(1, 6)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(-1, 5)));
   EXPECT_FALSE(cg::convex_contains(cont, point_2(-1, 6)));
}

TEST(contains, convex_ccw_point_uniform0)
{
   using cg::point_2;
   using cg::contour_2;


   for (size_t cnt_points = 3; cnt_points < 10; cnt_points++)
   {
      std::vector<point_2> pts = uniform_points(cnt_points);
      std::vector<point_2> pts2 = uniform_points(100000);

      auto it = cg::graham_hull(pts.begin(), pts.end());
      pts.resize(std::distance(pts.begin(), it));

      contour_2 cont(pts);

      for (size_t i = 0; i < cont.size(); i++)
      {
         EXPECT_TRUE(cg::convex_contains(cont, cont[i]));
      }

      for (size_t i = 0; i < pts2.size(); i++)
      {
         EXPECT_EQ(cg::convex_contains(cont, pts2[i]), details::point_in_ccw_contour(cont, pts2[i]));
      }
   }
}

TEST(contains, convex_ccw_point_uniform1)
{
   using cg::point_2;
   using cg::contour_2;


   for (size_t cnt_tests = 3; cnt_tests < 10; cnt_tests++)
   {
      std::vector<point_2> pts = uniform_points(100000);
      std::vector<point_2> pts2 = uniform_points(100000);

      auto it = cg::graham_hull(pts.begin(), pts.end());
      pts.resize(std::distance(pts.begin(), it));

      contour_2 cont(pts);

      for (size_t i = 0; i < cont.size(); i++)
      {
         EXPECT_TRUE(cg::convex_contains(cont, cont[i]));
      }

      for (size_t i = 0; i < pts2.size(); i++)
      {
         EXPECT_EQ(cg::convex_contains(cont, pts2[i]), details::point_in_ccw_contour(cont, pts2[i]));
      }
   }
}
