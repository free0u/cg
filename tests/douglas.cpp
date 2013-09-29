#include <gtest/gtest.h>

#include "random_utils.h"

#include <boost/assign/list_of.hpp>

#include <cg/algorithms/douglas.h>

TEST(douglas, one_point)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(10, 15));
   std::vector<point_2> simple;

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 0, std::back_inserter(simple));
   EXPECT_EQ(a, simple);

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 0.1, std::back_inserter(simple));
   EXPECT_EQ(a, simple);

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 1, std::back_inserter(simple));
   EXPECT_EQ(a, simple);

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 100, std::back_inserter(simple));
   EXPECT_EQ(a, simple);
}


TEST(douglas, two_points)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(10, 15))
                                                  (point_2(4, 5));
   std::vector<point_2> simple;

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 0, std::back_inserter(simple));
   EXPECT_EQ(a, simple);

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 0.1, std::back_inserter(simple));
   EXPECT_EQ(a, simple);

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 1, std::back_inserter(simple));
   EXPECT_EQ(a, simple);

   simple.clear();
   cg::algoritms::simplify(a.begin(), a.end(), 100, std::back_inserter(simple));
   EXPECT_EQ(a, simple);
}


TEST(douglas, test0)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(2, 1))
                                                  (point_2(0, 4));
   double eps = 0.1;
   std::vector<point_2> b = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(2, 1))
                                                  (point_2(0, 4));
   std::vector<point_2> simple;
   cg::algoritms::simplify(a.begin(), a.end(), eps, std::back_inserter(simple));
   EXPECT_EQ(b, simple);
}

TEST(douglas, test1)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(2, 1))
                                                  (point_2(0, 4));
   double eps = 2;
   std::vector<point_2> b = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(2, 1))
                                                  (point_2(0, 4));
   std::vector<point_2> simple;
   cg::algoritms::simplify(a.begin(), a.end(), eps, std::back_inserter(simple));
   EXPECT_EQ(b, simple);
}

TEST(douglas, test1_1)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(2, 1))
                                                  (point_2(0, 4));
   double eps = 3;
   std::vector<point_2> b = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(0, 4));
   std::vector<point_2> simple;
   cg::algoritms::simplify(a.begin(), a.end(), eps, std::back_inserter(simple));
   EXPECT_EQ(b, simple);
}

TEST(douglas, test1_2)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(2, 1))
                                                  (point_2(4, 0));
   double eps = 3;
   std::vector<point_2> b = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(4, 0));
   std::vector<point_2> simple;
   cg::algoritms::simplify(a.begin(), a.end(), eps, std::back_inserter(simple));
   EXPECT_EQ(b, simple);
}

TEST(douglas, test2)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(0.1, 10))
                                                  (point_2(0.2, 0));
   double eps = 2;
   std::vector<point_2> b = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(0.1, 10))
                                                  (point_2(0.2, 0));
   std::vector<point_2> simple;
   cg::algoritms::simplify(a.begin(), a.end(), eps, std::back_inserter(simple));
   EXPECT_EQ(b, simple);
}

TEST(douglas, test3)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(0.1, 10))
                                                  (point_2(0.2, 0));
   double eps = 20;
   std::vector<point_2> b = boost::assign::list_of(point_2(0, 0))
                                                  (point_2(0.2, 0));
   std::vector<point_2> simple;
   cg::algoritms::simplify(a.begin(), a.end(), eps, std::back_inserter(simple));
   EXPECT_EQ(b, simple);
}


TEST(douglas, test4)
{
   using cg::point_2;
   std::vector<point_2> a = boost::assign::list_of(point_2(10, 10))
                                                  (point_2(15, 15))
                                                  (point_2(17, 17));
   double eps = 0.1;
   std::vector<point_2> b = boost::assign::list_of(point_2(10, 10))
                                                  (point_2(17, 17));
   std::vector<point_2> simple;
   cg::algoritms::simplify(a.begin(), a.end(), eps, std::back_inserter(simple));
   EXPECT_EQ(b, simple);
}

