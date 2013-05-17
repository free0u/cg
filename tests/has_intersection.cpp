#include <gtest/gtest.h>

#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/has_intersection/triangle_segment.h>
#include <cg/operations/has_intersection/rectangle_segment.h>

using cg::point_2;
using cg::segment_2;

TEST(has_intersection, segment_segment0)
{
   segment_2 s[] =
   {
      segment_2(point_2(0, 0), point_2(2, 2)),
      segment_2(point_2(1, 0), point_2(0, 1)),
      segment_2(point_2(0, 0), point_2(2, 0)),
      segment_2(point_2(0, 0), point_2(2, -1))
   };

   EXPECT_TRUE(cg::has_intersection(s[0], s[1]));
   EXPECT_TRUE(cg::has_intersection(s[1], s[2]));
   EXPECT_TRUE(cg::has_intersection(s[0], s[2]));

   EXPECT_FALSE(cg::has_intersection(s[1], s[3]));

   segment_2 a(point_2(1.0, 0.0), point_2(4.0, 0.0));
   EXPECT_TRUE(cg::has_intersection(a, segment_2(point_2(2.0, -2.0), point_2(2.0, 2.0))));
   EXPECT_TRUE(cg::has_intersection(a, segment_2(point_2(2.0, 0.0), point_2(2.0, 2.0))));
   EXPECT_FALSE(cg::has_intersection(a, segment_2(point_2(1.0, 2.0), point_2(2.0, 2.0))));

   point_2 a1(0.5, 0), a2(0.5, 0), a3(0, 0), a4(1, 0);
   segment_2 s1(a1, a2), s2(a3, a4);
   EXPECT_TRUE(cg::has_intersection(s1, s2));

   s1 = { {0, 0}, {0, 0} };
   s2 = { {-1, -1}, {1, -1} };
   EXPECT_FALSE(cg::has_intersection(s1, s2));

   s1 = { {0, 0}, {0, 0} };
   s2 = { {0, 0}, {0, 0} };
   EXPECT_TRUE(cg::has_intersection(s1, s2));

   s1 = { {0, 0}, {0, 0} };
   s2 = { {1, 0}, {1, 0} };
   EXPECT_FALSE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment1)
{
   segment_2 a(point_2(1, 1), point_2(2, 2));
   segment_2 b(point_2(2, 2), point_2(3, 2));

   EXPECT_TRUE(cg::has_intersection(a, b));
}

TEST(has_intersection, segment_segment2)
{
    segment_2 a(point_2(1, 1), point_2(20, 20));
    segment_2 b(point_2(2, 2), point_2(3, 3));

    EXPECT_TRUE(cg::has_intersection(a, b));
}

TEST(has_intersection, segment_segment3)
{
    segment_2 a(point_2(1, 1), point_2(2, 2));
    segment_2 b(point_2(1.5, 1.5), point_2(1.5, 1.5));

    EXPECT_TRUE(cg::has_intersection(a, b));
}

TEST(has_intersection, segment_segment4)
{
    segment_2 a(point_2(1, 1), point_2(2, 2));
    segment_2 b(point_2(0, 1.5), point_2(10, 1.5));

    EXPECT_TRUE(cg::has_intersection(a, b));
}


TEST(has_intersection, segment_segment5)
{
    segment_2 a(point_2(1, 1), point_2(2, 2));
    segment_2 b(point_2(3, 3), point_2(4, 4));

    EXPECT_FALSE(cg::has_intersection(a, b));
}

TEST(has_intersection, segment_segment6)
{
    segment_2 a(point_2(3, 3), point_2(4, 4));
    segment_2 b(point_2(1, 1), point_2(2, 2));

    EXPECT_FALSE(cg::has_intersection(a, b));
}

TEST(has_intersection, triangle_segment0)
{
   using cg::point_2;
   using cg::segment_2;
   using cg::triangle_2;

   triangle_2 t(point_2(0, 0), point_2(1, 1), point_2(2, 0));

   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 0), point_2(-1, -1))));

   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 1), point_2(2, 1))));
   EXPECT_FALSE(cg::has_intersection(t, segment_2(point_2(0, 2), point_2(2, 2))));

   triangle_2 t1(point_2(0.0, 0.0), point_2(2.0, 0.0), point_2(2.0, 2.0));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(0.0, 1.0), point_2(3.0, 1.0))));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(2.0, 1.0), point_2(3.0, 1.0))));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(2.0, 0.0), point_2(3.0, -1.0))));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(0.2, 0.1), point_2(1.5, 1.0))));
   EXPECT_FALSE(cg::has_intersection(t1, segment_2(point_2(-1.0, 1.0), point_2(2.0, 3.0))));
}

TEST(has_intersection, rectangle_segment)
{
   using cg::point_2;
   using cg::segment_2;
   using cg::rectangle_2;
   using cg::range;

   rectangle_2 r(range(0.0, 4.0), range(0.0, 4.0));
   EXPECT_FALSE(cg::has_intersection(r, segment_2(point_2(-2.0, -2.0), point_2(-1.0, -1.0))));
   EXPECT_TRUE(cg::has_intersection(r, segment_2(point_2(-1.0, -1.0), point_2(1.0, 1.0))));
   EXPECT_TRUE(cg::has_intersection(r, segment_2(point_2(-2.0, -2.0), point_2(0.0, 0.0))));

   range a(0, 2), b(0, 2);
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(-2, 2), point_2(2, 2))));
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(1, 1), point_2(1, 1.5))));
   EXPECT_FALSE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(0, 3), point_2(3, 3))));
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(-1, -1), point_2(3, 3))));
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(1, -1), point_2(1, 3))));

   cg::rectangle_2 rec(cg::range_t<double>(1, 5), cg::range_t<double>(1, 4));

   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(1, 1), point_2(5, 1))));
   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(1, 1), point_2(1, 4))));
   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(1, 4), point_2(5, 4))));
   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(5, 4), point_2(5, 1))));

   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(1, 1), point_2(5, 4))));
   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(1, 4), point_2(5, 4))));

   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(2, 2), point_2(3, 3))));

   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(2, 0), point_2(2, 3))));
   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(0, 3), point_2(20, 3))));
   EXPECT_TRUE(cg::has_intersection(rec, segment_2(point_2(0, 3), point_2(3, 0))));

   EXPECT_FALSE(cg::has_intersection(rec, segment_2(point_2(0, 3), point_2(0, 4))));
   EXPECT_FALSE(cg::has_intersection(rec, segment_2(point_2(0, 1), point_2(1, 0))));
   EXPECT_FALSE(cg::has_intersection(rec, segment_2(point_2(0, 10), point_2(20, 10))));
}


TEST(has_intersection, triangle_segment1)
{
   using cg::point_2;

   cg::triangle_2 t(point_2(0, 0), point_2(3, 0), point_2(0, 3));

   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 0), point_2(1, 1))));
   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 1), point_2(1, 0))));
   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 0), point_2(2, 2))));
   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(-2, 2), point_2(10, 2))));
   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(1, -1), point_2(-1, 1))));
}
