#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/segment.h>

#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/has_intersection/segment_segment.h>

namespace cg
{
   inline bool has_intersection(triangle_2 const & t, segment_2 const & s)
   {
      if (contains(t, s[0]) || contains(t, s[1]))
      {
         return true;
      }

      for (size_t i = 0; i != 3; ++i)
      {
         if (has_intersection(t.side(i), s))
         {
            return true;
         }
      }
      return false;
   }
}
