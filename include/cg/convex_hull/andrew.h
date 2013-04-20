#pragma once

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

#include <iostream>

namespace cg
{
   template <class BidIter>
   BidIter andrew_hull(BidIter p, BidIter q)
   {
      if (p == q)
         return p;

      BidIter it_min = std::min_element(p, q);
      BidIter it_max = std::max_element(p, q);

      std::iter_swap(p, it_min);

      BidIter t = p++;

      if (p == q)
         return p;

      std::iter_swap(p, it_max);

      BidIter s = p++;

      BidIter part = std::partition(p, q, [t, s] (point_2 const & a)
      {
         return orientation(*t, *s, a) != CG_LEFT;
      });


      for (BidIter i = p; i != q; ++i) std::cerr << *i;
      std::cerr << "------------" << std::endl;



      std::cerr << *t << std::endl;
      std::cerr << *s << std::endl;


      std::cerr << std::endl;


      BidIter l = --part;
      ++part;
      std::iter_swap(s, l);


      for (BidIter i = s; i != l; ++i) std::cerr << *i;
      std::cerr << std::endl;

      for (BidIter i = part; i != q; ++i) std::cerr << *i;
      std::cerr << std::endl;
      std::cerr << "===" << std::endl;



      std::sort(s, l, [] (point_2 const & a, point_2 const & b)
      {
         return a < b;
      });

      std::sort(part, q, [] (point_2 const & a, point_2 const & b)
      {
         if (a.x == b.x)
                return a.y < b.y;
         return a.x > b.x;
      });

      for (BidIter i = s; i != l; ++i) std::cerr << *i;
      std::cerr << std::endl;

      for (BidIter i = part; i != q; ++i) std::cerr << *i;
      std::cerr << std::endl;
      std::cerr << "===" << std::endl;

      std::cerr << std::endl << "------------" << std::endl;
      for (BidIter i = t; i != q; ++i) std::cerr << *i;
      std::cerr << std::endl;

      return cg::contour_graham_hull(t, q);
   }
}
