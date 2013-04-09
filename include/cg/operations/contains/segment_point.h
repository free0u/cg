#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>
#include <cg/primitives/range.h>

#include <cg/operations/orientation.h>

namespace cg
{
   inline bool contains(segment_2 s, point_2 const & q)
   {
      if (orientation(s[0], s[1], q) != CG_COLLINEAR)
      {
         return false;
      }

      return range_t<point_2>(min(s), max(s)).contains(q);
   }
}
