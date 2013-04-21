#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/rectangle.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/segment.h>

#include <cg/operations/contains/rectangle_point.h>
#include <cg/operations/has_intersection/triangle_segment.h>

namespace cg
{
   inline bool has_intersection(rectangle_2 const & t, segment_2 const & s)
   {
      triangle_2 t1(t.corner(0, 0), t.corner(1, 0), t.corner(1, 1));
      triangle_2 t2(t.corner(0, 0), t.corner(0, 1), t.corner(1, 1));

      return has_intersection(t1, s) || has_intersection(t2, s);
   }
}
