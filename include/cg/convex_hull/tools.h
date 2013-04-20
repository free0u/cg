#pragma once

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

#include <iostream>
#include <ctime>
#include <vector>

namespace cg
{
   template <class BidIter>
   BidIter contour_graham_hull(BidIter p, BidIter q)
   {
      if (p == q) // 0
         return p;

      BidIter b = p;

      BidIter pt = p++;

      if (p == q) // 1
         return p;

      BidIter t = p++;

      if (p == q) // 2
         return p;

      while (p != q)
      {
         switch (orientation(*pt, *t, *p))
         {
         case CG_LEFT:
            pt = t++;
            std::iter_swap(t, p++);
            break;
         case CG_RIGHT:
            if (pt == b)
            {
               std::iter_swap(t, p++);
               break;
            }
            t = pt--;
            break;
         case CG_COLLINEAR:
            std::iter_swap(t, p);
            p++;
         }
      }

      while (orientation(*pt, *t, *b) == CG_RIGHT)
      {
         t = pt--;
      }

      if (b != pt && orientation(*pt, *t, *b) == CG_COLLINEAR)
      {
         --t;
      }

      return ++t;
   }
}
