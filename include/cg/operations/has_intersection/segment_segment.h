#pragma once

#include <cg/primitives/segment.h>
#include <cg/operations/contains/segment_point.h>
#include <cg/operations/orientation.h>

namespace cg
{
   bool has_intersection(segment_2 a, segment_2 b)
   {
      orientation_t t0 = orientation(a[0], a[1], b[0]);
      orientation_t t1 = orientation(a[0], a[1], b[1]);

      if (t0 == t1 && t0 == CG_COLLINEAR) // segments is collinear
      {
         if (a[0] > a[1]) {
            std::swap(a[0], a[1]);
         }
         if (b[0] > b[1]) {
            std::swap(b[0], b[1]);
         }
         range_t<point_2> ra(a[0], a[1]);
         range_t<point_2> rb(b[0], b[1]);
         return !((ra & rb).is_empty());
      }

      orientation_t t2 = orientation(b[0], b[1], a[0]);
      orientation_t t3 = orientation(b[0], b[1], a[1]);

      return t0 != t1 && t2 != t3;
   }
}
