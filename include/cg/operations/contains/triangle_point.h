#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/segment.h>

#include <cg/operations/orientation.h>
#include <cg/operations/contains/segment_point.h>
#include <algorithm>

namespace cg
{
   inline bool contains(triangle_2 const & t, point_2 const & q)
   {
      orientation_t to = orientation(t[0], t[1], t[2]);

      if (to == CG_COLLINEAR)
      {
         segment_2 s(*std::min_element(&t[0], &t[0] + 3),
                     *std::max_element(&t[0], &t[0] + 3));
         return contains(s, q);
      }

      for (int l = 0, ln = 2; l != 3; ln = l++) {
         if (opposite(orientation(t[ln], t[l], q), to)) {
            return false;
         }
      }
      return true;
   }
}
