#pragma once

#include "tools.h"

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

namespace cg
{
   template <class BidIter>
   BidIter graham_hull(BidIter p, BidIter q)
   {
      if (p == q)
         return p;

      std::iter_swap(p, std::min_element(p, q));

      RandIter t = p++;

      if (p == q)
         return p;

      std::sort(p, q, [t] (point_2 const & a, point_2 const & b)
                        {
                           switch (orientation(*t, a, b))
                           {
                           case CG_LEFT: return true;
                           case CG_RIGHT: return false;
                           case CG_COLLINEAR: return a < b;
                           }
                        }
               );

      return contour_hull(t, q);
   }
}
