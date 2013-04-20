#pragma once

#include "tools.h"

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

#include <iostream>
#include <vector>
#include <iterator>

namespace cg
{
   template <class BidIter>
   BidIter andrew_hull(BidIter p, BidIter q)
   {
      if (p == q)
         return p;

      std::iter_swap(p, std::min_element(p, q));
      BidIter t = p++;

      if (p == q)
         return p;

      std::iter_swap(p, std::max_element(p, q));
      BidIter s = p++;

      BidIter part = std::partition(p, q, [t, s] (point_2 const & a)
      {
         return orientation(*t, *s, a) != CG_LEFT;
      });


      BidIter l = part;
      std::iter_swap(s, --l);

      std::sort(s, l);
      std::sort(part, q, std::greater<typename std::iterator_traits<BidIter>::value_type>());

      return cg::contour_hull(t, q);
   }
}
