#pragma once

#include "tools.h"

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

#include <iostream>
#include <vector>
#include <iterator>

using std::cerr;
using std::endl;

namespace cg
{
   template <class BidIter>
   BidIter out(BidIter p, BidIter q)
   {
      for (BidIter i = p; i != q; ++i) cerr << *i;
      cerr << endl;
   }



   template <class BidIter>
   BidIter quick_hull_helper(BidIter p, BidIter q, BidIter A, BidIter B)
   {

   }

   template <class BidIter>
   BidIter quick_hull(BidIter p, BidIter q)
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
         return orientation(*t, *s, a) != CG_RIGHT;
      });

      BidIter l = part;
      std::iter_swap(s, --l);

      out(t, l);
      out(l, q);

      return cg::contour_hull(t, q);
   }
}
