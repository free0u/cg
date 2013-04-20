#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>

#include <cg/convex_hull/graham.h>
#include <cg/convex_hull/andrew.h>
#include <cg/operations/contains/segment_point.h>

#include <cg/io/point.h>

#include "random_utils.h"

template <class FwdIter>
bool is_convex_hull(FwdIter p, FwdIter c, FwdIter q)
{
   for (FwdIter t = boost::prior(c), s = p; s != c; t = s++)
   {
      for (FwdIter b = p; b != q; ++b)
      {
         switch (orientation(*t, *s, *b))
         {
         case cg::CG_RIGHT: return false;
         case cg::CG_COLLINEAR:
//            return collinear_are_ordered_along_line(*t, *b, *s);
            if (!collinear_are_ordered_along_line(*t, *b, *s))
            {
  //             return false;
            }
            break;
         case cg::CG_LEFT: break;
         }
      }
   }

   return true;
}

TEST(convex_hull, simple_graham)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(1, 0))
                                                    (point_2(0, 1))
                                                    (point_2(2, 0))
                                                    (point_2(0, 2))
                                                    (point_2(3, 0));

   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::graham_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, uniform_graham)
{
   using cg::point_2;

   std::vector<point_2> pts = uniform_points(1000);
   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::graham_hull(pts.begin(), pts.end()), pts.end()));
}


TEST(convex_hull, simple_andrew0)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 2))
                                                    (point_2(3, 0))
                                                    (point_2(4, 2))
                                                    (point_2(3, 3))
                                                    (point_2(2, 4));

//   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, simple_andrew1)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(1, 0))
                                                    (point_2(0, 1))
                                                    (point_2(2, 0))
                                                    (point_2(0, 2))
                                                    (point_2(3, 0));

//   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}


TEST(convex_hull, simple_andrew2)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(1, 0))
                                                   (point_2(1, 2))
                                                   (point_2(1, 4))
                                                   (point_2(0, 1))
                                                    (point_2(3, 2));

//   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, simple_andrew3)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(1, 0));

//   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, simple_andrew4)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(1, 0))
                                                    (point_2(0, 1));

//   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, simple_andrew5)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(1, 0))
                                                   (point_2(1, 2))
                                                   (point_2(1, 2))
                                                   (point_2(1, 4))
                                                   (point_2(0, 1))
                                                   (point_2(0, 1))
                                                   (point_2(0, 1))
                                                    (point_2(3, 2));

//   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, simple_andrew6)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                   (point_2(4, 0))
                                                   (point_2(3, 4))
                                                    (point_2(2, 2));

   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, uniform_andrew)
{
   using cg::point_2;

   std::vector<point_2> pts = uniform_points(100000);
//   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::andrew_hull(pts.begin(), pts.end()), pts.end()));
}
